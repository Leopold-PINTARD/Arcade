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

static void redirect_all_stdout(void) {
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(default, default, .init = redirect_all_stdout) {
    std::cout << "Hello, World!" << std::endl;
    cr_assert_stdout_eq_str("Hello, World!\n");
}
