#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <list>
#include <thread>
#include <chrono>
#include <mutex>
#include "string.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cstring>

/*原文件中存在，仅做测试*/
#define CMD_UNIT_SIZE   20480
#define CMD_BUFFER_SIZE 51200
#define cmd_start_live "*MG2011BAF"
#define CMD_NEW_4G_REMOTE_UPLOAD_TREE        "*MG2011BN"    //新目录树同步
#define CMD_START_4G_REMOTE_CONTROL			"*MG2011RA"  //远程调阅直播
#define cmd_start_capture_video_new "*MG2011BADEX"
#define cmd_start_capture_pic_new "*MG2011BACEX"
#define cmd_start_str_new  "*MG2011BMD"
#define CMD_RECORDER_VIDEO_UPLOAD			"*MG2011TASK"//远程设备录像视频提取
#define CMD_MAPGOO_HEAD "*MG"
#define CMD_MAPGOO_END  35 //#
#define TOKEN_SIZE                     20
#define CMD_MAPGOO_HEAD_1 "%["
#define CMD_MAPGOO_END_1  ']' //
#define cmd_start_busi_media_pick           "*MG2011VMD"

typedef struct _cmd_buffer_
{
	char cmd_buffer[CMD_BUFFER_SIZE];
	int  cmd_buffer_size;
}cmd_buffer_s;

cmd_buffer_s g_cmd_buffer = { 0,0 };

bool g_SimulationStop_flag = 0;

int parse_cmd_data(char* cmd, int cmd_size, char* result, int* result_size)
{
	if (memcmp(cmd, CMD_MAPGOO_HEAD, strlen(CMD_MAPGOO_HEAD)) == 0)
	{
		int start_index = 0;
		char* cmd_end = (char *)memchr(cmd + strlen(CMD_MAPGOO_HEAD), CMD_MAPGOO_END,
			cmd_size - strlen(CMD_MAPGOO_HEAD));
		if (cmd_end == NULL)
		{
			//LOG_ERROR("not find end char");
			//return CMD_NOT_FIND_END;
		}
		int end_index = (cmd_end - cmd) + 1;
		*result_size = end_index - start_index;
		memcpy(result, cmd, *result_size);
		//return CMD_OK;
	}
	else if (memcmp(cmd, CMD_MAPGOO_HEAD_1, strlen(CMD_MAPGOO_HEAD_1)) == 0)
	{
		int start_index = 0;
		char* cmd_end = (char *)memchr(cmd + strlen(CMD_MAPGOO_HEAD_1), CMD_MAPGOO_END_1,
			cmd_size - strlen(CMD_MAPGOO_HEAD_1));
		if (cmd_end == NULL)
		{
			//LOG_ERROR("not find end char");
			//return CMD_NOT_FIND_END;
		}
		int end_index = (cmd_end - cmd) + 1;
		*result_size = end_index - start_index;
		memcpy(result, cmd, *result_size);
		//return CMD_OK;
	}
	else
	{
		//LOG_ERROR("error protocol head : %s", cmd);
		//return CMD_ERROR;
	}
}
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
enum CMD_ERROR_CODE
{
	CMD_OK = 0,
	CMD_NOT_FIND_END,
	CMD_ERROR,
	CMD_INGNORE
};
#define LIVE_ID                        1
#define REMOTE_UPLOAD_TREE_ID          2
#define REMOTE_CONTROL_ID              3
#define CAPTURE_VIDEO_ID               4
#define CAPTURE_PIC_ID                 5
#define PICK_ID                        6
#define VEDIO_UPLOAD_ID                7
#define COMMON_SIZE_32K             32768
#define RECV_BUFFER_SIZE COMMON_SIZE_32K
/*---------------------------------------------------*/

std::string get_current_time();
void checkAndRemoveExpiredTasks();

struct BuffAndLength {
    char* buff1;
    int length1;
    char *buff2;
    int length2;
};

