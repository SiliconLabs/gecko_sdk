#ifndef SL_BTMESH_BLOB_STORAGE_CONFIG_H
#define SL_BTMESH_BLOB_STORAGE_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <q SL_BTMESH_BLOB_STORAGE_LOGGING_CFG_VAL> Logging
#define SL_BTMESH_BLOB_STORAGE_LOGGING_CFG_VAL 0

// <o SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL> Alignment
// <1=> Byte (1)
// <2=> Word (2)
// <4=> Double Word (4)
// <8=> Quad Word (8)
#define SL_BTMESH_BLOB_STORAGE_ALIGNMENT_CFG_VAL 8

// <o SL_BTMESH_BLOB_STORAGE_DATA_CHECK_JUMP_CFG_VAL> Data check interval <1-255>
// <i> When checking whether a slot is empty, occupied, or corrupted, use this interval to jump ahead in memory.
// <i> Higher value results in faster operation, but there's a probability of it yielding false results.
#define SL_BTMESH_BLOB_STORAGE_DATA_CHECK_JUMP_CFG_VAL 255

// <o SL_BTMESH_BLOB_STORAGE_ASYNC_DELETE_SEPARATION_TIME_MS_CFG_VAL> Async delete separation time (ms) <0-1000>
// <i> Separation time between two asynchronous delete steps in milliseconds.
// <i> The BLOB storage async delete is performed in multiple steps and each delete step blocks the code execution.
// <i> If delete steps are executed too often then it could starve other timing sensitive SW components.
#define SL_BTMESH_BLOB_STORAGE_ASYNC_DELETE_SEPARATION_TIME_MS_CFG_VAL 10

// <<< end of configuration section >>>

#endif // SL_BTMESH_BLOB_STORAGE_CONFIG_H
