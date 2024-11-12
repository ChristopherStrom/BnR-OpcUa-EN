
{REDUND_CONTEXT} FUNCTION ArPubSubDGetUdpMsgSendTotal : UDINT (*Returns the total amount of messages being sent for all PubSub UDP connections.*)
END_FUNCTION

{REDUND_CONTEXT} FUNCTION ArPubSubDGetUdpMsgSendError : UDINT (*Returns the amount of messages that faced sending problems for all PubSub UDP connections.*)
END_FUNCTION

{REDUND_CONTEXT} FUNCTION ArPubSubDGetUdpMsgReceiveTotal : UDINT (*Returns the total amount of received messages for all PubSub UDP connections.*)
END_FUNCTION

{REDUND_CONTEXT} FUNCTION ArPubSubDGetUdpMsgReceiveError : UDINT (*Returns the amount of network timed out messages for all PubSub UDP connections*)
END_FUNCTION

{REDUND_CONTEXT} FUNCTION ArPubSubDGetDataSetSendTotal : UDINT (*Returns the total amount of publisher datasets being processed.*)
END_FUNCTION

{REDUND_CONTEXT} FUNCTION ArPubSubDGetDataSetSendError : UDINT (*Returns the amount of erroneous publisher datasets being processed. A dataset is erroneous if at least one of the dataset fields is erroneous (e.g. if it does not contain data for a process variable).*) 
END_FUNCTION

{REDUND_CONTEXT} FUNCTION ArPubSubDGetDataSetReceiveTotal : UDINT (*Returns the total amount of subscriber datasets being processed.*)
END_FUNCTION

{REDUND_CONTEXT} FUNCTION ArPubSubDGetDataSetReceiveError : UDINT (*Returns the amount of erroneous subscriber datasets being processed. A dataset is erroneous if at least one of the dataset fields is erroneous (e.g. if it does not contain data for a process variable or if the received statuscode is not "OPC UA good").*)
END_FUNCTION
