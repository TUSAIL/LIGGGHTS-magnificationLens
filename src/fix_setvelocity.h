/* ----------------------------------------------------------------------
   LIGGGHTS - LAMMPS Improved for General Granular and Granular Heat
   Transfer Simulations

   LIGGGHTS is part of the CFDEMproject
   www.liggghts.com | www.cfdem.com

   LIGGGHTS is based on LAMMPS
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   This software is distributed under the GNU General Public License.

   See the README file in the top-level directory.
------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------
   Contributing authors:
   Tobias Kronlachner
------------------------------------------------------------------------- */

#ifdef FIX_CLASS

FixStyle(setvelocity,FixSetVelocity)

#else

#ifndef LMP_FIX_SET_VELOCITY_H
#define LMP_FIX_SET_VELOCITY_H

#include "fix.h"

namespace LAMMPS_NS {

/**
 * @brief FixSetVelocity
 *        sets the velocity of particles.
 *
 * This class sets the velocity of the particles in a given region
 */
class FixSetVelocity : public Fix {
 public:
  FixSetVelocity(class LAMMPS *, int, char **);
  ~FixSetVelocity();
  int setmask();
  void init();
  void setup(int);
  void min_setup(int);
  void post_force(int);
  void post_force_respa(int, int, int);
  void min_post_force(int);
  double memory_usage();

 private:
  double xvalue,yvalue,zvalue;
  int varflag,iregion;
  char *xstr,*ystr,*zstr;
  char *idregion;
  int xvar,yvar,zvar,evar,xstyle,ystyle,zstyle;
  int nlevels_respa;

  int maxatom;
  double **setvelocity;
};

}

#endif
#endif

/* ERROR/WARNING messages:


*/
