#include "fft.h"
#include "arm_math.h"
#include "math.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "adc.h"

//*****************************************************************************

#define FFT_TASK_PRIO          4        //任务优先级
#define FFT_STK_SIZE           128       //任务堆栈大小

extern uint32_t ADC1_SampleValue[512];
extern float fft_outputbuff[1024];
extern float fft_inputbuff[2048];
//*****************************************************************************
//
// This task toggles the user selected LED at a user selected frequency. User
// can make the selections by pressing the left and right buttons.
//
//*****************************************************************************
void
DemoFFTTask(void *pvParameters)
{
		//FOR循环使用
		uint16_t i=0,j=0;
		//ADC转换后的值
		double ADC1_Value;		
		//定义fft句柄
		arm_cfft_radix4_instance_f32 fft;
	  arm_cfft_radix4_init_f32(&fft,1024,0,1);
		for(i=0;i<1024;i++)
		{
			fft_inputbuff[2*i]=100+	
												 10*arm_sin_f32(2*3.1415*i/1024)+
												 30*arm_sin_f32(2*3.1415*i*4/1024)+
												 30*arm_sin_f32(2*3.1415*i*8/1024);
		}	
    while(1)
    {
			for(i=0;i<256;i++)
			{
				ADC1_Value=(double)((uint16_t)(ADC1_SampleValue[i]>>16));
				ADC1_Value=ADC1_Value*3.3/4096;
	//			fft_inputbuff[j++]=ADC1_Value;
	//			fft_inputbuff[j++]=0;
				printf("%d:%.2f\r\n",i,ADC1_Value);
				ADC1_Value=(double)((uint16_t)ADC1_SampleValue[i]);
				ADC1_Value=ADC1_Value*3.3/4096;
				printf("%d:%.2f\r\n",i+1,ADC1_Value);			
	//			fft_inputbuff[j++]=ADC1_Value;
	//			fft_inputbuff[j++]=0;
			}
			
			arm_cfft_radix4_f32(&fft,fft_inputbuff);
			arm_cmplx_mag_f32(fft_inputbuff,fft_outputbuff,1024);
			
			for(i=0;i<1024;i++)
			{
				printf("%d:%f\r\n",i,fft_outputbuff[i]);
			}
			j=0;  

			vTaskDelay(500); 
    }
}

//*****************************************************************************
//
// Initializes the FFT task.
//
//*****************************************************************************
void
FFTTaskInit(void)
{

    //
    // Create the LED task.
    //
    xTaskCreate(
                        DemoFFTTask,                       //任务函数
                       (const portCHAR *)"FFT", //任务名称 
                        FFT_STK_SIZE,              // 任务堆栈大小 
                        NULL,       
                        FFT_TASK_PRIO,
                        NULL
    );
    
    
}