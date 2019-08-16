//---------------------------------------------------------------------- define

#define WIZARDS "/etc/wizards"

//-------------------------------------------------------------------- variable

mapping groups = ([
    "(apprentice)" : 1,
    "(wizard)"     : 2,
    "(arch)"       : 3,
    "(admin)"      : 4,
]);

mapping wizards;

//----------------------------------------------------------------- constructor

private void create() {
    if (file_size(WIZARDS) > 0) {
        wizards = restore_variable(read_file(WIZARDS));
    } else {
        wizards = ([]);
    }
}

//-------------------------------------------------------------------- function

string query_group(mixed ob) {
    string group;

    if (objectp(ob)) {
        group = wizards[getuid(ob)];
    } else if (stringp(ob)) {
        group = wizards[ob];
    }

    return group ? group : "(player)";
}

//-----------------------------------------------------------------------------

int query_level(mixed ob) {
    return groups[query_group(ob)];
}

//-----------------------------------------------------------------------------
