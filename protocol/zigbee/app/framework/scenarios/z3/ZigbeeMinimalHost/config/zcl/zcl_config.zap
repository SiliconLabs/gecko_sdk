{
  "fileFormat": 2,
  "featureLevel": 99,
  "creator": "zap",
  "keyValuePairs": [
    {
      "key": "commandDiscovery",
      "value": "1"
    },
    {
      "key": "defaultResponsePolicy",
      "value": "conditional"
    },
    {
      "key": "manufacturerCodes",
      "value": "0x1049"
    }
  ],
  "package": [
    {
      "pathRelativity": "relativeToZap",
      "path": "../../../../../../../../../app/zcl/zcl-zap.json",
      "type": "zcl-properties",
      "category": "zigbee",
      "version": 1,
      "description": "Zigbee Silabs ZCL data"
    },
    {
      "pathRelativity": "relativeToZap",
      "path": "../../../../../gen-template/gen-templates.json",
      "type": "gen-templates-json",
      "category": "zigbee",
      "version": "zigbee-v0"
    }
  ],
  "endpointTypes": [
    {
      "id": 1,
      "name": "Primary",
      "deviceTypeRef": {
        "code": 65535,
        "profileId": 65535,
        "label": "Custom ZCL Device Type",
        "name": "Custom ZCL Device Type"
      },
      "deviceTypes": [
        {
          "code": 65535,
          "profileId": 65535,
          "label": "Custom ZCL Device Type",
          "name": "Custom ZCL Device Type"
        }
      ],
      "deviceVersions": [
        1
      ],
      "deviceIdentifiers": [
        65535
      ],
      "deviceTypeName": "Custom ZCL Device Type",
      "deviceTypeCode": 65535,
      "deviceTypeProfileId": 65535,
      "clusters": []
    }
  ],
  "endpoints": [
    {
      "endpointTypeName": "Primary",
      "endpointTypeIndex": 0,
      "profileId": 65535,
      "endpointId": 1,
      "networkId": 0
    }
  ]
}