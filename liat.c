/* ***************************************************************************
* liat.c
* liat - List It At the Top
* Author: Steven G. Lamers 11-19-2019 - ALL RIGHTS RESERVED 2025
* Version: 3.0
* History:
*       1. First beta release - 04-30-2019
*       2. Second release after testing the changes made from V1
*       3. Changed back to read from stdin instead of file 09-25-2025
*       
* Usage example: tail -f <some_file_name> liat 
*
* ************************************************************************* */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#define MAX_LINE_LENGTH 400
#define MAX_LINE_NUMBER 100

void resizeHandler(int);

char  screen[MAX_LINE_NUMBER][MAX_LINE_LENGTH];   /* The screen */
int   height = 0, width = 0;

void main(int argc, char **argv)
{

char  buffer[MAX_LINE_LENGTH] ;   /* line buffer   Quit if no arguments are passed. */
int   x         = 0 ;
int   q         = 0 ;

  initscr();

  scrollok(stdscr, TRUE );
   
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
  
  return;
  }

  while(1)
  {

    if (fgets(buffer, MAX_LINE_LENGTH - 1, stdin) != NULL ) {

      wmove(stdscr, height, 0 );

      /* clear the line */
      clrtoeol();  
  
      /* print the line */
      wprintw( stdscr, "%s" , buffer );

      /* Refresh the screen */
      wrefresh(stdscr);
  
      /* push stack down */
      for( q = height - 1; q > 0 ; q-- )
      {
        strcpy( screen[ q ] , screen[ q - 1 ] );      
      }
          
      /* Insert the line at the top of the stack */
      strcpy( screen[ 0 ] , buffer);

      /* Print output */
      for( x=0 ; x < (height - 1);  x++ )
      {                         
        /* move to x,0  */
        wmove(stdscr, x, 0);

        /* clear the current line */
        clrtoeol();          
                      
        /* print the new line */
        wprintw( stdscr, "%s" , screen[ x ] );
            
        /* Refresh the screen */
        wrefresh(stdscr);
      }  
    } else {
            usleep(100000);           // Sleep for 100 milliseconds
    }
  }
  
  endwin();

  return;

} /* end of main () */
