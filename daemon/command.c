//---------------------------------------------------------------------- define

void init_commands();

//-------------------------------------------------------------------- variable

mapping tables = ([]);

string *paths = ({ "std", "usr", "apr", "wiz", "arch", "adm" });

//----------------------------------------------------------------- constructor

private void create() {
    init_commands();
}

//-------------------------------------------------------------------- function

object find_command(int priv, string verb) {
    while (priv >= 0) {
        string path = paths[priv];
        mapping table = tables[path];
        object command = table[verb];

        if (!command) {
            if (undefinedp(command)) {
                priv--;
                continue;
            } else {
                command = load_object("/cmds/" + path + "/" + verb);
                table[verb] = command;
            }
        }

        return command;
    }

    return 0;
}

//-----------------------------------------------------------------------------

void init_commands() {
    foreach (string path in paths) {
        mapping table = ([]);
        string *files = get_dir("/cmds/" + path + "/*.c");

        if (files) {
            foreach (string file in files) {
                table[file[0..<3]] = 0;
            }
        }

        tables[path] = table;
    }
}

//-----------------------------------------------------------------------------
