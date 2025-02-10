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

#ifdef FIX_CLASS

FixStyle(couple/cfd/cell/tfm,FixCfdCouplingCellTFM)

#else

#ifndef LMP_FIX_CFD_COUPLING_CELL_TFM_H
#define LMP_FIX_CFD_COUPLING_CELL_TFM_H

#include "fix_cfd_coupling.h"
#include <vector>

namespace LAMMPS_NS {

class FixCfdCouplingCellTFM : public Fix {

 public:
  FixCfdCouplingCellTFM(class LAMMPS *, int, char **);
  ~FixCfdCouplingCellTFM();
  void post_create();
  void pre_delete(bool unfixflag);

  virtual int setmask();
  virtual void init();

 protected:
  int num_patches;      // # of patches
  int iarg_;
  char **patch_names_;  // list of patch names
  int *num_cells_;    // # of patch face ids

  class FixCfdCoupling* fix_coupling_;
  class FixPropertyGlobal* fix_UsCell_;
  class FixPropertyGlobal* fix_ThetaCell_;
  class FixPropertyGlobal* fix_AlphaCell_;
  class FixPropertyGlobal* fix_totPartVolCell_;
  class FixPropertyGlobal* fix_PXXCell_;
  class FixPropertyGlobal* fix_PYYCell_;
  class FixPropertyGlobal* fix_PZZCell_;


};

}

#endif
#endif
