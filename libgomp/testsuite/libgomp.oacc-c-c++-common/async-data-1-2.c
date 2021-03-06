/* Verify back to back 'async' operations, two data mappings.

   Make sure that despite two data mappings, this isn't using the libgomp
   'cbuf' buffering.
*/


#include <stdlib.h>


#define N 128


static void
t1 (void)
{
  unsigned int *a, *b;
  int i;
  int nbytes;

  nbytes = N * sizeof (unsigned int);

  a = (unsigned int *) malloc (nbytes);
  b = (unsigned int *) malloc (nbytes);

  for (i = 0; i < N; i++)
    b[i] = a[i] = 3;

#pragma acc parallel async copy (a[0:N], b[0:N])
  for (int ii = 0; ii < N; ii++)
    b[ii] += (a[ii] += 1);

#pragma acc parallel async copy (a[0:N], b[0:N])
  for (int ii = 0; ii < N; ii++)
    b[ii] += (a[ii] += 1);

#pragma acc wait

  for (i = 0; i < N; i++)
    {
      if (a[i] != 5)
	abort ();
      if (b[i] != 12)
	abort ();
    }
}


static void
t2 (void)
{
  unsigned int *a, *b;
  int i;
  int nbytes;

  nbytes = N * sizeof (unsigned int);

  a = (unsigned int *) malloc (nbytes);
  b = (unsigned int *) malloc (nbytes);

#pragma acc data copyin (a[0:N], b[0:N])
  {
    for (i = 0; i < N; i++)
      b[i] = a[i] = 3;

#pragma acc update async device (a[0:N], b[0:N])
#pragma acc parallel async present (a[0:N], b[0:N])
  for (int ii = 0; ii < N; ii++)
    b[ii] += (a[ii] += 1);
#pragma acc update async host (a[0:N], b[0:N])

#pragma acc update async device (a[0:N], b[0:N])
#pragma acc parallel async present (a[0:N], b[0:N])
  for (int ii = 0; ii < N; ii++)
    b[ii] += (a[ii] += 1);
#pragma acc update async host (a[0:N], b[0:N])

#pragma acc wait
  }

  for (i = 0; i < N; i++)
    {
      if (a[i] != 5)
	abort ();
      if (b[i] != 12)
	abort ();
    }
}


int
main (void)
{
  t1 ();

  t2 ();

  return 0;
}
