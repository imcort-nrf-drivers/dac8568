#include "dac8568.h"

DAC_MSG_OBJECT msg_obj;

void dac8568_sendCommand(uint32_t cmd)
{
    
    uint8_t buf[4];
    buf[0] = cmd >> 24;
    buf[1] = cmd >> 16;
    buf[2] = cmd >> 8;
    buf[3] = cmd & 0xff;
    NRF_LOG_HEXDUMP_INFO(buf, 4);
    digitalWrite(DAC_SYNC, LOW);
    spi_transfer(buf, 4, NULL, 0);
    digitalWrite(DAC_SYNC, HIGH);
}

uint32_t DAC8568_Reset() {
  msg_obj.prefix = PREFIX_DONT_CARE;
  msg_obj.control = CONTROL_SOFTWARE_RESET;
  msg_obj.address = ADDRESS_DONT_CARE;
  msg_obj.data = DATA_DONT_CARE;
  msg_obj.feature = FEATURE_DONT_CARE;

  return *(uint32_t*)& msg_obj;
}

uint32_t DAC8568_Setup(CONTROL_SETUP_MODE control_field, INTERNAL_REF_COMM_DATA data_field, INTERNAL_REF_COMM_FEATURE feature_field) {
  //Prefix always 0b0XXX
  msg_obj.prefix = PREFIX_DONT_CARE;

  msg_obj.control = control_field;
  
  //Address 0bXXXX for Setup
  msg_obj.address = ADDRESS_DONT_CARE;

  msg_obj.data = data_field;
  msg_obj.feature = feature_field;

  return *(uint32_t*)& msg_obj;
}

uint32_t DAC8568_Power_Up_Down(POWER_UP_DOWN_DAC data_field_power, uint8_t channel_field) {
  //Prefix always 0b0XXX
  msg_obj.prefix = PREFIX_DONT_CARE;

  msg_obj.control = CONTROL_POWER_DOWN_COMM;

  //Address 0bXXXX for setup.  Power Up/Down Address controlled by Data and Feature bits.
  msg_obj.address = ADDRESS_DONT_CARE;

  //OR the data field to combine the bits to select power on or off.
  msg_obj.data = data_field_power | (channel_field >> 4);
  msg_obj.feature = channel_field;

  return *(uint32_t*)& msg_obj;
}

uint32_t DAC8568_Write_Input_Reg_And_Update_Single(CHANNEL_SELECT address_field, uint16_t data_field) {
  msg_obj.prefix = PREFIX_DONT_CARE;
  msg_obj.control = CONTROL_WRITE_TO_DAC_CH_AND_UPDATE_SINGLE_REG;
  msg_obj.address = address_field;
  msg_obj.data = data_field;
  msg_obj.feature = FEATURE_DONT_CARE;

  return *(uint32_t*)& msg_obj;
}

uint32_t DAC8568_Write_Input_Reg_And_Update_All(CHANNEL_SELECT address_field, uint16_t data_field) {
  msg_obj.prefix = PREFIX_DONT_CARE;
  msg_obj.control = CONTROL_WRITE_TO_DAC_CH_AND_UPDATE_ALL_REG;
  msg_obj.address = address_field;
  msg_obj.data = data_field;
  msg_obj.feature = FEATURE_DONT_CARE;

  return *(uint32_t*)& msg_obj;
}

uint32_t DAC8568_Load_DAC(uint8_t channel_field) {
  msg_obj.prefix = PREFIX_DONT_CARE;
  msg_obj.control = CONTROL_WRITE_TO_LDAC_REG;
  msg_obj.address = ADDRESS_DONT_CARE;
  msg_obj.data = channel_field >> 4;
  msg_obj.feature = channel_field;

  return *(uint32_t*)& msg_obj;
}

uint32_t DAC8568_Write_Input_Reg(CHANNEL_SELECT address_field, uint16_t data_field) {
  //Prefix always 0b0XXX
  msg_obj.prefix = PREFIX_DONT_CARE;

  msg_obj.control = CONTROL_WRITE_TO_INPUT_REGISTER;

  msg_obj.address = address_field;

  msg_obj.data = data_field;
  msg_obj.feature = FEATURE_DONT_CARE;

  return *(uint32_t*)& msg_obj;
}

uint32_t DAC8568_Update_Dac_Reg(CHANNEL_SELECT address_field, uint16_t data_field) {
  //Prefix always 0b0XXX
  msg_obj.prefix = PREFIX_DONT_CARE;

  msg_obj.control = CONTROL_UPDATE_DAC_REGISTER;

  msg_obj.address = address_field;

  msg_obj.data = data_field;
  msg_obj.feature = FEATURE_DONT_CARE;

  return *(uint32_t*)& msg_obj;
}

void dac8568_begin(void)
{
    pinMode(DAC_SYNC, OUTPUT);
    spi_init();
    
    dac8568_sendCommand(DAC8568_Reset());
    dac8568_sendCommand(DAC8568_Setup(CONTROL_SETUP_STATIC_MODE, DATA_POWER_UP_INT_REF_STATIC, FEATURE_POWER_UP_INT_REF_STATIC));
    dac8568_sendCommand(DAC8568_Power_Up_Down(POWER_UP_DAC, 0xff));
}

void dac8568_setChannel(CHANNEL_SELECT address_field, uint16_t val)
{
    dac8568_sendCommand(DAC8568_Write_Input_Reg_And_Update_Single(address_field, val));
}
