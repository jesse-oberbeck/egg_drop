#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

int bruteUp(egg *e, int bottom, int *drops)
{
    int count = bottom;
    printf("BOTTOM: %d\n", bottom);
    printf("egg status: %d\n", egg_is_broken(e));
    while(egg_is_broken(e) == 0)
    {
        ++count;
        ++*drops;
        egg_drop_from_floor(e, count);
        checkAndPrint(e, count);
    }
    printf("%d is the maximum safe floor, found after %d drops.\n", count - 1, *drops);
    return(count - 1);
}

int findFloor(egg *e, int *egg_count, long int floors, int *drops)
{
    //int drops = 0;
    int top = floors;
    int bottom = 0;
    int half = floors / 2;
    while((*egg_count > 0) || (top == bottom + 1))
    {
        if(top == bottom + 1)
        {
            printf("%d is the maximum safe floor, found after %d drops.\n", half - 1, *drops);
            return(0);
        }
        if(*egg_count < 2)
        {
            printf("NUMBERS AT EXIT: %d %d\n", top, bottom + 1);
            return(bottom);
        }
        egg_drop_from_floor(e, half);
        ++(*drops);

        if(egg_is_broken(e) != 0)
        {
            printf("#floor %d CRACK\n", half);
            top = half;
            half = half - ((top - bottom) / 2);
            destroy_egg(e);
            e = lay_egg();
            --(*egg_count);
        }
        else
        {
            printf("#floor %d safe\n", half);
            bottom = half;
            half = half + ((top - bottom) / 2);
        }
        
    }
    puts("Leaving find floor");
    return(bottom);
}


int main(int argc, char **argv)
{
    long int floors = 0;
    int egg_count = 0;
    int bottom = 0;
    int drops = 0;

    //Checking for args.
    if(argc <= 1)
    {
        puts("I need at least one egg, and a number of floors.");
        return(1);
    }

    egg_count = strtol(argv[2], NULL, 10);
    floors = strtol(argv[1], NULL, 10);
    printf("eggs: %d\nfloors: %ld\n", egg_count, floors);


    //Checking for invalid egg numbers or over/underflows.
    if(egg_count < 1)
    {
        puts("I need at least one egg...");
        return(1);
    }

    //Make the first egg. MIGHT REMOVE.
    egg *e = calloc(sizeof(struct _egg*), 1);
    e= lay_egg();

    bottom = findFloor(e, &egg_count, floors, &drops);

    if(bottom)
    {
        //Brute force time...
        printf("result: %d\n", bruteUp(e, bottom, &drops) );
    }

    //Removing remaining eggs.
    destroy_egg(e);

}
