/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** defaulttests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "ILib.hpp"
#include "DLLoader.hpp"

static void redirect_all_stdout(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(init_and_use_lib, init_and_use_lib, .init = redirect_all_stdout) {
    {
        DLLoader<ILib> loader("./tests/bar.so");
        std::unique_ptr<ILib> &bar = loader.getInstance();
        bar->init();
        std::cout << bar->getName() << std::endl;
        bar->stop();
    }
    cr_assert_stdout_eq_str("[Start] Loading bar...\n"
                            "Entrypoint for bar!\n"
                            "Bar init\n"
                            "Bar\n"
                            "Bar stop\n"
                            "[End] Unloading bar...\n");
}

Test(open_inexistant_lib, open_inexistant_lib, .init = redirect_all_stdout) {
    try {
        DLLoader<ILib> loader("./tests/doesnotexist.so");
        std::unique_ptr<ILib> &bar = loader.getInstance();
        bar->init();
        std::cout << bar->getName() << std::endl;
        bar->stop();
    } catch (DLLoader<ILib>::DLLoaderException &e) {
        std::cout << e.what() << std::endl;
    }
    cr_assert_stdout_eq_str("./tests/doesnotexist.so: cannot open shared "
                            "object file: No such file or directory\n");
}

Test(use_inexistant_function, use_inexistant_function,
    .init = redirect_all_stdout) {
    try {
        DLLoader<ILib> loader("./tests/nocreate.so");
        std::unique_ptr<ILib> &bar = loader.getInstance();
        (void)bar;
    } catch (DLLoader<ILib>::DLLoaderException &e) {
        std::cout << e.what() << std::endl;
    }
    cr_assert_stdout_eq_str("[Start] Loading bar...\n"
                            "[End] Unloading bar...\n"
                            "./tests/nocreate.so: undefined symbol: create\n");
}

Test(close_lib, close_lib, .init = redirect_all_stdout) {
    try {
        DLLoader<ILib> loader("./tests/bar.so");
        loader.~DLLoader();
    } catch (DLLoader<ILib>::DLLoaderException &e) {
        cr_assert_stdout_eq_str("[Start] Loading bar...\n"
            "[End] Unloading bar...\n");
        cr_assert(true);
        return;
    }
    cr_assert(false);
}
