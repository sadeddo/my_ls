
#include "handlers.h"
#include<sys/types.h>
#include<stdio.h>
#include<dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>






//afficher un caractère
int my_putchar(char *c)
{
    return write(sizeof(char), &c, 1);
}

//afficher une chaine de caractère
int my_putstr(char *str)
{
    int a = 0;
    if(str == NULL) return my_putstr("(NULL)");
    while(str[a]!= '\0')
    {
        write(sizeof(char), &str[a], 1);
        a++;
    }
    return a;
}


char* return_converted(int num, int base)
{
    char number[] = "0123456789";
    char *conv = malloc(100*sizeof(int));
    int affichenum, index = 0;
    while(num > 0)
    {
        affichenum = num % base;
        for(int i =0; i < base; i++)
        {
            if(affichenum == i)
            {
                conv[index] = number[i];
                index++;
            }
            num /= base;
        }
    }
    return conv;
}


int	my_putcharr(char c)
{
  write (1, &c, 1);
  return 0;
}


//affichier un entier 
int	my_putint(int nb)
{
  int	mod;

  if (nb < 0)
    {
      my_putcharr('-');
      nb = nb * (-1);
    }
  if (nb >= 0)
    {
      if (nb >= 10)
	{
	  mod = (nb % 10);
          nb = (nb - mod) / 10;
	  my_putint(nb);
	  my_putcharr(48 + mod);
        }
      else
        my_putcharr(48 + nb % 10);
    }
    return 0;
}

int my_printf(char* format, ...)
{
    va_list args;
    char *outputString, *s; //, enter = '\n', *newline =&enter
    int i, ret = 0;
    
    va_start(args, format);

    for(outputString = format; *outputString != '\0'; outputString++)
    {
        if(*outputString == '%')
        {
            outputString++;
             switch(*outputString){
                case 'c' : s = va_arg(args, char *);
                    ret += my_putchar(s); 
                    break;
                case 'd': i = va_arg(args, int);
                    ret += my_putint(i);
                    break;
                case 's': s = va_arg(args, char*);
                    ret+= my_putstr(s);
                    break;
            }
        }
        else ret += write(1,outputString, 1);
    }    
    va_end(args);
    
    return ret;
}
    ////
int	my_strcmp(char *s1, char *s2)
{
  int i;
  i = 0;
  while ((s1[i] == s2[i]) && (s1[i] != '\0') && (s2[i] != '\0'))
    {
      i++;
    }
  return (s1[i] - s2[i]);
}
int lsA(int ac,char *av[]) 
{
        DIR *dir;
    struct dirent *dirent;

    dir = opendir(".");


    while ((dirent = readdir(dir)) != NULL)
    {
        if (((my_strcmp(dirent->d_name, ".") != 0)) && ((my_strcmp(dirent->d_name, "..") != 0)))
        {
            printf("%s\n",dirent->d_name);
        }

    };

    closedir(dir);

    return (0);
        
}
int lsa(int ac,char *av[]) 
{
       DIR *dir;
    struct dirent *dirent;

    dir = opendir(".");

    if(dir == NULL)
    {
        printf("Error");
        return(1);
    }
   while ((dirent=readdir(dir)) != NULL)
   {
       printf("%s\n" ,dirent->d_name);
   }
   closedir(dir);

        return 0;
        
}

void lsR(const char* dirname) 
{
    DIR* dir = opendir(dirname);
    if (dir == NULL)
    {
        return;
    }
    my_printf(" %s:\n", dirname);
    struct dirent* entity;

    entity = readdir(dir);
    while (entity != NULL) 
    {
        if (entity->d_name[0] != '.')
        {
            my_printf(" %s\n", entity->d_name);
            if (entity->d_type == DT_DIR && my_strcmp(entity->d_name, ".") != 0 && my_strcmp(entity->d_name, "..") != 0)
            {
                char path[100] = { 0 };
                strcat(path, dirname);
                strcat(path, "/");
                strcat(path, entity->d_name);
                lsR(path);
            }
        }
        entity = readdir(dir);
    }
    closedir(dir);
}

