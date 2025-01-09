How-to for superquadric particles
=================================

Introduction
------------

Superquadric simulations allow LIGGGHTS(R) to use superquadric bodies as particles. 
This text describes how to perform superquadric simulations in LIGGGHTS(R).

Compilation
-----------

.. _boost: http://www.boost.org/



To compile LIGGGHTS(R) with this feature the `boost <boost_>`_ library must be
available on the system.
On most Linux-distributions a recent version can be installed via the package
managment systems.

The way how to enable the superquadric feature depends on the build-system.

Using make
^^^^^^^^^^

Before starting the compilation, you have to enable the superquadric model in
your Makefile. You have to add the following settings to your Makefile:


.. parsed-literal::

   LMP_INC += -DSUPERQUADRIC_ACTIVE_FLAG -DNONSPHERICAL_ACTIVE_FLAG

In case of a non-system-wide boost installation add:


.. parsed-literal::

   EXTRA_INC += -IPath/to/your/Boost/include

.. note::

   Make sure that you add the definitions after the original assignments of
   LMP\_INC and EXTRA\_INC. Otherwise your changes will be overwritten.

.. note::

   Most Boost libraries are header-only: they consist entirely of header
   files containing templates and inline functions, and require no
   separately-compiled library binaries or special treatment when linking. (`link <boost_>`_)

Using CMake
^^^^^^^^^^^

To enable the superquadric feature using the CMake build system, we provide
CMake a command-line parameter.


.. parsed-literal::

   cmake ../src -DUSE_SUPERQUADRIC=on

Compile the ParaView plug-in
----------------------------

The superquadric feature of LIGGGHTS comes with its own dedicated ParaView
plug-in to properly visualize superquadric particles.

The compilation of the plug-in is done with the following steps. Adjust the
paths according to your local installation.


.. parsed-literal::

   cd ~/CFDEM/LIGGGHTS/tools/paraview/SuperquadricGlyph
   mkdir build
   cd build
   cmake .. -DParaView_DIR:PATH=/absolute/path/to/paraview/build/dir
   make

.. note::

   The path to ParaView is the build directory, and not the source directory.
   If a CFDEM environment has been sourced, then CMake should be able to
   automatically find the proper path to ParaView.

If compilation finishes without any errors, then the build directory will
contain a library named libSuperquadricGlyphFilter.so.

To visualize superquadrics in ParaView, open the converted dump files of a
superquadric case, click in the menu "Tools --> Manage Plugins...", click on the
"Load New ..." button and select the libSuperquadricGlyphFilter.so file.

Detailed description
--------------------

The overall simulation structure stays the same for superquadric simulations as
used for standard LIGGGHTS(R) simulations. In order to create a superquadric
simulation based on an existing case you have to perform following steps:

* Use :doc:`atom\_style superquadric <atom_style>`
* For contact models (pair\_style gran as well as fix wall/gran) use :doc:`surface superquadric <gran_surface_superquadric>`
* The superquadric model requires a special integrator, namly :doc:`fix nve/superquadric <fix_nve_superquadric>`
* To define new superquadric particles use the :doc:`fix particletemplate/superquadric <fix_particletemplate_superquadric>`

Performance
-----------

The superquadric model uses the framework of LIGGGHTS(R). Therefore, the parallel
scalability is linear as LIGGGHTS(R) itself. Compared to standard LIGGGHTS(R),
the calculation of contact points is computational expensive for superquadric
bodies.


