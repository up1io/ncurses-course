#include <curses.h>
#include <ncurses.h>
#include <panel.h>

int main(void) {
  WINDOW *win, *temp_win;
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
  refresh();
  keypad(stdscr, TRUE);

  win = newwin(h, w, y, x);
  box(win, 0, 0);
  panel = new_panel(win);
  wrefresh(win);
  printw("<press up and down to scale the panel>");

  int multiple = 0;
  while ((ch = getch()) != 'q') {
    switch (ch) {
    case KEY_UP:
      multiple++;
      break;
    case KEY_DOWN:
      multiple--;
      break;
    }

    temp_win = newwin(h + multiple, w + multiple, y, x);
    box(temp_win, 0, 0);
    replace_panel(panel, temp_win);

    delwin(win);
    win = temp_win;

    refresh();
    update_panels();
    doupdate();
    wrefresh(win);
  }

  endwin();
  return 0;
}
