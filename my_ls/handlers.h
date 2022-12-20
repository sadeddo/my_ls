#ifndef HANDLERS
#define HANDLERS
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h> 
#include <errno.h>
#include <string.h> 
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <libgen.h>
#include <sys/types.h>
#include <grp.h>
#include "handlers.h"

    int my_putchar(char *c);
    int my_putstr(char *str);
    char* return_converted(int num, int base); 
    int    my_putcharr(char c);
    int    my_putint(int nb);
    int my_printf(char* format, ...);
    int    my_strcmp(char *s1, char *s2);
    int lsA(int ac,char *av[]);
    int lsa(int ac,char *av[]);
    void lsR(const char* dirname);
    int lsl(int ac,char *av[]);
    int lst(int ac,char *av[]);
    int lsr(int ac,char *av[]);
    int ls(int ac,char *av[]);
    void lsd(const char* dirname);
    int lsF(int argc,char *argv[]);
    int lsg(int ac,char *av[]);
#endif
