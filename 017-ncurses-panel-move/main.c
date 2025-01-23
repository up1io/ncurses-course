#include <ncurses.h>
#include <panel.h>

/*
 * A demostration of the move_panel function to move a panel to a new location.
 */

int main(void) {
  WINDOW *win;
  PANEL *panel;

  int h, w, x, y;
  int ch;

  h = 5;
  w = 10;
  y = 2;
  x = 2;

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  clear();

  win = newwin(h, w, y, x);
  box(win, 0, 0);
  panel = new_panel(win);

  printw("<use the arrow keys to move the panel>");
  refresh();

  update_panels();
  doupdate();

  int newx, newy;
  newx = x;
  newy = y;

  while ((ch = getch()) != 'q') {
    switch (ch) {
    case KEY_UP:
      if (newy > 1) {
        newy--;
      }
      break;
    case KEY_DOWN:
      newy++;
      break;
    case KEY_LEFT:
      if (newx > 1) {
        newx--;
      }
      break;
    case KEY_RIGHT:
      newx++;
      break;
    }

    clear();
    mvprintw(0, 0, "Panel Position: x: %d y: %d", newx, newy);
    move_panel(panel, newy, newx);

    refresh();
    update_panels();
    doupdate();
  }

  delwin(win);
  endwin();
  return 0;
}
