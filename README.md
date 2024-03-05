# RC state publisher mod for Scout ROS packages
by E. Aaltonen 2023

This project includes additions and modifications necessary to publish RC data in Agilex Bunker and Scout Mini (https://github.com/westonrobot/ugv_sdk (license: BSD) - version v1.x). 


## Modified files & changes:

* ugv_sdk/src/bunker_base.cpp: added new case item to assign RCStateMessage to body.rc_state
* ugv_sdk/src/scout_base.cpp: added new case item to assign RCStateMessage to body.rc_state
* ugv_sdk/include/ugv_sdk/proto/agx_protocol_v2.h: corrected the incorrect datatypes of in RcStateMessage (uint8 to int8) (stick values -100...100)
* ugv_sdk/include/ugv_sdk/bunker/bunker_types.hpp: added member RCState in struct BunkerState
* ugv_sdk/include/ugv_sdk/scout/scout_types.hpp: added member RCState in struct ScoutState

RC data is published in topic /scout_rc_status:


## Versions:

These modifications are no longer necessary with the latest version of the ugv_sdk package, making this project obsolete.

