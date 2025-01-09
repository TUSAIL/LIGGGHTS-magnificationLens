gran rolling\_friction epsd
===========================

Syntax
""""""


.. parsed-literal::

   rolling_friction epsd

**LIGGGHTS vs. LAMMPS Info:**

This part of :doc:`pair gran <pair_gran>` and 
:doc:`fix wall/gran <fix_wall_gran>`
is not available in LAMMPS.

Description
"""""""""""

This model can be used as part of :doc:`pair gran <pair_gran>` and 
:doc:`fix wall/gran <fix_wall_gran>`

The elastic-plastic spring-dashpot (EPSD) model (see Ai et al.) adds an additional 
torque contribution, equal to

.. image:: Eqs/pair_gran_hooke_eqEpsd1.png
   :align: center

where the torque due to the spring M\_rk is calculated as

.. image:: Eqs/pair_gran_hooke_eqEpsd2.png
   :align: center

Here k\_r denotes the rolling stiffness and dtheta\_r is the incremental relative 
rotation between the particles. The spring torque is limited by the full mobilization 
torque M\_rm that is determined by the normal force F\_n and the coefficient of rolling 
friction (rmu) (compare the :doc:`CDT model <gran_rolling_friction_cdt>`).

The viscous damping torque M\_rd is implemented as

.. image:: Eqs/pair_gran_hooke_eqEpsd3.png
   :align: center

where in the current implementation the damping is disabled in case of full mobilization 
(f = 0). The damping coefficient C\_r may be expressed as:

.. image:: Eqs/pair_gran_hooke_eqEpsd4.png
   :align: center

Here I\_i/j is the moment of inertia and m\_i/j is the mass of the particles i and j, 
respectively.

The coefficient of rolling friction (rmu) must be defined as


.. parsed-literal::

   fix id all property/global coefficientRollingFriction peratomtypepair n_atomtypes value_11 value_12 .. value_21 value_22 .. .
       (value_ij=value for the coefficient of rolling friction between atom type i and j; n_atomtypes is the number of atom types you want to use in your simulation)

This coefficient rmu is equal to the rmu as defined in the :doc:`CDT model <gran_rolling_friction_cdt>`.
In addition to rmu, eta\_r is the required material property that must be defined as


.. parsed-literal::

   fix id all property/global coefficientRollingViscousDamping peratomtypepair n_atomtypes value_11 value_12 .. value_21 value_22 .. .
       (value_ij=value for the coefficient of rolling friction between atom type i and j; n_atomtypes is the number of atom types you want to use in your simulation)

.. warning::

   You have to use atom styles beginning from 1, e.g. 1,2,3,...

**(Ai)** Jun Ai, Jian-Fei Chen, J. Michael Rotter, Jin Y. Ooi, Powder Technology, 206 (3), p 269-282 (2011).


