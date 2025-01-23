#include <curses.h>

/*
 * Shows a simple demostration of ncurses window feature.
 */

int main(void) {
  WINDOW *win;
  int x, y, w, h;
  int ch;

  initscr();
  cbreak();
  noecho();

  w = 10;
  h = 10;

  y = (LINES - h) / 2;
  x = (COLS - w) / 2;

  refresh();

  win = newwin(h, w, y, x);

  box(win, 0, 0);
  // wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');

  mvwaddch(win, 2, 2, 'X');
  wrefresh(win);

  getch();

  delwin(win);
  endwin();

  return 0;
}
