#ifndef EXPANDER_H
# define EXPANDER_H

void    expander(t_mini *data);
void    handle_node_expander(t_mini *data, t_parser *node);
void    expand_string(t_mini *data, char **string);
char    *handle_question_mark(char *string, int start, int exit_code, int *i);
char    *expand_substring(t_mini *data, char *string, int start, int end, int *i);
char    *expand_var(char *string, int start, int end, char *expansion, int *i);
int     is_single_quoted(char *str);

#endif
