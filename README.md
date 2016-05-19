# OSVR-ANTVR 
> Maintained at <https://github.com/OSVR/OSVR-ANTVR>
>
> For details, see <http://osvr.github.io>

This is a plugin for OSVR that provides access to the tracker data on ANTVR HMDs.

It is Windows-only, and requires the file "ANTVRHidApi.dll" to build.

To use ANTVRHidApi.dll, just put the file in folder OSVR-Core/bin/ (The same folder where osvr_server.exe lies).

And then build it and put the generated file "com_osvr_ANTVR.dll" in bin/osvr-plugins-0/

The last step, follow OSVR tutorial, run osvr_server.exe and use file "osvr_server_config.antvr.sample.json" as configure.


## Licenses
This plugin: Licensed under the Apache License, Version 2.0.

Note that since this builds on the ANTVR SDK, you are responsible for complying with the terms of that license.
