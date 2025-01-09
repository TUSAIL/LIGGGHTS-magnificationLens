gran model hertz
================

Syntax
""""""


.. parsed-literal::

   model hertz [other model_type/model_name pairs as described :doc:`here <pair_gran>` ] keyword values

* zero or more keyword/value pairs may be appended

.. parsed-literal::

     *limitForce* values = 'on' or 'off'
       on = ensures that the normal force is never attractive (an artefact that can occur at the end of a collision).
       off = standard implementation that might lead to attractive forces.
     *tangential_damping* values = 'on' or 'off'
       on = activates tangential damping
       off = no tangential damping

**LIGGGHTS vs. LAMMPS Info:**

This part of :doc:`pair gran <pair_gran>` and 
:doc:`fix wall/gran <fix_wall_gran>`
is not available in LAMMPS.

Description
"""""""""""

This granular model uses the following formula for the frictional force between two granular 
particles, when the distance r between two particles of radii Ri and Rj is less than their 
contact distance d = Ri + Rj. There is no force between the particles when r > d:

.. image:: Eqs/pair_gran_html_60b8ced2.png
   :align: center

In the first term is the normal force between the two particles and the second term is the 
tangential force. The normal force has 2 terms, a spring force and a damping force. The 
tangential force also has 2 terms: a shear force and a damping force. The shear force is 
a "history" effect that accounts for the tangential displacement ("tangential overlap") 
between the particles for the duration of the time they are in contact.
This term is controlled by the :doc:`tangential model <Section_gran_models>` in action
Keyword *tangential\_damping* can be used to eliminate the second part of the force in 
tangential direction. The way how the Coulomb friction limit acts is also controlled
by the :doc:`tangential model <Section_gran_models>` chosen by the user.

The quantities in the equations are as follows:

* delta\_n = d - r = overlap distance of 2 particles
* k\_n = elastic constant for normal contact
* k\_t = elastic constant for tangential contact
* gamma\_n = viscoelastic damping constant for normal contact
* gamma\_t = viscoelastic damping constant for tangential contact
* delta\_t = tangential displacement vector between 2 spherical particles which is truncated to satisfy a frictional yield criterion
* rmu = coefficient of rolling friction
* contactradius = contact radius, equal to particle radius - 0.5 \* delta\_n
* v\_n = normal component of the relative velocity of the 2 particles
* v\_t = tangential component of the relative velocity of the 2 particles
* w\_r = relative rotational velocity of the 2 particles


The Kn, Kt, gamma\_n, and gamma\_t coefficients are calculated as follows from the material properties:

.. image:: Eqs/pair_gran_html_m5aad056c.png
   :align: center

.. image:: Eqs/pair_gran_html_m225ba7de.png
   :align: center

To define those material properties, it is mandatory to use multiple :doc:`fix property/global <fix_property>` commands:


.. parsed-literal::

   fix id all property/global youngsModulus peratomtype value_1 value_2 ...
       (value_i=value for Youngs Modulus of atom type i)
   fix id all property/global poissonsRatio peratomtype value_1 value_2 ...
       (value_i=value for Poisson ratio of atom type i)
   fix id all property/global coefficientRestitution peratomtypepair n_atomtypes value_11 value_12 .. value_21 value_22 .. .
       (value_ij=value for the coefficient of restitution between atom type i and j; n_atomtypes is the number of atom types you want to use in your simulation)
   fix id all property/global coefficientFriction peratomtypepair n_atomtypes value_11 value_12 .. value_21 value_22 .. .
       (value_ij=value for the (static) coefficient of friction between atom type i and j; n_atomtypes is the number of atom types you want to use in your simulation)

.. warning::

   You have to use atom styles beginning from 1, e.g. 1,2,3,...

**Force Limiting:**

Note, that not using limitForce might lead to attractive forces between particles and walls, especially in case the coefficient of restitution is small. Be sure you include this key word for the pair style and the wall model if you like to avoid this.

Restrictions
""""""""""""


If using SI units, youngsModulus must be > 5e6
If using CGS units, youngsModulus must be > 5e5
When using the limitForce, the specified coefficient of restitution is only approximate. This might become problematic for low coefficients of restitution as shown in Schwager and Poschel.

Default
"""""""

*tangential\_damping* = 'on'
*limitForce* = 'off'

**(Di Renzo)** Alberto Di Renzo, Francesco Paolo Di Maio, CES, 59 (3), p 525–541 (2004).

**(Ai)** Jun Ai, Jian-Fei Chen, J. Michael Rotter, Jin Y. Ooi, Powder Technology, 206 (3), p 269-282 (2011).

**(Brilliantov)** Brilliantov, Spahn, Hertzsch, Poschel, Phys Rev E, 53, p 5382-5392 (1996).
**(Schwager)** Schwager, Poschel, Gran Matt, 9, p 465-469 (2007).

**(Silbert)** Silbert, Ertas, Grest, Halsey, Levine, Plimpton, Phys Rev E, 64, p 051302 (2001).

**(Zhang)** Zhang and Makse, Phys Rev E, 72, p 011301 (2005).


