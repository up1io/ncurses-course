#include <ncurses.h>

/*
 * This example demostrate how to dump a window content into a file and restore
 * it from the target file.
 *
 * Note(john): Take a look at the win.out format how the data is actually
 * stored.
 */

int main(void) {
  FILE *filep;
  WINDOW *win;

  int w, h, x, y;

  w = 20;
  h = 20;

  x = 5;
  y = 5;

  initscr();
  clear();
  cbreak();
  noecho();

  refresh();

  win = newwin(h, w, y, x);
  box(win, 0, 0);

  mvwaddstr(win, 2, 2, "Win Content");
  wrefresh(win);

  printw("<press a key to clear and reload window content>");

  getch();

  filep = fopen("win.out", "wb+");
  if (filep == NULL) {
    delwin(win);
    endwin();
    perror("Failed to opening file");
    return 1;
  }

  putwin(win, filep);
  fclose(filep);
  clear();

  printw("<press a key to load the win content>");
  getch();

  refresh();
  WINDOW *loaded_win;
  loaded_win = getwin(filep);
  wrefresh(loaded_win);
  refresh();

  getch();

  delwin(win);
  delwin(loaded_win);
  endwin();
  return 0;
}
