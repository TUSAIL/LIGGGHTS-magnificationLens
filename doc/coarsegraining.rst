.. index:: coarsegraining

coarsegraining command
======================

Syntax
""""""


.. parsed-literal::

   coarsegraining cg_factor args

* cg\_factor = coarse-graining factor to be applied (dimensionless)
* args = *model\_check*
  
  .. parsed-literal::
  
       *model_check* = error or warn



Examples
""""""""


.. parsed-literal::

   coarsegraining 2.0

Description
"""""""""""

Coarsegraining is a methodology to reduce the computational effort of a DEM
calculation by scaling up the particle size by a coarse-graining factor
(cg\_factor). Thereby, the model size decreases by factor cg-factor\^3.

However, changing particle size will change the physics of the model. 
On the particle scale, this change is obviously inevitable. However,
in many cases model constants can be adapted so that on the bulk scale
the change of the physics caused by the coarse-graining model is acceptable. 
See e.g. :ref:`(Radl) <Radl>` and :ref:`(Bierwisch) <Bierwisch>` for details.

Some of the models in LIGGGHTS support scaling of the model constants
to counteract this change in physics on the bulk scale. Moreover,
some commands (such as insertion commands or the neighbor command) re-scale
some of their length scales. Using *model\_check* = error will throw an error 
if a model/command does not yield consistent results with coarse-graining.
Using *model\_check* = warn will issue a warning if a model/command does not 
yield consistent results with coarse-graining.

**Model overview:**

This table provides an overview of how different models behave when
coarsegraining is used. Some models scale length-scales, other models
scale model parameters to make results more coarse-graining consistent.
Models that are not mentioned here are not affected by using the 
coarsegraining command

+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`create\_atoms <create_atoms>`                                        |                                        | not supported                                         |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`fix addforce <fix_addforce>`                                         |                                        | not supported / inconsistent                          |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`fix drag <fix_drag>`                                                 |                                        | not supported / inconsistent                          |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| fix dragforce                                                              |                                        | downscaling of A, Re; upscaling of dragforce          |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`fix efield <fix_efield>`                                             |                                        | not supported / inconsistent                          |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`fix heat/gran/conduction <fix_heat_gran_conduction>`                 |                                        | not supported / inconsistent                          |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`fix mesh/surface/stress <fix_mesh_surface_stress>`                   | Finnie wear model                      | inherently compatible                                 |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`fix particletemplate/sphere <fix_particletemplate_sphere>`           |                                        | radius -> cg\_factor\*radius                          |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`fix particletemplate/multisphere <fix_particletemplate_multisphere>` |                                        | radius -> cg\_factor\*radius                          |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`fix spring <fix_spring>`                                             |                                        | not supported / inconsistent                          |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`fix spring/rg <fix_spring_rg>`                                       |                                        | not supported / inconsistent                          |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`fix spring/self <fix_spring_self>`                                   |                                        | not supported / inconsistent                          |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`fix viscous <fix_viscous>`                                           |                                        | not supported / inconsistent                          |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`neighbor <read_data>`                                                |                                        | skin -> cg\_factor\*skin                              |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`pair gran/\* <pair_gran>`                                            | any cohesion or rolling friction model | not supported / inconsistent                          |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`pair gran/hertz/history <pair_gran>`                                 | base model                             | inherently compatible                                 |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`pair gran/hooke/history base model <pair_gran>`                      | base model                             | inherently compatible                                 |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`pair gran/hooke  base model <pair_gran>`                             | base model                             | inherently compatible                                 |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`pair gran/hertz/history/stiffness <pair_gran>`                       |                                        | not supported / inconsistent                          |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`pair gran/hooke/history/stiffness <pair_gran>`                       | base model with damp\_massflag=0       | kn -> cg\_factor\*kn, gamman -> cg\_factor\^2\*gamman |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`pair gran/hooke/history/stiffness <pair_gran>`                       | base model with damp\_massflag=1       | kn -> cg\_factor\*kn, gamman -> gamman/cg\_factor     |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`pair gran/hooke/stiffness <pair_gran>`                               | base model with damp\_massflag=0       | kn -> cg\_factor\*kn, gamman -> cg\_factor\^2\*gamman |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`pair gran/hooke/stiffness <pair_gran>`                               | base model with damp\_massflag=1       | kn -> cg\_factor\*kn, gamman -> gamman/cg\_factor     |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+
| :doc:`set <set>`                                                           |                                        | diameter -> cg\_factor\*diameter                      |
+----------------------------------------------------------------------------+----------------------------------------+-------------------------------------------------------+

.. warning::

   Even if a model does not support proper coarse graining, in many cases
   it will still be possible to calibrate the model constant manually to capture the
   bulk scale physics with a coarse-grained model.

Restrictions
""""""""""""


General warning: Coarse graining is an approximative method and
will \_never\_ deliver exactly the same results than a fine-grained
simulation.

One natural restriction is that the ratio of geometry length scale to 
particle length scale should be >> 1 when coarse graining is applied.

See description above the fact that not all LIGGGHTS models will
deliver consistent results with coarse-graining ratios > 1.

**Related commands:** 
see table above

**Default:** 
cg\_factor = 1 (no coarse-graining applied)


----------


.. _Radl:



**(Radl)** S. Radl et. al., PARCEL-BASED APPROACH FOR THE SIMULATION OF GAS-PARTICLE FLOWS, Proc. 8th International Conference on CFD in Oil & Gas, Metallurgical and Process Industries, 2011

.. _Bierwisch:



**(Bierwisch)** Journal of the Mechanics and Physics of Solids, Volume 57, Issue 1, January 2009, Pages 10ff


