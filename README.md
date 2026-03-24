# OLED 128x64 I2C 驅動程式 (for PIC Microcontroller)

這是一個針對 PIC 單晶片設計的 I2C 介面 128x64 OLED (SSD1306) 驅動程式。程式碼基於 MPLAB Code Configurator (MCC) 產生的 I2C 函式庫。

## 功能
- 支援 SSD1306 控制晶片。
- 提供文字（6x8, 8x16）及自訂中文字元（16x16）顯示。
- 提供點陣圖 (Bitmap) 顯示功能。
- 直接寫入模式，不需額外記憶體緩衝區 (RAM buffer)。

## 依賴項目
本驅動程式需要以下由 MCC 產生的模組支援：
1.  **I2C Host (MSSP):** 用於 I2C 通訊。程式中使用 `I2C1_Host`。
2.  **Delay:** 用於初始化的延遲。

並需要包含以下驅動程式自有的檔案：
1.  `OLED128x64.h`
2.  `OLED128x64.c`
3.  `OLED_FONTs.h` (提供字型資料)

## 使用方法

### 1. 初始化
在您的 `main.c` 中，務必先執行系統和OLED的初始化。
```c
#include "mcc_generated_files/system/system.h"
#include "OLED128x64.h"

void main(void)
{
    // 1. 初始化單晶片系統 (由 MCC 產生)
    SYSTEM_Initialize();

    // 2. 初始化 OLED
    OLED_Init();

    // 接下來就可以開始使用OLED了
    // ...
}
```

### 2. 基本範例
以下是一個顯示文字的基本範例：
```c
// ... 在 main 函式中 ...

// 初始化 OLED
OLED_Init();

// 清除螢幕
OLED_CLS();

// 在座標 (24, 2) 的位置顯示 8x16 大小的字串
OLED_Put8x16Str(24, 2, "PIC16F13145");

// 在座標 (0, 4) 的位置顯示 6x8 大小的字串
OLED_Put6x8Str(0, 4, "Hello, World!");

while (1)
{
    // 此驅動為直接寫入模式，主迴圈可以不做任何事
}
```

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
