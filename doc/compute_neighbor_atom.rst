.. index:: compute neighbor/atom

compute neighbor/atom command
=============================

Syntax
""""""


.. parsed-literal::

   compute ID group-ID neighbor/atom

* ID, group-ID are documented in :doc:`compute <compute>` command
* neighbor/atom = style name of this compute command

Examples
""""""""


.. parsed-literal::

   compute 1 all neighbor/atom

Description
"""""""""""

Define a computation that calculates the number of neighbors
for each atom in a group.

The value of the neighbor number will be 0.0 for atoms not in the
specified compute group.

**Output info:**

This compute calculates a per-atom vector, whose values can be
accessed by any command that uses per-atom values from a compute as
input.  See :ref:`Section\_howto 15 <howto_15>` for an
overview of LAMMPS output options.

The per-atom vector values will be a number >= 0.0, as explained
above.

Restrictions
""""""""""""


Related commands
""""""""""""""""

**Default:** none


