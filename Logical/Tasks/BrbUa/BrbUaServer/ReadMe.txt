
Hier werden dieselben lokalen Variablen 'VarsLocal' zur Verf�gung gestellt wie im Task 'ServerData'.
Auf sie wird im Task 'BrbUaClient' zugegriffen.
Zus�tzlich wird der Umgang mit dem Datentyp "UAByteStringBrbEventId_TYP" gezeigt, welcher eine 16 Byte lange
EventId aufnimmt und ver�ffentlicht.

Ausserdem ist dieselbe Methode 'Calculate' implementiert wie im Task 'ServerMethods'.
Beachtenswert ist die K�rze des Codes. Statt einer kompletten Schrittkette kann die Methode in einem relativ
kleinen If-Then-Else-Block abgehandelt werden.

Auch das Feuern eines Events mithilfe des RunServers ist hier implementiert. Im Gegegsatz zur herk�mmlichen
Programmierung (Tasks 'ServerEvents') wird hier aber nicht das Event 'ProgessType', sondern 'TransitionType'
gefeuert. Auch hier ist die K�rze des Codes ausschlaggebend.
