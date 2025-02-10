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
#include "fix_cfd_coupling_cell_tfm.h"
#include "fix_property_global.h"

using namespace LAMMPS_NS;
using namespace FixConst;
using namespace MathConst;

/* ---------------------------------------------------------------------- */

FixCfdCouplingCellTFM::FixCfdCouplingCellTFM(LAMMPS *lmp, int narg, char **arg) :  Fix(lmp, narg, arg),
   fix_UsCell_(NULL),
   fix_ThetaCell_(NULL),
   fix_AlphaCell_(NULL),
   fix_totPartVolCell_(NULL),
   fix_PXXCell_(NULL),
   fix_PYYCell_(NULL),
   fix_PZZCell_(NULL)
{
    num_patches = 0;
    iarg_ = 3;
    patch_names_ = NULL;
    num_cells_ = NULL;

    if (narg < iarg_ + 3)
        error->all (FLERR,"Fix couple/cfd/cell/tfm: Wrong number of arguments");

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

        else if (strcmp(arg[iarg_],"n_cells") == 0)
        {

            if (iarg_ + num_patches > narg)
                error->fix_error(FLERR,this, "Wrong number of arguments");
            num_cells_ = new int[num_patches];
            iarg_++;
            for (int i = 0; i < num_patches; ++i)
            {
                num_cells_[i] = atoi(arg[iarg_]);
                iarg_++;
            }
            hasargs = true;

        }

        else if (strcmp(this->style,"couple/cfd/cell/tfm") == 0)
        {
            error->fix_error(FLERR,this,"unknown keyword");
        }
    }

}

/* ---------------------------------------------------------------------- */

FixCfdCouplingCellTFM::~FixCfdCouplingCellTFM()
{
        if (patch_names_)   for (int i = 0; i < num_patches; i++) delete [] patch_names_[i];

        delete [] patch_names_;
        delete [] num_cells_;
}

/* ---------------------------------------------------------------------- */

void FixCfdCouplingCellTFM::pre_delete(bool unfixflag)
{
    if (unfixflag && fix_UsCell_) modify->delete_fix("UsCell");
    if (unfixflag && fix_ThetaCell_) modify->delete_fix("ThetaCell");
    if (unfixflag && fix_AlphaCell_) modify->delete_fix("AlphaCell");
    if (unfixflag && fix_totPartVolCell_) modify->delete_fix("totPartVolCell");
    if (unfixflag && fix_PXXCell_) modify->delete_fix("PXXCell");
    if (unfixflag && fix_PYYCell_) modify->delete_fix("PYYCell");
    if (unfixflag && fix_PZZCell_) modify->delete_fix("PZZCell");

}

/* ---------------------------------------------------------------------- */

int FixCfdCouplingCellTFM::setmask()
{
    int mask = 0;
    return mask;
}

/* ---------------------------------------------------------------------- */

