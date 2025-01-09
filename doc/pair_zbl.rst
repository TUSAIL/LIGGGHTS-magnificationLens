.. index:: pair\_style zbl

pair\_style zbl command
=======================

pair\_style zbl/omp command
===========================

Syntax
""""""


.. parsed-literal::

   pair_style zbl inner outer

* inner = distance where switching function begins
* outer = global cutoff for ZBL interaction

Examples
""""""""


.. parsed-literal::

   pair_style zbl 3.0 4.0
   pair_coeff \* \* 73.0
   pair_coeff 1 1 14.0

Description
"""""""""""

Style *zbl* computes the Ziegler-Biersack-Littmark (ZBL) screened nuclear
repulsion for describing high-energy collisions between atoms.
:ref:`(Ziegler) <Ziegler>`. It includes an additional switching function 
that ramps the energy, force, and curvature smoothly to zero 
between an inner and outer cutoff. The potential
energy due to a pair of atoms at a distance r\_ij is given by:

.. image:: Eqs/pair_zbl.jpg
   :align: center

where e is the electron
charge, epsilon\_0 is the electrical permittivity of vacuum, and 
Z\_i and Z\_j are the nuclear charges of the two atoms in electron
charge units. 
The switching
function S(r) is identical to that used by 
:doc:`pair\_style lj/gromacs <pair_gromacs>`. 
Here, the inner and outer cutoff are the same 
for all pairs of atom types.

The following coefficient must be defined for each pair of atom types
via the :doc:`pair\_coeff <pair_coeff>` command as in the examples above,
or in the LAMMPS data file. 
Z can not be specified for two different atoms types.
Therefore the lists of atom types I and atom types J must match.

* Z (electron charge)

Although Z must be defined for all atom type pairs I,J, it is only
stored for individual atom types, i.e. when I = J.  Z is normally equal
to the atomic number of the atom type.

.. warning::

   The numerical values of the exponential decay
   constants in the screening function depend on the unit of distance. In
   the above equation they are given for units of angstroms. LAMMPS will
   automatically convert these values to the distance unit of the
   specified LAMMPS :doc:`units <units>` setting.  The values of Z should
   always be given in units of electron charge.


----------


Styles with a *cuda*\ , *gpu*\ , *omp*\ , or *opt* suffix are functionally
the same as the corresponding style without the suffix.  They have
been optimized to run faster, depending on your available hardware, as
discussed in :doc:`Section\_accelerate <Section_accelerate>` of the
manual.  The accelerated styles take the same arguments and should
produce the same results, except for round-off and precision issues.

These accelerated styles are part of the USER-CUDA, GPU, USER-OMP and OPT
packages, respectively.  They are only enabled if LAMMPS was built with
those packages.  See the :ref:`Making LAMMPS <start_3>`
section for more info.

You can specify the accelerated styles explicitly in your input script
by including their suffix, or you can use the :ref:`-suffix command-line switch <start_7>` when you invoke LAMMPS, or you can
use the :doc:`suffix <suffix>` command in your input script.

See :doc:`Section\_accelerate <Section_accelerate>` of the manual for
more instructions on how to use the accelerated styles effectively.


----------


**Mixing, shift, table, tail correction, restart, rRESPA info**\ :

Mixing is not relevant for this pair style, since as explained above,
Z values are stored on a per-type basis, and both Zi and Zj are used
explicitly in the ZBL formula.

The ZBL pair style does not support the :doc:`pair\_modify <pair_modify>`
shift option, since the ZBL interaction is already smoothed to 0.0 at
the cutoff.

The :doc:`pair\_modify <pair_modify>` table option is not relevant for
this pair style.

This pair style does not support the :doc:`pair\_modify <pair_modify>`
tail option for adding long-range tail corrections to energy and
pressure, since there are no corrections for a potential that goes to
0.0 at the cutoff.

This pair style does not write information to :doc:`binary restart files <restart>`, so pair\_style and pair\_coeff commands must be
specified in an input script that reads a restart file.

This pair style can only be used via the *pair* keyword of the
:doc:`run\_style respa <run_style>` command.  It does not support the
*inner*\ , *middle*\ , *outer* keywords.


----------


Restrictions
""""""""""""
 none

Related commands
""""""""""""""""

:doc:`pair\_coeff <pair_coeff>`

**Default:** none


----------


.. _Ziegler:



**(Ziegler)** J.F. Ziegler, J. P. Biersack and U. Littmark, "The
Stopping and Range of Ions in Matter," Volume 1, Pergamon, 1985.


