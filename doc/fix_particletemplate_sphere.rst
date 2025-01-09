.. index:: fix particletemplate/sphere

fix particletemplate/sphere command
===================================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID particletemplate/sphere seed keyword values ...

* ID, group-ID are documented in :doc:`fix <fix>` command
* particletemplate/sphere = style name of this fix command
* seed = random number generator seed (integer value)
* zero or more keyword/value pairs can be appended
* keyword = *atom\_type* or *density* or *volume\_limit* or *radius*
  
  .. parsed-literal::
  
     *atom_type* value = atom type assigned to this particle template
     *density* values = random_style param1 (param2)
       random_style = 'constant' or 'uniform' or 'gaussian'
       param1 = density for 'constant', low value of density for 'uniform', expectancy value for 'gaussian'
       param2 = omitted for 'constant', high value of density for 'uniform', sigma value for 'gaussian'
     *volume_limit* value = lowest particle volume allowed in simulation
     *radius* values = random_style param1 (param2)
       random_style = 'constant' or 'uniform number' or 'uniform mass' or 'gaussian number'
       param1 = radius for 'constant', low value of radius for 'uniform', mu value for 'gaussian'
       param2 = omitted for 'constant', high value of radius for 'uniform', sigma value for 'gaussian'



Examples
""""""""


.. parsed-literal::

   fix pts1 all particletemplate/sphere 1 atom_type 1 density constant 2500 radius constant 0.0015

**LIGGGHTS vs. LAMMPS Info:**

This LIGGGHTS command is not available in LAMMPS.

Description
"""""""""""

Define a particle that is used as input for a :doc:`fix\_particledistribution\_discrete <fix_particledistribution_discrete>` command. You can choose the atom type, density and radius of the particles. For density and radius, you can choose between 'constant', 'uniform' and 'gaussian' random styles. Note that for radius, you can additionally choose between a number-based and mass-based uniform distribution, where the latter is used more frequently typically. 'gaussian' for radius only supports a number-based distribution.

It is thus possible to define a uniform or gaussian distribution on top of the discrete distribution defined by :doc:`fix\_particledistribution\_discrete <fix_particledistribution_discrete>`.

.. warning::

   As opposed to the number-based distributions used by :doc:`fix\_pour\_legacy <fix_pour>`, this fix uses the more common distribution based on mass-% for the radius distribution (as does :doc:`fix\_particledistribution\_discrete <fix_particledistribution_discrete>`).

LIGGGHTS will throw an error if the particle volume is too small compared to machine precision. 
If you are sure you know what you are doing you can override the default limit of 1e-12.

**Restart, fix\_modify, output, run start/stop, minimize info:**

Information about the random state in this fix is written to :doc:`binary restart files <restart>` so you can restart a simulation with the same particles being chosen for insertion. None of the :doc:`fix\_modify <fix_modify>` options are relevant to this fix. No global scalar or vector or per-atom quantities are stored by this fix for access by various :ref:`output commands <howto_15>`. No parameter of this fix can be used with the *start*\ /\ *stop* keywords of the :doc:`run <run>` command. This fix is not invoked during :doc:`energy minimization <minimize>`.

Restrictions
""""""""""""
 none

Related commands
""""""""""""""""

:doc:`fix\_particletemplate\_sphere <fix_particletemplate_sphere>`

**Default:** radius = 1.0, density = 1.0, atom\_type = 1, volume\_limit = 1e-12


