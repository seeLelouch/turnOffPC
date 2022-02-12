/*
Made by see#0368 (discord)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

int size_input(char *input)
{
    int size = 0;
    while (input[size] != '\0')
    {
        size++;
    }
    
    return size;
}

int validate_input(char *input, int length, long *days, long *hours, long *minutes, long *seconds, char *seconds_A, char *minutes_A, char *hours_A, char *days_A)
{
    system("cls");

    int cmp = strncmp(input, "now", length);
    if (cmp == 0)
    {
        return 0;
    }

    int times_s = 0;
    int times_m = 0;
    int times_h = 0;
    int times_d = 0;

    for (int i = length; i >= 0; i--)
    {
        if (input[i] == 's')
        {
            times_s++;
            if (times_s == 1)
            {

                int lauf_s = i - 1;
                int duration_s = 0;

                while (!(isalpha(input[lauf_s])) && lauf_s > -1)
                {
                    duration_s++;
                    lauf_s--;
                }

                for (int j = 0; j < duration_s; j++)
                {
                    seconds_A[j] = input[lauf_s + (j + 1)];
                }

                seconds_A[duration_s] = '\0';
                *seconds = strtol(seconds_A, 0, 10);

                if (*seconds == LONG_MIN || *seconds == LONG_MAX)
                {
                    if (errno == ERANGE)
                    {
                        printf("Way too big of a number bro\n");
                        return 8;
                    }
                }
            }
            else
            {
                return 4;
            }
        }

        if (input[i] == 'm')
        {
            times_m++;
            if (times_m == 1)
            {

                int lauf_m = i - 1;
                int duration_m = 0;
                while (!(isalpha(input[lauf_m])) && lauf_m > -1)
                {
                    duration_m++;
                    lauf_m--;
                }

                for (int k = 0; k < duration_m; k++)
                {
                    minutes_A[k] = input[lauf_m + (k + 1)];
                }
                minutes_A[duration_m] = '\0';
                *minutes = strtol(minutes_A, 0, 10);
                if (*minutes == LONG_MIN || *minutes == LONG_MAX)
                {
                    if (errno == ERANGE)
                    {
                        printf("Way too big of a number bro\n");
                        return 8;
                    }
                }
            }
            else
            {
                return 4;
            }
        }

        if (input[i] == 'h')
        {
            times_h++;
            if (times_h == 1)
            {

                int lauf_h = i - 1;
                int duration_h = 0;
                while (!(isalpha(input[lauf_h])) && lauf_h > -1)
                {
                    duration_h++;
                    lauf_h--;
                }

                for (int l = 0; l < duration_h; l++)
                {
                    hours_A[l] = input[lauf_h + (l + 1)];
                }
                hours_A[duration_h] = '\0';
                *hours = strtol(hours_A, 0, 10);
                if (*hours == LONG_MIN || *hours == LONG_MAX)
                {
                    if (errno == ERANGE)
                    {
                        printf("Way too big of a number bro\n");
                        return 8;
                    }
                }
            }
            else
            {
                return 4;
            }
        }

        if (input[i] == 'd')
        {
            times_d++;
            if (times_d == 1)
            {

                int lauf_d = i - 1;
                int duration_d = 0;
                while (!(isalpha(input[lauf_d])) && lauf_d > -1)
                {
                    duration_d++;
                    lauf_d--;
                }

                for (int m = 0; m < duration_d; m++)
                {
                    days_A[m] = input[lauf_d + (m + 1)];
                }
                days_A[duration_d] = '\0';
                *days = strtol(days_A, 0, 10);
                if (*days == LONG_MIN || *days == LONG_MAX)
                {
                    if (errno == ERANGE)
                    {
                        printf("Way too big of a number bro\n");
                        return 8;
                    }
                }
            }
            else
            {
                return 4;
            }
        }
    }

    if (*seconds == 0 && *minutes == 0 && *days == 0 && *hours == 0)
        return 1;

    return 2;
}

int main()
{
    printf("After how long do you want to shut off your computer?\n");
    printf("Examples: \"now, 20h, 6h30m, 2d3h24m30s\"\n");

    char input[16] = {0};
    scanf("%15s", input);
    input[15] = '\0';

    long days = 0;
    long hours = 0;
    long minutes = 0;
    long seconds = 0;

    char seconds_A[15] = {0};
    char minutes_A[15] = {0};
    char hours_A[15] = {0};
    char days_A[15] = {0};

    int length = size_input(input);
    if (length <= 0)
    {
        printf("Just no.\n");
        return 0;
    }

    int when = validate_input(input, length, &days, &hours, &minutes, &seconds, seconds_A, minutes_A, hours_A, days_A);

    if (when == 0)
    {
        printf("Pc will shut down any second, this is so the program won't damage your pc.");
        system("shutdown -s -t 3");
        return 0;
    }
    if (when == 1)
    {
        printf("You didn't specify any times so how will I shutdown for: \n");
        printf("%s?\n", input);
        printf("%s Bananas? Eggs? Watermelons?\n", input);
        system("PAUSE");
        return 0;
    }

    if (when == 2)
    {

        if (days > 30 || hours > 720 || minutes > 43200 || seconds > 2592000)
        {
            printf("Can't set shut off for longer than 30 days. Why would you even want to?\n");
            system("PAUSE");
            return 0;
        }

        long long totalseconds = (long long)(seconds + minutes * 60 + hours * 60 * 60 + days * 24 * 60 * 60);

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

        long t_seconds = (long)totalseconds;

        if (t_seconds < 5)
        {
            printf("Minimum shutdown time is 5 seconds (or just use \"now\")\n");
            system("PAUSE");
            return 0;
        }

        char *command = calloc(50, sizeof(char));

        sprintf(command, "shutdown -s -t %ld", t_seconds);

        system(command);
        free(command);

        printf("Pc will shutdown in %ld days, %ld, hours, %ld minutes %ld seconds like you requested. :)\n", days, hours, minutes, seconds);
        system("PAUSE");
        return 0;
    }

    if (when == 4)
    {
        printf("Why the fuck do you want a single measurement twice? I'm not a calculator\n");
        system("PAUSE");
        return 0;
    }

    if (when == 8)
    {
        system("PAUSE");
        return 0;
    }
    return 0;
}