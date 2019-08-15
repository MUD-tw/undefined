#include <localtime.h>

//-------------------------------------------------------------------- function

void log_file(string file, string text) {
    int *now = localtime(time());

    write_file("/var/log/" + file, sprintf("%d%02d%02d:%02d%02d%02d %s\n",
                                           now[LT_YEAR],
                                           now[LT_MON] + 1,
                                           now[LT_MDAY],
                                           now[LT_HOUR],
                                           now[LT_MIN],
                                           now[LT_SEC],
                                           text));
}

//-----------------------------------------------------------------------------
