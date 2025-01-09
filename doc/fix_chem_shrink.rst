.. index:: fix chem/shrink

fix chem/shrink command
=======================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID chem/shrink speciesA A_name molMassA A_value speciesC C_name molMassC C_value molMassB B_value k k_value rmin r_value

* ID, group-ID are documented in :doc:`fix <fix>` command
* chem/shrink = style name of this fix command
* speciesA = obligatory keyword
* A\_name = name of species A (reacting gas)
* molMassA = obligatory keyword
* A\_value = molar mass of species A in kg/mol
* speciesC = obligatory keyword
* C\_name = name of species C (product gas)
* molMassC = obligatory keyword
* C\_value = molar mass of species C in kg/mol
* molMassB = obligatory keyword
* B\_value = molar mass of particle kg/mol
* k = obligatory keyword
* k\_value = reaction rate constant
* rmin = obligatory keyword
* r\_value = minimum radius value


Examples
""""""""


.. parsed-literal::

   fix cfd4 all chem/shrink speciesA O2 molMassA 31.99 speciesC CO2 molMassC 44.01 molMassB 12.01 k 2.5e3 rmin 0.005

**LIGGGHTS vs. LAMMPS info:**

This command is not available in LAMMPS.

Description
"""""""""""

The mass flow rate for the reactant gas species can be calculated with the equation

dmA = -k\*rho\_gas\*Y\_a\*Particle\_surface\_area\*dt,

in which Y\_a and rho\_gas are the reactant gas species concentration and the
density at the particle location.
The mass flow rates of particle and product gas can then be calculated as

dmB =  dmA\*MolarMassB/MolarMassA,

dmC = -dmA\*MolarMassC/MolarMassA.

The calculation of mass flow rate of the particle allows us to determine the new
mass at each time step, and thus the new radius of particle.
Since the particle reacts with gas, the radius will shrink.

With the help of the user defined *rmin* value, the minimum particle radius is
defined. Particles that reach the *rmin* value are deleted from the domain in
order to avoid numerical complications.

It must be kept in mind that the mass flow rates depend highly on the reaction
rate coefficient.
The higher the reaction rate constant, the faster the reduction of the particle
will be.

**Restart, fix\_modify, run start/stop, minimize info:**

No information about this fix is written to :doc:`binary restart files <restart>`.
None of the :doc:`fix\_modify <fix_modify>` options are relevant to this fix.

No global or per-atom quantities are stores by this fix for access by various
:ref:`output commands <howto_15>`.

No parameter of this fix can be used with the *start/stop* keywords of
the :doc:`run <run>` command.  This fix is not invoked during :doc:`energy minimization <minimize>`.

Restrictions
""""""""""""


This fix needs a fix couple/cfd and couple/cfd/chemistry before it is defined.

Related commands
""""""""""""""""

:doc:`fix couple/cfd/chemistry <fix_cfd_coupling_chemistry>`

**Default:** none


