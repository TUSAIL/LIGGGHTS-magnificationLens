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

#ifdef FIX_CLASS

FixStyle(massflow/mesh/face/tfm,FixMassflowMeshFaceTFM)

#else

#ifndef LMP_FIX_MASSFLOW_MESH_FACE_TFM_H
#define LMP_FIX_MASSFLOW_MESH_FACE_TFM_H

#include <vector>
#include <map>
#include <set>
#include "fix.h"
#include "constParticleTemplateSphere.h"


namespace LAMMPS_NS {

class FixMassflowMeshFaceTFM : public Fix {

  friend class FixInsertPackFaceTFM;

 public:

  FixMassflowMeshFaceTFM(class LAMMPS *lmp, int narg, char ** arg);
  ~FixMassflowMeshFaceTFM();

  virtual void post_create();
  virtual void pre_delete(bool unfixflag);

  virtual void init();
  virtual void setup(int vflag);
  virtual int setmask();

  virtual void post_integrate();
 // virtual void pre_exchange();

  virtual void write_restart(FILE *fp);
  virtual void restart(char *buf);

  virtual double compute_scalar();
  virtual double compute_vector(int index);
  virtual double compute_array(int i, int j);

 protected:

  virtual double compute_array_by_id(int face_id, int j);

  virtual const std::map<int, int>& get_face_ids() const
  {
    return faceid2index_;
  }

  virtual int get_face_ids_size() const
  {
    return faceid2index_.size();
  }

  char fixid_[200];

  // mass and particles which was counted
  double mass_;
  int nparticles_;
  int couple_nevery_; // coupling interval for DEM simulations
  int nFaces_; // # number of magnification lens faces equal to the size of arrays from cfdemcoupling!
  double density_; // particle density
  double radius_; // particle radius
  double shFactor_; //The factor that shrinks the particle radius (useful for insertion in dense regions)

  // Arrays to store the data in the current time step and send it to the insert_pack!
  std::vector<double> mass_face_;
  std::vector<int> nparticles_face_;
  std::vector<double> granTemp_cell_;
  std::vector<double> solidVol_frac_cell_;
  std::vector<double> vx_cell_;
  std::vector<double> vy_cell_;
  std::vector<double> vz_cell_;
  std::vector<double> accumulated_mass_face_last_;

  // data write
  bool screenflag_;
  FILE *fp_;

  // data for particle and mass flow calculation
  double t_count_, delta_t_;
  int insertion_frequency_counter_;
  int insertion_frequency_;


  std::map<int, int> faceid2index_;
  double cg_, cg3_;

  // containers holding per timestep values
  // using member variables to avoid extensive memory reallocation
  std::vector<double> mass_face_this;
  std::vector<int> nparticles_face_this;
  std::vector<double> granTemp_cell_this;
  std::vector<double> solidVol_frac_cell_this;
  std::vector<double> vx_cell_this;
  std::vector<double> vy_cell_this;
  std::vector<double> vz_cell_this;
  std::vector<double> accumulated_mass_face_this;

  class FixPropertyGlobal *fix_faceIDs_;
  class FixPropertyGlobal *fix_facefluxes_;
  class FixPropertyGlobal *fix_cellVel_;
  class FixPropertyGlobal *fix_cellGranTemp_;
  class FixPropertyGlobal *fix_cellSolidVolFrac_;


 private:

  std::vector<DiscreteParticleDistribution> distributions_face_;
  virtual void reset_distributions(int);
  virtual void increment_distribution(const ConstantParticleTemplateSphere&, int);


  const std::vector<DiscreteParticleDistribution>& get_distributions()
  { return distributions_face_; }


}; //end class

}
#endif
#endif
