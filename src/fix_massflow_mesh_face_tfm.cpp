/* ----------------------------------------------------------------------
   LIGGGHTS - LAMMPS Improved for General Granular and Granular Heat
   Transfer Simulations

   LIGGGHTS is part of the CFDEMproject
   www.liggghts.com | www.cfdem.com

   Christoph Kloss, christoph.kloss@cfdem.com
   Copyright 2009-2012 JKU Linz
   Copyright 2012-     DCS Computing GmbH, Linz

   LIGGGHTS is based on LAMMPS
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   This software is distributed under the GNU General Public License.

   See the README file in the top-level directory.
------------------------------------------------------------------------- */

#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "atom.h"
#include "atom_vec.h"
#include "comm.h"
#include "modify.h"
#include "force.h"
#include "memory.h"
#include "update.h"
#include "error.h"
#include "mpi_liggghts.h"
#include "math_extra_liggghts.h"
#include "fix_massflow_mesh_face_tfm.h"
#include "cfd_datacoupling.h"
#include "fix_cfd_coupling.h"

using namespace LAMMPS_NS;
using namespace MathExtraLiggghts;
using namespace MathConst;
using namespace FixConst;

//#define INERTIA 0.4
//#define FAVRE_AVERAGED
/* ---------------------------------------------------------------------- */

FixMassflowMeshFaceTFM::FixMassflowMeshFaceTFM(LAMMPS *lmp, int narg, char **arg) :
  Fix(lmp, narg, arg),
  mass_(0.),
  nparticles_(0),
  shFactor_(1.),
  screenflag_(false),
  fp_(NULL),
  t_count_(0.),
  delta_t_(0.),
  insertion_frequency_counter_(0),
  cg_(1.),
  cg3_(1.)
{

    // parse args for this class
    int iarg = 3;
    cg_ = force->cg();
    cg3_ = cg_*cg_*cg_;
    bool hasargs = true;
    while(iarg < narg && hasargs)
    {
        hasargs = false;

        if(strcmp(arg[iarg],"couple_every") == 0){
            if(narg < iarg+2)
                error->fix_error(FLERR,this,"expecting keyword 'couple_every'");
        iarg++;
        couple_nevery_ = atoi(arg[iarg]);
        if(couple_nevery_ < 0)
          error->fix_error(FLERR,this,"'couple_every' value must be > 0");
        iarg++;
        hasargs = true;
        } else if(strcmp(arg[iarg],"n_MagnificationLensFaces") == 0) {
             if(narg < iarg+2)
                error->fix_error(FLERR,this,"Illegal keyword entry for 'n_MagnificationLensFaces'");
          iarg++;
          nFaces_ = atoi(arg[iarg]);
          if(nFaces_ < 0)
            error->fix_error(FLERR,this,"'n_MagnificationLensFaces' value must be > 0");
          iarg++;
          hasargs = true;
        } else if(strcmp(arg[iarg],"density") == 0) {
            if(narg < iarg+2)
               error->fix_error(FLERR,this,"Illegal keyword entry for 'density'");
            iarg++;
            density_ = atof(arg[iarg]);
            if(density_ < 0)
              error->fix_error(FLERR,this,"'density' value must be > 0");
            iarg++;
            hasargs = true;
        } else if(strcmp(arg[iarg],"shrink_factor") == 0) {
            if(narg < iarg+2)
               error->fix_error(FLERR,this,"Illegal keyword entry for 'shrink_factor'");
            iarg++;
            shFactor_ = atof(arg[iarg]);
            if(shFactor_ < 0)
              error->fix_error(FLERR,this,"'shrink_factor' value must be > 0");
            iarg++;
            hasargs = true;
        } else if(strcmp(arg[iarg],"radius") == 0) {
            if(narg < iarg+2)
               error->fix_error(FLERR,this,"Illegal keyword entry for 'radius'");
            iarg++;
            radius_ = atof(arg[iarg]);
            if(radius_ < 0)
              error->fix_error(FLERR,this,"'radius' value must be > 0");
            iarg++;
            hasargs = true;
        } else if(strcmp(arg[iarg],"file") == 0 || strcmp(arg[iarg],"append") == 0) {
            if(narg < iarg+2)
                error->fix_error(FLERR,this,"Illegal keyword entry");

            char* filecurrent = new char[strlen(arg[iarg+1]) + 8];
            if (1 < comm->nprocs) //open a separate file for each processor
                 sprintf(filecurrent,"%s%s%d",arg[iarg+1],".",comm->me);
            else  //open one file for proc 0
                 sprintf(filecurrent,"%s",arg[iarg+1]);

            if (strcmp(arg[iarg],"file") == 0)
                fp_ = fopen(filecurrent,"w");
            else
                fp_ = fopen(filecurrent,"a");
            if (fp_ == NULL) {
                char str[128];
                sprintf(str,"Cannot open file %s",arg[iarg+1]);
                error->fix_error(FLERR,this,str);
            }
            iarg += 2;
            hasargs = true;
          } else if (strcmp(arg[iarg],"screen") == 0) {
            if(narg < iarg+2)
                error->fix_error(FLERR,this,"Illegal keyword entry");
            if (strcmp(arg[iarg+1],"yes") == 0) screenflag_ = true;
            else if (strcmp(arg[iarg+1],"no") == 0) screenflag_ = false;
            else error->fix_error(FLERR,this,"Illegal screen option");
            iarg += 2;
            hasargs = true;
          } else if(strcmp(arg[iarg],"insertion_frequency") == 0) {
            if(narg < iarg+2)
               error->fix_error(FLERR,this,"Illegal keyword entry for 'insertion_frequency'");
            iarg++;
            insertion_frequency_ = atof(arg[iarg]);
            if(insertion_frequency_ < 0)
              error->fix_error(FLERR,this,"'insertion_frequency_' value must be > 0");
            iarg++;
            hasargs = true;
          }  else if(strcmp(style,"massflow/mesh/face/tfm") == 0) {
            error->fix_error(FLERR,this,"unknown keyword");
          } else {
            ++iarg;
            hasargs = true;
        }
    }

    radius_ /= shFactor_;

    if(fp_ && 1 < comm->nprocs && 0 == comm->me)
      fprintf(screen,"**FixMassflowMeshFaceTFM: > 1 process - will write to multiple files\n");

    restart_global = 1;

    vector_flag = 1;
    size_vector = 10;
    global_freq = 1; // available always

    array_flag = 1;
    size_array_rows = 1; // rows in global array
    size_array_cols = 17; // columns in global array
}

