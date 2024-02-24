#ifndef CanUtils_h
#define CanUtils_h
#include <stdint.h>
#include <Arduino.h>
#include <mcp2515.h>


namespace canUtils
{

enum PRIORITY_LEVEL 
{
  ULTRA_LOW   = 7,
  LOW_        = 6,
  MEDIUM_LOW  = 5,
  MEDIUM      = 4, 
  MEDIUM_HIGH = 3,
  HIGH_       = 2,
  ULTRA_HIGH  = 1,
  PRIORITY_LEVEL_NONE = 0
};

enum MODULE_ADDRESS 
{
  MODULE_ADDRESS_NONE = 0,
  SLOT1 = 1,
  SLOT2 = 2,
  SLOT3 = 3,
  SLOT4 = 4,
  SLOT5 = 5,
  SLOT6 = 6,
  SLOT7 = 7,
  SLOT8 = 8,
  EIGHT_CHANNEL_RELAY = 9,
  CONTROL_CENTER = 10
};

enum ACTIVITY_CODE 
{
  ACTIVITY_CODE_NONE = 0,
  net2rpy_STATES_INFO_OF_EIGHT_CHANNEL_RELAY_MODULE = 1,
  rpy2net_SET_STATE_OF_EIGHT_CHANNEL_RELAY_MODULE   = 2,
  rpy2net_SET_STATES_OF_EIGHT_CHANNEL_RELAY_MODULE  = 3,
  rpy2net_FLIP_STATE_OF_EIGHT_CHANNEL_RELAY_MODULE  = 4,
  rpy2net_FLIP_STATES_OF_EIGHT_CHANNEL_RELAY_MODULE = 5,
0
};

uint32_t createCanMsgCanId(PRIORITY_LEVEL priorityLevel, ACTIVITY_CODE activityCode, MODULE_ADDRESS destinationAddress, MODULE_ADDRESS originAddress);
PRIORITY_LEVEL getPriorityLevelFromCanMsgCanId(uint32_t canId);
ACTIVITY_CODE getActivityCodeFromCanMsgCanId(uint32_t canId);
MODULE_ADDRESS getDestinationAddressFromCanMsgCanId(uint32_t canId);
MODULE_ADDRESS getOriginAddressFromCanMsgCanId(uint32_t canId);

void serialPrintCanMsg(struct can_frame canMsg);
void visualizeCanNetwork(MCP2515& canNetwork, struct can_frame* p_canMsg,
                         PRIORITY_LEVEL priorityLevelAllowed      = PRIORITY_LEVEL_NONE,
                         ACTIVITY_CODE  activityCodeAllowed       = ACTIVITY_CODE_NONE,
                         MODULE_ADDRESS destinationAddressAllowed = MODULE_ADDRESS_NONE,
                         MODULE_ADDRESS originAddressAllowed      = MODULE_ADDRESS_NONE);

MCP2515::ERROR readCanMsg(MCP2515& canNetwork, struct can_frame* p_canMsg, 
                          MODULE_ADDRESS destinationAddressAllowed = MODULE_ADDRESS_NONE,
                          MODULE_ADDRESS originAddressAllowed      = MODULE_ADDRESS_NONE);
void stdCanNetworkSetUp(MCP2515& canNetwork);


}

#endif