#pragma once

#include <pebble.h>

// Begin a new packet. Must be called before putting anything in it.
// Returns:
//   bool - true if the packet was successfully initialised, false otherwise.
//          Check app logs to see any error reason.
bool packet_begin();

// Put an integer into the packet.
// Parameters:
//   key   - The tuple's key.
//   value - The tuple's integer value.
// Returns:
//   bool - true if the integer was written to the packet, false otherwise.
bool packet_put_integer(int key, int value);

// Put a string into the packet.
// Parameters:
//   key    - The tuple's key.
//   string - The tuple's string value.
// Returns:
//   bool - true if the string was written to the packet, false otherwise.
bool packet_put_string(int key, char *string);

// Send the packet.
// Returns:
//   bool - true if the packet was successfully sent, false otherwise.
//          Check app logs to see any error reason.
bool packet_send();
