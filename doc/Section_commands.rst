Commands
========

This section describes how a LAMMPS input script is formatted and the
input script commands used to define a LAMMPS simulation.

| 3.1 :ref:`LAMMPS input script <cmd_1>`
| 3.2 :ref:`Parsing rules <cmd_2>`
| 3.3 :ref:`Input script structure <cmd_3>`
| 3.4 :ref:`Commands listed by category <cmd_4>`
| 3.5 :ref:`Commands listed alphabetically <cmd_5>`
|





.. _cmd\_1:

LAMMPS input script
-------------------

LAMMPS executes by reading commands from a input script (text file),
one line at a time.  When the input script ends, LAMMPS exits.  Each
command causes LAMMPS to take some action.  It may set an internal
variable, read in a file, or run a simulation.  Most commands have
default settings, which means you only need to use the command if you
wish to change the default.

In many cases, the ordering of commands in an input script is not
important.  However the following rules apply:

(1) LAMMPS does not read your entire input script and then perform a
simulation with all the settings.  Rather, the input script is read
one line at a time and each command takes effect when it is read.
Thus this sequence of commands:


.. parsed-literal::

   timestep 0.5
   run      100
   run      100

does something different than this sequence:


.. parsed-literal::

   run      100
   timestep 0.5
   run      100

In the first case, the specified timestep (0.5 fmsec) is used for two
simulations of 100 timesteps each.  In the 2nd case, the default
timestep (1.0 fmsec) is used for the 1st 100 step simulation and a 0.5
fmsec timestep is used for the 2nd one.

(2) Some commands are only valid when they follow other commands.  For
example you cannot set the temperature of a group of atoms until atoms
have been defined and a group command is used to define which atoms
belong to the group.

(3) Sometimes command B will use values that can be set by command A.
This means command A must precede command B in the input script if it
is to have the desired effect.  For example, the
:doc:`read\_data <read_data>` command initializes the system by setting
up the simulation box and assigning atoms to processors.  If default
values are not desired, the :doc:`processors <processors>` and
:doc:`boundary <boundary>` commands need to be used before read\_data to
tell LAMMPS how to map processors to the simulation box.

Many input script errors are detected by LAMMPS and an ERROR or
WARNING message is printed.  :doc:`This section <Section_errors>` gives
more information on what errors mean.  The documentation for each
command lists restrictions on how the command can be used.


----------


.. _cmd\_2:

Parsing rules
-------------

Each non-blank line in the input script is treated as a command.
LAMMPS commands are case sensitive.  Command names are lower-case, as
are specified command arguments.  Upper case letters may be used in
file names or user-chosen ID strings.

Here is how each line in the input script is parsed by LAMMPS:

(1) If the last printable character on the line is a "&" character
(with no surrounding quotes), the command is assumed to continue on
the next line.  The next line is concatenated to the previous line by
removing the "&" character and newline.  This allows long commands to
be continued across two or more lines.

(2) All characters from the first "#" character onward are treated as
comment and discarded.  See an exception in (6).  Note that a
comment after a trailing "&" character will prevent the command from
continuing on the next line.  Also note that for multi-line commands a
single leading "#" will comment out the entire command.

(3) The line is searched repeatedly for $ characters, which indicate
variables that are replaced with a text string.  See an exception in
(6).

If the $ is followed by curly brackets, then the variable name is the
text inside the curly brackets.  If no curly brackets follow the $,
then the variable name is the single character immediately following
the $.  Thus ${myTemp} and $x refer to variable names "myTemp" and
"x".

If the $ is followed by parenthesis, then the text inside the
parenthesis is treated as an "immediate" variable and evaluated as an
:doc:`equal-style variable <variable>`.  This is a way to use numeric
formulas in an input script without having to assign them to variable
names.  For example, these 3 input script lines:


.. parsed-literal::

   variable X equal (xlo+xhi)/2+sqrt(v_area)
   region 1 block $X 2 INF INF EDGE EDGE
   variable X delete

can be replaced by


.. parsed-literal::

   region 1 block $((xlo+xhi)/2+sqrt(v_area)) 2 INF INF EDGE EDGE

so that you do not have to define (or discard) a temporary variable X.

Note that neither the curly-bracket or immediate form of variables can
contain nested $ characters for other variables to substitute for.
Thus you cannot do this:


.. parsed-literal::

   variable        a equal 2
   variable        b2 equal 4
   print           "B2 = ${b$a}"

Nor can you specify this $($x-1.0) for an immediate variable, but
you could use $(v\_x-1.0), since the latter is valid syntax for an
:doc:`equal-style variable <variable>`.

See the :doc:`variable <variable>` command for more details of how
strings are assigned to variables and evaluated, and how they can be
used in input script commands.

(4) The line is broken into "words" separated by whitespace (tabs,
spaces).  Note that words can thus contain letters, digits,
underscores, or punctuation characters.

(5) The first word is the command name.  All successive words in the
line are arguments.

(6) If you want text with spaces to be treated as a single argument,
it can be enclosed in either double or single quotes.  E.g.


.. parsed-literal::

   print "Volume = $v"
   print 'Volume = $v'
   if "$\ *steps* > 1000" then quit

The quotes are removed when the single argument is stored internally.
See the :doc:`dump modify format <dump_modify>` or :doc:`print <print>` or
:doc:`if <if>` commands for examples.  A "#" or "$" character that is
between quotes will not be treated as a comment indicator in (2) or
substituted for as a variable in (3).

.. warning::

   If the argument is itself a command that requires a
   quoted argument (e.g. using a :doc:`print <print>` command as part of an
   :doc:`if <if>` or :doc:`run every <run>` command), then the double and
   single quotes can be nested in the usual manner.  See the doc pages
   for those commands for examples.  Only one of level of nesting is
   allowed, but that should be sufficient for most use cases.


----------


.. _cmd\_3:

Input script structure
-----------------------------------

This section describes the structure of a typical LAMMPS input script.
The "examples" directory in the LAMMPS distribution contains many
sample input scripts; the corresponding problems are discussed in
:doc:`Section\_example <Section_example>`, and animated on the `LAMMPS WWW Site <lws_>`_.

A LAMMPS input script typically has 4 parts:

1. Initialization
2. Atom definition
3. Settings
4. Run a simulation

The last 2 parts can be repeated as many times as desired.  I.e. run a
simulation, change some settings, run some more, etc.  Each of the 4
parts is now described in more detail.  Remember that almost all the
commands need only be used if a non-default value is desired.

(1) Initialization

Set parameters that need to be defined before atoms are created or
read-in from a file.

The relevant commands are :doc:`units <units>`,
:doc:`dimension <dimension>`, :doc:`newton <newton>`,
:doc:`processors <processors>`, :doc:`boundary <boundary>`,
:doc:`atom\_style <atom_style>`, :doc:`atom\_modify <atom_modify>`.

If force-field parameters appear in the files that will be read, these
commands tell LAMMPS what kinds of force fields are being used:
:doc:`pair\_style <pair_style>`, :doc:`bond\_style <bond_style>`,
:doc:`angle\_style <angle_style>`, :doc:`dihedral\_style <dihedral_style>`,
:doc:`improper\_style <improper_style>`.

(2) Atom definition

There are 3 ways to define atoms in LAMMPS.  Read them in from a data
or restart file via the :doc:`read\_data <read_data>` or
:doc:`read\_restart <read_restart>` commands.  These files can contain
molecular topology information.  Or create atoms on a lattice (with no
molecular topology), using these commands: :doc:`lattice <lattice>`,
:doc:`region <region>`, :doc:`create\_box <create_box>`,
:doc:`create\_atoms <create_atoms>`.  The entire set of atoms can be
duplicated to make a larger simulation using the
:doc:`replicate <replicate>` command.

(3) Settings

Once atoms and molecular topology are defined, a variety of settings
can be specified: force field coefficients, simulation parameters,
output options, etc.

