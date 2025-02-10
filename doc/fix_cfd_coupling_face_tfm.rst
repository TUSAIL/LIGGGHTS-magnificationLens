.. index:: fix couple/cfd/face/tfm

fix couple/cfd/face/tfm command
======================================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID couple/cfd/face/tfm keyword values

* ID, group-ID are documented in :doc:`fix <fix>` command
* couple/cfd/face/tfm = style name of this fix command
* keyword = *n_patches* or *n_faceids*
  
  .. parsed-literal::
  
       *n_patches* value = number of magnification lens boundary patches
       *n_faceids* value = number of faces of each patch

Examples
""""""""

.. parsed-literal::

   fix cfd3 all couple/cfd/face/tfm n_patches 2 n_faceids 1024 1024

Description
"""""""""""

This fix exchanges patch face ids and face fluxes from CFDEMcoupling. These properties become available as fix property/global.

Restrictions
""""""""""""


This fix needs a fix couple/cfd before it is defined.

This fix requires transferDataModels *transferFaceData* be active in couplingProperties.


