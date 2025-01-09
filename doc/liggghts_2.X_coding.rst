LIGGGHTS 2.X Coding Manual
##########################

Introduction:
*************

This is a short coding manual for LIGGGHTS 2.X

A short list of guidelines
**************************

* class data members should be denoted with a **\_** (like *x\_*)
* inline access functions should be used to get access to *x\_*, like *x()*
* class data members , both *x\_particle\_* and *xParticle\_* are allowed
* template params should be written in LARGE\_CAPS
* file names like fix\_mesh\_gran.cpp, mesh\_mover.h
* fix style fix move/mesh/gran is in file fix\_move\_mesh\_gran.cpp/h
* header guard in file fix\_foo\_model.h like LMP\_FIX\_FOO\_MODEL\_H
* coding format should be ANSI
* for fixes, use error->fix\_error to throw error messages in constructors, this enhances object orientation


