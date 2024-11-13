Here, variables are provided that the custom OpcUa server publishes.

The server is configured in the system configuration under 'OPCUA Server'. The PV information model V2.0 is set.

User/Role configuration is located at ConfigurationView/AccessAndSecurity/UserRoleSystem. The following authentication is specified:
    Username:           Admin
    Password:           admin

Data is set up as a global variable 'gVarsGlobal' and as a local variable 'VarsLocal'.
They are configured for the server in the file 'OpcUaMap.uad' (see ConfigurationView/Connectivity/OpcUa).
They contain the structures 'Read', 'Write', and 'ReadWrite', which are also configured as such.
These, in turn, contain a sub-element for each standard data type.
Definitions are available under LogicalView/Global.typ.
The elements of the 'Read' sub-structure are changed in the task cycle (500ms).

A translation of the 'Description' attribute is implemented as an example for the nodes 'gVarsGlobal' and 'VarsLocal'.
The texts are retrieved from the file 'Texts/OpcUaServerTexts'.

Additionally, there are structures 'WriteC' and 'WriteST', whose elements are partially written to by clients.

Use of dynamic arrays:
    On a PLC, an array can never be dynamic, meaning it cannot have a variable length. 
    The length of an array must be defined during project configuration and cannot be changed at runtime.
    However, OpcUa supports dynamic arrays.
    The B&R server can deliver an array declared on the PLC side as dynamic to OpcUa clients using a trick.
    Similarly, a received dynamic array can be transferred to a fixed PLC array.
    A simple example is the variable 'DynamicUintArrayLength', which is declared through a user-defined data type. 
    The data type is as follows:
        DynamicUintArrayLength_TYP:  STRUCT 
            nLength: UAArrayLength;
            anData: ARRAY[0..9] OF UINT;
        END_STRUCT;
    The element 'anData' contains the array with a fixed maximum length, as required on the PLC.
    The element 'nLength' contains the number of valid array elements. By setting this value, the array served at the OpcUa server is adjusted.
    The variable is normally released at the OpcUa server (without sub-elements). Based on the declaration, the system recognizes this variable as a dynamic array and handles it accordingly.
    In a DirectRead or as a MonitoredItem of a subscription, an array with the current length is transmitted.
    In a DirectWrite, the values transmitted as an array are written to 'anData', and 'nLength' is set accordingly.
    The length can also be declared as 'UANoOfElements' instead of 'UAArrayLength'. The difference lies in the format in which the array is transmitted to or expected from the client:
        UAArrayLength:       Transmitted as Uint16[].
        UANoOfElements:      Transmitted as ExtensionObject containing the UINT array.
        
    An example of the second variant is the variable 'DynamicUintArrayElements'. Using a test client like UaExpert or RnCommTest, the difference in format can be easily recognized.
    Which variant to use depends on the format the client can handle. On the PLC side, handling is identical.
    
    This concept works not only with all standard data types but also with structure arrays. Examples include the variables 'DynamicStructArrayLength' and 'DynamicStructArrayElements'.
    Warning: At least one scalar instance of the usaed structure must be released for the data type to be published by the server, enabling the client to resolve the structure. If the structure data type is used only in an array, this will not happen!
    
    Warning: When writing to a dynamic array, the number of written elements MUST NOT exceed the length of the 'anData' array, as the server would then be unable to transfer the received data into the array.
    If this is done, the server will not execute the write command and will return the status '0x8074000' = BadTypeMismatch!
    
    Note: Only 1-dimensional dynamic arrays are supported, not multi-dimensional arrays.
    
    Implementation in the example task:
    Arrays are pre-set in the task’s Init. In the cyclic part (500ms), only the lengths of individual instances are randomly changed.
    
Known bugs in AR versions:
    Fixed as of C4.72:
        Definition with 'UAArrayLength':
            For a dynamic standard data type array subscribed by the client, the server delivered only the current length upon value change instead of the array.
            Note: Worked correctly with 'UANoOfElements'.
    
    Fixed as of B4.73:
        Definition with 'UAArrayLength':
            Usage as method argument did not work correctly. If fewer elements than the maximum number of elements were sent, the server acknowledged with '0x80AB000 = BadInvalidArgument'.
            Note: Worked correctly with 'UANoOfElements'.

Writable attributes:
    The variable 'nWritableAttributes' is configured in the file 'OpcUaMap.uad' so that the attributes 'BrowseName', 'DisplayName', and 'Description' can be written to by a client.
    Warning: Changed values are not retained after a warm start!
