#ifndef CONFIG_16F13145_H
#define CONFIG_16F13145_H

#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/adc/adc.h"
#include <stdint.h>

void USER_CLB1I0_ISR(void);
void USER_TMR0_ISR(void);
void USER_ADC_ISR(void);
void VR_TO_STR(uint16_t value, uint8_t *buffer);
void BATT_TO_STR(uint16_t value, uint8_t *buffer);

struct {
	uint8_t	switchFlag :1;
	uint8_t VR_ConvertFlag :1;
	uint8_t BATT_ConvertFlag :1;
	uint8_t POINT_TO_VR :1;
}stateFlag;

#define switchFlag			stateFlag.switchFlag
#define VR_ConvertFlag		stateFlag.VR_ConvertFlag
#define BATT_ConvertFlag	stateFlag.BATT_ConvertFlag
#define POINT_TO_VR			stateFlag.POINT_TO_VR

#define IND_ON 	0
#define IND_OFF 1
#define SET 1
#define	CLEAR 0

#define VR_SAMPLE_RATE	22
#define ADC_CONVERT_SETTING	8

extern volatile uint8_t		VR_SampleCnt;
extern volatile uint8_t		VR_ConvertCnt;
extern volatile uint8_t		BATT_ConvertCnt;

extern volatile adc_result_t	VR_tmpValue;
extern volatile adc_result_t	VR_avgValue;
extern volatile adc_result_t	BATT_tmpValue;
extern volatile adc_result_t	BATT_avgValue;

//extern uint16_t BATT_realValue;

#endif // CONFIG_16F13145_H
