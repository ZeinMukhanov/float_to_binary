#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ------------------ First Exercise ------------------ //

// function that converts a float to a binary string
char *float_to_binary(float value)
{
    // Allocate memory to store the binary representation.
    char *fl_2_bin = malloc(sizeof(char) * 33);
    // Cast the input float value to an unsigned integer pointer and
    // get the integer representation of the float.
    unsigned int *ptr = (unsigned int *)&value;
    unsigned int bits = *ptr;
    // Convert the integer to binary and store it in the fl_2_bin string.
    for (int i = 31; i >= 0; i--)
    {
        fl_2_bin[i] = (bits % 2) ? '1' : '0';
        bits /= 2;
    }
    // Add the null-terminator to the end of the string.
    fl_2_bin[32] = '\0';
    // Return the binary string representation.
    return fl_2_bin;
}

// function that switches the significand and exponent positions in string representation of float
char *switch_significand_exponent_string(char *value)
{
    char *switched_str = malloc(sizeof(char) * 33); // allocate memory for the new string
    strncpy(switched_str, value, 32);               // copy the first 32 characters of the input string to the new string
    switched_str[32] = '\0';                        // add a null terminator to the new string
    char exponent[9];
    char significand[24];
    strncpy(exponent, &switched_str[1], 8);     // extract the exponent from the input string
    exponent[8] = '\0';                         // add a null terminator to the exponent string
    strncpy(significand, &switched_str[9], 23); // extract the significand from the input string
    significand[23] = '\0';                     // add a null terminator to the significand string
    strncpy(&switched_str[1], significand, 23); // copy the significand to the exponent position in the new string
    strncpy(&switched_str[24], exponent, 8);    // copy the exponent to the significand position in the new string
    return switched_str;
}

// expand the significand to 52 bits and the exponent to 11 bits
char *expand_switched_significand_exponent(char *switched_value)
{
    // Allocate memory for the expanded string.
    char *double_str = malloc(sizeof(char) * 65);

    // Extract the sign bit and copy it to the expanded string.
    strncpy(double_str, switched_value, 1);

    // Extract the exponent and copy it to a separate string.
    char *exponent_str = malloc(sizeof(char) * 8);
    strncpy(exponent_str, switched_value + 24, 8);

    // Extract the significand and copy it to the expanded string.
    strncpy(double_str + 1, switched_value + 1, 23);

    // Add the necessary trailing zeros to the significand.
    for (int i = 0; i < 29; i++)
        double_str[24 + i] = '0';

    // Calculate the new exponent and adjust the bias.
    unsigned int exponent = (unsigned int)strtol(exponent_str, NULL, 2);
    unsigned int new_exponent = exponent + 896; // 1023 - 127 = 896

    // Format the new exponent as a binary string.
    char *new_exponent_str = malloc(sizeof(char) * 11);
    int i = 0;
    while (new_exponent != 0)
    {
        // Compute the least significant bit of the new exponent and store it in the string.
        new_exponent_str[10 - i] = (new_exponent % 2 == 1) ? '1' : '0';
        new_exponent /= 2; // Shift the new exponent right by one bit.
        i++;
    }
    // If the new exponent has fewer than 11 bits, add the necessary leading zeros to the string.
    while (i < 11)
    {
        new_exponent_str[10 - i] = '0';
        i++;
    }

    // Copy the new exponent to the expanded string.
    for (int i = 0; i < 11; i++)
    {
        double_str[53 + i] = new_exponent_str[i];
    }

    // Add a null terminator to the end of the expanded string.
    double_str[64] = '\0';

    // Free the memory allocated for the new exponent string and the exponent string.
    free(new_exponent_str);
    free(exponent_str);

    // Return the expanded string.
    return double_str;
}

// // ------------------ Second Exercise ------------------ //
// print the value of a variable in binary
void print_binary(unsigned int value)
{
    int i;
    for (i = 31; i >= 0; i--)
    {
        printf("%u", (value >> i) & 1);
    }
    printf("\n");
}

// helper function for extraction of bits
unsigned int extract_bits(unsigned int value, unsigned int mask)
{
    return (value & mask);
}

// function that extracts the significand from float using bit operations
unsigned int get_significand(float value)
{
    unsigned int *ptr = (unsigned int *)&value; // casting the floating point into unsigned int
    unsigned int fl_2_u = *ptr;
    unsigned int significand = extract_bits(fl_2_u, 0x007FFFFF);
    return significand;
}

// function that extracts the exponent from float using bit operations
unsigned int get_exponent(float value)
{
    unsigned int *ptr = (unsigned int *)&value; // casting the floating point into unsigned int
    unsigned int fl_2_u = *ptr;
    unsigned int exponent = extract_bits(fl_2_u, 0x7F800000);
    return exponent;
}

// function that extracts the sign from float using bit operations
unsigned int get_sign(float value)
{
    unsigned int *ptr = (unsigned int *)&value; // casting the floating point into unsigned int
    unsigned int fl_2_u = *ptr;
    unsigned int sign_bit = extract_bits(fl_2_u, 0x80000000);
    return sign_bit;
}

// function that switches the significand and exponent positions in float using bit operations using previous functions
unsigned int switch_significand_exponent(float value)
{
    // Convert the float to an unsigned int
    unsigned int *ptr = (unsigned int *)&value; // casting the floating point into unsigned int
    unsigned int fl_2_u = *ptr;

    // Extract significand, exponent, and sign-bit bits
    unsigned int significand = get_significand(value);
    unsigned int exponent = get_exponent(value) >> 23;
    unsigned int sign_bit = get_sign(value) >> 31;

    // swap the exponent bits and significand bits
    unsigned int new_float_as_uint = (sign_bit << 31) | (significand << 8) | exponent;

    return new_float_as_uint;
}
