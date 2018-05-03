/*
 * RTC-Bluetooth.c
 *
 * Created: 03-05-2018 15:46:38
 * Author : vivek
 */

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#include "DS1307.h"
#include "Driver_USART.h"

int main(void)
{
	char cmd[30];
	TIME time;
	int hour,min,sec;

	PORTD = 1<<7;
	if((PIND & 1<<7) == 0){
		USART_Initialise(USART_Character_Size_8|USART_Tx_Enable|USART_Rx_Enable);
		while (1)
		{
			while (USART_Status_Flag & USART_Tx_Busy){}
			USART_Transmit("\r\n1.SetTime\r\n2.ShowTime\r\n3.Exit\r\n>>",36);
			USART_Receive(cmd,1);
			while (USART_Status_Flag & USART_Rx_Busy){}

			if(cmd[0]== '1'){
				USART_Transmit("\r\nSetTime as HH MM SS\r\n>>",24);
				USART_Receive(cmd,8);
				while (USART_Status_Flag & USART_Rx_Busy){}
				cmd[9]=0;

				sscanf(cmd,"%d %d %d",&hour,&min,&sec);

				DS1307_Read_Time(&time);
				time.hour=hour; time.min=min; time.sec=sec;
				DS1307_Set_Time(&time);
				USART_Transmit("Time Set",8);
			}
			else if(cmd[0]== '2'){
				DS1307_Read_Time(&time);
				sprintf(cmd,"\r\n%02d:%02d:%02d\r\n",time.hour,time.min,time.sec);
				USART_Transmit(cmd,12);
			}
			else if(cmd[0]== '3'){
				USART_Transmit("Exiting",7);
				break;
			}
		}
	}

    while (1)
    {

    }
}
