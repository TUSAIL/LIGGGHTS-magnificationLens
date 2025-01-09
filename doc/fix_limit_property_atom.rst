.. index:: fix limit/property/atom

fix limit/property/atom command
===============================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID limit/property/atom targetfixname min min_value(s) max max_value(s)

* ID, group-ID are documented in :doc:`fix <fix>` command
* limit/property/atom = style name of this fix command
* targetfixname = name of the fix/property/atom to be limited
* min\_value(s) = list of lower limiting values
* max\_value(s) = list of upper limiting values


Examples
""""""""


.. parsed-literal::

   fix limT all limit/property/atom Temp min 250 max 350

**LIGGGHTS vs. LAMMPS Info:**

This LIGGGHTS command is not available in LAMMPS.

Description
"""""""""""

**Fix limit/property/atom** limits the values stored by a fix/property/atom from below and from above.

Note that the group of atoms the fix is applied to is ignored.

**Restart, fix\_modify, output, run start/stop, minimize info:** none

Restrictions
""""""""""""
 none

Related commands
""""""""""""""""

:doc:`fix\_property <fix_property>`

**Default:** none