Force field coefficients are set by these commands (they can also be
set in the read-in files): :doc:`pair\_coeff <pair_coeff>`,
:doc:`bond\_coeff <bond_coeff>`, :doc:`angle\_coeff <angle_coeff>`,
:doc:`dihedral\_coeff <dihedral_coeff>`,
:doc:`improper\_coeff <improper_coeff>`,
:doc:`kspace\_style <kspace_style>`, :doc:`dielectric <dielectric>`,
:doc:`special\_bonds <special_bonds>`.

Various simulation parameters are set by these commands:
:doc:`neighbor <neighbor>`, :doc:`neigh\_modify <neigh_modify>`,
:doc:`group <group>`, :doc:`timestep <timestep>`,
:doc:`reset\_timestep <reset_timestep>`, :doc:`run\_style <run_style>`,
:doc:`min\_style <min_style>`, :doc:`min\_modify <min_modify>`.

Fixes impose a variety of boundary conditions, time integration, and
diagnostic options.  The :doc:`fix <fix>` command comes in many flavors.

Various computations can be specified for execution during a
simulation using the :doc:`compute <compute>`,
:doc:`compute\_modify <compute_modify>`, and :doc:`variable <variable>`
commands.

Output options are set by the :doc:`thermo <thermo>`, :doc:`dump <dump>`,
and :doc:`restart <restart>` commands.

(4) Run a simulation

A molecular dynamics simulation is run using the :doc:`run <run>`
command.  Energy minimization (molecular statics) is performed using
the :doc:`minimize <minimize>` command.  A parallel tempering
(replica-exchange) simulation can be run using the
:doc:`temper <temper>` command.


----------


.. _cmd\_4:

Commands listed by category
---------------------------

This section lists all LAMMPS commands, grouped by category.  The
:ref:`next section <cmd_5>` lists the same commands alphabetically.  Note
that some style options for some commands are part of specific LAMMPS
packages, which means they cannot be used unless the package was
included when LAMMPS was built.  Not all packages are included in a
default LAMMPS build.  These dependencies are listed as Restrictions
in the command's documentation.

Initialization:

:doc:`atom\_modify <atom_modify>`,
:doc:`atom\_style <atom_style>`,
:doc:`boundary <boundary>`,
:doc:`dimension <dimension>`,
:doc:`newton <newton>`,
:doc:`processors <processors>`,
:doc:`region <region>`,
:doc:`units <units>`

Atom definition:

:doc:`create\_atoms <create_atoms>`,
:doc:`create\_box <create_box>`,
:doc:`lattice <lattice>`,
:doc:`read\_data <read_data>`,
:doc:`read\_dump <read_dump>`,
:doc:`read\_restart <read_restart>`,
:doc:`replicate <replicate>`

Force fields:

:doc:`angle\_coeff <angle_coeff>`,
:doc:`angle\_style <angle_style>`,
:doc:`bond\_coeff <bond_coeff>`,
:doc:`bond\_style <bond_style>`,
:doc:`dielectric <dielectric>`,
:doc:`dihedral\_coeff <dihedral_coeff>`,
:doc:`dihedral\_style <dihedral_style>`,
:doc:`improper\_coeff <improper_coeff>`,
:doc:`improper\_style <improper_style>`,
:doc:`kspace\_modify <kspace_modify>`,
:doc:`kspace\_style <kspace_style>`,
:doc:`pair\_coeff <pair_coeff>`,
:doc:`pair\_modify <pair_modify>`,
:doc:`pair\_style <pair_style>`,
:doc:`pair\_write <pair_write>`,
:doc:`special\_bonds <special_bonds>`

Settings:

:doc:`communicate <communicate>`,
:doc:`group <group>`,
:doc:`mass <mass>`,
:doc:`min\_modify <min_modify>`,
:doc:`min\_style <min_style>`,
:doc:`neigh\_modify <neigh_modify>`,
:doc:`neighbor <neighbor>`,
:doc:`reset\_timestep <reset_timestep>`,
:doc:`run\_style <run_style>`,
:doc:`set <set>`,
:doc:`timestep <timestep>`,
:doc:`velocity <velocity>`

Fixes:

:doc:`fix <fix>`,
:doc:`fix\_modify <fix_modify>`,
:doc:`unfix <unfix>`

Computes:

:doc:`compute <compute>`,
:doc:`compute\_modify <compute_modify>`,
:doc:`uncompute <uncompute>`

Output:

:doc:`dump <dump>`,
:doc:`dump image <dump_image>`,
:doc:`dump movie <dump_image>`,
:doc:`dump\_modify <dump_modify>`,
:doc:`restart <restart>`,
:doc:`thermo <thermo>`,
:doc:`thermo\_modify <thermo_modify>`,
:doc:`thermo\_style <thermo_style>`,
:doc:`undump <undump>`,
:doc:`write\_data <write_data>`,
:doc:`write\_dump <write_dump>`,
:doc:`write\_restart <write_restart>`

Actions:

:doc:`delete\_atoms <delete_atoms>`,
:doc:`delete\_bonds <delete_bonds>`,
:doc:`displace\_atoms <displace_atoms>`,
:doc:`change\_box <change_box>`,
:doc:`minimize <minimize>`,
:doc:`neb <neb>`,
:doc:`prd <prd>`,
:doc:`rerun <rerun>`,
:doc:`run <run>`,
:doc:`temper <temper>`

Miscellaneous:

:doc:`clear <clear>`,
:doc:`echo <echo>`,
:doc:`extract\_surface <extract_surface>`,
:doc:`extrude\_surface <extrude_surface>`,
:doc:`if <if>`,
:doc:`include <include>`,
:doc:`jump <jump>`,
:doc:`label <label>`,
:doc:`log <log>`,
:doc:`next <next>`,
:doc:`print <print>`,
:doc:`shell <shell>`,
:doc:`variable <variable>`


----------


.. _cmd\_5:

.. _comm:

Individual commands
-------------------------------------------

This section lists all LAMMPS and LIGGGHTS commands alphabetically, with a separate
listing below of styles within certain commands. Note
that some style options for some commands are part of specific LAMMPS
packages, which means they cannot be used unless the package was
included when LAMMPS was built.  Not all packages are included in a
default LAMMPS build.  These dependencies are listed as Restrictions
in the command's documentation.