/* ---------------------------------------------------------------------- */

FixMassflowMeshFaceTFM::~FixMassflowMeshFaceTFM()
{
   if(fp_) fclose(fp_);
}

/* ---------------------------------------------------------------------- */

void FixMassflowMeshFaceTFM::post_create()
{

   int nfaceids = nFaces_;
    mass_face_.resize(nfaceids);
    nparticles_face_.resize(nfaceids);
    granTemp_cell_.resize(nfaceids);
    solidVol_frac_cell_.resize(nfaceids);
    vx_cell_.resize(nfaceids);
    vy_cell_.resize(nfaceids);
    vz_cell_.resize(nfaceids);
    reset_distributions(nfaceids);
    std::fill_n(mass_face_.begin(),            nfaceids, 0.);
    std::fill_n(nparticles_face_.begin(),      nfaceids, 0 );
    std::fill_n(granTemp_cell_.begin(),      nfaceids, 0. );
    std::fill_n(solidVol_frac_cell_.begin(),      nfaceids, 0. );
    std::fill_n(vx_cell_.begin(),      nfaceids, 0. );
    std::fill_n(vy_cell_.begin(),      nfaceids, 0. );
    std::fill_n(vz_cell_.begin(),      nfaceids, 0. );


    accumulated_mass_face_last_.resize(nfaceids);
    std::fill_n(accumulated_mass_face_last_.begin(), nfaceids, 0. );

    mass_face_this.resize(nfaceids, 0.);
    nparticles_face_this.resize(nfaceids, 0);
    granTemp_cell_this.resize(nfaceids, 0.);
    solidVol_frac_cell_this.resize(nfaceids, 0.);
    vx_cell_this.resize(nfaceids, 0.);
    vy_cell_this.resize(nfaceids, 0.);
    vz_cell_this.resize(nfaceids, 0.);
    accumulated_mass_face_this.resize(nfaceids, 0.);

    size_array_rows = nfaceids; // rows in global array
    fix_faceIDs_ = static_cast<FixPropertyGlobal*>(modify->find_fix_property("totPatchFaceIDs","property/global","vector",0,0,style));
    fix_facefluxes_ = static_cast<FixPropertyGlobal*>(modify->find_fix_property("totPatchFaceFluxes","property/global","vector",0,0,style));
    fix_cellVel_ = static_cast<FixPropertyGlobal*>(modify->find_fix_property("UsCell","property/global","matrix",0,3,style));
    fix_cellGranTemp_ = static_cast<FixPropertyGlobal*>(modify->find_fix_property("ThetaCell","property/global","vector",0,0,style));
    fix_cellSolidVolFrac_ = static_cast<FixPropertyGlobal*>(modify->find_fix_property("AlphaCell","property/global","vector",0,0,style));
}

