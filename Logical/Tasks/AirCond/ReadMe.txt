
Mit diesem Beispiel wird verdeutlicht, wie eigene oder extern definierte OpcUa-Modelle eingesetzt werden k�nnen.
	Hinweis: Um die implementierten Modelle zu betrachten und besser zu verstehen, sollte mit einem Test-Client
	(z.B. UaExpert oder RnCommTest) eine Verbindung aufgebaut und der Adress-Raum gebrowst werden.

Erkl�rung der Task-Funktionalit�t:
	Als funktionelles Beispiel dient die Implementierung mehrerer Instanzen einer Klima-Anlage.
	Es gibt einen Typ Klima-Anlage, dessen Daten in der Struktur "AirCond_TYP" aufgelegt sind:
		AirCond_TYP
			sName																	Name der Instanz
			Act																		Ist-Werte
				eOperationMode											Betriebs-Modus (0=Aus, 1=Manuell, 2=Automatik)
				rTemperature												Ist-Temperatur in [�C]
				nFanLevel														Ist-L�fter-Stufe (0-5, 0=Aus)
			Set																		Soll-Werte
				rTemperature												Soll-Temperatur in [�C] f�r Automatik
				nFanLevel														Soll-L�fter-Stufe (0-5, 0=Aus) f�r Manuell

	Es gibt drei Instanzen: Schlafzimmer, Flur und Wohnzimmer. F�r jede dieser Instanzen werden die
	entsprechenden Funktionen "Init", "Operate" und "Simulation" aufgerufen. Das bedeutet, dass der
	Code einer Klima-Anlage nur einmal vorhanden ist und �nderung daran nur an einer Stelle gemacht
	werden m�ssen.
	Jede dieser Instanzen ist im OpcUa-Model mit entsprechenden Rechten freigegeben (siehe Configuration View
	unter "../PC/Connectivity/OpcUA/OpcUaMap.uad").
	Zus�tzlich gibt es f�r jede Klima-Anlagen-Instanz auch noch eine Struktur-Variable "AirCondIntern_TYP". Sie
	enth�lt Elemente, die als Variablen f�r die interne Behandlung einer Instanz n�tig sind (z.B. 
	Schrittketten-Z�hler), welche aber nicht �ber OpcUa freigegeben sind.
	
	Hier nun die Beschreibung der einzelnen Funktionen, welche f�r jede Instanz aufgerufen werden:
	Init: Die Werte einer Instanz werden hier vorbesetzt.

	Steuerung:
		Betriebsmodus:
			Aus:
				Der L�fter bleibt ausgeschaltet (Stufe=0).
			Manuell:
				Der L�fter wird auf die im Sollwert angegebene Stufe gesetzt.
			Automatik:
				Die L�fter-Stufe wird aufgrund der prozentualen Abweichung zwischen Ist- und Soll-Wert gesetzt.
		Ausserdem wird hier in einer Schrittkette der Methoden-Aufruf f�r "SetOperationMode" behandelt.
		Es gibt auch eine Schrittkette, die das Feuern eines Events beim �ndern des Betriebsmodus behandelt.

	Simulation:
		Die Ist-Temperatur wird st�ndig erh�ht und dr�ngt dadurch auf 26.0�C.
		Je nach L�fter-Stufe wird die Ist-Temperatur abgesenkt und wirkt dadurch der nat�rlichen
		Erw�rmung entgegen.
		Die Ist-Temperatur wird auf den Bereich 15.0 - 26.0�C begrenzt, um ein Abdriften zu verhindern.
					
	OpcUa-Methode "SetOperationMode":
		Die Methode setzt den Betriebsmodus, welcher als einziges Eingangs-Argument �bergeben wird.
		Als Ausgangs-Argument wird ein applikativer Status zur�ckgegeben, welcher auf einen ung�ltigen
		Betriebsmodus hinweisen kann (dies ist eigentlich nicht m�glich, da der Betriebsmodus als Enumeration
		aufgelegt ist).

	OpcUa-Event "AirConditionOperationModeChanged":
		Bei jeder �nderung des Betriebsmodus wird ein Event gefeuert, welches als zus�tzliche Felder die 
		Informationen 'OldOperationMode' und 'NewOperationMode' besitzt.

