/*
** EPITECH PROJECT, 2019
** minishell2
** File description:
** binary_trees
*/

#ifndef tree_h
#define tree_h

typedef struct tree {
    struct tree *left;
    struct tree **right;
    char *line;
    int redir_type;
    int separator_type;
} tree_t;

    /* init */

    tree_t *create_tree_from_input(char *);
    int is_a_separator(char *, int);
    char **get_expr_tab(char *);
    char *replace_sign(char *);

    /* errors */

    int check_basic_errors(char *);

    /* fill */

    int *handle_sep_index(int *, int, int);
    int manage_tree(tree_t *, char **, int *);
    tree_t **add_right(char *, int);
    int add_left(tree_t *, char *, int);
    int add_current(tree_t *, char *, int);
    tree_t *create_node(void);
    int check_redir(char *, int);
    int is_a_redirection(char *);
    char *get_redir_name(char *);
    tree_t **simple_node(tree_t **, char *, int);

#endif /* !tree.h */