class CmdEntiry {
public:
    // 构造函数
    CmdEntiry(int id, const int operate, int priority, const std::string& describe, int channel, bool isResumable, const std::string& file, const std::string& time, char* buff, int length, const std::string& play_id)
        : id(id), operate(operate), priority(priority), describe(describe), channel(channel), isResumable(isResumable), file(file), time(time), length(length), play_id(play_id) {
        startTime = std::chrono::system_clock::now();
        this->buff = new char[strlen(buff) + 1];  // 为 buff 分配内存
        strcpy(this->buff, buff);  // 复制 buff 内容
    }

    // equal函数，判断id,channel,file是否相等
    bool equal(const CmdEntiry& cmd)  {
        return this->id == cmd.id && this->channel == cmd.channel && this->file == cmd.file;
    }

    // group函数，判断id相同但operate不同
    bool group(const CmdEntiry& cmd)  {
        return this->id == cmd.id && this->operate != cmd.operate;
    }

    bool isExpired(){
        auto now = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - startTime);
        if(id==4||id==5||id==7){
            return duration.count() >= 5;
        }
        else{
            return duration.count() >= 6;
        }
    }

    void updateStartTime() {
        startTime = std::chrono::system_clock::now();
        this->time = get_current_time();
    }

    int getPriority() const{
        return priority;
    }

    int getOperate() const{
        return operate;
    }

    int getID() const{
        return id;
    }

    char* getBuff(){
        return buff;
    }
    std::string getTime() const {
        return time;
    }

    void setTime(CmdEntiry cmd){
        this->time = cmd.time;
    }

    void setID(int ID){
        this->id = ID;
    }
    void setOperate(int newOperate){
        this->operate = newOperate;
    }


    bool getIsResumable() const {
        return isResumable;
    }

    int getChannel() const{
        return channel;
    }

    std::string getFile() const {
        return file;
    }

      std::string getDescription() const {
        return describe;
    }

    int getLength(){
        return length;
    }

    std::string getPlay_id() const {
        return play_id;
    }
        // 打印 CmdEntiry 对象信息
    void print() const {
        std::cout << "CmdEntiry(" 
                  << "id: " << id << ", "
                  << "operate: " << operate << ", "
                  << "priority: " << priority << ", "
                  << "describe: " << describe << ", "
                  << "channel: " << channel << ", "
                  << "isResumable: " << (isResumable ? "true" : "false") << ", "
                  << "file: " << file << ", "
                  << "time: " << time << ", "
                  << "buff: " << buff << ", "
                  << "length:" 
                  << ")\n";
    }
private:
    int id;                      // id
    int operate;                 // operate: start, stop, switch
    int priority;                // priority: 0-7
    std::string describe;        // describe
    int channel;                 // channel
    bool isResumable;            // 是否可恢复
    std::string file;            // 文件路径
    std::string time;            // 时间
    std::chrono::system_clock::time_point startTime;
    char* buff;
    int length;                  // buff长度
    std::string play_id;         // 远程调阅
};

#if 0
bool CompareCmd(const CmdEntiry &cmd1, const CmdEntiry &cmd2){
    return cmd1.getID() == cmd2.getID() && cmd1.getChannel() == cmd2.getChannel();
}
#endif

bool CompareCmd(const CmdEntiry &cmd1, const CmdEntiry &cmd2){
    return cmd1.getID() == cmd2.getID() && cmd1.getChannel() == cmd2.getChannel() && cmd1.getPlay_id()==cmd2.getPlay_id();
}

std::list<CmdEntiry> runninglist;
std::list<CmdEntiry> waitinglist;
std::mutex listMutex; // 互斥锁保护

#if 1
bool isNeedManage(char* cmd)
{
    //获取到cmd数组，开始判断
    if(is_begin_with(cmd,cmd_start_live))
    {
        std::cout << "live start" << std::endl;
        return true;
    }
    else if(is_begin_with(cmd,CMD_NEW_4G_REMOTE_UPLOAD_TREE))
    {
 
        return true;
    }
    else if(is_begin_with(cmd,CMD_RECORDER_VIDEO_UPLOAD))
    {

        return true;
    }
    else if(is_begin_with(cmd,cmd_start_busi_media_pick))
    {

        return true;
    }
}
#endif

