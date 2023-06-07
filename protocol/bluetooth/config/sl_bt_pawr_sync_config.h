#ifndef SL_BT_PAWR_SYNC_CONFIG_H
#define SL_BT_PAWR_SYNC_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Bluetooth PAwR Synchronizer Configuration

// <o SL_BT_CONFIG_MAX_PAWR_SYNCHRONIZERS> Max number of PAwR synchronizers <0-255>
// <i> Default: 1
// <i> Define the number of periodic synchronizing instances that the application needs to use concurrently for Periodic Advertising with Responses. This number must not exceed the number of periodic advertising synchronization instances configured by SL_BT_CONFIG_MAX_PERIODIC_SYNC in the component "bluetooth_feature_periodic_sync".
#define SL_BT_CONFIG_MAX_PAWR_SYNCHRONIZERS     (1)

// </h> End Bluetooth PAwR Synchronizer Configuration

// <<< end of configuration section >>>

#endif // SL_BT_PAWR_SYNC_CONFIG_H