.. list-table::
   :widths: auto

   * - :doc:`angle\_coeff <angle_coeff>`
     - :doc:`angle\_style <angle_style>`
     - :doc:`atom\_modify <atom_modify>`
     - :doc:`atom\_style <atom_style>`
     - :doc:`balance <balance>`
   * - :doc:`bond\_coeff <bond_coeff>`
     - :doc:`bond\_style <bond_style>`
     - :doc:`boundary <boundary>`
     - :doc:`box <box>`
     - :doc:`change\_box <change_box>`
   * - :doc:`clear <clear>`
     - :doc:`coarsegraining <coarsegraining>`
     - :doc:`communicate <communicate>`
     - :doc:`compute <compute>`
     - :doc:`compute\_modify <compute_modify>`
   * - :doc:`create\_atoms <create_atoms>`
     - :doc:`create\_box <create_box>`
     - :doc:`create\_multisphere\_clump <create_multisphere_clump>`
     - :doc:`delete\_atoms <delete_atoms>`
     - :doc:`delete\_bonds <delete_bonds>`
   * - :doc:`dielectric <dielectric>`
     - :doc:`dihedral\_coeff <dihedral_coeff>`
     - :doc:`dihedral\_style <dihedral_style>`
     - :doc:`dimension <dimension>`
     - :doc:`displace\_atoms <displace_atoms>`
   * - :doc:`dump <dump>`
     - :doc:`dump\_modify <dump_modify>`
     - :doc:`echo <echo>`
     - :doc:`extract\_surface <extract_surface>`
     - :doc:`extrude\_surface <extrude_surface>`
   * - :doc:`fix <fix>`
     - :doc:`fix\_modify <fix_modify>`
     - :doc:`group <group>`
     - :doc:`group2ndx <group2ndx>`
     - :doc:`if <if>`
   * - :doc:`improper\_coeff <improper_coeff>`
     - :doc:`improper\_style <improper_style>`
     - :doc:`include <include>`
     - :doc:`jump <jump>`
     - :doc:`kspace\_modify <kspace_modify>`
   * - :doc:`kspace\_style <kspace_style>`
     - :doc:`label <label>`
     - :doc:`lattice <lattice>`
     - :doc:`log <log>`
     - :doc:`mass <mass>`
   * - :doc:`min\_modify <min_modify>`
     - :doc:`min\_style <min_style>`
     - :doc:`minimize <minimize>`
     - :doc:`modify\_timing <modify_timing>`
     - :doc:`neb <neb>`
   * - :doc:`neigh\_modify <neigh_modify>`
     - :doc:`neighbor <neighbor>`
     - :doc:`newton <newton>`
     - :doc:`next <next>`
     - :doc:`package <package>`
   * - :doc:`pair\_coeff <pair_coeff>`
     - :doc:`pair\_modify <pair_modify>`
     - :doc:`pair\_style <pair_style>`
     - :doc:`pair\_write <pair_write>`
     - :doc:`partition <partition>`
   * - :doc:`prd <prd>`
     - :doc:`print <print>`
     - :doc:`processors <processors>`
     - :doc:`quit <quit>`
     - :doc:`read\_data <read_data>`
   * - :doc:`read\_dump <read_dump>`
     - :doc:`read\_restart <read_restart>`
     - :doc:`region <region>`
     - :doc:`replicate <replicate>`
     - :doc:`rerun <rerun>`
   * - :doc:`reset\_timestep <reset_timestep>`
     - :doc:`restart <restart>`
     - :doc:`run <run>`
     - :doc:`run\_style <run_style>`
     - :doc:`set <set>`
   * - :doc:`shell <shell>`
     - :doc:`special\_bonds <special_bonds>`
     - :doc:`suffix <suffix>`
     - :doc:`tad <tad>`
     - :doc:`temper <temper>`
   * - :doc:`thermo <thermo>`
     - :doc:`thermo\_log <thermo_log>`
     - :doc:`thermo\_modify <thermo_modify>`
     - :doc:`thermo\_style <thermo_style>`
     - :doc:`timestep <timestep>`
   * - :doc:`uncompute <uncompute>`
     - :doc:`undump <undump>`
     - :doc:`unfix <unfix>`
     - :doc:`units <units>`
     - :doc:`variable <variable>`
   * - :doc:`velocity <velocity>`
     - :doc:`write\_data <write_data>`
     - :doc:`write\_dump <write_dump>`
     - :doc:`write\_restart <write_restart>`
     -


----------


angle\_style potentials
-----------------------

See the :doc:`angle\_style <angle_style>` command for an overview of
angle potentials.  Click on the style itself for a full description:

.. list-table::
   :widths: auto

   * - :doc:`charmm <angle_charmm>`
     - :doc:`class2 <angle_class2>`
     - :doc:`cosine <angle_cosine>`
     - :doc:`cosine/delta <angle_cosine_delta>`
   * - :doc:`cosine/periodic <angle_cosine_periodic>`
     - :doc:`cosine/shift <angle_cosine_shift>`
     - :doc:`cosine/shift/exp <angle_cosine_shift_exp>`
     - :doc:`cosine/squared <angle_cosine_squared>`
   * - :doc:`dipole <angle_dipole>`
     - :doc:`fourier <angle_fourier>`
     - :doc:`fourier/simple <angle_fourier_simple>`
     - :doc:`harmonic <angle_harmonic>`
   * - :doc:`hybrid <angle_hybrid>`
     - :doc:`none <angle_none>`
     - :doc:`quartic <angle_quartic>`
     - :doc:`sdk <angle_sdk>`
   * - :doc:`table <angle_table>`
     -
     -
     -

These are accelerated angle styles, which can be used if LAMMPS is
built with the :doc:`appropriate accelerated package <Section_accelerate>`.

.. list-table::
   :widths: auto

   * - :doc:`charmm/omp <angle_charmm>`
     - :doc:`class2/omp <angle_class2>`
     - :doc:`cosine/delta/omp <angle_cosine_delta>`
     - :doc:`cosine/omp <angle_cosine>`
   * - :doc:`cosine/periodic/omp <angle_cosine_periodic>`
     - :doc:`cosine/shift/exp/omp <angle_cosine_shift_exp>`
     - :doc:`cosine/shift/omp <angle_cosine_shift>`
     - :doc:`cosine/squared/omp <angle_cosine_squared>`
   * - :doc:`dipole/omp <angle_dipole>`
     - :doc:`fourier/omp <angle_fourier>`
     - :doc:`fourier/simple/omp <angle_fourier_simple>`
     - :doc:`harmonic/omp <angle_harmonic>`
   * - :doc:`quartic/omp <angle_quartic>`
     - :doc:`table/omp <angle_table>`
     -
     -


----------


bond\_style potentials
----------------------

See the :doc:`bond\_style <bond_style>` command for an overview of bond
potentials.  Click on the style itself for a full description:

.. list-table::
   :widths: auto

   * - :doc:`class2 <bond_class2>`
     - :doc:`fene <bond_fene>`
     - :doc:`fene/expand <bond_fene_expand>`
     - :doc:`harmonic <bond_harmonic>`
   * - :doc:`harmonic/shift <bond_harmonic_shift>`
     - :doc:`harmonic/shift/cut <bond_harmonic_shift_cut>`
     - :doc:`hybrid <bond_hybrid>`
     - :doc:`morse <bond_morse>`
   * - :doc:`none <bond_none>`
     - :doc:`nonlinear <bond_nonlinear>`
     - :doc:`quartic <bond_quartic>`
     - :doc:`table <bond_table>`

These are accelerated bond styles, which can be used if LAMMPS is
built with the :doc:`appropriate accelerated package <Section_accelerate>`.

.. list-table::
   :widths: auto

   * - :doc:`class2/omp <bond_class2>`
     - :doc:`fene/expand/omp <bond_fene_expand>`
     - :doc:`fene/omp <bond_fene>`
     - :doc:`harmonic/omp <bond_harmonic>`
   * - :doc:`harmonic/shift/cut/omp <bond_harmonic_shift_cut>`
     - :doc:`harmonic/shift/omp <bond_harmonic_shift>`
     - :doc:`morse/omp <bond_morse>`
     - :doc:`nonlinear/omp <bond_nonlinear>`
   * - :doc:`quartic/omp <bond_quartic>`
     - :doc:`table/omp <bond_table>`
     -
     -


----------


compute styles
--------------

See the :doc:`compute <compute>` command for one-line descriptions of
each style or click on the style itself for a full description:

