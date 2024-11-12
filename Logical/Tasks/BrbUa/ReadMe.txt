
Die kostenlose Bibliothek 'BrbLibUa' enth�lt n�tzliche Funktionen rund um das Thema OpcUa. 
Sie ist in der enthaltenen Datei 'BrbLibUa - Dokumentation' komplett beschrieben.
Sie hat eine Abh�ngigkeit auf die Bibliothek 'BrbLib', welche allgemein n�tzliche Funktionen enth�lt.
Beide Bibliotheken k�nnen kostenlos genutzt werden, aber es besteht f�r den Anwender kein Anspruch auf Support, Wartung
oder Fehlerbehebung. Die Benutzung geschieht auf eigene Gefahr.

Viele der Funktionen sind hier beispielhaft verwendet und zeigen den Vorteil dieser Bibliothek im Gegensatz zur
herk�mmlichen Programmierung. Dies bedeutet, dass viele der Funktionalit�ten mit relativ wenig Aufwand implementiert
werden k�nnen.

Unter anderem wird hier mithilfe der Bibliothek ein OpcUa-Client implementiert, welcher dieselben Funktionalit�ten hat
wie der herk�mmlich programmierte Client in diesem Projekt (Task 'Clients').
Schon anhand des Vergleichs der Code-L�ngen der beiden Tasks kann die enorme Zeitersparnis erahnt werden, welche mit
der Bibliothek erreicht werden kann.
Zus�tzlich ist das Abonnieren der Server-Info- und Server-Diagnose-Daten implementiert. Dies k�nnte auch herk�mmlich gemacht
werden, da dazu nur die Abonnierung bestimmter Knoten n�tig ist, welche komplexe Datentypen mit dynamischen Arrays haben.
Bequemerweise sind diese Datentypen in der Bibliothek schon vordefiniert. Deshalb und weil die Abonnierung hier keinen Code
ben�tigt, ist das Beispiel nur hier implementiert. Au�erdem k�nnen interessante Informationen dazu in der Hilfe der Bibliothek
nachgelesen werden.

Auch server-seitig gibt es Unterst�tzung. So ist z.B. eine Methode mithilfe der Bibliothek implementiert, was ebenfalls
eine Ersparnis zur herk�mmlichen Programmierung bringt.
Auch das Feuern von Events wird von der Bibliothek unterst�tzt.