OpcUa-Methode(n) "SetOperationMode":
	In "Methods.uam" ist f�r jede Instanz jeweils die Methode "SetOperationMode" deklariert. So wird garantiert,
	dass bei jeder Instanz diese Methode gleichzeitig zu den anderen Instanzen aufgerufen werden kann.
	Die Schrittkette f�r diese Methode ist nur einmal implementiert und wird f�r jede Instanz einzeln aufgerufen
	(siehe oben).
	
OpcUa-Event(s) "AirConditionOperationModeChanged":
	Dieses Event wurde eigens f�r dieses Beispiel modelliert und ist im Fremd-Modell hinterlegt (siehe 
	'/Root/Types/EventTypes/BaseEventType/AirConditionOperationModeChanged').
	Normalerweise (wie auch hier) k�nnen alle am Server gefeuerten Events durch Abonnierung des Knotens
	'/Root/Objects/Server' (i=2253)	von einem Client empfangen werden. In dieses Beispiel wurde eine zus�tzliche
	M�glichkeit implementiert:
	Auch der Instanz-Knoten einer Klima-Anlage im Fremd-Modell (z.B. 'BedRoom') soll abonniert werden k�nnen,
	aber nur das Event der betreffenden Instanz feuern.
	Der meiste Teil dieser Anforderung muss im Modeller umgesetzt werden. Im Sps-Programm ist nur eines wichtig:
	Beim Feuern des Events muss das Feld 'SourceNode' applikativ mit der NodeId des Hauptknotens besetzt werden
	(also z.B. 'ns=6;i=5013' f�r 'BedRoom' in der ANSI-C-Variante).
	Hinweis: Ob ein Knoten Events feuern und deswegen abonniert werden kann, l�sst sich sehr leicht mit dem
	Attribut 'EventNotifier' des Knotens pr�fen. Es ist bitcodiert. Ist Bit#0 (=SubscribeToEvents) gesetzt,
	so kann der Knoten auf Events abonniert werden.

