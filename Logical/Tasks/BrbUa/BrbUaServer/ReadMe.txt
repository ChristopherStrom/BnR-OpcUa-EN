
Hier werden dieselben lokalen Variablen 'VarsLocal' zur Verfügung gestellt wie im Task 'ServerData'.
Auf sie wird im Task 'BrbUaClient' zugegriffen.
Zusätzlich wird der Umgang mit dem Datentyp "UAByteStringBrbEventId_TYP" gezeigt, welcher eine 16 Byte lange
EventId aufnimmt und veröffentlicht.

Ausserdem ist dieselbe Methode 'Calculate' implementiert wie im Task 'ServerMethods'.
Beachtenswert ist die Kürze des Codes. Statt einer kompletten Schrittkette kann die Methode in einem relativ
kleinen If-Then-Else-Block abgehandelt werden.

Auch das Feuern eines Events mithilfe des RunServers ist hier implementiert. Im Gegegsatz zur herkömmlichen
Programmierung (Tasks 'ServerEvents') wird hier aber nicht das Event 'ProgessType', sondern 'TransitionType'
gefeuert. Auch hier ist die Kürze des Codes ausschlaggebend.
