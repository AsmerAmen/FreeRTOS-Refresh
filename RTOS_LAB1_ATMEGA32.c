/*
 * RTOS_LAB1_ATMEGA32.c
 *
 * Created: 1/27/2014 12:22:11 AM
 *  Author: Islam
 */ 

#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "LCD.h"
#include "utilss.h"
#include "semphr.h"
#include <avr/delay.h>
#include "Types.h"
#include "ADC_Driver.h"

 /* create Queue */
xQueueHandle xQueue;



/* Define Tasks Priorities */
#define  TASK_PRIORITY (2)


/*tasks codes prototypes */
 void task1_code(void*pvParamter);
 void task2_code(void*pvParamter);


int main(void)
{
	/*initialize LCD*/
	LCD_voidInit('C');
	LCD_voidString((U8* const)"LCD ON ");
	_delay_ms(500);
	LCD_voidString((U8* const)"1 ");
	_delay_ms(500);
	LCD_voidString((U8* const)"2 ");
	_delay_ms(500);
	LCD_voidString((U8* const)"3 ");
	_delay_ms(500);

	/* ADC */
	ADC_voidInit();
	ADC_voidInterrupt();


	LCD_voidClear();
	LCD_voidString((U8* const)"ADC Interrupt.");
	_delay_ms(2000);

	xQueue = xQueueCreate(5, sizeof(int));
	if(xQueue != NULL){
		LCD_voidClear();
		LCD_voidString((U8* const)"Queue Created.");
		_delay_ms(2000);
		/*Create tasks*/
		xTaskCreate(task1_code, NULL, 400, NULL, TASK_PRIORITY, NULL);
//		xTaskCreate(task2_code, NULL, 400, NULL, TASK_PRIORITY, NULL);

		/*start Scheduler */
		vTaskStartScheduler();
	}

	for(;;);

	return 0;
}


	/*Task1 Code */
 void task1_code(void*pvParamter){

	portBASE_TYPE xTicksToWait = 100/portTICK_RATE_MS;
	int intTemp = 0;
	portBASE_TYPE xStatus;
	for (;;)
	{
		LCD_voidClear();
		LCD_voidString((U8* const)"Task 1");
		_delay_ms(500);
		if(uxQueueMessagesWaiting(xQueue)){
			xStatus = xQueueReceive(xQueue, &intTemp, xTicksToWait);
			if(xStatus == pdPASS){
				LCD_voidClear();
				LCD_voidString((U8* const)"Temp: ");
				LCD_voidInteger((int)intTemp);
			}
			else{
//				LCD_voidClear();
//				LCD_voidString((U8* const)"Couldn't Recv.");
			}

			vTaskDelay(2000);
		}
	}
}


	/*Task1 Code */
void task2_code(void*pvParamter){

	portBASE_TYPE xTicksToWait = 100/portTICK_RATE_MS;
	U16 sampledValue;
	int Analog;
	for(;;){
//		LCD_voidClear();
//		LCD_voidString((U8* const)"Task 2");
//		_delay_ms(500);

		sampledValue = ADC_u16Read(5);

		Analog = ( sampledValue * 500 ) / RESOLUTION ;

		portBASE_TYPE xStatus = xQueueSend(xQueue, &Analog, xTicksToWait);
		if(xStatus != pdPASS){
//			LCD_voidClear();
//			LCD_voidString((U8* const)"Failed to send");
		}
	}
//	vTaskDelay(2000);
}



void __vector_16 (void)
{
	clr_bit(SREG, 7);
//	LCD_voidClear();
//	LCD_voidString((U8* const)"ISR");
//	_delay_ms(500);

	volatile portBASE_TYPE xStatus;
	U16 Analog = ( ADCH * 500 ) / RESOLUTION ;
	int temp = (int) Analog;
	xStatus = xQueueSendToBackFromISR(xQueue, (const void *) &temp, 0);
	if(xStatus != pdPASS){
		LCD_voidClear();
		LCD_voidString((U8* const)"Failed to send");
	}
	set_bit(ADCSRA, 4);
	set_bit(SREG, 7);
}
