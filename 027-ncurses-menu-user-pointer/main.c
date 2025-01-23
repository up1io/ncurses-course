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

void print_name_from_func(char *name);

int main(void) {
  ITEM **items;
  MENU *menu;
  int ch;
  int n_options, i;
  ITEM *curr_item;

  initscr();
  cbreak();
  noecho();
  clear();

  keypad(stdscr, TRUE);

  n_options = ARRAY_SIZE(options);
  items = (ITEM **)calloc(n_options + 1, sizeof(ITEM *));
  for (i = 0; i < n_options; ++i) {
    items[i] = new_item(options[i], options[i]);
    set_item_userptr(items[i], print_name_from_func);
  }

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
    case 's':
      void (*p)(char *);
      curr_item = current_item(menu);
      p = item_userptr(curr_item);
      p((char *)item_name(curr_item));
      break;
    }
  }

  unpost_menu(menu);
  for (i = 0; i < n_options; ++i) {
    free_item(items[i]);
  }

  free_menu(menu);
  endwin();

  return 0;
}

void print_name_from_func(char *name) {
  move(20, 0);
  clrtoeol();
  mvprintw(20, 2, "Item selected (from func): %s", name);
  refresh();
}
