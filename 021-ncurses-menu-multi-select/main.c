#include <curses.h>
#include <menu.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char *options[] = {
    "Sword", "Bow", "Magic", "Shield", "Armor",
};

/*
 * Showcase how multi selection in menu works.
 *
 * Note(john): In this example for simplicity and focus only on the mutli
 * selection logic. I didn't implement a clear function for the printed
 * item so it would display a wrong outcome on the second <enter> if the
 * selection is lower than previous. Keep that in mind just restart the program.
 */

int main(void) {
  ITEM **items;
  MENU *menu;
  int ch, i;
  int n_options;

  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  clear();

  n_options = ARRAY_SIZE(options);
  items = (ITEM **)calloc(n_options + 1, sizeof(ITEM *));

  for (i = 0; i < n_options; ++i) {
    items[i] = new_item(options[i], options[i]);
  }

  menu = new_menu((ITEM **)items);

  menu_opts_off(menu,
                O_ONEVALUE); /* Turn one value off to allow multi selection */

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
    case ' ':
      menu_driver(menu, REQ_TOGGLE_ITEM);
      break;
    case 10:
      ITEM **current_items;
      current_items = menu_items(menu);

      mvprintw(20, 2, "Your selected items:");

      int select_count = 0;
      for (i = 0; i < item_count(menu); ++i) {
        if (item_value(current_items[i]) == TRUE) {
          ++select_count;
          mvprintw(20 + select_count, 2, "+ %s", item_name(current_items[i]));
        }
      }

      refresh();
      break;
    }
  }

  for (i = 0; i < n_options; ++i) {
    free_item(items[i]);
  }

  free_menu(menu);
  endwin();

  return 0;
}
