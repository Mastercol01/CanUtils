#include <mcp2515.h>
#include <CanUtils.h>

MCP2515 network0(9);
MCP2515 network1(10);

struct can_frame canMsg;
struct can_frame canMsg0;
struct can_frame canMsg1;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  
  // ---- CAN MODULES CONFIG ----
  canUtils::stdCanNetworkSetUp(network0);
  canUtils::stdCanNetworkSetUp(network1);

  canMsg0.can_dlc = 8;
  canMsg1.can_dlc = 8;

  for (int i=0; i<8; i++){
    canMsg0.data[i]=0;
    canMsg1.data[i]=1;
  }

  canMsg0.can_id = 
  canUtils::createCanMsgCanId(canUtils::ULTRA_LOW, 
                              canUtils::net2rpy_STATES_INFO_OF_EIGHT_CHANNEL_RELAY_MODULE,
                              canUtils::SLOT2, 
                              canUtils::SLOT1);

  canMsg1.can_id = 
  canUtils::createCanMsgCanId(canUtils::ULTRA_HIGH, 
                              canUtils::net2rpy_STATES_INFO_OF_EIGHT_CHANNEL_RELAY_MODULE,
                              canUtils::SLOT1, 
                              canUtils::SLOT2);

}

void loop() {
  // put your main code here, to run repeatedly:

  network0.sendMessage(&canMsg0);
  network1.sendMessage(&canMsg1);

  if(canUtils::readCanMsg(network0, &canMsg, canUtils::SLOT1) == MCP2515::ERROR_OK){canUtils::serialPrintCanMsg(canMsg);}
  //if(canUtils::readCanMsg(network0, &canMsg, canUtils::SLOT2) == MCP2515::ERROR_OK){canUtils::serialPrintCanMsg(canMsg);}
    


}
