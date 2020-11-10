/* { dg-do run } */
/* { dg-options "-O3 -march=z14 -mzarch --save-temps" } */
#include <assert.h>
#include <stdint.h>

__attribute__ ((noipa)) static uint16_t
long_double_to_u16 (long double x)
{
  return x;
}

/* { dg-final { scan-assembler-times {\n\tclfxbr\t} 1 } } */

int
main (void)
{
  assert (long_double_to_u16 (42.L) == 42);
  /* Not (-42 & 0xffff) due to loss of precision.  */
  assert (long_double_to_u16 (-42.L) == 0);
}