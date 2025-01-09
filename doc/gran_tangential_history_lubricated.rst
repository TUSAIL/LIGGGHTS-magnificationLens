gran tangential history/lubricated
==================================

Syntax
""""""


.. parsed-literal::

   tangential history/lubricated

**LIGGGHTS vs. LAMMPS Info:**

This part of :doc:`pair gran <pair_gran>` and 
:doc:`fix wall/gran <fix_wall_gran>`
is not available in LAMMPS.

Description
"""""""""""

In this granular model, the tangential contact force is calculated in the same manner
as in :doc:`tangential history <gran_tangential_history>`. This model is to be used in
conjunction with the normal model :doc:`hertz/lubricated <gran_model_hertz_lubricated>`,
and will throw errors without it.

The coefficient of friction is selected from the dry or the lubricated value, depending
on the minimum approach distance between particle surfaces.

.. image:: Eqs/gran_tangential_history_lubricated_1.png
   :align: center

To define the material properties, it is mandatory to use multiple :doc:`fix property/global <fix_property>` commands:


.. parsed-literal::

   fix id all property/global coefficientFriction peratomtypepair n_atomtypes value_11 value_12 .. value_21 value_22 .. .
       (value_ij=value for the (static) dry coefficient of friction between atom type i and j; n_atomtypes is the number of atom types you want to use in your simulation)
   fix id all property/global coefficientFrictionLubricated peratomtypepair n_atomtypes value_11 value_12 .. value_21 value_22 .. .
       (value_ij=value for the (static) lubricated coefficient of friction between atom type i and j; n_atomtypes is the number of atom types you want to use in your simulation)

Related commands
""""""""""""""""

:doc:`model hertz/lubricated <gran_model_hertz_lubricated>`

**(Nijssen)** T.M.J. Nijssen, M. Ottens, J.T. Padding, Powder Technology (2022).


