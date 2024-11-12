
Unter Verwendung der Bibliothek 'AsOpcUac' ist hier das Beispiel eines Clients implementiert.

Allgemeine Konfiguration:
	Der Client baut automatisch nach dem Hochlauf der Sps die Verbindung zum Server auf. Die Variable 'bStartClient'
	ist im Init auf '1' gesetzt. Will man den Client nicht automatisch starten, kann diese Variable im Init auf '0' und
	dann im Watch auf '1' gesetzt werden.
	Verbunden wird auf den eigenen Server. Durch �nderung der Parameter kann aber auch auf einen externen Server verbunden
	werden.

	Der Ablauf sieht wie folgt aus:
		1. Aufbauen der Verbindung
		2. Ermitteln des NamespaceIndex f�r den Namespace der Foundation "http://opcfoundation.org/UA/"
		3. Ermitteln des NamespaceIndex f�r den Namespace von B&R-Variablen "http://br-automation.com/OpcUa/PLC/PV/"
		4. Anlegen einer Subscription f�r Variablen
		5. Ermitteln der NodeHandles f�r die Subscription
		6. Hinzuf�gen der MonitorItems
		7. Schleife auf 4. Wenn alle Var-Subscriptions angelegt sind, wird auf Punkt 8. gesprungen
		8. Anlegen einer Subscription f�r Events
		9. Ermitteln des NodeHandles f�r den EventNotifier-Knoten ns=0;i=2253 (Root/Objects/Server)
		10. Hinzuf�gen des EventItems mit den zu sendenden Feldern
		11. Ermitteln der NodeHandles f�r Read
		12. Ermitteln der NodeHandles f�r Write
		13. Ermitteln der Handles f�r Methoden
		14. Verbindungs-Abbruch pr�fen
		15. Alle 1000ms wird zu 16 gesprungen
		16. Lesen der Read-Werte
		17. Schreiben der Write-Werte
		18. Aufruf der Methode 'Calculate'
		19. Sprung auf 14.
			
	Variablen-Subscriptions:
		Es werden 3 Subscriptions mit je 4 MonitoredItems angelegt. Die Parameter der Subscriptions sind wie folgt vergeben:
		SubVar[0]:		PublishingInterval: 500ms					Priority: 200
		SubVar[1]:		PublishingInterval: 1000ms				Priority: 100
		SubVar[2]:		PublishingInterval: 2000ms				Priority: 50
		
		Im Beispiel f�r AS4.1 wird noch der FB 'UA_MonitoredItemAdd' verwendet.
		Ab AS4.2 ist der FB 'UA_MonitoredItemAddList' verf�gbar, der hier verwendet wird.
		Folgendes muss beachtet werden: Wenn der Parameter 'QueueSize' eines MonitoredItems gr��er als '0' gesetzt wird,
		MUSS f�r diese Subscription auch der FB 'UA_MonitoredItemOperateList' ZYKLISCH aufgerufen werden, sonst werden
		keine Werte auf die Variablen geschrieben!
		In diesem Beispiel ist QueueSize immer '0', so dass es auch ohne Operate funktioniert.
		Da diese Informationen in diesem Beispiel nicht ben�tigt werden, werden f�r die IN/OUT 'ValuesChanged',
		'RemainingValueCount', 'TimeStamps' und	'NodeQualityIds' des FB 'UA_MonitoredItemAddList' in jeder Subscription
		diesselben Arrays referenziert. Sollten diese Werte ben�tigt werden, so m�ssten	sie auf verschiedene Arrays
		gelegt werden.
		Abonniert werden alle Standard-Datentypen der Struktur 'ServerData::VarsLocal.ReadOnly'. Das INT-Array	wird nicht
		abonniert. Die empfangenen Werte werden in die lokale Struktur 'ClientXXX:ClientVarsSubscription' eingetragen.
	
	Event-Subscription:
		Es wird eine zus�tzliche Subscription angelegt, in der nur ein Item hinzugef�gt wird. Allerdings handelt es sich
		dabei nicht um ein MonitoredItem (also eine Variable), sondern um ein EventItem, um damit Events zu empfangen.
		Die Abonnierung muss auf einem Knoten erfolgen, dessen Attribut 'EventNotifier' auf '1=SubscribeToEvents' gesetzt
		ist. Damit teilt der Server mit, dass dieser Knoten Events feuern kann. Am OpcUa-Server der B&R-Sps gibt es 
		standardm�ssig nur einen solchen Knoten. Das ist ns=0;i=2253 (Root/Objects/Server). Mit ihm k�nnen alle Events des
		Servers abonniert	werden.
		Bei der clientseitigen Abonnierung wird dem Server ein Filter �bermittelt, der zwei Einstellungen enth�lt:
			1. Event-Typ
				Er ist als NodeId aufgelegt und enth�lt den Knoten, der das zu filternde Event angibt. Im Baum sind die
				m�glichen Typen ab 'Root/Types/EventTypes/' zu finden. Wird ein Knoten angegeben, werden dieser
				Typ und alle unterlagerten an den Client gesendet. Wird z.B. der Typ ns=0;i= 2041 (BaseEventType) angegeben,
				werden alle Events geschickt.
				In diesem Beispiel wird der Filter auf ns=0;i=11436 (ProgressEventType) gesetzt, da dieses Event im Task
				'ServerEvents' zyklisch gefeuert wird.
			
			2. Zu sendende Felder
				Die Felder, die der Server bei jedem Event mitsenden soll, sind als Array aufgelegt. Ein Array-Element enth�lt
				den relativen Browse-Pfad des Feldes. Besetzt werden muss nur die Struktur 'TargetName', wobei TargetName.Name
				den Namen des Feldes enth�lt.
				In diesem Beispiel sind folgende Felder angegeben:
					'EventId', 'EventType', 'LocalTime', 'Message', 'ReceiveTime', 'Severity', 'SourceName', 'SourceNode' und
						'Time' aus dem Typen 'BaseEventType'.
					'Context' und 'Progress' aus dem Typen 'ProgressEventType'
				F�r jedes dieser angemeldeten Felder muss eine Variable bereitgestellt werden, die vom Stack beim Empfangen
				eines Events mit dem jeweiligen Wert gef�llt werden kann. Dazu wird ein String-Array mit den Namen der Variablen
				�bergeben. Die Reihenfolge entspricht der Reihenfolge der Felder. Der Datentyp der Variable muss nat�rlich dem
				des Feldes entsprechen.
				
		Um nun das Empfangen eines Events applikativ verarbeiten zu k�nnen, muss zyklisch der Baustein 'UA_EventItemOperate'
		aufgerufen werden. Sobald dessen Ausgang 'EventProcessed' auf 1 geht, ist ein neues Event empfangen und die Feld-
		Variablen mit den gesendeten Werten besetzt worden.
		In diesem Beispiel sind die Feld-Variablen in der Struktur 'ReceivedEvent' enthalten.
		Beim Erkennen eines neuen Events werden applikativ zwei Dinge getan. Zum einen wird zu Diagnosezwecken der Z�hler
			'ReceivedEvent.nReceivedCount' hochgez�hlt. Zum anderen wird die als Byte-Array empfangene EventId zu einem
			Hex-String gewandelt, um sie so besser anzeigen zu k�nnen.
		
		Hinweis: Auch Audit-Events k�nnen mit diesem Konzept empfangen werden. Der Server sendet Audit-Events aber nur, wenn
			eine verschl�sselte Verbindung aufgebaut ist.
		Hinweis: Weitere Informationen zu Events und Felder siehe ReadMe des Tasks 'ServerEvents'.

	Read:
		Alle 1000ms werden Werte gelesen.
		Gelesen werden von der Struktur 'ServerData:VarsLocal.ReadOnly' jeweils die Elemente 'nUdint', 'nDint' und
		'anInt' (Array) und in die entsprechenden Elemente der lokalen Struktur 'ClientXXX:ClientVarsRead' eingetragen.
		Achtung: Zyklisches Lesen (Polling) sollte niemals in einer Applikation implementiert werden! Stattdessen sollte
		unbedingt Subscription verwendet werden. Dieses Beispiel soll lediglich die Besetzung des FB's veranschaulichen.
		
	Write:
		Alle 1000ms werden Werte geschrieben.
		Geschrieben werden die oben gelesenen Elemente von der lokalen Struktur 'ClientXXX:ClientVarsRead' auf 
		'ServerData::WriteXXX'.

	Method 'Calculate'
		Alle 1000ms wird die Methode aufgerufen.
		Die Eingangs-Argumente werden vor dem Aufruf in der lokalen Struktur 'MethCalculateArgs.In' bef�llt.
		Nach dem Aufruf sind die Ausgangs-Argumente in der lokalen Struktur 'MethCalculateArgs.Out' abgelegt.
	
	NamespaceUri und NamespaceIndex:
		Normalerweise w�rde die NamespaceUri verwendet, um einen Knoten zu adressieren. Da aber die �bertragung eines
		Texts bei jedem Zugriff zu unperformant w�re, wird bei OpcUa der NamespaceUri in einen ebenso eindeutigen
		NamespaceIndex gewandelt.
		Achtung: Der NamespaceIndex ist nicht statisch und muss folglich nach jedem Verbingungsaufbau mit
		'UA_GetNamespaceIndex' ermittelt werden!
		Jeder Knoten k�nnte theoretisch in einem anderen Namespace untergebracht sein. Weil beim B&R-Server die Variablen 
		aber alle im selben Namespace sind,	wird hier der Index nur einmal ermittelt und f�r jedes Item verwendet.
		Ab AS4.3 ist die NamespaceUri bei B&R ge�ndert worden:
			AS					Version			NamespaceUri
			<=AS4.2			V1.0				urn:B&R/pv/
			>=As4.3			V2.0				http://br-automation.com/OpcUa/PLC/PV/
		Um kombatibel zu �lteren Versionen zu bleiben, kann ab AS4.3 die Modell-Version in der System-
		Konfiguration eingestellt werden.
		Ursache der �nderung: Manche OpcUa-Clients von Fremdherstellern hatten Probleme mit dem '&' im Namespace.

	Verbindungsabbruch:
		Bricht die Verbindung zum Server ab (z.B. durch Abstecken eines Kabels oder Neustart des Servers) und kehrt wieder,
		kann das Betriebssystem automatisch die Verbindung komplett (mit Subscriptions + MonitoredItems) wieder
		restaurieren. Der Task �berpr�ft lediglich, ob die Verbindung wiedergekehrt ist. 	

	Fehler:
		In der Struktur 'Step' wird der zuletzt aufgetretene Fehler gespeichert sowie der Schritt, in dem der Fehler
		aufgetreten ist, ausserdem optional der	Index der Subscription bzw. des Items.
		Bei manchen Fehlern kann trotzdem weiter gearbeitet werden. Wenn zum Beispiel die Parameter eines MonitoredItems
		falsch sind, k�nnen die restlichen trotzdem angelegt werden.
		Auf den Schritt 'eSTEP_PAR_ERROR' wird nur dann gesprungen, wenn ein Fehler auftritt, bei dem die Schrittkette
		aufgrund eines falschen Parameters nicht weitergef�hrt werden kann. Dieser Parameter muss dann unbedingt berichtigt
		werden, weil sonst der Client nicht arbeitet.

	Server-Diagnose:
		Das Ermitteln von Server-Diagnose-Daten (z.B. wie viele und welche Clients verbunden sind) ist hier nicht implementiert.
		Zwar k�nnte dies auch hier gemacht werden, da	dazu nur die Abonnierung bestimmter Knoten n�tig ist. Da diese aber komplexe
		Datentypen mit dynamischen Arrays haben, welche bequemerweise schon in der Bibliothek "BrbLibUa" vordefiniert sind, ist das
		Beispiel dazu auch im Task 'BrbUa' implementiert. Au�erdem k�nnen interessante Informationen dazu in der Hilfe der
		Bibliothek nachgelesen werden.
