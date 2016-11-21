#include <pebble.h>

#include "modules/food.h"

#include "windows/main_window.h"

static void init(void) {
  food_init();
  main_window_push();
}

static void deinit(void) {
  food_deinit();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
