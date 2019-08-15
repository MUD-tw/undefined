//-------------------------------------------------------------------- function

int restore() {
    object ob = this_object();
    string file = ob->query_save_file();

    if (file) {
        if (SAVE_D->restore(ob, file)) {
            return 1;
        }

        return restore_object(file);
    }

    return 0;
}

//-----------------------------------------------------------------------------

int save() {
    object ob = this_object();
    string file = ob->query_save_file();

    if (file) {
        if (SAVE_D->save(ob, file)) {
            return 1;
        }

        SAVE_D->assure(file + __SAVE_EXTENSION__);

        return save_object(file);
    }

    return 0;
}

//-----------------------------------------------------------------------------
