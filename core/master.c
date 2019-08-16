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

int valid_seteuid(object target, string euid) {
    if (euid) {
        string uid = getuid(target);

        if (uid != euid && uid != ROOT) {
            return 0;
        }
    }

    return 1;
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

private object connect() {
    return new(CONNECTION);
}

//-----------------------------------------------------------------------------

private void preload(string file) {
    load_object(file);
}

//-----------------------------------------------------------------------------
