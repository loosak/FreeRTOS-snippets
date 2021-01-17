FreeRTOS Task Notification
==========================

Lite 

## ESP32 ESP-IDF 

```
. esp-idf/export.sh
cd freertos-snippets/task-notifications
idf.py set-target [ esp32 | esp32s2 ]
idf.py build
idf.py -p /dec/cu.[SLAB_USBtoUART | ] flash monitor
```