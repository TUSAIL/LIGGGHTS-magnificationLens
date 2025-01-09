gran rolling\_friction cdt
==========================

Syntax
""""""


.. parsed-literal::

   rolling_friction cdt

**LIGGGHTS vs. LAMMPS Info:**

This part of :doc:`pair gran <pair_gran>` and 
:doc:`fix wall/gran <fix_wall_gran>`
is not available in LAMMPS.

Description
"""""""""""

This model can be used as part of :doc:`pair gran <pair_gran>` and 
:doc:`fix wall/gran <fix_wall_gran>`

The constant directional torque (CDT) model adds an additional torque 
contribution, equal to

.. image:: Eqs/pair_gran_roll_cdt_eq1.png
   :align: center

w\_r\_shear is the projection of w\_r into the shear plane, where w\_r = w1-w2

If the rolling friction model is activated, the coefficient of rolling friction (rmu) must be defined as


.. parsed-literal::

   fix id all property/global coefficientRollingFriction peratomtypepair n_atomtypes value_11 value_12 .. value_21 value_22 .. .
       (value_ij=value for the coefficient of rolling friction between atom type i and j; n_atomtypes is the number of atom types you want to use in your simulation)

.. warning::

   You have to use atom styles beginning from 1, e.g. 1,2,3,...

**(Ai)** Jun Ai, Jian-Fei Chen, J. Michael Rotter, Jin Y. Ooi, Powder Technology, 206 (3), p 269-282 (2011).


