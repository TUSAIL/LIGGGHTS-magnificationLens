gran tangential no\_history
===========================

Syntax
""""""


.. parsed-literal::

   tangential no_history

**LIGGGHTS vs. LAMMPS Info:**

This part of :doc:`pair gran <pair_gran>` and 
:doc:`fix wall/gran <fix_wall_gran>`
is not available in LAMMPS.

Description
"""""""""""

This granular model is based on the general description of granular
force interaction as described in :doc:`pair gran <pair_gran>`.

If this model is chose, then this "tangential overlap" spring force is
NOT calculated / taken into account, i.e. k\_t = 0.

The coefficient of friction cof is the upper limit of the tangential force through 
the Coulomb criterion Ft = cof\*Fn, where Ft and Fn are the tangential spring and normal 
force components in the formulas above.


