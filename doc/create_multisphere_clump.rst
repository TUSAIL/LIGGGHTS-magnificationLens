.. index:: create\_multisphere\_clump

create\_multisphere\_clump command
==================================

Syntax
""""""


.. parsed-literal::

   create_multisphere_clump dmin dstyle dvalue rmin rvalue pmax pvalue seed svalue surfacefile file keyword values filetype fileargs

* dmin = obligatory keyword
* dstyle = *absolute* or *radius\_ratio*
* dvalue = minimum distance between spheres and next surface point used for sphere generation
* rmin  = obligatory keyword
* rvalue = minimum sphere radius
* pmax = obligatory keyword
* pvalue = maximum fraction of surface points used for sphere generation
* seed  = obligatory keyword
* svalue = random number seed
* surfacefile = obligatory keyword
* file = surface file name
* zero or more keyword/value pairs may be appended
* keyword = *invert\_normals* or *subdivide*
  
  .. parsed-literal::
  
       *invert_normals* value = *yes* or *no*
       *subdivide* values = style N
         style = *linear* or *loop* or *butterfly*
         N = number of subdivision iterations

* one output filetype must be appended
* filetype = *clumpfile* or *datafile*
  
  .. parsed-literal::
  
       *clumpfile* args = filename
       *datafile* args = filename atom_type density
         filename = data filename
         atom_type = atom type (optional)
         density = particle density (optional)



Examples
""""""""


.. parsed-literal::

   create_multisphere_clump dmin absolute 0.0002 rmin 0.002 pmax 1.0 seed 2133421 surfacefile meshes/infile1.vtk clumpfile data/clump1.dat

Description
"""""""""""

This command creates a multi-sphere clump from a VTK, STL or PLY surface mesh
file and writes the clump data to a file.
The VTK library is used to read an STL file, a PLY file, or an unstructured grid
or polydata dataset from VTK simple legacy or XML files.
The polygons of the surface mesh are triangulated and optionally the surface is
subdivided.
Finally, the overlapping multi-sphere clump method (OMCM, see :ref:`Ferellec <Ferellec2010>`)
is used to generate a clump configuration which is then written to a clump or
data file.

Restrictions
""""""""""""


Requires LIGGGHTS to be linked to the VTK library.

Related commands
""""""""""""""""

:doc:`fix particletemplate/multisphere <fix_particletemplate_multisphere>`, :doc:`read\_data <read_data>`

Default
"""""""

*invert\_normals* = *yes*\ , *subdivide* = off, atom\_type = 1, density = 1000


----------


.. _Ferellec2010:



**(Ferellec, 2010)** "A method to model realistic particle shape and inertia in DEM", J.F. Ferellec and G.R. McDowell, Granular Matter (2010) 12:459–467


