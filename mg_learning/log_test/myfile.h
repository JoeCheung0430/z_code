#ifndef __MYFILE__
#define __MYFILE__


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cerrno>
#include <cstring>


#define LOG_DIR_PATH 			"/data/mlink/log"

bool is_file_exist(const char *filePath);
int create_folder_r(const char *path);
long long get_file_size(const char *filePath);

#ifndef     SAFE_CLOSE
#define SAFE_CLOSE(p)                   { if( (p) != NULL ) { close(p);     (p) = 0; } }
#endif

#ifndef     SAFE_FREE
#define SAFE_FREE(p)                    { if(p != NULL) { free((p)); (p) = NULL; } }
#endif


#endif
