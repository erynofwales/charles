/* object.h
 *
 * Declaration of scene Objects.
 *
 * Eryn Wells <eryn@erynwells.me>
 */


#ifndef __OBJECT_H
#define __OBJECT_H

#include "basics.h"


typedef enum {
    ObjectTypeSphere = 1,
} ObjectType;

typedef struct _Object Object;


Object *object_init(ObjectType type);
void object_destroy(Object *obj);

Vector3 object_get_location(Object *obj);
void object_set_location(Object *obj, Vector3 location);

// Sphere methods
float object_sphere_get_radius(Object *obj);
void object_sphere_set_radius(Object *obj, float r);


#endif
