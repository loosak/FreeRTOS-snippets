#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

// Globals
static const char* TAG = "tasks";
TaskHandle_t myTask1Handle = NULL;

void myTask1(void* pvParameter)
{
    // https://embeddedartistry.com/blog/2017/03/15/c-casting-or-oh-no-they-broke-malloc/
    //int count = reinterpret_cast<intptr_t>(pvParameter); //reinterpret_cast<int>(pvParameter);
    //count = static_cast<int>(count);
    int count = static_cast<int>(reinterpret_cast<intptr_t>(pvParameter));

    for(;;)
    {
        ESP_LOGI(TAG, "Hello World from %s [%d]", __FUNCTION__, count++);
        if(count == 55)
        {
            ESP_LOGI(TAG, "delete task %s", __FUNCTION__);
            vTaskDelete(myTask1Handle);
        }
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

/* Inside .cpp file, app_main function must be declared with C linkage */
extern "C" void app_main(void)
{
    esp_log_level_set(TAG, ESP_LOG_VERBOSE);
    ESP_LOGI(TAG, "Running at %s:%d", __FILE__, __LINE__);

    int pass = 25;
    /* Create the task, storing the handle. */
    BaseType_t xReturned = xTaskCreate(
                            myTask1,                /* Function that implements the task. */
                            "task1",                /* Text name for the task. */
                            4096,                   /* Stack size in words, not bytes. */
                            (void *) pass,          /* Parameter passed into the task. */
                            tskIDLE_PRIORITY,       /* Priority at which the task is created. */
                            &myTask1Handle );       /* Used to pass out the created task's handle. */

    if( xReturned == pdPASS )
    {
        /* The task was created.  Use the task's handle to delete the task. */
        ESP_LOGI(TAG, "xReturned == pdPASS");
        //vTaskDelete( xHandle );
    }

    //vTaskStartScheduler();
}