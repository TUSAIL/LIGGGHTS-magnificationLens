.. index:: fix remove

fix remove command
==================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID remove nevery N massrate massrate_value style style_value [delete_below delete_below_value] seed seed_value keyword value ...

* ID, group-ID are documented in :doc:`fix <fix>` command
* remove = style name of this fix command
* nevery = obligatory keyword
* N = remove particles every this many timesteps
* massrate = obligatory keyword
* massrate\_value = rate at which to remove particles
* massratevariable = alternative keyword to massrate
* massrate\_name = name of variable with which to remove particles
* style = obligatory keyword
* style\_value = *shrink* or *delete*
* delete\_below = obligatory keyword if style\_value is *shrink*
* delete\_below\_value = radius below which particles are removed if style\_value is *shrink*
* seed = obligatory keyword
* seed\_value = random # seed (positive integer)
* zero or more keyword/value pairs may be appended
* keywords = *region* or *atomtype* or *integrated\_error* or *minmass* or *restart\_read* or *restart\_write* or *monitor\_heat* or *verbose* or *compress*
  
  .. parsed-literal::
  
       *region* value = region-ID
         region-ID = ID of the region where the particles will be removed
       *atomtype* value = type
         type = type of atoms to remove
       *integrated_error* value = *yes* or *no*
       *minmass* value = minimal mass to be removed at once
       *restart_read* value = *yes* or *no*
       *restart_write* value = *yes* or *no*
       *monitor_heat* value = *yes* or *no*
       *verbose* value = *yes* or *no*
       *compress* value = *yes* or *no*



Examples
""""""""


.. parsed-literal::

   fix 1 all remove nevery 500 massrate 3.5 style delete seed 5143 region del_region atomtype 1
   fix 1 all remove nevery 500 massrate 3.5 style shrink delete_below 0.001 seed 7543 region del_region
   fix 1 all remove nevery 500 massratevariable removal_rate style delete seed 2137 integrated_error no

Description
"""""""""""

Remove atoms from the simulation at the specified rate.

For style *delete*\ , all atoms belonging to the group are deleted immediately.

For style *shrink*\ , atoms belonging to the group are shrunk and get deleted only
if their radius is smaller than the value set via *delete\_below*.

The region from which particles are removed can be specified using the *region*
keyword.

The *atomtype* option allows to restrict deletion to a single type of atoms.

The *integrated\_error* option (default yes) accumulates the mass to be removed over time and subtracts the actually removed mass. If disabled, mass
is removed proportionally to the removal rate.

The *minmass* option allows to specify a minimal value (default 1e-6) for the mass to be removed at once.

The *monitor\_heat* keyword determines if in addition to the removed mass, also the amount of removed heat is stored.

The *verbose* keyword controls whether statistics about particle
removal is output to the screen each time particles are removed.

The *restart* options (default true) determine whether the fix reads and/or writes restart information.

If the *compress* keyword is set to *yes*\ , then after atoms are
removed, the atom IDs are re-assigned so that they run from 1 to the
number of atoms in the system. This is not done for molecular systems
(see the :doc:`atom\_style <atom_style>` command), regardless of the
*compress* setting, since it would foul up the bond connectivity that
has already been assigned.


----------


**Restart, fix\_modify, output, run start/stop, minimize info:**

If *restart\_write* is not disabled, information about the state of this fix is written to :doc:`binary restart files <restart>`.  None of the :doc:`fix\_modify <fix_modify>` options
are relevant to this fix. The accumulated removed mass and optionally the heat are stored
by this fix for access by various :ref:`output commands <howto_15>`.
No parameter of this fix can be used with the *start/stop* keywords of the
:doc:`run <run>` command.
This fix is not invoked during :doc:`energy minimization <minimize>`.

Restrictions
""""""""""""


Style *shrink* is not supported for multisphere particles

Related commands
""""""""""""""""

:doc:`delete\_atoms <delete_atoms>`

Default
"""""""

The option defaults are monitor\_heat = no, verbose = no and compress = yes


