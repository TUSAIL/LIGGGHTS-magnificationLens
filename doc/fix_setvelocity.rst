.. index:: fix setvelocity

fix setvelocity command
=======================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID setvelocity vx vy vz keyword value ...

* ID, group-ID are documented in :doc:`fix <fix>` command
* setvelocity = style name of this fix command
* vx,vy,vz = set-velocity component values (velocity units)
  
  .. parsed-literal::
  
       any of vx,vy,vz can be a variable (see below)



Examples
""""""""


.. parsed-literal::

   fix vel all setvelocity NULL 7.0 NULL
   fix vel all setvelocity 0.0 7.0 0.0
   fix vel all setvelocity NULL NULL v_var

Description
"""""""""""

This fix sets the specified velocity components vx,vy,vz for 
each atom in the group. This command can be used to constrain the 
velocity of the atoms in a simulation, e.g. at an outlet with a 
well-defined massflow (screw conveyor).

Any of the 3 quantities defining the set-velocity can be specified
as an equal-style or atom-style :doc:`variable <variable>`, namely *vx*\ ,
*vy*\ , *vz*\ .  If the value is a variable, it should be specified as
v\_name, where name is the variable name.  In this case, the variable
will be evaluated each timestep, and its value(s) used to determine
the set-velocity component. Any of the x,y,z values can be specified 
as NULL which means they stay untouched.

Equal-style variables can specify formulas with various mathematical
functions, and include :doc:`thermo\_style <thermo_style>` command
keywords for the simulation box parameters and timestep and elapsed
time.  Thus it is easy to specify a time-dependent velocity field.

Atom-style variables can specify the same formulas as equal-style
variables but can also include per-atom values, such as atom
coordinates.  Thus it is easy to specify a spatially-dependent velocity
field with optional time-dependence as well.


----------


**Restart, fix\_modify, output, run start/stop, minimize info:**

No information about this fix is written to :doc:`binary restart files <restart>`.

No parameter of this fix can be used with the *start/stop* keywords of
the :doc:`run <run>` command.

Restrictions
""""""""""""
 none

Related commands
""""""""""""""""

:doc:`fix addforce <fix_addforce>`, :doc:`fix drag <fix_drag>`, :doc:`fix speedcontrol <fix_speedcontrol>`

Default
"""""""


