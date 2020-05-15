#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "json-c/json.h"

static void glitch_in_the_matrix(struct json_object *jobj, int i, int e)
{
	struct json_object *pos1, *pos2;

	pos1 = json_object_get(json_object_array_get_idx(jobj, i));
	pos2 = json_object_get(json_object_array_get_idx(jobj, e));

	// json_object_array_put_idx decrement the refcount if you replace an
	// element, but we don't whant that.
	//json_object_array_put_idx(jobj, 0, json_object_get(pos2));

	json_object_array_put_idx(jobj, e, pos1);
	json_object_array_put_idx(jobj, i, pos2);

//	printf("%s\n", json_object_to_json_string(jobj));
}

int main(void){

    struct json_object *obj, *array, *tmp, *ttt, *sss, *yu, *po, *ts;
    array_list *list;
    char *test;

    array = json_object_new_array();
    yu = json_object_new_array();
    obj = json_object_new_object();

    tmp = json_object_new_string("test");
    json_object_object_add(obj, "sample", tmp);
    json_object_object_add(obj, "acquisition", json_object_new_int(221));
    json_object_array_add(array, obj);

    obj = json_object_new_object();

    ttt = json_object_new_string("assert");
    json_object_object_add(obj, "tet", ttt);
    json_object_object_add(obj, "acquisition", json_object_new_int(34));
    json_object_array_add(array, obj);

    obj = json_object_new_object();

    sss = json_object_new_string("sss");
    json_object_object_add(obj, "eee", sss);
    json_object_object_add(obj, "acquisition", json_object_new_int(333));
    json_object_array_add(array, obj);
    printf("%s\n", json_object_to_json_string(array));
//    printf("%s\n", json_object_get_string(json_object_array_get_idx(array, 0)));

    obj = json_object_new_object();
    yu = json_object_new_string("yu");
    json_object_object_add(obj, "wakaran", yu);
    json_object_object_add(obj, "acquisition", json_object_new_int(9999));
    json_object_array_add(array, obj);

//    glitch_in_the_matrix(array);

	struct json_object *pos1, *pos2;
//    printf("%i", json_object_array_length(array));
    for(int i = 0; i < json_object_array_length(array); i++){
//        printf("%s", json_object_to_json_string(json_object_array_get_idx(array, i)));
        json_object_object_get_ex(json_object_array_get_idx(array, i), "acquisition", &po);

//        printf("%s\n", json_object_get_string(po));

//        json_object_object_foreach(json_object_array_get_idx(array, i), key, val){
//            printf("%s\n", key);
//            printf("%s\n", json_object_get_string(val));
//        }

        for(int e = i + 1; e < json_object_array_length(array); e++){
//            json_object_object_get_ex(json_object_array_get_idx(array, i), "acquisition", &po);
            json_object_object_get_ex(json_object_array_get_idx(array, e), "acquisition", &ts);


            if(json_object_get_int64(po) < json_object_get_int64(ts)){
//                glitch_in_the_matrix(array, i, e);
	            pos1 = json_object_get(json_object_array_get_idx(array, i));
	            pos2 = json_object_get(json_object_array_get_idx(array, e));
	            json_object_array_put_idx(array, e, pos1);
	            json_object_array_put_idx(array, i, pos2);
            }
        }
        json_object_object_del(json_object_array_get_idx(array, i), "acquisition");
    }


	printf("%s\n", json_object_to_json_string(array));
}
