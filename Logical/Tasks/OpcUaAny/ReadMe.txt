
Der OpcUaAny-Client ist als HW-Modul an der Ethernet-Schnittstelle eingefügt.
Er repräsentiert einen Server als IO-Modul und wird auch als 'normales' IO-Modul parametriert. Bedient
wird er automatisch durch einen im Betriebssystem integrierten Client.

Allgemeine Konfiguration:
	Die Einstellung 'Module supervised' sollte auf 'off' stehen. Sie verhält sie genauso wie bei jedem anderen
	IO-Modul. Das bedeutet, wenn sie auf 'on' steht und das Modul (also der Server) nicht erreicht wird, geht
	die SPS in den ServiceMode!
	Durch die Einstellung 'Server Diagnostics' werden Diagnose-Werte zur Verfügung gestellt, welche auf
	Variablen gemappt werden können (siehe IO-Mapping).
	Bei den Security-Einstellungen ist die SSL-Config angegeben, welche auch schon für den Lib-Client verwendet 
	wird (Zertifikat mit 50 Jahren Laufzeit). Auch hier gilt: Wenn kein Zertifikat angegeben wird, wird 
	automatisch eines mit einer Laufzeit von 10 Jahren angelegt.
	Ausserdem ist hier der Benutzer eingestellt, mit dem sich der Client am Server anmeldet.
	
Kanal-Konfiguration:
	Es wurden für dieses Beispiel je 3 Eingangs- und 3 Ausgangs-Kanäle angelegt. Eingänge dienen dem Lesen vom
	Server (genauer gesagt Abonnieren als MonitoredItems in Subscription(s)), Ausgänge dienen dem zyklischen
	Schreiben auf den Server.

	Zum Angeben des Knotens wird dabei nicht wie im Lib-Client eine NodeId verwendet, sondern die Einstellung
	'Browse path', welche eine alternative Addressierung darstellt. Sie muss den korrekten Browse-Pfad des zu
	addressierenden Knotens enthalten.
	Er besteht aus einzelnen Elementen, welche durch '/' getrennt sind und jeweils einen Knoten der Hierarchie
	darstellen. Ein Element enthält den Wert des Attributs 'BrowseName' des Knotens. Dieser wiederum besteht aus dem
	Namespace-Index und dann durch Doppelpunkt getrennt dem Knotennamen. Um Sonderzeichen trotzdem auch im
	eigentlichen Namen verwenden zu können, werden diese innerhalb des Pfades mit einem '&' als Prefix gekennzeichnet.
	Folgende Sonderzeichen werden gekennzeichnet:
		Zeichen			Ersetzung
		&						&&
		!						&!
		#						&#
		:						&:
		>						&>
		<						&<
		.						&.
		/						&/
		
	Somit ergibt z.B. bei B&R folgender Browse-Pfad:
	/0:Root/0:Objects/4:PLC/4:Modules/7:&:&:/7:OpcUaAny/7:Data/7:Read/7:Server/7:nUsint
	|																	|				|						|
	|																	|				|						+---	Ab hier beginnt der Variablenname
	|																	|				+---------------	Hier steht der Taskname
	|																	+-----------------------	Die : des Namens werden mit Präfix '&' gekennzeichnet
	+---------------------------------------------------------	Dies ist der Beginn des hierarchischen Address-Baums
																															Er ist bei B&R immer gleich

	Bei Fremd-Herstellern anderer Server kann der Pfad anders lauten.
	Im Zweifelsfalle können die BrowseNames der einzelnen Knoten durch einen generischen Client wie z.B.
	'UAExpert' (frei im Internet erhältlicher Windows-UA-Client) herausgefunden werden.
	
IO-Mapping:
	Standard-Kanäle
		ModuleOk
			Verhält sich wie bei einem normalen IO-Modul: Wenn der Server nicht erreichbar ist oder die Verbindung
			abbricht, geht dieser Kanal auf 'False'. Sobald die Verbindung besteht, ist er 'True'.
		ConnectionLostCount, ClientErrorCount und LastClientError
			Immer vorhandene Diagnose-Datenpunkte. Wenn ein Parametrier-Fehler vorliegt (z.B. falscher Browse-Pfad), kann
			dies an 'LastClientError' gesehen werden.
		ServerViewCount, CurrentSessionCount usw.
			Nur dann vorhandene Diagnose-Datenpunkte, wenn die Einstellung 'Server Diagnostics' auf 'on' steht.
		
	Benutzerdefinierte Kanäle
		Hier können die Kanäle gemappt werden, welche in der Konfiguration parametriert wurden.
	
	Wichtig: Eine zu mappende Variable muss den zum Datenpunkt passenden Datentyp haben!
	
Variablen in diesem Beispiel
	Der Task 'OpcUaAny' ist in diesem Beispiel nur vorhanden, um Variablen bereit zu stellen, welche an die
	Datenpunkte gemappt werden können.
	
	Eingänge:
		Die Elemente der Struktur 'Data.Read.Server' werden im Task inkrementiert und vom Client abonniert. Die
		empfangenen Werte werden auf die Struktur 'Data.Read.Client' geschrieben.

	Ausgänge:
		Die Elemente der Struktur 'Data.Write.Client' werden im Task inkrementiert und vom Client geschrieben.
		Serverseitig addressiert sind dabei die Elemente der Struktur 'Data.Write.Server'.
	
Verbindungsabbruch
	Wie schon beim Lib-Client wird auch hier nach einem Verbindungsabbruch die gesamte Kommunikation wieder
	automatisch restauriert. Ob eine Verbindung besteht, kann über den Eingangs-Kanal 'ModuleOk' abgefragt werden.
