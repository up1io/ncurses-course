#include <curses.h>

/*
 * This show how to move the cursor to a certain position and draw a char at
 * the moved localtion.
 */

int main(void) {
  initscr(); /* Start curses mode                    */
  noecho();  /* Don't echo() while we do getch       */

  move(5, 5); /* Move to {row:5,col:5}                */
  addch('A'); /* Print a char at the current point    */

  // Short form of the above version
  mvaddch(10, 10, 'B'); /* Move the curser to {Y:10,X:10} and draw char */

  refresh(); /* Print it on the real screen                                  */
  getch();   /* Wait for user input                                          */
  endwin();  /* End curses mode                                              */

  return 0;
}
