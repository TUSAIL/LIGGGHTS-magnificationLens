gran tangential incremental\_history
====================================

Syntax
""""""


.. parsed-literal::

   tangential incremental_history

**LIGGGHTS vs. LAMMPS Info:**

This part of :doc:`pair gran <pair_gran>` and 
:doc:`fix wall/gran <fix_wall_gran>`
is not available in LAMMPS.

Description
"""""""""""

This granular model is based on the general description of granular
force interaction as described in :doc:`pair gran <pair_gran>`.

The spring part of the tangential force (k\_t) is a "history" effect 
that accounts for the tangential displacement ("tangential overlap") 
between the particles for the duration of the time they are in contact.

If this model is chosen, then this "tangential overlap" spring force is
actually calculated / taken into account.
The coefficient of friction cof is the upper limit of the tangential force through 
the Coulomb criterion Ft = cof\*Fn, where Ft and Fn are the tangential spring and
normal force components in the contact force model.

Note that opposed to the :doc:`history <gran_tangential_history>` model which
calculates the tangential force in an integral way, the *incremental\_history*
model computes the tangential force in an incremental way.

More precisely, in the *history* model the tangential overlap gets updated each
time step by projecting the tangential overlap accumulated so far into the current 
tangential plane and adding the current increment of the tangential overlap.
This overlap is used in combination with the current tangential spring stiffness
to calculate the current tangential force.

The *incremental\_history* model on the other hand updates the tangential force
each time step by projecting the tangential force accumulated so far into the
current tangential plane. The current increment of the tangential overlap is
used in combination with the current tangential spring stiffness to calculate
the current increment of the tangential force.

For a detailed discussion see :ref:`Thornton et al. 2011 <Thornton2011>` and
:ref:`Thornton et al. 2013 <Thornton2013>`


----------


.. _Thornton2011:



.. _Thornton2013:

**(Thornton et al., 2011)** "An investigation of the comparative behaviour of alternative contact force models during elastic collisions", C. Thornton, S.J. Cummins, P.W. Cleary, Powder Technology, 210 (3), pp. 189-197 (2011).


**(Thornton et al., 2013)** "An investigation of the comparative behaviour of alternative contact force models during inelastic collisions", C. Thornton, S.J. Cummins, P.W. Cleary, Powder Technology, 233, pp. 30-46 (2013).


