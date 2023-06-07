#include "af-support-host.h"
#include "command-prototypes.h"

EmberAfStatus sli_zigbee_af_support_read_attribute(EmberAfAttributeSearchRecord *attRecord,
                                                   EmberAfAttributeType *dataType,
                                                   uint8_t *dataPtr,
                                                   uint16_t readLength)
{
  // call ezsp command to read attribute
  return ezspReadAttribute(attRecord->endpoint, attRecord->clusterId, attRecord->attributeId,
                           attRecord->clusterMask, attRecord->manufacturerCode, dataType, (uint8_t*)(&readLength), dataPtr);
}

EmberAfStatus sli_zigbee_af_support_write_attribute(EmberAfAttributeSearchRecord *attRecord,
                                                    EmberAfAttributeType dataType,
                                                    uint8_t *dataPtr,
                                                    bool overrideReadOnlyAndDataType,
                                                    bool justTest)
{
  uint8_t dataLength = 0;
  if (emberAfIsStringAttributeType(dataType)) {
    dataLength = emberAfStringLength(dataPtr);
  } else if (emberAfIsLongStringAttributeType(dataType)) {
    dataLength = emberAfLongStringLength(dataPtr);
  } else {
    dataLength = emberAfGetDataSize(dataType);
  }
  return ezspWriteAttribute(attRecord->endpoint, attRecord->clusterId, attRecord->attributeId,
                            attRecord->clusterMask, attRecord->manufacturerCode, overrideReadOnlyAndDataType, justTest, dataType, dataLength, dataPtr);
}
