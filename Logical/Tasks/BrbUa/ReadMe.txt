
Die kostenlose Bibliothek 'BrbLibUa' enthält nützliche Funktionen rund um das Thema OpcUa. 
Sie ist in der enthaltenen Datei 'BrbLibUa - Dokumentation' komplett beschrieben.
Sie hat eine Abhängigkeit auf die Bibliothek 'BrbLib', welche allgemein nützliche Funktionen enthält.
Beide Bibliotheken können kostenlos genutzt werden, aber es besteht für den Anwender kein Anspruch auf Support, Wartung
oder Fehlerbehebung. Die Benutzung geschieht auf eigene Gefahr.

Viele der Funktionen sind hier beispielhaft verwendet und zeigen den Vorteil dieser Bibliothek im Gegensatz zur
herkömmlichen Programmierung. Dies bedeutet, dass viele der Funktionalitäten mit relativ wenig Aufwand implementiert
werden können.

Unter anderem wird hier mithilfe der Bibliothek ein OpcUa-Client implementiert, welcher dieselben Funktionalitäten hat
wie der herkömmlich programmierte Client in diesem Projekt (Task 'Clients').
Schon anhand des Vergleichs der Code-Längen der beiden Tasks kann die enorme Zeitersparnis erahnt werden, welche mit
der Bibliothek erreicht werden kann.
Zusätzlich ist das Abonnieren der Server-Info- und Server-Diagnose-Daten implementiert. Dies könnte auch herkömmlich gemacht
werden, da dazu nur die Abonnierung bestimmter Knoten nötig ist, welche komplexe Datentypen mit dynamischen Arrays haben.
Bequemerweise sind diese Datentypen in der Bibliothek schon vordefiniert. Deshalb und weil die Abonnierung hier keinen Code
benötigt, ist das Beispiel nur hier implementiert. Außerdem können interessante Informationen dazu in der Hilfe der Bibliothek
nachgelesen werden.

Auch server-seitig gibt es Unterstützung. So ist z.B. eine Methode mithilfe der Bibliothek implementiert, was ebenfalls
eine Ersparnis zur herkömmlichen Programmierung bringt.
Auch das Feuern von Events wird von der Bibliothek unterstützt.
