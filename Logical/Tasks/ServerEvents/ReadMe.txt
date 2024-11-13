Example of user-triggered event firing.

In this example, the event 'ProgressEventType' is fired. It is typically used to report the progress of a process.
Since it is derived directly from 'BaseEventType', it inherits its fields: 'EventId', 'EventType', 'LocalTime',
'Message', 'ReceiveTime', 'Severity', 'SourceName', 'SourceNode', and 'Time'.
In the task, only 'Message' and 'Severity' are set. The others are not passed and are automatically assigned by the operating system:
- **EventId** contains an automatically generated unique GUID.
- **EventType** contains 'ns=0;i=11436', the node of 'ProgressEventType'.
- **LocalTime** holds the local server time offset from UTC.
- **ReceiveTime** contains the UTC time when the event was received by the server, if the server is not the event creator. 
  In this case, it defaults to 'Time'.
- **SourceName** contains the display name of the node specified in 'SourceNode'.
- **SourceNode** contains the NodeId of the node that triggered the event. If not set in the application, it defaults to "i=0".
- **Time** holds the UTC time when the event occurred.

For each firing, the following BaseEvent fields are set by the user:
- **Message** should contain a LocalizedText describing the event in clear text.
- **Severity** should indicate the priority of the event (1=Info; 1000=Catastrophe). In this example, it is a random number between 1 and 500.

The fired event 'ProgressEventType' also includes its own fields 'Context' and 'Progress':
- **Context** is of type 'BaseDataType'. It is a Variant and can hold any data type.
  In this example, the value is passed as a custom structure 'FieldContext_TYP'. 
  However, it could also be a variable of type 'REAL' or 'UDINT', etc.
  **Note:** For a client to resolve this structure (sent as an ExtensionObject/Byte array), at least one instance of this data type must be released on the server 
  (see OpcUaMap.uad). This ensures the server automatically publishes the structure's definition.
  **Known issue in certain AR versions (A4.90 to D4.90):**
  - Unfortunately, the function block returns error 0x803D0000 = 'Bad_NotSupported' if a structure with a globally defined type is linked to this field. 
    From E4.90 onwards, this issue is resolved.
  - If using one of the affected versions, a workaround is to define the structure locally.

- **Progress** contains the progress value as a UINT, incremented with each event firing.
  Progress is interpreted as a percentage and resets to 0 after reaching 100%.

Variables bound to fields must match the field's data type. If the field is of type 'BaseDataType' (Variant), any data type can be bound.

**Step sequence process:**
- **eSTEP_INIT:** Start the sequence.
- **eSTEP_GET_NS_ORG:** Retrieve the NamespaceIndex for 'http://opcfoundation.org/UA/'.
- **eSTEP_GET_NS_BR_PV:** Retrieve the NamespaceIndex for 'http://br-automation.com/OpcUa/PLC/PV/'.
- **eSTEP_DELAY:** Wait on the timer.
- **eSTEP_SET_FIELD_VALUES:** User-populate event fields.
- **eSTEP_FIRE:** Fire the event.

The namespace URIs are fixed and do not change. The associated namespace indices are assigned when the server starts and must be retrieved.
An event is fired every 5 seconds using a timer. This can be prevented by the 'bSuspendTimer' variable. 
The event can also be manually fired using the 'bFire' variable.

To receive the event client-side, the node 'ns=0;i=2253' (Root/Objects/Server) must be subscribed to in a subscription.
The filter of the EventItem must include the fields to be sent.
**Note:** In the free test client 'UaExpert', the filter is automatically set to include all fields when subscribing to the node.
In other test clients (e.g., RnCommTest), the filter and fields may need to be configured manually.

The 'Client' task contains an example of how this event can be received on the PLC.

Since both the ANSIC task and the ST task operate independently, the event would be fired by both tasks. 
Therefore, one of the tasks should always be disabled. In this case, it is the 'SrvEvntST' task.