// 获取当前时间字符串
std::string get_current_time(){
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_c);

    // 格式化时间为字符串
    std::ostringstream oss;
    oss << std::put_time(now_tm, "%H:%M:%S");
    return oss.str();
}

void remoteHash(std::string& play_id){
    int index = 0;
    for(char c : play_id){
        if(c!='#'){
            play_id[index++] = c;
        }
    }
    play_id.resize(index);
}

void SimulationStopCommand(CmdEntiry& cmd)
{
    if(cmd.getID()==1){
        // 停止直播指令
        std::cout << "---------------stop live---------------\n" << std::endl;
        /*
        int camera_id = cmd.getChannel();
        stop_mg_live(camera_id);
        */
    }
    else if(cmd.getID()==3){
        // 停止远程调阅
        std::cout << "---------------stop remote---------------\n" << std::endl;
        int camera_id = cmd.getChannel();
        std::string playid = cmd.getPlay_id();
        remoteHash(playid);
        /*
        stop_mg_history_playback();
        */
    }
}

void handleStartCommand(CmdEntiry& cmd)
{
    std::cout << "enter handlestartcommand\n"<< std::endl;
    if(runninglist.empty() && waitinglist.empty()){
        // 如果运行队列和等待队列都为空，直接添加到运行队列
        cmd.updateStartTime();
        runninglist.push_back(cmd);
    }
    else if(!runninglist.empty()){
        // 运行队列不为空，获取当前正在运行的命令
        CmdEntiry& currentcmd = const_cast<CmdEntiry&>(runninglist.front());
        if(currentcmd.getID()==cmd.getID()){
            //ID相同
            // 遍历运行队列
            std::list<CmdEntiry>::iterator it = find_if(runninglist.begin(), runninglist.end(), [&](const CmdEntiry cmd_t){ 
                    return CompareCmd(cmd_t, cmd); });
            if(it == runninglist.end()){
                // 运行队列里面没有相同指令
                cmd.updateStartTime();
                runninglist.push_back(cmd);
            }
            else{
                it->setTime(cmd);
            }
        }
        else{
            //ID不同
            if(cmd.getPriority() >= currentcmd.getPriority()){
                //新来的优先级低
                if(cmd.getIsResumable()){
                    //可恢复
                    if(!waitinglist.empty()){
                        //等待队列不为空
                        std::list<CmdEntiry>::iterator it = find_if(waitinglist.begin(), waitinglist.end(), [&](const CmdEntiry cmd_t){
                            return CompareCmd(cmd_t, cmd); });
                        if(it == waitinglist.end()){
                            //没找到，加入等待队列
                            waitinglist.push_back(cmd);
                            // waitinglist按照优先级排序
                            waitinglist.sort([](const CmdEntiry& a, const CmdEntiry& b) {
                                return a.getPriority() < b.getPriority();
                            });
                        }
                        else{
                            //找到了,更新时间
                            it->setTime(cmd);
                        }
                    }
                    else{
                        //等待队列为空
                        waitinglist.push_back(cmd);
                    }
                }
                else{
                    return;
                }
            }
            else{
                //新来的优先级高
                if(currentcmd.getIsResumable()){
                    // 可恢复
                    // 模拟分发指令A对应结束指令
                    int runningsize = runninglist.size();
                    for (int i = 1; i <= runningsize;i++){
                        // 逐个添加到waitinglist中
                        CmdEntiry temp = runninglist.front();
                        std::list<CmdEntiry>::iterator it = find_if(waitinglist.begin(), waitinglist.end(), [&](const CmdEntiry cmd_t){
                            return CompareCmd(cmd_t, temp); });
                        if(it == waitinglist.end()){
                            // 没找到，加入等待队列
                            waitinglist.push_back(temp);
                            // 按优先级排序
                            waitinglist.sort([](const CmdEntiry& a, const CmdEntiry& b) {
                                return a.getPriority() < b.getPriority();
                            });
                        }
                        else{
                            it->setTime(temp);
                        }
                        SimulationStopCommand(temp);
                        runninglist.pop_front();
                    }
                    cmd.updateStartTime();
                    runninglist.push_back(cmd);
                }
                else{
                    // 不可恢复
                    // 模拟分发指令A对应结束指令
                    int runningsize = runninglist.size();
                    for (int i = 1; i <= runningsize;i++){
                        CmdEntiry del_cmd = runninglist.front();
                        SimulationStopCommand(del_cmd);
                        runninglist.pop_front();
                    }
                    //增加新指令
                    cmd.updateStartTime();
                    runninglist.push_back(cmd);
                }
            }
        }
    }
}


