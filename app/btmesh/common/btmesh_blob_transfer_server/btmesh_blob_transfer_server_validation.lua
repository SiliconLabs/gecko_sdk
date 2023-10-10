-- Log function to add prefix to log messages
local LOG_LVL_INFO = 3
local LOG_LVL_WARNING = 2
local LOG_LVL_ERROR = 1
local LOG_PREFIX = "btmesh_blob_transfer_server_validation: "
local VALIDATION_PREFIX = "BLOB Transfer Server: "
local log_level = LOG_LVL_WARNING

-- Status code definitions
local STATUS = {
    OK = 0,
    CONFIG_DOES_NOT_EXIST = -1,
    CONFIG_TYPE_MISMATCH = -2
}

local function log_info(message)
    if LOG_LVL_INFO <= log_level then
        logit("[I] " .. LOG_PREFIX .. message)
    end
end

local function log_warning(message)
    if LOG_LVL_WARNING <= log_level then
        logit("[W] " .. LOG_PREFIX .. message)
    end
end

local function log_error(message)
    if LOG_LVL_ERROR <= log_level then
        logit("[E] " .. LOG_PREFIX .. message)
    end
end

local function report_error(problem, target, description, quickfix)
    log_error(problem .. " - " .. description)
    validation.error(VALIDATION_PREFIX .. problem,
                     target,
                     description,
                     quickfix)
end

local function report_warning(problem, target, description, quickfix)
    log_warning(problem .. " - " .. description)
    validation.warning(VALIDATION_PREFIX .. problem,
                       target,
                       description,
                       quickfix)
end

local function conf_name_inst(unresolved_name, inst)
  return string.gsub(unresolved_name, "INSTANCE", string.upper(inst))
end

-- Iterate over the configuration name and descriptor pairs from config_schema
-- and checks if the configuration exists (for required config names) and
-- converts it to the descriptor value type.
-- If the configuration name does not exist or type conversion is not successful
-- then error is reported in the log and on the user interface of Simplicity
-- Studio. The preprocessed config is written to preprocessed_config parameter.
local function preprocess_config(inst, preprocessed_config, config_schema)
    local status = STATUS.OK
    for unresolved_name, descriptor in pairs(config_schema) do
        -- The INSTANCE shall be substituted in BLOB Transfer Server component
        -- instance configuration names only however the INSTANCE keyword is
        -- present in these names only. So the substitution can be performed
        -- for each configuration name.
        local name = conf_name_inst(unresolved_name, inst)
        if slc.config(name) == nil then
            if descriptor.required then
                local problem = "Configuration missing"
                local description = "Configuration constant does not exist: " .. name
                report_error(problem, validation.target_for_project(), description, nil)
                if status == STATUS.OK then
                    -- Store the status code of the first error
                    status = STATUS.CONFIG_DOES_NOT_EXIST
                end
            end
        else
            if (descriptor.value_type == "number") or (descriptor.value_type == "boolean") then
                local num = autonumber_common.autonumber(slc.config(name).value)
                if num ~= nil then
                    if (descriptor.value_type == "boolean") then
                        preprocessed_config[name] = (num ~= 0)
                    else
                        preprocessed_config[name] = num
                    end
                end
            else
                preprocessed_config[name] = slc.config(name).value
            end

            -- If the number or boolean conversion fails then the name doesn't
            -- exist in the config table so the preprocessed_config[name] is nil
            -- which has nil type
            if type(preprocessed_config[name]) ~= descriptor.value_type then
                local problem = "Configuration type mismatch"
                local description =
                    string.format("The %s constant is not a %s (value: %s)",
                                  name,
                                  descriptor.value_type,
                                  tostring(slc.config(name).value))
                report_error(problem, validation.target_for_defines({name}), description, nil)
                if status == STATUS.OK then
                    -- Store the status code of the first error
                    status = STATUS.CONFIG_TYPE_MISMATCH
                end
            end
        end
    end
    return status
end

local function chunk_size_to_message_count(chunk_size)
    local MAX_UNSEGMENTED_PAYLOAD = 11
    local MAX_PAYLOAD_PER_SEGMENT = 12
    local CHUNK_SIZE_HEADER_MIN_SIZE = 3 -- Opcode (1) + Chunk Number (2)
    local TRANSMIC_MIN_SIZE = 4
    local MAX_UNSEGMENTED_CHUNK_SIZE = MAX_UNSEGMENTED_PAYLOAD
                                       - CHUNK_SIZE_HEADER_MIN_SIZE
    if MAX_UNSEGMENTED_CHUNK_SIZE < chunk_size then
        return math.ceil((CHUNK_SIZE_HEADER_MIN_SIZE + chunk_size + TRANSMIC_MIN_SIZE)
                         / MAX_PAYLOAD_PER_SEGMENT)
    else
        return 1
    end
end

local min_block_size_log = "SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_MIN_BLOCK_SIZE_LOG_CFG_VAL"
local max_block_size_log = "SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_MAX_BLOCK_SIZE_LOG_CFG_VAL"
local max_chunks_per_block = "SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_MAX_CHUNKS_PER_BLOCK_CFG_VAL"
local max_chunk_size = "SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_MAX_CHUNK_SIZE_CFG_VAL"
local push_mode = "SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_PUSH_MODE_CFG_VAL"
local pull_mode = "SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_PULL_MODE_CFG_VAL"
local pull_chunk_request_cnt = "SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_PULL_CHUNK_REQUEST_CNT_CFG_VAL"
local lpn_mode = "SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_LPN_MODE_CFG_VAL"
local lpn_min_queue_length = "SL_BTMESH_LPN_MIN_QUEUE_LENGTH_CFG_VAL"

