/*
Made by see#0368 (discord)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>

// Finds the length of input but also sets a boolean if it has found any numerical value inside the input.
int sizeInput(char *input, bool *hasNumber)
{
    int size = 0;

    while (input[size] != '\0')
    {
        size++;

        if (!(isalpha(input[size - 1])))
            *hasNumber = true;
    }

    input[size] = '\0';
    return size;
}

void getTime(char *input, char *time_A, int i)
{

    int lauf_time = i - 1; // One spot before the found time
    int duration_time = 0; // Length of time

    // This while-loop finds out the length of the time
    while (!(isalpha(input[lauf_time])) && lauf_time > -1)
    {
        duration_time++;
        lauf_time--;
    }

    // Writes the time into given Array
    for (int j = 0; j < duration_time; j++)
    {
        time_A[j] = input[lauf_time + (j + 1)];
    }

    time_A[duration_time] = '\0';
}

bool stringToLongLong(long long *time, char *time_A)
{
    *time = (long long)strtol(time_A, 0, 10);

    if (*time == LONG_MIN || *time == LONG_MAX)
    {
        if (errno == ERANGE)
        {
            return true;
        }
    }

    return false;
}

/*
Returns a different integer value for different inputs. Writes seconds, minutes, hours and days if found.

    return 0 = Shutdown PC now
    return 1 = No numerical value provided
    return 2 = A time value has been provided twice
    return 3 = Too big of a number
    return 4 = Everything went smoothly and shutdown is not set for "now"
*/

int validateInput(char *input, int size, long long *days, long long *hours, long long *minutes, long long *seconds, char *seconds_A, char *minutes_A, char *hours_A, char *days_A, bool *hasNumber)
{
    system("cls");

    int cmp = strncmp(input, "now", size);
    if (cmp == 0)
        return 0;

    if (*hasNumber == false)
        return 1;

    for (int i = size - 1; i >= 0; i--)
    {

        int times_S = 0;
        int times_M = 0;
        int times_H = 0;
        int times_D = 0;

        switch (input[i])
        {

        case 's':
            times_S++;

            if (times_S == 1)
                getTime(input, seconds_A, i);
            else
                return 1;

            break;

        case 'm':
            times_M++;

            if (times_M == 1)
                getTime(input, minutes_A, i);
            else
                return 1;

            break;

        case 'h':
            times_H++;

            if (times_H == 1)
                getTime(input, hours_A, i);
            else
                return 1;

            break;

        case 'd':
            times_D++;

            if (times_D == 1)
                getTime(input, days_A, i);
            else
                return 1;

            break;

        default: // Do nothing if it's not s, m, h or d
            break;
        }
    }

    if (stringToLongLong(seconds, seconds_A) == true)
        return 2;

    if (stringToLongLong(minutes, minutes_A) == true)
        return 2;

    if (stringToLongLong(hours, hours_A) == true)
        return 2;

    if (stringToLongLong(days, days_A) == true)
        return 2;

    return 3;
}
int main()
{

    printf("After how long do you want to shut off your computer?\n");
    printf("Examples: \"now, 20h, 6h30m, 2d3h24m30s\"\n");
    printf("\n Made by #see0368 (discord)\n");

    char input[16] = {'\0'};
    scanf("%15s", input);
    input[15] = '\0';

    long long days = 0;
    long long hours = 0;
    long long minutes = 0;
    long long seconds = 0;
    long long totalseconds = 0;

    char seconds_A[15] = {'\0'};
    char minutes_A[15] = {'\0'};
    char hours_A[15] = {'\0'};
    char days_A[15] = {'\0'};

    bool hasNumber = false;
    int size = sizeInput(input, &hasNumber);

    if (size <= 0)
    {
        printf("Just no.\n");
        system("PAUSE");
        return 0;
    }

    int val = validateInput(input, size, &days, &hours, &minutes, &seconds, seconds_A, minutes_A, hours_A, days_A, &hasNumber);

    switch (val)
    {
    case 0:

        printf("Pc will shut down any second!");
        system("shutdown -s -t 3");
        return 0;

    case 1:

        printf("You didn't specify any times so how will I shutdown for: \n");
        printf("%s?\n", input);
        printf("%s Bananas? Eggs? Watermelons?\n", input);
        system("PAUSE");
        return 0;

    case 2:

        printf("Why the fuck do you want a single measurement twice? I'm not a calculator\n");
        system("PAUSE");
        return 0;

    case 3:

        printf("Way too big of a number bro\n");
        system("PAUSE");
        return 0;

    case 4:

        totalseconds = (seconds + minutes * 60 + hours * 60 * 60 + days * 24 * 60 * 60);

        if (totalseconds >= LONG_MAX)
        {
            printf("Way too big of a number bro\n");
            system("PAUSE");
            return 0;
        }

        if (totalseconds > 2592000)
        {
            printf("Can't set shut off for longer than 30 days. Why would you even want to?\n");
            system("PAUSE");
            return 0;
        }

        long final_seconds = (long)totalseconds;

        if (final_seconds < 5)
        {
            printf("Minimum shutdown time is 5 seconds (or just use \"now\")\n");
            system("PAUSE");
            return 0;
        }

        char command[50] = {'\0'};

        sprintf(command, "shutdown -s -t %ld", final_seconds);

        system(command);

        printf("Pc will shutdown in %lld days, %lld, hours, %lld minutes %lld seconds like you requested. :)\n", days, hours, minutes, seconds);
        system("PAUSE");
        return 0;

    default:
        printf("This shouldn't have been reached, you found a bug in my code. Please provide me with your input on discord: see#0368\n");
        printf("Your input: %s\n", input);
        system("PAUSE");
        return 0;
    }
}