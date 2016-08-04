# pebble-packet

Simple wrapper for AppMessage integer and string types with built in error reporting.

Available on [NPM](https://www.npmjs.com/package/pebble-packet).

## How to use

1. Ensure `AppMessage` is open:

  ```c
  const int inbox = 128;
  const int outbox = 128;
  app_message_open(inbox, outbox);
  ```

2. Begin, build, and send a packet:

  ```c
  if(packet_begin()) {
    packet_put_integer(AppKeyInteger, 42);
    packet_put_string(AppKeyString, "Don't talk to me about life.");
    packet_send();
  }
  ```

## Documentation

See `include/pebble-packet.h` for function documentation.

## TODO

- `AppMessageOutboxFailed` handling.
- Some kind of 'is there a packet in progress?' boolean check.
- Some kind of 'is `AppMessage` open?' check.
