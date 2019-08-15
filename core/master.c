#include <runtime_config.h>

//---------------------------------------------------------------------- define

#define BACKBONE "BACKBONE"
#define ROOT     "ROOT"
#define SYSTEM   "SYSTEM"

//-------------------------------------------------------------------- function

string creator_file(string file) {
    string *names = explode(file, "/");

    switch (names[0]) {
        case "daemon":
            return ROOT;
    }

    return SYSTEM;
}

//-----------------------------------------------------------------------------

string * epilog() {
    return ({
        SAVE_D,
    });
}

//-----------------------------------------------------------------------------

string get_bb_uid() {
    return BACKBONE;
}

//-----------------------------------------------------------------------------

string get_root_uid() {
    return ROOT;
}

//-----------------------------------------------------------------------------

int valid_bind(object ob, object from, object to) {
    return geteuid(ob) == ROOT;
}

//-----------------------------------------------------------------------------

int valid_write(string file, mixed ob, string func) {
    string id = geteuid(ob);

    if (id == ROOT) {
        return 1;
    }

    switch (func) {
        case "save_object":
            if (pcre_match(file_name(ob), "^/obj/")) {
                return 1;
            }
            break;
        case "write_file":
            if (file_name(ob) == SIMUL_EFUN_FILE) {
                return 1;
            }
            break;
    }

    return 0;
}

//------------------------------------------------------------ private function

private void preload(string file) {
    load_object(file);
}

//-----------------------------------------------------------------------------
