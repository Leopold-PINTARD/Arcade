/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** defaulttests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "DLLoader.hpp"
#include "ILib.hpp"

static void redirect_all_stdout(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(init_and_use_lib, init_and_use_lib, .init = redirect_all_stdout) {
    {
        DLLoader<ILib> loader("./tests/bar.so");
        std::unique_ptr<ILib> &bar = loader.getInstance("create");
        bar->init();
        std::cout << bar->getName() << std::endl;
        bar->stop();
    }
    cr_assert_stdout_eq_str(
        "[Start] Loading bar...\n"
        "Entrypoint for bar!\n"
        "Bar init\n"
        "Bar\n"
        "Bar stop\n"
        "[End] Unloading bar...\n");
}

Test(open_inexistant_lib, open_inexistant_lib, .init = redirect_all_stdout) {
    try {
        DLLoader<ILib> loader("./tests/doesnotexist.so");
        std::unique_ptr<ILib> &bar = loader.getInstance("create");
        bar->init();
        std::cout << bar->getName() << std::endl;
        bar->stop();
    } catch (DLLoader<ILib>::DLLoaderException &e) {
        std::cout << e.what() << std::endl;
    }
    cr_assert_stdout_eq_str(
        "./tests/doesnotexist.so: cannot open shared "
        "object file: No such file or directory\n");
}

Test(use_inexistant_function, use_inexistant_function,
     .init = redirect_all_stdout) {
    try {
        DLLoader<ILib> loader("./tests/nocreate.so");
        std::unique_ptr<ILib> &bar = loader.getInstance("create");
        (void)bar;
    } catch (DLLoader<ILib>::DLLoaderException &e) {
        std::cout << e.what() << std::endl;
    }
    cr_assert_stdout_eq_str(
        "[Start] Loading bar...\n"
        "[End] Unloading bar...\n"
        "./tests/nocreate.so: undefined symbol: create\n");
}

Test(close_lib, close_lib, .init = redirect_all_stdout) {
    try {
        DLLoader<ILib> loader("./tests/bar.so");
        loader.~DLLoader();
    } catch (DLLoader<ILib>::DLLoaderException &e) {
        cr_assert_stdout_eq_str(
            "[Start] Loading bar...\n"
            "[End] Unloading bar...\n");
        cr_assert(true);
        return;
    }
    cr_assert(false);
}

Test(get_instance_twice, get_instance_twice, .init = redirect_all_stdout) {
    {
        DLLoader<ILib> loader("./tests/bar.so");
        std::unique_ptr<ILib> &bar = loader.getInstance("create");
        std::unique_ptr<ILib> &foo = loader.getInstance("create");
        bar->init();
        std::cout << bar->getName() << std::endl;
        bar->stop();
        foo->init();
        std::cout << foo->getName() << std::endl;
        foo->stop();
    }
    cr_assert_stdout_eq_str(
        "[Start] Loading bar...\n"
        "Entrypoint for bar!\n"
        "Bar init\n"
        "Bar\n"
        "Bar stop\n"
        "Bar init\n"
        "Bar\n"
        "Bar stop\n"
        "[End] Unloading bar...\n");
}

Test(switch_lib, switch_lib_then_get_instance, .init = redirect_all_stdout) {
    {
        DLLoader<ILib> loader("./tests/bar.so");
        std::unique_ptr<ILib> &bar = loader.getInstance("create");
        bar->init();
        std::cout << bar->getName() << std::endl;
        bar->stop();
        loader.switchLib("./tests/foo.so");
        std::unique_ptr<ILib> &foo = loader.getInstance("create");
        foo->init();
        std::cout << foo->getName() << std::endl;
        foo->stop();
    }
    cr_assert_stdout_eq_str(
        "[Start] Loading bar...\n"
        "Entrypoint for bar!\n"
        "Bar init\n"
        "Bar\n"
        "Bar stop\n"
        "[End] Unloading bar...\n"
        "[Start] Loading foo...\n"
        "Entrypoint for foo!\n"
        "Foo init\n"
        "Foo\n"
        "Foo stop\n"
        "[End] Unloading foo...\n");
}
