#include <curses.h>
#include <form.h>

int main(void) {
  FIELD *fields[2];
  FORM *form;
  int ch;

  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_YELLOW, COLOR_RED);

  fields[0] = new_field(1, 10, 4, 18, 0, 0);
  set_field_fore(fields[0], COLOR_PAIR(1));
  set_field_back(fields[0], COLOR_PAIR(2));

  fields[1] = NULL;

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
