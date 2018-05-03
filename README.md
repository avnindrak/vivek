# Atmega DS1307 Bluetooth

### Connection between Bluetooth and Atmega8
|Atmega Pin|Bluetooth Pin|
|---|---|
|TXD|Rx|
|RXD|Tx|

### Connection between DS1307 and Atmega8
|Atmega Pin|DS1307 Pin|
|---|---|
|SCL|SCL|
|SDA|SDA|

### Switches
Connect push buttons as shown in the _Proteus_ schematic file.

### Working
Under Normal cases the program skips the time setting part and goes to the infinite `while` loop.
```c
while (1)
{
  /* Do your work here*/
}
```

But when `PIND7` is pressed while _Resetting_ the UART code gets executed.
```c
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
```

### Serial Bluetooth
1. Install any Bluetooth Serial app in your mobile phone.
   * We tested with Arduino Bluetooth Controller App
2. Connect to the Bluetooth module.
3. Reset the Controller while pressing the `PIND7` button.
You will be presented with the command text.
