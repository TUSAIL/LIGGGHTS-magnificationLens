.. index:: pair\_coeff

pair\_coeff command
===================

Syntax
""""""


.. parsed-literal::

   pair_coeff I J args

* I,J = atom types (see asterisk form below)
* args = coefficients for one or more pairs of atom types

Examples
""""""""


.. parsed-literal::

   pair_coeff 1 2 1.0 1.0 2.5
   pair_coeff 2 \* 1.0 1.0
   pair_coeff 3\* 1\*2 1.0 1.0 2.5
   pair_coeff \* \* 1.0 1.0
   pair_coeff \* \* nialhjea 1 1 2
   pair_coeff \* 3 morse.table ENTRY1
   pair_coeff 1 2 lj/cut 1.0 1.0 2.5 (for pair_style hybrid)

Description
"""""""""""

Specify the pairwise force field coefficients for one or more pairs of
atom types.  The number and meaning of the coefficients depends on the
pair style.  Pair coefficients can also be set in the data file read
by the :doc:`read\_data <read_data>` command or in a restart file.

I and J can be specified in one of two ways.  Explicit numeric values
can be used for each, as in the 1st example above.  I <= J is
required.  LAMMPS sets the coefficients for the symmetric J,I
interaction to the same values.

A wildcard asterisk can be used in place of or in conjunction with the
I,J arguments to set the coefficients for multiple pairs of atom
types.  This takes the form "\*" or "\*n" or "n\*" or "m\*n".  If N = the
number of atom types, then an asterisk with no numeric values means all
types from 1 to N.  A leading asterisk means all types from 1 to n
(inclusive).  A trailing asterisk means all types from n to N
(inclusive).  A middle asterisk means all types from m to n
(inclusive).  Note that only type pairs with I <= J are considered; if
asterisks imply type pairs where J < I, they are ignored.

Note that a pair\_coeff command can override a previous setting for the
same I,J pair.  For example, these commands set the coeffs for all I,J
pairs, then overwrite the coeffs for just the I,J = 2,3 pair:


.. parsed-literal::

   pair_coeff \* \* 1.0 1.0 2.5
   pair_coeff 2 3 2.0 1.0 1.12

A line in a data file that specifies pair coefficients uses the exact
same format as the arguments of the pair\_coeff command in an input
script, with the exception of the I,J type arguments.  In each line of
the "Pair Coeffs" section of a data file, only a single type I is
specified, which sets the coefficients for type I interacting with
type I.  This is because the section has exactly N lines, where N =
the number of atom types.  For this reason, the wild-card asterisk
should also not be used as part of the I argument.  Thus in a data
file, the line corresponding to the 1st example above would be listed
as


.. parsed-literal::

   2 1.0 1.0 2.5

For many potentials, if coefficients for type pairs with I != J are
not set explicitly by a pair\_coeff command, the values are inferred
from the I,I and J,J settings by mixing rules; see the
:doc:`pair\_modify <pair_modify>` command for a discussion.  Details on
this option as it pertains to individual potentials are described on
the doc page for the potential.

Many pair styles, typically for many-body potentials, use tabulated
potential files as input, when specifying the pair\_coeff command.
Potential files provided with LAMMPS are in the potentials directory
of the distribution.  For some potentials, such as EAM, other archives
of suitable files can be found on the Web.  They can be used with
LAMMPS so long as they are in the format LAMMPS expects, as discussed
on the individual doc pages.

When a pair\_coeff command using a potential file is specified, LAMMPS
looks for the potential file in 2 places.  First it looks in the
location specified.  E.g. if the file is specified as "niu3.eam", it
is looked for in the current working directory.  If it is specified as
"../potentials/niu3.eam", then it is looked for in the potentials
directory, assuming it is a sister directory of the current working
directory.  If the file is not found, it is then looked for in the
directory specified by the LAMMPS\_POTENTIALS environment variable.
Thus if this is set to the potentials directory in the LAMMPS distro,
then you can use those files from anywhere on your system, without
copying them into your working directory.  Environment variables are
set in different ways for different shells.  Here are example settings
for


.. parsed-literal::

   csh, tcsh:
   % setenv LAMMPS_POTENTIALS /path/to/lammps/potentials

   bash:
   % export LAMMPS_POTENTIALS=/path/to/lammps/potentials

   Windows:
   % set LAMMPS_POTENTIALS="C:\Path to LAMMPS\Potentials


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


This command must come after the simulation box is defined by a
:doc:`read\_data <read_data>`, :doc:`read\_restart <read_restart>`, or
:doc:`create\_box <create_box>` command.

Related commands
""""""""""""""""

:doc:`pair\_style <pair_style>`, :doc:`pair\_modify <pair_modify>`,
:doc:`read\_data <read_data>`, :doc:`read\_restart <read_restart>`,
:doc:`pair\_write <pair_write>`

**Default:** none


