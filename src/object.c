/* object.c
 *
 * Definition of scene Objects.
 *
 * Eryn Wells <eryn@erynwells.me>
 */


#include <assert.h>
#include <stdlib.h>
#include "basics.h"
#include "object.h"


struct _Object {
    ObjectType type;
    Vector3 location;
    void *shape;
};

typedef struct _Sphere {
    float radius;
} Sphere;


/*
 * object_init ---
 *
 * Create a new object of the given type.
 */
Object *
object_init(ObjectType type)
{
    Object *obj = malloc(sizeof(Object));
    if (obj == NULL) {
        return NULL;
    }

    switch (type) {
        case ObjectTypeSphere:
            obj->shape = malloc(sizeof(Sphere));
            break;
        default:
            assert(0);
    }

    return obj;
}


/*
 * object_destroy --
 *
 * Destroy the given object.
 */
void
object_destroy(Object *obj)
{
    assert(obj != NULL);
    assert(obj->shape != NULL);

    free(obj->shape);
    free(obj);
}


/*
 * object_get_location --
 * object_set_location --
 *
 * Get and set the location of the object.
 */
Vector3
object_get_location(Object *obj)
{
    assert(obj != NULL);
    return obj->location;
}

void
object_set_location(Object *obj, Vector3 location)
{
    assert(obj != NULL);
    obj->location = location;
}

/*
 * Sphere functions
 */

/*
 * object_sphere_get_radius --
 * object_sphere_set_radius --
 *
 * Get and set the radius of a Sphere object.
 */
float
object_sphere_get_radius(Object *obj)
{
    assert(obj != NULL && obj->type == ObjectTypeSphere);
    return ((Sphere *)obj->shape)->radius;
}

void
object_sphere_set_radius(Object *obj, float r)
{
    assert(obj != NULL && obj->type == ObjectTypeSphere);
    ((Sphere *)obj->shape)->radius = r;
}