/* ---------------------------------------------------------------------- */

void FixMassflowMeshFaceTFM::pre_delete(bool unfixflag)
{
    if (unfixflag)
    {
        modify->delete_fix(fixid_);
    }
}

/* ----------------------------------------------------------------------
   initialize this fix
------------------------------------------------------------------------- */

void FixMassflowMeshFaceTFM::init()
{

}

/* ---------------------------------------------------------------------- */

void FixMassflowMeshFaceTFM::setup(int /*vflag*/)
{
}

/* ---------------------------------------------------------------------- */

int FixMassflowMeshFaceTFM::setmask()
{
    int mask = 0;
    mask |= POST_INTEGRATE;
    return mask;
}

void FixMassflowMeshFaceTFM::reset_distributions(int size)
{
    distributions_face_.clear();
    distributions_face_.resize(size);
}

void FixMassflowMeshFaceTFM::post_integrate()
{
   FixCfdCoupling* fcfd = (FixCfdCoupling*)modify->find_fix_style_strict("couple/cfd",0);
   bigint checkFlag = fcfd ? fcfd->get_dc()->latestpull("totPatchFaceIDs") : -1;
   if (checkFlag == -1)
   {
         if (comm->me == 0) printf("Doing Nothing! \n");
   } else {
        const double *faceIDs_= fix_faceIDs_->get_values();
        // faceid2index_->first:  unique face id
        // faceid2index_->second: index in std::vector member variables
        for(int iFace= 0; iFace < nFaces_; ++iFace)
        {
            faceid2index_[faceIDs_[iFace]] = iFace;
        }
        int nfaceids = faceid2index_.size();

        // shFactor_ shrinks the real particle radius but the particle mass should stay intact to have the correct number of particles based on the mass flux
        double particleMass_ = density_ * (radius_ * shFactor_) * (radius_ * shFactor_) * (radius_ * shFactor_) * cg3_ * 4.*M_PI/3.; // mono-disperse particle mass

        if((update->ntimestep % couple_nevery_) == 2)
        {
            const double *facefluxes_ = fix_facefluxes_->get_values();
            double const* const* cellVel_ = fix_cellVel_->get_array();
            const double *cellGranTemp_ = fix_cellGranTemp_->get_values();
            const double *cellSolidVolFrac_ = fix_cellSolidVolFrac_->get_values();
            // update time for counter
            t_count_ += update->dt;
            insertion_frequency_counter_ += 1;
            // facefluxes_ and faceIDs_ arrays are allready broadcasted to all the processors in cfd_datacoupling_mpi.h
            // Therefore do the calculations on the master node and then broadcast the data
            if (comm->me == 0)
            {
               for (int iFace = 0; iFace < nfaceids; ++iFace)
                {
                    if (facefluxes_[iFace] > 0){
                        mass_face_this[iFace] = (facefluxes_[iFace] * update->dt * couple_nevery_) + accumulated_mass_face_last_[iFace];
                    } else {
                        mass_face_this[iFace] = accumulated_mass_face_last_[iFace];
                    }
                }
                // Corresponding granular temp in the cells next to the boundaries from TFM
                for (int iCell = 0; iCell < nfaceids; ++iCell) //face ids are equal to the cell ids!
                {
                    granTemp_cell_this[iCell] = cellGranTemp_[iCell];
                }
                // Corresponding solid volume fraction in the cells next to the boundaries from TFM
                for (int iCell = 0; iCell < nfaceids; ++iCell) //face ids are equal to the cell ids!
                {
                    solidVol_frac_cell_this[iCell] = cellSolidVolFrac_[iCell];
                }
                // Corresponding particle velocities in x-, y- and z-directions in the cells next to the boundaries from TFM
                for (int iCell = 0; iCell < nfaceids; ++iCell) //face ids are equal to the cell ids!
                {
                    vx_cell_this[iCell] = cellVel_[iCell][0];
                    vy_cell_this[iCell] = cellVel_[iCell][1];
                    vz_cell_this[iCell] = cellVel_[iCell][2];
                }
                for (int iFace = 0; iFace < nfaceids; ++iFace)
                {
                    if (facefluxes_[iFace] > 0) {
                        accumulated_mass_face_this[iFace] = mass_face_this[iFace];
                    } else {
                        accumulated_mass_face_this[iFace] = accumulated_mass_face_last_[iFace];
                    }

                }
                // storing the rounding error of nparticles_this
                if((insertion_frequency_counter_ % insertion_frequency_) == 0)
                {
                    printf("counter of frequency is: %d \n", insertion_frequency_counter_);
                   for (int iFace = 0; iFace < nfaceids; ++iFace)
                    {
                        if (facefluxes_[iFace] > 0) {
                           // monodisperse TFM
                           nparticles_face_this[iFace] = mass_face_this[iFace]/particleMass_;
                           nparticles_ += nparticles_face_this[iFace];
                           mass_ += nparticles_face_this[iFace]*particleMass_; // Total mass of the particles across all faces
                           accumulated_mass_face_this[iFace] = mass_face_this[iFace] - nparticles_face_this[iFace]*particleMass_;

                        } else {
                            accumulated_mass_face_this[iFace] = accumulated_mass_face_last_[iFace];
                            nparticles_face_this[iFace] = 0;
                            nparticles_ += 0;
                            mass_ += 0.0;
                        }

                    }
                }
                   // storing the variables in another array just to broadcast
                    for(int i=0; i<nfaceids; ++i)
                    {
                        mass_face_[i] = mass_face_this[i];
                        nparticles_face_[i] = nparticles_face_this[i];
                        granTemp_cell_[i] = granTemp_cell_this[i];
                        solidVol_frac_cell_[i] = solidVol_frac_cell_this[i];
                        vx_cell_[i] = vx_cell_this[i];
                        vy_cell_[i] = vy_cell_this[i];
                        vz_cell_[i] = vz_cell_this[i];
                        accumulated_mass_face_last_[i] = accumulated_mass_face_this[i];
                    }
               // }
            }

            MPI_Bcast(&nparticles_,1,MPI_INT,0,world);
            MPI_Bcast(&mass_,1,MPI_DOUBLE,0,world);
            MPI_Bcast(&mass_face_[0],mass_face_.size(), MPI_DOUBLE,0,world);
            MPI_Bcast(&nparticles_face_[0],nparticles_face_.size(), MPI_INT,0,world);
            MPI_Bcast(&granTemp_cell_[0],granTemp_cell_.size(), MPI_DOUBLE,0,world);
            MPI_Bcast(&solidVol_frac_cell_[0],solidVol_frac_cell_.size(), MPI_DOUBLE,0,world);
            MPI_Bcast(&vx_cell_[0],vx_cell_.size(), MPI_DOUBLE,0,world);
            MPI_Bcast(&vy_cell_[0],vy_cell_.size(), MPI_DOUBLE,0,world);
            MPI_Bcast(&vz_cell_[0],vz_cell_.size(), MPI_DOUBLE,0,world);
            MPI_Bcast(&accumulated_mass_face_last_[0],accumulated_mass_face_last_.size(), MPI_DOUBLE,0,world);

            // filling the face distributions on each processor
            if(nparticles_ > 0)
            {

                ConstantParticleTemplateSphere cpts;

                for(int i=0; i<nfaceids; ++i)
                {
                    if(nparticles_face_[i] > 0)
                    {
                        for(int p = 0; p < nparticles_face_[i]; ++p)
                        {
                            cpts.radius_ = radius_*cg_; //  monodisperse TFM
                            cpts.mass_ = (particleMass_/(shFactor_*shFactor_*shFactor_));  // monodisperse TFM
                            cpts.atomtype_ = 1; // monodisperse TFM
                            increment_distribution(cpts, i);
                        }
                    }
                }
            }


        } else {
            mass_ = 0.0;
            nparticles_ = 0;
            std::fill(mass_face_this.begin(), mass_face_this.end(), 0.);
            std::fill(nparticles_face_this.begin(), nparticles_face_this.end(), 0);
            std::fill(granTemp_cell_this.begin(), granTemp_cell_this.end(), 0.);
            std::fill(solidVol_frac_cell_this.begin(), solidVol_frac_cell_this.end(), 0.);
            std::fill(vx_cell_this.begin(), vx_cell_this.end(), 0.);
            std::fill(vy_cell_this.begin(), vy_cell_this.end(), 0.);
            std::fill(vz_cell_this.begin(), vz_cell_this.end(), 0.);
            std::fill(accumulated_mass_face_this.begin(), accumulated_mass_face_this.end(), 0);

            std::fill(mass_face_.begin(), mass_face_.end(), 0.);
            std::fill(nparticles_face_.begin(), nparticles_face_.end(), 0);
            std::fill(granTemp_cell_.begin(), granTemp_cell_.end(), 0.);
            std::fill(solidVol_frac_cell_.begin(), solidVol_frac_cell_.end(), 0.);
            std::fill(vx_cell_.begin(), vx_cell_.end(), 0.);
            std::fill(vy_cell_.begin(), vy_cell_.end(), 0.);
            std::fill(vz_cell_.begin(), vz_cell_.end(), 0.);

            reset_distributions(nfaceids);


        }
       }
}