BuffAndLength handleStopCommand(CmdEntiry& cmd, char* data, int data_size)
{
    BuffAndLength result;
    if(!runninglist.empty()){
        std::list<CmdEntiry>::iterator it = find_if(runninglist.begin(), runninglist.end(), [&](const CmdEntiry cmd_t){
            return CompareCmd(cmd_t, cmd); });
        if(!(it==runninglist.end())){
            //运行队列有对应的运行任务
            runninglist.erase(it);
        }
    }
    result.buff1 = cmd.getBuff();
    result.length1 = cmd.getLength();
    return result;
}

std::chrono::system_clock::time_point getTimePointFromString(const std::string& timeStr) {
    return std::chrono::system_clock::from_time_t(std::stoll(timeStr));
}


void checkRunningTasks(){
    while(true){
        std::this_thread::sleep_for(std::chrono::minutes(1)); // 每隔1分钟检测一次
        std::lock_guard<std::mutex> lock(listMutex); // 确保操作线程安全
        auto now = std::chrono::system_clock::now();
        for (auto it = runninglist.begin(); it != runninglist.end(); /* no increment here */) {
            if (!it->getIsResumable()) {
                auto startTime = getTimePointFromString(it->getTime()); // 获取任务开始时间
                auto elapsedMinutes = std::chrono::duration_cast<std::chrono::minutes>(now - startTime).count();
                // 检查特定ID任务的时间限制
                if ((it->getID() == 1 && elapsedMinutes > 5) || (it->getID() == 2 && elapsedMinutes > 3)) {
                    // 模拟发送停止命令
                    it = runninglist.erase(it); // 从运行队列中删除任务
                } else {
                    ++it; // 继续下一个任务
                }
            } else {
                ++it; // 继续下一个任务
            }
        }
    }
}

void printQueueStatus() {
    std::cout << "\nRunning List:" << std::endl;
    for (auto& cmd : runninglist) {
        std::cout << "  ID=" << cmd.getID() << ", Operate=" << cmd.getOperate() << ", Priority=" << cmd.getPriority() 
                  << ", Channel=" << cmd.getChannel() << ", Description=" << cmd.getDescription() << ", time=" << cmd.getTime() << ", buff=" << cmd.getBuff() << ", length="<<cmd.getLength()<< ", play_id="<<cmd.getPlay_id()<< std::endl;
    }

    std::cout << "\nWaiting List:" << std::endl;
    for (const auto& cmd : waitinglist) {
        std::cout << "  ID=" << cmd.getID() << ", Operate=" << cmd.getOperate() << ", Priority=" << cmd.getPriority() 
                  << ", Channel=" << cmd.getChannel() << ", Description=" << cmd.getDescription() << std::endl;
    }
}



void get_cmd_token(char* cmd, char *tokens[], int *token_count) {
    char *token = strtok(cmd, ",");
    while (token != NULL && *token_count < TOKEN_SIZE) {
        tokens[(*token_count)++] = token;
        token = strtok(NULL, ",");
    }
}



