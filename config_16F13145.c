#include "config_16F13145.h"
#include "mcc_generated_files/adc/adc.h"
#include "mcc_generated_files/system/pins.h"
#include <stdint.h>

volatile adc_result_t	VR_tmpValue = 0;
volatile adc_result_t	VR_avgValue = 0;
volatile adc_result_t	BATT_tmpValue = 0;
volatile adc_result_t	BATT_avgValue = 0;

volatile uint8_t	VR_ConvertCnt = 0;
volatile uint8_t	VR_SampleCnt = 0;
volatile uint8_t	BATT_ConvertCnt = 0;

void USER_CLB1I0_ISR()
{
	// Add your custom CLB1I0 interrupt code here
	if(SW_PORT == 1)
		switchFlag = SET;
}

void USER_TMR0_ISR()
{
	// Add your custom TMR0 interrupt code here

	/*
	VR_SamlpeCnt++;
	if(VR_SamlpeCnt >= VR_SAMPLE_RATE)
	{
		VR_SamlpeCnt = 0;
		ADC_ConversionStart();
	}
	*/

	VR_SampleCnt = (VR_SampleCnt + 1) % VR_SAMPLE_RATE;
	if(VR_SampleCnt == 0)
	{
		if(POINT_TO_VR)
		{
			ADC_ChannelSelect(VR);
			ADC_ConversionStart();
		}
		else
		{
			ADC_ChannelSelect(VIN);
			ADC_ConversionStart();
		}
		
	}
}

void USER_ADC_ISR()
{
	if(POINT_TO_VR)
	{
		VR_tmpValue += ADC_ConversionResultGet();
		VR_ConvertCnt++;

		if(VR_ConvertCnt >= ADC_CONVERT_SETTING)
		{
			VR_ConvertCnt = 0;
			VR_avgValue = VR_tmpValue / ADC_CONVERT_SETTING;
			VR_tmpValue = 0;
			POINT_TO_VR = CLEAR;
			VR_ConvertFlag = SET;
		}
	}
	else	//!POINT_TO_VR = point to BATT
	{
		BATT_tmpValue += ADC_ConversionResultGet();
		BATT_ConvertCnt++;
		
		POINT_TO_VR = SET;

		if(BATT_ConvertCnt >= ADC_CONVERT_SETTING)
		{
			BATT_ConvertCnt = 0;
			BATT_avgValue = BATT_tmpValue / ADC_CONVERT_SETTING;
			BATT_tmpValue = 0;
			BATT_ConvertFlag = SET;
		}
	}
}


void VR_TO_STR(uint16_t value, uint8_t *buffer)
{
	/*
	 * 假設傳入的 stage buffer 至少有 5 bytes。
	 * 我們先填入預設空白與終止字元, 再從右邊填數字,
	 * 並使用前置/顯式索引以避免編譯器對於後置遞減的
	 * 無號比較或退化比較警告。
	 */
	buffer[0] = ' ';
	buffer[1] = ' ';
	buffer[2] = ' ';
	buffer[3] = ' ';
	buffer[4] = '\0';

	int idx = 3; // 從右邊第一個數字位置開始

	if (value == 0) {
		buffer[idx] = '0';
		return;
	}

	while (value > 0 && idx >= 0) {
		buffer[idx] = '0' + (value % 10);
		value /= 10;
		--idx;
	}

	/* 前方已經是空白，不需再填 */
}

void BATT_TO_STR(uint16_t value, uint8_t *buffer)
{
	 /* buffer format: d.dd\0  (total 5 bytes) */
    buffer[0] = '0';
    buffer[1] = '.';
    buffer[2] = '0';
    buffer[3] = '0';
    buffer[4] = '\0';

    /* 僅取最低 3 位，避免誤用 */
    value %= 1000;

    /* 個位 (0.0X) */
    buffer[3] = '0' + (value % 10);
    value /= 10;

    /* 十位 (0.X0) */
    buffer[2] = '0' + (value % 10);
    value /= 10;

    /* 百位 (X.00) */
    buffer[0] = '0' + (value % 10);
}
