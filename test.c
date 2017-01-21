#include <stdio.h>
#include "egg.h"
#include "drop.h"

int
main (int argc, char **argv)
{
  long int floors = 0;
  int egg_count = 0;

  //Bottom moves up as the program goes through functions to reduce
  //the number of guesses for each approach.
  int bottom = 1;

  //Top changes with the eggs over 2 approach, but it seems it neither
  //hurts nor helps the outcome.
  int top = 2147483647;		//Max for int.
  int drops = 0;

  //Checking for args.
  if (argc <= 1)
    {
      puts ("I need at least one egg, and a number of floors.");
      return (1);
    }

  egg_count = strtol (argv[2], NULL, 10);
  floors = strtol (argv[1], NULL, 10);
  printf ("eggs: %d\nfloors: %ld\n\n", egg_count, floors);


  //Checking for invalid egg numbers or over/underflows.
  if (egg_count < 1)
    {
      puts ("I need at least one egg...");
      return (1);
    }

  if (egg_count > 2)
    {
      bottom = findFloor (&egg_count, floors, &drops, &top);
    }

  if (bottom)
    {
      int remainingFloors = top - bottom;

      bottom = twoEggs (&remainingFloors, &bottom, &drops, &egg_count);
    }

  if (bottom)
    {
      //Brute force time...
      bruteUp (bottom, &drops, floors);
    }
}
