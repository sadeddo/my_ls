
#include "handlers.h"
#include "handlers.c"
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
#include <getopt.h>

int main(int ac, char *av[]) {


   int option = 0;
   int l = 0;
    int R = 0;
    int d = 0;
    int t = 0;
    int a = 0;
    int AA = 0;
    int L = 0;
    int F = 0;
    int g = 0;

    
    //int yl(int ac, char *av[]){
    // put ':' at the starting of the string so compiler can distinguish between '?' and ':'                                                
   while((option = getopt(ac, av, "lRrdtaALFg")) != -1){ //get option from the getopt() method    
        
                           
      switch(option){
         //For option i, r, l, print that these are options   

                                                                               
         case 'l':
                l = 1;
                break;
            case 'R':
                R = 1;
                break;
            case 'r':
                R = 1;
                break;
            case 'd':
                d = 1;
                break;
            case 't':
                t = 1;
                break;
            case 'a':
                a=1;
                break;
            case 'A':
                AA = 1;
                break;
            case 'L':
                 L = 1;
                break;
            case 'F':
                 F = 1;
                break;
            case 'g':
                 g = 1;
                break;
            
         
               
      }
   }

   if (l == 1)
   {
       lsl(ac,av);
      
   }
   
  else  if ( R == 1 )
    {
        lsR(".");
        
    }
   
   else if ( d == 1 )
    {
      lsd(".");
    }
  else  if ( t == 1 )
    {
        lst(ac,av);
    }
  else  if ( a == 1 )
    {
        lsa(ac,av);
    }
  else  if ( AA == 1 )
    {
        lsA(ac,av);
    }
  else  if ( F == 1 )
    {
        lsF(ac,av);
    }
  else  if ( g == 1 )
    {
        lsg(ac,av);
    }
  else{
    ls(ac,av);
  }

    
return 0;
}