int lsl(int ac,char *av[]) 
{
        DIR *dir;
        struct dirent *dirent;
        struct stat sd;
        struct tm *timeInfo;

        //char *folder_name = (ac < 2) ? "." : av[1];
       

        if ((dir = opendir(".")) == NULL)
        {
            my_printf("my_ls: cannot access ",strerror(errno));
            return(1);
        }

        struct tiles 
        {
            char *name; 
            int size; 
            int nlink;
            char *nameuser;
            char *ID;
            int modeR;
            long int date;
        };

        struct tiles t_array[256];


        int nbr=0;

        while ((dirent = readdir(dir)) != NULL)
        {
            if (dirent->d_name[0] != '.')
            {
              stat(dirent->d_name,&sd);
                t_array[nbr].name=dirent->d_name;
                t_array[nbr].size=sd.st_size;
                t_array[nbr].nlink=sd.st_nlink;
                t_array[nbr].nameuser=getgrgid(sd.st_gid)->gr_name;
                t_array[nbr].ID=getpwuid(sd.st_uid)->pw_name;
                t_array[nbr].modeR=sd.st_mode;
                t_array[nbr].date=sd.st_mtime;
                     
                nbr++;
            }
        }

        struct tiles temp;
    
        for(int i=0; i<nbr; i++)
        {
            for(int j=0; j<nbr-1-i; j++)
            {
                if(my_strcmp(t_array[j].name, t_array[j+1].name) > 0)
                //if(t_array[j].date<t_array[j+1].date)
                {
                    temp = t_array[j];
                    t_array[j] = t_array[j + 1];
                    t_array[j + 1] = temp;
                } 
            }
        }
        for(int i=0;i<nbr;i++)
        {

            my_printf("%c",(t_array[i].modeR & S_IRUSR)==S_IRUSR ? 'r' : '-'); // owner R
            my_printf("%c",(sd.st_mode & S_IWUSR)==S_IWUSR ? 'w' : '-'); // owner W
            my_printf("%c",(t_array[i].modeR & S_IXUSR)==S_IXUSR ? 'x' : '-'); // owner X
            my_printf("%c",(t_array[i].modeR & S_IRGRP)==S_IRGRP ? 'r' : '-'); // group R
            my_printf("%c",(t_array[i].modeR & S_IWGRP)==S_IWGRP ? 'w' : '-'); // group W
            my_printf("%c",(t_array[i].modeR & S_IXGRP)==S_IXGRP ? 'x' : '-'); // group X
            my_printf("%c",(t_array[i].modeR & S_IROTH)==S_IROTH ? 'r' : '-'); // other R
            my_printf("%c",(t_array[i].modeR & S_IWOTH)==S_IWOTH ? 'w' : '-'); // other W
            my_printf("%c ",(t_array[i].modeR & S_IXOTH)==S_IXOTH ? 'x' : '-'); // other X
           
            my_printf("     %d ",t_array[i].nlink);
            my_printf("  %s ",t_array[i].nameuser);
            my_printf("  %s ",t_array[i].ID);

            timeInfo=localtime(&t_array[i].date);
            my_printf("  %d-%d-%d %d:%d:%d",timeInfo->tm_year+1900,timeInfo->tm_mon+1,timeInfo->tm_mday,timeInfo->tm_hour+6,timeInfo->tm_min,timeInfo->tm_sec);
            my_printf("  %d ",t_array[i].size);
            my_printf(" %s\n",t_array[i].name);
            
        }
        closedir(dir);

        return 0;
        
    }

