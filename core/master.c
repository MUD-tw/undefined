#include <runtime_config.h>

//---------------------------------------------------------------------- define

#define BACKBONE "BACKBONE"
#define ROOT     "ROOT"

//-------------------------------------------------------------------- function

string get_bb_uid() {
    return BACKBONE;
}

//-----------------------------------------------------------------------------

string get_root_uid() {
    return ROOT;
}

//-----------------------------------------------------------------------------

int valid_write(string file, mixed ob, string func) {
    switch (func) {
        case "write_file":
            if (file_name(ob) == SIMUL_EFUN_FILE) {
                return 1;
            }
            break;
    }

    return 0;
}

//-----------------------------------------------------------------------------
