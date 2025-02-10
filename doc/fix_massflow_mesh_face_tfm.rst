.. index:: fix massflow/mesh/face/tfm

fix massflow/mesh/face/tfm command
==============================


Syntax
""""""


.. parsed-literal::

   fix ID group-ID massflow/mesh/face/tfm keywords values

* ID, group-ID are documented in :doc:`fix <fix>` command
* massflow/mesh/face/tfm = style name of this fix command
* keywords = *couple_every* or *n_MagnificationLensFaces* or *density* or *radius* or *shrink_factor* or *insertion_frequency* 
  
  .. parsed-literal::
  
       *couple_every* value = n
        n = integer number corresponding to the coupling time steps between CFD-DEM and TFM
       *n_MagnificationLensFaces* value = n
        n = total number of insertion faces (all insertion regions combined)
       *density* value = n
        n = density of the particle
       *radius* value = n
        n = radius of the particle
       *shrink_factor* value = n
         n = integer number this is used in case of inserting coarse-grained particles and particle size is divided by it 
       *insertion_frequency* value = n
        n = frequency of insertion



Examples
""""""""


.. parsed-literal::

        fix massflux all massflow/mesh/face/tfm couple_every 50 n_MagnificationLensFaces 1900 density 2600 radius 350e-6 shrink_factor 6 insertion_frequency 5

**LIGGGHTS vs. LAMMPS Info:**

This LIGGGHTS command is not available in LAMMPS.

Description
"""""""""""

Fix massflow/mesh/face/tfm receives the insertion face ids, face mass flux, particle velocity and granular temperature of the cells next to the insertion boundary from TFM. It determines the number of particles to be inserted from each face id based on the corresponding face mass flux. 




