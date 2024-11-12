
Mit diesem Beispiel wird verdeutlicht, wie eigene oder extern definierte OpcUa-Modelle eingesetzt werden können.
	Hinweis: Um die implementierten Modelle zu betrachten und besser zu verstehen, sollte mit einem Test-Client
	(z.B. UaExpert oder RnCommTest) eine Verbindung aufgebaut und der Adress-Raum gebrowst werden.

Erklärung der Task-Funktionalität:
	Als funktionelles Beispiel dient die Implementierung mehrerer Instanzen einer Klima-Anlage.
	Es gibt einen Typ Klima-Anlage, dessen Daten in der Struktur "AirCond_TYP" aufgelegt sind:
		AirCond_TYP
			sName																	Name der Instanz
			Act																		Ist-Werte
				eOperationMode											Betriebs-Modus (0=Aus, 1=Manuell, 2=Automatik)
				rTemperature												Ist-Temperatur in [°C]
				nFanLevel														Ist-Lüfter-Stufe (0-5, 0=Aus)
			Set																		Soll-Werte
				rTemperature												Soll-Temperatur in [°C] für Automatik
				nFanLevel														Soll-Lüfter-Stufe (0-5, 0=Aus) für Manuell

	Es gibt drei Instanzen: Schlafzimmer, Flur und Wohnzimmer. Für jede dieser Instanzen werden die
	entsprechenden Funktionen "Init", "Operate" und "Simulation" aufgerufen. Das bedeutet, dass der
	Code einer Klima-Anlage nur einmal vorhanden ist und Änderung daran nur an einer Stelle gemacht
	werden müssen.
	Jede dieser Instanzen ist im OpcUa-Model mit entsprechenden Rechten freigegeben (siehe Configuration View
	unter "../PC/Connectivity/OpcUA/OpcUaMap.uad").
	Zusätzlich gibt es für jede Klima-Anlagen-Instanz auch noch eine Struktur-Variable "AirCondIntern_TYP". Sie
	enthält Elemente, die als Variablen für die interne Behandlung einer Instanz nötig sind (z.B. 
	Schrittketten-Zähler), welche aber nicht über OpcUa freigegeben sind.
	
	Hier nun die Beschreibung der einzelnen Funktionen, welche für jede Instanz aufgerufen werden:
	Init: Die Werte einer Instanz werden hier vorbesetzt.

	Steuerung:
		Betriebsmodus:
			Aus:
				Der Lüfter bleibt ausgeschaltet (Stufe=0).
			Manuell:
				Der Lüfter wird auf die im Sollwert angegebene Stufe gesetzt.
			Automatik:
				Die Lüfter-Stufe wird aufgrund der prozentualen Abweichung zwischen Ist- und Soll-Wert gesetzt.
		Ausserdem wird hier in einer Schrittkette der Methoden-Aufruf für "SetOperationMode" behandelt.
		Es gibt auch eine Schrittkette, die das Feuern eines Events beim Ändern des Betriebsmodus behandelt.

	Simulation:
		Die Ist-Temperatur wird ständig erhöht und drängt dadurch auf 26.0°C.
		Je nach Lüfter-Stufe wird die Ist-Temperatur abgesenkt und wirkt dadurch der natürlichen
		Erwärmung entgegen.
		Die Ist-Temperatur wird auf den Bereich 15.0 - 26.0°C begrenzt, um ein Abdriften zu verhindern.
					
	OpcUa-Methode "SetOperationMode":
		Die Methode setzt den Betriebsmodus, welcher als einziges Eingangs-Argument übergeben wird.
		Als Ausgangs-Argument wird ein applikativer Status zurückgegeben, welcher auf einen ungültigen
		Betriebsmodus hinweisen kann (dies ist eigentlich nicht möglich, da der Betriebsmodus als Enumeration
		aufgelegt ist).

	OpcUa-Event "AirConditionOperationModeChanged":
		Bei jeder Änderung des Betriebsmodus wird ein Event gefeuert, welches als zusätzliche Felder die 
		Informationen 'OldOperationMode' und 'NewOperationMode' besitzt.

OpcUa-Methode(n) "SetOperationMode":
	In "Methods.uam" ist für jede Instanz jeweils die Methode "SetOperationMode" deklariert. So wird garantiert,
	dass bei jeder Instanz diese Methode gleichzeitig zu den anderen Instanzen aufgerufen werden kann.
	Die Schrittkette für diese Methode ist nur einmal implementiert und wird für jede Instanz einzeln aufgerufen
	(siehe oben).
	
