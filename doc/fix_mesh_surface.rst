.. index:: fix mesh/surface

fix mesh/surface command
========================

fix mesh/surface/planar command
===============================

fix mesh/surface/omp command
============================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID mesh/surface file filename premesh_keywords premesh_values mesh_keywords mesh_values surface_keywords surface_values
   fix ID group-ID mesh/surface/planar file filename premesh_keywords premesh_values mesh_keywords mesh_values surface_keywords surface_values

* ID is documented in :doc:`fix <fix>` command.
* mesh/surface or mesh/surface/planar = style name of this fix command
* file = obligatory keyword
* filename = name of STL or VTK file containing the triangle mesh data
* zero or more premesh\_keywords/premesh\_value pairs may be appended
* premesh\_keyword = *type* or *precision* or *heal* or *element\_exclusion\_list* or *cell\_data* or *verbose*
  
  .. parsed-literal::
  
       *type* value = atom type (material type) of the wall imported from the STL file
       *precision* value = length mesh nodes this far away at maximum will be recognized as identical (length units)
       *heal* value = auto_remove_duplicates or no
       *element_exclusion_list* values = mode element_exlusion_file
         mode = read or write
         element_exlusion_file = name of file containing the elements to be excluded
       *cell_data* value = yes or no to load per element data from VTK files
       *verbose* value = yes or no

* zero or more mesh\_keywords/mesh\_value pairs may be appended
* mesh\_keyword = *scale* or *move* or *rotate* or *temperature*
  
  .. parsed-literal::
  
       *scale* value = factor
         factor = factor to scale the mesh in x-, y-, and z-direction (double value)
       *move* values = mx my mz
         mx my mz = move the mesh by this extent in x-, y-, and z-direction (length units)
       *rotate* values = axis ax ay az angle ang
         axis = obligatory keyword 
         ax, ay, az = axis vector for rotation (length units) 
         angle = obligatory keyword 
         ang = angle to rotate the geometry around the specified axis (in degrees) 
       *temperature* value = T0
         T0 = Temperature of the wall (temperature units)

* zero or more surface\_keywords/surface\_value pairs may be appended
* surface\_keyword = *surface\_vel* or *surface\_ang\_vel* or *curvature* or *curvature\_tolerant*
  
  .. parsed-literal::
  
       *surface_vel* values = vx vy vz
         vx vy vz = conveyor belt surface velocity  (velocity units)
       *surface_ang_vel* values = origin ox oy oz axis ax ay az omega om
         origin = mandatory keyword
         ox oy oz = origin of rotation (length units)
         axis = mandatory keyword
         ax ay az = axis vector for rotation (length units)
         omega = mandatory keyword
         om = rotaional velocity around specifyied axis (rad/time units)
       *curvature* value = c
         c = maximum angle between mesh faces belonging to the same surface (in degree)
       *curvature_tolerant* value = ct
         ct = yes or no



Examples
""""""""


.. parsed-literal::

   fix cad all mesh/surface file mesh.stl type 1

**LIGGGHTS vs. LAMMPS Info:**

This command is not available in LAMMPS.

