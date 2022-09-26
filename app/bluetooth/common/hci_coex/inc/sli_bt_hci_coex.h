#ifndef SLI_BT_HCI_COEX_H
#define SLI_BT_HCI_COEX_H

#include <stdint.h>

typedef struct sli_bt_hci_coex_set_options{
  uint32_t mask;
  uint32_t options;
} sli_bt_hci_coex_set_options_t;

void sli_bt_hci_init_coex(void);

#endif //SLI_BTHCI_COEX_H
