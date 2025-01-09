Contact models
==============

This section describes what granular models can be used along with
:doc:`pair gran <pair_gran>` and :doc:`fix wall/gran <fix_wall_gran>`.

.. _con\_1:

surface commands
----------------

Click on the surface model style itself for a full description:

+---------------------------------------+--------------------------+-------------------------------------------------+
| :doc:`default <gran_surface_default>` | :ref:`roughness <con_1>` | :doc:`superquadric <gran_surface_superquadric>` |
+---------------------------------------+--------------------------+-------------------------------------------------+

.. _con\_2:

model commands
--------------

Click on the normal model style itself for a full description:

+-----------------------------------------------------+-------------------------------------------------------+
| :doc:`hertz <gran_model_hertz>`                     | hertz/break                                           |
+-----------------------------------------------------+-------------------------------------------------------+
| :doc:`hertz/stiffness <gran_model_hertz_stiffness>` | :doc:`hertz/lubricated <gran_model_hertz_lubricated>` |
+-----------------------------------------------------+-------------------------------------------------------+
| :doc:`hooke <gran_model_hooke>`                     | hooke/break                                           |
+-----------------------------------------------------+-------------------------------------------------------+
| hooke/hysteresis                                    | :doc:`hooke/stiffness <gran_model_hooke_stiffness>`   |
+-----------------------------------------------------+-------------------------------------------------------+
| hooke/stiffness/collheat                            | jkr                                                   |
+-----------------------------------------------------+-------------------------------------------------------+

.. _con\_3:

cohesion commands
-----------------

Click on the cohesion model style itself for a full description:

+------------------------------------+----------------------------------+
| capillary                          | hamaker                          |
+------------------------------------+----------------------------------+
| morse                              | :doc:`sjkr <gran_cohesion_sjkr>` |
+------------------------------------+----------------------------------+
| :doc:`sjkr2 <gran_cohesion_sjkr2>` |                                  |
+------------------------------------+----------------------------------+

.. _con\_4:

tangential commands
-------------------

Click on the tangential model style itself for a full description:

+-------------------------------------------------------------------+----------------------------------------------------------------+
| :doc:`history <gran_tangential_history>`                          | :doc:`history/lubricated <gran_tangential_history_lubricated>` |
+-------------------------------------------------------------------+----------------------------------------------------------------+
| :doc:`incremental\_history <gran_tangential_incremental_history>` | :doc:`no\_history <gran_tangential_no_history>`                |
+-------------------------------------------------------------------+----------------------------------------------------------------+

.. _con\_5:

rolling\_friction commands
--------------------------

Click on the rolling friction model style itself for a full description:

+----------------------------------------+------------------------------------------+--------------------------------------------+
| :doc:`cdt <gran_rolling_friction_cdt>` | :doc:`epsd <gran_rolling_friction_epsd>` | :doc:`epsd2 <gran_rolling_friction_epsd2>` |
+----------------------------------------+------------------------------------------+--------------------------------------------+


