/*
** EPITECH PROJECT, 2019
** minishell1
** File description:
** minishell1's header
*/

#ifndef sh_h
#define sh_h

#include <errno.h>
#include <dirent.h>

#include "op_section.h"
#include "tree.h"

static const char *shell_command[] = {"cd", "setenv", "unsetenv", "exit",
                                    "echo", "alias", "history", "where",
                                    "which"};

static const char *BACKUP_PATH = "/bin/";

typedef struct shell {
    char **b_envp;
    char **env_dup;
    char **path;
    char **history;
    char *home;
    char *base_line;
    char *alias_path;
    int *hist_flag;
    int skip;
    int return_value;
    int n_read;
    int command_lenght;
    int dir_error;
    int errno_value;
    int history_pointer;
    int history_adder;
    int detect_free;
    int doors;
    int *sep_list;
} shell_t;

typedef struct fds {
    int *pipefd;
    int nb_pipes;
    int count;
} fd_t;

    /* src */

        /* commands */

        void exec_functions(shell_t *);
        int get_semis(char *);
        char **get_commands_from_input(char *, shell_t *);
        int execute_command(char *, char **, shell_t *, tree_t **);
        int get_spaces(char *);
        char *get_bin(char *);
        char **get_args(char *);
        char *getnewline(shell_t *);
        int is_a_wave(char *, char **, shell_t *);
        void check_status(int, shell_t *);
        char *get_home(char **);
        void print_error(char *, shell_t *);
        int is_valid_input(char *, shell_t *, char **, tree_t **);
        char *check_aliases(char *, char *);
        int check_redirections(char *, char **, shell_t *, tree_t *);
        int handle_input(char **strings, shell_t *shell);
        int is_completed(char *, char **, shell_t *, tree_t **);
        char ***get_arguments(char **);
        int list_functions(tree_t *, char **, shell_t *);
        int seek_command(char *, char **, shell_t *, tree_t **);
        char **setup_commands(char *);
        int is_a_pipe(char *, shell_t *, tree_t **);
        int doors_and_or(shell_t *, tree_t *);
        int *setup_sep_list(tree_t *);
        void handle_dups(fd_t *, tree_t **);
        int env_slashed(char **, char *);

        /* redirections */

        int simple_redirection(int, char *);
        int double_redirection(int, char *);
        int simple_input(int, char *);
        int double_input(int, char *);
        int redirect_by_index(int, char *, int);

        /* built_in */

        int check_other_functions(char *, shell_t *, char **);
        int my_echo(shell_t *, char **);
        int functions(char *, shell_t *, char **, tree_t **);
        char *update_wave(char *, shell_t *);
        int is_a_binary(char *, char **, shell_t *, tree_t **);
        char **remove_index(char *, shell_t *);
        char **fill_env(char **, char *, char *, shell_t *);
        void my_exit(char **, shell_t *);
        char *get_name(char *);
        char *find_old_pwd(shell_t *);
        int my_setenv(shell_t *, char **);
        int my_cd(shell_t *, char **);
        int my_unsetenv(shell_t *, char **);

        /* infos */

        void update_shell(shell_t *, char *);
        char **malloc_args(char *, char *, int);
        char **get_replacement_env(shell_t *);
        char **malloc_array(char **, int);
        void free_tab(char **);
        void free_utility(char *, char **);
        void free_shell(shell_t *);
        void update_path(char *, char *, shell_t *);
        int check_strings(char **);
        int setenv_err(void);
        char *my_calloc(int);
        int get_exit_value(char *, shell_t *);
        char *get_pwd(void);
        int update_env_by_str(shell_t *, char *, char *);
        char **realloc_tab(char **, char *);
        char *get_value(char *, char);

        /* setup */

        shell_t *get_struct(char **);
        int get_indexes(char **);
        void fill_path(shell_t *, char **);
        void remove_oldpwd(shell_t *);
        char **path_replacement(void);

        /* unused */

        char **add_ls_color(char **);
        char **add_endline(char **);

        /* history */

        void get_and_print_time(char *str_time);
        void disp_start_spaces(int i);
        void display_history(char **, shell_t *);
        void fill_history_file(char **, char **, shell_t *);
        int setup_basic_hist_var(shell_t *);
        void check_history_flags(shell_t *, char **);
        void reinit_hist_var(shell_t *);
        int which_flag(shell_t *, char ***, char **);
        int history_flag_c(char **);
        void history_flag_r(char **, shell_t *);
        void history_flag_h(char **, shell_t *);
        void history_flag_maj_m(char ***, shell_t *);
        int for_number(char **, shell_t *);
        void last_hist(char **, char **, shell_t *, int);
        int search_in_history(char ***, shell_t *, char **);
        void complex_flag(char ***, char **, shell_t *);
        int check_flags(char **, shell_t *);

        /* inhibitor */

        char *is_inhibitor(char *);
        int check_inhibitor(char *);
        char **get_args_inhibitor(char *);
        int space_is_inhibitor(char *);
        char *convert_arg_ini(char *);
        int check_is_ini(shell_t *);

        /* backtick */

        int error_backchar(shell_t *shell);

        /* alias */

        char ***open_alias(char *);
        void my_alias(shell_t *, char **);
        char *get_alias_path(void);
        char *get_value_alias(char *);
        char *get_name_alias(char *);

        /* globings */

        char *error(char *, char *);
        char *check_hook(char *, char *);
        char *check_interrogation_point(char *, char *);
        int fill_new_string(char **, char **, shell_t *);
        void compare_str_star(char *, char **, char *);
        void find_complete_str(struct dirent *, char *, char **, char *);
        void check_last_char(char *);

        /* other optional function */

        void is_repeat(shell_t *, char **);
        void my_where(shell_t *, char **);
        void my_which(shell_t *, char **);

    /* lib */

char *my_strcat_with_space(char *dest, char const *src);
void delete_char(char *str, char chara);
int my_strcmp(char *const str, char *const cmp);
int my_getnbr(char *str);
int my_ngetnbr(char *str, int i);
void my_putchar_err(char c);
int my_putstr_err(char const *str);
int my_strcmpn(char *const str, char *const cmp, int n);
char *my_strcat(char *dest, char const *src);
int my_putstr_octal(char const *str);
char *my_strcat_env(char *dest, char const *src);
char *my_binary_convertor(unsigned int nb);
int my_printf(const char *str, ...);
void get_addr_ptr(char *str);
char *my_revstr(char *str);
char *my_strclean(char *line);
void my_put_nbr(int nb);
char *my_memset(char *res, char c, int size);
short *decimal_to_binary(int number);
int my_strlen(char const *str);
int my_getnbr(char *const str);
char *my_itoa(int number);
char *my_replace(char *str, char target, char replace);
char **str_to_tab(char *line, char delim);
void my_octal_convertor(unsigned int nb);
void my_hex_convertor(unsigned int nb);
void my_hex_convertor_min(unsigned int nb);
void get_addr_ptr(char *str);
int check_null_ptr(char *str);
void my_putchar(char c);
int my_putstr(char const *str);
char *my_strcpy(char *dest, char const *src);
int my_natoi(char const *str, int i);
char **spe_realloc(char **tab, int size);
char *my_strncat(char *dest, char const *src, int i);
int my_strcharcmp(char const *s1, char const *s2, char const stop_str, int *i);
int my_strstarcmp(char const *s1, char const *s2, char const stop_str, int *i);
int my_stricmp(char *const str, char *const cmp, int i);

#endif /* !sh.h */
