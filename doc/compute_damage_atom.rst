.. index:: compute damage/atom

compute damage/atom command
===========================

Syntax
""""""


.. parsed-literal::

   compute ID group-ID damage/atom

* ID, group-ID are documented in :doc:`compute <compute>` command
* damage/atom = style name of this compute command

Examples
""""""""


.. parsed-literal::

   compute 1 all damage/atom

Description
"""""""""""

Define a computation that calculates the per-atom damage for each atom
in a group.  Please see the `PDLAMMPS user guide <http://www.sandia.gov/~mlparks/papers/PDLAMMPS.pdf>`_ for a formal
definition of "damage" and more details about Peridynamics as it is
implemented in LAMMPS.

The value of the damage will be 0.0 for atoms not in the specified
compute group.

**Output info:**

This compute calculates a per-atom vector, which can be accessed by
any command that uses per-atom values from a compute as input.  See
:ref:`Section\_howto 15 <howto_15>` for an overview of
LAMMPS output options.

The per-atom vector values will be a number >= 0.0, as explained
above.

Restrictions
""""""""""""


This compute is part of the PERI package.  It is only enabled if
LAMMPS was built with that package.  See the :ref:`Making LAMMPS <start_3>` section for more info.

Related commands
""""""""""""""""

:doc:`dump custom <dump>`

**Default:** none


