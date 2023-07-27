#ifndef MAIN_H
#define MAIN_H
/**
 * struct alias - a struct data type for alias.
 * @name: key name
 * @value: value
 * Description: a struct data type with 2 elements to make up an alias
 */
struct alias
{
	char *name;
	char *value;
};
typedef struct alias alias_t;
char *_strdup(const char *str);
unsigned int _strlen(const char *str);
void execute(char *ppath, char *cmd_input, char **env, char *execname);
extern char **environ;
char *_getenv(char *name);
char *p_input(char *buf, char *arg, char **env, alias_t **aliases);
char *_strcpy(char *copy, char *origin);
char *joinpath(char *dest, char *s1, size_t s1_len, char *s2, size_t s2_len);
int _strncmp(char *s1, char *s2, int len);
int _strcmp(char *s1, char *s2);
char **get_cmds(char *buffer);
void freelist(char **arr);
void error_disp(char *cmd, unsigned int count, char *arg);
int _putchar(char c);
int _atoi(char *s);
int process_cmds(char *buffer, char *exec, char **env, alias_t ***as);
char *get_path(char *pname, char *buf);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void trim(char **str);
int check_d_alias(char *str);
void add_alias(struct alias ***aliases, char *name, char *value, int *alias_c);
void print_all_alias(struct alias **aliases);
void print_alias(char *alias, struct alias **aliases);
char **get_alias_args(char *alias_cmdline);
int process_alias(char *alias_cmdline, struct alias ***aliases, int *alias_c);
void free_all_alias(struct alias **aliases);
void exit_call(char *buffer, char **cmds, int *stat, alias_t ***as, int count);
int chkpstatus(int status);
char *_strchr(char *str, int c);
int print_env(char **env);
int get_status(int res);
char *check_value(char *pname, alias_t **aliases);
int _isdigit(char *str);
#endif