#if 1
CmdEntiry buildCmdEntiry(char* cmd,char* buff,int length)
{
    //获取时间
    std::string current_time = get_current_time();
    if(is_begin_with(cmd,cmd_start_live)){
        //直播
        char *tokens[TOKEN_SIZE] = {0};
        int token_count = 0;
        get_cmd_token(cmd, tokens, &token_count);
        if(token_count == 8){
            //开始直播
            int camera_id = atoi(tokens[4]);
            std::string file = tokens[5];
            CmdEntiry start_live_object(LIVE_ID, 1, 1, "start live cmd", camera_id, false, file, current_time,buff,length,"");
            return start_live_object;
        }
        else if (token_count == 5) {
            // 结束直播
            int camera_id = atoi(tokens[4]);
            CmdEntiry stop_live_object(LIVE_ID, 2, 1, "stop live cmd", camera_id, false, "", current_time,buff,length,"");
            return stop_live_object;
        }
    }
    else if(is_begin_with(cmd,CMD_NEW_4G_REMOTE_UPLOAD_TREE)){
        //新目录树同步
        char *tokens[TOKEN_SIZE] = {0};
        int token_count = 0;
        get_cmd_token(cmd, tokens, &token_count);
        int camera_id = atoi(tokens[4]);
        CmdEntiry tree_object(REMOTE_UPLOAD_TREE_ID, 1, 1, "dir tree remote cmd", camera_id, true,"",current_time,buff,length,"");
        return tree_object;
    }
    else if(is_begin_with(cmd,CMD_START_4G_REMOTE_CONTROL)){
        //远程调阅
        char *tokens[TOKEN_SIZE] = {0};
        int token_count = 0;
        get_cmd_token(cmd, tokens, &token_count);
        if(token_count == 8 || token_count == 9){
            //开始远程回放
            int camera_id = atoi(tokens[4]);
            std::string play_id = tokens[7];
            CmdEntiry start_remote_object(REMOTE_CONTROL_ID, 1, 1, "start mg history playback", camera_id, false,"",current_time,buff,length,play_id);
            return start_remote_object;
        }
        if(token_count==6){
            //停止远程回放
            int camera_id = atoi(tokens[4]);
            std::string play_id = tokens[5];
            remoteHash(play_id);
            CmdEntiry stop_remove_object(REMOTE_CONTROL_ID, 2, 1, "end mg 4G remote", camera_id, false,"",current_time,buff,length,play_id);
            return stop_remove_object;
        }
    }
    else if(is_begin_with(cmd,cmd_start_capture_video_new)){
        //视频抓拍
        char *tokens[TOKEN_SIZE] = {0};
        int token_count = 0;
        get_cmd_token(cmd, tokens, &token_count);
        int camera_id = atoi(tokens[4]);
        CmdEntiry cap_vedio_object(CAPTURE_VIDEO_ID, 1, 2, "get a capture video", camera_id, false,"",current_time,buff,length,"");
        return cap_vedio_object;
    }
    else if(is_begin_with(cmd,cmd_start_capture_pic_new)){
        //图片抓拍
        char *tokens[TOKEN_SIZE] = {0};
        int token_count = 0;
        get_cmd_token(cmd, tokens, &token_count);
        int camera_id = atoi(tokens[6]);
        CmdEntiry cap_picture_object(CAPTURE_PIC_ID, 1, 2, "get a capture pic", camera_id, false,"",current_time,buff,length,"");
        return cap_picture_object;
    }
    else if(is_begin_with(cmd,cmd_start_str_new)){
        //抽帧
        char *tokens[TOKEN_SIZE] = {0};
        int token_count = 0;
        get_cmd_token(cmd, tokens, &token_count);
        CmdEntiry cap_frame_object(PICK_ID, 5, 2, "get a capture pic", -1, true,"",current_time,buff,length,"");
        return cap_frame_object;
    }
    else if(is_begin_with(cmd,CMD_RECORDER_VIDEO_UPLOAD)){
        //视频提取
        char *tokens[TOKEN_SIZE] = {0};
        int token_count = 0;
        get_cmd_token(cmd, tokens, &token_count);
        int camera_id = atoi(tokens[3]);
        CmdEntiry upload_vedio_object(VEDIO_UPLOAD_ID, 1, 2, "recorder vedio upload", camera_id, false, "", current_time,buff,length,"");
        return upload_vedio_object;
    }
    return CmdEntiry(-1, -1, -1, "wrong command", -1, false, "", current_time,buff,length,"");
}
#endif

