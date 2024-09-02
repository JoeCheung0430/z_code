#include <iostream>
#include "zlog.h"
#include "ret.h"
#include <cstring>
#include <stdlib.h>
#include "ev_timer.h"

#define MLINK_LOG_PATH	        "G:/mylog/mylog.log"
#define MG_MLINK_LOG_LEVEL EM_LL_WARN
#define cmd_start_live "*MG2011BAF"
#define CMD_START_4G_REMOTE_CONTROL			"*MG2011RA"  //远程调阅直播
#define TOKEN_SIZE 20

int is_begin_with(const char * str1, const char *str2)
{
	if (memcmp(str1, str2, strlen(str2)) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void get_cmd_token(char* cmd, char *tokens[], int *token_count) {
    char *token = strtok(cmd, ",");
    while (token != NULL && *token_count < TOKEN_SIZE) {
        tokens[(*token_count)++] = token;
        token = strtok(NULL, ",");
    }
}

void createStopCommand(char* startCommand, char* stopCommand, size_t size)
{
    if(startCommand==NULL){
        LOG_INFO("Input command is NULL");
        stopCommand[0] = '\0';
        return;
    }

    char *tokens[TOKEN_SIZE] = {0};
    int token_count = 0;
    get_cmd_token(startCommand, tokens, &token_count);
    int Operate = 0;
    
    //构建直播的停止指令 0 1 2 3 4 #
    if(is_begin_with(startCommand,cmd_start_live)){
        LOG_INFO("Start creating live stop command");
        snprintf(stopCommand,size,"%s,%s,%s,%d,%d#",tokens[0],tokens[1],tokens[2],Operate,atoi(tokens[4]));
        LOG_INFO("Live top command created: %s", stopCommand);
    }
    // 构建调阅的停止指令 0 1 7 3 4 7 #
    else if(is_begin_with(startCommand,CMD_START_4G_REMOTE_CONTROL)){
        LOG_INFO("Start creating remote control stop command");
        snprintf(stopCommand,size,"%s,%s,%s,%d,%d,%s#",tokens[0],tokens[1],tokens[7],Operate,atoi(tokens[4]),tokens[7]);
        LOG_INFO("Remote control command created: %s", stopCommand);
    }

    else{
        LOG_INFO("Command does not match start command format.");
        stopCommand[0] = '\0';  // 返回空字符串表示未生成stopCommand
    }
}

int main()
{
    ERetCode er = LOG_INIT(MLINK_LOG_PATH, 1, EM_LL_INFO);
    if (er != EM_RC_OK)
    {
        printf("create log file fail:%d", er);
        //return er;
    }
    char startCommand1[] = "*MG2011RA,869218069642112,824706142948450304,1,1,2024-07-30 17:10:53:000,2024-07-30 17:11:53:999,892821359187472385,rtmp://live-k8s.4s12580.com:1946/playback/869218069642112-1?app=playback#";
    char startCommand2[] = "*MG2011BAF,869218069642112,892738516394455041,1,1,rtmp://live-k8s.4s12580.com:1936/live/869218069642112-1?streamId=892738516394455040,512,480#";
    char stopCommand1[256];
    char stopCommand2[256];
    createStopCommand(startCommand1, stopCommand1,sizeof(stopCommand1));
    LOG_INFO("Final stopCommand: %s", stopCommand1);
    createStopCommand(startCommand2, stopCommand2,sizeof(stopCommand2));
    LOG_INFO("Final stopCommand: %s", stopCommand2);
    
    LOG_UNINIT();
    return 0;
}