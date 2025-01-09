.. index:: fix particletemplate/fragments

fix particletemplate/fragments command
======================================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID particletemplate/fragments seed keyword values ...

* ID, group-ID are documented in :doc:`fix <fix>` command
* particletemplate/fragments = style name of this fix command
* seed = random number generator seed (integer value)
* zero or more keyword/value pairs can be appended
* keyword = *atom\_type* or *density* or *breakage\_index* or *tn\_family* or *maxattempt* or *omit\_radius*
  
  .. parsed-literal::
  
       *atom_type* value = atom type assigned to this particle template
       *density* values = random_style param1 (param2)
         random_style = 'constant' or 'uniform' or 'gaussian'
         param1 = density for 'constant', low value of density for 'uniform', expectancy value for 'gaussian'
         param2 = omitted for 'constant', high value of density for 'uniform', sigma value for 'gaussian'
       *breakage_index* values = A minsize
         A = maximum achievable t10 in a single breakage event
         minsize = minimum size of generated fragments (fraction of parent particle size)
       *tn_family* values = n frac1 (frac2 ...)
         n = number of size distribution curves tn to use
         frac = tn family curve to use
       *maxattempt* value = n
         n = number of attempts to pack a fragment into the volume of the parent particle with minimum overlap
       *omit_radius* values = ogenerate orad
         ogenerate = omit fragments *pre* or *post* generation of actual size distribution
         orad = minimum radius below which fragments will be removed from simulation



Examples
""""""""


.. parsed-literal::

   fix pts3 all particletemplate/fragments 321 atom_type 1 density constant 2500 breakage_index 0.1 0.095 tn_family 3 2 5 10

**LIGGGHTS vs. LAMMPS Info:**

This LIGGGHTS command is not available in LAMMPS.

Description
"""""""""""

Define a particle template that is used as input for a
:doc:`fix\_particledistribution\_discrete <fix_particledistribution_discrete>`
command to produce fragments of particles for the discrete fragmentation method (DFM).

You can choose the atom type, density and radius distribution of the particles.
For density, you can choose between 'constant', 'uniform' and 'gaussian' random styles.
The radius distribution is determined by the breakage index *t10* calculated from
the breakage probability *P* of a :doc:`fix\_break\_particle <fix_break_particle>`

.. image:: Eqs/fix_particletemplate_fragments.png
   :align: center

*t10* is the cumulative mass percentage of the fragments which are smaller than 1/10
of the parent particle size and *A* is the maximum achievable *t10* in a single
breakage event. This parameter is uniquely related to other points on a family of size
distribution curves *tn*\ , thus yielding the particle size distribution (PSD).

The *breakage\_index* option defines *A* and the minimum size of fragments created
(specified as fraction of the parent particle size).

The *tn\_family* values specify the tn family curves used to generate the size
distribution of fragments.

The *maxattempt* option determines the number of attempts to pack a fragment
into the volume of the parent particle with a minimum overlap. Note that if
this value is exceeded, large overlaps of fragments may occur.

The *omit\_radius* option allows to neglect fragments below a certain size
to speed up the simulation. This can be done by either subtracting the 
corresponding mass fraction from the parent particle mass (keyword *pre*\ ) or
by generating the size distribution from the given tn family curves and 
subsequently omitting fragments which are smaller than the given radius
(keyword *post*\ ).

**Restart, fix\_modify, output, run start/stop, minimize info:**

Information about the random state in this fix is written to :doc:`binary restart files <restart>`. None of the :doc:`fix\_modify <fix_modify>` options are relevant to this fix. No global scalar or vector or per-atom quantities are stored by this fix for access by various :ref:`output commands <howto_15>`. No parameter of this fix can be used with the *start*\ /\ *stop* keywords of the :doc:`run <run>` command. This fix is not invoked during :doc:`energy minimization <minimize>`.

Restrictions
""""""""""""
 none

Related commands
""""""""""""""""

:doc:`fix\_particletemplate\_sphere <fix_particletemplate_sphere>`,
:doc:`fix\_break\_particle <fix_break_particle>`

**Default:** density = 1.0, atom\_type = 1, tn\_family= 4 2 3 5 10, maxattempt = 200, omit\_radius = 0.0


