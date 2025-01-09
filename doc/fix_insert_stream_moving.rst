.. index:: fix insert/stream/moving

fix insert/stream/moving command
================================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID insert/stream/moving seed seed_value distributiontemplate dist-ID general_keywords general_values stream_keywords stream_values ...

* ID, group-ID are documented in :doc:`fix <fix>` command
* insert/stream/moving = style name of this fix command
* all other keywords/values are documented in :doc:`fix insert/stream <fix_insert_stream>` command


Examples
""""""""


.. parsed-literal::

   fix ins all insert/stream/moving seed 1001 distributiontemplate pdd1 nparticles 5000 vel constant 0. -0.5 -2. particlerate 1000 overlapcheck yes insertion_face ins_mesh extrude_length 0.6

Description
"""""""""""

Insert particles into a granular run, identically to 
the :doc:`fix insert/stream <fix_insert_stream>` command.
However, when using fix insert/stream/moving the insertion
face can be moved spatially via a :doc:`fix move/mesh <fix_move_mesh>`
command

**Restart, fix\_modify, output, run start/stop, minimize info:**

See :doc:`fix insert/stream <fix_insert_stream>` command.

Restrictions
""""""""""""


See :doc:`fix insert/stream <fix_insert_stream>` command.

Related commands
""""""""""""""""

:doc:`fix insert/pack <fix_insert_pack>`, :doc:`fix insert/rate/region <fix_insert_rate_region>`,
:doc:`fix deposit <fix_deposit>`, :doc:`fix pour/legacy <fix_pour>`

Default
"""""""

See :doc:`fix insert/stream <fix_insert_stream>` command.


