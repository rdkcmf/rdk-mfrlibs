/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2014 RDK Management
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

/**
 * @file   mfrApi.h
 * @brief  MFRLibs API interface.
 *
 * This API defines the HAL for Manufacturer Libs interface.
 *
 * @par Document
 * Document reference.
 *
 * @par Open Issues (in no particular order)
 * -# None
 *
 * @par Assumptions
 * -# None
 *
 * @par Abbreviations 
 * - BE:      Big-Endian.
 * - cb:      Callback function (suffix).
 * - DS:      Device Settings.
 * - FPD:     Front-Panel Display.
 * - HAL:     Hardware Abstraction Layer.
 * - LE:      Little-Endian.
 * - LS:      Least Significant.
 * - MBZ:     Must be zero.
 * - MS:      Most Significant.
 * - RDK:     Reference Design Kit.
 * - _t:      Type (suffix).
 *
 * @par Implementation Notes
 * -# None
 *
 */
 
#ifndef _MFR_API_H__
#define _MFR_API_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "mfrTypes.h"

/**
 * @defgroup MFRLIBS MFRLibs
 * The Manufacturer Libraries (MFRLibs) is an abstraction layer used by various system components to gain access to:
 *  - hardware capabilities resident on the STB (aka. serialization data), 
 *    including manufacturer, model name, product class, hardware/software versions,
 *  - secure NVRAM, including DTCP certificates,
 *  - non-secure NVRAM, including boot image info,
 *  - flash memory for STB image upgrade.
 * Below are currently used APIs for the RDK enabled devices that need to be normalized into a set of
 * operator specific MFR APIs specification. These APIs should include any HALs as well as other dependent components.
 * - Initializes the manufacturer specific modules like, drivers, NVRAM and other devices
 * - Gets serialized read-only data from the device & it is upto the application to de-serialize and understand the data returned.
 * - Reads data from the secure NVRAM partition.
 * - Writes data to the secure NVRAM partition.
 * - Reads data from the un-secure NVRAM partition.
 * - Writes data to the un-secure NVRAM partition.
 * - Writes firmware image to the flash memory.
 * - API to take care of validating headers, manufacturer, model number and perform a signature
 * check while writing firmware image into the flash memory.
 * - Perform a CRC check after flashing the image to the NVRAM partition and write the CRC to a partition in NVRAM
 * - Gets current firmware upgrade status.
 *
 * @defgroup MFRLIBS_HAL_TYPES MFRLibs HAL Data types
 * @ingroup MFRLIBS
 *
 * @defgroup MFRLIBS_HAL_API MFRLibs HAL API
 * @ingroup MFRLIBS
 * @{
 */

/**
 * @brief Initializes the MFRLibs sub-system.
 *
 * This function initializes the manufacturer specific modules like, drivers, NVRAM and other devices.
 *
 * @param  None.
 *
 * @return Error code.
 * @retval ::mfrERR_NONE Initialization succeeced.
 * @retval ::mfrError_t  Other specific code on error. The initialization has failed and no further calls can work as expected.
 */
mfrError_t mfrInit(void);

/**
 * @brief Terminates the MFRLibs sub-system.
 *
 * This function terminates the manufacturer specific modules like drivers, NVRAM etc. 
 * It cancels the threads that are running within. No calls to the MFRLibs can be made after this call.
 *
 * @param  None.
 *
 * @return Error code.
 * @retval ::mfrERR_NONE Termination succeeded.
 * @retval ::mfrError_t Other specific code on error if the MFRLibs have not been properly terminated.
 */
mfrError_t mfrTerm(void);

/**
 * @brief Initializes the MFRLibs Firmware Upgrade sub-system.
 *
 * This function initializes the manufacturer specific modules like, drivers, NVRAM and other devices based on firmware upgrade requirements.
 *
 * @param  None.
 *
 * @return Error code.
 * @retval ::mfrERR_NONE Initialization succeeced.
 * @retval ::mfrError_t  Other specific code on error. The initialization has failed and no further calls can work as expected.
 */
mfrError_t mfrFWUpgradeInit(void);

