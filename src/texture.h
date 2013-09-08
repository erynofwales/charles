/* texture.h
 *
 * Declaration of Texture object. Texture objects are attached to scene objects and define its color and shader.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __TEXTURE_H__
#define __TEXTURE_H__


typedef struct _Texture Texture;

Texture *texture_init();
void texture_destroy(Texture *tex);
Color texture_get_color(Texture *tex);
void texture_set_color(Texture *tex, Color color);


#endif
