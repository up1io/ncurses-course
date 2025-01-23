#include <curses.h>
#include <eti.h>
#include <form.h>

/*
 * Form field validation that accept alphabetic and digits, no blanks, no
 * sepcial characters.
 */

int main(void) {
  FIELD *fields[2];
  FORM *form;
  int ch;

  initscr();
  cbreak();
  noecho();
  clear();

  keypad(stdscr, TRUE);

  fields[0] = new_field(1, 20, 6, 1, 0, 0);
  fields[1] = NULL;

  set_field_back(fields[0], A_UNDERLINE);
  set_field_type(fields[0], TYPE_ALNUM, 1);

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

    int status = form_driver(form, REQ_VALIDATION);
    if (status == E_INVALID_FIELD) {
      mvaddstr(20, 2, "Invalid Field");
      refresh();
    } else if (status == E_OK) {
      move(20, 2);
      clrtoeol();
    }
  }

  unpost_form(form);
  free_form(form);

  free_field(fields[0]);

  endwin();

  return 0;
}
