#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "decimalToFraction.h"

// Recursive function to retrun GCD
long long gcd(long long a, long long b)
{
    if (a == 0)
      return b;
    else if (b == 0)
      return a;
    if (a < b)
      return gcd(a, b % a);
    else
      return gcd(b, a % b);
}

double string2double (char *str) {
    double res = 0;

    char *token_1 = strtok(str, ".");
    char *token_2 = strtok(NULL, ".");

    if (token_2 != NULL) {
        //str is decimal string
        double n_1 = (double)strtol(token_1, NULL, 10);

        int len = strlen(token_2);
        double n_2 = ((double)strtol(token_2, NULL, 10)) / (10 * len);

        res = n_1 + n_2;
    } else {
        // str is integer string
        res = (double)strtol(str, NULL, 10);
    }
    return res;
}

// Function to convert decimal to fraction
fraction decimalToFraction(char *str)
{
    fraction res;
    double number = string2double(str);
    // Fetch integral value of the decimal
    double intVal = floor(number);

    // Fetch fractional part of the decimal
    double fVal = number - intVal;

    // Consider precision value to
    // convert fractional part to
    // integral equivalent
    const long pVal = 1000000000;

    // Calculate GCD of integral
    // equivalent of fractional
    // part and precision value
    long long gcdVal = gcd(round(fVal * pVal), pVal);

    // Calculate num and deno
    res.denominator = pVal / gcdVal;
    res.numerator = (intVal * res.denominator) + round(fVal * pVal) / gcdVal;

    return res;
}

int main (int argc, char *argv[]) {
    fraction res = decimalToFraction(argv[1]);

    printf("numerator: %d\ndenominator: %d\n", res.numerator, res.denominator);
    return 0;
}
