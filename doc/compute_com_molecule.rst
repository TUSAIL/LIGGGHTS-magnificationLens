.. index:: compute com/molecule

compute com/molecule command
============================

Syntax
""""""


.. parsed-literal::

   compute ID group-ID com/molecule

* ID, group-ID are documented in :doc:`compute <compute>` command
* com/molecule = style name of this compute command
* zero or more keyword/value pairs may be appended
* keyword = *unwrap*
  
  .. parsed-literal::
  
       *unwrap* value = yes or no
         yes = coordinates of the center-of-mass in unwrapped form
         no = coordinates of the center-of-mass remapped into the periodic domain



Examples
""""""""


.. parsed-literal::

   compute 1 fluid com/molecule

Description
"""""""""""

Define a computation that calculates the center-of-mass of individual
molecules.  The calculation includes all effects due to atoms passing
through periodic boundaries.

The x,y,z coordinates of the center-of-mass for a particular molecule
are only computed if one or more of its atoms are in the specified
group.  Normally all atoms in the molecule should be in the group,
however this is not required.  LAMMPS will warn you if this is not the
case.  Only atoms in the group contribute to the center-of-mass
calculation for the molecule.

The ordering of per-molecule quantities produced by this compute is
consistent with the ordering produced by other compute commands that
generate per-molecule datums.  Conceptually, the molecule IDs will be
in ascending order for any molecule with one or more of its atoms in
the specified group.

.. warning::

   The coordinates of an atom contribute to the
   molecule's center-of-mass in "unwrapped" form, by using the image
   flags associated with each atom.  See the :doc:`dump custom <dump>`
   command for a discussion of "unwrapped" coordinates.  See the Atoms
   section of the :doc:`read\_data <read_data>` command for a discussion of
   image flags and how they are set for each atom.  You can reset the
   image flags (e.g. to 0) before invoking this compute by using the :doc:`set image <set>` command.

.. warning::

   If an atom is part of a rigid body (see the :doc:`fix rigid <fix_rigid>` command), its periodic image flags are altered,
   and its contribution to the center-of-mass may not reflect its true
   contribution.  See the :doc:`fix rigid <fix_rigid>` command for details.
   Thus, to compute the center-of-mass of rigid bodies as they cross
   periodic boundaries, you will need to post-process a :doc:`dump file <dump>` containing coordinates of the atoms in the bodies.

**Output info:**

This compute calculates a global array where the number of rows =
Nmolecules and the number of columns = 6 for the x,y,z center-of-mass
coordinates and x,y,z components of the center-of-mass velocity of each
molecule.
These values can be accessed by any command that uses global array values
from a compute as input.
See :ref:`Section\_howto 15 <howto_15>` for an overview of
LAMMPS output options.

The array values are "intensive".  The array values will be in
distance :doc:`units <units>`.

Restrictions
""""""""""""
 none

Related commands
""""""""""""""""

:doc:`compute com <compute_com>`

Default
"""""""

unwrap = yes


