
Beispiel-Methode 'Calculate'
Die Methode ist in der Datei 'Methods.uam' deklariert, welche zum Task hinzugefügt wurde.
Sie enthält 3 Eingangs-Argumente ('nValue0', 'nValue1' und 'anArrayIn') sowie 3 Ausgangs-
Argumente ('nAddition', 'nMultiplication' und 'anArrayOut').
Die Eingangswerte werden sowohl addiert als auch multipliziert. Das Array wird nur auf den Ausgang
übernommen.

Die Methode ist in der Datei 'OpcUaMap.uad' (siehe ConfigurationView/Connectivity/OpcUa) für den Server konfiguriert.

Ablauf:
	1. Es wird geprüft, ob die Methode von einem Client aufgerufen wurde. Wenn ja, wird auf 2. geprungen
	2. Der applikative Code der Methode wird ausgeführt (Addition, Multiplikation + Übernahme des Arrays)
	3. Es wird zurückgemeldet, dass die Methode ausgeführt wurde
	
Beim Aufruf werden die Eingangs-Argumente in der lokalen Struktur 'MethCalculateArgs.In' übergeben.
Die Ausgangs-Argumente können über die lokale Struktur 'MethCalculateArgs.Out' zurückgegeben werden.