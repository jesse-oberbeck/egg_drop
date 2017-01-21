#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "egg.h"

void checkAndPrint(egg *e, int floor)
{
    if(egg_is_broken(e) != 0)
    {
        printf("#floor %d CRACK\n", floor);
    }
    else
    {
        printf("#floor %d safe\n", floor);
    }
}

int bruteUp(int bottom, int *drops, int floors)
{
    //"Last resort" used when on the last egg.
    //Brute forces up from last known safe floor.
    egg *e = lay_egg();
    int count = bottom;
    while(egg_is_broken(e) == 0)
    {
        if(count >= floors)
        {
            puts("Can't be broken in this building!");
            destroy_egg(e);
            return(0);
        }
        ++count;
        ++*drops;
        egg_drop_from_floor(e, count);
        checkAndPrint(e, count);
    }
    printf("%d is the maximum safe floor, found after %d drops.\n", count - 1, *drops);
    destroy_egg(e);
    return(count - 1);
}

int findFloor(int *egg_count, long int floors, int *drops, int *top)
{
    //Handles initial guessing/calculation while egg count is above 2.
    egg *e = lay_egg();
    *top = floors;
    int bottom = 1;
    int half = floors / 2;
    while((*egg_count > 2) || (*top == bottom + 1))
    {
        if(*top == bottom + 1)
        {
            printf("%d is the maximum safe floor, found after %d drops.\n", half , *drops);
            destroy_egg(e);
            return(0);
        }

        egg_drop_from_floor(e, half);
        ++(*drops);

        if(egg_is_broken(e) != 0)
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
    puts("Leaving find floor");
    destroy_egg(e);
    return(bottom);
}

int twoEggs(int *floors, int *bottom, int *drops, int *egg_count)
{
    //Meant to reduce probable number of guesses, especially in
    //situations with higher numbers of floors, when the egg
    //count is no more and no less than 2.
    if(*egg_count < 2)
    {
        return(*bottom);
    }
    egg *e = lay_egg();
    int currentFloor = *bottom;
    int step = ceil(( -1 + (sqrt(1 + 8 * (*floors)))) / 2 );
    while(!(egg_is_broken(e)))
    {
        egg_drop_from_floor(e, currentFloor);
        ++(*drops);
        if(egg_is_broken(e))
        {
            destroy_egg(e);
            --(*egg_count);
            return(currentFloor - step);
        }
        --step;
        currentFloor = currentFloor + step;
    }
    return(currentFloor);
}

int main(int argc, char **argv)
{
    long int floors = 0;
    int egg_count = 0;
    //Bottom moves up as the program goes through functions to reduce
    //the number of guesses for each approach.
    int bottom = 1;
    //Top changes with the eggs over 2 approach, but it seems it neither
    //hurts nor helps the outcome.
    int top = 0;
    int drops = 0;

    //Checking for args.
    if(argc <= 1)
    {
        puts("I need at least one egg, and a number of floors.");
        return(1);
    }

    egg_count = strtol(argv[2], NULL, 10);
    floors = strtol(argv[1], NULL, 10);
    printf("eggs: %d\nfloors: %ld\n\n", egg_count, floors);


    //Checking for invalid egg numbers or over/underflows.
    if(egg_count < 1)
    {
        puts("I need at least one egg...");
        return(1);
    }

    if(egg_count > 1)
    {
        bottom = findFloor(&egg_count, floors, &drops, &top);
    }

    if(bottom)
    {
        int remainingFloors = top - bottom;
        bottom = twoEggs(&remainingFloors, &bottom, &drops, &egg_count);
    }

    if(bottom)
    {
        //Brute force time...
        printf("result: %d\n", bruteUp(bottom, &drops, floors) );
    }
}
