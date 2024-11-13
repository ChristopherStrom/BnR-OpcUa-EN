Example of a client implementation using the 'AsOpcUac' library.

**General Configuration:**
The client automatically establishes a connection to the server after the PLC starts. The variable `bStartClient` is set to `1` in the initialization phase. If you want to prevent the client from starting automatically, set this variable to `0` in the initialization phase and then to `1` in the watch phase.

The client connects to its own server by default, but the parameters can be changed to connect to an external server.

**Process Flow:**
1. Establish connection
2. Retrieve NamespaceIndex for the Foundation namespace: `http://opcfoundation.org/UA/`
3. Retrieve NamespaceIndex for B&R variables namespace: `http://br-automation.com/OpcUa/PLC/PV/`
4. Create a subscription for variables
5. Retrieve NodeHandles for the subscription
6. Add MonitoredItems
7. Repeat step 4 until all variable subscriptions are created, then proceed to step 8
8. Create a subscription for events
9. Retrieve the NodeHandle for the EventNotifier node `ns=0;i=2253` (Root/Objects/Server)
10. Add an EventItem with fields to send
11. Retrieve NodeHandles for read operations
12. Retrieve NodeHandles for write operations
13. Retrieve handles for methods
14. Check for connection interruption
15. Every 1000ms, proceed to step 16
16. Read values
17. Write values
18. Call the method `Calculate`
19. Return to step 14

**Variable Subscriptions:**
Three subscriptions, each with four MonitoredItems, are created. Their parameters are:
- `SubVar[0]`: PublishingInterval = 500ms, Priority = 200
- `SubVar[1]`: PublishingInterval = 1000ms, Priority = 100
- `SubVar[2]`: PublishingInterval = 2000ms, Priority = 50

From AS4.1, the `UA_MonitoredItemAdd` function block is used. Starting with AS4.2, `UA_MonitoredItemAddList` is available and used here.

If a MonitoredItem’s `QueueSize` parameter is greater than `0`, the `UA_MonitoredItemOperateList` function block **must** be called cyclically; otherwise, values won’t be written to the variables. In this example, `QueueSize` is always `0`, so it operates without the `Operate` block.

All standard data types in the structure `ServerData::VarsLocal.ReadOnly` are subscribed to, except the `INT` array. Received values are stored in the local structure `ClientXXX:ClientVarsSubscription`.

**Event Subscription:**
An additional subscription is created, containing only one item, which is an EventItem (not a variable). This subscription allows receiving events.

The subscription must target a node with the `EventNotifier` attribute set to `1=SubscribeToEvents`. On B&R’s OPC UA server, this is `ns=0;i=2253` (Root/Objects/Server). All server events can be subscribed through this node.

The client sends a filter to the server during subscription, specifying:
1. **Event Type**: Defined as NodeId. For example, `ns=0;i=11436` (ProgressEventType), which is fired cyclically in the `ServerEvents` task. Specifying `ns=0;i=2041` (BaseEventType) would allow receiving all events.
2. **Fields to Send**: An array of relative browse paths for the fields, including:
   - From `BaseEventType`: `EventId`, `EventType`, `LocalTime`, `Message`, `ReceiveTime`, `Severity`, `SourceName`, `SourceNode`, `Time`
   - From `ProgressEventType`: `Context`, `Progress`

Each field must have a corresponding variable for the stack to fill upon receiving an event. These variables are passed as a string array, with their order matching the field order. The variable’s data type must match the field’s.

To process received events, the `UA_EventItemOperate` function block must be called cyclically. When its `EventProcessed` output goes high, a new event has been received, and the field variables are populated. In this example, field variables are contained in the `ReceivedEvent` structure.

Upon detecting a new event:
- The `ReceivedEvent.nReceivedCount` counter is incremented for diagnostics.
- The received `EventId` (as a byte array) is converted into a hexadecimal string for better display.

**Notes:**
- Audit events can also be received, but the server sends them only over an encrypted connection.
- See the `ServerEvents` task’s ReadMe for more details on events and fields.

**Read:**
Values are read every 1000ms from the `ServerData:VarsLocal.ReadOnly` structure and written to `ClientXXX:ClientVarsRead`. This includes the elements `nUdint`, `nDint`, and `anInt` (array).

**Caution:** Cyclical reading (polling) should not be implemented in applications. Use subscriptions instead. This example demonstrates function block setup only.

**Write:**
Values are written every 1000ms from `ClientXXX:ClientVarsRead` to `ServerData::WriteXXX`.

**Method `Calculate`:**
The method is called every 1000ms. Input arguments are set in `MethCalculateArgs.In`, and output arguments are populated in `MethCalculateArgs.Out`.

**NamespaceUri and NamespaceIndex:**
Typically, a NamespaceUri is used to address a node. However, since transmitting a text during each access is inefficient, the NamespaceUri is converted to a unique NamespaceIndex in OPC UA.

**Note:** The NamespaceIndex is not static and must be determined after each connection using `UA_GetNamespaceIndex`.

B&R servers group all variables in the same namespace, so the index is retrieved once and reused.

NamespaceUri changes by AS version:
- **AS = 4.2**: V1.0 = `urn:B&R/pv/`
- **AS = 4.3**: V2.0 = `http://br-automation.com/OpcUa/PLC/PV/`

To remain compatible with older versions, you can configure the model version in the system settings.

**Connection Interruption:**
If the server connection is lost (e.g., due to cable disconnection or server restart) and re-established, the operating system can automatically restore the connection, including subscriptions and MonitoredItems.

**Errors:**
Errors are logged in the `Step` structure, including the last error, the step where it occurred, and optionally the subscription or item index.

Some errors allow continued operation. For instance, if a MonitoredItem has incorrect parameters, others can still be created. However, a fatal error in parameters requires correction to ensure the client operates.

**Server Diagnostics:**
Server diagnostic data (e.g., connected clients) is not implemented here but can be obtained by subscribing to specific nodes. These often contain dynamic arrays and are easier to handle using the `BrbLibUa` library. An example is implemented in the `BrbUa` task.
