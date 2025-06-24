#pragma once
#include "Arduino.h"
#include <cstring>
#if defined(BOARD_TYPE_WAVESHARE_ESP32_C6_1_47)
    #include "SD.h"
#endif
#include "FS.h"
#include "SD_MMC.h"

#if defined(BOARD_TYPE_WAVESHARE_ESP32_S3_1_47) or defined(BOARD_TYPE_WAVESHARE_ESP32_S3_1_47B)
    #define SD_CLK_PIN    14
    #define SD_CMD_PIN    15 
    #define SD_D0_PIN     16
    #define SD_D1_PIN     18
    #define SD_D2_PIN     17 
    #define SD_D3_PIN     21 
#endif


// Digital I/O used
#if defined(BOARD_TYPE_WAVESHARE_ESP32_C6_1_47)
    #define SD_CS     4        //  SD_D3:
#endif
extern uint16_t SDCard_Size;
extern uint16_t Flash_Size;


bool SD_Init();
void Flash_test();

bool File_Search(const char* directory, const char* fileName);
uint16_t Folder_retrieval(const char* directory, const char* fileExtension, char File_Name[][100],uint16_t maxFiles);
void remove_file_extension(char *file_name);