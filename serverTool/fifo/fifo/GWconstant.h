#ifndef FILEINFO_H
#define FILEINFO_H
#include <stdint.h>

#define PAGESIZE   4096 //4k
#define TRILLION   1048576 //1MB
const  uint32_t INIT_FILE_SIZE = 104857600;  //100MB
const  int MAX_TAG_NUM = 255;

const  char* const  GW_FILE_EXPAND_NAME = ".bat";
const  char* const   GW_FIFO_INFO_FILE = "gwfifoinfo.bat";
const  char* const  GW_TAG_INFO_FILE = "gwtagfileinfo.bat";

const time_t  COMMIT_PERIOD_TIME = 120;

#endif //FILEINFO_H
