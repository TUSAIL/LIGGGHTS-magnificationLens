.. index:: fix speedcontrol

fix speedcontrol command
========================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID speedcontrol vx vy vz keyword value ...

* ID, group-ID are documented in :doc:`fix <fix>` command
* speedcontrol = style name of this fix command
* vx,vy,vz = set-velocity component values (velocity units)
  
  .. parsed-literal::
  
       any of vx,vy,vz can be a variable (see below)

* zero or more keyword/value pairs may be appended to args
* keyword = *region* or *gain*
  
  .. parsed-literal::
  
       *region* value = region-ID
         region-ID = ID of region atoms must be in to have added force
       *gain* value = gain
         gain = proportional gain of the proportional controller



Examples
""""""""


.. parsed-literal::

   fix kick flow speedcontrol 1.0 0.0 0.0
   fix kick flow speedcontrol 1.0 0.0 v_oscillate region force_reg
   fix kick flow speedcontrol 0.0 NULL v_push gain v_gain

Description
"""""""""""

Add vx,vy,vz to the corresponding component of the set-velocity for 
each atom in the group. This command can be used to constrain the 
velocity of the atoms in a simulation, e.g. at an outlet with a 
well-defined massflow (screw conveyor).

This fix applies a force to each atom which is proportional to the 
controller gain times the difference between the atom's velocity and 
the set-velocity.

Any of the 3 quantities defining the set-velocity can be specified
as an equal-style or atom-style :doc:`variable <variable>`, namely *vx*\ ,
*vy*\ , *vz*\ .  If the value is a variable, it should be specified as
v\_name, where name is the variable name.  In this case, the variable
will be evaluated each timestep, and its value(s) used to determine
the set-velocity component. Any of the x,y,z values can be specified 
as NULL which means do not include that dimension in the application 
of the velocity controller.

Equal-style variables can specify formulas with various mathematical
functions, and include :doc:`thermo\_style <thermo_style>` command
keywords for the simulation box parameters and timestep and elapsed
time.  Thus it is easy to specify a time-dependent force field.

Atom-style variables can specify the same formulas as equal-style
variables but can also include per-atom values, such as atom
coordinates.  Thus it is easy to specify a spatially-dependent force
field with optional time-dependence as well.

If the *region* keyword is used, the atom must also be in the
specified geometric :doc:`region <region>` in order to have its velocity 
controlled.


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

:doc:`fix addforce <fix_addforce>`, :doc:`fix drag <fix_drag>`

Default
"""""""

The option defaults are gain = 0.1


