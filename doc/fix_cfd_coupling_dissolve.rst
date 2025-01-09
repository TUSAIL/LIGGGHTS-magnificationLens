.. index:: fix couple/cfd/dissolve

fix couple/cfd/dissolve command
===============================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID couple/cfd/dissolve rmin rm

* ID, group-ID are documented in :doc:`fix <fix>` command
* couple/cfd/dissolve = style name of this fix command
  
  .. parsed-literal::
  
     rm = minimal particle radius



Examples
""""""""


.. parsed-literal::

   fix cfd4 all couple/cfd/dissolve rmin 0.001

Description
"""""""""""

This fix exchanges mass transfer relevant data between LIGGGHTS and CFDEMcoupling, 
and shrinks/grows particles according to the mass flux. *rmin* specifies the minimal
particle radius, particles shrunk smaller than this value will be deleted.

Restrictions
""""""""""""


This fix needs a fix couple/cfd before it is defined.