.. list-table::
   :widths: auto

   * - :doc:`ackland/atom <compute_ackland_atom>`
     - :doc:`angle/local <compute_angle_local>`
     - :doc:`atom/molecule <compute_atom_molecule>`
     - :doc:`basal/atom <compute_basal_atom>`
   * - :doc:`body/local <compute_body_local>`
     - :doc:`bond/local <compute_bond_local>`
     - :doc:`centro/atom <compute_centro_atom>`
     - :doc:`cluster/atom <compute_cluster_atom>`
   * - :doc:`cna/atom <compute_cna_atom>`
     - :doc:`com <compute_com>`
     - :doc:`com/molecule <compute_com_molecule>`
     - :doc:`contact/atom <compute_contact_atom>`
   * - :doc:`coord/atom <compute_coord_atom>`
     - :doc:`damage/atom <compute_damage_atom>`
     - :doc:`dihedral/local <compute_dihedral_local>`
     - :doc:`displace/atom <compute_displace_atom>`
   * - :doc:`erotate/asphere <compute_erotate_asphere>`
     - :doc:`erotate/multisphere <compute_erotate_multisphere>`
     - :doc:`erotate/sphere <compute_erotate_sphere>`
     - :doc:`erotate/sphere/atom <compute_erotate_sphere_atom>`
   * - :doc:`erotate/superquadric <compute_erotate_superquadric>`
     - :doc:`event/displace <compute_event_displace>`
     - :doc:`group/group <compute_group_group>`
     - :doc:`gyration <compute_gyration>`
   * - :doc:`gyration/molecule <compute_gyration_molecule>`
     - :doc:`heat/flux <compute_heat_flux>`
     - :doc:`improper/local <compute_improper_local>`
     - :doc:`inertia/molecule <compute_inertia_molecule>`
   * - :doc:`ke <compute_ke>`
     - :doc:`ke/atom <compute_ke_atom>`
     - :doc:`ke/atom/eff <compute_ke_atom_eff>`
     - :doc:`ke/eff <compute_ke_eff>`
   * - :doc:`ke/multisphere <compute_ke_multisphere>`
     - :doc:`meso\_e/atom <compute_meso_e_atom>`
     - :doc:`meso\_rho/atom <compute_meso_rho_atom>`
     - :doc:`meso\_t/atom <compute_meso_t_atom>`
   * - :doc:`msd <compute_msd>`
     - :doc:`msd/molecule <compute_msd_molecule>`
     - :doc:`msd/nongauss <compute_msd_nongauss>`
     - :doc:`neighbor/atom <compute_neighbor_atom>`
   * - :doc:`nparticles/tracer/region <compute_nparticles_tracer_region>`
     - :doc:`pair <compute_pair>`
     - :doc:`pair/gran/local <compute_pair_gran_local>`
     - :doc:`pair/local <compute_pair_local>`
   * - :doc:`pe <compute_pe>`
     - :doc:`pe/atom <compute_pe_atom>`
     - :doc:`pressure <compute_pressure>`
     - :doc:`property/atom <compute_property_atom>`
   * - :doc:`property/local <compute_property_local>`
     - :doc:`property/molecule <compute_property_molecule>`
     - :doc:`rdf <compute_rdf>`
     - :doc:`reduce <compute_reduce>`
   * - :doc:`reduce/region <compute_reduce>`
     - :doc:`rigid <compute_rigid>`
     - :doc:`slice <compute_slice>`
     - :doc:`stress/atom <compute_stress_atom>`
   * - :doc:`temp <compute_temp>`
     - :doc:`temp/asphere <compute_temp_asphere>`
     - :doc:`temp/com <compute_temp_com>`
     - :doc:`temp/deform <compute_temp_deform>`
   * - :doc:`temp/deform/eff <compute_temp_deform_eff>`
     - :doc:`temp/eff <compute_temp_eff>`
     - :doc:`temp/partial <compute_temp_partial>`
     - :doc:`temp/profile <compute_temp_profile>`
   * - :doc:`temp/ramp <compute_temp_ramp>`
     - :doc:`temp/region <compute_temp_region>`
     - :doc:`temp/region/eff <compute_temp_region_eff>`
     - :doc:`temp/rotate <compute_temp_rotate>`
   * - :doc:`temp/sphere <compute_temp_sphere>`
     - :doc:`ti <compute_ti>`
     - :doc:`voronoi/atom <compute_voronoi_atom>`
     - :doc:`wall/gran/local <compute_pair_gran_local>`

These are accelerated compute styles, which can be used if LAMMPS is
built with the :doc:`appropriate accelerated package <Section_accelerate>`.

.. list-table::
   :widths: auto

   * - :doc:`pe/cuda <compute_pe>`
     - :doc:`pressure/cuda <compute_pressure>`
     - :doc:`temp/cuda <compute_temp>`
     - :doc:`temp/partial/cuda <compute_temp_partial>`


----------


dihedral\_style potentials
--------------------------

See the :doc:`dihedral\_style <dihedral_style>` command for an overview
of dihedral potentials.  Click on the style itself for a full
description:

.. list-table::
   :widths: auto

   * - :doc:`charmm <dihedral_charmm>`
     - :doc:`class2 <dihedral_class2>`
     - :doc:`cosine/shift/exp <dihedral_cosine_shift_exp>`
     - :doc:`fourier <dihedral_fourier>`
   * - :doc:`harmonic <dihedral_harmonic>`
     - :doc:`helix <dihedral_helix>`
     - :doc:`hybrid <dihedral_hybrid>`
     - :doc:`multi/harmonic <dihedral_multi_harmonic>`
   * - :doc:`nharmonic <dihedral_nharmonic>`
     - :doc:`none <dihedral_none>`
     - :doc:`opls <dihedral_opls>`
     - :doc:`quadratic <dihedral_quadratic>`
   * - :doc:`table <dihedral_table>`
     -
     -
     -

These are accelerated dihedral styles, which can be used if LAMMPS is
built with the :doc:`appropriate accelerated package <Section_accelerate>`.

.. list-table::
   :widths: auto

   * - :doc:`charmm/omp <dihedral_charmm>`
     - :doc:`class2/omp <dihedral_class2>`
     - :doc:`cosine/shift/exp/omp <dihedral_cosine_shift_exp>`
     - :doc:`fourier/omp <dihedral_fourier>`
   * - :doc:`harmonic/omp <dihedral_harmonic>`
     - :doc:`helix/omp <dihedral_helix>`
     - :doc:`multi/harmonic/omp <dihedral_multi_harmonic>`
     - :doc:`nharmonic/omp <dihedral_nharmonic>`
   * - :doc:`opls/omp <dihedral_opls>`
     - :doc:`quadratic/omp <dihedral_quadratic>`
     - :doc:`table/omp <dihedral_table>`
     -


----------


dump styles
-----------

Click on the style itself for a full description:

.. list-table::
   :widths: auto

   * - :doc:`custom/vtk <dump_custom_vtk>`
     - :doc:`image <dump_image>`
     - :doc:`molfile <dump_molfile>`
     - :doc:`movie <dump_image>`


----------


fix styles
----------

See the :doc:`fix <fix>` command for one-line descriptions
of each style or click on the style itself for a full description:

