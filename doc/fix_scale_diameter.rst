.. index:: fix scale/diameter

fix scale/diameter command
==========================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID scale/diameter N keyword value ...

* ID, group-ID are documented in :doc:`fix <fix>` command
* scale/diameter = style name of this fix command
* N = scale diameter every this many timesteps
* region = obligatory keyword
* region\_value = ID of a spherical or cylindrical :doc:`region <region>` where the particles will be scaled
* scale = obligatory keyword
* scale\_value = scaling factor for change in diameter at region center
* scale\_width = outer fraction of radius to be used for actual scaling **0;1**


Examples
""""""""


.. parsed-literal::

   fix scale all scale/diameter 10 region scale_region scale 0.5 0.5

Description
"""""""""""

Change particle diameter over time as a simulation runs.

If *N* is specified as 0, the particle diameters are only changed
once, before a simulation run begins. This is all that is needed if the
diameter is not time-dependent. If *N* > 0, then changes
are made every *N* steps during the simulation.

The *scale* value describes the relative change in diameter when particles
reach the center of the specified region.

If the per-atom mass is defined for particles
(e.g. :doc:`atom\_style granular <atom_style>`), then the mass of each
particle is also changed when the diameter changes (density is assumed
to stay constant).

For example, these commands would shrink the diameter of all granular
particles in the "center" group from 100% to 10% in a linear fashion
while advancing towards the region center and increase the diameter again
while diverging from the center:


.. parsed-literal::

   region scale_region sphere 0.0 0.0 0.0 0.5 units box
   fix scale center scale/diameter 10 region scale_region scale 0.1


----------


**Restart, fix\_modify, output, run start/stop, minimize info:**

This fix writes the original radius of the particles to :doc:`binary restart files <restart>`.  None of the :doc:`fix\_modify <fix_modify>` options
are relevant to this fix.  The per-atom radius is stored
by an internal fix and can be accessed by various :ref:`output commands <howto_15>`.  No parameter of this fix can
be used with the *start/stop* keywords of the :doc:`run <run>` command.
This fix is not invoked during :doc:`energy minimization <minimize>`.

Restrictions
""""""""""""
 none

Default
"""""""

scale = 1.0.


