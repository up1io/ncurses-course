#include <curses.h>

/*
 * Show the usage of listen for mouse events
 */

int main(void) {
  int ch;
  MEVENT event;

  initscr();
  raw();
  clear();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);

  mousemask(ALL_MOUSE_EVENTS, NULL);

  mvprintw(0, 1, "<click somewhere to place a 'X', press q to quit>");

  int run = 1;
  while (run) {
    ch = getch();
    switch (ch) {
    case KEY_MOUSE: {
      if (getmouse(&event) == OK) {
        mvprintw(1, 1, "Mouse press: x:%d y:%d", event.x, event.y);
        mvprintw(event.y, event.x, "X");
      }
      break;
    }
    case 'q': {
      run = 0;
      break;
    }
    }
    refresh();
  }

  endwin();

  return 0;
}