/**
 * @brief Terminates the MFRLibs Firmware Upgrade sub-system.
 *
 * This function terminates the manufacturer specific modules like drivers, NVRAM etc based on firmware upgrade requirements.
 * It cancels the threads that are running within. No calls to the MFRLibs can be made after this call.
 *
 * @param  None.
 *
 * @return Error code.
 * @retval ::mfrERR_NONE Termination succeeded.
 * @retval ::mfrError_t Other specific code on error if the MFRLibs have not been properly terminated.
 */
mfrError_t mfrFWUpgradeTerm(void);

/**
 * @brief Gets serialized read-only data from the device.
 *
 * This function retrieves serialized read-only data from device. The serialized data is returned as a byte stream. 
 * It is up to the application to de-serialize and understande the data returned. The caller must allocate
 * memory for ::mfrSerializedData_t and pass it.
 *
 * @param [in] type  Type of serialized data to read.
 * @param [in] data  Memory location of a buffer to hold the ::mfrSerializedData_t data structure on return.
 *
 * @return Error code.
 * @retval ::mfrERR_NONE The data has been read successfully.
 * @retval ::mfrError_t  Other specific code on error. The reading has failed and values in @a data should not be used.
 *
 * @note The data buffer @a data->pBuffer will be provided by this function. The caller is only responsible
 * of releasing the data buffer if @a data->freeBuffer function is provided. If @a freeBuffer is not NULL then 
 * the caller must use this function to free the data buffer once it has finished using it. Otherwise the caller
 * must not try to free the data buffer.
 * Even if the serialized data returned as "string", the buffer is not required to contain the null-terminator.
 *
 */
mfrError_t mfrGetSerializedData( mfrSerializedType_t type,  mfrSerializedData_t *data );

/**
 * @brief Reads data from the secure NVRAM partition.
 *
 * This function is used to read the specified data from the secured partition of NVRAM. The caller must allocate
 * memory for ::mfrNVRAMData_t and pass it.
 *
 * @param [in]  eType      The type of secure data to be read.
 * @param [out] pNvRamData Memory location of a buffer to hold the ::mfrNVRAMData_t data structure on return.
 *
 * @return Error code.
 * @retval ::mfrERR_NONE The data has been read successfully.
 * @retval ::mfrError_t  Other specific code on error. The read has failed and contents of @a pNvRamData should not be used.
 *
 * @note The data buffer @a pNvRamData->pBuffer will be provided by this function. The caller is only responsible
 * of releasing the data buffer if @a pNvRamData->freeBuffer function is provided. If @a freeBuffer is not NULL then 
 * the caller must use this function to free the data buffer once it has finished using it. Otherwise the caller
 * must not try to free the data buffer.
 *

 */
mfrError_t mfrReadSecureNvram (mfrSecureNvramData_t eType, mfrNVRAMData_t * pNvRamData);

/**
 * @brief Reads data from the unsecure NVRAM partition.
 *
 * This function is used to read the specified data from the normal, not secured NVRAM partition. The caller must allocate
 * memory for ::mfrNVRAMData_t and pass it.
 *
 * @param [in]  eType       The type of non-secure data to be read.
 * @param [out] pNvRamData  Memory location of a buffer to hold the ::mfrNVRAMData_t data structure on return.
 *
 * @return Error code.
 * @retval ::mfrERR_NONE The data has been read successfully.
 * @retval ::mfrError_t  Other specific code on error. The read has failed and contents @a pNvRamData should not be used.
 *
 * @note The data buffer @a pNvRamData->pBuffer will be provided by this function. The caller is only responsible
 * of releasing the data buffer if @a pNvRamData->freeBuffer function is provided. If @a freeBuffer is not NULL then 
 * the caller must use this function to free the data buffer once it has finished using it. Otherwise the caller
 * must not try to free the data buffer.
 */
mfrError_t mfrReadUnsecureNvram (mfrUnsecureNvramData_t eType, mfrNVRAMData_t * pNvRamData);

/**
 * @brief Writes data to the secure NVRAM partition.
 *
 * This function is used to write the specified data to the secured NVRAM partition. The caller must allocate
 * memory for both ::mfrNVRAMData_t and data buffer @a pNvRamData->pBuffer.
 *
 * @param [in] eType       The type of secure data to write.
 * @param [in] pNvRamData  Memory location of a buffer that holds the ::mfrNVRAMData_t structure describing the 
 *                         data to write.
 * @return Error code.
 * @retval ::mfrERR_NONE The data has been read successfully.
 * @retval ::mfrError_t  Other specific code on error if the write has failed.
 *
 * @note If @a pNvRamData->freeBuffer function is provided (not NULL) then it will be used to release the 
 * @a pNvRamData->pBuffer data buffer when the write is complete. Otherwise the caller is responsible for freeing 
 * the data buffer.
 */
