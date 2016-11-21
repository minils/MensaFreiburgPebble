#pragma once

#include <pebble.h>

static Window *s_window;
static TextLayer *s_text_layer;

void update_text_layer(char* text);

static void select_click_handler(ClickRecognizerRef recognizer, void *context);

static void up_click_handler(ClickRecognizerRef recognizer, void *context);

static void down_click_handler(ClickRecognizerRef recognizer, void *context);

static void click_config_provider(void *context);

static void window_load(Window *window);

static void window_unload(Window *window);

void main_window_push();
