#include <curses.h>
#include <form.h>

/*
 * Showcase how a form is placed inside a window.
 */

int main(void) {
  FIELD *fields[3];
  FORM *form;
  WINDOW *win;
  int ch;

  int h, w, y, x;

  h = 20;
  w = 40;
  y = 2;
  x = 2;

  initscr();
  cbreak();
  noecho();
  clear();

  fields[0] = new_field(1, 10, 6, 1, 0, 0);
  fields[1] = new_field(1, 10, 8, 1, 0, 0);
  fields[2] = NULL;

  set_field_back(fields[0], A_UNDERLINE);
  set_field_back(fields[1], A_UNDERLINE);

  form = new_form(fields);

  win = newwin(h, w, y, x);
  keypad(win, TRUE);

  int rows, cols;
  scale_form(form, &rows, &cols);

  set_form_win(form, win);
  set_form_sub(form, derwin(win, rows, cols, 2, 2));

  box(win, 0, 0);

  post_form(form);
  refresh();

  while ((ch = wgetch(win)) != 'q') {
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

    refresh();
  }

  unpost_form(form);
  free_form(form);
  free_field(fields[0]);
  free_field(fields[1]);

  delwin(win);

  endwin();

  return 0;
}
