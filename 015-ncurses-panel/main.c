#include <ncurses.h>
#include <panel.h>

/*
 * Showcase how to attach panels to a window. This allow to stack the panels on
 * each other.
 */

int main(void) {
  WINDOW *wins[2];
  PANEL *panels[2];

  int h, w, y, x;

  h = 5;
  w = 10;

  x = 2;
  y = 2;

  initscr();
  cbreak();
  noecho();
  clear();

  for (int i = 0; i < 2; ++i) {
    wins[i] = newwin(h, w, y + i, x + i);
    box(wins[i], 0, 0);
  }

  panels[0] = new_panel(wins[0]);
  panels[1] = new_panel(wins[1]);

  update_panels(); /* Update the stacking order */
  doupdate();      /* Show it on the screen     */

  getch();

  for (int i = 0; i < 2; i++) {
    delwin(wins[i]);
  }

  endwin();
  return 0;
}
