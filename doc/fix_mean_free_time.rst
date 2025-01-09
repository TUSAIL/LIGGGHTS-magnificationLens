.. index:: fix meanfreetime

fix meanfreetime command
========================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID meanfreetime keyword values

* ID, group-ID are documented in :doc:`fix <fix>` command
* meanfreetime = style name of this fix command
* zero or more keyword/value pairs may be appended to args
* keyword = *check\_every* or *t\_start*
  
  .. parsed-literal::
  
       *check_every* value = evaluate collisional state every Nth step
       *t_start* value = start sampling at this time



Examples
""""""""


.. parsed-literal::

   fix fmft all meanfreetime t_start 1.0

Description
"""""""""""

This fix sums up the time between collisions for each particle and counts the number of
these intervals. A starting time *t\_start* and a rate *check\_every* for
evaluation can be specified.

**Restart, fix\_modify, output info:**

No information about this fix is written to :doc:`binary restart files <restart>`.  None of the :doc:`fix\_modify <fix_modify>` options
are relevant to this fix.

This fix computes a global scalar, the time between contacts averaged
over all particles, which can be accessed by various
:ref:`output commands <howto_15>`. E.g. an equal-style variable
can be used to store and output the result.

Restrictions
""""""""""""
 none

**Related commands:** none

**Default:** *check\_every* = 1, *t\_start* = 0.0


