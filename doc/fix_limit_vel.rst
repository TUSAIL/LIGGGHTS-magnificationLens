.. index:: fix limit/vel

fix limit/vel command
=====================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID limit/vel vmax

* ID, group-ID are documented in :doc:`fix <fix>` command
* limit/vel = style name of this fix command
* vmax = maximum velocity


Examples
""""""""


.. parsed-literal::

   fix lim all limit/vel 1.0

Description
"""""""""""

If the velocity of a particle is larger than vmax, it is scaled down to vmax while keeping the direction of the velocity vector. This can be used to stabilize simulations by preventing artificially high velocities.


----------



