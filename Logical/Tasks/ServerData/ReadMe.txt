
Hier werden Variablen zur Verfügung gestellt, die der eigene OpcUa-Server veröffentlicht.

Der Server ist in der System-Konfiguration unter 'OPCUA Server' parametriert. Es ist das PV-Informationsmodell V2.0
eingestellt.

Die User-/Roles-Parametrierung ist unter ConfigurationView/AccessAndSecurity/UserRoleSystem.  Hier ist folgende
Authentifizierung angegeben:
	Username:			Admin
	Password:			admin

Daten sind als globale Variable 'gVarsGlobal' und als lokale Variable 'VarsLocal' angelegt.
Sie wurden in der Datei 'OpcUaMap.uad' (siehe ConfigurationView/Connectivity/OpcUa) für den Server konfiguriert.
Sie enthalten die Strukturen 'Read', 'Write' und 'ReadWrite', welche auch so parametriert sind.
Diese wiederum enthalten jeweils ein Unterelement jeden Standard-Datentyps.
Definition siehe LogicalView/Global.typ.
Die Elemente der Unter-Struktur 'Read' werden im Task-Takt (500ms) geändert.

Eine Übersetzung des Attributes 'Description' ist beispielhaft bei den beiden Knoten 'gVarsGlobal' und 'VarsLocal'
implementiert. Dabei werden die Texte aus der Datei 'Texts/OpcUaServerTexts' verwendet.

Ausserdem gibt es die Strukturen 'WriteC' und 'WriteST', auf deren Elemente teilweise von den Clients geschrieben wird.

Einsatz von dynamischen Arrays:
	Auf einer SPS kann ein Array nie dynamisch sein, also keine variable Länge haben. Die Länge eines Arrays 
	muss zur Projektierungszeit im AS  festgelegt werden und kann zur Laufzeit nicht mehr geändert werden.
	OpcUa untersützt jedoch dynamische Arrays.
	Der B&R-Server kann mit einem Trick ein in der SPS deklariertes Array OpcUa-seitig als dynamisch
	ausliefern. Auch ein empfangenes dynamisches Array kann so auf ein festes SPS-Array übertragen werden.
	Als einfaches Beispiel dient hier die Variable 'DynamicUintArrayLength', welche durch einen selbstdefinierten
	Datentyp deklariert wird. Der Datentyp sieht so aus:
		DynamicUintArrayLength_TYP : 	STRUCT 
			nLength : UAArrayLength;
			anData : ARRAY[0..9]OF UINT;
		END_STRUCT;
	Das Element 'anData' enthält das Array mit fester maximaler Länge, wie auf der SPS benötigt.
	Das Element 'nLength' enthält die Anzahl der gültigen Array-Elemente. Durch Setzen dieses Wertes wird	das am 
	OpcUa-Server bediente Array angepasst.
	Die Variable wird ganz normal am OpcUa-Server freigegeben (ohne Unter-Elemente). Das System erkennt aufgrund der
	Deklaration, dass diese	Variable ein dynamisches Array ist und behandelt es entsprechend.
	Bei einem DirectRead oder als MonitoredItem einer Subscription wird ein Array mit der aktuellen Länge übertragen.
	Bei einem DirectWrite werden die als Array übertragene Werte in 'anData' geschrieben und 'nLength' entsprechend
	gesetzt.
	Die Länge kann anstatt als 'UAArrayLength' auch als 'UANoOfElements' deklariert werden. Der Unterschied ist das Format,
	in welchem das Array an den Client übertragen bzw. vom Client erwartet wird:
		UAArrayLength:		Wird als Uint16[] übertragen.
		UANoOfElements:		Wird als ExtensionObject übertragen. Es enthält das UINT-Array.
		
	Als Beispiel für die zweite Variante ist die Variable 'DynamicUintArrayElements' implementiert. Über einen Test-Client
	wie UaExpert oder RnCommTest kann der Unterschied des Formats sehr leicht erkannt werden.
	Welche Variante verwendet werden sollte, hängt davon ab, mit welchem Format der Client umgehen kann. Sps-seitig ist
	Behandlung identisch.
	
	Dieses Konzept funktioniert nicht nur mit allen Standard-Datentypen, sondern auch mit Struktur-Arrays. Als Beispiele
	sind die beiden Variablen 'DynamicStructArrayLength' bzw. 'DynamicStructArrayElements' implementiert.
	Achtung: Mindestens eine skalare Instanz der verwendeten Struktur muss freigegeben sein, damit der Datentyp vom Server
	veröffentlicht wird und es dem Client so ermöglicht, die Struktur aufzulösen. Wenn der Struktur-Datentyp nur im Array
	verwendet wird, ist dies nicht der Fall!
	
	Achtung: Bei einem Schreib-Zugriff auf ein dynamisches Array darf die Anzahl der geschriebenen Elemente NICHT die 
	Länge des Array 'anData' überschreiten, da der Server dann die empfangenen Daten nicht in das Array übertragen kann.
	Wird dies	doch gemacht, führt der Server den Schreibauftrag nicht aus und gibt den Status
	'0x8074000' = BadTypeMismatch	zurück!
	
	Hinweis: Bei dynamischen Arrays werden nur 1-dimensionale, aber keine mehrdimensionalen Arrays unterstützt.
	
	Implementierung im Beispiel-Task:
	Die Arrays werden im Init des Tasks vorbesetzt. Im zyklischen Teil (500ms) werden nur die Längen der einzelnen
	Instanzen zufällig verändert.
	
	Bekannte Bugs in AR-Versionen:
	Behoben ab C4.72:
		Definition mit 'UAArrayLength':
			Bei einem dynamischen Standard-Datentypen-Array, welches vom Client über eine	Subscription abonniert wurde,
			lieferte der Server bei einer Wert-Änderung nicht das Array, sondern nur die aktuelle Länge.
			Hinweis: Mit 'UANoOfElements' funktionierte es korrekt.
	
	Behoben ab B4.73:
		Definition mit 'UAArrayLength':
			Die Verwendung als Methoden-Argument funktioniert nicht korrekt. Werden weniger Elemente als die maximale Anzahl
			an Elementen gesendet, quittiert dies der Server mit '0x80AB000 = BadInvalidArgument'
			Hinweis: Mit 'UANoOfElements' funktioniert es korrekt.

Schreibbare Attribute:
	Die Variable 'nWritableAttributes' ist in der Datei 'OpcUaMap.uad' so parametriert, dass die Attribute
	'BrowseName', 'DisplayName' und 'Description' von einem Client beschrieben werden können.
	Achtung: Geänderte Werte sind nicht warmstartsicher!