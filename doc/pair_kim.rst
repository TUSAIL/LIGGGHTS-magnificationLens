.. index:: pair\_style kim

pair\_style kim command
=======================

Syntax
""""""


.. parsed-literal::

   pair_style kim virialmode model

* virialmode = KIMvirial or LAMMPSvirial
* model = name of KIM model (potential)

Examples
""""""""


.. parsed-literal::

   pair_style kim KIMvirial model_Ar_P_Morse
   pair_coeff \* \* Ar Ar

Description
"""""""""""

This pair style is a wrapper on the `Knowledge Base for Interatomic Models (KIM) <http://openkim.org>`_ repository of interatomic potentials,
so that they can be used by LAMMPS scripts.

In KIM lingo, a potential is a "model" and a model contains both the
analytic formulas that define the potential as well as the parameters
needed to run it for one or more materials, including coefficients and
cutoffs.

The argument *virialmode* determines how the global virial is
calculated.  If *KIMvirial* is specified, the KIM model performs the
global virial calculation.  If *LAMMPSvirial* is specified, LAMMPS
computes the global virial using its fdotr mechanism.

The argument *model* is the name of the KIM model for a specific
potential as KIM defines it.  In principle, LAMMPS can invoke any KIM
model.  You should get an error or warning message from either LAMMPS
or KIM if there is an incompatibility.

Only a single pair\_coeff command is used with the *kim* style which
specifies the mapping of LAMMPS atom types to KIM elements.  This is
done by specifying N additional arguments after the \* \* in the
pair\_coeff command, where N is the number of LAMMPS atom types:

* N element names = mapping of KIM elements to atom types

As an example, imagine the KIM model supports Si and C atoms.  If your
LAMMPS simulation has 4 atom types and you want the 1st 3 to be Si,
and the 4th to be C, you would use the following pair\_coeff command:


.. parsed-literal::

   pair_coeff \* \* Si Si Si C

The 1st 2 arguments must be \* \* so as to span all LAMMPS atom types.
The first three Si arguments map LAMMPS atom types 1,2,3 to Si as
defined within KIM.  The final C argument maps LAMMPS atom type 4 to C
as defined within KIM.  If a mapping value is specified as NULL, the
mapping is not performed.  This can only be used when a *kim*
potential is used as part of the *hybrid* pair style.  The NULL values
are placeholders for atom types that will be used with other
potentials.


----------


In addition to the usual LAMMPS error messages, the KIM library itself
may generate errors, which should be printed to the screen.  In this
case it is also useful to check the kim.log file for additional error
information.  This file kim.log should be generated in the same
directory where LAMMPS is running.


----------


Here is information on how to build KIM for use with LAMMPS.  There is
a directory src/KIM/ with an important file in it: Makefile.lammps.
When you do 'make yes-kim' LAMMPS will use the settings in
src/KIM/Makefile.lammps to find KIM header files and the KIM library
itself for linking purposes.  Thus, you should ensure Makefile.lammps
has the correct settings for your system and your build of KIM.

Consult the KIM documentation for further details on KIM specifics.

OpenKIM is available for download from `this site <http://openkim.org>`_,
namely http://openkim.org.  The tarball you download is
"openkim-api-vX.X.X.tgz", which can be unpacked via


.. parsed-literal::

   tar xvfz openkim\*tgz

The openkim-api-vX.X.X/DOCS directory has further documentation.  For
more information on installing KIM and troubleshooting refer to
openkim/INSTALL.

Here is a brief summary of how to build KIM:

#. If you have previously used the openkim-api package (versions 1.1.1 or
   below), it is recommended that you remove all associated environment
   variables from your environment.  (These include, KIM\_DIR, KIM\_INTEL,
   KIM\_SYSTEM32, KIM\_DYNAMIC, KIM\_API\_DIR, KIM\_TESTS\_DIR,
   KIM\_MODEL\_DRIVERS\_DIR, and KIM\_MODELS\_DIR.)  All setting are now
   specified in the Makefile.KIM\_Config file.
#. Set up the Makefile.KIM\_Config file
  
  .. parsed-literal::
  
        (a) Copy the file Makefile.KIM_Config.example to Makefile.KIM_Config
            For example, if you untarred the 'openkim-api-vX.X.X.tgz' tarball in
            your home directory, you would do:

  
  .. parsed-literal::
  
            % cd $HOME/openkim-api-vX.X.X
            % cp Makefile.KIM_Config.example Makefile.KIM_Config

  
  .. parsed-literal::
  
            The '%' symbol represents the bash sell prompt and should not be typed.

  
  .. parsed-literal::
  
            (Above 'vX.X.X' represents the current release number.)

  
  .. parsed-literal::
  
        (b) Edit the file Makefile.KIM_Config and set the appropriate value for the
            KIM_DIR variable.  This must expand to an absolute path.  Using the same
            assumptions as above, this would be

  
  .. parsed-literal::
  
            KIM_DIR = $(HOME)/openkim-api-vX.X.X

  
  .. parsed-literal::
  
        (c) If appropriate, set explicit values for the remaining three 
            directories

  
  .. parsed-literal::
  
            KIM_MODEL_DRIVERS_DIR =
            KIM_MODELS_DIR =
            KIM_TESTS_DIR =

  
  .. parsed-literal::
  
            If these lines are commented out, defaults will be provided by the
            openkim-api make system.

  
  .. parsed-literal::
  
        (d) Set the value of KIM_COMPILERSUITE.  Possible values are 'GCC' and
            'INTEL'.

  
  .. parsed-literal::
  
            KIM_COMPILERSUITE = GCC

  
  .. parsed-literal::
  
        (e) Set the value of KIM_SYSTEMLINKER. Possible values are 'linux',
            'freebsd', and 'darwin'.

  
  .. parsed-literal::
  
            KIM_SYSTEMLINKER = linux

  
  .. parsed-literal::
  
        (f) Set the value of KIM_SYSTEMARCH.  Possible values are '32bit' and
            '64bit'.

  
  .. parsed-literal::
  
            KIM_SYSTEMARCH = 64bit

  
  .. parsed-literal::
  
        (g) Set the value of KIM_LINK.  Possible values are 'dynamic-load',
            'dynamic-link', and 'static-link'.

  
  .. parsed-literal::
  
            KIM_LINK = dynamic-load

  
  .. parsed-literal::
  
            'dynamic-load' is the preferred option. (Unless performance or
            other issues require it, you should use dynamic-load.)
            'dynamic-link' is like 'dynamic-load' but does not use the dl.h
            library.  This option requires a more complicated Makefile
            process, but may improve computation time in some instances.
            'static-link' only works with ONE Model and AT MOST ONE Model
            Driver (in order to avoid the possibility of symbol
            clashes).

  
  .. parsed-literal::
  
        (h) Set override values for other variables, if necessary, by
            adding the desired variable name (after the "# overwrite
            default variable values here" line) and filling in appropriate
            values.

  
  .. parsed-literal::
  
            # overwrite default variable values here

  
  .. parsed-literal::
  
            # overwrite default compiler options

  
  .. parsed-literal::
  
            CC =
            CXX =
            FC =

  
  .. parsed-literal::
  
            # overwrite default compiler option flag lists
            FFLAGS   =
            CCFLAGS  =
            CXXFLAGS =
            LDFLAGS  =

  
  .. parsed-literal::
  
            # overwrite default linker options
            LDSHAREDFLAG =
            LINKSONAME =
            LDWHOLEARCHIVESTARTFLAG =
            LDWHOLEARCHIVEENDFLAG =

  
  .. parsed-literal::
  
            # overwrite default install directories
            package_name =
            prefix =
            libdir =

#. In the remainder of the documentation we will use the string $KD to
   represent the location of the openkim-api source package (the value of
   the KIM\_DIR variable discussed above).  If you wish to, type the below
   commands exactly as written to set the shell variable KD to the
   appropriate value:
  
  .. parsed-literal::
  
        bash:
        % export KD=$HOME/openkim-api-vX.X.X

#. To compile the package, including the provided examples, change to the
   $KD directory and execute 'make examples' and then 'make':
  
  .. parsed-literal::
  
        % cd $KD
        % make examples
        % make

  
  .. parsed-literal::
  
          This builds all Model Drivers, Models, Tests, and the openkim-api service
          routine library.  The targets defined by the Makefile in this directory
          include:

  
  .. parsed-literal::
  
            'make'                -- compiles the API and all Models and Tests
            'make all'            -- same as 'make'
            'make clean'          -- will remove appropriate .o, .mod, .a, .so and
                                     executable files
            'make install'        -- install files to '/usr/local/lib' by default
            'make uninstall'      -- delete files installed by 'make install'
            'make openkim-api'    -- compiles only the API
            'make examples'       -- copies examples into the appropriate
                                     directories (no overwrite)
            'make examples-force' -- copies examples into the appropriate
                                     directories (overwrite)
            'make examples-clean' -- remove all examples from the MODEL_DRIVERS,
                                     MODELS, and TESTS directories.

#. Verify that the compilation was successful by running a Test.
  
  .. parsed-literal::
  
        The provided example Tests read in the name of a Model (or Models)
        which they use to perform their calculations.  For most Tests the
        name of the Model can be piped in using an 'echo' command.  For
        example, the following Fortran 90 Test reads in one Model:

  
  .. parsed-literal::
  
        % cd $KD/TESTs/test_Ar_free_cluster_CLUSTER_F90
        % echo "model_Ar_P_MLJ_CLUSTER_C" \| ./test_Ar_free_cluster_CLUSTER_F90

  
  .. parsed-literal::
  
       (See the README files in the Test directories for an explanation of what
        the Tests do.)

#. Each Test (and Model) has its own make file for compiling and linking.
   If changes are made to the code, re-compile (from the $KD
   directory).


----------


**Mixing, shift, table, tail correction, restart, rRESPA info**\ :

This pair style does not support the :doc:`pair\_modify <pair_modify>`
mix, shift, table, and tail options.

This pair style does not write its information to :doc:`binary restart files <restart>`, since KIM stores the potential parameters.
Thus, you need to re-specify the pair\_style and pair\_coeff commands in
an input script that reads a restart file.

This pair style can only be used via the *pair* keyword of the
:doc:`run\_style respa <run_style>` command.  It does not support the
*inner*\ , *middle*\ , *outer* keywords.


----------


Restrictions
""""""""""""


This pair style is part of the KIM package.  It is only enabled if
LAMMPS was built with that package.  See the :ref:`Making LAMMPS <start_3>` section for more info.

This current version of pair\_style kim is compatible with the
openkim-api package version 1.2.0 and higher.

Related commands
""""""""""""""""

:doc:`pair\_coeff <pair_coeff>`

**Default:** none


