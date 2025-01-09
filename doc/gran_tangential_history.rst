gran tangential history
=======================

Syntax
""""""


.. parsed-literal::

   tangential history

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
the Coulomb criterion Ft = cof\*Fn, where Ft and Fn are the tangential spring and normal 
force components in the formulas above.


