#pragma once

#include <pebble.h>

#include "../windows/main_window.h"

#define NUM_ITEMS 10

static const uint32_t inbox_size = 256;
static const uint32_t outbox_size = 64;
static char* s_food[NUM_ITEMS];
static int s_index = 0;

static void inbox_received_callback(DictionaryIterator *iter, void *context);
static void inbox_dropped_callback(AppMessageResult reason, void *context);
static void outbox_sent_callback(DictionaryIterator *iter, void *context);

bool food_get_update();

void food_init();

void food_deinit();
