.. index:: fix couple/cfd/fluidproperties

fix couple/cfd/fluidproperties command
======================================

Syntax
""""""


.. parsed-literal::

   fix ID group-ID couple/cfd/fluidproperties

* ID, group-ID are documented in :doc:`fix <fix>` command
* couple/cfd/fluidproperties = style name of this fix command


Examples
""""""""


.. parsed-literal::

   fix cfd5 all couple/cfd/fluidproperties

Description
"""""""""""

This fix exchanges fluid properties (density and dynamic viscosity) at the particle locations
from OpenFOAM to LIGGGHTS. These properties become available as :doc:`fix property/atom <fix_property>`
*fluidDensity* and *fluidViscosity*\ , respectively.

Restrictions
""""""""""""


This fix needs a fix couple/cfd before it is defined.

This fix requires forceModel *transferFluidProperties* be active.