mfrError_t mfrWriteSecureNvram (mfrSecureNvramData_t eType, const mfrNVRAMData_t * pNvRamData);

/**
 * @brief Writes data to the unsecure NVRAM partition.
 *
 * This function is used to write the specified data to the normal, not secured NVRAM partition. The caller must allocate
 * memory for both ::mfrNVRAMData_t and data buffer @a pNvRamData->pBuffer.
 *
 * @param [in] eType       The type of non-secure data to write.
 * @param [in] pNvRamData  Memory location of a buffer that holds the ::mfrNVRAMData_t structure describing the
 *                         data to write.
 * @return Error code.
 * @retval ::mfrERR_NONE The data has been read successfully.
 * @retval ::mfrError_t  Other specific code on error if the write has failed.
 *
 * @note If @a pNvRamData->freeBuffer function is provided (not NULL) then it will be used to release the 
 * @a pNvRamData->pBuffer data buffer when the write is complete. Otherwise the caller is responsible for freeing 
 * the data buffer.
 */
mfrError_t mfrWriteUnsecureNvram (mfrUnsecureNvramData_t eType, const mfrNVRAMData_t * pNvRamData);

/**
 * @brief Writes firmware image to the flash memory.
 *
 * This function validates and writes a firmware image into the flash memory. The process should follow these major steps:
 *   - Validate headers, manufacturer, model.
 *   - Perform signature check.
 *   - Flash the image.
 *   - Perform CRC of flashed NVRAM.
 *   - Update boot params and switch banks to prepare for a reboot event.
 *
 * State transitions:
 *  - Before the this function is invoked, the upgrade process should be in ::mfrUPGRADE_PROGRESS_NOT_STARTED state.
 *  - After this function returns with success, the upgrade process moves to ::mfrUPGRADE_PROGRESS_STARTED state.
 *  - After this function returns with error, the upgrade process stays in ::mfrUPGRADE_PROGRESS_NOT_STARTED state.
 *      Notify function will not be invoked.
 *  - The notify function is called at regular interval with @a progress set to ::mfrUPGRADE_PROGRESS_STARTED.
 *  - The last invocation of notify function should have either @a progress set to ::mfrUPGRADE_PROGRESS_COMPLETED or
 *    ::mfrUPGRADE_PROGRESS_ABORTED with an appropriate error code set.
 *
 * @param [in] name    The filename of the image file.
 * @param [in] path    The path of the image file in the STB file system.
 * @param [in] type    The type (e.g. format, signature type) of the image.
 *                     This can dictate the handling of the image within the MFR library.
 * @param [in] notify  Memory location of the notification structure holding the callback to provide status
 *                     of the image flashing process.
 *
 * @return Error code.
 * @retval ::mfrERR_NONE The image flashing process has been started successfully.
 * @retval ::mfrError_t  Other specific code on error if the image flashing process has not started.
 *
 * @note All upgrades should be done in the alternate bank. The current bank should not be disturbed at any cost.
 * (I.e. a second upgrade before a reboot will overwrite the non-current bank only.)
 */
mfrError_t mfrWriteImage(const char *name,  const char *path, mfrImageType_t type,  mfrUpgradeStatusNotify_t notify);

/**
 * @brief Gets current firmware upgrade status.
 *
 * This function returns the current status of the upgrade process. The caller must allocate memory for
 * ::mfrUpgradeProgress_t and pass it. 
 *
 * @param [out] pStatus  Memory location of a buffer to hold ::mfrUpgradeProgress_t data structure on return.
 *
 * @return Error code.
 * @retval ::mfrERR_NONE The upgrade status has been retrieved successfully.
 * @retval ::mfrError_t  Other specific code on error if the status couldn't be retrieved.
 */
mfrError_t mfrGetUpgradeStatus(mfrUpgradeProgress_t *pStatus);

/* End of MFRLIBS_HAL_API doxygen group */
/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif /* __MFR_API_H__ */

