#include <CanUtils.h>

uint32_t canId[7];
canUtils::PRIORITY_LEVEL priorityLevel;
canUtils::ACTIVITY_CODE  activityCode;
canUtils::MODULE_ADDRESS destinationAddress;
canUtils::MODULE_ADDRESS originAddress;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  canId[0] = canUtils::createCanMsgCanId(canUtils::ULTRA_LOW,   canUtils::STATES_OF_EIGHT_CHANNEL_RELAY_MODULE, canUtils::EIGHT_CHANNEL_RELAY, canUtils::SLOT1);
  canId[1] = canUtils::createCanMsgCanId(canUtils::LOW_,        canUtils::STATES_OF_EIGHT_CHANNEL_RELAY_MODULE, canUtils::CONTROL_CENTER,      canUtils::SLOT2);
  canId[2] = canUtils::createCanMsgCanId(canUtils::MEDIUM_LOW,  canUtils::STATES_OF_EIGHT_CHANNEL_RELAY_MODULE, canUtils::CONTROL_CENTER,      canUtils::SLOT3);
  canId[3] = canUtils::createCanMsgCanId(canUtils::MEDIUM,      canUtils::STATES_OF_EIGHT_CHANNEL_RELAY_MODULE, canUtils::CONTROL_CENTER,      canUtils::SLOT4);
  canId[4] = canUtils::createCanMsgCanId(canUtils::MEDIUM_HIGH, canUtils::STATES_OF_EIGHT_CHANNEL_RELAY_MODULE, canUtils::CONTROL_CENTER,      canUtils::SLOT5);
  canId[5] = canUtils::createCanMsgCanId(canUtils::HIGH_,       canUtils::STATES_OF_EIGHT_CHANNEL_RELAY_MODULE, canUtils::SLOT6,               canUtils::EIGHT_CHANNEL_RELAY);
  canId[6] = canUtils::createCanMsgCanId(canUtils::ULTRA_HIGH,  canUtils::STATES_OF_EIGHT_CHANNEL_RELAY_MODULE, canUtils::SLOT7,               canUtils::CONTROL_CENTER);

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<7; i++){
  priorityLevel      = canUtils::getPriorityLevelFromCanMsgCanId(canId[i]);
  activityCode       = canUtils::getActivityCodeFromCanMsgCanId(canId[i]);
  destinationAddress = canUtils::getDestinationAddressFromCanMsgCanId(canId[i]);
  originAddress      = canUtils::getOriginAddressFromCanMsgCanId(canId[i]);

  Serial.println("-------");
  Serial.print("canId: "); Serial.println(canId[i]);
  Serial.print("priorityLevel: "); Serial.println(priorityLevel);
  Serial.print("activityCode: "); Serial.println(activityCode);
  Serial.print("destinationAddress: "); Serial.println(destinationAddress);
  Serial.print("originAddress: "); Serial.println(originAddress);
  }
}

