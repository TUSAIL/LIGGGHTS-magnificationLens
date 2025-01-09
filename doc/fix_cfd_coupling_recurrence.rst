.. index:: fix couple/cfd/recurrence

fix couple/cfd/recurrence command
=================================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID couple/cfd/recurrence keyword values

* ID, group-ID are documented in :doc:`fix <fix>` command
* couple/cfd/recurrence = style name of this fix command
* zero or more keyword/value pairs may be appended
* keyword = *transfer\_density* or *transfer\_type* or *transfer\_force* or *transfer\_fluctuations* or *transfer\_tracer* or *limit\_fluctuations* or *max\_vfluc* or *limit\_convection* or *max\_vconv* or *relative\_limit* or *remove\_vel\_across\_walls* or *region*
  
  .. parsed-literal::
  
       *transfer_\** values = *yes* or *no*

  
  .. parsed-literal::
  
       *limit_fluctuations* value = *yes* or *no*

  
  .. parsed-literal::
  
       *max_vfluc* value = maximum fluctuation velocity

  
  .. parsed-literal::
  
       *limit_convection* value = *yes* or *no*

  
  .. parsed-literal::
  
       *max_vconv* value = maximum convection velocity

  
  .. parsed-literal::
  
       *relative_limit* value = *yes* or *no*

  
  .. parsed-literal::
  
       *remove_vel_across_walls* values = name of fix gran/walls and absolute value of critical force

  
  .. parsed-literal::
  
       *region* value = name of region



Examples
""""""""


.. parsed-literal::

   fix cfd2 all couple/cfd/recurrence transfer_force yes transfer_fluctuations yes

   fix cfd3 all couple/cfd/recurrence transfer_force yes transfer_fluctuations yes limit_fluctuations yes max_vfluc 0.05 relative_limit no region closeToWall

Description
"""""""""""

This fix exchanges the recurrence CFD relevant data between LIGGGHTS and CFDEMcoupling.
Particle positions, velocities, radii and volumeweights are transferred from LIGGGHTS to CFDEMcoupling, the recurrence-prescribed velocities from CFDEMcoupling to LIGGGHTS.

If needed, particle types and densities can also be communicated from LIGGGHTS to CFDEMcoupling (disabled per default) and forces (e.g. drag), velocity fluctuations and tracer concentrations from CFDEMcoupling to LIGGGHTS (disabled per default). Fluctuations or convection velocity (or both) may be limited with an absolute or relative (in units of particle radius per time step) value, either everywhere or in a specific region.

If *remove\_vel\_across\_walls* is enabled by providing the name of the gran/wall fix, it is checked for each particle if it is subject to a wall contact force. If so, the velocity component in the direction towards the wall is reversed such that the particle does not try to cross the wall. The value of the critical force provided by the user determines at which point the fix gets active for each particle.

This fix needs a fix couple/cfd before it is defined.


