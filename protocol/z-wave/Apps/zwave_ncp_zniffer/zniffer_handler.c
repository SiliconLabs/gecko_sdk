#include "zniffer_handler.h"

#include <stdbool.h>

#include <string.h>
#include "SizeOf.h"
#include "Assert.h"
//#define DEBUGPRINT
#include "DebugPrint.h"
#include "DebugPrintConfig.h"
#include <zpal_watchdog.h>
#include <zpal_misc.h>
#include <zpal_radio.h>

#include "comm_interface.h"
#include "commands.h"

#define BUF_SIZE (32)

uint8_t compl_workbuf[BUF_SIZE];

enum
{
  stateIdle,
  stateFrameParse,
};

typedef struct
{
  zpal_radio_region_t freq_no;
  uint8_t channels;
  char* description;
} frequency_descriptor_t;

#define MAX_NO_OF_FREQ_SUPPORTED 13

frequency_descriptor_t SUPPORTED_FREQ_LIST[MAX_NO_OF_FREQ_SUPPORTED] =
{
  { REGION_EU,               2, "EU" },
  { REGION_US,               2, "US" },
  { REGION_ANZ,              2, "ANZ" },
  { REGION_HK,               2, "HK" },
  { REGION_IN,               2, "IN" },
  { REGION_IL,               2, "IL" },
  { REGION_RU,               2, "RU" },
  { REGION_CN,               2, "CN" },
  { REGION_US_LR,            4, "US_LR" },
  { REGION_US_LR_BACKUP,     4, "US_LR_BACKUP" },
  { REGION_JP,               3, "JP" },
  { REGION_KR,               3, "KR" },
  { REGION_US_LR_END_DEVICE, 1, "US_LR_END_DEVICE" },
};

static uint8_t state = stateIdle;
static bool stopSniffer = true;

void Respond(uint8_t cmd, uint8_t const *pData, uint8_t len)
{
  comm_interface_transmit_frame(cmd, CMD_FRAME, pData, len, NULL);

  //reset the watchdog
  zpal_feed_watchdog();
}

void DoRespond(void)
{
  Respond(serial_frame->cmd, NULL, 0);
}

void DoRespond_workbuf(uint8_t cnt)
{
  Respond(serial_frame->cmd, compl_workbuf, cnt);
}

uint8_t GetRadioSpeed(zpal_radio_speed_t speed)
{
  switch(speed)
  {
    case ZPAL_RADIO_SPEED_9600:
      return 0;
    case ZPAL_RADIO_SPEED_40K:
      return 1;
    case ZPAL_RADIO_SPEED_100K:
      return 2;
    case ZPAL_RADIO_SPEED_100KLR:
      return 3;
    default:
      return 0;
  }
}

uint8_t GetRadioChannel(zpal_radio_rx_parameters_t * pRxParameters)
{
  uint8_t region = zpal_radio_get_region();
  switch(region)
  {
    case REGION_EU:
    case REGION_US:
    case REGION_ANZ:
    case REGION_HK:
    case REGION_IN:
    case REGION_IL:
    case REGION_RU:
    case REGION_CN:
      if (ZPAL_RADIO_SPEED_9600 == pRxParameters->speed || ZPAL_RADIO_SPEED_40K == pRxParameters->speed)
      {
        return 1;
      }
      return 0;

    case REGION_US_LR:
    case REGION_US_LR_BACKUP:
    case REGION_US_LR_END_DEVICE:
      if (ZPAL_RADIO_SPEED_9600 == pRxParameters->speed || ZPAL_RADIO_SPEED_40K == pRxParameters->speed)
      {
        return 1;
      }
      return pRxParameters->channel_id;

    case REGION_JP:
    case REGION_KR:
      return pRxParameters->channel_id;

    default:
      return 0;
  }
}

uint8_t GetBeamSpeed(void) {
  uint8_t region = zpal_radio_get_region();
  switch(region)
  {
    case REGION_EU:
    case REGION_US:
    case REGION_ANZ:
    case REGION_HK:
    case REGION_IN:
    case REGION_IL:
    case REGION_RU:
    case REGION_CN:
        return GetRadioSpeed(ZPAL_RADIO_SPEED_40K);

    case REGION_US_LR:
    case REGION_US_LR_BACKUP:
    case REGION_US_LR_END_DEVICE:
        return GetRadioSpeed(ZPAL_RADIO_SPEED_100KLR);
    case REGION_JP:
    case REGION_KR:
        return GetRadioSpeed(ZPAL_RADIO_SPEED_100K);

    default:
      return 0;
  }
}

bool handling_beam = false;
uint16_t counter = 0;

tx_beam_start_frame_t beam_start_frame;
tx_beam_stop_frame_t beam_stop_frame;
tx_data_frame_t frame;

void beamReceiveHandler(uint16_t beamNodeId, uint16_t homeId, uint8_t channel, uint8_t rssi)
{
  if (!stopSniffer)
  {
    ++counter;
    if (!handling_beam)
    {
      handling_beam = true;
      beam_start_frame.sof = '!';
      beam_start_frame.type = BEAM_START;
      beam_start_frame.timestamp1 = 0;
      beam_start_frame.timestamp2 = 0;
      beam_start_frame.ch_speed = (channel << 5) | GetBeamSpeed();
      beam_start_frame.freq_no = zpal_radio_get_region();
      beam_start_frame.rssi = rssi >> 2; // TODO
      uint8_t a[4] = {0x55, 0x00, 0x01, 0x00};
      a[1] = beamNodeId;
      a[3] = homeId;
      memcpy(beam_start_frame.payload, a, 4);
      comm_interface_transmit_frame(BEAM_START, BEAM_FRAME, (uint8_t *)&beam_start_frame, 0, NULL);
    }
  }
}

