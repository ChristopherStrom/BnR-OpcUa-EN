
Die gr��ten nativ auf der Sps unter IEC unterst�tzten Integer-Datentypen sind UDINT (Uint32) und DINT (Int32).
Manchmal werden aber auch gr��ere Datentypen als Z�hler ben�tigt (z.B. bei Companion Specifications).

Dieses Beispiel zeigt die Verwendung von 64-Bit-Datentypen wie Uint64 (ULINT) und Int64 (LINT) unter OpcUa.
Die ben�tigten Strukturen und Funktionen daf�r sind in der Basis-Bibliothek BrbLib ab V5.02 implementiert.
Beschreibungen und Hinweise dazu sind in der Hilfe der Bibliothek zu finden. Besonders beachtet werden sollte
der Hinweis zur Konsistenz!

Der Task definiert jeweils einen Uint64 (Variable nUint64) und einen Int64 (Variable nInt64).
Beide werden zyklisch ver�ndert, um den Umgang damit zu demonstrieren. Vor allem die Unter- bzw. �berl�ufe
werden dabei gezeigt:
	
	Uint64:
		Bereich: 0..18446744073709551615
		Startwert: 0
		Er wird auf 5 hochgez�hlt. Dann wird die Z�hlrichtung auf negativ gesetzt. Wird er bei 0 (=niedrigster Wert)
		nochmals um 1 dekrementiert, findet ein Unterlauf statt, der zum Wert 18446744073709551615 (=h�chster Wert) f�hrt.
		Es wird dann weiter bis 18446744073709551610 runtergez�hlt. Dann wird die Z�hlrichtung wieder auf positiv gesetzt.
		Wird bei 18446744073709551615 (=h�chster Wert) nochmals um 1 inkrementiert, findet ein �berlauf statt, der zum Wert
		0 (=niedrigster Wert) f�hrt. Dann startet die Z�hlung von vorne.
		Die Unter- bzw. �berlauf-Logik ist also gleich wie bei einem vorzeichenlosen Wert mit weniger Bits (z.B. ein UINT).
		Um den 64-Bit-Wert auf der Sps menschenlesbar zu machen, wird er zyklisch in einen Text gewandelt, der die tats�chliche
		Zahl zeigt (Variable sUint64).

	Int64: 
		Bereich: -9223372036854775808..+9223372036854775807
		Startwert: +9223372036854775802
		Er wird auf +9223372036854775807 (=h�chster Wert) hochgez�hlt. Wird dann nochmals um 1 inkrementiert, findet ein
		�berlauf statt, der zum Wert -9223372036854775808 (=niedrigster Wert) f�hrt. Es wird weiter hochgez�hlt
		auf -9223372036854775803. Dann wird die Z�hlrichtung auf negativ gesetzt. Wird beim Wert -9223372036854775808
		(=niedrigster Wert) nochmals um 1 dekrementiert, findet ein Unterlauf statt, der zum Wert +9223372036854775807
		(=h�chster Wert) f�hrt. Es wird weiter runtergez�hlt bis +9223372036854775802 und dann die Z�hlrichtung wieder auf
		positiv gesetzt. Dann startet die Z�hlung von vorne.
		Die Unter- bzw. �berlauf-Logik ist also gleich wie bei einem vorzeichenbehafteten Wert mit weniger Bits (z.B.
		ein INT).
		Um den 64-Bit-Wert auf der Sps menschenlesbar zu machen, wird er zyklisch in einen Text gewandelt, der die tats�chliche
		Zahl zeigt (Variable sInt64).

Ver�ffentlichung am OpcUa-Server als 64-Bit-Wert:
	Auf der Sps sind die 64-Bit-Werte also als Struktur aufgelegt (BrbUint64_TYP bzw. BrbInt64_TYP).
	Um den Server dazu zu bringen, diese Struktur als Uint64 bzw. Int64 zu ver�ffentlichen, ist nur eine einfache
	Konfiguration n�tig. Sie muss in der Datei 'OpcUaMap.uad' (siehe ConfigurationView/Connectivity/OpcUa) gemacht werden,
	und zwar in der Spalte 'UA Datatype' der Struktur-Variable (die Unterelemente der Struktur sollten nicht freigegeben
	werden). Hier kann optional ein anderer als der Sps-Datentyp als NodeId des OpcUa-Datentyps angegeben werden:
		Uint64: ns=0;i=9
		Int64: ns=0;i=8
	Der Server ver�ffentlicht dann den Variablen-Wert als angegebenen OpcUa-Datentyp.
	Dies funktioniert aber nur, wenn die Sps-Variable die L�nge in Bytes hat, welche vom angegebenen OpcUa-Typ ben�tigt wird.
	Die OpcUa-Datentypen Uint64 bzw. Int64 ben�tigen jeweils 8 Byte, welche durch die Instanzen der Strukturen
	'BrbUint64_TYP' bzw. 'BrbInt64_TYP' bereitgestellt werden.
	