int lst(int ac,char *av[]) 
{
        DIR *dir;
        struct dirent *dirent;
        struct stat sd;
        if ((dir = opendir(".")) == NULL)
        {
            my_printf("my_ls: cannot access '%s': %s\n",strerror(errno));
            return(1);
        }
        struct tiles 
        {
            char *name; 
            int size; 
            int nlink;
            char *nameuser;
            char *ID;
            int modeR;
            long int date;
        
        };

        struct tiles t_array[256];


        int nbr=0;

        while ((dirent = readdir(dir)) != NULL)
        {
            if (dirent->d_name[0] != '.')
            {
              stat(dirent->d_name,&sd);
             
                t_array[nbr].name=dirent->d_name;
                t_array[nbr].modeR=sd.st_mode;
                t_array[nbr].date=sd.st_mtime;
                       
                nbr++;
            }
        }

        struct tiles temp;
    
        for(int i=0; i<nbr; i++)
        {
            for(int j=0; j<nbr-1-i; j++)
            {
                if(t_array[j].date<t_array[j+1].date)
                {
                    temp = t_array[j];
                    t_array[j] = t_array[j + 1];
                    t_array[j + 1] = temp;
                } 
            }
        }
        for(int i=0;i<nbr;i++)
        {
            my_printf(" %s\n",t_array[i].name);
        }
        closedir(dir);

        return 0;
        
}

int lsr(int ac,char *av[]) 
{
        DIR *dir;
        struct dirent *dirent;
        struct stat sd;


        char *folder_name = (ac < 2) ? "." : av[1];
       

        if ((dir = opendir(folder_name)) == NULL)
        {
            my_printf("my_ls: cannot access '%s': %s\n",folder_name,strerror(errno));
            return(1);
        }

        struct tiles 
        {
                char *name; 
                int size; 
                int nlink;
                char *nameuser;
                char *ID;
                int modeR;
                long int date;
        };

        struct tiles t_array[256];
        int nbr=0;

        while ((dirent = readdir(dir)) != NULL)
        {
            if (dirent->d_name[0] != '.')
            {
              stat(dirent->d_name,&sd);
                t_array[nbr].name=dirent->d_name;
                nbr++;
            }
        }

        struct tiles temp;
        for(int i=0; i<nbr; i++)
        {
            for(int j=0; j<nbr-1-i; j++)
            {
                if(my_strcmp(t_array[j].name, t_array[j+1].name) < 0)
                //if(t_array[j].date<t_array[j+1].date)
                {
                    temp = t_array[j];
                    t_array[j] = t_array[j + 1];
                    t_array[j + 1] = temp;
                } 
            }
        }
        for(int i=0;i<nbr;i++)
        {
            my_printf(" %s\n",t_array[i].name);
        }
        closedir(dir);

        return 0;
}

///
int ls(int ac,char *av[]) 
{
        DIR *dir;
        struct dirent *dirent;
        struct stat sd;
        struct tm *timeInfo;

        //char *folder_name = (ac < 2) ? "." : av[1];
       

        if ((dir = opendir(".")) == NULL)
        {
            my_printf("my_ls: cannot access ",strerror(errno));
            return(1);
        }

        struct tiles 
        {
            char *name; 
            
            char *nameuser;
            char *ID;
            int modeR;
            long int date;
        };

        struct tiles t_array[256];


        int nbr=0;

        while ((dirent = readdir(dir)) != NULL)
        {
            if (dirent->d_name[0] != '.')
            {
              stat(dirent->d_name,&sd);
                t_array[nbr].name=dirent->d_name;
                t_array[nbr].modeR=sd.st_mode;
                t_array[nbr].date=sd.st_mtime;
                     
                nbr++;
            }
        }

        struct tiles temp;
    
        for(int i=0; i<nbr; i++)
        {
            for(int j=0; j<nbr-1-i; j++)
            {
                if(my_strcmp(t_array[j].name, t_array[j+1].name) > 0)
                
                {
                    temp = t_array[j];
                    t_array[j] = t_array[j + 1];
                    t_array[j + 1] = temp;
                } 
            }
        }
        for(int i=0;i<nbr;i++)
        {
            my_printf(" %s\n",t_array[i].name);
        }
        closedir(dir);

        return 0;
        
    }

void lsd(const char* dirname) 
{
    DIR* dir = opendir(dirname);
    if (dir == NULL)
    {
        return;
    }
    my_printf(" %s:\n", dirname);
    

    closedir(dir);
}

