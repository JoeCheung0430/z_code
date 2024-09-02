#ifndef __RET__
#define __RET__

typedef enum {
    EM_RC_OK = 0,
    EM_RC_INITED_ERR,
    EM_RC_FILE_OPEN_ERR,
    EM_RC_FILE_EXIST_ERR,
    EM_RC_DIR_ERR,
    EM_RC_PARAM_ERR
}ERetCode;

#endif