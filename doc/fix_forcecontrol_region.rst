.. index:: fix forcecontrol/region

fix forcecontrol/region command
===============================

fix forcecontrol/region/universe command
========================================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID forcecontrol/region control_keywords control_values
   fix ID group-ID forcecontrol/region/universe control_keywords control_values ukeywords uvalues

* ID, group-ID are documented in :doc:`fix <fix>` command
* forcecontrol/region = style name of this fix command
* control\_keyword/value pairs
* control\_keywords = *ctrlPV* (obligatory) or *actual\_val* (obligatory) or *target\_val* (obligatory) or *velocity\_limit* or *kp* or *ki* or *kd* or *actual\_cg* or *target\_cg* or *max\_cg*
  
  .. parsed-literal::
  
     *ctrlPV* values = *stress* or *velocity*
         stress = use stress as control process value
         velocity = use velocity as control process value
     *actual_val* values = fix-ID
         fix-ID = ID of a :doc:`fix ave/euler/region <fix_ave_euler_region>` command that holds the actual values for the controller
     *target_val* values = fix-ID
         fix-ID = ID of a :doc:`fix ave/euler/region <fix_ave_euler_region>` or :doc:`fix ave/euler/region/universe <fix_ave_euler_region>` command that holds the target values for the controller
     *velocity_limit* values = mode value
         mode = *off* or *on* or *relative* or *absolute*
         value = N/A to *off* or *on* mode, allowed deviation from target velocity for *relative* and *absolute* mode
     *kp* values = k
         k = proportional constant for PID controller 
     *ki* values = k
         k = integral constant for PID controller
     *kd* values = k
         k = differential constant for PID controller
     *actual_cg* values = cg
         cg = coarse-grain ratio of the actual particles (N/A to universe version)
     *target_cg* values = cg
         cg = coarse-grain ratio of the target particles (N/A to universe version)
     *max_cg* values = cg
         cg = maximum coarse-grain ratio in the simulation (N/A to universe version)

* two ukeyword/uvalue pairs must be appended for the universe version of this command
* ukeywords = *receive\_from\_partition* and *couple\_every*
  
  .. parsed-literal::
  
       *receive_from_partition* value = partition
         partition = partition to receive data from in multi-partition simulations
       *couple_every* value = interval
         interval = time interval for receiving data



Examples
""""""""


.. parsed-literal::

   fix stressctrl resolved forcecontrol/region ctrlPV stress actual_val resolvedave target_val coarseave kp 1. ki 10000. cg 2
   fix velocityctrl coarse forcecontrol/region ctrlPV velocity actual_val coarseave target_val resolvedave kp 0.1

Description
"""""""""""

This fix applies cell-wise forces on particles inside a hexhedral grid
until either a granular pressure (for *ctrlPV* = stress) or an average
velocity (for *ctrlPV* = velocity) is reached.
The actual cell-wise stress or velocity values are calculated by a
:doc:`fix ave/euler/region <fix_ave_euler_region>`, which is defined via
the keyword *actual\_val*. 
The cell-wise target stress or velocity values are calculated by a
:doc:`fix ave/euler/region <fix_ave_euler_region>`, which is defined via
the keyword *target\_val*.

For *ctrlPV* = stress the controller force is applied only in a boundary
layer of a cell with a thickness of 1.3 times the maximum particle diameter
d\_max. After this layer the force decays in a sine squared fashion within
0.25\*d\_max. The direction of the force is determined via the grid geometry
which should hold a vectorial element property with the label 'stress\_ctrl\_dir'
(e.g. by specifying a cell\_data property in the VTK geometry file).

For *ctrlPV* = velocity the controller force is kept constant over
the whole cell.

The controller itself is a proportional-integral-derivative (PID)
controller which is defined by 3 constants *kp*\ , *ki*\ , *kd*\ :

output = kp \* error + ki \* errorsum + kd \* errorchange

where 'error' is the current deviation of the control process value to the target value, 
'errorsum' is the time integration (sum) of the error values and 'errorchange' its derivative.

In difficult to control systems (i.e. hard to reach stress target values) the
controller force may produce undesirably high particle velocities.
In this case the *velocity\_limit* option may be used to bring velocities of the
controlled particles (or more precisely the controller force) in line with the
velocity range of the target system.
The option *velocity\_limit on* will try to limit particle velocities to the
target system's max/min velocities times (1 plus/minus 0.2), i.e. plus/minus 20%.
Similarly, the option *velocity\_limit relative value* will try to limit
particle velocities to the target system's max/min velocities times (1 plus/minus *value*\ ).
The option *velocity\_limit absolute value* will try to limit particle velocities
to the target system's max/min velocities plus/minus *value*\ .

The *actual\_cg* parameter allows to specify the coarse-grain ratio of the
controlled group of particles in single-partition multi-level coarse-grain
simulations.
In multi-partition simulations this coarse-grain ratio is automatically deduced
from the :doc:`coarsegraining <coarsegraining>` command active in the same
partition.

The *target\_cg* parameter allows to specify the coarse-grain ratio of the target
particles in single-partition multi-level coarse-grain simulations.
In multi-partition simulations this coarse-grain ratio is automatically deduced
from the :doc:`coarsegraining <coarsegraining>` command active in the coupled
partition.

The *max\_cg* parameter allows to specify the maximum coarse-grain ratio of
particles in single-partition multi-level coarse-grain simulations.
This coarse-grain ratio is need to properly scale the controlled region of
stress-based controllers.

If LIGGGHTS is invoked in multi-partition mode (cf. :ref:`Command-line options <start_7>`),
where each partition represents a separate coarse-graining level of the multi-level
coarse-grain model, the universe version of this command needs to be used.
In this case the coupled partition must be specified via the *receive\_from\_partition*
option.
Furthermore, *target\_val* needs to specify a fix of style *ave/euler/region/universe*
on the coupled partition and the interval for receiving data from that fix needs
to be set via the *couple\_every* option.

**Restart, fix\_modify, output, run start/stop, minimize info:**

This fix supports :doc:`fix\_modify <fix_modify>` with option *activate*\ /\ *deactivate* = cell-ID
to turn on/off the force controller for individual grid cells.

This fix also supports :doc:`fix\_modify <fix_modify>` with option *massflow\_correction\_on*/*massflow\_correction\_off* = cell-ID
to turn on/off corrections to a 'velocity' controller to achieve proper mass flow rates.

Related commands
""""""""""""""""

:doc:`fix ave/euler/region <fix_ave_euler_region>`, :doc:`region mesh/hex <region>`,
:doc:`partition <partition>`

Default
"""""""

*velocity\_limit* = *off*\ , *kp* = 1, *ki* = 0, *kd* = 0, *target\_cg* = 1,
*actual\_cg* = taken from *coarsegraining* command or 1, *max\_cg* = *actual\_cg*


