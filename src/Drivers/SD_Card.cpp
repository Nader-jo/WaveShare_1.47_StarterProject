#include "SD_Card.h"

bool SDCard_Flag;
bool SDCard_Finish;

uint16_t SDCard_Size;
uint16_t Flash_Size;

bool SD_Init() {
  #if defined(BOARD_TYPE_WAVESHARE_ESP32_S3_1_47) or defined(BOARD_TYPE_WAVESHARE_ESP32_S3_1_47B)
  // SD MMC
  if(!SD_MMC.setPins(SD_CLK_PIN, SD_CMD_PIN, SD_D0_PIN, SD_D1_PIN, SD_D2_PIN, SD_D3_PIN)){
    printf("SD MMC: Pin change failed!\r\n");
    return false;
  }
  if (SD_MMC.begin("/sdcard", true, true)) {                              
#endif
#if defined(BOARD_TYPE_WAVESHARE_ESP32_C6_1_47)
  // SD
  pinMode(SD_CS, OUTPUT);    
  digitalWrite(SD_CS, HIGH);               
  if (SD.begin(SD_CS, SPI)) {
#endif
    printf("SD card initialization successful!\r\n");
  } else {
    printf("SD card initialization failed!\r\n");
  }
  #if defined(BOARD_TYPE_WAVESHARE_ESP32_C6_1_47)
    uint8_t cardType = SD.cardType();
  #endif
  #if defined(BOARD_TYPE_WAVESHARE_ESP32_S3_1_47) or defined(BOARD_TYPE_WAVESHARE_ESP32_S3_1_47B)
    uint8_t cardType = SD_MMC.cardType();
  #endif
  if(cardType == CARD_NONE){
    printf("No SD card attached\r\n");
    return false;
  }
  else{
    printf("SD Card Type: ");
    if(cardType == CARD_MMC){
      printf("MMC\r\n");
    } else if(cardType == CARD_SD){
      printf("SDSC\r\n");
    } else if(cardType == CARD_SDHC){
      printf("SDHC\r\n");
    } else {
      printf("UNKNOWN\r\n");
    }
    #if defined(BOARD_TYPE_WAVESHARE_ESP32_C6_1_47)
    uint64_t totalBytes = SD.totalBytes();
    uint64_t usedBytes = SD.usedBytes();
    #endif
    #if defined(BOARD_TYPE_WAVESHARE_ESP32_S3_1_47) or defined(BOARD_TYPE_WAVESHARE_ESP32_S3_1_47B)
    uint64_t totalBytes = SD_MMC.totalBytes();
    uint64_t usedBytes = SD_MMC.usedBytes();
    #endif
    SDCard_Size = totalBytes/(1024*1024);
    printf("Total space: %llu\n", totalBytes);
    printf("Used space: %llu\n", usedBytes);
    printf("Free space: %llu\n", totalBytes - usedBytes);
  }
  return true;
}
bool File_Search(const char* directory, const char* fileName)    
{
#if defined(BOARD_TYPE_WAVESHARE_ESP32_C6_1_47)
  File Path = SD.open(directory);
#endif
#if defined(BOARD_TYPE_WAVESHARE_ESP32_S3_1_47) or defined(BOARD_TYPE_WAVESHARE_ESP32_S3_1_47B)
  File Path = SD_MMC.open(directory); 
#endif
  if (!Path) {
    printf("Path: <%s> does not exist\r\n",directory);
    return false;
  }
  File file = Path.openNextFile();
  while (file) {
    if (strcmp(file.name(), fileName) == 0) {                           
      if (strcmp(directory, "/") == 0)
        printf("File '%s%s' found in root directory.\r\n",directory,fileName);  
      else
        printf("File '%s/%s' found in root directory.\r\n",directory,fileName); 
      Path.close();                                                     
      return true;                                                     
    }
    file = Path.openNextFile();                                        
  }
  if (strcmp(directory, "/") == 0)
    printf("File '%s%s' not found in root directory.\r\n",directory,fileName);           
  else
    printf("File '%s/%s' not found in root directory.\r\n",directory,fileName);          
  Path.close();                                                         
  return false;                                                         
}
uint16_t Folder_retrieval(const char* directory, const char* fileExtension, char File_Name[][100],uint16_t maxFiles)    
{
  #if defined(BOARD_TYPE_WAVESHARE_ESP32_C6_1_47)
  File Path = SD.open(directory);
  #endif
  #if defined(BOARD_TYPE_WAVESHARE_ESP32_S3_1_47) or defined(BOARD_TYPE_WAVESHARE_ESP32_S3_1_47B)
  File Path = SD_MMC.open(directory);
  #endif
  if (!Path) {
    printf("Path: <%s> does not exist\r\n",directory);
    return false;
  }
  
  uint16_t fileCount = 0;
  char filePath[100];
  File file = Path.openNextFile();
  while (file && fileCount < maxFiles) {
    if (!file.isDirectory() && strstr(file.name(), fileExtension)) {
      strncpy(File_Name[fileCount], file.name(), sizeof(File_Name[fileCount])); 
      if (strcmp(directory, "/") == 0) {                                      
        snprintf(filePath, 100, "%s%s", directory, file.name());   
      } else {                                                            
        snprintf(filePath, 100, "%s/%s", directory, file.name());
      }
      printf("File found: %s\r\n", filePath);
      fileCount++;
    }
    file = Path.openNextFile();                                      
  }
  Path.close();                                                         
  if (fileCount > 0) {
    printf(" %d <%s> files were retrieved\r\n",fileCount,fileExtension);
    return fileCount;                                                 
  } else {
    printf("No files with extension '%s' found in directory: %s\r\n", fileExtension, directory);
    return 0;                                                         
  }
}

void remove_file_extension(char *file_name) {
  char *last_dot = strrchr(file_name, '.');
  if (last_dot != NULL) {
    *last_dot = '\0'; 
  }
}

void Flash_test()
{
  printf("/********** RAM Test**********/\r\n");
  // Get Flash size
  uint32_t flashSize = ESP.getFlashChipSize();
  Flash_Size = flashSize/1024/1024;
  printf("Flash size: %d MB \r\n", flashSize/1024/1024);

  printf("/******* RAM Test Over********/\r\n\r\n");
}