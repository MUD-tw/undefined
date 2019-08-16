inherit "/std/character";
inherit "/std/feature/save";

//----------------------------------------------------------------- constructor

private void create() {
    seteuid(0);
}

//-------------------------------------------------------------------- function

string query_save_file() {
    string uid = getuid();

    return "/var/user/" + uid[0..0] + "/" + uid + "/user";
}

//-----------------------------------------------------------------------------

void setup() {
    seteuid(getuid());

    enable_character();
}

//----------------------------------------------------------- private functions

private void net_dead() {
    object conn = query_temp("CONNECTION");

    if (conn) {
        destruct(conn);
    }
}

//-----------------------------------------------------------------------------
