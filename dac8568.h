#ifndef __DAC8568_H__
#define __DAC8568_H__

#include "transfer_handler.h"

//SPI MODE 1

#define PREFIX_SIZE 4
#define CONTROL_SIZE 4
#define ADDRESS_SIZE 4
#define DATA_SIZE 16
#define FEATURE_SIZE 4

typedef struct DAC_MSG_OBJECT {
  unsigned feature : FEATURE_SIZE;
  unsigned data : DATA_SIZE;
  unsigned address : ADDRESS_SIZE;
  unsigned control : CONTROL_SIZE;
  unsigned prefix : PREFIX_SIZE;
} DAC_MSG_OBJECT;

typedef enum CHANNEL_SELECT{
  CH_A,
  CH_B,
  CH_C,
  CH_D,
  CH_E,
  CH_F,
  CH_G,
  CH_H,
  NO_MSG,
  BROADCAST
} CHANNEL_SELECT;

//Prefix should always be 0b0XXX
#define PREFIX_DONT_CARE 0
#define ADDRESS_DONT_CARE 0
#define CONTROL_DONT_CARE 0
#define DATA_DONT_CARE 0
#define FEATURE_DONT_CARE 0

typedef enum {
  CONTROL_WRITE_TO_INPUT_REGISTER,
  CONTROL_UPDATE_DAC_REGISTER,
  CONTROL_WRITE_TO_DAC_CH_AND_UPDATE_ALL_REG,
  CONTROL_WRITE_TO_DAC_CH_AND_UPDATE_SINGLE_REG,
  CONTROL_POWER_DOWN_COMM,
  CONTROL_WRITE_TO_CLEAR_CODE_REG,
  CONTROL_WRITE_TO_LDAC_REG,
  CONTROL_SOFTWARE_RESET,
} CONTROL_TYPE;

typedef enum {
  CONTROL_SETUP_STATIC_MODE = 8,
  CONTROL_SETUP_FLEX_MODE = 9
} CONTROL_SETUP_MODE;

typedef enum {
  FEATURE_CLEAR_TO_ZERO_SCALE,
  FEATURE_CLEAR_TO_MID_SCALE,
  FEATURE_CLEAR_TO_FULL_SCALE,
  FEATURE_IGNORE_CLR_PIN
} CLEAR_CODE_FEATURE;

typedef enum {
  FEATURE_POWER_DOWN_INT_REF_STATIC,
  FEATURE_POWER_UP_INT_REF_STATIC,
  FEATURE_POWER_UP_INT_REF_FLEX = 0,
  FEATURE_POWER_UP_INT_REF_ALWAYS_FLEX = 0,
  FEATURE_POWER_DOWN_INT_REF_FLEX = 0,
  FEATURE_SWITCH_FROM_FLEX_TO_STATIC = 0
} INTERNAL_REF_COMM_FEATURE;

typedef enum {
  LDAC_REG_A = 1,
  LDAC_REG_B = 2,
  LDAC_REG_C = 4,
  LDAC_REG_D = 8,
  LDAC_REG_E = 16,
  LDAC_REG_F = 32,
  LDAC_REG_G = 64,
  LDAC_REG_H = 128
} WRITE_TO_LDAC_CH;

typedef enum {
  POWER_DAC_A = 1,
  POWER_DAC_B = 2,
  POWER_DAC_C = 4,
  POWER_DAC_D = 8,
  POWER_DAC_E = 16,
  POWER_DAC_F = 32,
  POWER_DAC_G = 64,
  POWER_DAC_H = 128
} POWER_UP_DOWN_CH;

typedef enum {
  POWER_UP_DAC = 0,
  POWER_DOWN_DAC_1KO_TO_GND = 16,
  POWER_DOWN_DAC_100KO_TO_GND = 32,
  POWER_DOWN_DAC_HIZ_TO_GND = 48
} POWER_UP_DOWN_DAC;

typedef enum {
  DATA_POWER_DOWN_INT_REF_STATIC = 0,
  DATA_POWER_UP_INT_REF_STATIC = 0,
  DATA_POWER_UP_INT_REF_FLEX = 32768,
  DATA_POWER_UP_INT_REF_ALWAYS_FLEX = 40960,
  DATA_POWER_DOWN_INT_REF_FLEX = 49152,
  DATA_SWITCH_FROM_FLEX_TO_STATIC = 0
} INTERNAL_REF_COMM_DATA;

void dac8568_begin(void);
void dac8568_setChannel(CHANNEL_SELECT address_field, uint16_t val);

#endif
