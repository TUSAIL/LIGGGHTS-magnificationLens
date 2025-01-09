.. index:: dihedral\_style quadratic

dihedral\_style quadratic command
=================================

dihedral\_style quadratic/omp command
=====================================

Syntax
""""""


.. parsed-literal::

   dihedral_style quadratic

Examples
""""""""


.. parsed-literal::

   dihedral_style quadratic
   dihedral_coeff 100.0 80.0

Description
"""""""""""

The *quadratic* dihedral style uses the potential:

.. image:: Eqs/dihedral_quadratic.jpg
   :align: center

This dihedral potential can be used to keep a dihedral in a predefined value.

The following coefficients must be defined for each dihedral type via the
:doc:`dihedral\_coeff <dihedral_coeff>` command as in the example above, or in
the data file or restart files read by the :doc:`read\_data <read_data>`
or :doc:`read\_restart <read_restart>` commands:

* K (energy/radian\^2)
* phi0 (degrees)


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


Restrictions
""""""""""""


This angle style can only be used if LAMMPS was built with the
USER\_MISC package.  See the :ref:`Making LAMMPS <start_3>` 
section for more info on packages.

Related commands
""""""""""""""""

:doc:`dihedral\_coeff <dihedral_coeff>`

**Default:** none


