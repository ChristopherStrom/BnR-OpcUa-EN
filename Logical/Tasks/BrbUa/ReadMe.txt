The free library 'BrbLibUa' contains useful functions related to the topic of OPC UA.
It is fully documented in the included file 'BrbLibUa - Documentation.'
It has a dependency on the library 'BrbLib,' which contains generally useful functions.
Both libraries can be used free of charge, but users are not entitled to support, maintenance,
or bug fixes. Use is at your own risk.

Many of the functions are exemplarily used here and demonstrate the advantage of this library compared to conventional programming.
This means that many functionalities can be implemented with relatively little effort.

Among other things, an OPC UA client is implemented here using the library, which offers the same functionalities
as the conventionally programmed client in this project (Task 'Clients').
Even by comparing the code lengths of the two tasks, one can estimate the significant time savings achievable with the library.

Additionally, the subscription to server info and server diagnostic data is implemented.
This could also be done conventionally, as it only requires subscribing to certain nodes,
which involve complex data types with dynamic arrays.
Conveniently, these data types are already predefined in the library.
Therefore, and because the subscription here requires no code, the example is implemented only here.
Moreover, more detailed information can be found in the library's documentation.

There is also support on the server side. For example, a method is implemented using the library,
which also results in savings compared to conventional programming.
The library also supports the firing of events.