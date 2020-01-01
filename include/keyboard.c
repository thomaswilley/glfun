#include <stdlib.h>
#include "utils.h"
#include "keyboard.h"

void keyboard(unsigned char key, int x, int y, struct session *session_data)
{
  TW_log("keyboard.c", "key pressed: %u, (%i, %i)\n", key, x, y);
  switch(key)
  {
    case 27 : 
      exit(1); 
      break;
    case 'w':
    case 'W':
      break;
    case 's':
    case 'S':
      break;
    case 'a':
    case 'A':
      break;
    case 'd':
    case 'D':
      break;
    case 'h':
    case 'H':
      TW_log("keyboard.c", "todo print help. for now, try a mix of ASWD..");
      break;
    case 'Z':
    case 'z':
      TW_log("keyboard.c", "todo: zoom.");
      break;
    case 'X':
    case 'x':
      TW_log("keyboard.c", "todo: zoom..");
      break;
  }
}
