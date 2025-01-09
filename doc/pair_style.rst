.. index:: pair\_style

pair\_style command
===================

Syntax
""""""


.. parsed-literal::

   pair_style style args

* style = one of the styles from the list below
* args = arguments used by a particular style

Examples
""""""""


.. parsed-literal::

   pair_style lj/cut 2.5
   pair_style eam/alloy
   pair_style hybrid lj/charmm/coul/long 10.0 eam
   pair_style table linear 1000
   pair_style none

Description
"""""""""""

Set the formula(s) LAMMPS uses to compute pairwise interactions.  In
LAMMPS, pair potentials are defined between pairs of atoms that are
within a cutoff distance and the set of active interactions typically
changes over time.  See the :doc:`bond\_style <bond_style>` command to
define potentials between pairs of bonded atoms, which typically
remain in place for the duration of a simulation.

In LAMMPS, pairwise force fields encompass a variety of interactions,
some of which include many-body effects, e.g. EAM, Stillinger-Weber,
Tersoff, REBO potentials.  They are still classified as "pairwise"
potentials because the set of interacting atoms changes with time
(unlike molecular bonds) and thus a neighbor list is used to find
nearby interacting atoms.

Hybrid models where specified pairs of atom types interact via
different pair potentials can be setup using the *hybrid* pair style.

The coefficients associated with a pair style are typically set for
each pair of atom types, and are specified by the
:doc:`pair\_coeff <pair_coeff>` command or read from a file by the
:doc:`read\_data <read_data>` or :doc:`read\_restart <read_restart>`
commands.

The :doc:`pair\_modify <pair_modify>` command sets options for mixing of
type I-J interaction coefficients and adding energy offsets or tail
corrections to Lennard-Jones potentials.  Details on these options as
they pertain to individual potentials are described on the doc page
for the potential.  Likewise, info on whether the potential
information is stored in a :doc:`restart file <write_restart>` is listed
on the potential doc page.

In the formulas listed for each pair style, *E* is the energy of a
pairwise interaction between two atoms separated by a distance *r*\ .
The force between the atoms is the negative derivative of this
expression.

If the pair\_style command has a cutoff argument, it sets global
cutoffs for all pairs of atom types.  The distance(s) can be smaller
or larger than the dimensions of the simulation box.

Typically, the global cutoff value can be overridden for a specific
pair of atom types by the :doc:`pair\_coeff <pair_coeff>` command.  The
pair style settings (including global cutoffs) can be changed by a
subsequent pair\_style command using the same style.  This will reset
the cutoffs for all atom type pairs, including those previously set
explicitly by a :doc:`pair\_coeff <pair_coeff>` command.  The exceptions
to this are that pair\_style *table* and *hybrid* settings cannot be
reset.  A new pair\_style command for these styles will wipe out all
previously specified pair\_coeff values.


----------


Here is an alphabetic list of pair styles defined in LAMMPS.  Click on
the style to display the formula it computes, arguments specified in
the pair\_style command, and coefficients specified by the associated
:doc:`pair\_coeff <pair_coeff>` command.

Note that there are also additional pair styles submitted by users
which are included in the LAMMPS distribution.  The list of these with
links to the individual styles are given in the pair section of :ref:`this page <cmd_5>`.

There are also additional accelerated pair styles included in the
LAMMPS distribution for faster performance on CPUs and GPUs.  The list
of these with links to the individual styles are given in the pair
section of :ref:`this page <cmd_5>`.

* :doc:`pair\_style none <pair_none>` - turn off pairwise interactions
* :doc:`pair\_style hybrid <pair_hybrid>` - multiple styles of pairwise interactions
* :doc:`pair\_style hybrid/overlay <pair_hybrid>` - multiple styles of superposed pairwise interactions

* :doc:`pair\_style adp <pair_adp>` - angular dependent potential (ADP) of Mishin
* :doc:`pair\_style airebo <pair_airebo>` - AIREBO potential of Stuart
* :doc:`pair\_style beck <pair_beck>` - Beck potential
* :doc:`pair\_style body <pair_body>` - interactions between body particles
* :doc:`pair\_style bop <pair_bop>` - BOP potential of Pettifor
* :doc:`pair\_style born <pair_born>` - Born-Mayer-Huggins potential
* :doc:`pair\_style born/coul/long <pair_born>` - Born-Mayer-Huggins with long-range Coulombics
* :doc:`pair\_style born/coul/msm <pair_born>` - Born-Mayer-Huggins with long-range MSM Coulombics
* :doc:`pair\_style born/coul/wolf <pair_born>` - Born-Mayer-Huggins with Coulombics via Wolf potential
* :doc:`pair\_style brownian <pair_brownian>` - Brownian potential for Fast Lubrication Dynamics
* :doc:`pair\_style brownian/poly <pair_brownian>` - Brownian potential for Fast Lubrication Dynamics with polydispersity
* :doc:`pair\_style buck <pair_buck>` - Buckingham potential
* :doc:`pair\_style buck/coul/cut <pair_buck>` - Buckingham with cutoff Coulomb
* :doc:`pair\_style buck/coul/long <pair_buck>` - Buckingham with long-range Coulombics
* :doc:`pair\_style buck/coul/msm <pair_buck>` - Buckingham long-range MSM Coulombics
* :doc:`pair\_style buck/long/coul/long <pair_buck>` - long-range Buckingham with long-range Coulombics
* :doc:`pair\_style colloid <pair_colloid>` - integrated colloidal potential
* :doc:`pair\_style comb <pair_comb>` - charge-optimized many-body (COMB) potential
* :doc:`pair\_style coul/cut <pair_coul>` - cutoff Coulombic potential
* :doc:`pair\_style coul/debye <pair_coul>` - cutoff Coulombic potential with Debye screening
* :doc:`pair\_style coul/dsf <pair_coul>` - Coulombics via damped shifted forces
* :doc:`pair\_style coul/long <pair_coul>` - long-range Coulombic potential
* :doc:`pair\_style coul/msm <pair_coul>` - long-range MSM Coulombics
* :doc:`pair\_style coul/wolf <pair_coul>` - Coulombics via Wolf potential
* :doc:`pair\_style dipole/cut <pair_dipole>` - point dipoles with cutoff
* :doc:`pair\_style dpd <pair_dpd>` - dissipative particle dynamics (DPD)
* :doc:`pair\_style dpd/tstat <pair_dpd>` - DPD thermostatting
* :doc:`pair\_style dsmc <pair_dsmc>` - Direct Simulation Monte Carlo (DSMC)
* :doc:`pair\_style eam <pair_eam>` - embedded atom method (EAM)
* :doc:`pair\_style eam/alloy <pair_eam>` - alloy EAM
* :doc:`pair\_style eam/fs <pair_eam>` - Finnis-Sinclair EAM
* :doc:`pair\_style eim <pair_eim>` - embedded ion method (EIM)
* :doc:`pair\_style gauss <pair_gauss>` - Gaussian potential
* :doc:`pair\_style gayberne <pair_gayberne>` - Gay-Berne ellipsoidal potential
* :doc:`pair\_style gran/hertz/history <pair_gran>` - granular potential with Hertzian interactions
* :doc:`pair\_style gran/hooke <pair_gran>` - granular potential with history effects
* :doc:`pair\_style gran/hooke/history <pair_gran>` - granular potential without history effects
* :doc:`pair\_style hbond/dreiding/lj <pair_hbond_dreiding>` - DREIDING hydrogen bonding LJ potential
* :doc:`pair\_style hbond/dreiding/morse <pair_hbond_dreiding>` - DREIDING hydrogen bonding Morse potential
* :doc:`pair\_style kim <pair_kim>` - interface to potentials provided by KIM project
* :doc:`pair\_style lcbop <pair_lcbop>` - long-range bond-order potential (LCBOP)
* :doc:`pair\_style line/lj <pair_line_lj>` - LJ potential between line segments
* :doc:`pair\_style lj/charmm/coul/charmm <pair_charmm>` - CHARMM potential with cutoff Coulomb
* :doc:`pair\_style lj/charmm/coul/charmm/implicit <pair_charmm>` - CHARMM for implicit solvent
* :doc:`pair\_style lj/charmm/coul/long <pair_charmm>` - CHARMM with long-range Coulomb
* :doc:`pair\_style lj/charmm/coul/msm <pair_charmm>` - CHARMM with long-range MSM Coulombics
* :doc:`pair\_style lj/class2 <pair_class2>` - COMPASS (class 2) force field with no Coulomb
* :doc:`pair\_style lj/class2/coul/cut <pair_class2>` - COMPASS with cutoff Coulomb
* :doc:`pair\_style lj/class2/coul/long <pair_class2>` - COMPASS with long-range Coulomb
* :doc:`pair\_style lj/cut <pair_lj>` - cutoff Lennard-Jones potential with no Coulomb
* :doc:`pair\_style lj/cut/coul/cut <pair_lj>` - LJ with cutoff Coulomb
* :doc:`pair\_style lj/cut/coul/debye <pair_lj>` - LJ with Debye screening added to Coulomb
* :doc:`pair\_style lj/cut/coul/dsf <pair_lj>` - LJ with Coulombics via damped shifted forces
* :doc:`pair\_style lj/cut/coul/long <pair_lj>` - LJ with long-range Coulombics
* :doc:`pair\_style lj/cut/coul/msm <pair_lj>` - LJ with long-range MSM Coulombics
* :doc:`pair\_style lj/cut/tip4p/cut <pair_lj>` - LJ with cutoff Coulomb for TIP4P water
* :doc:`pair\_style lj/cut/tip4p/long <pair_lj>` - LJ with long-range Coulomb for TIP4P water
* :doc:`pair\_style lj/expand <pair_lj_expand>` - Lennard-Jones for variable size particles
* :doc:`pair\_style lj/gromacs <pair_gromacs>` - GROMACS-style Lennard-Jones potential
* :doc:`pair\_style lj/gromacs/coul/gromacs <pair_gromacs>` - GROMACS-style LJ and Coulombic potential
* :doc:`pair\_style lj/long/coul/long <pair_lj_long>` - long-range LJ and long-range Coulombics
* :doc:`pair\_style lj/long/tip4p/long <pair_lj_long>` - long-range LJ and long-range Coulomb for TIP4P water
* :doc:`pair\_style lj/smooth <pair_lj_smooth>` - smoothed Lennard-Jones potential
* :doc:`pair\_style lj/smooth/linear <pair_lj_smooth_linear>` - linear smoothed Lennard-Jones potential
* :doc:`pair\_style lj96/cut <pair_lj96>` - Lennard-Jones 9/6 potential
* :doc:`pair\_style lubricate <pair_lubricate>` - hydrodynamic lubrication forces
* :doc:`pair\_style lubricate/poly <pair_lubricate>` - hydrodynamic lubrication forces with polydispersity
* :doc:`pair\_style lubricateU <pair_lubricateU>` - hydrodynamic lubrication forces for Fast Lubrication Dynamics
* :doc:`pair\_style lubricateU/poly <pair_lubricateU>` - hydrodynamic lubrication forces for Fast Lubrication with polydispersity
* :doc:`pair\_style meam <pair_meam>` - modified embedded atom method (MEAM)
* :doc:`pair\_style mie/cut <pair_mie>` - Mie potential
* :doc:`pair\_style morse <pair_morse>` - Morse potential
* :doc:`pair\_style peri/lps <pair_peri>` - peridynamic LPS potential
* :doc:`pair\_style peri/pmb <pair_peri>` - peridynamic PMB potential
* :doc:`pair\_style reax <pair_reax>` - ReaxFF potential
* :doc:`pair\_style rebo <pair_airebo>` - 2nd generation REBO potential of Brenner
* :doc:`pair\_style resquared <pair_resquared>` - Everaers RE-Squared ellipsoidal potential
* :doc:`pair\_style soft <pair_soft>` - Soft (cosine) potential
* :doc:`pair\_style sw <pair_sw>` - Stillinger-Weber 3-body potential
* :doc:`pair\_style table <pair_table>` - tabulated pair potential
* :doc:`pair\_style tersoff <pair_tersoff>` - Tersoff 3-body potential
* :doc:`pair\_style tersoff/zbl <pair_tersoff_zbl>` - Tersoff/ZBL 3-body potential
* :doc:`pair\_style tri/lj <pair_tri_lj>` - LJ potential between triangles
* :doc:`pair\_style yukawa <pair_yukawa>` - Yukawa potential
* :doc:`pair\_style yukawa/colloid <pair_yukawa_colloid>` - screened Yukawa potential for finite-size particles
* :doc:`pair\_style zbl <pair_zbl>` - Ziegler-Biersack-Littmark potential


----------


Restrictions
""""""""""""


This command must be used before any coefficients are set by the
:doc:`pair\_coeff <pair_coeff>`, :doc:`read\_data <read_data>`, or
:doc:`read\_restart <read_restart>` commands.

Some pair styles are part of specific packages.  They are only enabled
if LAMMPS was built with that package.  See the :ref:`Making LAMMPS <start_3>` section for more info on packages.
The doc pages for individual pair potentials tell if it is part of a
package.

Related commands
""""""""""""""""

:doc:`pair\_coeff <pair_coeff>`, :doc:`read\_data <read_data>`,
:doc:`pair\_modify <pair_modify>`, :doc:`kspace\_style <kspace_style>`,
:doc:`dielectric <dielectric>`, :doc:`pair\_write <pair_write>`

Default
"""""""


.. parsed-literal::

   pair_style none


