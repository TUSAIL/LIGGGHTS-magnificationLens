.. index:: fix couple/cfd/deform

fix couple/cfd/deform command
=============================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID couple/cfd/deform keyword values

* ID, group-ID are documented in :doc:`fix <fix>` command
* couple/cfd/deform = style name of this fix command
* zero or more keyword/value pairs may be appended
* keyword = *compress* or *verbose* or *rmin* or *monitor\_heat* or *use\_latent\_heat* or *latent\_heat* or *delete\_fully\_deformed\_particles*
  
  .. parsed-literal::
  
       *compress* value = *yes* or *no*
       *verbose* value = *yes* or *no*
       *rmin* value = radius below which particles cannot deform
       *monitor_heat* value = *yes* or *no*
       *use_latent_heat* value = *yes* or *no*
       *latent_heat* value = latent heat per kg that is required to remove a solid grain due to melting
       *delete_fully_deformed_particles* value = *yes* or *no*



Examples
""""""""


.. parsed-literal::

   fix cfd1 all couple/cfd/deform

   fix cfd2 all couple/cfd/deform verbose yes

   fix cfd3 all couple/cfd/deform rmin 0.01 monitor_heat yes use_latent_heat yes latent_heat 100000

Description
"""""""""""

This fix pulls data between 0 and 1 for each particle from CFDEMcoupling describing the extent a grains deforms subject to some local field. 0 means no deformation and 1 means maximum deformation. If desired, a value of > 1 leads to particle removal. The accumulated removed mass (and optionally heat) can be accessed analogously as for fix remove.

If deformation is due to softening with increasing temperature, and particles can even melt and be removed from the simulation, it is possible to specify the latent heat that is required for this process. This option needs to be activated via *use\_latent\_heat* and the latent heat per mass specified via *latent\_heat*. The value is defined with a positive sign. The option *delete\_fully\_deformed\_particles* (default yes) determines if fully deformed particles are deleted from the simulation or not. In the latter case, they are assigned to a group called "fullyDeformed" which can be accessed by other fixes etc.

This fix needs a fix couple/cfd before it is defined.


