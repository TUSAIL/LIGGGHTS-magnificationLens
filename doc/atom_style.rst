.. index:: atom\_style

atom\_style command
===================

Syntax
""""""


.. parsed-literal::

   atom_style style args

* style = *angle* or *atomic* or *body* or *bond* or *charge* or *dipole* or         *electron* or *ellipsoid* or *full* or *line* or *meso* or         *molecular* or *peri* or *sphere* or *granular* or *bond/gran* or *superquadric* or *tri* or *hybrid* or *sph*


.. parsed-literal::

     args = none for any style except *body* and *hybrid*
     *body* args = bstyle bstyle-args
       bstyle = style of body particles
       bstyle-args = additional arguments specific to the bstyle
                     see the :doc:`body <body>` doc page for details
     *hybrid* args = list of one or more sub-styles, each with their args

Examples
""""""""


.. parsed-literal::

   atom_style atomic
   atom_style bond
   atom_style superquadric
   atom_style full
   atom_style body nparticle 2 10
   atom_style hybrid charge bond
   atom_style hybrid charge body nparticle 2 5

Description
"""""""""""

Define what style of atoms to use in a simulation.  This determines
what attributes are associated with the atoms.  This command must be
used before a simulation is setup via a :doc:`read\_data <read_data>`,
:doc:`read\_restart <read_restart>`, or :doc:`create\_box <create_box>`
command.

Once a style is assigned, it cannot be changed, so use a style general
enough to encompass all attributes.  E.g. with style *bond*\ , angular
terms cannot be used or added later to the model.  It is OK to use a
style more general than needed, though it may be slightly inefficient.

The choice of style affects what quantities are stored by each atom,
what quantities are communicated between processors to enable forces
to be computed, and what quantities are listed in the data file read
by the :doc:`read\_data <read_data>` command.

These are the additional attributes of each style and the typical
kinds of physical systems they are used to model.  All styles store
coordinates, velocities, atom IDs and types.  See the
:doc:`read\_data <read_data>`, :doc:`create\_atoms <create_atoms>`, and
:doc:`set <set>` commands for info on how to set these various
quantities.

+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *angle*              | bonds and angles                                                     | bead-spring polymers with stiffness  |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *atomic*             | only the default values                                              | coarse-grain liquids, solids, metals |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *body*               | mass, inertia moments, quaternion, angular momentum                  | arbitrary bodies                     |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *bond*               | bonds                                                                | bead-spring polymers                 |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *bond/gran*          | number of bonds and bond information                                 | granular bond models                 |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *charge*             | charge                                                               | atomic system with charges           |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *dipole*             | charge and dipole moment                                             | system with dipolar particles        |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *electron*           | charge and spin and eradius                                          | electronic force field               |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *ellipsoid*          | shape, quaternion, angular momentum                                  | aspherical particles                 |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *full*               | molecular + charge                                                   | bio-molecules                        |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *line*               | end points, angular velocity                                         | rigid bodies                         |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *meso*               | rho, e, cv                                                           | SPH particles                        |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *sph*                | q(pressure), density                                                 | SPH particles                        |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *molecular*          | bonds, angles, dihedrals, impropers                                  | uncharged molecules                  |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *peri*               | mass, volume                                                         | mesocopic Peridynamic models         |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *sphere or granular* | diameter, mass, angular velocity                                     | granular models                      |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *superquadric*       | semi-axes, blockiness parameters, mass, angular velocity, quaternion | granular models                      |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *tri*                | corner points, angular momentum                                      | rigid bodies                         |
+----------------------+----------------------------------------------------------------------+--------------------------------------+
| *wavepacket*         | charge, spin, eradius, etag, cs\_re, cs\_im                          | AWPMD                                |
+----------------------+----------------------------------------------------------------------+--------------------------------------+

.. warning::

   It is possible to add some attributes, such as a
   molecule ID, to atom styles that do not have them via the :doc:`fix property/atom <fix_property>` command.  This command also
   allows new custom attributes consisting of extra integer or
   floating-point values to be added to atoms.  See the :doc:`fix property/atom <fix_property>` doc page for examples of cases
   where this is useful and details on how to initialize, access, and
   output the custom values.

All of the above styles define point particles, except the *sphere*\ ,
*ellipsoid*\ , *electron*\ , *peri*\ , *wavepacket*\ , *line*\ , *tri*\ , and
*body* styles, which define finite-size particles.  See :ref:`Section\_howto 14 <howto_14>` for an overview of using finite-size
particle models with LAMMPS.

All of the styles assign mass to particles on a per-type basis, using
the :doc:`mass <mass>` command, except for the finite-size particle
styles.  They assign mass to individual particles on a per-particle
basis.

For the *sphere* style, the particles are spheres and each stores a
per-particle diameter and mass.  If the diameter > 0.0, the particle
is a finite-size sphere.  If the diameter = 0.0, it is a point
particle. This is typically used for granular models. Instead of 
*sphere*\ , keyword *granular* can be used.

For the *bond/gran* style, the number of granular bonds per atom is
stored, and the information associated to it: the type of each bond,
the ID of the bonded partner atom and the so-called bond history.
The bond history is similar to the contact history for granular 
interaction, it stores the internal state of the bond. What exactly
is stored in this internal state is defined by the granular 
:doc:`bond style <bond_gran>` used. There are 2 parameters: The number
of bond types, and the maximum number of bonds that each atom can
have. For each bond type, the parameters have to be specified via the
:doc:`bond\_coeff <bond_coeff>` command (see example :doc:`here <bond_gran>` )
Note that *bond/gran* is an experimental code which is may not be 
available in your release of LIGGGHTS. An example for the syntax is given below:


.. parsed-literal::

   atom_style bond/gran n_bondtypes 1 bonds_per_atom 6

For the *ellipsoid* style, the particles are ellipsoids and each
stores a flag which indicates whether it is a finite-size ellipsoid or
a point particle.  If it is an ellipsoid, it also stores a shape
vector with the 3 diameters of the ellipsoid and a quaternion 4-vector
with its orientation.

For the *electron* style, the particles representing electrons are 3d
Gaussians with a specified position and bandwidth or uncertainty in
position, which is represented by the eradius = electron size.

For the *peri* style, the particles are spherical and each stores a
per-particle mass and volume.

The *meso* style is for smoothed particle hydrodynamics (SPH)
particles which store a density (rho), energy (e), and heat capacity
(cv).

The *wavepacket* style is similar to *electron*\ , but the electrons may
consist of several Gaussian wave packets, summed up with coefficients
cs= (cs\_re,cs\_im).  Each of the wave packets is treated as a separate
particle in LAMMPS, wave packets belonging to the same electron must
have identical *etag* values.

For the *line* style, the particles are idealized line segments and
each stores a per-particle mass and length and orientation (i.e. the
end points of the line segment).

For the *tri* style, the particles are planar triangles and each
stores a per-particle mass and size and orientation (i.e. the corner
points of the triangle).

For the *body* style, the particles are arbitrary bodies with internal
attributes defined by the "style" of the bodies, which is specified by
the *bstyle* argument.  Body particles can represent complex entities,
such as surface meshes of discrete points, collections of
sub-particles, deformable objects, etc.

The :doc:`body <body>` doc page describes the body styles LAMMPS
currently supports, and provides more details as to the kind of body
particles they represent.  For all styles, each body particle stores
moments of inertia and a quaternion 4-vector, so that its orientation
and position can be time integrated due to forces and torques.

Note that there may be additional arguments required along with the
*bstyle* specification, in the atom\_style body command.  These
arguments are described in the :doc:`body <body>` doc page.


----------


Typically, simulations require only a single (non-hybrid) atom style.
If some atoms in the simulation do not have all the properties defined
by a particular style, use the simplest style that defines all the
needed properties by any atom.  For example, if some atoms in a
simulation are charged, but others are not, use the *charge* style.
If some atoms have bonds, but others do not, use the *bond* style.

The only scenario where the *hybrid* style is needed is if there is no
single style which defines all needed properties of all atoms.  For
example, if you want dipolar particles which will rotate due to
torque, you need to use "atom\_style hybrid sphere dipole".  When
a hybrid style is used, atoms store and communicate the union of all
quantities implied by the individual styles.

LAMMPS can be extended with new atom styles as well as new body
styles; see :doc:`this section <Section_modify>`.

Restrictions
""""""""""""


This command cannot be used after the simulation box is defined by a
:doc:`read\_data <read_data>` or :doc:`create\_box <create_box>` command.

The *angle*\ , *bond*\ , *full*\ , and *molecular* styles are
part of the MOLECULE package.

The *line* and *tri* styles are part of the ASPHERE package.

The *body* style is part of the BODY package.

The *dipole* style is part of the DIPOLE package.

The *peri* style is part of the PERI package for Peridynamics.

The *electron* style is part of the USER-EFF package for :doc:`electronic force fields <pair_eff>`.

The *meso* style is part of the USER-SPH package for smoothed particle
hydrodynamics (SPH).  See `this PDF guide <USER/sph/SPH_LAMMPS_userguide.pdf>`_ to using SPH in LAMMPS.

The *wavepacket* style is part of the USER-AWPMD package for the
:doc:`antisymmetrized wave packet MD method <pair_awpmd>`.

They are only enabled if LAMMPS was built with that package.  See the :ref:`Making LAMMPS <start_3>` section for more info.

Related commands
""""""""""""""""

:doc:`read\_data <read_data>`, :doc:`pair\_style <pair_style>`

Default
"""""""

atom\_style atomic


