# pebble-packet

Simple wrapper for AppMessage integer and string types with built in error
reporting. Never directly use `DictionaryIterator` or `Tuple` again!

Available on [NPM](https://www.npmjs.com/package/pebble-packet).


## How to use

1. Install the Pebble package:

  ```
  $ pebble package install pebble-packet
  ```

2. Ensure `AppMessage` is open:

  ```c
  const int inbox = 128;
  const int outbox = 128;
  app_message_open(inbox, outbox);
  ```

3. Begin, build, and send a packet:

  ```c
  if(packet_begin()) {
    packet_put_integer(AppKeyInteger, 42);
    packet_put_string(AppKeyString, "Don't talk to me about life.");
    packet_send();
  }
  ```

4. Get data from a received dictionary:

  ```c
  static void in_recv_handler(DictionaryIterator *iter, void *context) {
    if(packet_contains_key(iter, MESSAGE_KEY_Integer)) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Got int: %d", packet_get_integer(iter, MESSAGE_KEY_Integer));
    }

    if(packet_contains_key(iter, MESSAGE_KEY_String)) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Got string: %s", packet_get_string(iter, MESSAGE_KEY_String));
    }

    if(packet_contains_key(iter, MESSAGE_KEY_Boolean)) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Got int: %s", packet_get_boolean(iter, MESSAGE_KEY_Boolean) ? "true" : "false");
    }

    APP_LOG(APP_LOG_LEVEL_INFO, "Size: %d", packet_get_size(iter));
  }
  ```


## Documentation

See `include/pebble-packet.h` for function documentation.


## Changelog

**1.0**
- Initial version

**1.1**
- Add `packet_get_size()`, `packet_contains_key()`, `packet_put_boolean()`, 
  `packet_get_boolean()`, `packet_get_integer()`, and `packet_get_string()`.


## TODO

- `AppMessageOutboxFailed` handling.
- Some kind of 'is there a packet in progress?' boolean check.
- Some kind of 'is `AppMessage` open?' check.
