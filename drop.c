#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "egg.h"

void
checkAndPrint(
    egg * e,
    int floor)
{
    if (egg_is_broken(e) != 0)
    {
        printf("#floor %d CRACK\n", floor);
    }
    else
    {
        printf("#floor %d safe\n", floor);
    }
}

int
bruteUp(
    int bottom,
    int *drops,
    int floors)
{
    //"Last resort" used when on the last egg.
    //Brute forces up from last known safe floor.
    egg *e = lay_egg();
    int count = bottom;

    while (egg_is_broken(e) == 0)
    {
        if (count >= floors)
        {
            puts("Can't be broken in this building!");
            destroy_egg(e);
            return (0);
        }
        ++count;
        ++*drops;
        egg_drop_from_floor(e, count);
        checkAndPrint(e, count);
    }
    printf("%d is the maximum safe floor, found after %d drops.\n", count - 1,
           *drops);
    destroy_egg(e);
    return (count - 1);
}

int
findFloor(
    int *egg_count,
    long int floors,
    int *drops,
    int *top)
{
    //Handles initial guessing/calculation while egg count is above 2.
    egg *e = lay_egg();

    *top = floors;
    int bottom = 1;
    int half = floors / 2;

    while ((*egg_count > 2) || (*top == bottom + 1))
    {
        if (*top == bottom + 1)
        {
            printf("%d is the maximum safe floor, found after %d drops.\n",
                   bottom, *drops);
            destroy_egg(e);
            return (0);
        }

        egg_drop_from_floor(e, half);
        ++(*drops);

        if (egg_is_broken(e) != 0)
        {
            printf("#floor %d CRACK\n", half);
            *top = half;
            half = half - ((*top - bottom) / 2);
            destroy_egg(e);
            e = lay_egg();
            --(*egg_count);
        }
        else
        {
            printf("#floor %d safe\n", half);
            bottom = half;
            half = half + ((*top - bottom) / 2);
        }

    }
    destroy_egg(e);
    return (bottom);
}

int
twoEggs(
    int *floors,
    int *bottom,
    int *drops,
    int *egg_count)
{
    //Meant to reduce probable number of guesses, especially in
    //situations with higher numbers of floors, when the egg
    //count is no more and no less than 2.
    if (*egg_count < 2)
    {
        return (*bottom);
    }
    egg *e = lay_egg();
    int currentFloor = *bottom;
    int step = ceil((-1 + (sqrt(1 + 8 * (*floors)))) / 2);

    while (!(egg_is_broken(e)))
    {
        egg_drop_from_floor(e, currentFloor);
        ++(*drops);
        if (egg_is_broken(e))
        {
            destroy_egg(e);
            --(*egg_count);
            return (currentFloor - step);
        }
        --step;
        currentFloor = currentFloor + step;
    }
    return (currentFloor);
}
