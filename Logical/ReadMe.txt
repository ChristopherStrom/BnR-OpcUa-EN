In this example, the implementation of OPC UA functionalities is demonstrated.
This is NOT an official example, and therefore, the user is not entitled to any
enhancements, bug fixes, training, or support. Error-free operation cannot be guaranteed either.

Tasks

Template: Serves as a template to quickly implement new tasks in the same format.
It is not required for this example.
ServerData: Provides variables that are published on the user's server and variables that can be written by clients.
SrvDt64C: Implementation of 64-bit values in ANSI-C.
SrvDt64ST: Implementation of 64-bit values in StructuredText.
SrvMethC: Implementation of custom server methods in ANSI-C.
SrvMethST: Implementation of custom server methods in StructuredText.
SrvEvntC: User-side firing of an event in ANSI-C.
SrvEvntST: User-side firing of an event in StructuredText. This task is disabled.
ClientC: Implementation of the client in ANSI-C.
ClientST: Implementation of the client in StructuredText.
BrbUaCltC: Implementation of the client using the BrbLibUa library in ANSI-C.
BrbUaCltST: Implementation of the client using the BrbLibUa library in StructuredText.
OpcUaAny: Only provides variables mapped to the OpcUaAny client.
BrbUaSrvC: Implementation of the server using the BrbLibUa library in ANSI-C.
BrbUaSrvST: Implementation of the server using the BrbLibUa library in StructuredText.
UaCertsC: Example of runtime management of certificates in ANSI-C.
UaCertsST: Example of runtime management of certificates in StructuredText.
AirCondC: Functional implementation for a custom data model example in ANSI-C.
AirCondST: Functional implementation for a custom data model example in StructuredText.
PubSub: Exemplary configuration of a PubSub connection.
Each task also contains a ReadMe.txt file with further details.
The task 'SrvEvntST' is disabled to prevent the event from being fired by both the ANSI-C and ST tasks.

To fully understand this example, studying the AS help is essential.
Additionally, the user should acquire knowledge about OPC UA concepts and general functionality.
B&R also offers courses for this purpose.

From AS4.4 onwards, the OpcUa_Any client can be used as a replacement for the library client.
This client is added to the HW tree and only needs to be parameterized instead of programmed.

From AS4.9 onwards, a library client can be implemented with significantly less effort using the BrbLibUa library.
An example for this is also provided.

IMPORTANT:
If no specific certificate is created for the server/client, certificates are automatically generated upon the first startup of the PLC.
These certificates are valid for 10 years.
For connections between B&R participants, this is not critical, as the validity period is not checked.
However, for connections to external participants (non-B&R), it must be determined if the validity period is checked. If so, the connection might be rejected!
In such cases, custom certificates should be created and used.

Refer to AS help GUID 'f83f9b82-60fe-4f7c-b101-504cb81ffc44' (='Access & Security/TLS/SSL (SSL at B&R)') and
GUID '2c919423-08bb-4895-88b8-afcf6114d0a2' (='Programming/Editors/Configuration Editors/Hardware Configuration/CPU Configuration/SG4/OPC UA Server').

In this example, a certificate for the server and client with a validity of 50 years was created under
ConfigurationView/AccessAndSecurity/CertificateStore/OwnCertificates.

The configuration ConfigurationView/AccessAndSecurity/TransportLayerSecurity/OpcUaCfg.sslcfg was created, where the entries are configured.
The SslCfgOpcUaServer configuration was assigned to the server in the system configuration.
The SslCfgOpcUaClient configuration is assigned to the client at the FB UA_Connect.

See also the package UACerts.