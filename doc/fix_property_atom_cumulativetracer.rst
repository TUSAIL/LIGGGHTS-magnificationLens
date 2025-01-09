.. index:: fix property/atom/cumulativetracer

fix property/atom/cumulativetracer command
==========================================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID property/atom/cumulativetracer keyword values

* ID, group-ID are documented in :doc:`fix <fix>` command
* property/atom/cumulativetracer = style name of this fix command
* several keyword/value pairs need to be appended
* keyword = *region\_mark* or *source\_strength* or *begin\_time* or *end\_time*
  
  .. parsed-literal::
  
       *region_mark* values = region ID

  
  .. parsed-literal::
  
       *source_strength* values = concentration injected per timestep

  
  .. parsed-literal::
  
       *begin_time* values = time at which injection starts

  
  .. parsed-literal::
  
       *end_time* values = time at which injection stops



Examples
""""""""


.. parsed-literal::

   fix tracers all property/atom/cumulativetracer region_mark mark source_strength 0.000001 begin_time 0.0 end_time 75.0

Description
"""""""""""

This fix injects a certain total amount of passive species into the particles currently in a specified region. If no particles are available at a timestep, the amount to be injected accumulates.


