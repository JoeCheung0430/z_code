#include "myfile.h"
#include "zlog.h"
#include <direct.h> // For _mkdir

bool is_file_exist(const char * filePath)
{
	if ( filePath == NULL || strlen(filePath) == 0 )
	{
		return false;
	}
	if (access(filePath, 0) == 0)
	{
		return true;
	}
	return false;
}

int create_folder_r(const char *path)
{
	if ( is_file_exist(path) )
	{
		return 0;
	}

	char dir_name[256];
	strcpy(dir_name, path);
	int i, len = strlen(dir_name);
	if (dir_name[len - 1] != '/')
		strcat(dir_name, "/");

	len = strlen(dir_name);
	for (i = 1; i < len; i++)
	{
		if (dir_name[i] == '/')
		{
			dir_name[i] = 0;
			if (access(dir_name, 0) != 0)
			{
				if (_mkdir(dir_name) == -1)
				{
					LOG_ERROR("create dir:%s fail:%d",dir_name,errno);
					return 1;
				}
			}
			dir_name[i] = '/';
		}
	}
	return 0;
}

long long get_file_size(const char *filePath)
{
    FILE* file = std::fopen(filePath, "rb");
    if (file == nullptr)
    {
        LOG_ERROR("File: %s not existed or cannot be opened, Error: %s", filePath, strerror(errno));
        return -1; // 使用 -1 表示文件不存在或无法打开
    }

    std::fseek(file, 0, SEEK_END); // 移动到文件末尾
    long long size = std::ftell(file); // 获取当前位置，即文件大小
    std::fclose(file);

    return size;
}









