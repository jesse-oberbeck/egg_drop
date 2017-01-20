#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "egg.h"

int bruteUp(egg *e)
{
    int count = 0;
    printf("egg status: %d\n", egg_is_broken(e));
    while(egg_is_broken(e) == 0)
    {
        ++count;
        egg_drop_from_floor(e, count);
    }
    return(count - 1);
}

int findFloor(egg **eggs, int *egg_count, int floors)
{
    int drops = 0;
    int top = floors;
    int bottom = 0;
    printf("count: %d\n", *egg_count);
    int half = floors / 2;
    while(*egg_count >= 1)
    {
        if(top == bottom + 1)
        {
            printf("%d is the maximum safe floor, found after %d drops.\n", half - 1, drops);
            return(0);
        }
        egg_drop_from_floor(eggs[*egg_count - 1], half);
        ++drops;

        if(egg_is_broken(eggs[*egg_count - 1]) != 0)
        {
            printf("#floor %d CRACK\n", half);
            top = half;
            half = half - ((top - bottom) / 2);
            destroy_egg(eggs[*egg_count - 1]);
            --(*egg_count);
        }
        else
        {
            printf("#floor %d safe\n", half);
            bottom = half;
            half = half + ((top - bottom) / 2);
        }
    }
    return(1);
}


int main(int argc, char **argv)
{
    int floors = 0;
    int egg_count = 0;

    if(argc <= 1)
    {
        puts("I need at least one egg, and a number of floors.");
        return(1);
    }
    //printf("STRING %s\n", argv[0]);
    egg_count = strtol(argv[2], NULL, 10);
    floors = strtol(argv[1], NULL, 10);
    printf("eggs: %d\nfloors: %d\n", egg_count, floors);
    egg **eggs = calloc(sizeof(struct _egg*), egg_count);
    
    //Fill egg array before testing.
    for(int i = 0; i < egg_count; ++i)
    {
        eggs[i] = lay_egg();
    }


    int bruteFlag = findFloor(eggs, &egg_count, floors);

    if(bruteFlag)
    {
        //Brute force time...
        printf("result: %d\n", bruteUp(eggs[1]) );
    }
    int deleteIndex = 0;
    for(; deleteIndex < egg_count; ++deleteIndex)
    {
        printf("%d\n", deleteIndex);
        destroy_egg(eggs[deleteIndex]);
    }
    free(eggs);
}
