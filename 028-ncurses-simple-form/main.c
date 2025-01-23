#include <curses.h>
#include <form.h>

/*
 * Shows a simple example of forms in ncurses.
 */

int main(void) {
  FIELD *field[2];
  FORM *form;
  int ch;

  initscr();
  cbreak();
  noecho();
  clear();

  keypad(stdscr, TRUE);

  field[0] = new_field(1, 10, 4, 18, 0, 0);
  field[1] = new_field(2, 10, 6, 18, 0, 0);

  set_field_back(field[0], A_UNDERLINE);
  field_opts_off(field[0], O_AUTOSKIP);

  set_field_back(field[1], A_UNDERLINE);
  field_opts_off(field[1], O_AUTOSKIP);

  form = new_form(field);
  post_form(form);

  mvprintw(4, 10, "Field 1:");
  mvprintw(6, 10, "Field 2:");
  refresh();

  while ((ch = getch()) != 'q') {
    switch (ch) {
    case KEY_UP:
      form_driver(form, REQ_PREV_FIELD);
      form_driver(form, REQ_END_LINE);
      break;
    case KEY_DOWN:
      form_driver(form, REQ_NEXT_FIELD);
      form_driver(form, REQ_END_LINE);
      break;
    default:
      form_driver(form, ch);
      break;
    }
  }

  unpost_form(form);

  free_field(field[0]);
  free_field(field[1]);
  free_form(form);

  endwin();
  return 0;
}
