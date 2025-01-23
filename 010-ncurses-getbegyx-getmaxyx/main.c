#include <curses.h>

/*
 * This code snippet demonstrate the usage of getbegyx and getmaxyx.
 */

int main(void) {
  WINDOW *win;

  initscr();
  clear();
  noecho();

  refresh();

  win = newwin(10, 7, 5, 3);
  box(win, 0, 0);
  wrefresh(win);

  int beg_x, beg_y;
  getbegyx(win, beg_y, beg_x);

  int max_x, max_y;
  getmaxyx(win, max_y, max_x);

  mvprintw(0, 0, "<begin windows pos x:%d y:%d>", beg_x, beg_y);
  mvprintw(1, 0, "<max windows pos x:%d y:%d>", max_x, max_y);

  getch();

  delwin(win);
  endwin();

  return 0;
}
