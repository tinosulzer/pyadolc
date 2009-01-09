/*----------------------------------------------------------------------------
 ADOL-C -- Automatic Differentiation by Overloading in C++
 File:     int_reverse_t.c
 Revision: $Id: int_reverse_t.c 149 2006-11-08 13:19:25Z kowarz $
 Contents: int_reverse (integer reverse mode tight for bit pattern propagation)
 
 Copyright (c) 2008
               Technical University Dresden
               Department of Mathematics
               Institute of Scientific Computing
  
 This file is part of ADOL-C. This software is provided as open source.
 Any use, reproduction, or distribution of the software constitutes 
 recipient's acceptance of the terms of the accompanying license file.

----------------------------------------------------------------------------*/
#define _INT_REV_ 1
#define _TIGHT_ 1
#include  <adolc/fo_rev.c>
#undef _INT_REV_
#undef _TIGHT_

