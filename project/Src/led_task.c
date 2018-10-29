#include "led_task.h"
#include "gpio.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
//*****************************************************************************

#define LED_TASK_PRIO          3        //�������ȼ�
#define LED_STK_SIZE           128       //�����ջ��С

//*****************************************************************************
//
// This task toggles the user selected LED at a user selected frequency. User
// can make the selections by pressing the left and right buttons.
//
//*****************************************************************************
void
DemoLEDTask(void *pvParameters)
{
    while(1)
    {
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
        vTaskDelay(1000);       
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
        vTaskDelay(1000);     
    }
}

//*****************************************************************************
//
// Initializes the LED task.
//
//*****************************************************************************
void
LEDTaskInit(void)
{

    //
    // Create the LED task.
    //
    xTaskCreate(
                        DemoLEDTask,                       //������
                       (const portCHAR *)"LED", //�������� 
                        LED_STK_SIZE,              // �����ջ��С 
                        NULL,       
                        LED_TASK_PRIO,
                        NULL
    );
    
    
}

