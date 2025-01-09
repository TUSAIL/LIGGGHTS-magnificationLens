.. index:: fix property/atom/timetracer

fix property/atom/timetracer command
====================================

Syntax
""""""


.. parsed-literal::

   fix id group property/atom/timetracer keyword value ...

* ID, group-ID are documented in :doc:`fix <fix>` command
* property/atom/timetracer = style name of this fix command
* zero or more keyword/value pairs may be appended to args
* keyword = *add\_region* or *check\_region\_every*
  
  .. parsed-literal::
  
       *add_region* value = *region-ID*
         region-ID = ID of region to be added to list of regions where residence time is evaluated
       *check_region_every* value = n
         n = check every that many time-step if atom are in region



Examples
""""""""


.. parsed-literal::

   fix tracer all property/atom/timetracer add_region tracereg

Description
"""""""""""

Fix property/atom/timetracer computes the residence time of particles 
in the simulation domain and (optionally) a list of regions.

Since the look-up if a particle is in a specific region can be
computationally costly, keyword *check\_region\_every* can be used to 
control how often the region is checked. Every *check\_region\_every*
time-steps, the lookup is performed and the residence time contribution
for each lookup is dt\**check\_region\_every*, where dt is the time-step 
size. However, be careful not to choose this value too large, in this case
you could skip particles passing through a region.

**Restart, fix\_modify, output, run start/stop, minimize info:**

Information about this fix is written to :doc:`binary restart files <restart>` .

In case no regions are specified, this fix computes a per-atom vector 
(the residence time of particles in the simulation domain) which can be 
accessed by various :ref:`output commands <howto_8>`.
In case one or more optional regions are specified, this fix computes
a per-atom array, where the first value for each particle is the residence 
time in the simulation domain and the following values are the residence
time in the specified regions (in the order in which the regions are
specified).

This fix computes a N-vector of residence times, where N=1+number of
regions specified, which can be accessed by various :ref:`output commands <howto_8>`. The vector components are the
average residence time in the fix group for the whole simulation domain
(first value) and for each region (following values). The order
is following the order in which the regions are specified.

Restrictions
""""""""""""


Currently, this feature does not support multi-sphere particles.

Related commands
""""""""""""""""

:doc:`compute nparticles/tracer/region <compute_nparticles_tracer_region>`

Default
"""""""

check\_region\_every = 10


