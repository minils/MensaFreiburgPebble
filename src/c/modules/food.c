#include "food.h"

static void inbox_received_callback(DictionaryIterator *iter, void *context) {
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Received food data");
  Tuple *food_t = dict_find(iter, MESSAGE_KEY_MondayFood1 + s_index);
  if (food_t) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, food_t->value->cstring);
    strcpy(s_food[s_index], food_t->value->cstring);
    s_index++;
  }
  if (s_index == NUM_ITEMS) {
    s_index = 0;
    APP_LOG(APP_LOG_LEVEL_INFO, "Transmission complete!");
    time_t temp = time(NULL);
    struct tm *ticktime = localtime(&temp);
    size_t day = ticktime->tm_wday;
    if (day == 0) {
      day = 6;
    } else {
      day--;
    }
    if (day >= 5) {
      day = 0;
    }
    update_text_layer(s_food[day]);
  }
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
}

static void outbox_sent_callback(DictionaryIterator *iter, void *context) {
}

bool food_get_update() {
  DictionaryIterator *out_iter;
  AppMessageResult result = app_message_outbox_begin(&out_iter);
  if (result == APP_MSG_OK) {
    int value = 0;
    dict_write_int(out_iter, MESSAGE_KEY_Request, &value, sizeof(int), true);
    result = app_message_outbox_send();
  }
  return (result == APP_MSG_OK);
}

void food_init() {
  app_message_open(inbox_size, outbox_size);
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_sent(outbox_sent_callback);

  for (int i = 0; i < NUM_ITEMS; ++i) {
    s_food[i] = (char *) malloc(250);
  }
}

void food_deinit() {
  for (int i = 0; i < NUM_ITEMS; ++i) {
    free(s_food[i]);
  }
}
  
