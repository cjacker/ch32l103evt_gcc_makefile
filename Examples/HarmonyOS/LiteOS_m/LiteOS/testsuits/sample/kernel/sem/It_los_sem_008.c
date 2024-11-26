/*
 * Copyright (c) 2013-2019 Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "osTest.h"
#include "It_los_sem.h"


static UINT32 Testcase(VOID)
{
    UINT32 ret;
    UINT32 i, ix;
    UINT32 semHandle[LOSCFG_BASE_IPC_SEM_LIMIT + 1];
    LosSemCB *semNode = NULL;

    UINT32 osMuxUsedcnt = 0;

    for (i = 0; i < LOSCFG_BASE_IPC_SEM_LIMIT; i++) {
        semNode = g_allSem + i;
        if (semNode->semStat == OS_SEM_USED) {
            osMuxUsedcnt++;
        }
    }

    for (i = 0; i < LOSCFG_BASE_IPC_SEM_LIMIT; i++) {
        ret = LOS_SemCreate(0, &semHandle[i]);
        if (ret != LOS_OK) {
            if ((i + osMuxUsedcnt) != LOSCFG_BASE_IPC_SEM_LIMIT) {
                ICUNIT_GOTO_EQUAL(ret, LOS_OK, ret, EXIT);
            } else {
                break;
            }
        }
    }

    ret = LOS_SemCreate(0, &semHandle[LOSCFG_BASE_IPC_SEM_LIMIT]);
    ICUNIT_TRACK_EQUAL(ret, LOS_ERRNO_SEM_ALL_BUSY, ret);

EXIT:
    for (ix = 0; ix < i; ix++) {
        ret = LOS_SemDelete(semHandle[ix]);
        ICUNIT_TRACK_EQUAL(ret, LOS_OK, ret);
    }

    return LOS_OK;
}

VOID ItLosSem008(void)
{
    TEST_ADD_CASE("ItLosSem008", Testcase, TEST_LOS, TEST_SEM, TEST_LEVEL0, TEST_FUNCTION);
}

