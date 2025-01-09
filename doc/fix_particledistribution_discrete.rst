.. index:: fix particledistribution/discrete

fix particledistribution/discrete command
=========================================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID particledistribution/discrete seed ntemp t_id t_m ...

* ID, group-ID are documented in :doc:`fix <fix>` command
* particledistribution/discrete = style name of this fix command
* seed = random number generator seed (integer value)
* ntemp = number of particle templates to be used in this command
* zero or more *t\_id*/*t\_m* pairs are appended, number of pairs must match ntemp
  
  .. parsed-literal::
  
     *t_id* = id of a fix of type particletemplate/sphere
     *t_m* = mass % for this template in the distribution



Examples
""""""""


.. parsed-literal::

   fix pdd1 all particledistribution/discrete 6778  1 pts1 1.0
   fix pdd1 all particledistribution/discrete 1239  2 pts1 0.3 pts2 0.7

**LIGGGHTS vs. LAMMPS Info:**

This command is not available in LAMMPS.

Description
"""""""""""

Define a discrete particle distribution to be inserted by the
:doc:`fix insert/pack <fix_insert_pack>`, :doc:`fix insert/pack/dense <fix_insert_pack_dense>`,
:doc:`fix insert/rate/region <fix_insert_rate_region>`,
:doc:`fix insert/stream <fix_insert_stream>` or
:doc:`fix insert/stream/moving <fix_insert_stream_moving>` command.
It takes several templates of type :doc:`fix\_particletemplate\_sphere <fix_particletemplate_sphere>`
as inputs, which define the properties of the single particles that are part of
the distribution.

At insertion, particles are chosen according to the mass-% distribution as
defined by each pair (t\_id, t\_m). Note that the sum of all weights t\_m must be
equal to 1.0, if this is not the case the user is warned at the distribution is
normalized. Note that large particles are inserted first, so that a higher
volume fraction can be achieved. If not all desired insertions could be
performed, it is likely that the distribution is not accurately reproduced.

.. warning::

   As opposed to the number-based distributions used by :doc:`fix pour/legacy <fix_pour>`, this fix uses the more common distribution based on mass-% as input (as does :doc:`fix particletemplate/sphere <fix_particletemplate_sphere>`).

**Restart, fix\_modify, output, run start/stop, minimize info:**

Information about the random state in this fix is written to :doc:`binary restart files <restart>`
so you can restart a simulation with the same particles being chosen for
insertion. None of the :doc:`fix\_modify <fix_modify>` options are relevant to this
fix. No global scalar or vector or per-atom quantities are stored by this fix
for access by various :ref:`output commands <howto_15>`. No parameter of
this fix can be used with the *start*\ /\ *stop* keywords of the :doc:`run <run>`
command. This fix is not invoked during :doc:`energy minimization <minimize>`.

Restrictions
""""""""""""
 none

Related commands
""""""""""""""""

:doc:`fix insert/pack <fix_insert_pack>`, :doc:`fix insert/pack/dense <fix_insert_pack_dense>`,
:doc:`fix insert/rate/region <fix_insert_rate_region>`, :doc:`fix insert/stream <fix_insert_stream>`,
`fix insert/stream/moving <fix_insert_stream_moving.htm>`_

**Default:** none