int lsF(int argc,char *argv[])
{
   
   
        DIR *dir;
        struct dirent *dirent;
        
        //char *folder_name = (ac < 2) ? "." : av[1];
       

        if ((dir = opendir(".")) == NULL)
        {
            my_printf("my_ls: cannot access ",strerror(errno));
            return(1);
        }

    int a = 0; 
   while ((dirent=readdir(dir)) != NULL)
   {
       if(dirent->d_name[0] != '.')
            if ((dirent->d_type) == 4)
            {
                my_printf("%s/ \n" ,dirent->d_name);
            }
            if ((dirent->d_type) == 8)
            {
                if ((dirent->d_reclen) != 32)
                {
                    my_printf("%s*\n" ,dirent->d_name);
                }
                else
                {
                    my_printf("%s\n" ,dirent->d_name);
                }
                
            }
            
   }
   closedir(dir);
   return 0;
}

int lsg(int ac,char *av[])
{
    DIR *dir;
        struct dirent *dirent;
        struct stat sd;
        struct tm *timeInfo;



    dir = opendir(".");

    if(dir == NULL)
    {
        printf("Error");
        return(1);
    }
        struct tiles 
        {
            char *name; 
            int size; 
            int nlink;
            char *nameuser;
            char *ID;
            int modeR;
            long int date;
        };

        struct tiles t_array[256];


        int nbr=0;

        while ((dirent = readdir(dir)) != NULL)
        {
            if (dirent->d_name[0] != '.')
            {
              stat(dirent->d_name,&sd);
                t_array[nbr].name=dirent->d_name;
                t_array[nbr].size=sd.st_size;
                t_array[nbr].nlink=sd.st_nlink;
                t_array[nbr].nameuser=getgrgid(sd.st_gid)->gr_name;
                t_array[nbr].ID=getpwuid(sd.st_uid)->pw_name;
                t_array[nbr].modeR=sd.st_mode;
                t_array[nbr].date=sd.st_mtime;
                     
                nbr++;
            }
        }

        struct tiles temp;
    
        for(int i=0; i<nbr; i++)
        {
            for(int j=0; j<nbr-1-i; j++)
            {
                if(strcmp(t_array[j].name, t_array[j+1].name) > 0)
                //if(t_array[j].date<t_array[j+1].date)
                {
                    temp = t_array[j];
                    t_array[j] = t_array[j + 1];
                    t_array[j + 1] = temp;
                } 
            }
        }
        
        char *mois[]= {"jan", "fév", "mar", "avr", "mai", "jui",
               "jui", "aoû", "sep", "oct", "nov", "déc"};
        for(int i=0;i<nbr;i++)
        {

            my_printf("%c",(t_array[i].modeR & S_IRUSR)==S_IRUSR ? 'r' : '-'); // owner R
            my_printf("%c",(sd.st_mode & S_IWUSR)==S_IWUSR ? 'w' : '-'); // owner W
            my_printf("%c",(t_array[i].modeR & S_IXUSR)==S_IXUSR ? 'x' : '-'); // owner X
            my_printf("%c",(t_array[i].modeR & S_IRGRP)==S_IRGRP ? 'r' : '-'); // group R
            my_printf("%c",(t_array[i].modeR & S_IWGRP)==S_IWGRP ? 'w' : '-'); // group W
            my_printf("%c",(t_array[i].modeR & S_IXGRP)==S_IXGRP ? 'x' : '-'); // group X
            my_printf("%c",(t_array[i].modeR & S_IROTH)==S_IROTH ? 'r' : '-'); // other R
            my_printf("%c",(t_array[i].modeR & S_IWOTH)==S_IWOTH ? 'w' : '-'); // other W
            my_printf("%c ",(t_array[i].modeR & S_IXOTH)==S_IXOTH ? 'x' : '-'); // other X
           
            my_printf("     %d ",t_array[i].nlink);
            my_printf("  %s ",t_array[i].nameuser);
            
            
            timeInfo=localtime(&t_array[i].date);
            my_printf("  %d    ",t_array[i].size);
            my_printf("%d  %s %d:%d ",timeInfo->tm_mday,mois[timeInfo->tm_mon],timeInfo->tm_hour+6,timeInfo->tm_min);
            
            my_printf(" %s\n",t_array[i].name);
            
        }
        closedir(dir);

        return 0;
}