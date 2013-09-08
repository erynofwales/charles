/* texture.c
 *
 * Definition of Texture object. Texture objects are attached to scene objects and define its color and shader.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <assert.h>
#include <stdlib.h>

#include "basics.h"
#include "texture.h"


struct _Texture {
    Color color;
};


/*
 * texture_init --
 *
 * Allocate and create a new Texture.
 */
Texture *
texture_init()
{
    Texture *tex = malloc(sizeof(Texture));
    if (tex == NULL) {
        return NULL;
    }

    tex->color = ColorBlack;

    return tex;
}


void
texture_destroy(Texture *tex)
{
    assert(tex != NULL);
    free(tex);
}


Color
texture_get_color(Texture *tex)
{
    assert(tex != NULL);
    return tex->color;
}


void
texture_set_color(Texture *tex, Color color)
{
    assert(tex != NULL);
    tex->color = color;
}
