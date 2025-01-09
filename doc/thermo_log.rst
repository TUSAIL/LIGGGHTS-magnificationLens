.. index:: thermo\_log

thermo\_log command
===================

Syntax
""""""


.. parsed-literal::

   thermo_log file keyword

* file = name of new thermo logfile
* keyword = *append* if output should be appended to thermo logfile (optional)

Examples
""""""""


.. parsed-literal::

   thermo_log log.equil
   thermo_log log.equil append

Description
"""""""""""

This command closes any current LAMMPS thermo log file, opens a new file with
the specified name, and begins logging thermo information to it.  If the
specified file name is *none*\ , then no new thermo log file is opened.  If the
optional keyword *append* is specified, then output will be appended
to an existing thermo log file, instead of overwriting it.

If multiple processor partitions are being used, the file name should
be a variable, so that different processors do not attempt to write to
the same thermo log file.

The default setting for the thermo log file is *none*\ .  The
name of the thermo log file can also be set by the command-line
switch -thermo.  See :ref:`Section 2.7 <start_7>` for
details.

Restrictions
""""""""""""
 none

**Related commands:** none

Default
"""""""

By default no separate thermo log file is created.