OpcUa-Event(s) "AirConditionOperationModeChanged":
	Dieses Event wurde eigens für dieses Beispiel modelliert und ist im Fremd-Modell hinterlegt (siehe 
	'/Root/Types/EventTypes/BaseEventType/AirConditionOperationModeChanged').
	Normalerweise (wie auch hier) können alle am Server gefeuerten Events durch Abonnierung des Knotens
	'/Root/Objects/Server' (i=2253)	von einem Client empfangen werden. In dieses Beispiel wurde eine zusätzliche
	Möglichkeit implementiert:
	Auch der Instanz-Knoten einer Klima-Anlage im Fremd-Modell (z.B. 'BedRoom') soll abonniert werden können,
	aber nur das Event der betreffenden Instanz feuern.
	Der meiste Teil dieser Anforderung muss im Modeller umgesetzt werden. Im Sps-Programm ist nur eines wichtig:
	Beim Feuern des Events muss das Feld 'SourceNode' applikativ mit der NodeId des Hauptknotens besetzt werden
	(also z.B. 'ns=6;i=5013' für 'BedRoom' in der ANSI-C-Variante).
	Hinweis: Ob ein Knoten Events feuern und deswegen abonniert werden kann, lässt sich sehr leicht mit dem
	Attribut 'EventNotifier' des Knotens prüfen. Es ist bitcodiert. Ist Bit#0 (=SubscribeToEvents) gesetzt,
	so kann der Knoten auf Events abonniert werden.

