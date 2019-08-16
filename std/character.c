inherit "/std/feature/property";

//---------------------------------------------------------------------- define

private int command_hook(object, int, string);

//---------------------------------------------------------- protected function

protected void disable_character() {
    disable_commands();
}

//-----------------------------------------------------------------------------

protected void enable_character() {
    int priv;
    object who = this_object();

    if (userp(who)) {
        priv = USER_D->query_level(who) + 1;

        if (priv > 1) {
            enable_wizard();
        } else {
            disable_wizard();
        }
    }

    enable_commands();
    add_action((: command_hook, who, priv :), "", 1);
    enable_commands(1);
}

//------------------------------------------------------------ private function

private int command_hook(object who, int priv, string arg) {
    string verb = query_verb();
    object command = COMMAND_D->find_command(priv, verb);

    if (command && command->main(who, arg)) {
        return 1;
    }

    return 0;
}

//-----------------------------------------------------------------------------