void FixMassflowMeshFaceTFM::increment_distribution(const ConstantParticleTemplateSphere& cpts, int iface)
{
    distributions_face_[iface][cpts] += 1;
}


/* ----------------------------------------------------------------------
   pack entire state of Fix into one write
------------------------------------------------------------------------- */

void FixMassflowMeshFaceTFM::write_restart(FILE *fp)
{
  int n = 0;
  double list[3];
  list[n++] = mass_;
  list[n++] = t_count_;
  list[n++] = static_cast<double>(nparticles_);

  if (comm->me == 0) {
    int size = n * sizeof(double);
    fwrite(&size,sizeof(int),1,fp);
    fwrite(list,sizeof(double),n,fp);
  }
}

/* ----------------------------------------------------------------------
   use state info from restart file to restart the Fix
------------------------------------------------------------------------- */

void FixMassflowMeshFaceTFM::restart(char *buf)
{
  int n = 0;
  double *list = (double *) buf;

  mass_ = list[n++];
  t_count_ = list[n++];
  nparticles_ = static_cast<int>(list[n++]);
}

/* ----------------------------------------------------------------------
   output # of faces
------------------------------------------------------------------------- */

double FixMassflowMeshFaceTFM::compute_scalar()
{
    return faceid2index_.size();
}