OpcUa-Modelle:
	Im B&R-Modell, das automatisch vom Compiler erzeugt und vom OpcUa-Server veröffentlicht wird, werden die
	drei Instanzen und deren Methoden in der Ebene des Tasks angezeigt:
		Root
		+--	Objects
				+--	PLC (hier beginnt das automatisch erzeugte B&R-Modell)
						+--	Modules
								+--	Default
										+--	AirCondC (dies ist der Task)
												+--	BedRoomSetOperationMode (Methode)
												+--	CorridorSetOperationMode (Methode)
												+--	LivingRoomSetOperationMode (Methode)
												+--	AirCond_BedRoom (Daten)
												|		+-- Act (Ist-Werte)
												|		|		+--	eOperationMode
												|		|		+--	nFanLevel
												|		|		+--	rTemperature
												|		+--	Set (Soll-Werte)
												|		|		+--	nFanLevel
												|		|		+--	rTemperature
												|		+--	sName (Name der Instanz)
												+--	AirCond_Corridor (Daten)
												|		+-- ...
												+--	AirCond_LivingRoom (Daten)
														+-- ...
		
	Es kann nun aber eine andere Hierarchie der Knoten gewünscht sein. In diesem Beispiel soll die Vorgabe
	sein, dass es jeweils einen Knoten pro Instanz gibt, der die Daten und die dazugehörige Methode enthält.
	Dieser Knoten soll auch das Event feuern können. Auch die Namen der Knoten sollen anders sein (keine
	Präfixe).
	Dazu wurde ein eigenes Modell definiert, das diese Vorgaben erfüllt. Da	dieses Beispiel Tasks sowohl für
	ANSI-C als auch für StructureText enthält, wurde auch im Modell diese	Aufteilung berücksichtigt. Hier das
	Modell für ANSI-C:
	
		Root
		+--	Objects
				+--	DeviceSet
						+--	AirConditions (hier beginnt das eigene Modell)
								+--	C	(ANSI-C-Variante)
										+--	BedRoom
										|		+--	SetOperationMode (Methode)
										|		+-- Act (Ist-Werte)
										|		|		+--	FanLevel
										|		|		+--	OperationMode
										|		|		+--	Temperature
										|		+--	Name (Name der Instanz)
										|		+--	Set (Soll-Werte)
										|				+--	FanLevel
										|				+--	Temperature
										+--	Corridor
										|		+-- ...
										+--	LivingRoom
												+-- ...
			
	Dieser Zweig des Modells musste in einem externen Modeler-Tool definiert werden. Momentan gibt es keine
	Möglichkeit, dies im AS zu tun. Hier wurde das Tool "UaModeler" der Fa. Unified Automation verwendet.
	Hinweis: Die übliche Praxis sieht vor, Datentypen und Instanzen der Knoten jeweils in separaten Modellen
	zu halten. Der Einfachkeit halber wurde in diesem Beispiel alles in ein Modell gepackt.
	Diese neuen Knoten können über das von der Foundation standardisierte Opc-Export-Format "nodeset" ins AS
	importiert werden. Dies geschieht im AS in der Configuration View unter dem Zweig
	"../PC/Connectivity/OpcUA/". Für dieses Beispiel ist es die Datei "aircondmodel.uanodeset", welche aus
	dem externen Model-Tool exportiert wurde.
	Diese neuen Knoten haben von sich aus aber keine Werte, sie hängen praktisch "in der Luft". Deshalb gibt es
	die Möglichkeit, solche Knoten an bereits bestehende B&R-Knoten zu "mappen" und diese so mit derselben
	Funktionalität zu versehen wie der gemappte Knoten.
	Dieses Mapping geschieht durch OpcUa-Referenzen. B&R hat hierzu eigene Referenz-Typen implementiert.
	Variablen:
		Durch die Referenz "BrHasValueAttribute" kann ein Knoten auf einen bestehenden Variablen-Knoten aus dem
		B&R-Modell gemappt werden. 
	Methoden:
		Analog dazu gibt es die Referenz "BrHasImplementation", mit der auf einen bestehenden Methoden-Knoten aus dem
		B&R-Modell gemappt werden kann.
	Dies bedeutet für den B&R-Server, diesen neuen Knoten genauso zu behandeln wie den gemappten Knoten.
	
	Mapping:
		Bis AS4.6 musste das Setzen der Vorwärts-Referenzen ebenfalls im externen Modeler-Tool gemacht werden. 
		Ab AS4.7 ist es möglich, eine Rückwärts-Referenz aus dem B&R-Modell ins neu importierte eigene Modell zu setzen.
		Dies hat den Vorteil, dass das externe Modell für das Mapping nicht mehr geändert werden muss.
		Beim Kompilieren des Projekts werden dann automatisch die Vorwärts-Referenzen für die Knoten im externen
		Modell gebildet.
		Das Setzen der Rückwärts-Referenzen geschieht in der Datei 'OpcUaMap.uad', in dem auch alle sonstigen Knoten-
		Einstellungen gemacht werden.
		
		Zuerst müssen die im externen Modell verwendeten Namespaces angegeben werden. Dies geschieht in den
		Eigenschaften	des obersten Knotens 'Default View'. Hier gibt es eine Liste 'Namespaces URIs', welche von Haus
		aus die vom	B&R-Modell verwendeten Namespaces enthält. Die Liste muss nun mit den im eigenen Modell verwendeten
		Namespaces erweitert werden. In unserem Fall ist dies nur einer mit dem Namen
		'http://br-automation.com/AirCondModel/' (so wurde es im externen Model definiert) mit dem Namespace-Index 5.
		
		Zum Mappen der Knoten gibt es jetzt einen Parameter 'Reference/Value Attribute Of' für Variablen-Knoten und
		'Reference/Implementation Of' für Methoden-Knoten in den Eigenschaften des Knotens. Hier muss textuell die
		NodeId auf den zu mappenden Knoten des eigenen Modells gesetzt werden (z.B.
		'ns=5;i=6041'). Dadurch wird der Knoten des externen Modells genauso behandelt wie der Knoten im B&R-Modell. 
		Als Namespace-Index muss der aus der obigen Liste verwendet werden. Achtung: Der Namespace-Index wird vom
		Server zur Laufzeit automatisch neu vergeben.
	
	Namespace-Indizes bei Verwendung eigener/externer Modelle:
		Namespace-Uri's von externen Modellen müssen angegeben werden. Bei der Parametrierung von Referenzen im AS muss
		der Namespace-Index dieser Liste angegeben werden (siehe oben).
		Die in dieser Liste angegebenen Indizes sind NICHT die zur Laufzeit verwendeten Namespace-Indizes!
		Zur Laufzeit werden die Namespaces erneut zusammengeführt und erhalten so andere Namespace-Indizes!
		In unserem Beispiel liegt der neue Namespace 'http://br-automation.com/AirCondModel/' auf dem Namespace-
		Index 6. Der Namespace-Index des B&R-Modells verschiebt sich daher auf 7! Dies muss bei allen Verwendungen
		von NodeId's/Browsepfaden auf das B&R-Modell berücksichtigt werden, auch bei allen externen Clients!
		In diesem Beispiel-Projekt war es daher nötig, die Browse-Pfade bei der Konfiguration des OpcUaAny-Clients
		anzupassen.
		Diese Verschiebung des B&R-Namespace-Index durch externe Modelle wird in einer der nächsten	AS-Versionen behoben
		sein, so dass der B&R-Index auf 6 bleiben wird.

	Erleichterung gegenüber AS4.6	
		Damit im externen Modell die Vorwärts-Referenzen gesetzt werden konnten (bis AS4.6), musste das vom AS
		erzeugte B&R-Modell in das Modeler-Tool importiert werden. Dies war zwar sehr einfach, jedoch konnte ein einmal
		importiertes B&R-Modell nicht ohne weiters nochmals importiert werden, wenn sich dieses geändert hatte. 
		Durch das Setzen der Referenzen im AS4.7 braucht das B&R-Modell gar nicht mehr im UaModeler importiert zu
		werden.

	Verwendung von Datentypen/Enumerationen im externen Modell:
		Dass das B&R-Modell im Modeler-Tool nicht bekannt ist, hat aber auch einen Nachteil: Im B&R-Projekt definierte
		Datentypen und Enumerationen sind dann im externen Modell nicht bekannt und können damit auch nicht in den
		neuen Knoten verwendet werden.
		In unserem Beispiel betrifft das die zwei Enumerationen:
		
			AirCondOperationMode_ENUM
				Dies ist die Aufzählung der Betriebsmodi für eine Klima-Anlage:
					eAC_OPERATIONMODE_OFF						0
					eAC_OPERATIONMODE_MANUAL				1
					eAC_OPERATIONMODE_AUTO					2
				Sie wird beim Modell benötigt für:
					-Variable 'Act.OperationMode'
					-Eingangs-Argument bei Methode 'SetOperationMode'
					-Felder des Events 'AirConditionOperationModeChanged'
				Natürlich könnten diese Knoten im externen Modell als Int32 deklariert werden, was aber den Vorteil einer
				Enumeration unter OpcUa zunichte macht:
					-Anzeige von Texten anstatt Zahlen
					-Definierte Grenzen (0..2) bei der Eingabe
				Um die Vorteile einer Enumeration trotzdem zu nutzen, ohne das B&R-Modell zu importieren, wurde folgende
				Alternative gewählt: Im externen Modell wurde ein eigener Enumerations-Datentyp angelegt, der der
				Definition im B&R-Projekt entspricht. Unter dem Pfad 'Root/Types/DataTypes/BaseDataType/Enumeration/' gibt
				es nun den Enumerations-Knoten 'AirConditionOperationModeType', der folgende Elemente enthält:
					Off															0
					Manual													1
					Automatic												2
				Dieser wird nun als Datentyp für die Variablen/Argumente/Felder verwendet.
			
			AirCondMethodStatus_ENUM
				Dies ist die Aufzählung für den Status einer 'SetOperationMode'-Methode:
					eAC_METH_STATUS_OK							0
					eAC_METH_STATUS_INVALID_OPMODE	1
				Sie wird beim Modell benötigt für das Ausgangs-Argument bei Methode 'SetOperationMode'.
				Auch hier wurde dieselbe Alternative gewählt: Im externen Modell wurde ein eigener Enumerations-Datentyp
				angelegt, der der	Definition im B&R-Projekt entspricht. Unter dem Pfad 
				'Root/Types/DataTypes/BaseDataType/Enumeration/' gibt	es nun den Enumerations-Knoten
				'AirConditionMethodStatusType', der folgende Elemente enthält:
					Ok															0
					InvalidOperationMode						1
				Dieser wird nun als Datentyp für das Argument verwendet.
				
			Übrigens ist dies eine übliche Praxis: Die im Fremd-Modell angelegten Datentypen und Enumerationen sind
			auf der Sps 'nachgebaut' und umgekehrt.
	
	Ordner 'UaModeler'
		In diesem Ordner des Packages sind die Dateien enthalten, welche für das externe Model-Tool benötigt werden
		(siehe ReadMe.txt im Ordner).

	Der Vorteil dieses OpcUa-Konzepts ist, dass damit benutzerdefinierte Hierarchien im Address-Raum möglich sind,
	die Funktionalität hinter den einzelnen Knoten aber ganz einfach über das bereits bestehende B&R-Modell
	abgebildet werden kann.
	Ebenso können von anderen Institutionen zur Verfügung gestellte Modelle ganz einfach verwendet werden, z.B. das
	Modell einer von der Opc-Foundation erstellten Companion Specification. Solche CS werden von der Opc-Foundation
	in Zusammenarbeit mit Industrie-Verbänden und Dach-Institutionen erstellt und haben das Ziel, die Schnittstelle
	bestimmter Maschinen international zu standardisieren.
	Es sind mittlerweile sehr viele solcher Companion Specifications und deren Modelle erhältlich. Z.B. gibt es für
	Injektions-Maschinen die Companion Specification 'EuroMap' sowie die zugehörigen Modelle.
	
	
	