local config_schema = {
    [min_block_size_log]     = {value_type = "number",  required = true},
    [max_block_size_log]     = {value_type = "number",  required = true},
    [max_chunks_per_block]   = {value_type = "number",  required = true},
    [max_chunk_size]         = {value_type = "number",  required = true},
    [push_mode]              = {value_type = "boolean", required = true},
    [pull_mode]              = {value_type = "boolean", required = true},
    [pull_chunk_request_cnt] = {value_type = "number",  required = true},
    [lpn_mode]               = {value_type = "boolean", required = true},
    [lpn_min_queue_length]   = {value_type = "number",  required = false}
}

local btmesh_blob_transfer_server_component = slc.component("btmesh_blob_transfer_server")
local btmesh_blob_transfer_server_instances = btmesh_blob_transfer_server_component.instances

-- The instances are in a lua set (table with string key and boolean value)
for inst, exists in pairs(btmesh_blob_transfer_server_instances) do
    log_info("BLOB Transfer Server instance: " .. inst)
end

local lpn_component_selected = slc.is_selected("btmesh_lpn")

if lpn_component_selected then
    log_info("Node with low power feature")
    config_schema[lpn_min_queue_length].required = true
end

for inst, exists in pairs(btmesh_blob_transfer_server_instances) do
    local config = {}
    local status = preprocess_config(inst, config, config_schema)

    if status == STATUS.OK then
        -- It is guaranteed that all required config parameters exist and these are
        -- converted to the proper type
        for name, value in pairs(config) do
            -- Log the converted configuration parameters
            log_info(name .. ": " .. tostring(value) .. " (type: " .. type(value) .. ")")
        end

        local min_block_size_log_inst = conf_name_inst(min_block_size_log, inst)
        local max_block_size_log_inst = conf_name_inst(max_block_size_log, inst)
        local max_chunks_per_block_inst = conf_name_inst(max_chunks_per_block, inst)
        local max_chunk_size_inst = conf_name_inst(max_chunk_size, inst)
        local push_mode_inst = conf_name_inst(push_mode, inst)
        local pull_mode_inst = conf_name_inst(pull_mode, inst)
        local pull_chunk_request_cnt_inst = conf_name_inst(pull_chunk_request_cnt, inst)
        local lpn_mode_inst = conf_name_inst(lpn_mode, inst)

        if config[max_block_size_log_inst] < config[min_block_size_log_inst] then
            local problem = "Block size configuration invalid"
            local description =
                string.format("Min Block Size Log (%i) shall not be greater than " ..
                              "Max Block Size Log (%i)",
                              config[min_block_size_log_inst],
                              config[max_block_size_log_inst])
            report_error(problem,
                         validation.target_for_defines({min_block_size_log_inst,
                                                        max_block_size_log_inst}),
                         description,
                         nil)
        end

        if (config[max_chunks_per_block_inst] * config[max_chunk_size_inst])
            < (2 ^ config[max_block_size_log_inst]) then
            local problem = "Block and chunk configuration inconsistent"
            local description =
                string.format("Max Block Size (%i) shall not be greater than product of " ..
                              "max chunk size (%i) and max number of chunks per block (%i)",
                              2 ^ config[max_block_size_log_inst],
                              config[max_chunk_size_inst],
                              config[max_chunks_per_block_inst])
            report_error(problem,
                         validation.target_for_defines({max_block_size_log_inst,
                                                        max_chunk_size_inst,
                                                        max_chunks_per_block_inst}),
                         description,
                         nil)
        end

        if config[lpn_mode_inst] ~= lpn_component_selected then
            local problem = "LPN mode and LPN component consistency issue"
            local description = "The LPN mode configuration option shall be turned on " ..
                                "if and only if the Low Power Node component is present"
            report_warning(problem,
                           validation.target_for_defines({lpn_mode_inst}),
                           description,
                           nil)
        elseif config[lpn_mode_inst] then
            -- LPN mode is turned on and the LPN component exists in the project

            if not config[pull_mode_inst] then
                local problem = "Transfer mode inconsistency"
                local description = "Pull transfer mode is recommended for low power nodes"
                report_warning(problem,
                               validation.target_for_defines({push_mode_inst, pull_mode_inst}),
                               description,
                               nil)
            end

            local chunk_message_count_inst = chunk_size_to_message_count(config[max_chunk_size_inst])
            if (config[lpn_min_queue_length] < config[pull_chunk_request_cnt_inst] * chunk_message_count_inst)
                and config[pull_mode] then
                local problem = "Requested chunks greater than friend queue size"
                local description =
                    string.format("The %i max chunk size fits into %i message and " ..
                                   "%i chunks requested at the same time which does " ..
                                   "not fit into min lpn queue size (%i message)",
                                   config[max_chunk_size_inst],
                                   chunk_message_count_inst,
                                   config[pull_chunk_request_cnt_inst],
                                   config[lpn_min_queue_length])
                report_warning(problem,
                               validation.target_for_defines({max_chunk_size_inst,
                                                              pull_chunk_request_cnt_inst,
                                                              lpn_min_queue_length}),
                               description,
                               nil)
            end
        end
    end
end