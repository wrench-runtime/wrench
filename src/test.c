/* strtod example */
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* strtod */

int main ()
{
  char input[] = "0x02";
  double d1 = strtod (input, NULL);
  printf ("%f\n", d1);
  return 0;
}