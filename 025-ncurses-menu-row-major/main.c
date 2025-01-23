#include <curses.h>
#include <menu.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char *options[] = {
    "Sword",
    "Bow",
    "Magic",
};

/*
 * Demonstrate how the ROWMAJOR options works on a menu.
 *
 * Note(john): O_ROWMAJOR is by default on to see the effect comment line 31.
 */

int main(void) {
  ITEM **items;
  MENU *menu;
  WINDOW *win;

  int ch;
  int n_options, i;

  int h, w, y, x;

  h = 20;
  w = 70;
  y = 2;
  x = 2;

  initscr();
  cbreak();
  noecho();
  clear();

  n_options = ARRAY_SIZE(options);
  items = (ITEM **)calloc(n_options + 1, sizeof(ITEM *));
  for (i = 0; i < n_options; ++i) {
    items[i] = new_item(options[i], options[i]);
  }

  menu = new_menu(items);

  menu_opts_off(menu, O_ROWMAJOR);
  // menu_opts_on(menu, O_ROWMAJOR);

  menu_opts_off(menu, O_SHOWDESC);
  set_menu_format(menu, 6, 2);

  win = newwin(h, w, y, x);
  keypad(win, TRUE);

  set_menu_win(menu, win);
  set_menu_sub(menu, derwin(win, 6, 68, 6, 1));

  box(win, 0, 0);
  refresh();

  post_menu(menu);
  wrefresh(win);

  while ((ch = wgetch(win)) != 'q') {
    switch (ch) {
    case KEY_LEFT:
      menu_driver(menu, REQ_LEFT_ITEM);
      break;
    case KEY_RIGHT:
      menu_driver(menu, REQ_RIGHT_ITEM);
      break;
    }
  }

  unpost_menu(menu);
  free_menu(menu);

  for (i = 0; i < n_options; ++i) {
    free_item(items[i]);
  }

  delwin(win);
  endwin();

  return 0;
}
