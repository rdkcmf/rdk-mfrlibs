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

#ifndef __MFR_TYPES_H__
#define __MFR_TYPES_H__

#include <stdlib.h>
#include <stdint.h>

/**
 * @file   mfrTypes.h
 * @brief  MFRLibs API interface.
 *
 * This API defines common types used by the Manufacturer Libs.
 *
 * @par Abbreviations 
 * - BE:      Big-Endian.
 * - cb:      Callback function (suffix).
 * - DS:      Device Settings.
 * - DTCP:    Digital Transmission Content Protection.
 * - EMI:     Encryption Mode Indicator.
 * - FPD:     Front-Panel Display.
 * - HAL:     Hardware Abstraction Layer.
 * - LE:      Little-Endian.
 * - LS:      Least Significant.
 * - MBZ:     Must be zero.
 * - MS:      Most Significant.
 * - NVRAM:   Non-Volatile Random-Access Memory.
 * - OUI:     Organizationally Unique Identifier.
 * - RDK:     Reference Design Kit.
 * - _t:      Type (suffix).
 *
 * @par Implementation Notes
 * -# None
 *
 */

/** 
 *  @addtogroup MFRLIBS_HAL_TYPES
 *  @{
 */
 
/**
 * @brief MFRLibs return codes.
 *
 * This enumeration defines types of errors that can be returned from the MFRLibs sub-system.
 */
typedef enum _mfrError_t {
    mfrERR_NONE = 0,                    /**< Operation successful.      */
    mfrERR_GENERAL = 0x1000,            /**< General unspecified error. */
    mfrERR_INVALID_PARAM,               /**< Invalid input parameters.  */
    mfrERR_INVALID_STATE,               /**< Invalid state.             */
    mfrERR_OPERATION_NOT_SUPPORTED,     /**< Operation not supported.   */
    mfrERR_MALLOC_FAILED,               /**< Memory allocation failed.  */
    mfrERR_NOT_INITIALIZED,             /**< MFRLibs not initialized.   */
    mfrERR_ENCRYPTION_FAILED,           /**< Encryption failed.         */
    mfrERR_DECRYPTION_FAILED,           /**< Decryption failed.         */
    mfrERR_UNKNOWN,                     /**< Unknown error.             */
} mfrError_t;

/**
 * @brief Serialized data types.
 *
 * This enumeration defines types of read-only data that can be read from the hardware.
 */
typedef enum _mfrSerializedType_t {
    mfrSERIALIZED_TYPE_MANUFACTURER = 0,                /**< Manufacturer name.             */
    mfrSERIALIZED_TYPE_MANUFACTUREROUI,                 /**< Manufacturer OUI.              */
    mfrSERIALIZED_TYPE_MODELNAME,                       /**< CPE model name.                */
    mfrSERIALIZED_TYPE_DESCRIPTION,                     /**< CPE description.               */
    mfrSERIALIZED_TYPE_PRODUCTCLASS,                    /**< Product class.                 */
    mfrSERIALIZED_TYPE_SERIALNUMBER,                    /**< CPE serial number.             */
    mfrSERIALIZED_TYPE_HARDWAREVERSION,                 /**< Hardware version.              */
    mfrSERIALIZED_TYPE_SOFTWAREVERSION,                 /**< Software version.              */
    mfrSERIALIZED_TYPE_PROVISIONINGCODE,                /**< ACS provisioning code.         */
    mfrSERIALIZED_TYPE_FIRSTUSEDATE,                    /**< First use date and time (UTC). */
    mfrSERIALIZED_TYPE_VENDOR_CONFIGFILE_ENTRIES,       /**< Vendor ConfigFile entries.     */
    mfrSERIALIZED_TYPE_VENDOR_LOGFILE_ENTRIES,          /**< Vendor LogFile entries.        */
    mfrSERIALIZED_TYPE_SUPPORTED_DATAMODEL_ENTRIES,     /**< Supported DataModel entries.   */
    mfrSERIALIZED_TYPE_PROCESSOR_ENTRIES,               /**< Processor entries.             */ 
    mfrSERIALIZED_TYPE_MAX,                             /**< Maxium index.                  */
} mfrSerializedType_t;

/**
 * @brief Secure NVRAM data types.
 *
 * This enumeration defines types of data that can be read from the secure NVRAM partition.
 */
