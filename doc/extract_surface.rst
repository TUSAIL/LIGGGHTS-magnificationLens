.. index:: extract\_surface

extract\_surface command
========================

Syntax
""""""


.. parsed-literal::

   extract_surface inputfile file surfacefile extrusionfile extrude_length l min_rad r mode

* inputfile = filename of VTK grid data
* file = obligatory keyword
* surfacefile = filename to write surface VTK data
* optional extrusion args
  
  .. parsed-literal::
  
       extrusionfile = filename to write extruded surface VTK data
       extrude_length = obligatory keyword
       l = total height of extruded volume
       min_rad = obligatory keyword
       r = distance volume is extruded outwards

* mode = output file mode *ascii* or *binary* (optional)


Examples
""""""""


.. parsed-literal::

   extract_surface data/grid.vtk file data/surface.vtk data/extrusion.vtk extrude_length 0.1 min_rad 0.025

Description
"""""""""""

Given an unstructured grid VTK file consisting of hexahedral cells,
this command will extract and triangulate the surface and save it to
an unstructured grid VTK file adding a unique ID for each cell face
(i.e. typically two triangles). Furthermore, the surface thus obtained
may be used to create a shell geometry extruding the surface *l-r* distance
units inwards and *r* distance units outwards. If used as insertion volume
for multi-level coarse-grain simulations, *r* should be set to the minimum
particle radius occuring in the simulation. The total extrusion length *l*
should be about 2 particle diameters but is ultimately determined by
the insertion rate and the velocity of the particles.

Restrictions
""""""""""""


none

Default
"""""""

mode = ascii


