#ifndef __ZLOG__
#define __ZLOG__
#include "ret.h"

#define     COMMON_SIZE_PATH            COMMON_SIZE_256
#define     COMMON_SIZE_128             128
#define     COMMON_SIZE_256             256
#define     COMMON_SIZE_512             512
#define     DIRSPLITER          '/'

enum ELogLevel
{
	EM_LL_DEBUG = 0,
	EM_LL_INFO,
	EM_LL_WARN,
	EM_LL_ERROR,
	EM_LL_NONE
};

ERetCode check_log_dir();

ERetCode LogInit(const char* pFile, char bPrintf, char log_level);

void setLogLevel(char log_level);

void LogInfo(const char* pSrcFile, const char* pFunc, int iLine, const char* fmt, ...);
void LogWarn(const char* pSrcFile, const char* pFunc, int iLine, const char* fmt, ...);
void LogDebug(const char* pSrcFile, const char* pFunc, int iLine, const char* fmt, ...);
void LogError(const char* pSrcFile, const char* pFunc, int iLine, const char* fmt, ...);

void LogUninit();

#define    LOG_INIT                 LogInit
#define    LOG_SET_LEVEL

#define    LOG_INFO(args...)        LogInfo(__FILE__,__FUNCTION__,__LINE__,##args)
#define    LOG_WARN(args...)        LogWarn(__FILE__,__FUNCTION__,__LINE__,##args) 
#define    LOG_ERROR(args...)       LogError(__FILE__,__FUNCTION__,__LINE__,##args) 
#define    LOG_DEBUG(args...)       LogDebug(__FILE__,__FUNCTION__,__LINE__,##args) 

#define    LOG_UNINIT               LogUninit

#endif