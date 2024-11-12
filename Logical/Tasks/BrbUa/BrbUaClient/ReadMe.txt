
Diese Client-Implementierung mithilfe der Bibliothek BrbLibUa enthält dieselbe Funktionalität wie der herkömmlich
programmierte Client in diesem Projekt (Task 'Clients').
Schon anhand des Vergleichs der Code-Längen der beiden Tasks kann die enorme Zeitersparnis erahnt werden, welche mit
der Bibliothek erreicht werden kann.

Hinweis: Als Beispiel zum Empfangen eines Events wurde das Event 'EventTransitionType' gewählt, welches auch von den
Tasks in 'BrbUaServer' gefeuert wird. Da es diesen Server-Task zweimal gibt (für ANSI-C und StructuredTest), wird dieses
Event von beiden Server-Tasks gefeuert und deshalb auch von beiden empfangen. Zum Test können die Client- bzw. Server-Tasks
der nicht benötigten Sprache deaktiviert werden.

Zusätzlich ist das Abonnieren der Server-Diagnose-Daten implementiert. Dies könnte auch herkömmlich gemacht werden, da
dazu nur die Abonnierung bestimmter Knoten nötig ist, welche komplexe Datentypen mit dynamischen Arrays haben. Bequemerweise
sind diese Datentypen in der Bibliothek schon vordefiniert. Deshalb und weil die Abonnierung hier keinen Code benötigt, ist
das Beispiel nur hier implementiert. Außerdem können interessante Informationen dazu in der Hilfe der Bibliothek nachgelesen
werden.
