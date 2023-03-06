#include <stdio.h>
#include "functions.c"

// main for the second exercise
int main()
{
  float test = 203.5;
  printf("\n");
  printf("Original value: %f\n", test);
  unsigned int u_int = *((unsigned int *)&test);

  // get binary
  printf("Original value in binary representation: ");
  print_binary(u_int);

  // get significand
  unsigned int significand = get_significand(test);
  printf("Significands:\n");
  printf(" 1)Significand of the original value in binary representation: ");
  print_binary(significand);
  printf(" 2)Significand of the original value in unsigned int: %u\n", significand);

  // get exponent
  unsigned int exponent = get_exponent(test);
  printf("Exponent of the original value: ");
  print_binary(exponent);

  // get sign
  unsigned int sign = get_sign(test);
  printf("Sign of the original value: ");
  print_binary(sign);

  // switch significand & get new float (both binary & float representations)
  unsigned int new_float = switch_significand_exponent(test);
  float f = *((float *)&new_float);
  printf("New float:\n");
  printf(" 1)Switched representation of the original value in binary: ");
  print_binary(new_float);
  printf(" 2)Switched representation of the original value in float: %f\n", f);
  printf("\n");
  return 0;
}