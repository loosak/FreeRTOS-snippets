#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"

// Globals
static const char* TAG = "task-notify";
TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;

void myTask1(void *pvParameter)
{
    ESP_LOGI(TAG, "the task2 has name: %s", pcTaskGetTaskName(myTask2Handle));
    for(;;)
    {
        xTaskNotifyGive(myTask2Handle);
        ESP_LOGI(TAG, ">>>%s send notification", __FUNCTION__);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

void myTask2(void *pvParameter)
{
    int notificationValue;

    for(;;)
    {
        notificationValue = ulTaskNotifyTake(pdTRUE, (TickType_t) portMAX_DELAY);

        if(notificationValue > 0)
        {
            ESP_LOGI(TAG, "<<<%s received notification: %d", __FUNCTION__, notificationValue);
        }
    }
}

/* Inside .cpp file, app_main function must be declared with C linkage */
extern "C" void app_main(void)
{
    esp_log_level_set(TAG, ESP_LOG_VERBOSE);
    ESP_LOGI(TAG, "Running at %s:%d", __FILE__, __LINE__);

    xTaskCreate(myTask1, "task1", 4096, (void*) 0, tskIDLE_PRIORITY, &myTask1Handle);
    
    /* Create the task, storing the handle. */
    BaseType_t xReturned = xTaskCreate(
                    myTask1,                /* Function that implements the task. */
                    "task1",                /* Text name for the task. */
                    4096,                   /* Stack size in words, not bytes. */
                    ( void * ) 0,           /* Parameter passed into the task. */
                    tskIDLE_PRIORITY,       /* Priority at which the task is created. */
                    &myTask1Handle );       /* Used to pass out the created task's handle. */

    if( xReturned == pdPASS )
    {
        /* The task was created.  Use the task's handle to delete the task. */
        ESP_LOGI(TAG, "xReturned == pdPASS");
        //vTaskDelete( xHandle );
    }
    xTaskCreate(myTask2, "task2", 4096, (void*) 0, tskIDLE_PRIORITY, &myTask2Handle);

    //vTaskStartScheduler();

}