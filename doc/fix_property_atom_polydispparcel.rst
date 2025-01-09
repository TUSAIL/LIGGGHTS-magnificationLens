.. index:: fix property/atom/polydispparcel

fix property/atom/polydispparcel command
========================================

Syntax
""""""


.. parsed-literal::

   fix id group property/atom/polydispparcel keyword value(s)

* ID, group-ID are documented in :doc:`fix <fix>` command
* property/atom/polydispparcel = style name of this fix command
* one keyword/value(s) pair needs to be appended to args
* keyword = *effvolfactor*
  
  .. parsed-literal::
  
       *effvolfactor* value(s) = evf1 evf2 ...
         evfi = effective volume enhancement due to polydispersity of atom type i (the same number of values as atom types present has to be specified)



Examples
""""""""


.. parsed-literal::

   fix fp all property/atom/polydispparcel effvolfactor 1.5 1.0

Description
"""""""""""

Fix property/atom/polydispparcel assigns an effective volume factor to each particle according to its atom type. Using the set command, values can be changed individually, e.g. for groups. Upon insertion of particles with a given density, their mass is scaled with the effective volume factor. The same mechanism is triggered by setting an effective volume factor with the set command.

**Restart, fix\_modify, output, run start/stop, minimize info:**

Information about this fix is written to :doc:`binary restart files <restart>` .


