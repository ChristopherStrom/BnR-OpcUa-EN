
Beispiel-Methode 'Calculate'
Die Methode ist in der Datei 'Methods.uam' deklariert, welche zum Task hinzugef�gt wurde.
Sie enth�lt 3 Eingangs-Argumente ('nValue0', 'nValue1' und 'anArrayIn') sowie 3 Ausgangs-
Argumente ('nAddition', 'nMultiplication' und 'anArrayOut').
Die Eingangswerte werden sowohl addiert als auch multipliziert. Das Array wird nur auf den Ausgang
�bernommen.

Die Methode ist in der Datei 'OpcUaMap.uad' (siehe ConfigurationView/Connectivity/OpcUa) f�r den Server konfiguriert.

Ablauf:
	1. Es wird gepr�ft, ob die Methode von einem Client aufgerufen wurde. Wenn ja, wird auf 2. geprungen
	2. Der applikative Code der Methode wird ausgef�hrt (Addition, Multiplikation + �bernahme des Arrays)
	3. Es wird zur�ckgemeldet, dass die Methode ausgef�hrt wurde
	
Beim Aufruf werden die Eingangs-Argumente in der lokalen Struktur 'MethCalculateArgs.In' �bergeben.
Die Ausgangs-Argumente k�nnen �ber die lokale Struktur 'MethCalculateArgs.Out' zur�ckgegeben werden.