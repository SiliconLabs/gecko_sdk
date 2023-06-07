{
  "featureLevel": 89,
  "creator": "zap",
  "keyValuePairs": [
    {
      "key": "commandDiscovery",
      "value": "1"
    },
    {
      "key": "defaultResponsePolicy",
      "value": "always"
    },
    {
      "key": "manufacturerCodes",
      "value": "0x1002"
    }
  ],
  "package": [
    {
      "pathRelativity": "relativeToZap",
      "path": "../../../../../framework/gen-template/gen-templates.json",
      "type": "gen-templates-json",
      "category": "zigbee",
      "version": "zigbee-v0"
    },
    {
      "pathRelativity": "relativeToZap",
      "path": "../../../../../../../../app/zcl/zcl-zap.json",
      "type": "zcl-properties",
      "category": "zigbee",
      "version": 1,
      "description": "Zigbee Silabs ZCL data"
    }
  ],
  "endpointTypes": [
    {
      "name": "GreenPower",
      "deviceTypeName": "GP-combo-basic",
      "deviceTypeCode": 102,
      "deviceTypeProfileId": 41440,
      "clusters": [
        {
          "name": "Green Power",
          "code": 33,
          "mfgCode": null,
          "define": "GREEN_POWER_CLUSTER",
          "side": "client",
          "enabled": 1,
          "commands": [
            {
              "name": "GpNotification",
              "code": 0,
              "mfgCode": null,
              "source": "client",
              "incoming": 1,
              "outgoing": 1
            },
            {
              "name": "GpPairingSearch",
              "code": 1,
              "mfgCode": null,
              "source": "client",
              "incoming": 0,
              "outgoing": 1
            },
            {
              "name": "GpTunnelingStop",
              "code": 3,
              "mfgCode": null,
              "source": "client",
              "incoming": 0,
              "outgoing": 0
            },
            {
              "name": "GpCommissioningNotification",
              "code": 4,
              "mfgCode": null,
              "source": "client",
              "incoming": 1,
              "outgoing": 1
            },
            {
              "name": "GpSinkCommissioningMode",
              "code": 5,
              "mfgCode": null,
              "source": "client",
              "incoming": 1,
              "outgoing": 1
            },
            {
              "name": "GpTranslationTableUpdate",
              "code": 7,
              "mfgCode": null,
              "source": "client",
              "incoming": 1,
              "outgoing": 1
            },
            {
              "name": "GpTranslationTableRequest",
              "code": 8,
              "mfgCode": null,
              "source": "client",
              "incoming": 1,
              "outgoing": 1
            },
            {
              "name": "GpPairingConfiguration",
              "code": 9,
              "mfgCode": null,
              "source": "client",
              "incoming": 1,
              "outgoing": 1
            },
            {
              "name": "GpSinkTableRequest",
              "code": 10,
              "mfgCode": null,
              "source": "client",
              "incoming": 1,
              "outgoing": 1
            },
            {
              "name": "GpProxyTableResponse",
              "code": 11,
              "mfgCode": null,
              "source": "client",
              "incoming": 0,
              "outgoing": 1
            }
          ],
          "attributes": [
            {
              "name": "gpp max proxy table entries",
              "code": 16,
              "mfgCode": null,
              "side": "client",
              "type": "int8u",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "0x14",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            },
            {
              "name": "proxy table",
              "code": 17,
              "mfgCode": null,
              "side": "client",
              "type": "long_octet_string",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            },
            {
              "name": "gpp functionality",
              "code": 22,
              "mfgCode": null,
              "side": "client",
              "type": "bitmap24",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "0x09AC2F",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            },
            {
              "name": "gpp active functionality",
              "code": 23,
              "mfgCode": null,
              "side": "client",
              "type": "bitmap24",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "0xFFFFFF",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            },
            {
              "name": "gp link key",
              "code": 34,
              "mfgCode": null,
              "side": "client",
              "type": "security_key",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "0x5a6967426565416c6c69616e63653039",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            },
            {
              "name": "cluster revision",
              "code": 65533,
              "mfgCode": null,
              "side": "client",
              "type": "int16u",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "0x0001",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            }
          ]
        },
        {
          "name": "Green Power",
          "code": 33,
          "mfgCode": null,
          "define": "GREEN_POWER_CLUSTER",
          "side": "server",
          "enabled": 1,
          "commands": [
            {
              "name": "GpNotificationResponse",
              "code": 0,
              "mfgCode": null,
              "source": "server",
              "incoming": 1,
              "outgoing": 1
            },
            {
              "name": "GpPairing",
              "code": 1,
              "mfgCode": null,
              "source": "server",
              "incoming": 1,
              "outgoing": 1
            },
            {
              "name": "GpProxyCommissioningMode",
              "code": 2,
              "mfgCode": null,
              "source": "server",
              "incoming": 1,
              "outgoing": 1
            },
            {
              "name": "GpResponse",
              "code": 6,
              "mfgCode": null,
              "source": "server",
              "incoming": 1,
              "outgoing": 1
            },
            {
              "name": "GpTranslationTableResponse",
              "code": 8,
              "mfgCode": null,
              "source": "server",
              "incoming": 0,
              "outgoing": 0
            },
            {
              "name": "GpSinkTableResponse",
              "code": 10,
              "mfgCode": null,
              "source": "server",
              "incoming": 1,
              "outgoing": 1
            },
            {
              "name": "GpProxyTableRequest",
              "code": 11,
              "mfgCode": null,
              "source": "server",
              "incoming": 1,
              "outgoing": 1
            }
          ],
          "attributes": [
            {
              "name": "gps max sink table entries",
              "code": 0,
              "mfgCode": null,
              "side": "server",
              "type": "int8u",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "0x05",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            },
            {
              "name": "sink table",
              "code": 1,
              "mfgCode": null,
              "side": "server",
              "type": "long_octet_string",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            },
            {
              "name": "gps communication mode",
              "code": 2,
              "mfgCode": null,
              "side": "server",
              "type": "bitmap8",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "0x01",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            },
            {
              "name": "gps commissioning exit mode",
              "code": 3,
              "mfgCode": null,
              "side": "server",
              "type": "bitmap8",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "0x02",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            },
            {
              "name": "gps commissioning window",
              "code": 4,
              "mfgCode": null,
              "side": "server",
              "type": "int16u",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "0x00FF",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            },
            {
              "name": "gps security level",
              "code": 5,
              "mfgCode": null,
              "side": "server",
              "type": "bitmap8",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "0x06",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            },
            {
              "name": "gps functionality",
              "code": 6,
              "mfgCode": null,
              "side": "server",
              "type": "bitmap24",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "0x0FAE2F",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            },
            {
              "name": "gps active functionality",
              "code": 7,
              "mfgCode": null,
              "side": "server",
              "type": "bitmap24",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "0xFFFFFF",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            },
            {
              "name": "gp shared security key type",
              "code": 32,
              "mfgCode": null,
              "side": "server",
              "type": "bitmap8",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "0x03",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            },
            {
              "name": "gp shared security key",
              "code": 33,
              "mfgCode": null,
              "side": "server",
              "type": "security_key",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            },
            {
              "name": "gp link key",
              "code": 34,
              "mfgCode": null,
              "side": "server",
              "type": "security_key",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "0x5a6967426565416c6c69616e63653039",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            },
            {
              "name": "cluster revision",
              "code": 65533,
              "mfgCode": null,
              "side": "server",
              "type": "int16u",
              "included": 1,
              "storageOption": "RAM",
              "singleton": 0,
              "bounded": 0,
              "defaultValue": "0x0002",
              "reportable": 0,
              "minInterval": 1,
              "maxInterval": 65534,
              "reportableChange": 0
            }
          ]
        }
      ]
    }
  ],
  "endpoints": [
    {
      "endpointTypeName": "GreenPower",
      "endpointTypeIndex": 0,
      "profileId": "0xA1E0",
      "endpointId": 242,
      "networkId": 0,
      "endpointVersion": 1,
      "deviceIdentifier": 102
    }
  ],
  "log": []
}
