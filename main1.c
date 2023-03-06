#include <stdio.h>
#include "functions.c"

// main for the first exercise
int main()
{
    float test = 203.5;
    printf("\n");
    printf("Original value: %f\n", test);
    char *binaryString = float_to_binary(test);
    //    print the value in binary
    printf("Original value in binary representation as a string: %s\n", binaryString);
    //    switch the significand and exponent in string representation
    char *switchedBinaryString = switch_significand_exponent_string(binaryString);
    //    print the switched value
    printf("Switched exponent and significand as a string: %s\n", switchedBinaryString);
    //    expand the switched string to 64 bits
    char *expand_to_64 = expand_switched_significand_exponent(switchedBinaryString);
    //    print the expanded value
    printf("Expanded value as a string: %s\n", expand_to_64);
    printf("\n");
    //    free allocated memory.
    free(binaryString);
    free(switchedBinaryString);
    free(expand_to_64);
    return 0;
}