void FixCfdCouplingCellTFM::post_create()
{
    // calculating the total number of cells to match the size of array receiving from CFDEMcoupling
    int sum_ = 0;
    for (int i = 0; i < num_patches; i++)
    {
        sum_ += num_cells_[i];
    }

    // register particle velocities per cell array
    fix_UsCell_ = static_cast<FixPropertyGlobal*>(modify->find_fix_property("UsCell","property/global","matrix",sum_,3,style,false));
        
    // fill the arguments
    if(!fix_UsCell_)
    {
        const char* fixarg[6 + 3*sum_];
        fixarg[0]="UsCell";
        fixarg[1]="all";
        fixarg[2]="property/global";
        fixarg[3]="UsCell";
        fixarg[4]="matrix";
        fixarg[5]="3";        
        for (int i = 0; i < 3*sum_; i++)
        {
            fixarg[i+6] = "-1.";
        }

        
       fix_UsCell_ = modify->add_fix_property_global((6+3*sum_),const_cast<char**>(fixarg),style);
    
    }

    // register granular temperature per cell array
    fix_ThetaCell_ = static_cast<FixPropertyGlobal*>(modify->find_fix_property("ThetaCell","property/global","vector",sum_,0,style,false));

    // fill the arguments
    if(!fix_ThetaCell_)
    {
        const char* fixarg[5 + sum_];
        fixarg[0]="ThetaCell";
        fixarg[1]="all";
        fixarg[2]="property/global";
        fixarg[3]="ThetaCell";
        fixarg[4]="vector";
        for (int i = 0; i < sum_; i++)
        {
            fixarg[i+5] = "-1.";
        }

        
        fix_ThetaCell_ = modify->add_fix_property_global((5+sum_),const_cast<char**>(fixarg),style);
    
    }

    // register solids volume fraction per cell array
    fix_AlphaCell_ = static_cast<FixPropertyGlobal*>(modify->find_fix_property("AlphaCell","property/global","vector",sum_,0,style,false));

    // fill the arguments
    if(!fix_AlphaCell_)
    {
        const char* fixarg[5 + sum_];
        fixarg[0]="AlphaCell";
        fixarg[1]="all";
        fixarg[2]="property/global";
        fixarg[3]="AlphaCell";
        fixarg[4]="vector";
        for (int i = 0; i < sum_; i++)
        {
            fixarg[i+5] = "-1.";
        }


        fix_AlphaCell_ = modify->add_fix_property_global((5+sum_),const_cast<char**>(fixarg),style);

    }

    // register total paticle volumes per cell array
    fix_totPartVolCell_ = static_cast<FixPropertyGlobal*>(modify->find_fix_property("totPartVolCell","property/global","vector",sum_,0,style,false));

    // fill the arguments
    if(!fix_totPartVolCell_)
    {
        const char* fixarg[5 + sum_];
        fixarg[0]="totPartVolCell";
        fixarg[1]="all";
        fixarg[2]="property/global";
        fixarg[3]="totPartVolCell";
        fixarg[4]="vector";
        for (int i = 0; i < sum_; i++)
        {
            fixarg[i+5] = "-1.";
        }


        fix_totPartVolCell_ = modify->add_fix_property_global((5+sum_),const_cast<char**>(fixarg),style);

    }

    // register diagonal components of the total stress per cell array
    fix_PXXCell_ = static_cast<FixPropertyGlobal*>(modify->find_fix_property("PXXCell","property/global","vector",sum_,0,style,false));

    // fill the arguments
    if(!fix_PXXCell_ )
    {
        const char* fixarg[5 + sum_];
        fixarg[0]="PXXCell";
        fixarg[1]="all";
        fixarg[2]="property/global";
        fixarg[3]="PXXCell";
        fixarg[4]="vector";
        for (int i = 0; i < sum_; i++)
        {
            fixarg[i+5] = "-1.";
        }

        
        fix_PXXCell_  = modify->add_fix_property_global((5+sum_),const_cast<char**>(fixarg),style);
    
    }


    fix_PYYCell_ = static_cast<FixPropertyGlobal*>(modify->find_fix_property("PYYCell","property/global","vector",sum_,0,style,false));

    // fill the arguments
    if(!fix_PYYCell_ )
    {
        const char* fixarg[5 + sum_];
        fixarg[0]="PYYCell";
        fixarg[1]="all";
        fixarg[2]="property/global";
        fixarg[3]="PYYCell";
        fixarg[4]="vector";
        for (int i = 0; i < sum_; i++)
        {
            fixarg[i+5] = "-1.";
        }

        
        fix_PYYCell_  = modify->add_fix_property_global((5+sum_),const_cast<char**>(fixarg),style);
    
    }
    

    fix_PZZCell_ = static_cast<FixPropertyGlobal*>(modify->find_fix_property("PZZCell","property/global","vector",sum_,0,style,false));

    // fill the arguments
    if(!fix_PZZCell_ )
    {
        const char* fixarg[5 + sum_];
        fixarg[0]="PZZCell";
        fixarg[1]="all";
        fixarg[2]="property/global";
        fixarg[3]="PZZCell";
        fixarg[4]="vector";
        for (int i = 0; i < sum_; i++)
        {
            fixarg[i+5] = "-1.";
        }

        
        fix_PZZCell_  = modify->add_fix_property_global((5+sum_),const_cast<char**>(fixarg),style);
    
    }    

}

/* ---------------------------------------------------------------------- */

void FixCfdCouplingCellTFM::init()
{
    // make sure there is only one fix of this style
    if (modify->n_fixes_style(style) != 1)
        error->fix_error(FLERR,this,"More than one fix of this style is not allowed");

    // find coupling fix
    fix_coupling_ = static_cast<FixCfdCoupling*>(modify->find_fix_style_strict("couple/cfd",0));
    if (!fix_coupling_)
        error->fix_error(FLERR,this,"needs a fix of type couple/cfd");

    // values to come from OF
    fix_coupling_->add_pull_property("UsCell","matrix-global");
    fix_coupling_->add_pull_property("ThetaCell","vector-global");
    fix_coupling_->add_pull_property("AlphaCell","vector-global");
    fix_coupling_->add_pull_property("totPartVolCell","vector-global");
    fix_coupling_->add_pull_property("PXXCell","vector-global");
    fix_coupling_->add_pull_property("PYYCell","vector-global");
    fix_coupling_->add_pull_property("PZZCell","vector-global");

}

/* ---------------------------------------------------------------------- */
