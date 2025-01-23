#include <ncurses.h>

/*
 * This demostrate dumping the screen and restore them.
 * All infos will be saved in a file that will be loaded again with restore.
 *
 * Note(john): Take a close look at scene1.out that will be created at the first
 * run.
 */

int main(void) {
  initscr();
  clear();
  cbreak();
  noecho();

  mvaddstr(20, 20, "Scene 1");
  refresh();

  scr_dump("scene1.out");
  clear();

  getch();

  scr_restore("scene1.out");
  doupdate();

  mvaddstr(0, 0, "<loaded dump>");
  refresh();

  getch();

  endwin();
  return 0;
}
