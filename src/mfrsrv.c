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
#include <unistd.h>
#include <pthread.h>
#include "mfrApi.h"
#include "uidev.h"


#define _DEBUG_ENTER() do {\
}while(0)

#define _DEBUG_EXIT(ret)  do {\
}while(0)

#define _MGR_NAME "MFRLibs"
#define IARM_Lock(lock) pthread_mutex_lock(&fpLock)
#define IARM_Unlock(lock) pthread_mutex_unlock(&fpLock)

static int m_isInitialized = 0;
static int m_isPlatInitialized = 0;
static void *m_grpCtx = NULL;
static pthread_mutex_t fpLock = PTHREAD_MUTEX_INITIALIZER;

static void _mfrInit (void *callCtx, unsigned long methodID, void *arg, unsigned int serial);
static void _mfrTerm (void *callCtx, unsigned long methodID, void *arg, unsigned int serial);

CMAF_Result_t mfrMgr_Init(void *grpCtx)
{
    CMAF_RegisterCall(grpCtx, _MGR_NAME, "mfrInit", _mfrInit, NULL/*callCtx*/);
    m_grpCtx = grpCtx;
    return CMAF_RESULT_SUCCESS;
}

CMAF_Result_t mfrMgr_Term (void *grpCtx)
{
    m_grpCtx = NULL;
    return CMAF_RESULT_SUCCESS;
}

static void _mfrInit (void *callCtx, unsigned long methodID, void *arg, unsigned int serial)
{
    IARM_Lock(lock);
    if (!m_isInitialized) {
        CMAF_RegisterCall(m_grpCtx, _MGR_NAME, "mfrTerm", _mfrTerm, NULL/*callCtx*/);
        m_isInitialized = 1;
    }

    if (!m_isPlatInitialized) {
        mfrInit();
        m_isPlatInitialized = 1;
    }
    CMAF_CallReturn(m_grpCtx, _MGR_NAME, "mfrInit", 0, serial);
    IARM_Unlock(lock);
}
static void _mfrTerm (void *callCtx, unsigned long methodID, void *arg, unsigned int serial)
{
    /*@TODO: Deregister the calls, if necessary */
    _DEBUG_ENTER();
    mfrError_t ret = mfrERR_NONE;
    IARM_Lock(lock);
    if (m_isPlatInitialized) {
        ret = mfrTerm ();
        printf("Un-init of MFR libs is done\r\n");
        m_isPlatInitialized = 0;
    }
    CMAF_CallReturn(m_grpCtx, _MGR_NAME, "mfrTerm", ret, serial);
    IARM_Unlock(lock);
}