typedef enum _mfrSecureNvramData_t
{
    mfrSECURE_NVRAM_DATA_NONE = 0x0,                   /**< None.                  */
    mfrSECURE_NVRAM_DATA_IEEE1394_DTCP_CERT_KEYS,      /**< DTCP certificate.      */
    mfrSECURE_NVRAM_DATA_IEEE1394_DTCP_SRM,            /**< DTCP SRM.              */
    mfrSECURE_NVRAM_DATA_IEEE1394_DTCP_SEED,           /**< DTCP seed.             */
    mfrSECURE_NVRAM_DATA_INVALID                       /**< Invalid type.          */
}mfrSecureNvramData_t;

/**
 * @brief Secure NVRAM data types.
 *
 * This enumeration defines types of data that can be read from the unsecure NVRAM partition.
 */
typedef enum _mfrUnsecureNvramData_t
{
    mfrUNSECURE_NVRAM_DATA_NONE = 0,                    /**< None.                     */
    mfrUNSECURE_NVRAM_DATA_PREVIOUS_IMAGE_NAME,         /**< Previous image name.      */
    mfrUNSECURE_NVRAM_DATA_BOOT_IMAGE_NAME,             /**< Boot image name.          */
    mfrUNSECURE_NVRAM_DATA_UPGRADE_IMAGE_NAME,          /**< Upgrade immge name.       */
    mfrUNSECURE_NVRAM_DATA_IEEE1394_DTCP_KEY_TYPE,      /**< DTCP key type.            */
    mfrUNSECURE_NVRAM_DATA_IEEE1394_DTCP_KEY_STATUS,    /**< DTCP key status.          */
    mfrUNSECURE_NVRAM_DATA_INVALID                      /**< Invalid type.             */
}mfrUnsecureNvramData_t;

/**
 * @brief Upgrade image types.
 *
 * This enumeration defines the types of upgrade images.
 */
typedef enum _mfrImageType_t {
    mfrIMAGE_TYPE_CDL,  /**< DOCSIS-based download. */
    mfrIMAGE_TYPE_RCDL, /**< HTTP-based download.   */
} mfrImageType_t;

/**
 * @brief Upgrade status types.
 *
 * This enumeration defines the statuses of an initiated firmware upgrade.
 */
typedef enum _mfrUpgradeProgress_t {
  mfrUPGRADE_PROGRESS_NOT_STARTED = 0,  /**< Upgrade not started.            */
  mfrUPGRADE_PROGRESS_STARTED,          /**< Upgrade in progress.            */
  mfrUPGRADE_PROGRESS_ABORTED,          /**< Upgrade aborted.                */
  mfrUPGRADE_PROGRESS_COMPLETED,        /**< Upgrade successfully completed. */
} mfrUpgradeProgress_t;

/**
 * @brief Serialized data structure.
 * 
 * This structure defines the serialized read-only data. 
 */
typedef struct _mfrSerializedData_t {
    size_t bufLen;                      /**< Length of the data buffer.                                  */
    char *pBuffer;                      /**< Buffer containing the serialized data.                      */
    void (* freeBuffer) (char *buf);    /**< Function used to free the buffer. If NULL, nothing to free. */
} mfrSerializedData_t;

/**
 * @brief NVRAM data structure.
 *
 * This structure defines the data read/written to the NVRAM memory.
 */
typedef mfrSerializedData_t mfrNVRAMData_t;

/**
 * @brief Upgrade status structure.
 *
 * This structure defines the upgrade status information.
 */
typedef struct _mfrUpgradeStatus_t {
  mfrUpgradeProgress_t progress;        /**< Status of progress (e.g. started, aborted).  */  
  mfrError_t error;                     /**< The error code to denote the upgrade status. */
  int percentage;                       /**< Percentage of the upgrade progress.          */
} mfrUpgradeStatus_t;

/**
 * @brief Upgrade status notification structure.
 *
 * This structure defines the upgrade notification callback and its frequency of occurence.
 */
typedef struct _mfrUpgradeStatusNotify_t {
    void (*cb) (mfrUpgradeStatus_t status); /**< Pointer to the callback function used to notify of the upgrade status. */
    int interval;  /**< Interval in seconds between two successive callbacks.  
                    * The value 0 means that the notification is expected only once to report final upgrade result.
                    * @note Manufacturer must at least support notifying the upgrade status at the end. */    

    
} mfrUpgradeStatusNotify_t;

/* End of MFRLIBS_HAL_TYPES doxygen group */
/**
 * @}
 */

#endif // __MFR_TYPES_H__

