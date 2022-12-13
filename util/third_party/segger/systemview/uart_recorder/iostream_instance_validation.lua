local iostream_instance = slc.config("SL_SYSTEMVIEW_UART_RECORDER_IOSTREAM_INSTANCE_NAME").value
local available_instance = slc.component("iostream_usart").instances

local valid = false
for instance in pairs(slc.component("iostream_usart").instances) do
  if instance == iostream_instance then
    valid = true
  end
end

for instance in pairs(slc.component("iostream_leuart").instances) do
  if instance == iostream_instance then
    valid = true
  end
end

for instance in pairs(slc.component("iostream_eusart").instances) do
  if instance == iostream_instance then
    valid = true
  end
end

if valid == false then
  validation.error("SL_SYSTEMVIEW_UART_RECORDER_IOSTREAM_INSTANCE_NAME is invalid. Must be a valid iostream UART instance", validation.target_for_defines({"SL_SYSTEMVIEW_UART_RECORDER_IOSTREAM_INSTANCE_NAME"}))
end