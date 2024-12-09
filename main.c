#include "al.h"
#include <stdio.h>

int main(void) {
  serial_begin(9600);
  while (1) {
    serial_print("Hello World!\r\n");
    DELAY_MS(1000);
  }
  return 0;
}
