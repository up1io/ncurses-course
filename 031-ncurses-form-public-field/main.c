#include <curses.h>
#include <form.h>

/*
 * Showcase the form field public options to not show the input of a form field.
 */

int main(void) {
  FIELD *fields[3];
  FORM *form;
  int ch, i;

  initscr();
  cbreak();
  noecho();
  clear();

  keypad(stdscr, TRUE);

  fields[0] = new_field(1, 10, 4, 18, 0, 0);
  fields[1] = new_field(1, 10, 6, 18, 0, 0);
  fields[2] = NULL;

  set_field_back(fields[0], A_UNDERLINE);
  set_field_back(fields[1], A_UNDERLINE);

  field_opts_off(fields[1], O_PUBLIC);

  form = new_form(fields);
  post_form(form);

  refresh();

  while ((ch = getch()) != 'q') {
    switch (ch) {
    case KEY_DOWN:
      form_driver(form, REQ_NEXT_FIELD);
      form_driver(form, REQ_END_LINE);
      break;
    case KEY_UP:
      form_driver(form, REQ_PREV_FIELD);
      form_driver(form, REQ_END_LINE);
      break;
    default:
      form_driver(form, ch);
      break;
    }
  }
  unpost_form(form);
  free_form(form);

  free_field(fields[0]);
  free_field(fields[1]);

  endwin();

  return 0;
}
