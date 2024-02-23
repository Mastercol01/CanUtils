#include <stdint.h>
#include <Arduino.h>
#include <mcp2515.h>
#include "CanUtils.h"


namespace canUtils
{

uint32_t createCanMsgCanId(PRIORITY_LEVEL priorityLevel, ACTIVITY_CODE activityCode, MODULE_ADDRESS destinationAddress, MODULE_ADDRESS originAddress){
  uint32_t canId = 0;
  canId |= uint32_t(originAddress);
  canId |= uint32_t(destinationAddress) << 8;
  canId |= uint32_t(activityCode)       << 16;
  canId |= uint32_t(priorityLevel)      << 26;
  canId |= uint32_t(1) << 31;
  return canId;
}

PRIORITY_LEVEL getPriorityLevelFromCanMsgCanId(uint32_t canId){
  uint32_t bitmask = (uint32_t(0b111) << 26);
  uint32_t priorityLevel = (canId & bitmask) >> 26;
  return static_cast<PRIORITY_LEVEL>(priorityLevel);
}

ACTIVITY_CODE getActivityCodeFromCanMsgCanId(uint32_t canId){
  uint32_t bitmask = (uint32_t(0b11111111) << 16);
  uint32_t activityCode = (canId & bitmask) >> 16;
  return static_cast<ACTIVITY_CODE>(activityCode);
}

MODULE_ADDRESS getDestinationAddressFromCanMsgCanId(uint32_t canId){
  uint32_t bitmask = (uint32_t(0b11111111) << 8);
  uint32_t destinationAddress = (canId & bitmask) >> 8;
  return static_cast<MODULE_ADDRESS>(destinationAddress);
}

MODULE_ADDRESS getOriginAddressFromCanMsgCanId(uint32_t canId){
  uint32_t bitmask = uint32_t(0b11111111);
  uint32_t originAddress = (canId & bitmask);
  return static_cast<MODULE_ADDRESS>(originAddress);
}

void serialPrintCanMsg(struct can_frame canMsg){
  Serial.println("--------------");
  Serial.print("can_id: ");  Serial.println(canMsg.can_id);
  Serial.print("can_dlc: "); Serial.println(canMsg.can_dlc);
  Serial.print("data: ");
  for (int i=0; i<8; i++){
    Serial.print(canMsg.data[i]);
    Serial.print(",");
  }
  Serial.println();
  Serial.print("priorityLevel: ");      Serial.println(getPriorityLevelFromCanMsgCanId(canMsg.can_id));
  Serial.print("activityCode: ");       Serial.println(getActivityCodeFromCanMsgCanId(canMsg.can_id));
  Serial.print("destinationAddress: "); Serial.println(getDestinationAddressFromCanMsgCanId(canMsg.can_id));
  Serial.print("originAddress: ");      Serial.println(getOriginAddressFromCanMsgCanId(canMsg.can_id));
}

void visualizeCanNetwork(MCP2515& canNetwork, struct can_frame* p_canMsg,
                         PRIORITY_LEVEL priorityLevelAllowed      = PRIORITY_LEVEL_NONE,
                         ACTIVITY_CODE  activityCodeAllowed       = ACTIVITY_CODE_NONE,
                         MODULE_ADDRESS destinationAddressAllowed = MODULE_ADDRESS_NONE,
                         MODULE_ADDRESS originAddressAllowed      = MODULE_ADDRESS_NONE){

  if (canNetwork.readMessage(p_canMsg) == MCP2515::ERROR_OK){

    bool logicPrint = true;
    uint32_t canId = p_canMsg->can_id;

    if (priorityLevelAllowed != PRIORITY_LEVEL_NONE){
      if (priorityLevelAllowed != getPriorityLevelFromCanMsgCanId(canId)){
        logicPrint = false;
      }
    }
    if ((activityCodeAllowed != ACTIVITY_CODE_NONE) && logicPrint){
      if (activityCodeAllowed != getActivityCodeFromCanMsgCanId(canId)){
        logicPrint = false;
      }
    }
    if ((destinationAddressAllowed != MODULE_ADDRESS_NONE) && logicPrint){
      if (destinationAddressAllowed != getDestinationAddressFromCanMsgCanId(canId)){
        logicPrint = false;
      }
    }
    if ((originAddressAllowed != MODULE_ADDRESS_NONE) && logicPrint){
      if (originAddressAllowed != getOriginAddressFromCanMsgCanId(canId)){
        logicPrint = false;
      }
    }
    if (logicPrint) {serialPrintCanMsg(*p_canMsg);} 
  }
}

MCP2515::ERROR readCanMsg(MCP2515& canNetwork, struct can_frame* p_canMsg, 
                          MODULE_ADDRESS destinationAddressAllowed = MODULE_ADDRESS_NONE){
  MCP2515::ERROR readError = canNetwork.readMessage(p_canMsg);
  if (readError == MCP2515::ERROR_OK){
    if (destinationAddressAllowed != MODULE_ADDRESS_NONE){
      if (destinationAddressAllowed != getDestinationAddressFromCanMsgCanId(p_canMsg->can_id)){
        readError = MCP2515::ERROR_FAIL;
      }
    }
  }
  return readError;
}

void stdCanNetworkSetUp(MCP2515& canNetwork){
  // The battery BMS has a bitrate of 250 kbps according to the datasheet sent by the Chinese.
  // The MCP2515 arduino module, has  an 8MHz clock.
  canNetwork.reset();
  canNetwork.setBitrate(CAN_250KBPS, MCP_8MHZ); 
  canNetwork.setNormalMode();
}







}