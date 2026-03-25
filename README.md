# OLED + ADC 顯示專案 (PIC16F13145)

這個專案使用 PIC16F13145 搭配 I2C 介面的 128x64 OLED (SSD1306)，
並透過 ADC 週期性量測 `VR (RA4)` 與 `VIN (RA5)`，將量測結果顯示在 OLED 上。

OLED 驅動程式基於 MPLAB Code Configurator (MCC) 產生的 I2C 函式庫，
而專案本身另外整合了 CLB、Timer0、ADC 與 FVR。

## 功能
- 支援 SSD1306 控制晶片。
- 提供文字（6x8, 8x16）及自訂中文字元（16x16）顯示。
- 提供點陣圖 (Bitmap) 顯示功能。
- 直接寫入模式，不需額外記憶體緩衝區 (RAM buffer)。
- 使用 `Timer0` 週期性觸發 ADC 單次轉換。
- 交替量測 `VR (RA4)` 與 `VIN (RA5)`。
- 以軟體方式累積 `8` 次 ADC 結果並取平均。
- 使用 `FVR` 作為 ADC reference。
- 使用 `CLB1I0 / CLB1I1` 中斷讀取按鍵狀態並切換顯示/指示燈。
- 以 `RA0 / RA1` 控制綠燈 / 紅燈指示目前狀態。

## 目前顯示內容
目前 `main.c` 的 OLED 畫面內容如下：

- 第 0 頁顯示標題：`PIC16F13145`
- 第 2 頁顯示 `VR_avgValue` 的 ADC 平均值
- 第 4 頁顯示 `BATT_avgValue` 的 ADC 平均值
- 第 6 頁顯示由 `BATT_avgValue` 換算出的 `Vin`

當 `switchFlag == SET` 時：
- 綠燈亮、紅燈滅
- OLED 持續更新 ADC 顯示

當 `switchFlag == CLEAR` 時：
- 紅燈亮、綠燈滅

## Pin Mapping

| Pin | Symbol / Alias | Direction | Function |
| --- | --- | --- | --- |
| RA0 | `IND_G` | Output | 綠色指示燈 |
| RA1 | `IND_R` | Output | 紅色指示燈 |
| RA2 | `SW` | Input | 按鍵輸入，同時送入 `CLB1:CLBIN0` |
| RA4 | `VR` | Analog Input | ADC 量測通道 `VR` |
| RA5 | `VIN` | Analog Input | ADC 量測通道 `VIN` |
| RC6 | `SCL` | I2C | OLED `SCL`，對應 `MSSP1 SCL1` |
| RC7 | `SDA` | I2C | OLED `SDA`，對應 `MSSP1 SDA1` |

補充說明：
- `RA2` 目前透過 `CLBIN0PPS` 接到 `CLB1`，由 `CLB1I0 / CLB1I1` ISR 改變 `switchFlag`。
- `RC6 / RC7` 為 OLED 使用的 I2C 腳位，需要外部 pull-up。
- `RA4 / RA5` 為 ADC 類比輸入腳位，目前由程式交替取樣。

## 依賴項目
本專案需要以下由 MCC 產生的模組支援：
1.  **I2C Host (MSSP):** 用於 I2C 通訊。程式中使用 `I2C1_Host`。
2.  **Delay:** 用於初始化的延遲。
3.  **ADC:** 用於量測 `VR` 與 `VIN`。
4.  **FVR:** 作為 ADC 參考電壓。
5.  **Timer0:** 週期性啟動 ADC 取樣。
6.  **CLB:** 用於按鍵相關中斷事件。

並需要包含以下驅動程式自有的檔案：
1.  `OLED128x64.h`
2.  `OLED128x64.c`
3.  `OLED_FONTs.h` (提供字型資料)
4.  `config_16F13145.h`
5.  `config_16F13145.c`

## 使用方法

### 1. 初始化
在 `main.c` 中，務必先完成系統、FVR ready 等待、ADC 狀態初始化，以及 OLED 初始化。
```c
#include "mcc_generated_files/adc/adc.h"
#include "mcc_generated_files/fvr/fvr.h"
#include "mcc_generated_files/system/system.h"
#include "OLED128x64.h"

void main(void)
{
    SYSTEM_Initialize();

    while(!FVR_IsOutputReady())
    {
    }

    POINT_TO_VR = SET;
    ADC_ChannelSelect(VR);
    ADC_AcquisitionTimeSet(32);

    OLED_Init();
    OLED_CLS();

    // 接下來註冊 callback 並開啟全域 / 周邊中斷
}
```

