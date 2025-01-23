#include <curses.h>
#include <form.h>
#include <menu.h>

/*
 * Show a example of form field justification.
 */

int main(void) {
  FIELD *fields[4];
  FORM *form;
  int ch;

  initscr();
  cbreak();
  noecho();
  clear();

  keypad(stdscr, TRUE);

  fields[0] = new_field(1, 20, 4, 18, 0, 0);
  fields[1] = new_field(1, 20, 6, 18, 0, 0);
  fields[2] = new_field(1, 20, 8, 18, 0, 0);
  fields[3] = NULL;

  set_field_back(fields[0], A_UNDERLINE);
  field_opts_off(fields[0], O_AUTOSKIP);
  set_field_just(fields[0], JUSTIFY_CENTER);
  set_field_buffer(fields[0], 0, "Center");

  set_field_back(fields[1], A_UNDERLINE);
  field_opts_off(fields[1], O_AUTOSKIP);
  set_field_just(fields[1], JUSTIFY_RIGHT);
  set_field_buffer(fields[1], 0, "Right");

  set_field_back(fields[2], A_UNDERLINE);
  field_opts_off(fields[2], O_AUTOSKIP);
  set_field_just(fields[2], JUSTIFY_LEFT);
  set_field_buffer(fields[2], 0, "Left");

  form = new_form(fields);
  post_form(form);
  refresh();

  move(8, 18);

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

  free_field(fields[0]);
  free_field(fields[1]);
  free_field(fields[2]);

  endwin();
  return 0;
}
