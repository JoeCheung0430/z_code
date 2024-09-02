#include <cstring>
#include <iostream>
#include <string>

std::string get_first_token(const char* cmd) {
    // 找到第一个逗号的位置
    const char* comma_pos = strchr(cmd, ',');
    if (comma_pos != nullptr) {
        // 计算第一个 token 的长度
        int length = comma_pos - cmd;
        // 返回第一个 token
        return std::string(cmd, length);
    } else {
        // 如果没有逗号，整个字符串作为第一个 token
        return std::string(cmd);
    }
}



int main() 
{
    // 示例命令字符串
    const char* cmd = "*MG2011BACEX,123,456,789";

    // 获取并打印第一个 token
    std::string first_token = get_first_token(cmd);
    std::cout << "First token: " << first_token << std::endl;

    return 0;
}
