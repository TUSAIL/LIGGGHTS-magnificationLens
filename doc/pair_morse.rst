.. index:: pair\_style morse

pair\_style morse command
=========================

pair\_style morse/cuda command
==============================

pair\_style morse/gpu command
=============================

pair\_style morse/omp command
=============================

pair\_style morse/opt command
=============================

Syntax
""""""


.. parsed-literal::

   pair_style morse cutoff

* cutoff = global cutoff for Morse interactions (distance units)

Examples
""""""""


.. parsed-literal::

   pair_style morse 2.5
   pair_coeff \* \* 100.0 2.0 1.5
   pair_coeff 1 1 100.0 2.0 1.5 3.0

Description
"""""""""""

Style *morse* computes pairwise interactions with the formula

.. image:: Eqs/pair_morse.jpg
   :align: center

Rc is the cutoff.

The following coefficients must be defined for each pair of atoms
types via the :doc:`pair\_coeff <pair_coeff>` command as in the examples
above, or in the data file or restart files read by the
:doc:`read\_data <read_data>` or :doc:`read\_restart <read_restart>`
commands:

* D0 (energy units)
* alpha (1/distance units)
* r0 (distance units)
* cutoff (distance units)

The last coefficient is optional.  If not specified, the global morse
cutoff is used.


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

None of these pair styles support mixing.  Thus, coefficients for all
I,J pairs must be specified explicitly.

All of these pair styles support the :doc:`pair\_modify <pair_modify>`
shift option for the energy of the pair interaction.

The :doc:`pair\_modify <pair_modify>` table options is not relevant for
the Morse pair styles.

None of these pair styles support the :doc:`pair\_modify <pair_modify>`
tail option for adding long-range tail corrections to energy and
pressure.

All of these pair styles write their information to :doc:`binary restart files <restart>`, so pair\_style and pair\_coeff commands do not need
to be specified in an input script that reads a restart file.

These pair styles can only be used via the *pair* keyword of the
:doc:`run\_style respa <run_style>` command.  They do not support the
*inner*\ , *middle*\ , *outer* keywords.


----------


Restrictions
""""""""""""
 none

Related commands
""""""""""""""""

:doc:`pair\_coeff <pair_coeff>`

**Default:** none


