#include <string>
#include <cstring> // For strcpy and strlen
#include <sstream> // For std::ostringstream
#include <iostream>

struct _local_command_info_{
    std::string g_local_command_head;
    std::string g_local_imei;
    int g_channel;
} g_local_cmd;

void set()
{
    g_local_cmd.g_local_command_head = "STOP_WIFI_PLAYBACK";
    g_local_cmd.g_local_imei = "869218069642112";
    g_local_cmd.g_channel = 1;
}

template<typename... Args>
char* combineCommandInfo(Args... args) {
    std::ostringstream oss;

    // 使用 fold expression 将参数合并为字符串
    ((oss << args << ","), ...);

    std::string combined = oss.str();

    // 去掉最后一个逗号并添加 '#'
    if (!combined.empty()) {
        combined.back() = '#';
    }

    // 分配内存
    char* result = new char[combined.length() + 1];
    std::strcpy(result, combined.c_str());

    return result;
}

int createLocalCommand(char * pbyBuff, int iSize)
{
    char *local_command = combineCommandInfo(g_local_cmd.g_local_command_head,
    g_local_cmd.g_local_imei,
    g_local_cmd.g_channel);

    // 结构体置0（用完即清）

    int size = strlen(local_command);
    //std::cout << "size" << size <<std::endl;
    if(size > 0)
    {
        iSize = size;
        std::memcpy(pbyBuff, local_command, size);
        std::cout << "Create local command successfully!" << std::endl;
    }
    else{
        std::cout << "Create local command fail!" << std::endl;
    }
    return size;
}

int localRecvNoblock(char *pbyBuff, int iSize)
{
    int length = createLocalCommand(pbyBuff, iSize);
    if(length <= 0)
    {
        std::cout << "local recv error!" << std::endl;
    }
    return length;
}


int main() {
    set();

    int iret = 0;
	char buff[32768] = { 0 };
	int data_length = localRecvNoblock(buff, 32768);
	if (data_length > 0)
    {
        std::cout << "cmd1:" << buff << std::endl;
    }
    return 0;
}