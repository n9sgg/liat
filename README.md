liat - list it at the top

Code for an application that Lists It At the Top

Think about liat as the unix tail utility in reverse.

That's what it does, it  Lists It At the Top!

liat uses the ncurses library and header files. 

If you do not have ncurses you can install it on ubuntu like below.

> sudo apt-get install libncurses5-dev libncursesw5-dev

To compile liat at the bash prompt ...

> gcc -c liat.c -o liat -lncurses


liat reads from stdin. To use liat try the following

tail -f <some_file_name> | liat 
