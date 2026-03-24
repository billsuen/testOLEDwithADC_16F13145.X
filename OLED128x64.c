
#include "OLED128x64.h"
#include "OLED_FONTs.h"
#include "mcc_generated_files/i2c_host/mssp1.h"
#include "mcc_generated_files/i2c_host/i2c_host_event_types.h"



//#define ReverseScreen

volatile unsigned char TxBuffer[16] ;
static volatile i2c_host_error_t oledLastError = I2C_ERROR_NONE;

static bool OLED_WriteBytes(uint8_t *data, uint8_t len);

//extern void ReadEncoder(void);

void OLED_Init(void)
{
    DELAY_milliseconds(50); // MCC Delay added by Calvin - Must import DELAY foundation service 

    // Pure SSD1306 initialization sequence for a 128x64 I2C module.
    OLEDWrCmd(0xAE);      // display off
    OLEDWrCmd(0xD5);      // set display clock divide ratio / oscillator
    OLEDWrCmd(0x80);
    OLEDWrCmd(0xA8);      // set multiplex ratio
    OLEDWrCmd(0x3F);      // 1/64 duty
    OLEDWrCmd(0xD3);      // set display offset
    OLEDWrCmd(0x00);
    OLEDWrCmd(0x40);      // set display start line
    OLEDWrCmd(0x8D);      // charge pump setting
    OLEDWrCmd(0x14);      // enable charge pump
    OLEDWrCmd(0x20);      // memory addressing mode
    OLEDWrCmd(0x02);      // page addressing mode
    OLEDWrCmd(0xA1);      // segment remap
    OLEDWrCmd(0xC8);      // COM scan direction remap
    OLEDWrCmd(0xDA);      // COM pins hardware configuration
    OLEDWrCmd(0x12);
    OLEDWrCmd(0x81);      // contrast control
    OLEDWrCmd(0x7F);
    OLEDWrCmd(0xD9);      // pre-charge period
    OLEDWrCmd(0x22);
    OLEDWrCmd(0xDB);      // VCOM deselect level
    OLEDWrCmd(0x20);
    OLEDWrCmd(0xA4);      // output follows RAM
    OLEDWrCmd(0xA6);      // normal display
    OLEDWrCmd(0xAF);      // display on
}

/********** copy from LQ12864 **********/

/*********************set OLED display location************************************/
void OLED_Set_Pos(uint8_t x, uint8_t y) 
{ 
    uint8_t real_x = x;
	uint8_t posData[] = {
        OLED_Command_Mode,        // Control byte: Command stream
        (uint8_t)(0xB0 + y),      // Set Page Address
        (uint8_t)(((real_x & 0xF0) >> 4) | 0x10), // Set High Column Address
        (uint8_t)(real_x & 0x0F)                  // Set Low Column Address
    };
    (void)OLED_WriteBytes(posData, sizeof(posData));
}

// 批量寫入資料函式
void OLEDWrDatBulk(const uint8_t *data, uint16_t len)
{
    uint8_t buffer[17]; // 1 control byte + 16 data bytes max to save RAM
    uint16_t sent = 0;
    
    while(sent < len) {
        uint8_t chunk = (len - sent > 16) ? 16 : (len - sent);
        buffer[0] = OLED_Data_Mode; // 0x40
        for(uint8_t i = 0; i < chunk; i++) {
            buffer[i+1] = data[sent + i];
        }
        (void)OLED_WriteBytes(buffer, chunk + 1);
        sent += chunk;
    }
}

// 專門用於填充固定值的批量寫入（如清屏）
void OLEDWrDatFill(uint8_t val, uint16_t len)
{
    uint8_t buffer[17]; 
    buffer[0] = OLED_Data_Mode;
    for(uint8_t i = 1; i < 17; i++) buffer[i] = val;
    
    uint16_t sent = 0;
    while(sent < len) {
        uint8_t chunk = (len - sent > 16) ? 16 : (len - sent);
        (void)OLED_WriteBytes(buffer, chunk + 1);
        sent += chunk;
    }
}

/********** display 16*16 matrix, coordinate(x,y) y range 0~7 *********/
void OLED_Put16x16Ch(uint8_t x, uint8_t y, uint8_t index)
{
	OLED_Set_Pos(x, y);
    OLEDWrDatBulk(&Font16x16[index][0], 16);
    
	OLED_Set_Pos(x, y + 1);
    OLEDWrDatBulk(&Font16x16[index][16], 16);
}

