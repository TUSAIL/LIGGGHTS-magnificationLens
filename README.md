# LIGGGHTS-magnificationLens 

LIGGGHTS® - LAMMPS Improved for General Granular and Granular Heat Transfer Simulations - is a discrete element method (DEM) particle simulation software.
LIGGGHTS® is part of the [CFDEM®project](https://www.cfdem.com) and is based on the molecular dynamics simulation code [LAMMPS](https://lammps.sandia.gov/).

[![CircleCI](https://circleci.com/gh/ParticulateFlow/LIGGGHTS.svg?style=shield&circle-token=4ca67fb317cf07f8794efaa7b37438f4886d5da3)](https://circleci.com/gh/ParticulateFlow/LIGGGHTS)
[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)

## Disclaimer

> This is an academic adaptation of the LIGGGHTS® software package, released by the
[Department of Particulate Flow Modelling at Johannes Kepler University in Linz, Austria.](https://www.jku.at/pfm)
> LIGGGHTS® and CFDEM® are registered trademarks, and this offering is not approved or
endorsed by DCS Computing GmbH, the official producer of the LIGGGHTS® and CFDEM®coupling software.

## Features
This LIGGGHTS version is designed to be compatible with magnification lens solver [(pfmFOAM-magnificationLens)](https://github.com/TUSAIL/pfmFOAM-magnificationLens). It contains the necessary source code to receive data from CFDEMcoupling-magnification and insert the discrete particles.


## How to cite
Behrad Esgandari, Daniel Queteschiner, Stefan Pirker, and Simon Schneiderbauer. "Discrete magnification lens model: A new hybrid multi-scale modelling method for fluid-particle systems." Powder Technology 445 (2024): 120094.

## Installation
First clone or download LIGGGHTS-magnificationLens repository, then change the folder name to LIGGGHTS.

### Install prerequisites

```bash
sudo apt-get install build-essential cmake openmpi-bin libopenmpi-dev python-dev
```

We recommend installing LIGGGHTS to a directory named `CFDEM`, especially when used with CFDEMcoupling.

```bash
cd
mkdir -p CFDEM
cd CFDEM
```

Clone or download the LIGGGHTS source from the repository.

### Build LIGGGHTS with CMake

```bash
cd LIGGGHTS
mkdir -p src-build
cd src-build
cmake ../src/
make
```

### Add an alias

You may want to create a permanent alias for the executable.

```bash
gedit ~/.bashrc &
alias liggghts='~/CFDEM/LIGGGHTS/src-build/liggghts'
source ~/.bashrc
```


## License

[![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)

- This software is distributed under the [GNU General Public License](https://opensource.org/licenses/GPL-2.0).
- Copyright © 2009-     JKU Linz
- Copyright © 2012-2015 DCS Computing GmbH, Linz
- Copyright © 2003      Sandia Corporation. Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains certain rights in this software.

