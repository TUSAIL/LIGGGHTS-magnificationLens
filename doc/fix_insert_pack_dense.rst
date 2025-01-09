.. index:: fix insert/pack/dense

fix insert/pack/dense command
=============================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID insert/pack seed seed_value distributiontemplate dist-ID region region-id keywords

* ID, group-ID are documented in :doc:`fix <fix>` command
* insert/pack/dense = style names of this fix command
* seed = obligatory keyword
* seed\_value = random # seed (positive integer)
* distributiontemplate = obligatory keyword
* dist-ID = ID of a :doc:`fix\_particledistribution\_discrete <fix_particledistribution_discrete>` to be used for particle insertion
* region = obligatory keyword
* region-id = id of the *region* to be used for insertion
  one or more keyword/value pairs can be appended
* keywords = *volumefraction\_region* or *insert\_every* or *target\_variable*
  
  .. parsed-literal::
  
       *volumefraction_region* = the intended volume fraction in the region
       *insert_every* = if specified, perform insertion every N time steps, otherwise only once
       *target_variable* = name of a previously defined variable together with a target and a threshold value; insertion only if they match



Examples
""""""""


.. parsed-literal::

   fix ins_pack_dense all insert/pack/dense seed 123 region reg distributiontemplate pdd2 volumefraction_region 0.53

   fix ins_pack_dense all insert/pack/dense seed 123 region reg distributiontemplate pdd2 volumefraction_region 0.53 insert_every 10000 target_variable fillLevel 0.0 0.1

Description
"""""""""""

This fix creates a dense packing of particles in a region defined by
the *region* keyword. The algorithm by Lozano et al. (Comput Math Appl
71 (2016), 1586-1601) is implemented.

This command must use the distributiontemplate keyword to refer to a
:doc:`fix\_particledistribution\_discrete <fix_particledistribution_discrete>`
(defined by dist-fix-ID) that defines the properties of the inserted
particles.

Insertion is always performed in the next timestep immediately after
defining the fix. It is recommended to unfix the fix after insertion
has happened, because it creates several data structures that might
take up a lot of memory.

In the published form, the algorithm creates a packing as dense as
possible. This implementation allows to create a lower volume fraction
by internally scaling the radius of the particles by the third root of
the ratio volumefraction\_region/volumefraction\_max where
volumefraction\_max is defined as 0.57. Depending on the region and the
particle distribution, volumefraction\_max can not always be reached,
however in the limit of tiny, monodisperse particles in a giant region
without complex geometrical features, 0.57 is a good estimate. If a
value > 0.57 is given, the fix will ignore it and output a warning.

Inserted particles are assigned the atom type specified by the
particledistribution defined via the
:doc:`fix\_particledistribution\_discrete <fix_particledistribution_discrete>`
and are assigned to 4 groups: the default group "all" and the group
specified in the fix insert command, as well as the groups specified
in the
:doc:`fix\_particledistribution\_discrete <fix_particledistribution_discrete>`
and :doc:`fix\_particletemplate\_sphere <fix_particletemplate_sphere>`
command (all of which can also be "all").

**Restart, fix\_modify, output, run start/stop, minimize info:**

No information to restart files is written by this fix.

Restrictions
""""""""""""


The insertion region can span several processors, but must be a single
continuous volume. Regions consisting of several disconnected volumes
will be filled incorrectly or not at all.

When running in parallel, the estimated number of particles is wrong
when using a region of type mesh/tet.

Dynamic regions are not supported as insertion region.

Related commands
""""""""""""""""

:doc:`fix\_insert\_stream <fix_insert_stream>`, :doc:`fix\_insert\_rate\_region <fix_insert_rate_region>`,
:doc:`fix\_deposit <fix_deposit>`, :doc:`region <region>`, 
:doc:`fix\_pour <fix_pour>`

Default
"""""""

The default values are volumefraction\_region = 0.57 (=volumefraction\_max)


