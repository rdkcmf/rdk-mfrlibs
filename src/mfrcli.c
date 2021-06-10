/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2013 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include <stdio.h>
#include <string.h>
#include "mfrApi.h"
#include "uidev.h"

#define _DEBUG_ENTER() do {\
}while(0)

#define _DEBUG_EXIT(ret)  do {\
}while(0)


static void *m_grpCtx = NULL;
static inline mfrError_t _IARM_CALL(char * _CALL_NAME, void *arg) 
{
    mfrError_t rpcRet = mfrERR_NONE; 
    CMAF_Call(m_grpCtx, "MFRLibs", _CALL_NAME, arg, (int *)&rpcRet);
    return rpcRet;
} 

mfrError_t mfrInit (void)
{
    _DEBUG_ENTER();
    if (m_grpCtx == NULL) {
        if (UIDev_GetContext(&m_grpCtx) == CMAF_RESULT_SUCCESS) {
            CMAF_Result_t rpcRet = CMAF_RESULT_SUCCESS;
            CMAF_Call(m_grpCtx, "MFRLibs", "mfrInit", NULL, (int *)&rpcRet);
            printf ("mfrInit() is successfully done\n");
        }
        else {
            printf ("mfrInit() is failed \n");
            return mfrERR_GENERAL;
        }
    }
    else {
        printf ("mfrInit() is already called\r\n");
    }

    return mfrERR_NONE;
}

mfrError_t mfrTerm (void)
{
    _DEBUG_ENTER();
    _RETURN_IF_ERROR(m_grpCtx != NULL, mfrERR_INVALID_STATE);
    mfrError_t ret = _IARM_CALL ("mfrTerm", NULL);

    return ret;
}

