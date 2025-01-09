.. index:: fix chem/shrink/core

fix chem/shrink/core command
============================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID chem/shrink/core speciesA A_name molMassA A_value speciesC C_name molMassC C_value kch2 kch2_value keyword values

* ID, group-ID are documented in :doc:`fix <fix>` command
* chem/shrink/core = style name of this fix command
* speciesA = obligatory keyword
* A\_name = name of species A
* molMassA = obligatory keyword
* A\_value = molar mass of species A in kg/mol
* speciesC = obligatory keyword
* C\_name = name of species C
* molMassC = obligatory keyword
* C\_value = molar mass of species C in kg/mol
* zero or more keyword/value pairs may be appended
* keyword = *nevery* or *scale\_reduction\_rate* or *screen*

.. parsed-literal::

     *nevery* value = every how many time-steps model is updated
     *scale_reduction_rate* value = multiplaction factor for reduction rate
     *screen* value = *yes* or *no*



Examples
""""""""

Single gas:


.. parsed-literal::

   fix cfd5 all chem/shrink/core speciesA CO molMassA 0.02801 speciesC CO2 molMassC 0.04401 scale_reduction_rate 2.0 nevery 10 screen yes

Multiple gases:


.. parsed-literal::

   fix cfd5 all chem/shrink/core speciesA CO molMassA 0.02801 speciesC CO2 molMassC 0.04401 scale_reduction_rate 10.0 screen yes
   fix cfd6 all chem/shrink/core speciesA H2 molMassA 0.00202 speciesC H2O molMassC 0.01801 scale_reduction_rate 10.0 screen yes

**LIGGGHTS vs. LAMMPS info:**

This command is not available in LAMMPS.

Description
"""""""""""

Activates the Un-reacted Shrinking Core Model (USCM), for reactant species A
and product species C.
Species molar masses have to be given in kg/mol units.

The fix follows through the loop of calculating particle layer masses,
fractional reduction, equilibrium constant and molar equilibrium values,
reaction resistance term, diffusion resistance term, mass transfer term,
chemical reaction rate, and particle and gas mass updates.

All three resistance terms are implemented according to the model described in
:ref:`Valipour (2009) <Valipour2009>`.
For detailed equations we refer to this publication and references therein.

Once this fix is activated, one needs to specify the following fixes defining
the reaction properties;


.. parsed-literal::

   fix k0-ID group-ID property/global k0_fix-ID vector Fe/Wustite-value Wustite/Magnetite-value Magnetite/Hematite-value
   fix Ea-ID group-ID property/global Ea_fix-ID vector Fe/Wustite-value Wustite/Magnetite-value Magnetite/Hematite-value

* k0-ID, Ea-ID = name for k0, Ea fix of type :doc:`property/global <fix_property>`
* k0\_fix-ID, Ea\_fix-ID = variable name, that must start with k0\_, Ea\_ and the fix-ID of the main fix chem/shrink/core appended
* Values = value for frequency factor and activation energies that can be found in the literature


**Examples - 2:**


.. parsed-literal::

   fix k0_CO all property/global k0_cfd5 vector 17 25 2700
   fix Ea_CO all property/global Ea_cfd5 vector 69488 73674 113859
   fix k0_H2 all property/global k0_cfd6 vector 30 23 160
   fix Ea_H2 all property/global Ea_cfd6 vector 63627 71162 92092

Group properties such as layer porosity, tortuosity, pore diameter, and density
also need to be defined using the :doc:`fix property/global <fix_property>` command.
In these fix commands, variable names are to be formed with the keywords
*porosity\_*, *tortuosity\_*, *pore\_diameter\_*, and *density\_* and appending the
group-ID the fixes apply to.

**Examples - 3:**


.. parsed-literal::

   fix porosity      all property/global porosity_all      vector 0.61 0.31 0.16 0.15
   fix tortuosity    all property/global tortuosity_all    scalar 3
   fix pore_diameter all property/global pore_diameter_all vector 3.e-07 1.5e-05 1.e-05
   fix density       all property/global density_all       vector 7870. 5740. 5170. 5240.

The initial relative layer radii also need to be specified via a
:doc:`fix property/atom <fix_property>` command and the variable name *relRadii*\ .

**Examples - 4:**


.. parsed-literal::

   fix layerRelRad all property/atom relRadii vector yes no no 1.0 0.998 0.995 0.98

Additional internal fixes can be used to print out informative values of the reduction:


.. parsed-literal::

   fix massLayer            all property/atom massLayer            vector yes no no 0. 0. 0. 0.
   fix rhoeff               all property/atom rhoeff               vector yes no no 0. 0. 0. 0.
   fix fracRed              all property/atom fracRed              vector yes no no 0. 0. 0.
   fix Aterm_fix-ID         all property/atom Aterm_fix-ID         vector yes no no 0. 0. 0.
   fix Bterm_fix-ID         all property/atom Bterm_fix-ID         vector yes no no 0. 0. 0.
   fix Massterm_fix-ID      all property/atom Massterm_fix-ID      scalar yes no no 0.
   fix effDiffBinary_fix-ID all property/atom effDiffBinary_fix-ID vector yes no no 0. 0. 0.
   fix effDiffKnud_fix-ID   all property/atom effDiffKnud_fix-ID   vector yes no no 0. 0. 0.

**Restart, fix\_modify, run start/stop, minimize info:**

No information about this fix is written to :doc:`binary restart files <restart>`.
None of the :doc:`fix\_modify <fix_modify>` options are relevant to this fix.
No global or per-atom quantities are stored by this fix for access by various
:ref:`output commands <howto_15>`.

No parameter of this fix can be used with the *start/stop* keywords of
the :doc:`run <run>` command.  This fix is not invoked during :doc:`energy minimization <minimize>`.

Restrictions
""""""""""""


This fix requires a fix couple/cfd and a fix couple/cfd/chemistry to already be defined.

Related commands
""""""""""""""""

:doc:`fix couple/cfd/chemistry <fix_cfd_coupling_chemistry>`

Default
"""""""

*scale\_reduction\_rate* = 1, *screen* = *no*


----------


.. _Valipour2009:



**(Valipour, 2009)** "Mathematical Modeling of a Non-Catalytic Gas-Solid Reaction: Hematite Pellet Reduction with Syngas", M. S. Valipour, Sci. Iran., Vol. 16, No. 2, pp. 108-124 (2009)