void checkAndRemoveExpiredTasks() {
    
    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> guard(listMutex);
        bool taskAdded = false;  // 标志，确保只加入一个任务
        auto it = runninglist.begin();
        while(it != runninglist.end()){
            if(it->isExpired()){
                std::cout << "Removing expired task: ";
                it->print();
                it = runninglist.erase(it);
                if(!waitinglist.empty()&&!taskAdded){
                    CmdEntiry newtask = waitinglist.front();
                    waitinglist.pop_front();
                    newtask.updateStartTime();
                    runninglist.push_back(newtask);
                    std::cout << "Moved task from waitingList to runningList: ";
                    newtask.print();
                    taskAdded = true;  // 设置标志，表示已加入一个任务
                }
            }
            else{
                ++it;
            }
        }
    }
}


#if 0
BuffAndLength handle_priority_commands(char* data, int data_size)
{
    int buff_length = data_size;
    char *buff = new char[buff_length];
    memcpy(buff, data, buff_length);

    //数据拷贝到缓冲区 data->g_cmd_buffer.cmd_buffer
    memcpy(g_cmd_buffer.cmd_buffer + g_cmd_buffer.cmd_buffer_size, data, data_size);
	g_cmd_buffer.cmd_buffer_size += data_size;
    //处理命令缓冲区的数据
    while (g_cmd_buffer.cmd_buffer_size)
    {
        char cmd[CMD_UNIT_SIZE] = { 0 };
		int cmd_size = 0;
        //解析命令数据
		int iret = parse_cmd_data(g_cmd_buffer.cmd_buffer, g_cmd_buffer.cmd_buffer_size, cmd, &cmd_size);
		if (iret == CMD_OK)
		{
            //移除已处理的命令数据
			memmove(g_cmd_buffer.cmd_buffer, g_cmd_buffer.cmd_buffer + cmd_size,
				g_cmd_buffer.cmd_buffer_size - cmd_size);
			g_cmd_buffer.cmd_buffer_size -= cmd_size;

            /*开始管控数据*/
            //检测到直播指令
            BuffAndLength result;
            if(isNeedManage(cmd))
            {
                CmdEntiry command = buildCmdEntiry(cmd,buff,buff_length);
                {
                    std::lock_guard<std::mutex> guard(listMutex);
                    if(command.getOperate()==1)
                    {
                        handleStartCommand(command);
                    }
                    else if(command.getOperate()==2)
                    {
                        result=handleStopCommand(command,buff,buff_length);
                        return result;
                    }
                }

                // 启动线程检查和移除过期的任务
                std::thread checkerThread(checkAndRemoveExpiredTasks);

                // 在运行队列有任务时，取出一个任务的 buff 和 buff_length 并返回
                {
                    std::lock_guard<std::mutex> guard(listMutex);
                    if(!runninglist.empty())
                    {
                        CmdEntiry runningCommand = runninglist.front(); // 取出第一个任务
                        result.buff1 = runningCommand.getBuff(); // 获取命令的 buff
                        result.length1 = runningCommand.getLength();// 获取命令的 buff_length
                    }
                    else{
                        result.buff1 = nullptr;
                        result.length1 = 0;
                    }
                }
                checkerThread.join(); // 确保线程完成
            }
            else{
                result.buff1 = nullptr;
                result.length1 = 0;
            }
            return result;
        }
    }
}
#endif

