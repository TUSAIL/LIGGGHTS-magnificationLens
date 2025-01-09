.. index:: fix deposit

fix deposit command
===================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID deposit N type M seed keyword values ...

* ID, group-ID are documented in :doc:`fix <fix>` command
* deposit = style name of this fix command
* N = # of atoms to insert
* type = atom type to assign to inserted atoms
* M = insert a single particle every M steps
* seed = random # seed (positive integer)
* one or more keyword/value pairs may be appended to args
* keyword = *region* or *id* or *global* or *local* or *near* or *attempt* or *rate* or *vx* or *vy* or *vz* or *units*
  
  .. parsed-literal::
  
       *region* value = region-ID
         region-ID = ID of region to use as insertion volume
       *id* value = *max* or *next*
         max = atom ID for new atom is max ID of all current atoms plus one
         next = atom ID for new atom increments by one for every deposition
       *global* values = lo hi
         lo,hi = put new particle a distance lo-hi above all other particles (distance units)
       *local* values = lo hi delta
         lo,hi = put new particle a distance lo-hi above any nearby particle beneath it (distance units)
         delta = lateral distance within which a neighbor is considered "nearby" (distance units)
       *near* value = R
         R = only insert particle if further than R from existing particles (distance units)
       *attempt* value = Q
         Q = attempt a single insertion up to Q times
       *rate* value = V
         V = z velocity (y in 2d) at which insertion volume moves (velocity units)
       *vx* values = vxlo vxhi
         vxlo,vxhi = range of x velocities for inserted particle (velocity units)
       *vy* values = vylo vyhi
         vylo,vyhi = range of y velocities for inserted particle (velocity units)
       *vz* values = vzlo vzhi
         vzlo,vzhi = range of z velocities for inserted particle (velocity units)
       *target* values = tx ty tz
         tx,ty,tz = location of sputtering target (distance units)
       *units* value = *lattice* or *box*
         lattice = the geometry is defined in lattice units
         box = the geometry is defined in simulation box units



Examples
""""""""


.. parsed-literal::

   fix 3 all deposit 1000 2 100 29494 region myblock local 1.0 1.0 1.0 units box
   fix 2 newatoms deposit 10000 1 500 12345 region disk near 2.0 vz -1.0 -0.8
   fix 4 sputter deposit 1000 2 500 12235 region sphere vz -1.0 -1.0 target 5.0 5.0 0.0 units lattice

Description
"""""""""""

Insert a single particle into the simulation domain every M timesteps
until N particles have been inserted.  This is useful for simulating
the deposition of particles onto a surface.

Inserted particles have the specified atom type and are assigned to
two groups: the default group "all" and the group specified in the fix
deposit command (which can also be "all").

If you are computing temperature values which include inserted
particles, you will want to use the :doc:`compute\_modify <compute_modify>`
dynamic option, which insures the current number of atoms is used as a
normalizing factor each time temperature is computed.

Care must be taken that inserted particles are not too near existing
particles, using the options described below.  When inserting
particles above a surface in a non-periodic box (see the
:doc:`boundary <boundary>` command), the possibility of a particle
escaping the surface and flying upward should be considered, since the
particle may be lost or the box size may grow infinitely large.  A
:doc:`fix wall/reflect <fix_wall_reflect>` command can be used to
prevent this behavior.  Note that if a shrink-wrap boundary is used,
it is OK to insert the new particle outside the box, however the box
will immediately be expanded to include the new particle. When
simulating a sputtering experiment it is probably more realistic
to ignore those atoms using the :doc:`thermo\_modify <thermo_modify>`
command with the *lost ignore* option and a fixed :doc:`boundary <boundary>`.

This command must use the *region* keyword to define an insertion
volume.  The specified region must have been previously defined with a
:doc:`region <region>` command.  It must be defined with side = *in*\ .

Each timestep a particle is to be inserted, its coordinates are chosen
as follows.  A random position within the insertion volume is
generated.  If neither the *global* or *local* keyword is used, that
is the trial position.  If the *global* keyword is used, the random
x,y values are used, but the z position of the new particle is set
above the highest current atom in the simulation by a distance
randomly chosen between lo/hi.  (For a 2d simulation, this is done for
the y position.)  If the *local* keyword is used, the z position is
set a distance between lo/hi above the highest current atom in the
simulation that is "nearby" the chosen x,y position.  In this context,
"nearby" means the lateral distance (in x,y) between the new and old
particles is less than the delta parameter.

Once a trial x,y,z location has been computed, the insertion is only
performed if no current particle in the simulation is within a
distance R of the new particle.  If this test fails, a new random
position within the insertion volume is chosen and another trial is
made.  Up to Q attempts are made.  If an atom is not successfully
deposited, LAMMPS prints a warning message.

The *rate* option moves the insertion volume in the z direction (3d)
or y direction (2d).  This enables particles to be inserted from a
successively higher height over time.  Note that this parameter is
ignored if the *global* or *local* keywords are used, since those
options choose a z-coordinate for insertion independently.

The vx, vy, and vz components of velocity for the inserted particle
are set using the values specified for the *vx*\ , *vy*\ , and *vz*
keywords.  Note that normally, new particles should be a assigned a
negative vertical velocity so that they move towards the surface.

In case the *target* option is used, the velocity vector of the 
inserted particle will be changed in a way so that it would pass
through the specified coordinate. This allows convenient simulation
of a sputtering process.

The *id* keyword determines how an atom ID is assigned to newly
deposited atoms.  For the *max* setting, the IDs of all current atoms
are checked and the new ID is the current maximum value plus one.
This means that if atoms have left the system, the new ID may reflect
this fact.  For the *next* setting, the maximum ID of all atoms is
stored at the time the fix is defined.  Each time a deposited atom is
added, this value is incremented by one and assigned to the new atom.
Thus atom IDs for deposited atoms will be consecutive even if atoms
leave the system over time.

The *units* keyword determines the meaning of the distance units used
for the other deposition parameters.  A *box* value selects standard
distance units as defined by the :doc:`units <units>` command,
e.g. Angstroms for units = real or metal.  A *lattice* value means the
distance units are in lattice spacings.  The :doc:`lattice <lattice>`
command must have been previously used to define the lattice spacing.
Note that the units choice affects all the keyword values that have
units of distance or velocity.

**Restart, fix\_modify, output, run start/stop, minimize info:**

This fix writes the state of the deposition to :doc:`binary restart files <restart>`.  This includes information about how many atoms
have been depositied, the random number generator seed, the next
timestep for deposition, etc.  See the
:doc:`read\_restart <read_restart>` command for info on how to re-specify
a fix in an input script that reads a restart file, so that the
operation of the fix continues in an uninterrupted fashion.

None of the :doc:`fix\_modify <fix_modify>` options are relevant to this
fix.  No global or per-atom quantities are stored by this fix for
access by various :ref:`output commands <howto_15>`.  No
parameter of this fix can be used with the *start/stop* keywords of
the :doc:`run <run>` command.  This fix is not invoked during :doc:`energy minimization <minimize>`.

Restrictions
""""""""""""


The specified insertion region cannot be a "dynamic" region, as
defined by the :doc:`region <region>` command.

Related commands
""""""""""""""""

:doc:`fix pour <fix_pour>`, :doc:`region <region>`

Default
"""""""

The option defaults are id = max, delta = 0.0, near = 0.0, attempt =
10, rate = 0.0, vx = 0.0 0.0, vy = 0.0 0.0, vz = 0.0 0.0, and units =
lattice.


