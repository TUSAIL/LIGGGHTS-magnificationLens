/* ----------------------------------------------------------------------
   LIGGGHTS - LAMMPS Improved for General Granular and Granular Heat
   Transfer Simulations

   LIGGGHTS is part of the CFDEMproject
   www.liggghts.com | www.cfdem.com

   Copyright 2021- Eindhoven University of Technology

   LIGGGHTS is based on LAMMPS
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   This software is distributed under the GNU General Public License.

   See the README file in the top-level directory.
------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------
   Contributing authors:
   Behrad Esgandari, JKU, PFM 2023-
------------------------------------------------------------------------- */

#include <string.h>
#include <stdlib.h>
#include "atom.h"
#include "atom_vec.h"
#include "update.h"
#include "respa.h"
#include "error.h"
#include "neighbor.h"
#include "memory.h"
#include "modify.h"
#include "group.h"
#include "comm.h"
#include <math.h>
#include "vector_liggghts.h"
#include "math_const.h"
#include "mpi_liggghts.h"
#include "fix_cfd_coupling_face_tfm.h"
#include "fix_property_global.h"

using namespace LAMMPS_NS;
using namespace FixConst;
using namespace MathConst;

/* ---------------------------------------------------------------------- */

FixCfdCouplingFaceTFM::FixCfdCouplingFaceTFM(LAMMPS *lmp, int narg, char **arg) :  Fix(lmp, narg, arg),
   fix_fluxes_(NULL),
   fix_faceids_(NULL)
{
    num_patches = 0;
    iarg_ = 3;
    patch_names_ = NULL;
    num_faceids_ = NULL;

    if (narg < iarg_ + 3)
        error->all (FLERR,"Fix couple/cfd/face/tfm: Wrong number of arguments");

    bool hasargs = true;

    while (iarg_ < narg && hasargs)
    {
        hasargs = false;

        if (strcmp(arg[iarg_],"n_patches") == 0)
        {
            if (iarg_ + 2 > narg)
                error->fix_error(FLERR,this,"Wrong number of arguments in n_patches");
            iarg_++;
            num_patches = atoi(arg[iarg_]);
            if (num_patches < 1)
                error->fix_error(FLERR,this,"n_patches > 0 is required");
            hasargs = true;
            iarg_ ++;
        }
        else if (strcmp(arg[iarg_],"patch_names") == 0)
        {
            if (num_patches < 1)
                error->fix_error (FLERR,this, "have to define number of patches before 'patch_names'");
            if (iarg_ + num_patches > narg)
                error->fix_error(FLERR,this, "Wrong number of arguments");
            patch_names_ = new char*[num_patches];
            iarg_++;
            for (int i = 0; i < num_patches; ++i)
            {
                patch_names_[i] = new char[strlen(arg[iarg_])+1];
                strcpy(patch_names_[i], arg[iarg_]);
                iarg_++;
            }
            hasargs = true;
        }

        else if (strcmp(arg[iarg_],"n_faceids") == 0)
        {

            if (iarg_ + num_patches > narg)
                error->fix_error(FLERR,this, "Wrong number of arguments");
            num_faceids_ = new int[num_patches];
            iarg_++;
            for (int i = 0; i < num_patches; ++i)
            {
                num_faceids_[i] = atoi(arg[iarg_]);
                iarg_++;
            }
            hasargs = true;

        }

        else if (strcmp(this->style,"couple/cfd/face/tfm") == 0)
        {
            error->fix_error(FLERR,this,"unknown keyword");
        }
    }

}

/* ---------------------------------------------------------------------- */

FixCfdCouplingFaceTFM::~FixCfdCouplingFaceTFM()
{
        if (patch_names_)   for (int i = 0; i < num_patches; i++) delete [] patch_names_[i];

        delete [] patch_names_;
        delete [] num_faceids_;
}

/* ---------------------------------------------------------------------- */

void FixCfdCouplingFaceTFM::pre_delete(bool unfixflag)
{
    if (unfixflag && fix_faceids_) modify->delete_fix("totPatchFaceIDs");
    if (unfixflag && fix_fluxes_) modify->delete_fix("totPatchFaceFluxes");
}

/* ---------------------------------------------------------------------- */

int FixCfdCouplingFaceTFM::setmask()
{
    int mask = 0;
    return mask;
}

/* ---------------------------------------------------------------------- */

void FixCfdCouplingFaceTFM::post_create()
{
    // calculating the total number of patch face ids to match the size of array receiving from CFDEMcoupling
    int sum_ = 0;
    for (int i = 0; i < num_patches; i++)
    {
        sum_ += num_faceids_[i];
        //printf("Number of face ids in the face/tfm is: %d \n", num_faceids_[i]);
    }



    // register face ids
    fix_faceids_ = static_cast<FixPropertyGlobal*>(modify->find_fix_property("totPatchFaceIDs","property/global","vector",sum_,0,style,false));
        
    // fill the arguments
    if(!fix_faceids_)
    {
        const char* fixarg[5 + sum_];
        fixarg[0]="totPatchFaceIDs";
        fixarg[1]="all";
        fixarg[2]="property/global";
        fixarg[3]="totPatchFaceIDs";
        fixarg[4]="vector";
        for (int i = 0; i < sum_; i++)
        {
            fixarg[i+5] = "-1.";
        }

        
       fix_faceids_ = modify->add_fix_property_global((5+sum_),const_cast<char**>(fixarg),style);
    
    }

    // register face fluxes
    fix_fluxes_ = static_cast<FixPropertyGlobal*>(modify->find_fix_property("totPatchFaceFluxes","property/global","vector",sum_,0,style,false));

    // fill the arguments
    if(!fix_fluxes_)
    {
        const char* fixarg[5 + sum_];
        fixarg[0]="totPatchFaceFluxes";
        fixarg[1]="all";
        fixarg[2]="property/global";
        fixarg[3]="totPatchFaceFluxes";
        fixarg[4]="vector";
        for (int i = 0; i < sum_; i++)
        {
            fixarg[i+5] = "-1.";
        }

        
        fix_fluxes_ = modify->add_fix_property_global((5+sum_),const_cast<char**>(fixarg),style);
    
    }
}

/* ---------------------------------------------------------------------- */

void FixCfdCouplingFaceTFM::init()
{
    // make sure there is only one fix of this style
    if (modify->n_fixes_style(style) != 1)
        error->fix_error(FLERR,this,"More than one fix of this style is not allowed");

    // find coupling fix
    fix_coupling_ = static_cast<FixCfdCoupling*>(modify->find_fix_style_strict("couple/cfd",0));
    if (!fix_coupling_)
        error->fix_error(FLERR,this,"needs a fix of type couple/cfd");

    // values to come from OF
    fix_coupling_->add_pull_property("totPatchFaceIDs","vector-global");
    fix_coupling_->add_pull_property("totPatchFaceFluxes","vector-global");
}

/* ---------------------------------------------------------------------- */
