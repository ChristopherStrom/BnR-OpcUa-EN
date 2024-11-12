
Die größten nativ auf der Sps unter IEC unterstützten Integer-Datentypen sind UDINT (Uint32) und DINT (Int32).
Manchmal werden aber auch größere Datentypen als Zähler benötigt (z.B. bei Companion Specifications).

Dieses Beispiel zeigt die Verwendung von 64-Bit-Datentypen wie Uint64 (ULINT) und Int64 (LINT) unter OpcUa.
Die benötigten Strukturen und Funktionen dafür sind in der Basis-Bibliothek BrbLib ab V5.02 implementiert.
Beschreibungen und Hinweise dazu sind in der Hilfe der Bibliothek zu finden. Besonders beachtet werden sollte
der Hinweis zur Konsistenz!

Der Task definiert jeweils einen Uint64 (Variable nUint64) und einen Int64 (Variable nInt64).
Beide werden zyklisch verändert, um den Umgang damit zu demonstrieren. Vor allem die Unter- bzw. Überläufe
werden dabei gezeigt:
	
	Uint64:
		Bereich: 0..18446744073709551615
		Startwert: 0
		Er wird auf 5 hochgezählt. Dann wird die Zählrichtung auf negativ gesetzt. Wird er bei 0 (=niedrigster Wert)
		nochmals um 1 dekrementiert, findet ein Unterlauf statt, der zum Wert 18446744073709551615 (=höchster Wert) führt.
		Es wird dann weiter bis 18446744073709551610 runtergezählt. Dann wird die Zählrichtung wieder auf positiv gesetzt.
		Wird bei 18446744073709551615 (=höchster Wert) nochmals um 1 inkrementiert, findet ein Überlauf statt, der zum Wert
		0 (=niedrigster Wert) führt. Dann startet die Zählung von vorne.
		Die Unter- bzw. Überlauf-Logik ist also gleich wie bei einem vorzeichenlosen Wert mit weniger Bits (z.B. ein UINT).
		Um den 64-Bit-Wert auf der Sps menschenlesbar zu machen, wird er zyklisch in einen Text gewandelt, der die tatsächliche
		Zahl zeigt (Variable sUint64).

	Int64: 
		Bereich: -9223372036854775808..+9223372036854775807
		Startwert: +9223372036854775802
		Er wird auf +9223372036854775807 (=höchster Wert) hochgezählt. Wird dann nochmals um 1 inkrementiert, findet ein
		Überlauf statt, der zum Wert -9223372036854775808 (=niedrigster Wert) führt. Es wird weiter hochgezählt
		auf -9223372036854775803. Dann wird die Zählrichtung auf negativ gesetzt. Wird beim Wert -9223372036854775808
		(=niedrigster Wert) nochmals um 1 dekrementiert, findet ein Unterlauf statt, der zum Wert +9223372036854775807
		(=höchster Wert) führt. Es wird weiter runtergezählt bis +9223372036854775802 und dann die Zählrichtung wieder auf
		positiv gesetzt. Dann startet die Zählung von vorne.
		Die Unter- bzw. Überlauf-Logik ist also gleich wie bei einem vorzeichenbehafteten Wert mit weniger Bits (z.B.
		ein INT).
		Um den 64-Bit-Wert auf der Sps menschenlesbar zu machen, wird er zyklisch in einen Text gewandelt, der die tatsächliche
		Zahl zeigt (Variable sInt64).

Veröffentlichung am OpcUa-Server als 64-Bit-Wert:
	Auf der Sps sind die 64-Bit-Werte also als Struktur aufgelegt (BrbUint64_TYP bzw. BrbInt64_TYP).
	Um den Server dazu zu bringen, diese Struktur als Uint64 bzw. Int64 zu veröffentlichen, ist nur eine einfache
	Konfiguration nötig. Sie muss in der Datei 'OpcUaMap.uad' (siehe ConfigurationView/Connectivity/OpcUa) gemacht werden,
	und zwar in der Spalte 'UA Datatype' der Struktur-Variable (die Unterelemente der Struktur sollten nicht freigegeben
	werden). Hier kann optional ein anderer als der Sps-Datentyp als NodeId des OpcUa-Datentyps angegeben werden:
		Uint64: ns=0;i=9
		Int64: ns=0;i=8
	Der Server veröffentlicht dann den Variablen-Wert als angegebenen OpcUa-Datentyp.
	Dies funktioniert aber nur, wenn die Sps-Variable die Länge in Bytes hat, welche vom angegebenen OpcUa-Typ benötigt wird.
	Die OpcUa-Datentypen Uint64 bzw. Int64 benötigen jeweils 8 Byte, welche durch die Instanzen der Strukturen
	'BrbUint64_TYP' bzw. 'BrbInt64_TYP' bereitgestellt werden.
	