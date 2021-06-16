/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2017 RDK Management
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
#include "mfr_temperature.h"

static int g_iTempThresholdHigh = 60;
static int g_iTempThresholdCritical = 75;

/**
* @brief get current temperature of the core
*
* @param [out] curState:  the current state of the core temperature
* @param [out] temperatureValue:  raw temperature value of the core
*              in degrees Celsius
* @param [out] wifiTemp: temperature value of wifi chipset
*
* @return Error Code
*/
mfrError_t mfrGetTemperature(mfrTemperatureState_t *curState, int *temperatureValue, int *wifiTemp)
{
    if ( curState == NULL || temperatureValue == NULL || wifiTemp == NULL )
        return mfrERR_INVALID_PARAM;

    int value = 0;
    mfrTemperatureState_t state = mfrTEMPERATURE_NORMAL;

    FILE* fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if( fp != NULL )
    {
        fscanf (fp, "%d", &value);
        fclose(fp);
    }

    value /= 1000;

    if( value >= g_iTempThresholdHigh )
        state = mfrTEMPERATURE_HIGH;
    if( value >= g_iTempThresholdCritical )
        state = mfrTEMPERATURE_CRITICAL;

    *curState = state;
    *temperatureValue = value;

    return mfrERR_NONE;
}

/**
* @brief Set temperature thresholds which will determine the state returned
<200b><200b>*        from a call to mfrGetTemperature
*
* @param [in] tempHigh:  Temperature threshold at which mfrTEMPERATURE_HIGH
*                        state will be reported.
* @param [in] tempCritical:  Temperature threshold at which mfrTEMPERATURE_CRITICAL
*                            state will be reported.
*
* @return Error Code
*/
mfrError_t mfrSetTempThresholds(int tempHigh, int tempCritical)
{
    g_iTempThresholdHigh     = tempHigh;
    g_iTempThresholdCritical = tempCritical;

    return mfrERR_NONE;
}


/**
* @brief Get the temperature thresholds which determine the state returned
<200b><200b>*        from a call to mfrGetTemperature
*
* @param [out] tempHigh:  Temperature threshold at which mfrTEMPERATURE_HIGH
*                        state will be reported.
* @param [out] tempCritical:  Temperature threshold at which mfrTEMPERATURE_CRITICAL
*                            state will be reported.
*
* @return Error Code
*/
mfrError_t mfrGetTempThresholds(int *tempHigh, int *tempCritical)
{
    if( tempHigh == NULL || tempCritical == NULL )
        return mfrERR_INVALID_PARAM;

    *tempHigh     = g_iTempThresholdHigh;
    *tempCritical = g_iTempThresholdCritical;

    return mfrERR_NONE;
}
