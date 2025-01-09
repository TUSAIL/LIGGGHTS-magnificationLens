gran rolling\_friction epsd2
============================

Syntax
""""""


.. parsed-literal::

   rolling_friction epsd2

**LIGGGHTS vs. LAMMPS Info:**

This part of :doc:`pair gran <pair_gran>` and 
:doc:`fix wall/gran <fix_wall_gran>`
is not available in LAMMPS.

Description
"""""""""""

This model can be used as part of :doc:`pair gran <pair_gran>` and 
:doc:`fix wall/gran <fix_wall_gran>`

The alternative elastic-plastic spring-dashpot (EPSD2) model (see Iwashita and Oda) adds an additional 
torque contribution. It is similar to the :doc:`EPSD model <gran_rolling_friction_epsd>`, but in contrast
to the original model the rolling stiffness k\_r is defined as

.. image:: Eqs/pair_gran_hooke_eqEpsd5.png
   :align: center

where k\_t is the abovementioned tangential stiffness. Furthermore, the viscous damping torque M\_rd is disabled at all.

The coefficient of rolling friction (rmu) must be defined as


.. parsed-literal::

   fix id all property/global coefficientRollingFriction peratomtypepair n_atomtypes value_11 value_12 .. value_21 value_22 .. .
       (value_ij=value for the coefficient of rolling friction between atom type i and j; n_atomtypes is the number of atom types you want to use in your simulation)

This coefficient rmu is equal to the rmu as defined in the :doc:`CDT model <gran_rolling_friction_cdt>`.

.. warning::

   You have to use atom styles beginning from 1, e.g. 1,2,3,...

**(Ai)** Jun Ai, Jian-Fei Chen, J. Michael Rotter, Jin Y. Ooi, Powder Technology, 206 (3), p 269-282 (2011).


