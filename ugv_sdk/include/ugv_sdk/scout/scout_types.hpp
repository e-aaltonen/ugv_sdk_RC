/*
 * scout_state.hpp
 *
 * Created on: Jun 11, 2019 08:48
 * Description:
 *
 * Copyright (c) 2019 Ruixiang Du (rdu)
 */
 
 /* Modifications by E. Aaltonen 2024
 * for publishing RC status messages
 * changes indicated: // EA
 */

#ifndef SCOUT_STATE_HPP
#define SCOUT_STATE_HPP

#include <cstdint>
#include <iostream>

namespace westonrobot {
struct ScoutState {
  enum MotorID {
    FRONT_RIGHT = 0,
    FRONT_LEFT = 1,
    REAR_LEFT = 2,
    REAR_RIGHT = 3
  };

  struct MotorState {
    double current = 0;  // in A
    double rpm = 0;
    double temperature = 0;
  };

  struct LightState {
    uint8_t mode = 0;
    uint8_t custom_value = 0;
  };

  struct RCState {
    uint8_t sws = 0;
    int8_t var_a = 0;
  };    // EA
  
  // base state
  uint8_t base_state = 0;
  uint8_t control_mode = 0;
  uint16_t fault_code = 0;
  double battery_voltage = 0.0;

  // motor state
  static constexpr uint8_t motor_num = 4;
  MotorState motor_states[motor_num];

  // light state
  bool light_control_enabled = false;
  LightState front_light_state;
  LightState rear_light_state;

  // motion state
  double linear_velocity = 0;
  double angular_velocity = 0;
  
  // RC state    // EA
  RCState rc_state;
};

struct ScoutMotionCmd {
  enum class FaultClearFlag {
    NO_FAULT = 0x00,
    BAT_UNDER_VOL = 0x01,
    BAT_OVER_VOL = 0x02,
    MOTOR1_COMM = 0x03,
    MOTOR2_COMM = 0x04,
    MOTOR3_COMM = 0x05,
    MOTOR4_COMM = 0x06,
    MOTOR_DRV_OVERHEAT = 0x07,
    MOTOR_OVERCURRENT = 0x08
  };

  ScoutMotionCmd(int8_t linear = 0, int8_t angular = 0,
                 FaultClearFlag fault_clr_flag = FaultClearFlag::NO_FAULT)
      : linear_velocity(linear),
        angular_velocity(angular),
        fault_clear_flag(fault_clr_flag) {}

  int8_t linear_velocity;
  int8_t angular_velocity;
  FaultClearFlag fault_clear_flag;
};

struct ScoutCmdLimits {
  static constexpr double max_linear_velocity = 1.5;       // 1.5 m/s
  static constexpr double min_linear_velocity = -1.5;      // -1.5 m/s
  static constexpr double max_angular_velocity = 0.5235;   // 0.5235 rad/s
  static constexpr double min_angular_velocity = -0.5235;  // -0.5235 rad/s
};

struct ScoutMiniCmdLimits {
  static constexpr double max_linear_velocity = 3.0;       // 3.0 m/s
  static constexpr double min_linear_velocity = -3.0;      // -3.0 m/s
  static constexpr double max_angular_velocity = 2.5235;   // 2.5235 rad/s
  static constexpr double min_angular_velocity = -2.5235;  // -2.5235 rad/s
};

struct ScoutLightCmd {
  enum class LightMode {
    CONST_OFF = 0x00,
    CONST_ON = 0x01,
    BREATH = 0x02,
    CUSTOM = 0x03
  };

  ScoutLightCmd() = default;
  ScoutLightCmd(LightMode f_mode, uint8_t f_value, LightMode r_mode,
                uint8_t r_value)
      : front_mode(f_mode),
        front_custom_value(f_value),
        rear_mode(r_mode),
        rear_custom_value(r_value) {}

  LightMode front_mode;
  uint8_t front_custom_value;
  LightMode rear_mode;
  uint8_t rear_custom_value;
};
}  // namespace westonrobot

#endif /* SCOUT_STATE_HPP */
