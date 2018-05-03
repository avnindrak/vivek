#ifndef DS1307_H_
#define DS1307_H_

typedef struct _time{
	uint8_t _RESERVED;
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t dow;
	uint8_t date;
	uint8_t mon;
	uint8_t year;
}TIME;

typedef struct{
	uint8_t address;
	union{
		void *data_to_store;
		void *data_to_read;
	};
	uint8_t len_of_data;
}DS1307_EEPROM_Data;

extern void DS1307_Set_Time(void* time);
extern void DS1307_Read_Time(void* time);
//extern void DS1307_Store_Data(void *data, uint8_t data_len);
//extern void DS1307_Read_Data(void *data, uint8_t data_len);
extern void DS1307_Store_Data(DS1307_EEPROM_Data *);
extern void DS1307_Read_Data(DS1307_EEPROM_Data *);

#endif