OpcUa-Modelle:
	Im B&R-Modell, das automatisch vom Compiler erzeugt und vom OpcUa-Server ver�ffentlicht wird, werden die
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
		
	Es kann nun aber eine andere Hierarchie der Knoten gew�nscht sein. In diesem Beispiel soll die Vorgabe
	sein, dass es jeweils einen Knoten pro Instanz gibt, der die Daten und die dazugeh�rige Methode enth�lt.
	Dieser Knoten soll auch das Event feuern k�nnen. Auch die Namen der Knoten sollen anders sein (keine
	Pr�fixe).
	Dazu wurde ein eigenes Modell definiert, das diese Vorgaben erf�llt. Da	dieses Beispiel Tasks sowohl f�r
	ANSI-C als auch f�r StructureText enth�lt, wurde auch im Modell diese	Aufteilung ber�cksichtigt. Hier das
	Modell f�r ANSI-C:
	
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
	M�glichkeit, dies im AS zu tun. Hier wurde das Tool "UaModeler" der Fa. Unified Automation verwendet.
	Hinweis: Die �bliche Praxis sieht vor, Datentypen und Instanzen der Knoten jeweils in separaten Modellen
	zu halten. Der Einfachkeit halber wurde in diesem Beispiel alles in ein Modell gepackt.
	Diese neuen Knoten k�nnen �ber das von der Foundation standardisierte Opc-Export-Format "nodeset" ins AS
	importiert werden. Dies geschieht im AS in der Configuration View unter dem Zweig
	"../PC/Connectivity/OpcUA/". F�r dieses Beispiel ist es die Datei "aircondmodel.uanodeset", welche aus
	dem externen Model-Tool exportiert wurde.
	Diese neuen Knoten haben von sich aus aber keine Werte, sie h�ngen praktisch "in der Luft". Deshalb gibt es
	die M�glichkeit, solche Knoten an bereits bestehende B&R-Knoten zu "mappen" und diese so mit derselben
	Funktionalit�t zu versehen wie der gemappte Knoten.
	Dieses Mapping geschieht durch OpcUa-Referenzen. B&R hat hierzu eigene Referenz-Typen implementiert.
	Variablen:
		Durch die Referenz "BrHasValueAttribute" kann ein Knoten auf einen bestehenden Variablen-Knoten aus dem
		B&R-Modell gemappt werden. 
	Methoden:
		Analog dazu gibt es die Referenz "BrHasImplementation", mit der auf einen bestehenden Methoden-Knoten aus dem
		B&R-Modell gemappt werden kann.
	Dies bedeutet f�r den B&R-Server, diesen neuen Knoten genauso zu behandeln wie den gemappten Knoten.
	
	Mapping:
		Bis AS4.6 musste das Setzen der Vorw�rts-Referenzen ebenfalls im externen Modeler-Tool gemacht werden. 
		Ab AS4.7 ist es m�glich, eine R�ckw�rts-Referenz aus dem B&R-Modell ins neu importierte eigene Modell zu setzen.
		Dies hat den Vorteil, dass das externe Modell f�r das Mapping nicht mehr ge�ndert werden muss.
		Beim Kompilieren des Projekts werden dann automatisch die Vorw�rts-Referenzen f�r die Knoten im externen
		Modell gebildet.
		Das Setzen der R�ckw�rts-Referenzen geschieht in der Datei 'OpcUaMap.uad', in dem auch alle sonstigen Knoten-
		Einstellungen gemacht werden.
		
		Zuerst m�ssen die im externen Modell verwendeten Namespaces angegeben werden. Dies geschieht in den
		Eigenschaften	des obersten Knotens 'Default View'. Hier gibt es eine Liste 'Namespaces URIs', welche von Haus
		aus die vom	B&R-Modell verwendeten Namespaces enth�lt. Die Liste muss nun mit den im eigenen Modell verwendeten
		Namespaces erweitert werden. In unserem Fall ist dies nur einer mit dem Namen
		'http://br-automation.com/AirCondModel/' (so wurde es im externen Model definiert) mit dem Namespace-Index 5.
		
		Zum Mappen der Knoten gibt es jetzt einen Parameter 'Reference/Value Attribute Of' f�r Variablen-Knoten und
		'Reference/Implementation Of' f�r Methoden-Knoten in den Eigenschaften des Knotens. Hier muss textuell die
		NodeId auf den zu mappenden Knoten des eigenen Modells gesetzt werden (z.B.
		'ns=5;i=6041'). Dadurch wird der Knoten des externen Modells genauso behandelt wie der Knoten im B&R-Modell. 
		Als Namespace-Index muss der aus der obigen Liste verwendet werden. Achtung: Der Namespace-Index wird vom
		Server zur Laufzeit automatisch neu vergeben.
	
	Namespace-Indizes bei Verwendung eigener/externer Modelle:
		Namespace-Uri's von externen Modellen m�ssen angegeben werden. Bei der Parametrierung von Referenzen im AS muss
		der Namespace-Index dieser Liste angegeben werden (siehe oben).
		Die in dieser Liste angegebenen Indizes sind NICHT die zur Laufzeit verwendeten Namespace-Indizes!
		Zur Laufzeit werden die Namespaces erneut zusammengef�hrt und erhalten so andere Namespace-Indizes!
		In unserem Beispiel liegt der neue Namespace 'http://br-automation.com/AirCondModel/' auf dem Namespace-
		Index 6. Der Namespace-Index des B&R-Modells verschiebt sich daher auf 7! Dies muss bei allen Verwendungen
		von NodeId's/Browsepfaden auf das B&R-Modell ber�cksichtigt werden, auch bei allen externen Clients!
		In diesem Beispiel-Projekt war es daher n�tig, die Browse-Pfade bei der Konfiguration des OpcUaAny-Clients
		anzupassen.
		Diese Verschiebung des B&R-Namespace-Index durch externe Modelle wird in einer der n�chsten	AS-Versionen behoben
		sein, so dass der B&R-Index auf 6 bleiben wird.

	Erleichterung gegen�ber AS4.6	
		Damit im externen Modell die Vorw�rts-Referenzen gesetzt werden konnten (bis AS4.6), musste das vom AS
		erzeugte B&R-Modell in das Modeler-Tool importiert werden. Dies war zwar sehr einfach, jedoch konnte ein einmal
		importiertes B&R-Modell nicht ohne weiters nochmals importiert werden, wenn sich dieses ge�ndert hatte. 
		Durch das Setzen der Referenzen im AS4.7 braucht das B&R-Modell gar nicht mehr im UaModeler importiert zu
		werden.

	Verwendung von Datentypen/Enumerationen im externen Modell:
		Dass das B&R-Modell im Modeler-Tool nicht bekannt ist, hat aber auch einen Nachteil: Im B&R-Projekt definierte
		Datentypen und Enumerationen sind dann im externen Modell nicht bekannt und k�nnen damit auch nicht in den
		neuen Knoten verwendet werden.
		In unserem Beispiel betrifft das die zwei Enumerationen:
		
			AirCondOperationMode_ENUM
				Dies ist die Aufz�hlung der Betriebsmodi f�r eine Klima-Anlage:
					eAC_OPERATIONMODE_OFF						0
					eAC_OPERATIONMODE_MANUAL				1
					eAC_OPERATIONMODE_AUTO					2
				Sie wird beim Modell ben�tigt f�r:
					-Variable 'Act.OperationMode'
					-Eingangs-Argument bei Methode 'SetOperationMode'
					-Felder des Events 'AirConditionOperationModeChanged'
				Nat�rlich k�nnten diese Knoten im externen Modell als Int32 deklariert werden, was aber den Vorteil einer
				Enumeration unter OpcUa zunichte macht:
					-Anzeige von Texten anstatt Zahlen
					-Definierte Grenzen (0..2) bei der Eingabe
				Um die Vorteile einer Enumeration trotzdem zu nutzen, ohne das B&R-Modell zu importieren, wurde folgende
				Alternative gew�hlt: Im externen Modell wurde ein eigener Enumerations-Datentyp angelegt, der der
				Definition im B&R-Projekt entspricht. Unter dem Pfad 'Root/Types/DataTypes/BaseDataType/Enumeration/' gibt
				es nun den Enumerations-Knoten 'AirConditionOperationModeType', der folgende Elemente enth�lt:
					Off															0
					Manual													1
					Automatic												2
				Dieser wird nun als Datentyp f�r die Variablen/Argumente/Felder verwendet.
			
			AirCondMethodStatus_ENUM
				Dies ist die Aufz�hlung f�r den Status einer 'SetOperationMode'-Methode:
					eAC_METH_STATUS_OK							0
					eAC_METH_STATUS_INVALID_OPMODE	1
				Sie wird beim Modell ben�tigt f�r das Ausgangs-Argument bei Methode 'SetOperationMode'.
				Auch hier wurde dieselbe Alternative gew�hlt: Im externen Modell wurde ein eigener Enumerations-Datentyp
				angelegt, der der	Definition im B&R-Projekt entspricht. Unter dem Pfad 
				'Root/Types/DataTypes/BaseDataType/Enumeration/' gibt	es nun den Enumerations-Knoten
				'AirConditionMethodStatusType', der folgende Elemente enth�lt:
					Ok															0
					InvalidOperationMode						1
				Dieser wird nun als Datentyp f�r das Argument verwendet.
				
			�brigens ist dies eine �bliche Praxis: Die im Fremd-Modell angelegten Datentypen und Enumerationen sind
			auf der Sps 'nachgebaut' und umgekehrt.
	
	Ordner 'UaModeler'
		In diesem Ordner des Packages sind die Dateien enthalten, welche f�r das externe Model-Tool ben�tigt werden
		(siehe ReadMe.txt im Ordner).

	Der Vorteil dieses OpcUa-Konzepts ist, dass damit benutzerdefinierte Hierarchien im Address-Raum m�glich sind,
	die Funktionalit�t hinter den einzelnen Knoten aber ganz einfach �ber das bereits bestehende B&R-Modell
	abgebildet werden kann.
	Ebenso k�nnen von anderen Institutionen zur Verf�gung gestellte Modelle ganz einfach verwendet werden, z.B. das
	Modell einer von der Opc-Foundation erstellten Companion Specification. Solche CS werden von der Opc-Foundation
	in Zusammenarbeit mit Industrie-Verb�nden und Dach-Institutionen erstellt und haben das Ziel, die Schnittstelle
	bestimmter Maschinen international zu standardisieren.
	Es sind mittlerweile sehr viele solcher Companion Specifications und deren Modelle erh�ltlich. Z.B. gibt es f�r
	Injektions-Maschinen die Companion Specification 'EuroMap' sowie die zugeh�rigen Modelle.
	
	
	