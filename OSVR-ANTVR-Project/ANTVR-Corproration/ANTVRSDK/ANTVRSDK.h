#ifndef ANTVRSDK_H
#define ANTVRSDK_H

#include<Windows.h>
#include "AntvrDriver.h"
#ifdef __cplusplus
extern "C"{
#endif //__cplusplus

	enum ANTVR_RETURN
	{
		ANTVR_FAILED				= 0,
		ANTVR_SUCCESS				= 1,
		ANTVR_DEV_NOT_EXIST			= 2,
		ANTVR_DEV_EXIST				= 3,
		ANTVR_LOAD_LIBRARY_FAILED	= 4,
		ANTVR_LOAD_LIBRARY_SUCCESS	= 5,
		ANTVR_LOAD_FUNCTION_ERROR	= 6,
	};


	int LoadAntvrDLL()
	{
		antvrHidApi = LoadLibraryA("AntvrHidApi.dll");
		if (antvrHidApi)
		{
			GetAntvrHeadsetRotationAngle = (PGETANTVR_HEADSET_ROTATIONANGLE)GetProcAddress(antvrHidApi, "GetAntvrHeadsetRotationAngle");
			if (!GetAntvrHeadsetRotationAngle)
				return ANTVR_LOAD_FUNCTION_ERROR;
			else
				return ANTVR_LOAD_LIBRARY_SUCCESS;
		}
		return ANTVR_LOAD_LIBRARY_FAILED;
	}

	int FreeAntvrDLL()
	{
		if (antvrHidApi)
		{
			FreeLibrary(antvrHidApi);
			antvrHidApi = NULL;
			return ANTVR_SUCCESS;
		}
		return ANTVR_SUCCESS;
	}


#ifdef __cplusplus
}
#endif //__cplusplus

#endif ANTVRSDK_H