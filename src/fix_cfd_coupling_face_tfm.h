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

FixStyle(couple/cfd/face/tfm, FixCfdCouplingFaceTFM)

#else

#ifndef LMP_FIX_CFD_COUPLING_FACE_TFM_H
#define LMP_FIX_CFD_COUPLING_FACE_TFM_H

#include "fix_cfd_coupling.h"
#include <vector>

namespace LAMMPS_NS {

class FixCfdCouplingFaceTFM : public Fix {

 public:
  FixCfdCouplingFaceTFM(class LAMMPS *, int, char **);
  ~FixCfdCouplingFaceTFM();
  void post_create();
  void pre_delete(bool unfixflag);

  virtual int setmask();
  virtual void init();

 protected:
  int num_patches;      // # of patches
  int iarg_;
  char **patch_names_;  // list of patch names
  int *num_faceids_;    // # of patch face ids

  class FixCfdCoupling* fix_coupling_;
  class FixPropertyGlobal* fix_fluxes_;
  class FixPropertyGlobal* fix_faceids_;

};

}

#endif
#endif
