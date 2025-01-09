.. index:: fix couple/cfd/chemistry

fix couple/cfd/chemistry command
================================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID couple/cfd/chemistry n_species Ns species_names s_names n_diff Nd diffusant_names d_names keyword value

* ID, group-ID are documented in :doc:`fix <fix>` command
* couple/cfd/chemistry = style name of this fix command
* n\_species = obligatory keyword
* Ns = number of gas species flowing in
* species\_names = obligatory keyword
* s\_names = names of the relative gases
* n\_diff = obligatory keyword
* Nd = number of diffusant names
* diffusant\_names = obligatory keyword
* d\_names = diffusant names
* zero or more keyword/value pairs may be appended
* keyword = *transfer\_reactant*
  
  .. parsed-literal::
  
       *transfer_reactant* value = *yes* or *no*



Examples
""""""""


.. parsed-literal::

   fix cfd3 all couple/cfd/chemistry n_species 5 species_names H2 H2O CO CO2 N2 n_diff 2 diffusant_names CO H2

Description
"""""""""""

This fix exchanges chemical reaction relevant data between LIGGGHTS and CFDEMcoupling.
Particle positions, velocities, radii and volumeweights are transferred from
LIGGGHTS to CFDEMcoupling, the reacting gas species and product gas species from
CFDEMcoupling to LIGGGHTS.

Restrictions
""""""""""""


This fix needs a fix couple/cfd before it is defined.

Default
"""""""

*transfer\_reactant* = *no*


