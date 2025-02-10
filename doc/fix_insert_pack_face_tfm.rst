.. index:: fix insert/pack/face/tfm

fix insert/pack/face/tfm command
============================


Syntax
""""""


.. parsed-literal::

   fix ID group-ID insert/pack/face/tfm seed seed_value general_keywords general_values pack_face_keywords pack_face_values

* ID, group-ID are documented in :doc:`fix <fix>` command
* insert/pack/face/tfm = style names of this fix command
* seed = obligatory keyword
* seed\_value = random # seed (positive integer)
* one or more general keyword/value pairs can be appended
* general\_keywords = *verbose* or *maxattampt* or *insert\_every* or *all\_in*
  
  .. parsed-literal::
  
       *verbose* = yes or no
       *maxattempt* value = ma
         ma = max # of insertion attempts per atom (positive integer)
       *insert_every* value = ie
         ie = every how many time-steps particles are inserted - insertion happens periodically (positive integer)
       *start* value = ts
         ts = time-step at which insertion should start (positive integer larger than current time-step)
       *all_in* value = yes or no
       *overlapcheck* value = yes or no

* following the general keyword/value section, one or more pack\_face keyword/value pairs can be appended for the fix insert/pack/face command
* pack\_face\_keywords = *region* or *massflow\_face* or *type\_offset* or *ntry\_mc* or *start_index* or *end_index* or *n_MagnificationLensFaces*
  
  .. parsed-literal::
  
       *region* value = region-ID
         region-ID = ID of the region mesh/hex where the particles will be generated
       *massflow_face* values = fix-ID
         fix-ID =  ID of a :doc:`fix massflow/mesh/face/tfm <fix_massflow_mesh_face_tfm>`
       *ntry_mc* values = n
         n = number of Monte-Carlo steps for calculating the region's volume (positive integer)
       *start_index* values = n
         n = the index of the first faceID of the insertion region (for the first fix insert/pack/face/tfm it should be 0 and for the second fix insert/pack/face/tfm it should be total number of insertion region faces of the first fix)
       *end_index* values = n
         n = the index of the last faceID of the insertion region (for the first fix insert/pack/face/tfm it should be total number of insertion faces - 1 and for the second fix insert/pack/face/tfm it should be sum of total number of first and second insertion region faces - 1)
       *n_MagnificationLensFaces* values = n
       n = sum of total number of insertion region faces
         
         


Examples
""""""""


.. parsed-literal::

   fix insMagLens1 all insert/pack/face/tfm seed 7331 random_distribute exact maxattempt 100 insert_every 250 start 1002&
    overlapcheck yes all_in yes region hexRegion1 ntry_mc 1500 massflow_face massflux start_index 0 end_index 1023 n_MagnificationLensFaces 1024
   fix insMagLens2 all insert/pack/face/tfm seed 7331 random_distribute exact maxattempt 100 insert_every 250 start 1002&
    overlapcheck yes all_in yes region hexRegion2 ntry_mc 1500 massflow_face massflux start_index 1024 end_index 2047 n_MagnificationLensFaces 1024

Description
"""""""""""

Insert particles recorded by :doc:`fix massflow/mesh/face/tfm <fix_massflow_mesh_face_tfm>`
into a granular run every few timesteps within the specified region,
as defined via the *region* keyword. The region of type mesh/hex must
hold the element property 'face\_id' corresponding to the 'face\_id' property
of the mesh used in fix massflow/mesh/face/tfm. This command uses a distributiontemplate
generated automatically from the data collected by fix massflow/mesh/face/tfm to define
the properties of the inserted particles.

The *verbose* keyword controls whether statistics about particle
insertion is output to the screen each time particles are inserted.

At each insertion step, fix insert/pack/face/tfm tries to insert all particles
recorded by fix massflow/mesh/face/tfm since the last insertion.

The frequency of the particle insertion can be controlled by the 
keyword *insert\_every*, which defines the number of time-steps between 
two insertions.

The *start* keyword can be used to set the time-step at which the insertion 
should start.

Inserted particles are assigned the atom types recorded by fix massflow/mesh/face/tfm.

Overlap is checked for at insertion, both within the inserted particle package
and with other existig particles. The number of insertion attempts per particle
can be specified via the *maxattempt* keyword. Each timestep particles are inserted,
the command will make up to a total of M tries to insert the new particles without
overlaps, where M = # of inserted particles \* *maxattempt*\ .
If unsuccessful at completing all insertions, a warning will be printed.

The *all\_in* flag determines if the particle is completely contained 
in the insertion region (*all\_in yes*) or only the particle center 
(*all\_in no*).

The initial velocity of the inserted particles is determined by the particle velocity and granular temperature of the cells next to the insertion boundary gathered by fix massflow/mesh/face/tfm. The particle velocity and granular temperature are adopted to insert the particles based on the Maxwellian distribution.

**Description for fix insert/pack/face/tfm:**

This command must use the *region* keyword to define an insertion
volume. The specified region must have been previously defined with a
:doc:`region mesh/hex <region>` command. Dynamic regions are not supported
as insertion region. Each timestep particles are inserted, they are placed
randomly inside the hexahedral cell of the insertion volume that corresponds
to the face of the surface mesh used by fix massflow/mesh/face/tfm.

The *massflow\_face\_tfm* must be used to specify a
:doc:`fix massflow/mesh/face/tfm <fix_massflow_mesh_face_tfm>` command that
determines the number and parameters of the particles to insert.

To determine the volume of each hexahedron of the insertion region,
a Monte Carlo approach is used. The *ntry\_mc* keyword is used to control
the number of MC tries that are used for the volume calculation.

Since the face mass flux from TFM is sent to LIGGGHTS as one array containing the data
for all the insertion regions faces, it is necessary to specify "start\_index" and 
"end\_index" for all insertion regions. This helps the code to correctly select the
face mass flux values for each insertion region.

*n_MagnificationLensFaces* is only used to help the user to correcty specify the 
"start\_index" and "end\_index".


Restrictions
""""""""""""


Dynamic regions are not supported as insertion region.

Related commands
""""""""""""""""

:doc:`fix insert/pack <fix_insert_pack>`, :doc:`fix insert/rate/region <fix_insert_rate_region>`,
:doc:`fix insert/stream <fix_insert_stream>`, :doc:`fix deposit <fix_deposit>`,
`fix pour <fix_pour.html">`_, region"_region.html, :doc:`partition <partition>`

Default
"""""""

The defaults are *maxattempt* = 50, *all\_in* = *no*\ , *start* = next time-step, *type\_offset* = 0, *ntry\_mc* = 100000


