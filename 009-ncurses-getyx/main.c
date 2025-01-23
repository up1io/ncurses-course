#include <curses.h>

/*
 * Showcase the getyx() to get cursor point from a specified window.
 */

int main(void) {
  WINDOW *win = initscr();

  mvaddstr(10, 10, "X");
  refresh();

  int y, x;
  getyx(win, y, x);

  mvprintw(0, 0, "<Stored position X: %d, Y: %d>", x, y);
  refresh();

  getch();
  endwin();
}
