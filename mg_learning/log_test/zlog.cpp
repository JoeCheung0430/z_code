#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdarg.h>
#include <ctime>
#include <chrono>
#include <sstream>
#include <cstring>
#include <iomanip> 

#include "zlog.h"
#include "myfile.h"

#ifdef UNICODE
    #define LOG_OUTPUT_STRING			    L"%s-%-5s - [%-24s]: %s - [%s(%d)]\n"
#else
    #define LOG_OUTPUT_STRING			    "%s-%-5s - [%-24s]: %s - [%s(%d)]\n"
    #define LOG_OUTPUT_STRING_W			  "\033[40;33m%s-%-5s - [%-24s]: %s - [%s(%d)]\033[0m\n"
    #define LOG_OUTPUT_STRING_E			  "\033[40;31m%s-%-5s - [%-24s]: %s - [%s(%d)]\033[0m\n"
#endif

#ifdef DEBUG
#define	LOG_FILE_MAXSIZE			(20*1024*1024)
#else
#define	LOG_FILE_MAXSIZE			(5*1024*1024)
#endif

#define	LOG_MAX_SIZE 				10240
#define LOG_MAX_TIME_SIZE			24

struct TLogString
{
    char acLog;
    char acString;
};

const char* g_aLogLevel[] = 
{
	"DEBUG","INFO","WARN","ERROR","NONE"
};

#define FILE_ERROR -1

typedef struct __mg_log__
{               
	int     bPrintf_;                       
	char    chLogFile_[COMMON_SIZE_256];	 
	char*   pComment_;
	int     logLevel;
    int     fLog_ = FILE_ERROR;

	pthread_mutex_t mutex_;
}mg_log;

mg_log g_mg_log;
char g_log_content[LOG_MAX_SIZE + COMMON_SIZE_512];

void GetFmtTimeString(char* chTimeString);
void WriteLog(int iLogLevel, const char* pSrcFile, const char* pFunc, int nLine);

ERetCode LogInit(const char* pFile, char bPrintf, char log_level)
{
    if(pFile == NULL)
        return EM_RC_PARAM_ERR;
	check_log_dir();
    if(g_mg_log.fLog_ != FILE_ERROR)
        return EM_RC_FILE_EXIST_ERR;

	if ( g_mg_log.pComment_  == NULL)
		g_mg_log.pComment_ = (char *)malloc(LOG_MAX_SIZE * sizeof(char));

	pthread_mutex_init(&g_mg_log.mutex_, NULL);

	memset(g_mg_log.chLogFile_, 0, COMMON_SIZE_PATH);
    strcpy(g_mg_log.chLogFile_,pFile);
    g_mg_log.fLog_ = open(g_mg_log.chLogFile_, O_CREAT | O_RDWR | O_APPEND, 0666);
    if(g_mg_log.fLog_ == FILE_ERROR)
        return EM_RC_FILE_OPEN_ERR;

	g_mg_log.logLevel = log_level;
    g_mg_log.bPrintf_ = bPrintf;
    return EM_RC_OK;
}

ERetCode check_log_dir()
{
	int ir = 0;
	if (!is_file_exist(LOG_DIR_PATH))
	{
		ir = create_folder_r(LOG_DIR_PATH);
		if (ir < 0)
		{
			LOG_ERROR("not create dir:%s", LOG_DIR_PATH);
			return EM_RC_DIR_ERR;
		}
		else
		{
			printf("not create dir:%s\n", LOG_DIR_PATH);
		}
	}
	return EM_RC_OK;
}

void setLogLevel(char log_level)
{
	g_mg_log.logLevel = log_level;
}

void LogDebug(const char* pSrcFile, const char* pFunc, int nLine, const char* fmt, ...)
{
	if (g_mg_log.fLog_ == FILE_ERROR)
	{
		g_mg_log.fLog_ = open(g_mg_log.chLogFile_, O_CREAT | O_RDWR | O_APPEND, 0666);
		if(g_mg_log.fLog_ == FILE_ERROR)
    	return; 
	}

	if (g_mg_log.logLevel <= EM_LL_DEBUG)
	{
		va_list vl;
		pthread_mutex_lock(&g_mg_log.mutex_);

		memset(g_mg_log.pComment_, 0, LOG_MAX_SIZE);
		va_start(vl, fmt);
		vsnprintf(g_mg_log.pComment_,(LOG_MAX_SIZE-1), fmt, vl);
		va_end(vl);

		WriteLog(EM_LL_DEBUG, pSrcFile, pFunc, nLine);
		pthread_mutex_unlock(&g_mg_log.mutex_);
	}
}

void LogInfo(const char* pSrcFile,const char* pFunc,int nLine,const char* fmt,...)
{
    if(g_mg_log.fLog_ == FILE_ERROR)
	{
		g_mg_log.fLog_ = open(g_mg_log.chLogFile_, O_CREAT | O_RDWR | O_APPEND, 0666);
		if(g_mg_log.fLog_ == FILE_ERROR)
    	return; 
	}

	if ( g_mg_log.logLevel <= EM_LL_INFO)
	{
		va_list vl;

		pthread_mutex_lock(&g_mg_log.mutex_);

		memset(g_mg_log.pComment_, 0, LOG_MAX_SIZE);
		va_start(vl, fmt);
		vsnprintf(g_mg_log.pComment_,(LOG_MAX_SIZE-1), fmt, vl);
		va_end(vl);

		WriteLog(EM_LL_INFO, pSrcFile, pFunc, nLine);

		pthread_mutex_unlock(&g_mg_log.mutex_);
	}
}

