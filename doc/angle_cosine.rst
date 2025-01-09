.. index:: angle\_style cosine

angle\_style cosine command
===========================

angle\_style cosine/omp command
===============================

Syntax
""""""


.. parsed-literal::

   angle_style cosine

Examples
""""""""


.. parsed-literal::

   angle_style cosine
   angle_coeff \* 75.0

Description
"""""""""""

The *cosine* angle style uses the potential

.. image:: Eqs/angle_cosine.jpg
   :align: center

where K is defined for each angle type.

The following coefficients must be defined for each angle type via the
:doc:`angle\_coeff <angle_coeff>` command as in the example above, or in
the data file or restart files read by the :doc:`read\_data <read_data>`
or :doc:`read\_restart <read_restart>` commands:

* K (energy)


----------


Styles with a *cuda*\ , *gpu*\ , *omp*\ , or *opt* suffix are functionally
the same as the corresponding style without the suffix.  They have
been optimized to run faster, depending on your available hardware, as
discussed in :doc:`Section\_accelerate <Section_accelerate>` of the
manual.  The accelerated styles take the same arguments and should
produce the same results, except for round-off and precision issues.

These accelerated styles are part of the USER-CUDA, GPU, USER-OMP and OPT
packages, respectively.  They are only enabled if LAMMPS was built with
those packages.  See the :ref:`Making LAMMPS with optional packages <start_3>` section for more info.

You can specify the accelerated styles explicitly in your input script
by including their suffix, or you can use the :ref:`-suffix command-line switch <start_7>` when you invoke LAMMPS, or you can
use the :doc:`suffix <suffix>` command in your input script.

See :doc:`Section\_accelerate <Section_accelerate>` of the manual for
more instructions on how to use the accelerated styles effectively.


----------


Restrictions
""""""""""""


This angle style can only be used if LAMMPS was built with the
MOLECULE package.  See the :ref:`Making LAMMPS with optional packages <start_3>` section for more info on packages.

Related commands
""""""""""""""""

:doc:`angle\_coeff <angle_coeff>`

**Default:** none