Description
"""""""""""

This fix allows the import of triangular surface mesh wall geometry for granular simulations from 
ASCII STL files or legacy ASCII VTK files. Style *mesh/surface* is a general surface mesh, and
*mesh/surface/planar* represents a planar mesh. *mesh/surface/planar* requires the mesh to 
consist of only 1 planar face.

Generally, you can apply scaling, offset and rotation to the imported mesh via keywords *scale*\ , 
*move*\ , *rotate*\ . Operations are applied in the order as they are specified. The group-ID defines
which particles will "see" the mesh, in case it is used as a granular wall.

One fix represents one wall with a specific material, where the material is identified 
via keyword *type*\ . If multiple meshes with different materials are desired, the respective 
meshes must be imported with different fix mesh/surface commands.

With the *temperature* keyword, you can define a constant temperature for a mesh in 
conjunction with heat conduction via :doc:`fix heat/gran <fix_heat_gran_conduction>`. Note that the 
actual calculation of the heat transfer happens only if you use the mesh in conjunction 
with a granular wall, see :doc:`fix wall/gran <fix_wall_gran>`.

With the optional *surface\_vel* keyword, you can specify the imported mesh as conveyor belt. 
The velocity direction for each mesh face is given by the projection of the conveyor 
belt velocity parallel to the mesh face, the velocity magnitude for each mesh face is 
equal to the conveyor belt velocity. This ensures the model makes sense also in case 
the mesh is curved. Likewise, the optional rotation model activated via keyword
*surface\_ang\_vel* mimics rotational motion of the mesh (e.g. for modeling a shear cell)

The *precision* keyword specifies how far away mesh nodes can be at maximum to
be recognized as identical.

If LIGGGHTS stalls because of duplicate elements, you can try setting 
*heal* to auto\_remove\_duplicates. LIGGGHTS will then try to heal the geometry
by removing duplicate elements.

If the optional *element\_exclusion\_list* keyword is used in mode 'write', LIGGGHTS 
will write a list of elements which

* have more than the allowed 5 face neighbors per surface
* have an angle below 0.0181185 degrees
* are duplicate elements

to a file. The 'read' mode can then use this file and will skip the elements in 
the list. However, you can also manually write such a file to exclude certain elements.

.. warning::

   The *element\_exclusion\_list write* model works in serial only. However,
   this is not a real restriction, since you can generate the exclusion lists in serial,
   but then read them to import the mesh into a parallel simulation

.. warning::

   If you use the 'heal' or 'element\_exclusion\_list' keywords,
   you should check the changes to the geometry, e.g. by using a :doc:`dump mesh/stl <dump>` command.

The *curvature* keyword lets you specify up to which angle between two triangles the 
triangles should be treated as belonging to the same surface (e.g. useful for bends). 
This angle is used to decide if (a) contact history is copied from one triangle to 
the other as the contact point proceeds and (b) if edge and corner interaction is 
calculated.

The *curvature\_tolerant* keyword can simply turn off the check that
the *curvature* must not be larger than any angle in any mesh element.
This is typically not recommended, but can be used as a last resort measure.

**Quality checks / error and warning messages:**

LIGGGHTS checks a couple of quality criteria upon loading a mesh. LIGGGHTS tries
to give you as much information about the issue as possible.

Warning messages:

* There should be no angle < 0.5&deg; in any element
* The number of neighbor elements should be <= 5 for any element
* All nodes should be within the simulation box

If any of the above rules is not fulfilled, a warning is generated. Keyword
*verbose* controls if details about the warning are written to the screen.

Error messages:

* The *curvature* must not be larger than any angle in any mesh element
* Mesh elements must not be duplicate
* Coplanar mesh elements that share an edge must not overlap
* Mesh elements must not leave the simulation domain

If any of the above rules is not fulfilled, an error is generated and 
LIGGGHTS halts. Error messages are always *verbose*\ . 
If LIGGGHTS halts due to the last error, you might think about (a) 
changing the mesh import parameters (\ *scale*\ , *move*\ , *rotate*\ ), (b) 
changing the mesh dynamics if a :doc:`fix move/mesh <fix_move_mesh>` is 
applied or using :doc:`boundary m m m <boundary>`.


----------


Styles with a *cuda*\ , *gpu*\ , *omp*\ , or *opt* suffix are functionally
the same as the corresponding style without the suffix.  They have
been optimized to run faster, depending on your available hardware, as
discussed in :doc:`Section\_accelerate <Section_accelerate>` of the
manual.  The accelerated styles take the same arguments and should
produce the same results, except for round-off and precision issues.

These accelerated styles are part of the USER-CUDA, GPU, USER-OMP and OPT
packages, respectively.  They are only enabled if LAMMPS was built with
those packages.  See the :ref:`Making LAMMPS <start_3>`
section for more info.

You can specify the accelerated styles explicitly in your input script
by including their suffix, or you can use the :ref:`-suffix command-line switch <start_7>` when you invoke LAMMPS, or you can
use the :doc:`suffix <suffix>` command in your input script.

See :doc:`Section\_accelerate <Section_accelerate>` of the manual for
more instructions on how to use the accelerated styles effectively.


----------


**Restart, fix\_modify, output, run start/stop, minimize info:**

This fix writes the STL data to binary :doc:`restart files <restart>` to be able to 
correctly resume the simulation in case the mesh is moved. None of the 
:doc:`fix\_modify <fix_modify>` options are relevant to this fix. No global 
scalar or vector or per-atom quantities are stored by this fix for access by 
various :ref:`output commands <howto_15>`. No parameter of this fix 
can be used with the *start/stop* keywords of the :doc:`run <run>` command. 
This fix is not invoked during :doc:`energy minimization <minimize>`.

Restrictions
""""""""""""


To date, only ASCII STL and VTK files can be read (binary is not supported). 
In the current implementation, each processor allocates memory for the whole 
geometry, which may lead to memory issues for very large geometries . 
It is not supported to use both the moving mesh and the conveyor belt feature.

Related commands
""""""""""""""""

:doc:`fix wall/gran <fix_wall_gran>`

**Default:** curvature = 0.256235 degrees, precision = 1e-8, verbose = no, heal = no


