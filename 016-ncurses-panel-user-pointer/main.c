#include <ncurses.h>
#include <panel.h>

/*
 * Showcase how to store any information in the panel userptr and recieved the
 * value via the panel.
 */

int main(void) {
  WINDOW *win;
  PANEL *panel;

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
  panel = new_panel(win);

  char *value;
  value = "stored panel value";

  set_panel_userptr(panel, value);

  char *recieved_value;
  recieved_value = (char *)panel_userptr(panel);

  mvaddstr(2, 2, recieved_value);

  getch();

  endwin();
  return 0;
}
