#include <curses.h>
#include <menu.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char *options[] = {
    "Sword", "Bow", "Magic", "Armor", "Shield", "Health", "Mana", "Quest",
};

/*
 * Demonstrate the scrolling behaviour on a menu.
 */

int main(void) {
  ITEM **items;
  MENU *menu;
  WINDOW *win;
  int ch;
  int n_options, i;

  int h, w, y, x;

  h = 10;
  w = 40;
  y = 4;
  x = 4;

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

  win = newwin(h, w, y, x);
  keypad(win, TRUE);

  set_menu_win(menu, win);
  set_menu_sub(menu, derwin(win, 6, 38, 1, 1));
  set_menu_format(menu, 2, 1);

  box(win, 0, 0);

  post_menu(menu);
  wrefresh(win);

  while ((ch = wgetch(win)) != 'q') {
    switch (ch) {
    case KEY_UP:
      menu_driver(menu, REQ_UP_ITEM);
      break;
    case KEY_DOWN:
      menu_driver(menu, REQ_DOWN_ITEM);
      break;
    case KEY_NPAGE:
      menu_driver(menu, REQ_SCR_DPAGE);
      break;
    case KEY_PPAGE:
      menu_driver(menu, REQ_SCR_UPAGE);
      break;
    }
    wrefresh(win);
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
