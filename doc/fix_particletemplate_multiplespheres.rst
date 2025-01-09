.. index:: fix particletemplate/multiplespheres

fix particletemplate/multiplespheres command
============================================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID particletemplate/multiplespheres seed keyword values nspheres nspheresvalue ntry ntryvalue spheres values_spheres opt_keyword opt_values

* ID, group-ID are documented in :doc:`fix <fix>` command
* particletemplate/multiplespheres = style name of this fix command
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

* opt\_keyword = *bonded* or *bond\_type*
  
  .. parsed-literal::
  
     *bonded* value = one of the following options
       option 1 = *yes/implicit* where bonds are created based on sphere distances
       option 2 = *yes/explicit nbond_pairs npairs p11 p21 p12 p22...* where npairs is the number of bonded pairs and p1n/p2n are the spheres of the nth pair to be bonded
       option 3 = *no*
     *bond_type* value = bond type assigned to the bonds of this particle template



Examples
""""""""


.. parsed-literal::

   fix pts1 all particletemplate/multiplespheres 41981 atom_type 1 density constant 2500 nspheres 3 ntry 10000 spheres 0.0 0.0 0.0 0.005  0.005 0.0 0.0 0.005  0.01 0.0 0.0 0.005  
   fix pts2 all particletemplate/multiplespheres 74163 atom_type 1 density constant 2500 nspheres 3 ntry 10000 spheres file spherefile.txt scale 1.0 bonded yes/explicit nbond_pairs 2 1 2 2 3

**LIGGGHTS vs. LAMMPS Info:**

This command is not available in LAMMPS.

Description
"""""""""""

Define a multiplespheres particle template that is used as input for a 
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

If the granular bond model is used, the keyword *bonded* can be used
to define the bonds between the individual spheres of the template.
If the option *yes/implicit* is used, bonds between spheres are created
based on the skin distance. 
If the option *yes/explicit* is used, the number of bonded pairs and a list
of bond partners must be specified explicitly.

The optional keyword *bond\_type* can be used to define the type of bond that is
used for this template.

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

:doc:`fix particletemplate/sphere <fix_particletemplate_sphere>`,
:doc:`fix particletemplate/multisphere <fix_particletemplate_multisphere>`

**Default:** atom\_type = 1, bonded = no, bond\_type = 1