#if 1
BuffAndLength bufftest(char* data, int data_size)
{
    int buff_length = data_size;
    char *buff = new char[buff_length];
    memcpy(buff, data, buff_length);

    char cmd[] = "*MG2011BAF,869218069642112,892738516235071489,1,0,rtmp://live-k8s.4s12580.com:1946/live/869218069642112-0?streamId=892738516235071488,512,480#";
    BuffAndLength result;
    if(isNeedManage(cmd))
    {
        std::cout << "is need" << std::endl;
        CmdEntiry command = buildCmdEntiry(cmd,data,data_size);
        {
            std::lock_guard<std::mutex> guard(listMutex);
            if(command.getOperate()==1)
            {
                handleStartCommand(command);
            }
            else if(command.getOperate()==2)
            {
                result=handleStopCommand(command,buff,buff_length);
            }
        }
        std::thread checkerThread(checkAndRemoveExpiredTasks);
        {
            std::lock_guard<std::mutex> guard(listMutex);
            if(!runninglist.empty())
            {
                std::cout << "qurenwu" << std::endl;
                CmdEntiry runningCommand = runninglist.front();
                result.buff1 = runningCommand.getBuff();
                result.length1 = runningCommand.getLength();
            }
            else{
                std::cout << "else null" << std::endl;
                result.buff1 = nullptr;
                result.length1 = 0;
            }
        }
        checkerThread.join();
    }
    else{
        result.buff1 = nullptr;
        result.length1 = 0;
    }
}
#endif

void printResult(const BuffAndLength& result) {
    if (result.buff1 != nullptr && result.length1 > 0) {
        // 打印 buff 的内容
        std::cout << "Buff: ";
        for (int i = 0; i < result.length1; ++i) {
            std::cout << result.buff1[i];
        }
        std::cout << std::endl;

        // 打印 buff 的长度
        std::cout << "Buff Length: " << result.length1 << std::endl;
    } else {
        std::cout << "Buff is empty or invalid." << std::endl;
    }
}

