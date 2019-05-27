/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** fais les tests unitaires oui
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "mysh.h"

void redirect_all_std (void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test (my_strlen, string, .init = redirect_all_std)
{
    int i = my_strlen("ABC");

    cr_assert_eq(i, 3);
}

Test (my_strcpy, string, .init = redirect_all_std)
{
    char str[] = "bonjour";
    char *dest = malloc(sizeof(char) * 8);

    cr_assert_eq(str, my_strcpy(str, dest));
}

Test (my_putchar, simple_character, .init = redirect_all_std)
{
    my_putchar('a');
    cr_assert_stdout_eq_str("a");
}

Test (my_putstr, simple_character, .init = redirect_all_std)
{
    my_putstr("test");
    cr_assert_stdout_eq_str("test");
}

Test (my_put_nbr, simple_character, .init = redirect_all_std)
{
    my_put_nbr(32);
    cr_assert_stdout_eq_str("32");
}

Test (my_put_nbr, minus_character, .init = redirect_all_std)
{
    my_put_nbr(-32);
    cr_assert_stdout_eq_str("-32");
}

Test (my_getnbr, simple_character, .init = redirect_all_std)
{
    char str[] = "32";

    cr_assert_eq(my_getnbr(str), 32);
}

Test (my_getnbr, minus_character, .init = redirect_all_std)
{
    char str[] = "-32";

    cr_assert_eq(my_getnbr(str), -32);
}

Test(my_printf , simple_string , .init = redirect_all_std)
{
    my_printf("hello  world");
    cr_assert_stdout_eq_str("hello  world");
}

Test(my_printf, s_flag, .init = redirect_all_std)
{
    my_printf("%s", "hello  world");
    cr_assert_stdout_eq_str("hello  world");
}

Test(my_printf, i_flag, .init = redirect_all_std)
{
    my_printf("%i", 42);
    cr_assert_stdout_eq_str("42");
}

Test(my_printf, d_flag, .init = redirect_all_std)
{
    my_printf("%d", 50);
    cr_assert_stdout_eq_str("50");
}

Test(my_printf, S_flag, .init = redirect_all_std)
{
    char str[3] = "ab";

    str[0] = 20;
    my_printf("%S", str);
    cr_assert_stdout_eq_str("\\24b");
}

Test(my_printf, multiple_flags, .init = redirect_all_std)
{
    my_printf("%s%c%i", "Bonjour", 'A', 42);
    cr_assert_stdout_eq_str("BonjourA42");
}

Test(my_printf, a_real_test, .init = redirect_all_std)
{
    my_printf("%i,%s test test , %s%c %%", 3000, "issou", "la chancla", 'A');
    cr_assert_stdout_eq_str("3000,issou test test , la chanclaA %");
}

Test(my_printf, wrong_flag, .init = redirect_all_std)
{
    my_printf("%y", 42);
    cr_assert_stdout_eq_str("%y");
}

Test(my_printf, o_flag, .init = redirect_all_std)
{
    my_printf("%o", 42);
    cr_assert_stdout_eq_str("52");
}

Test(my_printf, c_flag, .init = redirect_all_std)
{
    my_printf("%c", 'A');
    cr_assert_stdout_eq_str("A");
}
Test(my_printf, modulo_flag, .init = redirect_all_std)
{
    my_printf("%%");
    cr_assert_stdout_eq_str("%");
}

Test (my_putchar_err, simple_character, .init = redirect_all_std)
{
    my_putchar_err('a');
    cr_assert_stderr_eq_str("a");
}

Test (my_putstr_err, simple_character, .init = redirect_all_std)
{
    my_putstr_err("test");
    cr_assert_stderr_eq_str("test");
}

Test (my_strcat, simple_character)
{
    char *src = "Oui le ";
    char *dest = "test";
    char *res = my_strcat(src, dest);

    cr_assert(res, "Oui le test");
}

Test(my_itoa, simple_test)
{
    int test = 42;
    char *res = my_itoa(test);

    cr_assert(res, "42");
}

Test(my_strcmp, valid)
{
    cr_assert_eq(my_strcmp("Oui", "Oui"), 0);
}

Test(my_strcmp, not_valid)
{
    cr_assert_eq(my_strcmp("Oui", "Non"), 1);
}

Test(my_strcmp, null)
{
    cr_assert_eq(my_strcmp("Oui", NULL), -1);
}

Test(my_strcmpn, valid)
{
    cr_assert_eq(my_strcmpn("Oui", "Oui", 3), 0);
}

Test(my_strcmpn, valid_first_char)
{
    cr_assert_eq(my_strcmpn("Oui", "Ounon", 2), 0);
}

Test(my_strcmpn, null)
{
    cr_assert_eq(my_strcmpn("Oui", NULL, 42), -1);
}

Test(my_strcmpn, wrong_first_char)
{
    cr_assert_eq(my_strcmpn("Oui", "Nui", 3), 1);
}

Test(my_strcmpn, n_equal_0)
{
    cr_assert_eq(my_strcmpn("Oui", "Oui", 0), -1);
}

Test(get_name, get_name_from_env)
{
    char *env = "TEST=abc";

    cr_assert(get_name(env), "TEST");
}

Test(print_unvalid, print_errors, .init = redirect_all_std)
{
    print_unvalid("./wrong_arch");
    cr_assert_stderr_eq("./wrong_arch: Exec format error."
                        "Binary file not executable.\n");
}

Test(check_basic_errors, redirections)
{
    cr_assert_eq(check_basic_errors("ls >>>> tamere"), 1);
}

Test(check_basic_errors, separators)
{
    cr_assert_eq(check_basic_errors("ls &|"), 1);
}

Test(check_basic_errors, valid)
{
    cr_assert_eq(check_basic_errors("ls -la ; echo oui && cd .."), 0);
}

Test(check_inhibitor, test_error)
{
    char *line = strdup("\\\\");
    int res = check_inhibitor(line);

    cr_assert_eq(res, 84);
    free(line);
}

Test(check_inhibitor, test_error1)
{
    char *line = strdup("\\");
    int res = check_inhibitor(line);

    cr_assert_eq(res, 0);
    free(line);
}
