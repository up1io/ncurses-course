#include <curses.h>

int main(void) {
  initscr();
  cbreak();
  noecho();

  keypad(stdscr, TRUE); /* Enable listen for keypad inputs */

  int ch;
  while ((ch = getch()) != KEY_EXIT) {
    clear();
    printw("Key pressed: %d (keycode)", ch);
    refresh();
  }

  endwin();
  return 0;
}