.. list-table::
   :widths: auto

   * - :doc:`adapt <fix_adapt>`
     - :doc:`addforce <fix_addforce>`
     - :doc:`addtorque <fix_addtorque>`
   * - :doc:`append/atoms <fix_append_atoms>`
     - :doc:`atc <fix_atc>`
     - :doc:`ave/atom <fix_ave_atom>`
   * - :doc:`ave/correlate <fix_ave_correlate>`
     - :doc:`ave/euler <fix_ave_euler>`
     - :doc:`ave/euler/region <fix_ave_euler_region>`
   * - :doc:`ave/euler/region/universe <fix_ave_euler_region>`
     - :doc:`ave/histo <fix_ave_histo>`
     - :doc:`ave/spatial <fix_ave_spatial>`
   * - :doc:`ave/time <fix_ave_time>`
     - :doc:`aveforce <fix_aveforce>`
     - :doc:`balance <fix_balance>`
   * - :doc:`bond/break <fix_bond_break>`
     - :doc:`bond/create <fix_bond_create>`
     - :doc:`bond/swap <fix_bond_swap>`
   * - :doc:`box/relax <fix_box_relax>`
     - :doc:`break/particle <fix_break_particle>`
     - :doc:`buoyancy <fix_buoyancy>`
   * - :doc:`check/timestep/gran <fix_check_timestep_gran>`
     - :doc:`chem/shrink <fix_chem_shrink>`
     - :doc:`chem/shrink/core <fix_chem_shrink_core>`
   * - :doc:`colvars <fix_colvars>`
     - :doc:`couple/cfd/chemistry <fix_cfd_coupling_chemistry>`
     - :doc:`couple/cfd/convection <fix_cfd_coupling_convection>`
   * - :doc:`couple/cfd/deform <fix_cfd_coupling_deform>`
     - :doc:`couple/cfd/dissolve <fix_cfd_coupling_dissolve>`
     - :doc:`couple/cfd/fluidproperties <fix_cfd_coupling_fluidproperties>`
   * - :doc:`couple/cfd/recurrence <fix_cfd_coupling_recurrence>`
     - :doc:`deform <fix_deform>`
     - :doc:`deposit <fix_deposit>`
   * - :doc:`drag <fix_drag>`
     - :doc:`dt/reset <fix_dt_reset>`
     - :doc:`efield <fix_efield>`
   * - :doc:`enforce2d <fix_enforce2d>`
     - :doc:`evaporate <fix_evaporate>`
     - :doc:`execute <fix_execute>`
   * - :doc:`external <fix_external>`
     - :doc:`forcecontrol/region <fix_forcecontrol_region>`
     - :doc:`forcecontrol/region/universe <fix_forcecontrol_region>`
   * - :doc:`freeze <fix_freeze>`
     - :doc:`gcmc <fix_gcmc>`
     - :doc:`gld <fix_gld>`
   * - :doc:`gravity <fix_gravity>`
     - :doc:`heat <fix_heat>`
     - :doc:`heat/gran <fix_heat_gran_conduction>`
   * - :doc:`heat/gran/conduction <fix_heat_gran_conduction>`
     - :doc:`heat/gran/radiation <fix_heat_gran_radiation>`
     - :doc:`imd <fix_imd>`
   * - :doc:`indent <fix_indent>`
     - :doc:`insert/pack <fix_insert_pack>`
     - :doc:`insert/pack/dense <fix_insert_pack_dense>`
   * - :doc:`insert/pack/face <fix_insert_pack_face>`
     - :doc:`insert/pack/face/universe <fix_insert_pack_face>`
     - :doc:`insert/rate/region <fix_insert_rate_region>`
   * - :doc:`insert/stream <fix_insert_stream>`
     - :doc:`insert/stream/moving <fix_insert_stream_moving>`
     - :doc:`langevin <fix_langevin>`
   * - :doc:`langevin/eff <fix_langevin_eff>`
     - :doc:`lb/fluid <fix_lb_fluid>`
     - :doc:`lb/momentum <fix_lb_momentum>`
   * - :doc:`lb/pc <fix_lb_pc>`
     - :doc:`lb/rigid/pc/sphere <fix_lb_rigid_pc_sphere>`
     - :doc:`lb/viscous <fix_lb_viscous>`
   * - :doc:`limit/property/atom <fix_limit_property_atom>`
     - :doc:`limit/vel <fix_limit_vel>`
     - :doc:`lineforce <fix_lineforce>`
   * - :doc:`massflow/mesh <fix_massflow_mesh>`
     - :doc:`massflow/mesh/face <fix_massflow_mesh_face>`
     - :doc:`massflow/mesh/face/universe <fix_massflow_mesh_face>`
   * - :doc:`meanfreetime <fix_mean_free_time>`
     - :doc:`mesh/6dof <fix_mesh_surface_stress_6dof>`
     - :doc:`mesh/surface <fix_mesh_surface>`
   * - :doc:`mesh/surface/planar <fix_mesh_surface>`
     - :doc:`mesh/surface/stress <fix_mesh_surface_stress>`
     - :doc:`mesh/surface/stress/servo <fix_mesh_surface_stress_servo>`
   * - :doc:`meso <fix_meso>`
     - :doc:`meso/stationary <fix_meso_stationary>`
     - :doc:`momentum <fix_momentum>`
   * - :doc:`move <fix_move>`
     - :doc:`move/mesh <fix_move_mesh>`
     - :doc:`msst <fix_msst>`
   * - :doc:`multisphere <fix_multisphere>`
     - :doc:`neb <fix_neb>`
     - :doc:`nph <fix_nh>`
   * - :doc:`nph/asphere <fix_nph_asphere>`
     - :doc:`nph/eff <fix_nh_eff>`
     - :doc:`nph/sphere <fix_nph_sphere>`
   * - :doc:`nphug <fix_nphug>`
     - :doc:`npt <fix_nh>`
     - :doc:`npt/asphere <fix_npt_asphere>`
   * - :doc:`npt/eff <fix_nh_eff>`
     - :doc:`npt/sphere <fix_npt_sphere>`
     - :doc:`nve <fix_nve>`
   * - :doc:`nve/asphere <fix_nve_asphere>`
     - :doc:`nve/asphere/noforce <fix_nve_asphere_noforce>`
     - :doc:`nve/body <fix_nve_body>`
   * - :doc:`nve/eff <fix_nve_eff>`
     - :doc:`nve/limit <fix_nve_limit>`
     - :doc:`nve/line <fix_nve_line>`
   * - :doc:`nve/noforce <fix_nve_noforce>`
     - :doc:`nve/sphere <fix_nve_sphere>`
     - :doc:`nve/superquadric <fix_nve_superquadric>`
   * - :doc:`nve/tri <fix_nve_tri>`
     - :doc:`nvt <fix_nh>`
     - :doc:`nvt/asphere <fix_nvt_asphere>`
   * - :doc:`nvt/eff <fix_nh_eff>`
     - :doc:`nvt/sllod <fix_nvt_sllod>`
     - :doc:`nvt/sllod/eff <fix_nvt_sllod_eff>`
   * - :doc:`nvt/sphere <fix_nvt_sphere>`
     - :doc:`orient/fcc <fix_orient_fcc>`
     - :doc:`particledistribution/discrete <fix_particledistribution_discrete>`
   * - :doc:`particletemplate/fragments <fix_particletemplate_fragments>`
     - :doc:`particletemplate/multiplespheres <fix_particletemplate_multiplespheres>`
     - :doc:`particletemplate/multisphere <fix_particletemplate_multisphere>`
   * - :doc:`particletemplate/sphere <fix_particletemplate_sphere>`
     - :doc:`particletemplate/superquadric <fix_particletemplate_superquadric>`
     - :doc:`phonon <fix_phonon>`
   * - :doc:`planeforce <fix_planeforce>`
     - :doc:`pour/legacy <fix_pour>`
     - :doc:`press/berendsen <fix_press_berendsen>`
   * - :doc:`print <fix_print>`
     - :doc:`property/atom <fix_property>`
     - :doc:`property/atom/cumulativetracer <fix_property_atom_cumulativetracer>`
   * - :doc:`property/atom/timetracer <fix_property_atom_timetracer>`
     - :doc:`property/atom/tracer <fix_property_atom_tracer>`
     - :doc:`property/atom/tracer/stream <fix_property_atom_tracer_stream>`
   * - :doc:`property/global <fix_property>`
     - :doc:`qeq/comb <fix_qeq_comb>`
     - :doc:`qeq/reax <fix_qeq_reax>`
   * - :doc:`reax/bonds <fix_reax_bonds>`
     - :doc:`reax/c/bonds <fix_reax_bonds>`
     - :doc:`reax/c/species <fix_reaxc_species>`
   * - :doc:`recenter <fix_recenter>`
     - :doc:`remove <fix_remove>`
     - :doc:`restrain <fix_restrain>`
   * - :doc:`rigid <fix_rigid>`
     - :doc:`rigid/nph <fix_rigid>`
     - :doc:`rigid/npt <fix_rigid>`
   * - :doc:`rigid/nve <fix_rigid>`
     - :doc:`rigid/nvt <fix_rigid>`
     - :doc:`rigid/small <fix_rigid>`
   * - :doc:`scale/diameter <fix_scale_diameter>`
     - :doc:`setforce <fix_setforce>`
     - :doc:`setvelocity <fix_setvelocity>`
   * - :doc:`shake <fix_shake>`
     - :doc:`smd <fix_smd>`
     - :doc:`speedcontrol <fix_speedcontrol>`
   * - :doc:`sph/density/continuity <fix_sph_density_continuity>`
     - :doc:`sph/density/corr <fix_sph_density_corr>`
     - :doc:`sph/density/summation <fix_sph_density_summation>`
   * - :doc:`sph/pressure <fix_sph_pressure>`
     - :doc:`spring <fix_spring>`
     - :doc:`spring/rg <fix_spring_rg>`
   * - :doc:`spring/self <fix_spring_self>`
     - :doc:`srd <fix_srd>`
     - :doc:`store/force <fix_store_force>`
   * - :doc:`store/state <fix_store_state>`
     - :doc:`temp/berendsen <fix_temp_berendsen>`
     - :doc:`temp/rescale <fix_temp_rescale>`
   * - :doc:`temp/rescale/eff <fix_temp_rescale_eff>`
     - :doc:`thermal/conductivity <fix_thermal_conductivity>`
     - :doc:`ti/rs <fix_ti_rs>`
   * - :doc:`ti/spring <fix_ti_spring>`
     - :doc:`tmd <fix_tmd>`
     - :doc:`ttm <fix_ttm>`
   * - :doc:`tune/kspace <fix_tune_kspace>`
     - :doc:`viscosity <fix_viscosity>`
     - :doc:`viscous <fix_viscous>`
   * - :doc:`wall/colloid <fix_wall>`
     - :doc:`wall/gran <fix_wall_gran>`
     - :doc:`wall/harmonic <fix_wall>`
   * - :doc:`wall/lj1043 <fix_wall>`
     - :doc:`wall/lj126 <fix_wall>`
     - :doc:`wall/lj93 <fix_wall>`
   * - :doc:`wall/piston <fix_wall_piston>`
     - :doc:`wall/reflect <fix_wall_reflect>`
     - :doc:`wall/region <fix_wall_region>`
   * - :doc:`wall/region/sph <fix_wall_region_sph>`
     - :doc:`wall/srd <fix_wall_srd>`
     -

