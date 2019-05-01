/* **********************************************************************************
*
* liat.c
* 
* liat - List It At the Top
* 
* Written by: Steven G. Lamers - COPYRIGHT 4-30-2019 - ALL RIGHTS RESERVED
*
* Version: 1.0
*
* History:
*       1. First beta release - 04-30-2019
*
* Usage: liat [filename]
*       
*
* **********************************************************************************
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

 /* TODO - add a switch to overwite and not scroll on updates */

#define MAX_LINE_LENGTH 1024
#define MAX_LINE_NUMBER 200

char  screen[MAX_LINE_NUMBER][MAX_LINE_LENGTH];   /* The screen */

void resizeHandler(int);

int height = 0, width = 0;

int main(int argc, char **argv)
{
    FILE  *fp       = NULL ;
    int   x         = 0 ;
    int   q         = 0 ;
    char  buffer[MAX_LINE_LENGTH] ;   /* line buffer */
 
    /* if no arguments are passed use stdin */
    if ( argc >= 2 ) {

      /* Open the file */
      fp = fopen(argv[1], "r");
  
      if ( fp == NULL )
      {
        /* Can't open file */
        printf("%s can't open input file %s\n", argv[0], argv[1]);
        exit(1);
      }
    }

    signal(SIGWINCH, resizeHandler);

    initscr();

    scrollok(stdscr, FALSE );
   
    getmaxyx(stdscr, height, width);

    if( ( height > MAX_LINE_NUMBER ) || ( width > MAX_LINE_LENGTH ) )
    {

      /* move to 0,0  */
      wmove(stdscr, 0, 0);

      /* clear the line */
      clrtoeol();          
                      
      /* print the error */
      wprintw( stdscr, "Sorry, the screen height is %d  the width is %d : MAX_LINE_NUMBER is %d and MAX_LINE_LENGTH is %d \n", 
                height,
                width, 
                MAX_LINE_NUMBER,
                MAX_LINE_LENGTH 
              );

      /* Refresh the screen */
      wrefresh(stdscr);

      exit(1);
    }

  
    while(1)
    {


        if( fp != NULL )
        {
           fgets( buffer, MAX_LINE_LENGTH, fp);

        }
        else 
        { 
          fgets( buffer, MAX_LINE_LENGTH, stdin );
        }
        
            /* push stack down */
            for( q = height ; q > 0 ; q-- )
            {
              strcpy( screen[ q ] , screen[ q - 1 ] );      
            }
          
            /* Insert the word at the top of the stack */
            strcpy( screen[ 0 ] , buffer );

            /* Print output */
            for( x=0 ; x <= (height - 1);  x++ )
            {
                          
              /* move to x,0  */
              wmove(stdscr, x, 0);

              /* clear the line */
              clrtoeol();          
                      
              /* print the line */
              wprintw( stdscr, "%s" , screen[ x ] );
            }

            /* Refresh the screen */
            wrefresh(stdscr);
   
    }

    endwin();
  
    exit(0);


  exit(0);

/* end main */
}

void resizeHandler(int sig)
{
    int h, w;

    getmaxyx(stdscr, h, w);  /* get the new screen size */

    height = h;
    width  = w;

    if( height > MAX_LINE_NUMBER  )
    {
      height = MAX_LINE_NUMBER ;
    }

    
    if( width > MAX_LINE_LENGTH )
    {
      width = MAX_LINE_LENGTH ;
    }

}


