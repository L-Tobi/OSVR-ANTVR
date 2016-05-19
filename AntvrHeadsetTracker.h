


#ifndef INCLUDE_ANTVRHEADSETTRACKER_H
#define INCLUDE_ANTVRHEADSETTRACKER_H

// Internal Includes
// - none

// Library/third-party includes
#include<ANTVRSDK.h>
#include<Windows.h>

// Standard includes
#include <iostream>
#include<tchar.h>
namespace {
class AntvrHeadsetTracker
{
public:
	AntvrHeadsetTracker(){ 
		m_dllstatus = LoadAntvrDLL(); 
		if (m_dllstatus == 5) 
			std::cout << "[ANTVR]:" << "Successfully Loaded DLL!" << std::endl;
		else 
			std::cout << "[ANTVR] :" << "Failed Loaded DLL" << std::endl;
	};
	~AntvrHeadsetTracker() {};

	int GetDllStatus() { return m_dllstatus; }

	void GetTrackQuaternion(float &_x, float &_y, float &_z, float &_w)
	{
		GetAntvrHeadsetRotationQuaternion(_x, _y, _z, _w);
	}
private:
	int m_dllstatus;
};
}
#endif //INCLUDE_ANTVRHEADSETTRACKER_H