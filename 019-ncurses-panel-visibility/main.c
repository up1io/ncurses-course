#include <curses.h>
#include <panel.h>

/*
 * Show the functionality to hide and show panel.
 */

int main(void) {
  WINDOW *win;
  PANEL *panel;
  int ch;
  int h, w, y, x;

  h = 5;
  w = 10;
  y = 2;
  x = 2;

  initscr();
  cbreak();
  noecho();
  clear();

  win = newwin(h, w, y, x);
  box(win, 0, 0);

  panel = new_panel(win);

  update_panels();
  doupdate();
  wrefresh(win);
  printw("<use the key s for show panel and h for hidding panel>");

  while ((ch = getch()) != 'q') {
    switch (ch) {
    case 's':
      show_panel(panel);
      break;
    case 'h':
      hide_panel(panel);
      break;
    }
    update_panels();
    doupdate();
  }

  endwin();
  return 0;
}