/********** display 6*8 ASCII character at coordinate(x,y), y range 0~7 ***********/
void OLED_Put6x8Str(uint8_t x, uint8_t y, const uint8_t ch[])
{
	uint8_t c, j = 0;
    
	while (ch[j] != '\0')
	{
		c = ch[j] - 0x20;
		if(x > 122) { // 128 - 6
            x = 0;
            y++;
        }
		OLED_Set_Pos(x, y);
        OLEDWrDatBulk(Font6x8[c], 6);
		x += 6;
		j++;
	}
}

/******* display 8*16 ASCII character at coordinate(x,y), y range 0~7 *******/
void OLED_Put8x16Str(uint8_t x, uint8_t y, const uint8_t ch[])
{
    OLED_Put8x16ASCII(x, y, 255, (uint8_t*)ch); // 255 represents null-terminated
}

/******* display 8*16 ASCII character at coordinate(x,y), y range 0~7 *******/
void OLED_Put8x16ASCII(uint8_t x, uint8_t y, uint8_t no, uint8_t data[])
{
	uint8_t cIndex, j = 0;
    
	while ((no == 255 && data[j] != '\0') || (no != 255 && j < no))
	{
		cIndex = data[j] - 0x20;
		if(x > 120) {
            x = 0;
            y += 2;
        }
		OLED_Set_Pos(x, y);
        OLEDWrDatBulk(&Font8x16[cIndex][0], 8);
        
		OLED_Set_Pos(x, y + 1);
        OLEDWrDatBulk(&Font8x16[cIndex][8], 8);
        
		x += 8;
		j++;
	}
}

void OLED_CLS(void)
{
	for(uint8_t y = 0; y < 8; y++)
	{
		// 手動設定座標到第 0 列，確保清除所有 128 列 RAM
        uint8_t posData[] = {
            OLED_Command_Mode,
            (uint8_t)(0xB0 + y),
            0x10,
            0x00
        };
        (void)OLED_WriteBytes(posData, sizeof(posData));
        
        OLEDWrDatFill(0, 128); // 清除全部 128 列
	}
}

/***** display BMP picture, initial coordinate(x,y), x range 0~127, y range 0~7 *****/
void Draw_BMP(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t BMP[])
{
	uint16_t j = 0;
    uint8_t width = x1 - x0;

	for(uint8_t y = y0; y < y1; y++)
	{
		OLED_Set_Pos(x0, y);
        OLEDWrDatBulk(&BMP[j], width);
        j += width;
	}
}

/********************* End of LQ12864 ******************/

void  OLEDWrCmd(uint8_t command)
{
       TxBuffer[0] = OLED_Command_Mode;
       TxBuffer[1] = command;
       (void)OLED_WriteBytes((uint8_t *)TxBuffer, 2);
}

void  OLEDWrDat(uint8_t data)
{
       TxBuffer[0] = OLED_Data_Mode;
       TxBuffer[1] = data;
       (void)OLED_WriteBytes((uint8_t *)TxBuffer, 2);
}

static bool OLED_WriteBytes(uint8_t *data, uint8_t len)
{
    if (!I2C1_Host.Write(OLED_ADDRESS, data, len))
    {
        oledLastError = I2C_ERROR_BUS_COLLISION;
        return false;
    }

    while (I2C1_Host.IsBusy())
    {
    }

    oledLastError = I2C1_Host.ErrorGet();
    return (oledLastError == I2C_ERROR_NONE);
}

uint8_t OLED_LastErrorGet(void)
{
    return (uint8_t)oledLastError;
}

void displayOn(void)
{
    OLEDWrCmd(0xAF);        //display on
}

// Turns display off.
void displayOff(void)
{
    OLEDWrCmd(0xAE);		//display off
}

// the most basic function, set a single pixel
//void drawPixel(uint8_t x, uint8_t y, uint8_t color) 
//{
//    if ((x < 0) || (x >= 128) || (y < 0) || (y >= 64))
//        return;
//
//    // x is which column
//    if (color == WHITE) 
//        BMP_buffer[x+ (y/8)*128] |= _BV((y%8));  
//    else
//        BMP_buffer[x+ (y/8)*128] &= ~_BV((y%8)); 
//}

