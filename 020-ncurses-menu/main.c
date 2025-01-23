#include <curses.h>
#include <menu.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char *options[] = {
    "Bow", "Sword", "Magic", "Shield", "Helm", "Armor",
};

int main(void) {
  ITEM **items;
  int ch;
  MENU *menu;
  int n_options, i;

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  n_options = ARRAY_SIZE(options);
  items = (ITEM **)calloc(n_options + 1, sizeof(ITEM *));

  for (i = 0; i < n_options; ++i) {
    items[i] = new_item(options[i], options[i]);
  }

  menu = new_menu((ITEM **)items);

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

  for (i = 0; i < n_options; ++i) {
    free_item(items[1]);
  }

  free_menu(menu);

  free(items);
  endwin();

  return 0;
}
