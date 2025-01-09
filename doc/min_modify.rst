.. index:: min\_modify

min\_modify command
===================

Syntax
""""""


.. parsed-literal::

   min_modify keyword values ...

* one or more keyword/value pairs may be listed
  
  .. parsed-literal::
  
     keyword = *dmax* or *line*
       *dmax* value = max
         max = maximum distance for line search to move (distance units)
       *line* value = *backtrack* or *quadratic*\ or *forcezero*
         backtrack,quadratic,forcezero = style of linesearch to use



Examples
""""""""


.. parsed-literal::

   min_modify dmax 0.2

Description
"""""""""""

This command sets parameters that affect the energy minimization
algorithms selected by the :doc:`min\_style <min_style>` command.  The
various settings may affect the convergence rate and overall number of
force evaluations required by a minimization, so users can experiment
with these parameters to tune their minimizations.

The *cg* and *sd* minimization styles have an outer iteration and an
inner iteration which is steps along a one-dimensional line search in
a particular search direction.  The *dmax* parameter is how far any
atom can move in a single line search in any dimension (x, y, or z).
For the *quickmin* and *fire* minimization styles, the *dmax* setting
is how far any atom can move in a single iteration (timestep).  Thus a
value of 0.1 in real :doc:`units <units>` means no atom will move
further than 0.1 Angstroms in a single outer iteration.  This prevents
highly overlapped atoms from being moved long distances (e.g. through
another atom) due to large forces.

The choice of line search algorithm for the *cg* and *sd* minimization
styles can be selected via the *line* keyword.  The default
backtracking search is robust and should always find a local energy
minimum.  However, it will "converge" when it can no longer reduce the
energy of the system.  Individual atom forces may still be larger than
desired at this point, because the energy change is measured as the
difference of two large values (energy before and energy after) and
that difference may be smaller than machine epsilon even if atoms
could move in the gradient direction to reduce forces further.

By contrast, the *quadratic* line search algorithm tries to 
reduce the forces to zero, while guaranteeing that the energy
changes is not positive (uphill). For some systems, it may also 
be more efficient than the backtracking algorithm by 
requiring fewer energy/force evaluations. The *forcezero* 
line search algorithm is similar to *quadratic*\ .
It may be more efficient than *quadratic* on some systems.

Restrictions
""""""""""""
 none

Related commands
""""""""""""""""

:doc:`min\_style <min_style>`, :doc:`minimize <minimize>`

Default
"""""""

The option defaults are dmax = 0.1 and line = backtrack.


