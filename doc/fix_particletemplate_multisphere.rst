.. index:: fix particletemplate/multisphere

fix particletemplate/multisphere command
========================================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID particletemplate/multisphere seed keyword values nspheres nspheresvalue ntry ntryvalue spheres values_spheres type mt opt_keyword opt_values

* ID, group-ID are documented in :doc:`fix <fix>` command
* particletemplate/multisphere = style name of this fix command
* seed = random number generator seed (integer value)
* zero or more keyword/value pairs can be appended
* keyword, values are documented in :doc:`fix particletemplate/sphere <fix_particletemplate_sphere>` command
* nspheres = obligatory keyword
* nspheresvalue = number of spheres in the template (integer value)
* ntry = obligatory keyword
* ntryvalue = number of tries for Monte Carlo approach
* spheres = obligatory keyword
* values\_spheres = one out of the following options
  
  .. parsed-literal::
  
         option 1 = *file* *filename* *scale* *scalefactor*
         option 2 = *x1 y1 z1 r1 x2 y2 r2...* where x/y/z are sphere positions and r are the radii

* type = obligatory keyword
* mt = multisphere type of the template
* opt\_keyword = *mass* or *inertia\_tensor* or *use\_volume* or *use\_density*
  
  .. parsed-literal::
  
     *mass* value = mass assigned to this particle template
     *inertia_tensor* values = Ixx Ixy Ixz Iyy Iyz Izz
       Ixx Ixy Ixz Iyy Iyz Izz = 6 independent components of the inertia tensor 
     *use_volume* = particle density calculated from mass and volume (only if keyword 'mass' is used')
     *use_density* = particle volume calculated from mass and density (only if keyword 'mass' is used')



Examples
""""""""


.. parsed-literal::

   fix pts1 all particletemplate/multisphere 57461 atom_type 1 density constant 2500 nspheres 3 ntry 1000000 spheres 0. 0. 0. 0.005   0.005 0. 0. 0.005   0.01 0. 0. 0.005 type 1
   fix pts2 all particletemplate/multisphere 31967 atom_type 1 density constant 2500 nspheres 30 ntry 1000000 spheres file spherefile.txt scale 1.0 type 1

**LIGGGHTS vs. LAMMPS Info:**

This command is not available in LAMMPS.

Description
"""""""""""

Define a multisphere particle template that is used as input for a 
:doc:`fix\_particledistribution\_discrete <fix_particledistribution_discrete>` 
command. The particle parameters (positions, radii) are either defined 
manually as arguments to this command or via a text file, via the keyword
*file*\ . The format of this text file is


.. parsed-literal::

   x1 y1 z1 r1
   x2 y2 z2 r2
   ...

and the number of lines in this file has to be equal to n\_spheres as 
defined in this command. Comments can be made in this file via the '#' 
character. When a file is used for defining the multi-sphere 
template, the keyword *scale* must be used to define a *scalefactor* to scale 
up or down the particle positions and radii.

After the spheres are read, a Monte Carlo procedure is used to assess 
everything that is needed for the motion integration: mass, center of mass, 
and the inertia tensor including its eigensystem.

As an alternative, the body's mass and inertia tensor can be specified
directly via keywords *mass* and *inertia\_tensor*. Note that you can
use these keywords only together, i.e. defining only *mass* but not
*inertia\_tensor* will throw an error. Also note that only 2 out of the
3 variables density, mass and volume are independent. Thus, you are 
offered two options when *mass* and *inertia\_tensor* are used:
(a) if keyword *use\_volume* is specified, LIGGGHTS will use the 
specified *mass* and volume\_mc (the volume of the particle template 
calculated by the Monte Carlo procedure), and calculate the density from 
these two variables.
(b) if keyword *use\_density* is used, LIGGGHTS will use the specified 
*mass* and the specified *density* (see doc of 
:doc:`fix particletemplate/sphere <fix_particletemplate_sphere>` command),
and the volume of the clump is then calculated from these two variables.
Note you have to use either *use\_volume* or *use\_density* in case
*mass* and *inertia\_tensor* are used.

The multisphere type or shape type as defined via the *type* keyword must 
be unique integer given to each fix particletemplate/multisphere 
command by the user (starting with 1), the list of all multisphere types
in the simulation must be consecutive. At the moment, the multisphere type
is not used, but will be used to implement orientation-dependent drag
for CFD-DEM simulations in the future.

.. warning::

   As opposed to the number-based distributions used by 
   :doc:`fix pour/legacy <fix_pour>`, this fix uses the more common 
   distribution based on mass-% for the radius distribution (as does 
   :doc:`fix\_particledistribution\_discrete <fix_particledistribution_discrete>`).

**Restart, fix\_modify, output, run start/stop, minimize info:**

Information about the random state in this fix is written to 
:doc:`binary restart files <restart>` so you can restart a simulation with 
the same particles being chosen for insertion. None of the 
:doc:`fix\_modify <fix_modify>` options are relevant to this fix. No global 
scalar or vector or per-atom quantities are stored by this fix for access 
by various :ref:`output commands <howto_15>`. No parameter of this 
fix can be used with the *start*\ /\ *stop* keywords of the :doc:`run <run>` 
command. This fix is not invoked during :doc:`energy minimization <minimize>`.

Restrictions
""""""""""""
 none

Related commands
""""""""""""""""

:doc:`fix particletemplate/sphere <fix_particletemplate_sphere>`

**Default:** radius = 1.0, density = 1.0, atom\_type = 1


