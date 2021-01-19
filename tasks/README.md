FreeRTOS Task Notification
==========================

Light Weight Event Group
[RTOS Task Notifications](http://www.realtimeengineers.co.uk/RTOS_Task_Notification_As_Event_Group.html)

## ESP32 ESP-IDF 

```
. esp-idf/export.sh
cd freertos-snippets/task-notifications
idf.py set-target [ esp32 | esp32s2 ]
idf.py build
idf.py -p /dev/cu.[SLAB_USBtoUART | ] flash monitor
```