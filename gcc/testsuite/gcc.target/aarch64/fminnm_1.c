/* { dg-options "-O2 -ftree-vectorize -fno-vect-cost-model" } */

#pragma GCC target "+nosve"

float
f1 (float x, float *ptr)
{
  for (int i = 0; i < 128; ++i)
    x = __builtin_fminf (x, ptr[i]);
  return x;
}

double
f2 (double x, double *ptr)
{
  for (int i = 0; i < 128; ++i)
    x = __builtin_fmin (x, ptr[i]);
  return x;
}

/* { dg-final { scan-assembler-times {\tfminnm\tv[0-9]+\.4s, v[0-9]+\.4s, v[0-9]+\.4s\n} 1 } } */
/* { dg-final { scan-assembler-times {\tfminnmv\ts[0-9]+, v[0-9]+\.4s\n} 1 } } */
/* { dg-final { scan-assembler-times {\tfminnm\tv[0-9]+\.2d, v[0-9]+\.2d, v[0-9]+\.2d\n} 1 } } */
/* { dg-final { scan-assembler-times {\tfminnmp\td[0-9]+, v[0-9]+\.2d\n} 1 } } */