These are accelerated fix styles, which can be used if LAMMPS is
built with the :doc:`appropriate accelerated package <Section_accelerate>`.

.. list-table::
   :widths: auto

   * - :doc:`addforce/cuda <fix_addforce>`
     - :doc:`aveforce/cuda <fix_aveforce>`
     - :doc:`enforce2d/cuda <fix_enforce2d>`
     - :doc:`freeze/cuda <fix_freeze>`
   * - :doc:`gravity/cuda <fix_gravity>`
     - :doc:`gravity/omp <fix_gravity>`
     - :doc:`nph/asphere/omp <fix_nph_asphere>`
     - :doc:`nph/omp <fix_nh>`
   * - :doc:`nph/sphere/omp <fix_nph_sphere>`
     - :doc:`nphug/omp <fix_nphug>`
     - :doc:`npt/asphere/omp <fix_npt_asphere>`
     - :doc:`npt/cuda <fix_nh>`
   * - :doc:`npt/omp <fix_nh>`
     - :doc:`npt/sphere/omp <fix_npt_sphere>`
     - :doc:`nve/cuda <fix_nve>`
     - :doc:`nve/omp <fix_nve>`
   * - :doc:`nve/sphere/omp <fix_nve_sphere>`
     - :doc:`nvt/asphere/omp <fix_nvt_asphere>`
     - :doc:`nvt/cuda <fix_nh>`
     - :doc:`nvt/omp <fix_nh>`
   * - :doc:`nvt/sllod/omp <fix_nvt_sllod>`
     - :doc:`nvt/sphere/omp <fix_nvt_sphere>`
     - :doc:`qeq/comb/omp <fix_qeq_comb>`
     - :doc:`setforce/cuda <fix_setforce>`
   * - :doc:`shake/cuda <fix_shake>`
     - :doc:`temp/berendsen/cuda <fix_temp_berendsen>`
     - :doc:`temp/rescale/cuda <fix_temp_rescale>`
     - :doc:`temp/rescale/limit/cuda <fix_temp_rescale>`
   * - :doc:`viscous/cuda <fix_viscous>`
     -
     -
     -


----------


improper\_style potentials
--------------------------

See the :doc:`improper\_style <improper_style>` command for an overview
of improper potentials.  Click on the style itself for a full
description:

.. list-table::
   :widths: auto

   * - :doc:`class2 <improper_class2>`
     - :doc:`cossq <improper_cossq>`
     - :doc:`cvff <improper_cvff>`
     - :doc:`fourier <improper_fourier>`
   * - :doc:`harmonic <improper_harmonic>`
     - :doc:`hybrid <improper_hybrid>`
     - :doc:`none <improper_none>`
     - :doc:`ring <improper_ring>`
   * - :doc:`umbrella <improper_umbrella>`
     -
     -
     -

These are accelerated improper styles, which can be used if LAMMPS is
built with the :doc:`appropriate accelerated package <Section_accelerate>`.

.. list-table::
   :widths: auto

   * - :doc:`class2/omp <improper_class2>`
     - :doc:`cossq/omp <improper_cossq>`
     - :doc:`cvff/omp <improper_cvff>`
     - :doc:`fourier/omp <improper_fourier>`
   * - :doc:`harmonic/omp <improper_harmonic>`
     - :doc:`ring/omp <improper_ring>`
     - :doc:`umbrella/omp <improper_umbrella>`
     -


----------


pair\_style potentials
----------------------

See the :doc:`pair\_style <pair_style>` command for an overview of pair
potentials.  Click on the style itself for a full description:

