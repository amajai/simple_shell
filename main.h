#ifndef MAIN_H
#define MAIN_H
char *_strdup(const char *str);
unsigned int _strlen(const char *str);
void execute(char *ppath, char *cmd_input, char **env, char *execname);
extern char **environ;
char *_getenv(char *name);
char *process_input(char *pname, char *buffer);
char *_strcpy(char *copy, char *origin);
char *joinpath(char *dest, char *s1, size_t s1_len, char *s2, size_t s2_len);
int _strncmp(char *s1, char *s2, int len);
int _strcmp(char *s1, char *s2);
#endif
