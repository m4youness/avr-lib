#include "al.h"
#include <stdio.h>

int main(void) {
  pin_mode(13, HIGH);
  while (1) {
    digital_write(13, HIGH);
    DELAY_MS(1000);

    digital_write(13, LOW);
    DELAY_MS(1000);
  }
  return 0;
}
