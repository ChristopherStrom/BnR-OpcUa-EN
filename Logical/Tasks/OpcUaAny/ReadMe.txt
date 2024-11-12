The OpcUaAny client is added as a hardware module to the Ethernet interface.
It represents a server as an I/O module and is parameterized like a "normal" I/O module.
It is automatically managed by a client integrated into the operating system.

General Configuration:
    - The setting "Module supervised" should be set to "off".
      If set to "on" and the module (server) is not reachable, the PLC enters ServiceMode.
    - The "Server Diagnostics" setting provides diagnostic values, which can be mapped to variables (see IO-Mapping).
    - The SSL configuration uses the same certificate (valid for 50 years) as the library client.
      If no certificate is specified, one with a 10-year validity is automatically created.
    - User credentials for client authentication on the server are configured here.

Channel Configuration:
    - Three input and three output channels are set up in this example.
      * Inputs: Used for reading from the server (MonitoredItems in Subscriptions).
      * Outputs: Used for cyclic writing to the server.

    - Instead of using NodeId like the library client, the "Browse path" is used.
      It must contain the correct path to the target node, formatted as:
        <NamespaceIndex>:<NodeName>
      - Path consists of elements separated by '/', each representing a node in the hierarchy.
      - Special characters are prefixed with '&'.

    Special character replacements:
        Character      Replacement
        &              &&
        !              &!
        #              &#
        :              &:
        >              &>
        <              &<
        .              &.
        /              &/

    Example B&R Browse Path:
        /0:Root/0:Objects/4:PLC/4:Modules/7:&:&:/7:OpcUaAny/7:Data/7:Read/7:Server/7:nUsint

        |                                                |         |            |
        |                                                |         |            +--- Variable Name Starts Here
        |                                                |         +---------------- Task Name
        |                                                +-------------------------- ':' in name prefixed with '&'
        +-------------------------------------------------------------------------- Start of Hierarchical Address Tree

        For other vendors, the path format may differ.
        Use a generic client like UAExpert to determine BrowseNames.

IO-Mapping:
    Standard Channels:
        - ModuleOk:
            * Behaves like a normal I/O module.
            * False if server unreachable or connection lost.
            * True when the connection is established.
        - ConnectionLostCount, ClientErrorCount, LastClientError:
            * Always available diagnostic data points.
            * Errors (e.g., incorrect browse path) shown in LastClientError.
        - ServerViewCount, CurrentSessionCount:
            * Available only if "Server Diagnostics" is enabled.

    Custom Channels:
        - Configured channels can be mapped here.
        - Important: Variable types must match the data points.

Variables in This Example:
    - Task "OpcUaAny" provides variables mapped to data points.

    Inputs:
        * Elements in "Data.Read.Server" are incremented and subscribed by the client.
        * Received values are written to "Data.Read.Client".

    Outputs:
        * Elements in "Data.Write.Client" are incremented and written by the client.
        * These map to "Data.Write.Server" on the server.

Connection Loss:
    - As with the library client, communication is automatically restored after connection loss.
    - Use the input channel "ModuleOk" to check connection status.
