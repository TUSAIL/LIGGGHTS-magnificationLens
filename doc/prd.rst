.. index:: prd

prd command
===========

Syntax
""""""


.. parsed-literal::

   prd N t_event n_dephase t_dephase t_correlate compute-ID seed keyword value ...

* N = # of timesteps to run (not including dephasing/quenching)
* t\_event = timestep interval between event checks
* n\_dephase = number of velocity randomizations to perform in each dephase run
* t\_dephase = number of timesteps to run dynamics after each velocity randomization during dephase
* t\_correlate = number of timesteps within which 2 consecutive events are considered to be correlated
* compute-ID = ID of the compute used for event detection
* random\_seed = random # seed (positive integer)
* zero or more keyword/value pairs may be appended
* keyword = *min* or *temp* or *vel*
  
  .. parsed-literal::
  
       *min* values = etol ftol maxiter maxeval
         etol = stopping tolerance for energy, used in quenching
         ftol = stopping tolerance for force, used in quenching
         maxiter = max iterations of minimize, used in quenching
         maxeval = max number of force/energy evaluations, used in quenching
       *temp* value = Tdephase
         Tdephase = target temperature for velocity randomization, used in dephasing
       *vel* values = loop dist
         loop = *all* or *local* or *geom*\ , used in dephasing
         dist = *uniform* or *gaussian*\ , used in dephasing



Examples
""""""""


.. parsed-literal::

   prd 5000 100 10 10 100 1 54982
   prd 5000 100 10 10 100 1 54982 min 0.1 0.1 100 200

