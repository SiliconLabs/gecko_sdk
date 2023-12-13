# True Status Module

## General Information

The True Status module implements the requirements for Lifeline Reports as specified in document "ZWave Plus v2 Device Type Specification".

The main components of the True Status module are described in the following sub-sections.

## True Status Engine

The True Status Engine component is located in the `ZAF/ApplicationUtilities/TrueStatusEngine` folder and consists of the following source files: 
1. ZAF_TSE.c
2. ZAF_TSE.h

TSE implements the functionality for registering and handling the state change events that a node wants to report to its lifeline association group members.
A state change can be triggered by a command from a remote note, or by a local change (e.g., a button press).

## Public functions

<!-- This section describes the functions in doxygen format. -->

@ref ZAF_TSE_Init
@param None 
@returns bool

@ref ZAF_TSE_Trigger
@brief Function for registering state change events and triggering the report to be sent to lifeline
group members after a predefined delay. The delay is currently defined to 250 ms. The delay is
a means to prevent network collisions and to avoid generation of redundant reports from rapid
state changes. The function also takes care of sending the report to the relevant lifeline group members only
i.e., it will not send the report to a lifeline destination that issued the command causing the
state change. The current implementation can hold up to 3 different state change requests in a
queue awaiting the predefined delay to expire. Additional requests during this period will be
discarded.

@param[in] pCallback Pointer to callback function for sending the state change report to the lifeline group members
@param[in] pData Pointer to a data struct that will be passed in argument to the pCallback function. The pData pointed
           struct __must__ contain a RECEIVE_OPTIONS_TYPE_EX variable indicating properties about the received frame 
           that triggered the change. Local changes must also include a RECEIVE_OPTIONS_TYPE_EX in the pData struct
@param[in] overwrite_previous_trigger Boolean parameter indicating if a previous trigger with the same pCallback and the 
           same source endpoint in the pData struct should be discarded or not. Set it to true to overwrite previous triggers 
           and false to stack up all the trigger messages

## True Status Callback Functions

The True Status Callback Functions consist of several functions that implement the functionality for sending the actual state change reports to the lifeline association group members. These functions are implemented in each of the relevant command class modules.
The True Status Callback Function is one of the arguments passed to the `ZAF_TSE_Trigger()` function (described in the previous section), and it will be executed by the True Status Engine for sending the state change reports to each of the relevant members of the lifeline group, one at a time.
An example of a True Status Callback Function implementation can be found in the Command Class BinarySwitch:

## True Status Sequence Flows

The following diagrams show the function call flows for a BinarySwitch example for the two use cases.
1. State change triggered by a command from a remote node 
2. State change triggered by a local change (e.g., a button press)

### Use Case 1 - State Change Triggered by a Command from a Remote Note
![Use Case 1](ZAF_TSE_UC1.png)

### Use Case 2 - State Change Triggered by a Local Change
![Use Case 2](ZAF_TSE_UC2.png)