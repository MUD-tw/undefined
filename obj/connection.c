inherit "/std/feature/property";
inherit "/std/feature/save";

//---------------------------------------------------------------------- define

private void time_out();

//----------------------------------------------------------------- constructor

private void create() {
    seteuid(0);
}

//-------------------------------------------------------------------- function

string query_save_file() {
    string uid = getuid();

    return "/var/user/" + uid[0..0] + "/" + uid + "/connection";
}

//-----------------------------------------------------------------------------

void setup() {
    seteuid(getuid());

    remove_call_out();
}

//------------------------------------------------------------ private function

private void logon() {
    call_out((: time_out :), 300);
}

//-----------------------------------------------------------------------------

private void net_dead() {
    destruct(this_object());
}

//-----------------------------------------------------------------------------

private void terminal_type(string term) {
    set_temp("TERM", term);
}

//-----------------------------------------------------------------------------

private void time_out() {
    write("登入程序逾時。\n");

    destruct(this_object());
}

//-----------------------------------------------------------------------------
