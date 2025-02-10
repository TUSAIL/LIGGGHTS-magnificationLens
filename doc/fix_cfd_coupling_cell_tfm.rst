.. index:: fix couple/cfd/cell/tfm

fix couple/cfd/cell/tfm command
======================================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID couple/cfd/cell/tfm keyword values

* ID, group-ID are documented in :doc:`fix <fix>` command
* couple/cfd/cell/tfm = style name of this fix command
* keyword = *n_patches* or *n_cells*
  
  .. parsed-literal::
  
       *n_patches* value = number of magnification lens boundary patches
       *n_cells* value = number of cells next to each boundary patch

Examples
""""""""

.. parsed-literal::

   fix cfd4 all couple/cfd/cell/tfm n_patches 2 n_cells 1024 1024

Description
"""""""""""

This fix exchanges cell-based particle velocity, granular temperature, solids volume fraction, total paticle volumes in cell, and diagonal components of the total particle stress tensor obtained from TFM through CFDEMcoupling. These properties become available as fix property/global.

Restrictions
""""""""""""


This fix needs a fix couple/cfd before it is defined.

This fix requires transferDataModels *transferCellData* be active in couplingProperties.


