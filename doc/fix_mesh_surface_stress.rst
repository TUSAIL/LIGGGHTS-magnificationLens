.. index:: fix mesh/surface/stress

fix mesh/surface/stress command
===============================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID mesh/surface/stress file filename premesh_keywords premesh_values mesh_keywords mesh_values surface_keyword surface_values stress_keywords stress_values

* ID, is documented in :doc:`fix <fix>` command, the group-ID is ignored for this command.
* mesh/surface/stress = style name of this fix command
* file filename premesh\_keywords premesh\_values  mesh\_keywords mesh\_values surface\_keyword surface\_values are documented in :doc:`fix mesh/surface <fix_mesh_surface>`.
* zero or more stress\_keyword/value pairs may be appended
* stress\_keyword = *stress* or *wear*
  
  .. parsed-literal::
  
       *stress* value = on or off
       *reference_point* values = rx ry rz
         rx, ry, rz = coordinates of reference point
       *wear* value = finnie or off



Examples
""""""""


.. parsed-literal::

   fix cad all mesh/surface/stress file mesh.stl type 1 wear finnie

**LIGGGHTS vs. LAMMPS Info:**

This command is not available in LAMMPS.

Description
"""""""""""

This fix is identical to :doc:`fix mesh/surface <fix_mesh_surface>` except for the fact 
that the pressure and shear force that the particles in the fix group exert on each 
triangle of the mesh is evaluated (which costs a bit of performance). Also, the total 
force and torque on the particle is calculated (see output info). The per-element forces 
can be dumped into VTK format using :doc:`dump mesh/vtk <dump>`.

With the optional *stress* keyword, stress tracking can be turned off is desired. The 
reference point for calculating the body torque can be controlled via the *referece\_point*
keyword. The optional *wear* keyword can activates a simple qualitative wear model 
(\ *finnie*\ ) - for details on the model, see the separate /doc/finnie-wear.pdf. The 
finnie constant k in Eq. (4.23) has to be specified as follows:


.. parsed-literal::

   fix id all property/global k_finnie peratomtypepair n_atomtypes value_11 value_12 .. value_21 value_22 .. .

       (value_ij=value for the finnie constant between atom type i and j; n_atomtypes is the number of atom types you want to use in your simulation)

**Restart, fix\_modify, output, run start/stop, minimize info:**

This fix stores a global vector with 6 components for access by various 
:ref:`output commands <howto_15>`. The first 3 components are equal to the 
total force on the mesh, the last 3 components store the total torque on the body 
exerted by the particles. Other info see :doc:`fix mesh/surface <fix_mesh_surface>`.

Related commands
""""""""""""""""

:doc:`fix mesh/surface <fix_mesh_surface>`
:doc:`fix wall/gran <fix_wall_gran>`

Default
"""""""

stress = on
reference\_point = 0. 0. 0.
wear = off


