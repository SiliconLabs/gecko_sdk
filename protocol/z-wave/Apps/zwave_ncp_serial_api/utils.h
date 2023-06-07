/**
 * @file
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef APPS_SERIALAPI_UTILS_H_
#define APPS_SERIALAPI_UTILS_H_

#include <stdint.h>
#include <ZW_application_transport_interface.h>
#include <app.h>

uint8_t QueueProtocolCommand(uint8_t *pCommand);

uint8_t GetCommandResponse(SZwaveCommandStatusPackage *pCmdStatus, EZwaveCommandStatusType cmdType);

uint8_t IsPrimaryController(void);

uint8_t GetControllerCapabilities(void);

void GetNodeInfo(uint16_t NodeId, t_ExtNodeInfo* pNodeInfo);

void Get_included_nodes(uint8_t* node_id_list);
void Get_included_lr_nodes(uint8_t* node_id_list);

void TriggerNotification(EApplicationEvent event);

void GetLongRangeChannel(uint8_t * channel_n, uint8_t *auto_channel_config);
bool    SetLongRangeChannel(uint8_t channel);

void SetLongRangeVirtualNodes(uint8_t bitmask);

uint8_t GetPTIConfig(void);

void SetTaskHandle(TaskHandle_t new_task_handle);
TaskHandle_t GetTaskHandle(void);

#endif /* APPS_SERIALAPI_UTILS_H_ */
