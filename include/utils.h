#ifndef UTILS_H
#define UTILS_H

char* expand_home(const char *path);

char* expand_command_path(const char* command, const char *commands_dir);

#endif
