
Here, the same local variables 'VarsLocal' are provided as in the task 'ServerData.'
These are accessed in the task 'BrbUaClient.'
Additionally, the handling of the data type "UAByteStringBrbEventId_TYP" is demonstrated,
which stores and publishes a 16-byte EventId.

Furthermore, the same method 'Calculate' is implemented as in the task 'ServerMethods.'
Noteworthy is the brevity of the code. Instead of a complete step chain, the method can be handled in a relatively
small If-Then-Else block.

The firing of an event using the RunServer is also implemented here.
In contrast to conventional programming (tasks 'ServerEvents'), the event 'TransitionType' is fired instead of 'ProgessType.'
The concise code structure highlights the efficiency of this approach.