/*
*   This small programm checks a credit card number that
*   a user inputs for validity and identifies which card type it is.
*
*   That includes checking the checksum (Luhn’s Algorithm) and general
*   length of the inputted number.
*
*   It prints AMEX, if it's American Express, or MASTERCARD or VISA or INVALID (if there are any problems).
*
*   This programm uses cs50 library that can be found at https://github.com/cs50/libcs50
*   The link to the problem: https://cs50.harvard.edu/x/2023/psets/1/credit/
*
*   ! IMPORTANT !
*   If you are in the process of completing your own cs50x course, please do NOT copy/use this solution.
*   It would go against the principle of academic honesty and would be defeating the purpose
*   of taking the course in the first place.
*
*   Credit: https://github.com/bgnMjr
*/
#include <cs50.h>
#include <stdio.h>

int get_length(long temp);
string get_type(long first);

int main(void)
{
    // Get credit card number from user
    long number;

    do
    {
        number = get_long("Enter credit card number: ");
    }
    while (number <= 0);

    // Get card length
    int length = get_length(number);

    // Invalid number is the one shorter than 13,
    // i.e. not even a VISA
    if (length < 13)
    {
        printf("INVALID\n");
        return 0;
    }

    // Calculate checksum

    long temp = number;
    long sum = 0;
    long first_number = 0;

    for (int i = 0; i < length; i++)
    {
        // Save the first 2 digits for later type check
        if (i == length - 2)
        {
            first_number = temp;
        }

        long last = temp % 10;

        // Get every second from last number
        if (i % 2 != 0)
        {
            long double_last = last * 2;

            if (double_last > 9)
            {
                // If the multiplied number has 2 digits, that is
                // if it's 10 or more, we add its digits
                sum += (double_last % 10) + ((double_last / 10) % 10);
            }
            else
            {
                // If not, just add it to the sum
                sum += double_last;
            }
        }
        else
        {
            // Add the digits that are not multiplied by 2 to the sum
            sum += last;
        }

        // In order to get the next-to-last digit,
        // we divide our temporary variable by 10
        temp /= 10;
    }

    // Check whether checksum is valid
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Print AMEX, MASTERCARD, VISA, or INVALID
    printf("%s\n", get_type(first_number));
}

// Gets length of a provided (long) number
int get_length(long temp)
{
    int n = 1;
    do
    {
        temp /= 10;
        n++;
    }
    while (temp > 10);

    return n;
}

// Get card type according to the first digits provided in the problem
string get_type(long first)
{
    if (first == 34 || first == 37)
    {
        return "AMEX";
    }
    else if (first >= 51 && first <= 55)
    {
        return "MASTERCARD";
    }
    else if ((first / 10) % 10 == 4)
    {
        return "VISA";
    }
    else
    {
        return "INVALID";
    }
}