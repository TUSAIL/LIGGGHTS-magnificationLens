.. index:: fix massflow/mesh/face

fix massflow/mesh/face command
==============================

fix massflow/mesh/face/universe command
=======================================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID massflow/mesh mesh mesh-ID vec_side vx vy vz keywords values
   fix ID group-ID massflow/mesh/universe mesh mesh-ID vec_side vx vy vz keywords values ukeywords uvalues

* ID, group-ID are documented in :doc:`fix <fix>` command
* massflow/mesh/face = style name of this fix command
* mesh = obligatory keyword
* mesh-ID = ID of a :doc:`fix mesh/surface <fix_mesh_surface>` command
* zero or more keyword/value pairs may be appended to args
* keywords = *check\_property* or *count* or *point\_at\_outlet* or *append* or *file* or *screen* or *delete\_atoms*
  
  .. parsed-literal::
  
       *check_property* property value
         property = name of atom property to check
         value = reference atom property value to check against
       *count* value = *once* or *multiple*
         once = count particles only once
         multiple = allow particles to be counted multiple times
       *point_at_outlet*  pointX pointY pointZ
         pointX pointY pointZ = coordinates of point on the outlet side of the surface
       *inside_out*
         use this in connection with *point_at_outlet* to flip direction particle counting
       *file* value = filename
       *append* value = filename
        filename = name of the file to print diameter, position and velocity values of the particles
       *screen* value = *yes* or *no*
       *delete_atoms* value = *yes* or *no*
         yes = to remove the particles that pass through the mesh surface
       *cg* value = cg
         cg = coarse grain ratio of measured particles (N/A to universe version)
       *temperature* value = *yes* or *no*
         yes = to measure the temperature of the particles
       *chemistry* value = *yes* or *no*
         yes = to measure the reduction state of the particles

* two ukeyword/uvalue pairs must be appended for the universe version of this command
* ukeywords = *send\_to\_partition* and *couple\_every*
  
  .. parsed-literal::
  
       *send_to_partition* value = partition
         partition = partition to send data to in multi-partition simulations
       *couple_every* value = interval
         interval = time interval for sending data



Examples
""""""""


.. parsed-literal::

   fix massflowcg2t all massflow/mesh/face mesh surfacet count once check_property i_cglevel 2 cg 2 inside_out

   fix massflowcg2b all massflow/mesh/face mesh surfaceb count multiple check_property i_cglevel 2 cg 2 file post/massflowprop.txt

**LIGGGHTS vs. LAMMPS Info:**

This LIGGGHTS command is not available in LAMMPS.

Description
"""""""""""

Fix massflow/mesh/face tracks how many particles penetrate through each face of
a mesh surface, as defined by a :doc:`fix mesh/surface <fix_mesh_surface>` command.
It counts the total number of particles and the associated mass. It calculates the
averaged velocity of the crossing particles and stores their size distribution as
well as their atom types. Only particles part of *group* are eligible for counting.
If *check\_property* is specified, only particles with the given property value are
considered. *check\_property* may refer to a :doc:`fix poperty/atom <fix_property>`
or a fix property/atom/lammps.

Particles are counted if they cross from the inner side of the mesh to the outer
side of the mesh. The outer side can be defined by the winding order of the mesh
vertices or by specifying a point at the outlet side of the mesh (keyword *point\_at\_outlet*).

The following restriction applies in case *point\_at\_outlet* is used: the *count* 
value has to be set to once.

The keyword *point\_at\_outlet* is especially useful in case a cylindrically-shaped
surface is used. The *point\_at\_outlet* value should be on the cylinder axis in
this case. If you like to track particles moving away from the cylinder axis,
specify the *point\_at\_outlet* on the axis, and use the keyword 
*inside\_out* to flip the direction.

If *count* = once, then each particle is only counted once, for *count* = multiple
a particle contributes to the statistics each time it crosses the mesh face.
This can happen e.g. in the case of periodic boundary conditions or in re-circulating
flow conditions.

The timestep of the crossing, the ID of the crossed face, the atom ID, as well as
the diameter, position and velocity of the particles can be written into a file
using the *file* keyword and specifying a filename.

If the *screen* keyword is used, output by this fix to the screen and
logfile can be turned on or off as desired.

If the *delete\_atoms* keyword is used then the particles passing through the mesh 
surface are deleted at the next re-neighboring step.

If LIGGGHTS is invoked in multi-partition mode (cf. :ref:`Command-line options <start_7>`),
where each partition represents a separate coarse-graining level of the multi-level
coarse-grain model, the universe version of this command needs to be used to
provide input data for a fix of style *insert/pack/face/universe* on the
coupled partition.
The coupled partition must be specified via the *send\_to\_partition* option.
Furthermore, in this mode the *couple\_every* option specifies the sending interval.

**Restart, fix\_modify, output, run start/stop, minimize info:**

Information about this fix is written to :doc:`binary restart files <restart>` .

This fix computes a per-atom vector (the marker) which can be accessed by
various :ref:`output commands <howto_15>`. The per-atom vector 
(i.e., the marker) can be accessed by dumps by using "f\_massflowface\_ID".
This fix also computes a global vector of length 10. This vector can be 
accessed via "f\_ID", where ID is the fix id. The first vector component 
is equal to the total mass which has crossed the mesh surface, the second vector 
component indicates the (resolved) particle count. The third vector component 
is equal to the total mass which has crossed the mesh surface since the last output 
divided by the time since the last output (i.e., the mass flow rate), the fourth vector 
component indicates the (resolved) particle count since the last output divided by the time
since the last output (i.e., the number rate of particles). The fifth and sixth vector
components are the deleted mass and the number of deleted particles. The seventh component
vector component indicates the (resolved) particle count since the last output.
The last three vector components are the favre-averaged velocity components.

This vector can also be accessed by various :ref:`output commands <howto_15>`.

Restrictions
""""""""""""


The mesh surface must provide the element property 'face\_id', e.g. by loading it from
a VTK file using the *cell\_data* option of the :doc:`fix mesh/surface <fix_mesh_surface>`
command. All triangles with the same ID are considered to form a face.

Related commands
""""""""""""""""

:doc:`compute nparticles/tracer/region <compute_nparticles_tracer_region>`,
:doc:`fix massflow/mesh <fix_massflow_mesh>`, :doc:`partition <partition>`

Default
"""""""

*count* = multiple, *inside\_out* = false, *delete\_atoms* = false, *cg* = 1