Description
"""""""""""

Run a parallel replica dynamics (PRD) simulation using multiple
replicas of a system.  One or more replicas can be used.

PRD is described in :ref:`this paper <Voter>` by Art Voter.  It is a method
for performing accelerated dynamics that is suitable for
infrequent-event systems that obey first-order kinetics.  A good
overview of accelerated dynamics methods for such systems in given in
:ref:`this review paper <Voter2>` from the same group.  To quote from the
paper: "The dynamical evolution is characterized by vibrational
excursions within a potential basin, punctuated by occasional
transitions between basins."  The transition probability is
characterized by p(t) = k\*exp(-kt) where k is the rate constant.
Running multiple replicas gives an effective enhancement in the
timescale spanned by the multiple simulations, while waiting for an
event to occur.

Each replica runs on a partition of one or more processors.  Processor
partitions are defined at run-time using the -partition command-line
switch; see :ref:`Section\_start 6 <start_7>` of the
manual.  Note that if you have MPI installed, you can run a
multi-replica simulation with more replicas (partitions) than you have
physical processors, e.g you can run a 10-replica simulation on one or
two processors.  For PRD, this makes little sense, since this offers
no effective parallel speed-up in searching for infrequent events. See
:ref:`Section\_howto 5 <howto_5>` of the manual for further
discussion.

When a PRD simulation is performed, it is assumed that each replica is
running the same model, though LAMMPS does not check for this.
I.e. the simulation domain, the number of atoms, the interaction
potentials, etc should be the same for every replica.

A PRD run has several stages, which are repeated each time an "event"
occurs in one of the replicas, as defined below.  The logic for a PRD
run is as follows:


.. parsed-literal::

   while (time remains):
     dephase for n_dephase\*t_dephase steps
     until (event occurs on some replica):
       run dynamics for t_event steps
       quench
       check for uncorrelated event on any replica
     until (no correlated event occurs):
       run dynamics for t_correlate steps
       quench
       check for correlated event on this replica
     event replica shares state with all replicas

Before this loop begins, the state of the system on replica 0 is
shared with all replicas, so that all replicas begin from the same
initial state. The first potential energy basin is identified by
quenching (an energy minimization, see below) the initial state and
storing the resulting coordinates for reference.

In the first stage, dephasing is performed by each replica
independently to eliminate correlations between replicas.  This is
done by choosing a random set of velocities, based on the
*random\_seed* that is specified, and running *t\_dephase* timesteps of
dynamics.  This is repeated *n\_dephase* times.  If the *temp* keyword
is not specified, the target temperature for velocity randomization
for each replica is the current temperature of that replica.
Otherwise, it is the specified *Tdephase* temperature.  The style of
velocity randomization is controlled using the keyword *vel* with
arguments that have the same meaning as their counterparts in the
:doc:`velocity <velocity>` command.

In the second stage, each replica runs dynamics continuously, stopping
every *t\_event* steps to check if a transition event has occurred.
This check is performed by quenching the system and comparing the
resulting atom coordinates to the coordinates from the previous basin.
The first time through the PRD loop, the "previous basin" is the set
of quenched coordinates from the initial state of the system.

A quench is an energy minimization and is performed by whichever
algorithm has been defined by the :doc:`min\_style <min_style>` command.
Minimization parameters may be set via the
:doc:`min\_modify <min_modify>` command and by the *min* keyword of the
PRD command.  The latter are the settings that would be used with the
:doc:`minimize <minimize>` command.  Note that typically, you do not
need to perform a highly-converged minimization to detect a transition
event.

The event check is performed by a compute with the specified
*compute-ID*\ .  Currently there is only one compute that works with the
PRD command, which is the :doc:`compute event/displace <compute_event_displace>` command.  Other
event-checking computes may be added.  :doc:`Compute event/displace <compute_event_displace>` checks whether any atom in
the compute group has moved further than a specified threshold
distance.  If so, an "event" has occurred.

In the third stage, the replica on which the event occurred (event
replica) continues to run dynamics to search for correlated events.
This is done by running dynamics for *t\_correlate* steps, quenching
every *t\_event* steps, and checking if another event has occurred.
The first time no correlated event occurs, the final state of the
event replica is shared with all replicas, the new basin reference
coordinates are updated with the quenched state, and the outer loop
begins again. While the replica event is searching for correlated
events, all the other replicas also run dynamics and event checking
with the same schedule, but the final states are always overwritten by
the state of the event replica.


----------


Four kinds of output can be generated during a PRD run: event
statistics, thermodynamic output by each replica, dump files, and
restart files.

When running with multiple partitions (each of which is a replica in
this case), the print-out to the screen and master log.lammps file is
limited to event statistics.  Note that if a PRD run is performed on
only a single replica then the event statistics will be intermixed
with the usual thermodynamic output discussed below.

The quantities printed each time an event occurs are the timestep,
CPU time, clock, event number, a correlation flag, 
the number of coincident events, and the replica number of the chosen event.

The timestep is the usual LAMMPS timestep, except that time does not
advance during dephasing or quenches, but only during dynamics.  Note
that are two kinds of dynamics in the PRD loop listed above.  The
first is when all replicas are performing independent dynamics.  The
second is when correlated events are being searched for and only one
replica is running dynamics.

The CPU time is the total processor time since the start of the PRD
run.

The clock is the same as the timestep except that it advances by M
steps every timestep during the first kind of dynamics when the M
replicas are running independently.  The clock represents the real
time that effectively elapses during a PRD simulation of *N* steps on
M replicas.  If most of the PRD run is spent in the second stage of
the loop above, searching for infrequent events, then the clock will
advance nearly N\*M steps.  Note the clock time between events will be
drawn from p(t).

The event number is a counter that increments with each event, whether
it is uncorrelated or correlated.

The correlation flag will be 0 when an uncorrelated event occurs
during the second stage of the loop listed above, i.e. when all
replicas are running independently.  The correlation flag will be 1
when a correlated event occurs during the third stage of the loop
listed above, i.e. when only one replica is running dynamics.

When more than one replica detects an event at the end of the second
stage, then one of them is chosen at random. The number of coincident 
events is the number of replicas that detected an event. Normally, we
expect this value to be 1. If it is often greater than 1, then either
the number of replicas is too large, or *t\_event* is too large.

The replica number is the ID of the replica (from 0 to M-1) that
found the event.


----------


When running on multiple partitions, LAMMPS produces additional log
files for each partition, e.g. log.lammps.0, log.lammps.1, etc.  For
the PRD command, these contain the thermodynamic output for each
replica.  You will see short runs and minimizations corresponding to
the dynamics and quench operations of the loop listed above.  The
timestep will be reset appropriately depending on whether the
operation advances time or not.

After the PRD command completes, timing statistics for the PRD run are
printed in each replica's log file, giving a breakdown of how much CPU
time was spent in each stage (dephasing, dynamics, quenching, etc).


----------


Any :doc:`dump files <dump>` defined in the input script, will be
written to during a PRD run at timesteps corresponding to both
uncorrelated and correlated events.  This means the requested dump
frequency in the :doc:`dump <dump>` command is ignored.  There will be
one dump file (per dump command) created for all partitions.

The atom coordinates of the dump snapshot are those of the minimum
energy configuration resulting from quenching following a transition
event.  The timesteps written into the dump files correspond to the
timestep at which the event occurred and NOT the clock.  A dump
snapshot corresponding to the initial minimum state used for event
detection is written to the dump file at the beginning of each PRD
run.


----------


If the :doc:`restart <restart>` command is used, a single restart file
for all the partitions is generated, which allows a PRD run to be
continued by a new input script in the usual manner.

The restart file is generated at the end of the loop listed above.  If
no correlated events are found, this means it contains a snapshot of
the system at time T + *t\_correlate*, where T is the time at which the
uncorrelated event occurred.  If correlated events were found, then it
contains a snapshot of the system at time T + *t\_correlate*, where T
is the time of the last correlated event.

The restart frequency specified in the :doc:`restart <restart>` command
is interpreted differently when performing a PRD run.  It does not
mean the timestep interval between restart files.  Instead it means an
event interval for uncorrelated events.  Thus a frequency of 1 means
write a restart file every time an uncorrelated event occurs.  A
frequency of 10 means write a restart file every 10th uncorrelated
event.

When an input script reads a restart file from a previous PRD run, the
new script can be run on a different number of replicas or processors.
However, it is assumed that *t\_correlate* in the new PRD command is
the same as it was previously.  If not, the calculation of the "clock"
value for the first event in the new run will be slightly off.


----------


Restrictions
""""""""""""


This command can only be used if LAMMPS was built with the REPLICA
package.  See the :ref:`Making LAMMPS <start_3>` section
for more info on packages.

*N* and *t\_correlate* settings must be integer multiples of
*t\_event*.

Runs restarted from restart file written during a PRD run will not
produce identical results due to changes in the random numbers used
for dephasing.

This command cannot be used when any fixes are defined that keep track
of elapsed time to perform time-dependent operations.  Examples
include the "ave" fixes such as :doc:`fix ave/spatial <fix_ave_spatial>`.  Also :doc:`fix dt/reset <fix_dt_reset>` and :doc:`fix deposit <fix_deposit>`.

Related commands
""""""""""""""""

:doc:`compute event/displace <compute_event_displace>`,
:doc:`min\_modify <min_modify>`, :doc:`min\_style <min_style>`,
:doc:`run\_style <run_style>`, :doc:`minimize <minimize>`,
:doc:`velocity <velocity>`, :doc:`temper <temper>`, :doc:`neb <neb>`,
:doc:`tad <tad>`

Default
"""""""

The option defaults are *min* = 0.1 0.1 40 50, no *temp* setting, and
*vel* = *geom* *gaussian*\ .


----------


.. _Voter:



**(Voter)** Voter, Phys Rev B, 57, 13985 (1998).

.. _Voter2:



**(Voter2)** Voter, Montalenti, Germann, Annual Review of Materials
Research 32, 321 (2002).


