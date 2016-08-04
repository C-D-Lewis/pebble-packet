#pragma once

#include <pebble.h>

bool packet_begin();

bool packet_put_integer(int key, int value);

bool packet_put_string(int key, char *string);

bool packet_send();

