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

#include <stdio.h>
#include <mfrMgr.h>
#include <mfrTypes.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PARAM_LEN 255
#define SIZE 50
void mfrFreeBuffer(char *buf)
{
	if(!buf)
		return;
	free(buf);

}

mfrError_t mfrGetSerializedData(mfrSerializedType_t param, mfrSerializedData_t *data)
{
	char cmd[100];// = "ifconfig | grep eth0 | tr -s ' ' | cut -d ' ' -f5 | sed -e 's/://g'";
	char mac[MAX_PARAM_LEN];
	FILE *fp = NULL;
	if(!data)
		return mfrERR_NONE;
	data->freeBuf=mfrFreeBuffer;	
	switch(param)
	{
		case mfrSERIALIZED_TYPE_MANUFACTURER:
			data->buf = (char*)malloc(sizeof(char) * MAX_PARAM_LEN);
			strcpy(data->buf,"LT TECHNOLOGY SERVICES");
			data->bufLen = strlen(data->buf);
			printf("buf= %s\t len=%d\n",data->buf,data->bufLen);
			break;

		case mfrSERIALIZED_TYPE_MANUFACTUREROUI:
			data->buf = (char*)malloc(sizeof(char) * MAX_PARAM_LEN);
			strcpy(data->buf,"A055DE");
			data->bufLen = strlen(data->buf);
			break;

		case mfrSERIALIZED_TYPE_MODELNAME:

			data->buf = (char*)malloc(sizeof(char) * MAX_PARAM_LEN);
			strcpy(data->buf,"RDKEMULATOR");
			data->bufLen = strlen(data->buf);
			break;

		case mfrSERIALIZED_TYPE_DESCRIPTION:

			data->buf = (char*)malloc(sizeof(char) * MAX_PARAM_LEN);
			strcpy(data->buf,"RDKEMULATOR- Desktop based implementation of RDK Software Stack");
			data->bufLen = strlen(data->buf);
			break;

		case mfrSERIALIZED_TYPE_PRODUCTCLASS:
			data->buf = (char*)malloc(sizeof(char) * MAX_PARAM_LEN);
			strcpy(data->buf,"RDK");
			data->bufLen = strlen(data->buf);
			break;

		case mfrSERIALIZED_TYPE_SERIALNUMBER:

			data->buf = (char*)malloc(sizeof(char) * MAX_PARAM_LEN);
			memset(data->buf,'\0',sizeof(char)*MAX_PARAM_LEN);
			//Generate serail number based on MAC Address
			//`ifconfig -a | sed 's/[ \t].*//;/^\(lo\|\)$/d' | head -n1` will extract ifname.

			sprintf(cmd,"ifconfig | grep `ifconfig -a | sed 's/[ \t].*//;/^\(lo\|\)$/d' | head -n1` | tr -s ' ' | cut -d ' ' -f5 | sed -e 's/://g'");

			if (( fp = popen(cmd, "r")) == NULL)
			{
				printf("popen failed.");

			}
			if(fp)
			{
				fgets(mac, sizeof(mac), fp) ;
				strcpy(data->buf,"RDKEMULATOR");
				strcat(data->buf,mac);
				data->bufLen = strlen(data->buf)-1;
				printf("MAC Address 1=%s \n",data->buf);
				pclose(fp);
			}

			break;

		case mfrSERIALIZED_TYPE_HARDWAREVERSION:

			data->buf = (char*)malloc(sizeof(char) * MAX_PARAM_LEN);
			strcpy(data->buf,"1.0");
			data->bufLen = strlen(data->buf);
			break;

		case mfrSERIALIZED_TYPE_SOFTWAREVERSION:

			data->buf = (char*)malloc(sizeof(char) * MAX_PARAM_LEN);
			strcpy(data->buf,"SW-VERSION-1.0");
			data->bufLen = strlen(data->buf);
			break;

		case mfrSERIALIZED_TYPE_PROVISIONINGCODE:
		case mfrSERIALIZED_TYPE_FIRSTUSEDATE:
		case mfrSERIALIZED_TYPE_MOCAMAC:
		case mfrSERIALIZED_TYPE_HDMIHDCP:
		case mfrSERIALIZED_TYPE_MAX:
			data->buf = (char*)malloc(sizeof(char) * MAX_PARAM_LEN);
			strcpy(data->buf,"XXXX");
			data->bufLen = strlen(data->buf);
			break;
		case mfrSERIALIZED_TYPE_DEVICEMAC:
			data->buf = (char*)malloc(sizeof(char) * MAX_PARAM_LEN);
			memset(data->buf,'\0',sizeof(char)*MAX_PARAM_LEN);
			sprintf(cmd,"ifconfig | grep `ifconfig -a | sed 's/[ \t].*//;/^\(lo\|\)$/d' | head -n1` | tr -s ' ' | cut -d ' ' -f5 | sed -e 's/://g'");

			if (( fp = popen(cmd, "r")) == NULL)
			{
				printf("popen failed.");

			}
			if(fp)
			{
				fgets(mac, sizeof(mac), fp) ;
				// strcpy(data->buf,"RDKEMULATOR-");
				strcat(data->buf,mac);
				data->bufLen = strlen(data->buf)-1;
				printf("MAC Address 1=%s \n",data->buf);
				pclose(fp);
			}
			break;
		default:
			data->buf = (char*)malloc(sizeof(char) * MAX_PARAM_LEN);
			strcpy(data->buf,"XXXX");
			data->bufLen = strlen(data->buf);
			break;
	}
	return mfrERR_NONE;
}

mfrError_t mfrDeletePDRI()
{
	return mfrERR_NONE;
}

mfrError_t mfrScrubAllBanks()
{
	return mfrERR_NONE;
}

mfrError_t mfrWriteImage(const char *str,  const char *str1, 
		mfrImageType_t imageType,  mfrUpgradeStatusNotify_t upgradeStatus)
{
	return mfrERR_NONE;
}

mfrError_t mfr_init()
{
	return mfrERR_NONE;
}
