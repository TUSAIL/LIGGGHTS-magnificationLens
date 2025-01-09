.. index:: fix ave/euler/region

fix ave/euler/region command
============================

fix ave/euler/region/universe command
=====================================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID ave/euler/region nevery N region reg-ID keywords values
   fix ID group-ID ave/euler/region/universe nevery N region reg-ID keywords values ukeywords uvalues

* ID, group-ID are documented in :doc:`fix <fix>` command
* ave/euler/region = style name of this fix command
* nevery = obligatory keyword
* N = calculate average values every this many timesteps (also sending interval in universe version)
* region = obligatory keyword
* reg-ID = ID of region with style mesh/hex defining the grid
* zero or more keyword/value pairs may be appended
* keyword = *basevolume\_region*
  
  .. parsed-literal::
  
       *basevolume_region* value = region-ID
         region-ID = correct grid cell volume based on this region

* one or more ukeyword/uvalue pairs must be appended for the universe version of this command
* ukeywords = *send\_to\_partition* (obligatory) or *sync*
  
  .. parsed-literal::
  
       *send_to_partition* value = partition
         partition = partition to send data to in multi-partition simulations
       *sync* value = mode
         mode = *yes* to use MPI_Ssend, *no* to use MPI_Bsend for communication between partitions



Examples
""""""""


.. parsed-literal::

   fix 1 all ave/euler/region nevery 10 region ave_reg
   fix 2 all ave/euler/region/universe nevery 10 region ave_reg send_to_partition 2 sync yes

Description
"""""""""""

Calculate cell-based averages of velocity, radius, volume fraction,
and pressure (-1/3 \* trace of the stress tensor) every few timesteps,
as specified by the *nevery* keyword. The cells are taken from the
specified region.

Note that velocity is favre (mass) averaged, whereas radius is arithmetically
averaged. To calculate the stress, this command internally uses a
:doc:`compute stress/atom <compute_stress_atom>` . It includes the convective
term correctly for granular particles with non-zero average velocity
(which is not included  in :doc:`compute stress/atom <compute_stress_atom>`).
However, it does not include bond, angle, diahedral or kspace contributions
so that the stress tensor finally reads

.. image:: Eqs/stress_tensor_granular.png
   :align: center

where vave is the (cell-based) average velocity.
The first term is a kinetic energy contribution for atom *I*\ .  The
second term is a pairwise energy contribution where *n* loops over the
*Np* neighbors of atom *I*\ , *r1* and *r2* are the positions of the 2
atoms in the pairwise interaction, and *F1* and *F2* are the forces on
the 2 atoms resulting from the pairwise interaction.

The *basevolume\_region* option allows to specify a region that
represents the volume which can theoretically be filled with
particles. This will then be used to correct the basis of the averaging
volume for each cell in the grid. For example, if you use a cylindrical
wall, it makes sense to use an identical cylindrical region for 
the *basevolume\_region* option, and the command will correctly
calculate the volume fraction in the near-wall cells.
the calculation of overlap between grid cells and the region
is done using a Monte-Carlo approach.

If LIGGGHTS is invoked in multi-partition mode (cf. :ref:`Command-line options <start_7>`),
where each partition represents a separate coarse-graining level of the multi-level
coarse-grain model, the universe version of this command needs to be used to
provide input data for a fix of style *forcecontrol/region/universe* on the
coupled partition.
The coupled partition must be specified via the *send\_to\_partition* option.
Furthermore, in this mode the *nevery* option also specifies the sending interval.


----------


**Restart, fix\_modify, output, run start/stop, minimize info:**

No information about this fix is written to :doc:`binary restart files <restart>`.  None of the :doc:`fix\_modify <fix_modify>` options
are relevant to this fix.

This fix computes the above-mentioned quantities for output via a
:doc:`dump euler/vtk <dump>` command.  The values can
only be accessed on timesteps that are multiples of *nevery* since that
is when calculations are performed.

No parameter of this fix can be used with the *start/stop* keywords of
the :doc:`run <run>` command.  This fix is not invoked during :doc:`energy minimization <minimize>`.

Restrictions
""""""""""""


Volume fractions and stresses are calculated based on the specified
grid, so volume fractions and stresses near walls that are not
aligned with the grid will be incorrect.

Related commands
""""""""""""""""

:doc:`compute <compute>`, :doc:`compute stress/atom <compute_stress_atom>`,
:doc:`fix ave/atom <fix_ave_atom>`, :doc:`fix ave/euler <fix_ave_euler>`,
:doc:`fix ave/histo <fix_ave_histo>`, :doc:`fix ave/time <fix_ave_time>`,
:doc:`fix ave/spatial <fix_ave_spatial>`, :doc:`partition <partition>`

**Default:** none