/* ----------------------------------------------------------------------
   always returns fg number of particles (also when coarse-grained!)
   Choose the extrude_length in a way that fix_insert can insert all the
   particles at one time step!
------------------------------------------------------------------------- */

double FixMassflowMeshFaceTFM::compute_vector(int index)
{
    switch(index)
    {
    case 0:
        return mass_;
    case 1:
    {FixCfdCoupling* fcfd = (FixCfdCoupling*)modify->find_fix_style_strict("couple/cfd",0);
        bigint checkFlag = fcfd?fcfd->get_dc()->latestpull("totPatchFaceIDs"): -1;
        if (checkFlag == -1){
            return 0;
        }else {
            return static_cast<double>(nparticles_);
        }
     }
    default:
        return 0.;
    }
}


double FixMassflowMeshFaceTFM::compute_array(int i, int j)
{
  switch(j)
  {
  case 0:
      return mass_face_[i];
  case 1:
      return static_cast<double>(nparticles_face_[i]);
  case 2:
      return granTemp_cell_[i];
  case 3:
      return vx_cell_[i];
  case 4:
      return vy_cell_[i];
  case 5:
      return vz_cell_[i];
  case 6:
      return solidVol_frac_cell_[i];
  default:
      return 0.;
  }
}


double FixMassflowMeshFaceTFM::compute_array_by_id(int face_id, int j)
{
  if(faceid2index_.find(face_id) == faceid2index_.end())
      error->fix_error(FLERR, this, "Invalid face id!");

  return compute_array(faceid2index_[face_id], j);
}
