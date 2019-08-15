#include <function.h>
#include <property.h>

//---------------------------------------------------------------------- define

private mapping _find(mapping, string ref, int);
private mixed _query(mapping, string, int);

//-------------------------------------------------------------------- variable

private mapping properties = ([]);
private nosave mapping temporaries;
private nosave mixed default_object;

//-------------------------------------------------------------------- function

void add(string path, mixed data) {
    mixed previous = query(path, 1);

    set(path, previous ? (previous + data) : data);
}

//-----------------------------------------------------------------------------

void add_temp(string path, mixed data) {
    mapping map;
    mixed previous;

    if (!temporaries) {
        temporaries = ([]);
    }

    map = _find(temporaries, ref path, 1);
    previous = map[path];
    map[path] = previous ? (previous + data) : data;
}

//-----------------------------------------------------------------------------

void delete(string path) {
    mapping map = _find(properties, ref path, 0);

    if (map) {
        map_delete(map, path);
    }
}

//-----------------------------------------------------------------------------

void delete_temp(string path) {
    if (temporaries) {
        mapping map = _find(temporaries, ref path, 0);

        if (map) {
            map_delete(map, path);
        }
    }
}

//-----------------------------------------------------------------------------

varargs mixed query(string path, int raw) {
    mixed data = _query(properties, path, raw);

    if (undefinedp(data) && default_object) {
        return default_object->query(path, raw);
    }

    return data;
}

//-----------------------------------------------------------------------------

mixed query_default_object() {
    return default_object;
}

//-----------------------------------------------------------------------------

mapping query_properties() {
    return properties;
}

//-----------------------------------------------------------------------------

varargs mixed query_temp(string path, int raw) {
    return temporaries ? _query(temporaries, path, raw) : NULL;
}

//-----------------------------------------------------------------------------

void set(string path, mixed data) {
    mapping map = _find(properties, ref path, 1);

    map[path] = data;
}

//-----------------------------------------------------------------------------

void set_default_object(mixed ob) {
    default_object = ob;
}

//-----------------------------------------------------------------------------

void set_temp(string path, mixed data) {
    mapping map;

    if (!temporaries) {
        temporaries = ([]);
    }

    map = _find(temporaries, ref path, 1);
    map[path] = data;
}

//------------------------------------------------------------ private function

private mapping _find(mapping map, string ref path, int flag) {
    int offset = strsrch(path, '/');

    while (offset >= 0) {
        string name = offset ? path[0..(offset - 1)] : "";
        mixed node = map[name];

        if (!mapp(node)) {
            if (flag) {
                node = ([]);
                map[name] = node;
            } else {
                return 0;
            }
        }

        map = node;
        path = path[(offset + 1)..];
        offset = strsrch(path, '/');
    }

    return map;
}

//-----------------------------------------------------------------------------

private mixed _query(mapping map, string path, int raw) {
    map = _find(map, ref path, 0);

    if (map) {
        mixed current = map[path];
        int flag = functionp(current);

        if (!flag || raw) {
            return current;
        } else if (~flag & FP_OWNER_DESTED) {
            return evaluate(current, this_object());
        }
    }

    return NULL;
}

//-----------------------------------------------------------------------------
