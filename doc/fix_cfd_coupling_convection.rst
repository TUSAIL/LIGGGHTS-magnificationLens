.. index:: fix couple/cfd/convection

fix couple/cfd/convection command
=================================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID couple/cfd/convection keyword values

* ID, group-ID are documented in :doc:`fix <fix>` command
* couple/cfd/convection = style name of this fix command
* zero or more keyword/value pairs may be appended
* keyword = *T0* or *transfer\_conduction* or *max\_change*
  
  .. parsed-literal::
  
       *T0* value = initial temperature for new particles
       *transfer_conduction* value = *yes* or *no* (default *no*\ )
       *max_change* value = maximum change of temperature per particle per time step



Examples
""""""""


.. parsed-literal::

   fix cfd1 all couple/cfd/convection T0 293

   fix cfd2 all couple/cfd/convection T0 293 transfer_conduction yes

   fix cfd3 all couple/cfd/convection T0 293 max_change 0.1

Description
"""""""""""

This fix pulls data for convective (and optionally conductive, if modeled in a Eulerian fashion) heat fluxes for each particle from CFDEMcoupling and passes them to a scalar transport equation. The maximum change of temperature for each particle may be limited to enhance numerical stability.

This fix needs a fix couple/cfd before it is defined.