.. list-table::
   :widths: auto

   * - :doc:`adp <pair_adp>`
     - :doc:`airebo <pair_airebo>`
     - :doc:`awpmd/cut <pair_awpmd>`
     - :doc:`beck <pair_beck>`
   * - :doc:`body <pair_body>`
     - :doc:`bop <pair_bop>`
     - :doc:`born <pair_born>`
     - :doc:`born/coul/long <pair_born>`
   * - :doc:`born/coul/msm <pair_born>`
     - :doc:`born/coul/wolf <pair_born>`
     - :doc:`brownian <pair_brownian>`
     - :doc:`brownian/poly <pair_brownian>`
   * - :doc:`buck <pair_buck>`
     - :doc:`buck/coul/cut <pair_buck>`
     - :doc:`buck/coul/long <pair_buck>`
     - :doc:`buck/coul/msm <pair_buck>`
   * - :doc:`buck/long/coul/long <pair_buck_long>`
     - :doc:`colloid <pair_colloid>`
     - :doc:`comb <pair_comb>`
     - :doc:`comb3 <pair_comb>`
   * - :doc:`coul/cut <pair_coul>`
     - :doc:`coul/debye <pair_coul>`
     - :doc:`coul/diel <pair_coul_diel>`
     - :doc:`coul/dsf <pair_coul>`
   * - :doc:`coul/long <pair_coul>`
     - :doc:`coul/msm <pair_coul>`
     - :doc:`coul/wolf <pair_coul>`
     - :doc:`dpd <pair_dpd>`
   * - :doc:`dpd/tstat <pair_dpd>`
     - :doc:`dsmc <pair_dsmc>`
     - :doc:`eam <pair_eam>`
     - :doc:`eam/alloy <pair_eam>`
   * - :doc:`eam/cd <pair_eam>`
     - :doc:`eam/fs <pair_eam>`
     - :doc:`edip <pair_edip>`
     - :doc:`eff/cut <pair_eff>`
   * - :doc:`eim <pair_eim>`
     - :doc:`gauss <pair_gauss>`
     - :doc:`gauss/cut <pair_gauss>`
     - :doc:`gayberne <pair_gayberne>`
   * - :doc:`gran <pair_gran>`
     - :doc:`hbond/dreiding/lj <pair_hbond_dreiding>`
     - :doc:`hbond/dreiding/morse <pair_hbond_dreiding>`
     - :doc:`hybrid <pair_hybrid>`
   * - :doc:`hybrid/overlay <pair_hybrid>`
     - :doc:`kim <pair_kim>`
     - :doc:`lcbop <pair_lcbop>`
     - :doc:`line/lj <pair_line_lj>`
   * - :doc:`list <pair_list>`
     - :doc:`lj/charmm/coul/charmm <pair_charmm>`
     - :doc:`lj/charmm/coul/charmm/implicit <pair_charmm>`
     - :doc:`lj/charmm/coul/long <pair_charmm>`
   * - :doc:`lj/charmm/coul/msm <pair_charmm>`
     - :doc:`lj/class2 <pair_class2>`
     - :doc:`lj/class2/coul/cut <pair_class2>`
     - :doc:`lj/class2/coul/long <pair_class2>`
   * - :doc:`lj/cubic <pair_lj_cubic>`
     - :doc:`lj/cut <pair_lj>`
     - :doc:`lj/cut/coul/cut <pair_lj>`
     - :doc:`lj/cut/coul/debye <pair_lj>`
   * - :doc:`lj/cut/coul/dsf <pair_lj>`
     - :doc:`lj/cut/coul/long <pair_lj>`
     - :doc:`lj/cut/coul/msm <pair_lj>`
     - :doc:`lj/cut/dipole/cut <pair_dipole>`
   * - :doc:`lj/cut/dipole/long <pair_dipole>`
     - :doc:`lj/cut/tip4p/cut <pair_lj>`
     - :doc:`lj/cut/tip4p/long <pair_lj>`
     - :doc:`lj/expand <pair_lj_expand>`
   * - :doc:`lj/gromacs <pair_gromacs>`
     - :doc:`lj/gromacs/coul/gromacs <pair_gromacs>`
     - :doc:`lj/long/coul/long <pair_lj_long>`
     - :doc:`lj/long/dipole/long <pair_dipole>`
   * - :doc:`lj/long/tip4p/long <pair_lj_long>`
     - :doc:`lj/sdk <pair_sdk>`
     - :doc:`lj/sdk/coul/long <pair_sdk>`
     - :doc:`lj/sf <pair_lj_sf>`
   * - :doc:`lj/sf/dipole/sf <pair_dipole>`
     - :doc:`lj/smooth <pair_lj_smooth>`
     - :doc:`lj/smooth/linear <pair_lj_smooth_linear>`
     - :doc:`lj96/cut <pair_lj96>`
   * - :doc:`lubricate <pair_lubricate>`
     - :doc:`lubricate/poly <pair_lubricate>`
     - :doc:`lubricateU <pair_lubricateU>`
     - :doc:`lubricateU/poly <pair_lubricateU>`
   * - :doc:`meam <pair_meam>`
     - :doc:`mie/cut <pair_mie>`
     - :doc:`morse <pair_morse>`
     - :doc:`nb3b/harmonic <pair_nb3b_harmonic>`
   * - :doc:`nm/cut <pair_nm>`
     - :doc:`nm/cut/coul/cut <pair_nm>`
     - :doc:`nm/cut/coul/long <pair_nm>`
     - :doc:`none <pair_none>`
   * - :doc:`peri/lps <pair_peri>`
     - :doc:`peri/pmb <pair_peri>`
     - :doc:`peri/ves <pair_peri>`
     - :doc:`reax <pair_reax>`
   * - :doc:`reax/c <pair_reax_c>`
     - :doc:`rebo <pair_airebo>`
     - :doc:`resquared <pair_resquared>`
     - :doc:`soft <pair_soft>`
   * - :doc:`sph <pair_sph>`
     - :doc:`sph/artVisc/tensCorr <pair_sph_artvisc_tenscorr>`
     - :doc:`sph/heatconduction <pair_sph_heatconduction>`
     - :doc:`sph/idealgas <pair_sph_idealgas>`
   * - :doc:`sph/lj <pair_sph_lj>`
     - :doc:`sph/rhosum <pair_sph_rhosum>`
     - :doc:`sph/taitwater <pair_sph_taitwater>`
     - :doc:`sph/taitwater/morris <pair_sph_taitwater_morris>`
   * - :doc:`sw <pair_sw>`
     - :doc:`table <pair_table>`
     - :doc:`tersoff <pair_tersoff>`
     - :doc:`tersoff/mod <pair_tersoff_mod>`
   * - :doc:`tersoff/table <pair_tersoff>`
     - :doc:`tersoff/zbl <pair_tersoff_zbl>`
     - :doc:`tip4p/cut <pair_coul>`
     - :doc:`tip4p/long <pair_coul>`
   * - :doc:`tri/lj <pair_tri_lj>`
     - :doc:`yukawa <pair_yukawa>`
     - :doc:`yukawa/colloid <pair_yukawa_colloid>`
     - :doc:`zbl <pair_zbl>`

These are accelerated pair styles, which can be used if LAMMPS is
built with the :doc:`appropriate accelerated package <Section_accelerate>`.

