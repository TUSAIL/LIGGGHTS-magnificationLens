.. index:: modify\_timing

modify\_timing command
======================

Syntax
""""""


.. parsed-literal::

   modify_timing style

* style = *off* or *on* or *verbose*

Examples
""""""""


.. parsed-literal::

   modify_timing on
   modify_timing verbose

Description
"""""""""""

This command determines whether fix calls are timed.  If the timing is set to *on*
LIGGGHTS will calculate and output the total time and maximum single-process time
spent in fixes. The *verbose* option in addition gives detailed per-process timing.

Restrictions
""""""""""""
 none

**Related commands:** none

Default
"""""""


.. parsed-literal::

   modify_timing off


