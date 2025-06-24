/**
 ******************************************************************************
 * @file     LVGL_Arduino.ino
 * @author   Yongqin Ou
 * @version  V1.0
 * @date     2024-10-30
 * @brief    Setup experiment for multiple modules
 * @license  MIT
 * @copyright Copyright (c) 2024, Waveshare
 ******************************************************************************
 * 
 * Experiment Objective: Learn how to set up and use multiple modules including SD card, display, LVGL, wireless, and RGB lamp.
 *
 * Hardware Resources and Pin Assignment: 
 * 1. SD Card Interface --> As configured in SD_Card.h.
 * 2. Display Interface --> As configured in Display_ST7789.h.
 * 3. Wireless Module Interface --> As configured in Wireless.h.
 * 4. RGB Lamp Interface --> As configured in RGB_lamp.h.
 *
 * Experiment Phenomenon:
 * 1. Runs various tests and initializations for different modules.
 * 2. Displays LVGL examples on the display.
 * 3. Continuously runs loops for timer, RGB lamp, and other tasks.
 * 
 * Notes:
 * None
 * 
 ******************************************************************************
 * 
 * Development Platform: ESP32
 * Support Forum: service.waveshare.com
 * Company Website: www.waveshare.com
 *
 ******************************************************************************
 */
#include "Drivers/SD_Card.h"
#include "Drivers/Display_ST7789.h"
#include "Drivers/LVGL_Driver.h"
#include "Drivers/Wireless.h"
#include "Drivers/RGB_lamp.h"
#include "LVGL_Example.h"

#if defined(BOARD_TYPE_WAVESHARE_ESP32_S3_1_47B)
  #include "Drivers/I2C_Driver.h"
  #include "Drivers/Gyro_QMI8658.h"
  #include "Drivers/Button_Driver.h"
  #include "Drivers/BAT_Driver.h"
#endif

void setup()
{
  Flash_test();
#if defined(BOARD_TYPE_WAVESHARE_ESP32_S3_1_47B)
  BAT_Init();
  Button_Init();
  I2C_Init();
  QMI8658_Init(); 
#endif

  SD_Init();         
  LCD_Init();
  Set_Backlight(90);
  RGB_Loop(5);
  Lvgl_Init();
  Lvgl_Example1();     
  // lv_demo_widgets();               
  // lv_demo_benchmark();          
  // lv_demo_keypad_encoder();     
  // lv_demo_music();  
  // lv_demo_stress();        
  Wireless_Test2();  

#if defined(BOARD_TYPE_WAVESHARE_ESP32_S3_1_47B)
  Simulated_Touch_Init();  
#endif
}

void loop()
{
  Timer_Loop();
  delay(5);
}