.. list-table::
   :widths: auto

   * - :doc:`adp/omp <pair_adp>`
     - :doc:`airebo/omp <pair_airebo>`
     - :doc:`beck/gpu <pair_beck>`
   * - :doc:`beck/omp <pair_beck>`
     - :doc:`born/coul/long/cuda <pair_born>`
     - :doc:`born/coul/long/gpu <pair_born>`
   * - :doc:`born/coul/long/omp <pair_born>`
     - :doc:`born/coul/msm/omp <pair_born>`
     - :doc:`born/coul/wolf/gpu <pair_born>`
   * - :doc:`born/coul/wolf/omp <pair_born>`
     - :doc:`born/gpu <pair_born>`
     - :doc:`born/omp <pair_born>`
   * - :doc:`brownian/omp <pair_brownian>`
     - :doc:`brownian/poly/omp <pair_brownian>`
     - :doc:`buck/coul/cut/cuda <pair_buck>`
   * - :doc:`buck/coul/cut/gpu <pair_buck>`
     - :doc:`buck/coul/cut/omp <pair_buck>`
     - :doc:`buck/coul/long/cuda <pair_buck>`
   * - :doc:`buck/coul/long/gpu <pair_buck>`
     - :doc:`buck/coul/long/omp <pair_buck>`
     - :doc:`buck/coul/msm/omp <pair_buck>`
   * - :doc:`buck/cuda <pair_buck>`
     - :doc:`buck/gpu <pair_buck>`
     - :doc:`buck/long/coul/long/omp <pair_buck_long>`
   * - :doc:`buck/omp <pair_buck>`
     - :doc:`colloid/gpu <pair_colloid>`
     - :doc:`colloid/omp <pair_colloid>`
   * - :doc:`comb/omp <pair_comb>`
     - :doc:`coul/cut/omp <pair_coul>`
     - :doc:`coul/debye/omp <pair_coul>`
   * - :doc:`coul/dsf/gpu <pair_coul>`
     - :doc:`coul/dsf/omp <pair_coul>`
     - :doc:`coul/long/gpu <pair_coul>`
   * - :doc:`coul/long/omp <pair_coul>`
     - :doc:`coul/msm/omp <pair_coul>`
     - :doc:`coul/wolf/omp <pair_coul>`
   * - :doc:`dpd/omp <pair_dpd>`
     - :doc:`dpd/tstat/omp <pair_dpd>`
     - :doc:`eam/alloy/cuda <pair_eam>`
   * - :doc:`eam/alloy/gpu <pair_eam>`
     - :doc:`eam/alloy/omp <pair_eam>`
     - :doc:`eam/alloy/opt <pair_eam>`
   * - :doc:`eam/cd/omp <pair_eam>`
     - :doc:`eam/cuda <pair_eam>`
     - :doc:`eam/fs/cuda <pair_eam>`
   * - :doc:`eam/fs/gpu <pair_eam>`
     - :doc:`eam/fs/omp <pair_eam>`
     - :doc:`eam/fs/opt <pair_eam>`
   * - :doc:`eam/gpu <pair_eam>`
     - :doc:`eam/omp <pair_eam>`
     - :doc:`eam/opt <pair_eam>`
   * - :doc:`eim/omp <pair_eim>`
     - :doc:`gauss/cut/omp <pair_gauss>`
     - :doc:`gauss/gpu <pair_gauss>`
   * - :doc:`gauss/omp <pair_gauss>`
     - :doc:`gayberne/gpu <pair_gayberne>`
     - :doc:`gayberne/omp <pair_gayberne>`
   * - :doc:`hbond/dreiding/lj/omp <pair_hbond_dreiding>`
     - :doc:`hbond/dreiding/morse/omp <pair_hbond_dreiding>`
     - :doc:`hybrid/omp <pair_hybrid>`
   * - :doc:`hybrid/overlay/omp <pair_hybrid>`
     - :doc:`line/lj/omp <pair_line_lj>`
     - :doc:`lj/charmm/coul/charmm/cuda <pair_charmm>`
   * - :doc:`lj/charmm/coul/charmm/implicit/cuda <pair_charmm>`
     - :doc:`lj/charmm/coul/charmm/implicit/omp <pair_charmm>`
     - :doc:`lj/charmm/coul/charmm/omp <pair_charmm>`
   * - :doc:`lj/charmm/coul/long/cuda <pair_charmm>`
     - :doc:`lj/charmm/coul/long/gpu <pair_charmm>`
     - :doc:`lj/charmm/coul/long/omp <pair_charmm>`
   * - :doc:`lj/charmm/coul/long/opt <pair_charmm>`
     - :doc:`lj/charmm/coul/msm/omp <pair_charmm>`
     - :doc:`lj/class2/coul/cut/cuda <pair_class2>`
   * - :doc:`lj/class2/coul/cut/omp <pair_class2>`
     - :doc:`lj/class2/coul/long/cuda <pair_class2>`
     - :doc:`lj/class2/coul/long/gpu <pair_class2>`
   * - :doc:`lj/class2/coul/long/omp <pair_class2>`
     - :doc:`lj/class2/cuda <pair_class2>`
     - :doc:`lj/class2/gpu <pair_class2>`
   * - :doc:`lj/class2/omp <pair_class2>`
     - :doc:`lj/cubic/omp <pair_lj_cubic>`
     - :doc:`lj/cut/coul/cut/cuda <pair_lj>`
   * - :doc:`lj/cut/coul/cut/gpu <pair_lj>`
     - :doc:`lj/cut/coul/cut/omp <pair_lj>`
     - :doc:`lj/cut/coul/debye/cuda <pair_lj>`
   * - :doc:`lj/cut/coul/debye/gpu <pair_lj>`
     - :doc:`lj/cut/coul/debye/omp <pair_lj>`
     - :doc:`lj/cut/coul/dsf/gpu <pair_lj>`
   * - :doc:`lj/cut/coul/dsf/omp <pair_lj>`
     - :doc:`lj/cut/coul/long/cuda <pair_lj>`
     - :doc:`lj/cut/coul/long/gpu <pair_lj>`
   * - :doc:`lj/cut/coul/long/omp <pair_lj>`
     - :doc:`lj/cut/coul/long/opt <pair_lj>`
     - :doc:`lj/cut/coul/msm/gpu <pair_lj>`
   * - :doc:`lj/cut/coul/msm/omp <pair_lj>`
     - :doc:`lj/cut/cuda <pair_lj>`
     - :doc:`lj/cut/dipole/cut/gpu <pair_dipole>`
   * - :doc:`lj/cut/dipole/cut/omp <pair_dipole>`
     - :doc:`lj/cut/experimental/cuda <pair_lj>`
     - :doc:`lj/cut/gpu <pair_lj>`
   * - :doc:`lj/cut/omp <pair_lj>`
     - :doc:`lj/cut/opt <pair_lj>`
     - :doc:`lj/cut/tip4p/cut/omp <pair_lj>`
   * - :doc:`lj/cut/tip4p/long/omp <pair_lj>`
     - :doc:`lj/cut/tip4p/long/opt <pair_lj>`
     - :doc:`lj/expand/cuda <pair_lj_expand>`
   * - :doc:`lj/expand/gpu <pair_lj_expand>`
     - :doc:`lj/expand/omp <pair_lj_expand>`
     - :doc:`lj/gromacs/coul/gromacs/cuda <pair_gromacs>`
   * - :doc:`lj/gromacs/coul/gromacs/omp <pair_gromacs>`
     - :doc:`lj/gromacs/cuda <pair_gromacs>`
     - :doc:`lj/gromacs/omp <pair_gromacs>`
   * - :doc:`lj/long/coul/long/omp <pair_lj_long>`
     - :doc:`lj/long/coul/long/opt <pair_lj_long>`
     - :doc:`lj/sdk/coul/long/gpu <pair_sdk>`
   * - :doc:`lj/sdk/coul/long/omp <pair_sdk>`
     - :doc:`lj/sdk/gpu <pair_sdk>`
     - :doc:`lj/sdk/omp <pair_sdk>`
   * - :doc:`lj/sf/dipole/sf/gpu <pair_dipole>`
     - :doc:`lj/sf/dipole/sf/omp <pair_dipole>`
     - :doc:`lj/sf/omp <pair_lj_sf>`
   * - :doc:`lj/smooth/cuda <pair_lj_smooth>`
     - :doc:`lj/smooth/linear/omp <pair_lj_smooth_linear>`
     - :doc:`lj/smooth/omp <pair_lj_smooth>`
   * - :doc:`lj96/cut/cuda <pair_lj96>`
     - :doc:`lj96/cut/gpu <pair_lj96>`
     - :doc:`lj96/cut/omp <pair_lj96>`
   * - :doc:`lubricate/omp <pair_lubricate>`
     - :doc:`lubricate/poly/omp <pair_lubricate>`
     - :doc:`mie/cut/gpu <pair_mie>`
   * - :doc:`morse/cuda <pair_morse>`
     - :doc:`morse/gpu <pair_morse>`
     - :doc:`morse/omp <pair_morse>`
   * - :doc:`morse/opt <pair_morse>`
     - :doc:`nb3b/harmonic/omp <pair_nb3b_harmonic>`
     - :doc:`nm/cut/coul/cut/omp <pair_nm>`
   * - :doc:`nm/cut/coul/long/omp <pair_nm>`
     - :doc:`nm/cut/omp <pair_nm>`
     - :doc:`peri/lps/omp <pair_peri>`
   * - :doc:`peri/pmb/omp <pair_peri>`
     - :doc:`rebo/omp <pair_airebo>`
     - :doc:`resquared/gpu <pair_resquared>`
   * - :doc:`resquared/omp <pair_resquared>`
     - :doc:`soft/gpu <pair_soft>`
     - :doc:`soft/omp <pair_soft>`
   * - :doc:`sw/cuda <pair_sw>`
     - :doc:`sw/gpu <pair_sw>`
     - :doc:`sw/omp <pair_sw>`
   * - :doc:`table/gpu <pair_table>`
     - :doc:`table/omp <pair_table>`
     - :doc:`tersoff/mod/omp <pair_tersoff_mod>`
   * - :doc:`tersoff/table/omp <pair_tersoff>`
     - :doc:`tersoff/zbl/omp <pair_tersoff_zbl>`
     - :doc:`tip4p/cut/omp <pair_coul>`
   * - :doc:`tip4p/long/omp <pair_coul>`
     - :doc:`tri/lj/omp <pair_tri_lj>`
     - :doc:`yukawa/colloid/gpu <pair_yukawa_colloid>`
   * - :doc:`yukawa/colloid/omp <pair_yukawa_colloid>`
     - :doc:`yukawa/gpu <pair_yukawa>`
     - :doc:`yukawa/omp <pair_yukawa>`
   * - :doc:`zbl/omp <pair_zbl>`
     -
     -


.. _lws: https://www.lammps.org/