### 2. 目前主程式行為
目前專案中的主流程大致如下：
```c
SYSTEM_Initialize();
while(!FVR_IsOutputReady())
{
}

POINT_TO_VR = SET;
ADC_ChannelSelect(VR);
ADC_AcquisitionTimeSet(32);

CLB1_CLB1I0_SetInterruptHandler(USER_CLB1I0_ISR);
CLB1_CLB1I1_SetInterruptHandler(USER_CLB1I1_ISR);
TMR0_PeriodMatchCallbackRegister(USER_TMR0_ISR);
ADC_ConversionDoneCallbackRegister(USER_ADC_ISR);

INTERRUPT_GlobalInterruptEnable();
INTERRUPT_PeripheralInterruptEnable();

OLED_Init();
OLED_CLS();
OLED_Put8x16Str(24, 0, "PIC16F13145");

while (1)
{
    // 根據 switchFlag 更新 LED
    // 根據 VR_ConvertFlag / BATT_ConvertFlag 更新 OLED 顯示
}
```

### 3. ADC 資料流
目前 ADC 相關流程如下：

1. `USER_TMR0_ISR()` 依固定週期交替選擇 `VR` 或 `VIN` channel。
2. 每次只啟動一次 `ADC_ConversionStart()`。
3. `USER_ADC_ISR()` 在 `ADC Conversion Done` 中斷中讀值。
4. 每一路各累積 `ADC_CONVERT_SETTING` 次後取平均。
5. `VR_ConvertFlag` / `BATT_ConvertFlag` 置位後，由主迴圈更新 OLED。

## 主要 API 說明

`void OLED_Init(void)`
> 初始化 OLED 模組。必須在使用任何其他 OLED 函式之前呼叫。

`void OLED_CLS(void)`
> 清除整個螢幕。

`void OLED_Put8x16Str(uint8_t x, uint8_t y, const uint8_t ch[])`
> 在指定座標顯示 8x16 大小的 ASCII 字串。
> - `x`: 起始 X 座標 (0-127)
> - `y`: 起始 Y **頁**座標 (0-7)
> - `ch[]`: 要顯示的字串

`void OLED_Put6x8Str(uint8_t x, uint8_t y, const uint8_t ch[])`
> 在指定座標顯示 6x8 大小的 ASCII 字串。
> - `x`: 起始 X 座標 (0-127)
> - `y`: 起始 Y **頁**座標 (0-7)
> - `ch[]`: 要顯示的字串

`void OLED_Put16x16Ch(uint8_t x, uint8_t y, uint8_t index)`
> 在指定座標顯示 `OLED_FONTs.h` 中定義的 16x16 中文字元。
> - `x`: 起始 X 座標 (0-127)
> - `y`: 起始 Y **頁**座標 (0-7)
> - `index`: 字元在 `Font16x16` 陣列中的索引

`void Draw_BMP(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t BMP[])`
> 在指定區域顯示點陣圖。
> - `x0`, `y0`: 左上角座標
> - `x1`, `y1`: 右下角座標
> - `BMP[]`: 點陣圖資料陣列

`void displayOn(void)`
> 喚醒螢幕（從睡眠模式）。

`void displayOff(void)`
> 讓螢幕進入睡眠模式以省電。

## 專案內自訂函式

`void USER_CLB1I0_ISR(void)`
> 按鍵觸發 `switchFlag = SET`。

`void USER_CLB1I1_ISR(void)`
> 按鍵觸發 `switchFlag = CLEAR`。

`void USER_TMR0_ISR(void)`
> 週期性切換 ADC channel 並啟動單次轉換。

`void USER_ADC_ISR(void)`
> 在 ADC conversion done ISR 中累積並平均 `VR` / `VIN` 的 ADC 結果。

`void VR_TO_STR(uint16_t value, uint8_t *buffer)`
> 將 ADC 整數值轉成固定寬度字串。

`void BATT_TO_STR(uint16_t value, uint8_t *buffer)`
> 將換算後的 `Vin` 數值轉成 `d.dd` 格式字串。
