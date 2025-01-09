.. index:: suffix

suffix command
==============

Syntax
""""""


.. parsed-literal::

   suffix style

* style = *off* or *on* or *opt* or *omp* or *gpu* or *cuda*

Examples
""""""""


.. parsed-literal::

   suffix off
   suffix on
   suffix gpu

Description
"""""""""""

This command allows you to use variants of various styles if they
exist.  In that respect it operates the same as the :ref:`-suffix command-line switch <start_7>`.  It also has options
to turn off/on any suffix setting made via the command line.

The specified style can be *opt*\ , *omp*\ , *gpu*\ , or *cuda*\ .  These refer to
optional packages that LAMMPS can be built with, as described in :ref:`this section of the manual <start_3>`.  The "opt" style
corresponds to the OPT package, the "omp" style to the USER-OMP package, 
the "gpu" style to the GPU package, and the "cuda" style to the
USER-CUDA package.

These are the variants these packages provide:

* OPT = a handful of pair styles, cache-optimized for faster CPU
  performance
* USER-OMP = a collection of pair, bond, angle, dihedral, improper,
  kspace, compute, and fix styles with support for OpenMP
  multi-threading
* GPU = a handful of pair styles and the PPPM kspace\_style, optimized to
  run on one or more GPUs or multicore CPU/GPU nodes
* USER-CUDA = a collection of atom, pair, fix, compute, and integrate
  styles, optimized to run on one or more NVIDIA GPUs

As an example, all of the packages provide a :doc:`pair\_style lj/cut <pair_lj>` variant, with style names lj/cut/opt, lj/cut/omp,
lj/cut/gpu, or lj/cut/cuda.  A variant styles can be specified
explicitly in your input script, e.g. pair\_style lj/cut/gpu.  If the
suffix command is used with the appropriate style, you do not need to
modify your input script.  The specified suffix (opt,omp,gpu,cuda) is
automatically appended whenever your input script command creates a
new :doc:`atom <atom_style>`, :doc:`pair <pair_style>`,
:doc:`bond <bond_style>`, :doc:`angle <angle_style>`,
:doc:`dihedral <dihedral_style>`, :doc:`improper <improper_style>`,
:doc:`kspace <kspace_style>`, :doc:`fix <fix>`, :doc:`compute <compute>`, or
:doc:`run <run_style>` style.  If the variant version does not exist,
the standard version is created.

If the specified style is *off*\ , then any previously specified suffix
is temporarily disabled, whether it was specified by a command-line
switch or a previous suffix command.  If the specified style is *on*\ ,
a disabled suffix is turned back on.  The use of these 2 commands lets
your input script use a standard LAMMPS style (i.e. a non-accelerated
variant), which can be useful for testing or benchmarking purposes.
Of course this is also possible by not using any suffix commands, and
explicitly appending or not appending the suffix to the relevant
commands in your input script.

Restrictions
""""""""""""
 none

Related commands
""""""""""""""""

:ref:`Command-line switch -suffix <start_7>`

**Default:** none


