#include <curses.h>
#include <menu.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char *options[] = {
    "Sword",
    "Bow",
    "Magic",
    "Shield",
};

/*
 * This show how to make items in a menu unselectable.
 */

int main(void) {
  ITEM **items;
  MENU *menu;
  int ch;
  int n_options, i;

  initscr();
  cbreak();
  noecho();
  clear();
  keypad(stdscr, TRUE);

  n_options = ARRAY_SIZE(options);
  items = (ITEM **)calloc(n_options + 1, sizeof(ITEM *));
  for (i = 0; i < n_options; ++i) {
    items[i] = new_item(options[i], options[i]);
  }

  item_opts_off(items[1], O_SELECTABLE);

  menu = new_menu(items);
  post_menu(menu);
  refresh();

  while ((ch = getch()) != 'q') {
    switch (ch) {
    case KEY_UP:
      menu_driver(menu, REQ_UP_ITEM);
      break;
    case KEY_DOWN:
      menu_driver(menu, REQ_DOWN_ITEM);
      break;
    }
    refresh();
  }

  unpost_menu(menu);
  for (i = 0; i < n_options; ++i) {
    free_item(items[i]);
  }
  free_menu(menu);

  endwin();

  return 0;
}
