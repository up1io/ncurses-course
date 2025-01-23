#include <ncurses.h>

/*
 * curs_set change the visiblility of the cursor.
 *
 * Note(john): Here are the settings.
 *
 * 0 : invisible
 * 1 : normal
 * 2 : very visible
 */

int main(void) {
  initscr();
  clear();
  noecho();
  cbreak();

  curs_set(0); /* Set the cursor mode to invisible */
  printw("Hello this is a text.");

  getch();

  endwin();
  return 0;
}
