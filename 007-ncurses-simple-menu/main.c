#include <curses.h>

/*
 * Example of a simple menu to choose from different options.
 * */

#define WIDTH 30
#define HEIGHT 10

char *options[] = {
    "Sword",
    "Bow",
    "Magic",
    "Exit",
};

int x = 0;
int y = 0;

int n_options = sizeof(options) / sizeof(char *);

void print_menu(WINDOW *menu_win, int highlight);

int main(void) {
  WINDOW *menu_win;
  int highlight = 1;
  int option = 0;
  int ch;

  initscr();
  clear();
  noecho();
  cbreak();

  x = (80 - WIDTH) / 2;
  y = (24 - HEIGHT) / 2;

  menu_win = newwin(HEIGHT, WIDTH, y, x);
  keypad(menu_win, TRUE);

  mvprintw(0, 0,
           "Use arrow keys to go up and down, Press enter to select a option");
  refresh();
  print_menu(menu_win, highlight);

  while (1) {
    ch = wgetch(menu_win);
    switch (ch) {
    case KEY_UP: {
      if (highlight == 1) {
        highlight = n_options;
      } else {
        --highlight;
      }
      break;
    }
    case KEY_DOWN: {
      if (highlight == n_options) {
        highlight = 1;
      } else {
        ++highlight;
      }
      break;
    }
    case 10: {
      option = highlight;
      mvprintw(23, 0, "You choose option %s\n", options[option - 1]);

      refresh();
      break;
    }
    default: {
      mvprintw(24, 0, "Character pressed is = %3d '%c'", ch, ch);
      refresh();
      break;
    }
    }

    print_menu(menu_win, highlight);
    if (option == n_options) {
      break;
    }
  }
  clrtoeol();
  refresh();
  endwin();

  return 0;
}

void print_menu(WINDOW *menu_win, int highlight) {
  int p_x, p_y, i;

  p_x = 2;
  p_y = 2;

  box(menu_win, 0, 0);
  for (i = 0; i < n_options; i++) {
    if (highlight == i + 1) {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, p_y, p_x, options[i]);
      wattroff(menu_win, A_REVERSE);
    } else {
      mvwprintw(menu_win, p_y, p_x, options[i]);
    }

    ++p_y;
  }
  wrefresh(menu_win);
}
