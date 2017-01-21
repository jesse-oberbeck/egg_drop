#ifndef EGG_H
#define EGG_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct _egg egg;

egg *lay_egg(
    void);

void destroy_egg(
    egg * e);

bool egg_is_broken(
    egg * e);

void egg_drop_from_floor(
    egg * e,
    size_t floor);

#endif