void LogWarn(const char* pSrcFile,const char* pFunc,int nLine,const char* fmt,...)
{
    if(g_mg_log.fLog_ == FILE_ERROR)
	{
		g_mg_log.fLog_ = open(g_mg_log.chLogFile_, O_CREAT | O_RDWR | O_APPEND, 0666);
		if(g_mg_log.fLog_ == FILE_ERROR)
    	return; 
	}

	if (g_mg_log.logLevel <= EM_LL_WARN)
	{
		va_list vl;

		pthread_mutex_lock(&g_mg_log.mutex_);

		memset(g_mg_log.pComment_, 0, LOG_MAX_SIZE);
		va_start(vl, fmt);
		vsnprintf(g_mg_log.pComment_,(LOG_MAX_SIZE-1), fmt, vl);
		va_end(vl);

		WriteLog(EM_LL_WARN, pSrcFile, pFunc, nLine);
		pthread_mutex_unlock(&g_mg_log.mutex_);
	}
}

void LogError(const char* pSrcFile,const char* pFunc,int nLine,const char* fmt,...)
{
    if(g_mg_log.fLog_ == FILE_ERROR)
	{
		g_mg_log.fLog_ = open(g_mg_log.chLogFile_, O_CREAT | O_RDWR | O_APPEND, 0666);
		if(g_mg_log.fLog_ == FILE_ERROR)
    	return; 
	}

	if (g_mg_log.logLevel <= EM_LL_ERROR)
	{
		va_list vl;
		pthread_mutex_lock(&g_mg_log.mutex_);

		memset(g_mg_log.pComment_, 0, LOG_MAX_SIZE);
		va_start(vl, fmt);
		vsnprintf(g_mg_log.pComment_,(LOG_MAX_SIZE-1), fmt, vl);
		va_end(vl);

		WriteLog(EM_LL_ERROR, pSrcFile, pFunc, nLine);
		pthread_mutex_unlock(&g_mg_log.mutex_);
	}
}

void CheckLine()
{
	static int st_logsize_check = 1000;

	if(st_logsize_check < 500) st_logsize_check ++;

	if(st_logsize_check >= 500)
	{
		st_logsize_check = 0;
		int file_length = get_file_size(g_mg_log.chLogFile_);
		if(file_length >= LOG_FILE_MAXSIZE)
		{
			char chTemp[COMMON_SIZE_PATH] = {0};
			strcpy(chTemp, g_mg_log.chLogFile_);
			strcat(chTemp, ".old");
			close(g_mg_log.fLog_);
			g_mg_log.fLog_ = -1;

			remove(chTemp);

			rename(g_mg_log.chLogFile_, chTemp);

			g_mg_log.fLog_ = open(g_mg_log.chLogFile_, O_CREAT | O_RDWR | O_APPEND, 0666);
		}
	}
}

void WriteLog(int iLogLevel,const char* pSrcFile,const char* pFunc,int nLine)
{	
    CheckLine();
    if(g_mg_log.fLog_ == FILE_ERROR)
	{
		return ;	
	}        
	
    char aNowTime[COMMON_SIZE_128] = {0};
    char acSrcFile[COMMON_SIZE_PATH] = {0};
    strcpy(acSrcFile,pSrcFile);
    char* pSrcName = strrchr(acSrcFile,DIRSPLITER);
    if(pSrcName == NULL)
        pSrcName = acSrcFile;
    else
        pSrcName++;

    GetFmtTimeString(aNowTime);

    if(g_mg_log.bPrintf_)
    {
        printf(LOG_OUTPUT_STRING,aNowTime,g_aLogLevel[iLogLevel],pFunc,g_mg_log.pComment_,pSrcName,nLine);
    }
	
	
	snprintf(g_log_content,sizeof(g_log_content),LOG_OUTPUT_STRING, aNowTime, g_aLogLevel[iLogLevel], pFunc, g_mg_log.pComment_, pSrcName, nLine);
    if (!is_file_exist(g_mg_log.chLogFile_))
	{
		g_mg_log.fLog_ = open(g_mg_log.chLogFile_, O_CREAT | O_RDWR | O_APPEND, 0666);
	}
	write(g_mg_log.fLog_, g_log_content, strlen(g_log_content));
	/*if (g_mg_log.iLogLine_ % 30 == 0)
	{
		sync();
	}*/
}

void GetFmtTimeString(char* chTimeString)
{
    // 使用 chrono 获取当前时间
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    // 转换为 tm 结构
    std::tm *pTime = std::localtime(&now_time_t);

    // 格式化时间字符串
    std::ostringstream oss;
    oss << "[" 
        << std::put_time(pTime, "%Y-%m-%d %H:%M:%S") 
        << ":" << std::setfill('0') << std::setw(3) << now_ms.count()
        << "]";

    // 复制到 chTimeString
    std::string timeString = oss.str();
    std::strcpy(chTimeString, timeString.c_str());
}

void LogUninit()
{
	pthread_mutex_lock(&g_mg_log.mutex_);
	SAFE_CLOSE(g_mg_log.fLog_);
	pthread_mutex_unlock(&g_mg_log.mutex_);

	pthread_mutex_destroy(&g_mg_log.mutex_);

	SAFE_FREE(g_mg_log.pComment_);
}


