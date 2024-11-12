
Diese Client-Implementierung mithilfe der Bibliothek BrbLibUa enth�lt dieselbe Funktionalit�t wie der herk�mmlich
programmierte Client in diesem Projekt (Task 'Clients').
Schon anhand des Vergleichs der Code-L�ngen der beiden Tasks kann die enorme Zeitersparnis erahnt werden, welche mit
der Bibliothek erreicht werden kann.

Hinweis: Als Beispiel zum Empfangen eines Events wurde das Event 'EventTransitionType' gew�hlt, welches auch von den
Tasks in 'BrbUaServer' gefeuert wird. Da es diesen Server-Task zweimal gibt (f�r ANSI-C und StructuredTest), wird dieses
Event von beiden Server-Tasks gefeuert und deshalb auch von beiden empfangen. Zum Test k�nnen die Client- bzw. Server-Tasks
der nicht ben�tigten Sprache deaktiviert werden.

Zus�tzlich ist das Abonnieren der Server-Diagnose-Daten implementiert. Dies k�nnte auch herk�mmlich gemacht werden, da
dazu nur die Abonnierung bestimmter Knoten n�tig ist, welche komplexe Datentypen mit dynamischen Arrays haben. Bequemerweise
sind diese Datentypen in der Bibliothek schon vordefiniert. Deshalb und weil die Abonnierung hier keinen Code ben�tigt, ist
das Beispiel nur hier implementiert. Au�erdem k�nnen interessante Informationen dazu in der Hilfe der Bibliothek nachgelesen
werden.
