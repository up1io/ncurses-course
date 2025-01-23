#include <curses.h>

int main(void) {
  initscr();
  noecho();

  refresh();
  getch(); /* Waiting for user input */

  endwin();
  return 0;
}
