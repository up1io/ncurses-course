#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * This code demostrate how to leave the curses mode temporarily and return to
 * mode.
 *
 * Note(john): In this example a /bin/sh is open on exit cmd the curses mode is
 * reset.
 */

int main(void) {
  initscr();
  cbreak();
  noecho();
  clear();

  mvprintw(2, 2, "<ncurses mode, press any key to continue to the sh>");
  refresh();

  getch();

  def_prog_mode();
  endwin();

  system("/bin/sh"); /* on exit cmd the program will continue */

  reset_prog_mode();
  refresh();

  mvprintw(3, 2, "<ncurses reconnected, press any key to quit>");
  refresh();

  getch();
  endwin();

  return 0;
}
