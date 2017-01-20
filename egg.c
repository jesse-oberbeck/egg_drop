#include "egg.h"

static const int SECRET_FLOOR_LIMIT = 84;

struct _egg
{
    int id;
};

egg *lay_egg(void)
{
    egg *e = malloc(sizeof(*e));
    if(e)
    {
        e->id = SECRET_FLOOR_LIMIT;
    }
    return e;
}

void destroy_egg(egg *e)
{
    free(e);
}

bool egg_is_broken(egg *e)
{
    return(e->id == 0);
}

void egg_drop_from_floor(egg *e, size_t floor)
{
    if(e && (size_t)e->id < floor)
    {
        e->id = 0;
    }
}
