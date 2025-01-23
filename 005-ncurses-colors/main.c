#include <curses.h>

/*
 * This demonstrate a simple case to use colors.
 * */

int main(void) {
  initscr();

  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    return 1;
  }

  start_color();

  // Define color pairs (foreground and background color)
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_BLUE, COLOR_BLACK);

  attron(COLOR_PAIR(1));
  mvaddstr(2, 2, "Hello World");
  attrset(COLOR_PAIR(2));
  addstr(" in color.");
  attroff(COLOR_PAIR(1));
  addstr(" None colored");
  getch();

  endwin();
  return 0;
}
