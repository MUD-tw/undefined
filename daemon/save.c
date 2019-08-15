//---------------------------------------------------------------------- define

#define JOURNALS_FILE __FILE__".journals"

private string load_data(string);
private void save_files(string *, int, int);
private int valid_object(object);

//-------------------------------------------------------------------- variable

function query_data = (: save_object :);
function restore_data = (: restore_from_string :);

int handle;

mapping journals;
mapping pendings = ([]);

//-----------------------------------------------------------------------------

mapping valid_objects = ([
]);

//----------------------------------------------------------------- constructor

private void create() {
    if (file_size(JOURNALS_FILE) >= 0) {
        mixed prev = restore_variable(read_file(JOURNALS_FILE));

        if (mapp(prev)) {
            journals = prev;

            save_files(keys(journals), sizeof(journals), 0);
        } else {
            rm(JOURNALS_FILE);
        }
    }
}

//-------------------------------------------------------------------- function

void assure(string file) {
    if (file_size(file) == -1) {
        string path = "";

        foreach (string name in explode(file, "/")[0..<2]) {
            path += "/" + name;

            if (file_size(path) == -1) {
                mkdir(path);
            }
        }
    }
}

//-----------------------------------------------------------------------------

varargs void flush(int flag) {
    if (sizeof(pendings)) {
        if (journals) {
            journals = journals + pendings;
        } else {
            journals = pendings;
        }

        pendings = ([]);

        write_file(JOURNALS_FILE, save_variable(journals), 1);
    } else if (!flag || !journals) {
        return;
    }

    if (handle) {
        remove_call_out(handle);
        handle = 0;
    }

    if (flag) {
        save_files(keys(journals), sizeof(journals), 0);
    } else {
        handle = call_out((: save_files :), 1, keys(journals),
                                               sizeof(journals),
                                               1);
    }
}

//-----------------------------------------------------------------------------

int restore(object ob, string file) {
    if (valid_object(ob)) {
        string data = load_data(file);

        if (data) {
            evaluate(bind(restore_data, ob), data);
            return 1;
        }
    }

    return 0;
}

//-----------------------------------------------------------------------------

int save(object ob, string file) {
    int flag = valid_object(ob);

    if (flag) {
        pendings[file] = ({ flag, evaluate(bind(query_data, ob)) });
        return 1;
    }

    return 0;
}

//------------------------------------------------------------ private function

private string load_data(string file) {
    mixed info = pendings[file];

    if (info) {
        return info[1];
    }

    if (journals) {
        info = journals[file];

        if (info) {
            return info[1];
        }
    }

    return read_file(file + __SAVE_EXTENSION__);
}

//-----------------------------------------------------------------------------

private void save_files(string *files, int index, int interval) {
    int count;

    while (--index >= 0) {
        string file = files[index], path = file + __SAVE_EXTENSION__;
        mixed info = journals[file];

        assure(path);
        write_file(path, info[1], 1);

        if (++count == 10) {
            if (interval) {
                handle = call_out((: save_files :), interval, files,
                                                              index,
                                                              interval);
                return;
            } else {
                count = 0;
                reset_eval_cost();
            }
        }
    }

    handle = 0;
    journals = 0;

    rm(JOURNALS_FILE);
}

//-----------------------------------------------------------------------------

private int valid_object(object ob) {
    return ob ? valid_objects[base_name(ob)] : 0;
}

//-----------------------------------------------------------------------------