void parseFrame(zpal_radio_rx_parameters_t * pRxParameters, zpal_radio_receive_frame_t * pFrame, uint8_t len)
{
  if (handling_beam)
  {
    handling_beam = false;
    beam_stop_frame.sof = '!';
    beam_stop_frame.type = BEAM_STOP;
    beam_stop_frame.timestamp1 = 0;
    beam_stop_frame.timestamp2 = 0;
    beam_stop_frame.rssi = ((uint8_t)pRxParameters->rssi) >> 2; // TODO
    beam_stop_frame.counter = counter;
    comm_interface_transmit_frame(BEAM_STOP, BEAM_FRAME, (uint8_t *)&beam_stop_frame, 0, NULL);
    comm_interface_wait_transmit_done();
  }
  counter = 0;
  frame.sof = '!';
  frame.type = 1;
  frame.timestamp1 = 0;
  frame.timestamp2 = 0;
  frame.ch_speed = (GetRadioChannel(pRxParameters) << 5) | GetRadioSpeed(pRxParameters->speed);
  frame.freq_no = zpal_radio_get_region();
  frame.rssi = ((uint8_t)pRxParameters->rssi) >> 2; // TODO
  frame.sodm = '!';
  frame.sod = 0x3;
  frame.len = len;
  memcpy(frame.payload, pFrame->frame_content, len);
  comm_interface_transmit_frame(0, DATA_FRAME, (uint8_t *)&frame, len, NULL);
}

void radioFrameReceiveHandler(zpal_radio_rx_parameters_t * pRxParameters, zpal_radio_receive_frame_t * pFrame)
{
  if (!stopSniffer)
  {
      parseFrame(pRxParameters, pFrame, pFrame->frame_content_length);
  }
}

void run_zniffer(void)
{
  comm_interface_init();

  for (;;)
  {
    switch (state)
    {
      case stateIdle:
      {
        zpal_feed_watchdog();

        uint8_t conState = comm_interface_parse_data();

        /* Nothing to transmit. Check if we received anything */
        if (conState == PARSE_FRAME_RECEIVED)
        {
          /* We got a frame... */
          state = stateFrameParse;
        }
        else if (conState == PARSE_IDLE)
        {

        }
      }
      break;
      case stateFrameParse:
      {
        uint8_t rxCmd = serial_frame->cmd;

        state = stateIdle;

        switch (rxCmd)
        {
          case FUNC_ID_ZN_GET_VERSION:
            DPRINT("FUNC_ID_ZN_GET_VERSION\n");
            compl_workbuf[0] = zpal_get_chip_type();
            compl_workbuf[1] = zpal_get_chip_revision();
            compl_workbuf[2] = zpal_get_app_version_major();
            compl_workbuf[3] = zpal_get_app_version_minor();
            DoRespond_workbuf(4);
            break;
          
          case FUNC_ID_ZN_SET_FREQUENCY:
          {
            DPRINT("FUNC_ID_ZN_SET_FREQUENCY\n");
            uint8_t freq_no = serial_frame->payload[0];
            zpal_radio_change_region(freq_no);
            DoRespond();
          }
          break;

          case FUNC_ID_ZN_GET_FREQUENCIES:
            DPRINT("FUNC_ID_ZN_GET_FREQUENCIES\n");
            compl_workbuf[0] = zpal_radio_get_region();
            for (int i = 0; i < MAX_NO_OF_FREQ_SUPPORTED; ++i)
            {
              compl_workbuf[i + 1] = SUPPORTED_FREQ_LIST[i].freq_no;
            }
            DoRespond_workbuf(MAX_NO_OF_FREQ_SUPPORTED + 1);
            break;
          
          case FUNC_ID_ZN_START:
            DPRINT("FUNC_ID_ZN_START\n");
            handling_beam = false;
            stopSniffer = false;
            DoRespond();
            break;
          
          case FUNC_ID_ZN_STOP:
            DPRINT("FUNC_ID_ZN_STOP\n");
            handling_beam = false;
            stopSniffer = true;
            DoRespond();
            break;
          
          case FUNC_ID_ZN_SET_BAUD_RATE:
          {
            DPRINT("FUNC_ID_ZN_SET_BAUD_RATE\n");
            uint8_t baud_rate = serial_frame->payload[0];
            if (0 == baud_rate)
            {
              DoRespond();
            }
            else if (1 == baud_rate)
            {
              // Not supported
            }
            else
            {
              break;
            }
          }
          break;
          
          case FUNC_ID_ZN_GET_FREQUENCY_STR:
          {
            DPRINT("FUNC_ID_ZN_GET_FREQUENCY_STR\n");
            uint8_t freq_no = serial_frame->payload[0];
            uint8_t i;
            for (i = 0; i < MAX_NO_OF_FREQ_SUPPORTED; ++i)
            {
              if (SUPPORTED_FREQ_LIST[i].freq_no == freq_no)
              {
                break;
              }
            }
            if (MAX_NO_OF_FREQ_SUPPORTED > i)
            {
              char* str;

              str = SUPPORTED_FREQ_LIST[i].description;
              compl_workbuf[0] = freq_no;
              compl_workbuf[1] = SUPPORTED_FREQ_LIST[i].channels;
              i = 0;
              while ('\0' != *str)
              {
                compl_workbuf[i + 2] = *str++;
                ++i;
              }
              DoRespond_workbuf(i + 2);
            }
            else
            {
              DoRespond();
            }
          }
          break;

          default:
            DPRINTF("rxCmd = %u\n", rxCmd);
            state = stateIdle;
            break;
        }
      }
      break;
    }
  }
}
