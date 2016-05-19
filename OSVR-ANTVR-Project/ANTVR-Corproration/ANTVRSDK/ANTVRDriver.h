#ifndef ANTVRDRIVER_H
#define ANTVRDRIVER_H


#ifdef __cplusplus
extern "C"{
#endif //__cplusplus

	//interface to AntvrHidApi.dll
	typedef void(*PGETANTVR_HEADSET_ROTATIONANGLE)(float& yaw, float& pitch, float &roll);

	PGETANTVR_HEADSET_ROTATIONANGLE							GetAntvrHeadsetRotationAngle = NULL;

	HMODULE antvrHidApi = NULL;



#ifdef __cplusplus
}
#endif //__cplusplus


#endif ANTVRDRIVER_H