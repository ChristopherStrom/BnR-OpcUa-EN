# OpcUaSamples
Samples for configuration and coding OpcUa in Ansi-C and StructuredText with many explainings and hints

<a name="Introduction"></a>
## Introduction
Running in Simulation

Everything is well documented, but only in German, I been working on translating to English

Implemented use cases in latest version:

  Server
   * TLS-Configuration (AS4.2)
   * User management (AS4.2)
   * Publish Variables (AS4.1)
   * Handle Methods (AS4.3)
   * Firing events (AS4.6)
   * Dynamic arrays (AS4.6)
   * Localization of texts (AS4.6)
   * Import of a foreign address space model (AS4.6, AS4.7)
   * Handling of 64-Bit datatypes Uint64 + Int64 (AS4.10)
   * etc...
  
  Library client
   * TLS-Configuration (AS4.2)
   * Establish a connection (AS4.1)
   * Determine conncetion status (AS4.1)
   * Closing a connection (AS4.1)
   * Determine namespace indices (AS4.1)
   * Direct read/write (AS4.1)
   * Several subscriptions for monitored items (AS4.1)
   * Calling of methods (AS4.3)
   * Receiving events (AS4.6)
   * Reading and Subscribing of Server info and diagnosis datapoints (AS4.10)
   * etc...
  
  OpcUa-Any-Client
   * Configuration (AS4.4)
   * Mapping (AS4.4)
  
  PubSub
   * Publisher configuration (AS4.9)
   * Subscriber configuration (AS4.9)
  
  Applicative management of certificates at runtime
   * Wrapping library functions with OpcUa methods (AS4.6)
  
  BrbLibUa V1.03 (contained in sample for AS4.10)
   * Library with useful functions around OpcUa including wrappers for server and client to reduce code enormously
 
