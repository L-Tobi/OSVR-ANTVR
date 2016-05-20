/** @file
    @brief Comprehensive example: Implementation of a dummy Hardware Detect
   Callback that creates a dummy device when it is "detected"

    @date 2016

    @author
    ANTVR, Inc.
    <http://antvr.com/>
*/

// Copyright 2016 ANTVR, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#define _USE_MATH_DEFINES

// Internal Includes
#include <osvr/PluginKit/PluginKit.h>
#include <osvr/PluginKit/TrackerInterfaceC.h>
#include "ANTVRHeadsetTracker.h"
// Generated JSON header file
#include "com_osvr_ANTVR_json.h"

// Library/third-party includes

// Standard includes
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <time.h>

// Anonymous namespace to avoid symbol collision
namespace {

typedef std::shared_ptr<AntvrHeadsetTracker> AntvrheadsetPtr;

class AntvrHeadset {
  public:
	  AntvrHeadset(OSVR_PluginRegContext ctx, AntvrheadsetPtr antvrheadptr) {
        /// Create the initialization options
        OSVR_DeviceInitOptions opts = osvrDeviceCreateInitOptions(ctx);

		tracker = antvrheadptr;

		osvrDeviceTrackerConfigure(opts, &m_tracker);

        /// Create the device token with the options
        m_dev.initAsync(ctx, "Antvr", opts);

        /// Send JSON descriptor
		m_dev.sendJsonDescriptor(com_osvr_ANTVR_json);

        /// Register update callback
        m_dev.registerUpdateCallback(this);

    }

    OSVR_ReturnCode update() {

		float x = 0, y = 0, z = 0, w = 0;

		//get data from here
		tracker->GetTrackQuaternion(w, x, y, z);

		OSVR_OrientationState trackerCoords = { x, y, z, w };

		osvrDeviceTrackerSendOrientation(m_dev, m_tracker, &trackerCoords, 0);

        return OSVR_RETURN_SUCCESS;
    }

  private:
    osvr::pluginkit::DeviceToken m_dev;
    OSVR_TrackerDeviceInterface m_tracker;
	AntvrheadsetPtr tracker;
};

class HardwareDetection {
  public:
	  HardwareDetection() : tracker(new AntvrHeadsetTracker()){}
    OSVR_ReturnCode operator()(OSVR_PluginRegContext ctx) {

        std::cout << "PLUGIN: Got a hardware detection request" << std::endl;
        if (tracker->GetDllStatus() == ANTVR_LOAD_LIBRARY_SUCCESS) {
            std::cout << "PLUGIN: We have detected our fake device! Doing "
                         "setup stuff!"
                      << std::endl;
            /// Create our device object
            osvr::pluginkit::registerObjectForDeletion(
				ctx, new AntvrHeadset(ctx, tracker));
			return OSVR_RETURN_SUCCESS;
        }
		else
		{
			std::cout << "PLUGIN: Load DLL error!" << std::endl;
			return OSVR_RETURN_FAILURE;
		}
        return OSVR_RETURN_SUCCESS;
    }

  private:
	  AntvrheadsetPtr tracker;
};
} // namespace

OSVR_PLUGIN(com_osvr_AntvrHeadset) {
    osvr::pluginkit::PluginContext context(ctx);
    /// Register a detection callback function object.
    context.registerHardwareDetectCallback(new HardwareDetection());

    return OSVR_RETURN_SUCCESS;
}
