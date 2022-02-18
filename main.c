/*
Made by see#0368 (discord)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    int times_S;
    int times_M;
    int times_H;
    int times_D;

    char seconds_A[15];
    char minutes_A[15];
    char hours_A[15];
    char days_A[15];

    uint64_t seconds;
    uint64_t minutes;
    uint64_t hours;
    uint64_t days;

    uint64_t totalseconds;

} times;

void fillTimes(times *mainTimes)
{
    mainTimes->times_S = 0;
    mainTimes->times_M = 0;
    mainTimes->times_H = 0;
    mainTimes->times_D = 0;

    mainTimes->seconds_A[14] = '\0';
    mainTimes->minutes_A[14] = '\0';
    mainTimes->hours_A[14] = '\0';
    mainTimes->days_A[14] = '\0';

    mainTimes->seconds = 0;
    mainTimes->minutes = 0;
    mainTimes->hours = 0;
    mainTimes->days = 0;

    mainTimes->totalseconds = 0;
}

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

void stringToNumber(times *mainTimes)
{
    mainTimes->seconds = (uint64_t)strtoll(mainTimes->seconds_A, 0, 10);
    mainTimes->minutes = (uint64_t)strtoll(mainTimes->minutes_A, 0, 10);
    mainTimes->hours = (uint64_t)strtoll(mainTimes->hours_A, 0, 10);
    mainTimes->days = (uint64_t)strtoll(mainTimes->days_A, 0, 10);
}

/*
Returns a different integer value for different inputs. Writes seconds, minutes, hours and days if found.

    return 0 = Shutdown PC now
    return 1 = No numerical value provided
    return 2 = A time value has been provided twice
    return 3 = Everything went smoothly and shutdown is not set for "now"
*/

int validateInput(times *mainTimes, char *input, int size, bool *hasNumber)
{
    system("cls");

    int cmp = strncmp(input, "now", size);
    if (cmp == 0)
        return 0;

    if (*hasNumber == false)
        return 1;

    for (int i = size - 1; i >= 0; i--)
    {

        switch (input[i])
        {

        case 's':
            mainTimes->times_S++;

            if (mainTimes->times_S == 1)
                getTime(input, mainTimes->seconds_A, i);
            else
                return 2;

            break;

        case 'm':
            mainTimes->times_M++;

            if (mainTimes->times_M == 1)
                getTime(input, mainTimes->minutes_A, i);
            else
                return 2;

            break;

        case 'h':
            mainTimes->times_H++;

            if (mainTimes->times_H == 1)
                getTime(input, mainTimes->hours_A, i);
            else
                return 2;

            break;

        case 'd':
            mainTimes->times_D++;

            if (mainTimes->times_D == 1)
                getTime(input, mainTimes->days_A, i);
            else
                return 2;

            break;

        default: // Do nothing if it's not s, m, h or d
            break;
        }
    }

    stringToNumber(mainTimes);
    return 3;
}
int main(void)
{

    printf("After how long do you want to shut off your computer?\n");
    printf("Examples: \"now, 20h, 6h30m, 2d3h24m30s\"\n");
    printf("\n Made by #see0368 (discord)\n");

    char input[16] = {'\0'};
    scanf("%15s", input);
    input[15] = '\0';

    times mainTimes;
    fillTimes(&mainTimes);

    bool hasNumber = false;
    int size = sizeInput(input, &hasNumber);

    if (size <= 0)
    {
        printf("Just no.\n");
        system("PAUSE");
        return 0;
    }

    int val = validateInput(&mainTimes, input, size, &hasNumber);

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

        // Should fit into uint64_t
        mainTimes.totalseconds = (mainTimes.seconds + mainTimes.minutes * 60 + mainTimes.hours * 60 * 60 + mainTimes.days * 24 * 60 * 60);

        if (mainTimes.totalseconds > 2592000)
        {
            printf("Can't set shut off for longer than 30 days. Why would you even want to?\n");
            system("PAUSE");
            return 0;
        }

        uint32_t finalseconds = (uint32_t)mainTimes.totalseconds;

        if (finalseconds < 5)
        {
            printf("Minimum shutdown time is 5 seconds (or just use \"now\")\n");
            system("PAUSE");
            return 0;
        }

        char command[50] = {'\0'};

        sprintf(command, "shutdown -s -t %u", finalseconds);

        system(command);

        printf("Pc will shutdown in %llu days, %llu, hours, %llu minutes %llu seconds like you requested. :)\n", mainTimes.days, mainTimes.hours, mainTimes.minutes, mainTimes.seconds);
        system("PAUSE");
        return 0;

    default:
        printf("This shouldn't have been reached, you found a bug in my code. Please provide me with your input on discord: see#0368\n");
        printf("Your input: %s\n", input);
        system("PAUSE");
        return 0;
    }
}