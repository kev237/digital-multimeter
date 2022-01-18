#include <avr/io.h>
#include <avr/interrupt.h>

//----------------------------------------------------------------------------------------------
//Funktionen
//----------------------------------------------------------------------------------------------
void Display_delay(unsigned long delay_time_us);

void Display_Aus(void);
void Display_An(void);
void Display_Init(void);

void Display_HardwareInit(void);

void Display_RS_Output(void);
void Display_RS_High(void);
void Display_RS_Low(void);

void Display_EN_Output(void);
void Display_EN_High(void);
void Display_EN_Low(void);

void Display_DATA_Output(void);
void Display_DATA_BitHigh(unsigned char DataBit);
void Display_DATA_BitLow(unsigned char DataBit);

void Display_Clear(void);
void Display_ReturnHome(void);
void Display_ModeEntry(unsigned char Options);
void Display_Control(unsigned char Options);
void Display_CursorOrDisplayShift(unsigned char Options);
void Display_SetMPUInterface(unsigned char Options);
void Display_SetCursor(unsigned char row, unsigned char column);
void Display_Transfer4BitData(unsigned char Data);
void Display_Write(unsigned char ASCII_of_char);
void Display_Print(unsigned char* text2print, unsigned char length);
void Display_GenerateNewChar(unsigned char address, unsigned char* Pattern_New_Char);


//----------------------------------------------------------------------------------------------
//#define's für die verwendeten Funktionen
//----------------------------------------------------------------------------------------------

//Display_Clear
#define DISPLAY_CLEAR_FUNCTION  				0x01
#define DISPLAY_CLEAR_DISPLAY_DELAY 			4000
//Display_ReturnHome
#define DISPLAY_RETURN_HOME_FUNCTION 			0x02
#define DISPLAY_RETURN_HOME_DELAY 				2000
//Display_ModeEntry
#define DISPLAY_MODE_INCR_SHIFT_OFF				0x06
#define DISPLAY_MODE_INCR_SHIFT_ON 				0x07
#define DISPLAY_MODE_DECR_SHIFT_OFF 			0x04
#define DISPLAY_MODE_DECR_SHIFT_ON 				0x05
#define DISPLAY_MODE_DELAY 50
//Display_Control
#define DISPLAY_OFF 							0x08
#define DISPLAY_ON_CURSOR_OFF					0x0C
#define DISPLAY_ON_CURSOR_ON_BLINK_OFF 			0x0E
#define DISPLAY_ON_CURSOR_ON_BLINK_ON 			0x0F
#define DISPLAY_CONTROL_DELAY 50
//Display_CursorOrDisplayShift
#define DISPLAY_SHIFT_CURSOR_RECHTS 			0x14
#define DISPLAY_SHIFT_CURSOR_LINKS 				0x10
#define DISPLAY_SHIFT_DISPLAY_RECHTS 			0x1C
#define DISPLAY_SHIFT_DISPLAY_LINKS 			0x18
#define DISPLAY_CURSOR_OR_DISPLAY_SHIFT_DELAY 	50
//Display_FunctionSet
#define DISPLAY_MPU_4BIT_2_LINES_5x7_DOTS 		0x28
#define DISPLAY_SET_MPU_INTERFACE_DELAY			50	//100

#define DISPLAY_FUNKTION_SET_DDRAM_ADRESSE 		0x80
#define DISPLAY_FUNKTION_SET_CGRAM_ADRESSE 		0x40
#define DISPLAY_SET_RAM_ADRESSE_DELAY 			50

//----------------------------------------------------------------------------------------------
//Definitionen für das µECU-Board
//dieser Teil muss neu definiert werden für ein anderes Board
//die 4 Datenbits müssen zum gleichen Port gehören
//----------------------------------------------------------------------------------------------
#define F_CPU 18432000UL

#define DISPLAY_SW_DDR_REG		DDRD
#define DISPLAY_SW_PORT_REG		PORTD
#define DISPLAY_SW_BIT			PD7

#define DISPLAY_RS_DDR_REG		DDRB
#define DISPLAY_RS_PORT_REG		PORTB
#define DISPLAY_RS_BIT			PB0

#define DISPLAY_EN_DDR_REG		DDRB
#define DISPLAY_EN_PORT_REG		PORTB
#define DISPLAY_EN_BIT			PB1

#define DISPLAY_DATA_DDR_REG		DDRC
#define DISPLAY_DATA_PORT_REG		PORTC
#define DISPLAY_DATA_DB7_BIT		PC3
#define DISPLAY_DATA_DB6_BIT		PC2
#define DISPLAY_DATA_DB5_BIT		PC1
#define DISPLAY_DATA_DB4_BIT		PC0

#define DATAPORTMASKE (~((1 << DISPLAY_DATA_DB7_BIT) | (1 << DISPLAY_DATA_DB6_BIT) | (1 << DISPLAY_DATA_DB5_BIT) | (1 << DISPLAY_DATA_DB4_BIT)))