// main 1
#if 0
int main() {

    //std::thread checkThread(checkRunningTasks);
    // 创建一些测试命令
    CmdEntiry startCmd1(1, 1, 3, "Start Command 1", 10, false, "file1", "10:00","abc",1);
    CmdEntiry startCmd2(2, 1, 1, "Start Command 2", 10, false, "file1", "9:00","abc",1);
    CmdEntiry startCmd3(2, 1, 1, "Start Command 3", 11, false, "file1", "9:00","abc",1);
    //CmdEntiry startCmd3(2, 1, 2, "Start Command 2", 10, false, "file1", "10:05");
    //CmdEntiry startCmd4(3, 1, 4, "Start Command 3", 10, true, "file1", "10:00");

    CmdEntiry stopCmd1(2, 2, 1, "Stop Command 2", 10, false, "file1", "10:15","abc",1);
    //CmdEntiry stopCmd2(2, 2, 1, "Stop Command 2", 10, true, "file2", "9:20");
    //CmdEntiry stopCmd3(3, 2, 0, "Stop Command 3", 20, true, "file3", "10:25");

    std::cout << "Initial Commands:\n";
    printQueueStatus();
    // 开始命令的处理
    handleStartCommand(startCmd2);
    std::cout << "\n--------------------------After 1 Commands:--------------------------\n";
    handleStartCommand(startCmd3);
    printQueueStatus();


    std::cout << "\nAfter Start Commands:\n";
    printQueueStatus();

    // 停止命令的处理
    handleStopCommand(stopCmd1);
    //handleStopCommand(stopCmd2);

    std::cout << "\nAfter Stop Commands:\n";
    printQueueStatus();
    //checkThread.join();


    return 0;
}
#endif
// main 2
#if 0
int main() {
    char cmd1[] = "*MG2011BAF,869218069642112,892738516235071489,1,0,rtmp://live-k8s.4s12580.com:1946/live/869218069642112-0?streamId=892738516235071488,512,480#";
    char cmd2[] = "*MG2011BAF,869218069642112,892738579946549248,0,#";
    char cmd3[] = "*MG2011BN,869218069642112,1721664000,1722355199,0,3,123456789#";
    char cmd4[] = "*MG2011RA,869218069642112,824706075664060416,1,0,2024-07-30 17:10:32:000,2024-07-30 17:11:32:999,892821291847921665,rtmp://live-k8s.4s12580.com:1936/playback/869218069642112-0?app=playback#";
    char cmd5[] = "*MG2011RA,869218069642112,892821319517745154,0,0,892821291847921665#";
    char cmd6[] = "*MG2011TASK,869218069642112,825324073911812096,0,165,0,2024-08-01 10:06:14,2024-08-01 10:07:14#";
    char cmd7[] = "*MG2011BMD,1,mg,MGLHX20240731172332";
    char cmd8[] = "*MG2011BADEX,1722416548130,1001,0,0";
    char cmd9[] = "";
    CmdEntiry cmd11 = buildCmdEntiry(cmd1);
    CmdEntiry cmd22 = buildCmdEntiry(cmd8);
    //CmdEntiry cmd33 = buildCmdEntiry(cmd3);
    //CmdEntiry cmd44 = buildCmdEntiry(cmd9);
    cmd11.print();
    cmd22.print();

    // 开始命令的处理
    handleStartCommand(cmd11);
    handleStartCommand(cmd22);


    std::cout << "\nAfter Start Commands:\n";
    printQueueStatus();

    //cmd33.print();
    //cmd44.print();

    return 0;
}
#endif
// main 3
#if 0
int main()
{
    char buff[] = "abc";
    int length = 1;
    BuffAndLength result;
    char cmd1[] = "*MG2011BAF,869218069642112,892738516235071489,1,0,rtmp://live-k8s.4s12580.com:1946/live/869218069642112-0?streamId=892738516235071488,512,480#";
    char cmd5[] = "*MG2011BAF,869218069642112,892738579946549248,0,0#";

    char cmd2[] = "*MG2011BN,869218069642112,1721664000,1722355199,0,3,123456789#";
    char cmd3[] = "*MG2011BMD,1,mg,MGLHX20240731172332";

    char cmd4[] = "*MG2011RA,869218069642112,824706075664060416,1,0,2024-07-30 17:10:32:000,2024-07-30 17:11:32:999,892821291847921665,rtmp://live-k8s.4s12580.com:1936/playback/869218069642112-0?app=playback#";
    char cmd6[] = "*MG2011RA,869218069642112,892821319517745154,0,0,892821291847921665#";

    CmdEntiry ADAS(10, 1, 0, "Start ADAS", 1, false,""," ",buff,length,"");
    CmdEntiry cmd11 = buildCmdEntiry(cmd1,buff,length);
    CmdEntiry cmd22 = buildCmdEntiry(cmd2,buff,length);
    CmdEntiry cmd33 = buildCmdEntiry(cmd3,buff,length);
    CmdEntiry cmd44 = buildCmdEntiry(cmd4,buff,length);
    CmdEntiry cmd66 = buildCmdEntiry(cmd6,buff,length);
    CmdEntiry cmd55 = buildCmdEntiry(cmd5,buff,length);

    {
        std::lock_guard<std::mutex> guard(listMutex);
        handleStartCommand(cmd11);
        handleStartCommand(ADAS);
        }
    std::thread checkerThread(checkAndRemoveExpiredTasks);

    while(true){
        {
            std::lock_guard<std::mutex> guard(listMutex);
            printQueueStatus();
            printResult(result);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));  // 模拟其他工作
    }

    checkerThread.join();
    return 0;
}
#endif

int main()
{
    char data[] = "Sample Data";
    int data_size = sizeof(data) / sizeof(data[0]);BuffAndLength result = bufftest(data, data_size);

    if (result.buff1 != nullptr) {
        std::cout << "Resulting buffer: " << result.buff1 << std::endl;
        std::cout << "Buffer length: " << result.length1 << std::endl;
    } else {
        std::cout << "No valid command was processed." << std::endl;
    }

    // 释放动态分配的内存
    delete[] result.buff1;

    return 0;
}