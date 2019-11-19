/* ***************************************************************************
* liat.c
* liat - List It At the Top
* Written by: Steven G. Lamers - COPYRIGHT 11-19-2019 - ALL RIGHTS RESERVED
* Version: 2.0
* History:
*       1. First beta release - 04-30-2019
*       2. Second release after testing the changes made from V1
* Usage: liat [filename]
* ************************************************************************* */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define MAX_LINE_LENGTH 400
#define MAX_LINE_NUMBER 100

void resizeHandler(int);

char  screen[MAX_LINE_NUMBER][MAX_LINE_LENGTH];   /* The screen */
int   height = 0, width = 0;

int main(int argc, char **argv)
{
FILE  *fp       = NULL ;
int   x         = 0 ;
int   q         = 0 ;
char  buffer[MAX_LINE_LENGTH] ;   /* line buffer */

  signal(SIGWINCH, resizeHandler);

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

    exit(1);
    
  }
 
  while(1)
  {

    /* Get a line */ 
    getnstr(buffer, MAX_LINE_LENGTH - 1 );
              
    /* push stack down */
    for( q = height ; q > 0 ; q-- )
    {
      strcpy( screen[ q ] , screen[ q - 1 ] );      
    }
          
    /* Insert the line at the top of the stack */
    strcpy( screen[ 0 ] , buffer);

    /* Print output */
    for( x=0 ; x <= (height - 1);  x++ )
    {
                          
      /* move to x,0  */
      wmove(stdscr, x, 0);

      /* clear the line */
      clrtoeol();          
                      
      /* print the line */
      wprintw( stdscr, "%s" , screen[ x ] );
            
      /* Refresh the screen */
      wrefresh(stdscr);
    }
  }

  endwin();
  
  exit(0);

}


void resizeHandler(int sig)
{
    int h, w;

    getmaxyx(stdscr, h, w);  /* get the new screen size */

    height = h; /* Set height to window height */
    width  = w; /* Set width to window width */

    if( height > MAX_LINE_NUMBER  )
    {
      height = MAX_LINE_NUMBER ;
    }
    
    if( width > MAX_LINE_LENGTH )
    {
      width = MAX_LINE_LENGTH ;
    }
    
    /* Resize the window */
    wresize(stdscr, height, width);

    /* Refresh the screen */
    wrefresh(stdscr);
}
