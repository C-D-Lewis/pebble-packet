#include "pebble-packet.h"

#define TAG "pebble-packet"

static DictionaryIterator *s_outbox;

/********************************** Internal **********************************/

static char *result_to_string(AppMessageResult result) {
  switch (result) {
    case APP_MSG_OK:               return "Success";
    case APP_MSG_SEND_TIMEOUT:     return "Send timeout";
    case APP_MSG_SEND_REJECTED:    return "Send rejected";
    case APP_MSG_NOT_CONNECTED:    return "Not connected";
    case APP_MSG_APP_NOT_RUNNING:  return "App not running";
    case APP_MSG_INVALID_ARGS:     return "Invalid arguments";
    case APP_MSG_BUSY:             return "Busy";
    case APP_MSG_BUFFER_OVERFLOW:  return "Buffer overflow";
    case APP_MSG_ALREADY_RELEASED: return "Already released";
    case APP_MSG_OUT_OF_MEMORY:    return "Out of memory";
    case APP_MSG_CLOSED:           return "Closed";
    case APP_MSG_INTERNAL_ERROR:   return "Internal error";
    case APP_MSG_INVALID_STATE:    return "Invalid state. Is AppMessage open?";
    default: {
      static char s_buff[32];
      snprintf(s_buff, sizeof(s_buff), "Unknown error (%d)", result);
      return &s_buff[0];
    }
  }
}

/************************************ API *************************************/

bool packet_begin() {
  AppMessageResult r = app_message_outbox_begin(&s_outbox);
  if(r != APP_MSG_OK) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "%s: Error opening outbox! Reason: %s", TAG, result_to_string(r));
    return false;
  }
  return true;
}

bool packet_put_integer(int key, int value) {
  DictionaryResult r = dict_write_int32(s_outbox, key, value);
  if(r != DICT_OK) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "%s: Error adding integer to outbox!", TAG);
    return false;
  }
  return true;
}

bool packet_put_string(int key, char *string) {
  DictionaryResult r = dict_write_cstring(s_outbox, key, string);
  if(r != DICT_OK) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "%s: Error adding string to outbox!", TAG);
    return false;
  }
  return true;
}

bool packet_send() {
  AppMessageResult r = app_message_outbox_send();
  if(r != APP_MSG_OK) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "%s: Error sending outbox! Reason: %s", TAG, result_to_string(r));
    return false;
  }
  return true;
}
