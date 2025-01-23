#include <curses.h>
#include <menu.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char *options[] = {
    "Sword", "Bow", "Magic", "Armor", "Shield", "Health", "Quest",
};

/*
 * Showcase how to work with menu that contains mutliple columns.
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
  menu_opts_off(menu, O_SHOWDESC);

  win = newwin(h, w, y, x);
  keypad(win, TRUE);

  set_menu_win(menu, win);
  set_menu_sub(menu, derwin(win, 8, 68, 3, 1));
  set_menu_format(menu, 5, 3);

  box(win, 0, 0);
  refresh();

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
    case KEY_LEFT:
      menu_driver(menu, REQ_LEFT_ITEM);
      break;
    case KEY_RIGHT:
      menu_driver(menu, REQ_RIGHT_ITEM);
      break;
    case KEY_PPAGE:
      menu_driver(menu, REQ_SCR_UPAGE);
      break;
    case KEY_NPAGE:
      menu_driver(menu, REQ_SCR_DPAGE);
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
