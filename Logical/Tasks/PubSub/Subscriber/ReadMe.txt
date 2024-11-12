Hier wird die Konfiguration des Subscribers erkl�rt.

	Die Konfiguration ist in der Datei 'UaPubSub.uaPubSub' unter 'ConfigurationView/ArSim/PC/Connectivity/OpcUA' enthalten.
	Hier k�nnen theoretisch beliebig viele Subscriber konfiguriert werden.
	Achtung: Einige der Parameter werden nur angezeigt, wenn die erweiterte Parameter-Ansicht in der Symbol-Leiste angehakt ist!
	
	In diesem Beispiel ist ein Subscriber konfiguriert, alle Daten des eigenen Publishers empfangen k�nnte.
	Hierarchischer Aufbau und wichtige Parameter:
		+	ExampleSubscriber									Ist gleichzeitig der Name der Subscriber-Konfiguration. Dient nur der Unterscheidung
		|																			zu anderen Elementen. Es kann beliebig viele Konfigurationen geben.
		+-	Publisher ID										Dieser Parameter gilt nur f�r die WriterGroups einer Publisher-Konfiguration, ist also
		|																			f�r diese Subscriber-Konfiguration nicht wichtig.
		+-	Network interface								Auswahl der Ethernet-Schnittstelle, an der gehorcht wird.
		+-+	Address													
		|	+-	IP address										Angabe der Multicast-Ip, auf die gehorcht wird.
		|	+-	Port number										Angabe des Ports, auf den gehorcht wird.
		+-+	ReaderGroups										Es kann beliebig viele ReaderGroups geben.
		  +-+	DataSetReader									Es kann beliebig viele Reader innerhalb einer ReaderGroup geben.
		  	+-	Name												Der Name dient nur der Unterscheidung zu anderen Elementen.
				+-	Publisher ID								Dieser Parameter wird zur Filterung der empfangenen Messages herangezogen.
				+-	WriterGroup ID							Dieser Parameter wird zur Filterung der empfangenen Messages herangezogen.
		  	+-	DataSetWriter ID						Dieser Parameter dient der Unterscheidung der DataSets, wird aber bei B&R nicht zur Filterung herangezogen.
				+-+	Message settings
				| +-	Group version							Sollte der Group version der Publisher-Konfiguration entsprechen.			
				| +-	Network message number		Momentan immer 1.
				| +-	DataSet offset						Dieser Parameter gibt die Stelle an, an welcher die Daten dieses Readers in der
				|																	Message beginnen. Das Ermitteln dieses Parameters h�ngt von sehr vielen Optionen
				|																	des Publishers ab und ist daher sehr komplex. Am Besten sollte er durch Import der
				|																	Publisher-Konfiguration besetzt werden. Dann ist er auf jeden Fall richtig.
		  	+-+	SubscribedDataSet						Es gibt nur 1 DataSet pro Writer.
		  		+-	Name											Der Name dient nur der Unterscheidung zu anderen Elementen.
		  		+-+	DataSet field							Es kann mehrere Fields innerhalb des DataSets geben.
						+-	DataSet field name			Der Name dient nur der Unterscheidung zu anderen Elementen.
						+-	DataSet field ID				Dient einer zuk�nftigen Funktionalit�t.
						+-	Target variable					Gibt den Knoten im Adressraum an, auf den ein empfangener Wert geschrieben wird. Der
																				Datentyp des Knotens muss selbstverst�ndlich zum Datentyp des Fields passen.
																				Achtung: Der Knoten muss im Server-Adressraums freigegeben sein. Dabei ist es
																				unwichtig, welche Rechte f�r welche Rolle vergeben sind.

		Hier noch Informationen zu bestimmten Parametern:
			Field/FieldMetaData
				Diese Angaben k�nnen nicht per Hand ver�ndert werden, weil sie automatisch bei Auswahl des Targets gesetzt werden.
		
		Notwendigkeit von verschiedenen Elementen
			Eine eigene Konfiguration muss immer dann verwendet werden, wenn unterschiedliche Multicast-Ip oder Ports verwendet
				werden sowie wenn an verschiedenen Ethernet-Schnittstellen gehorcht werden soll. Aus diesem Grund wird in diesem
				Beispiel nur eine Subscriber-Konfiguration verwendet.
			Alle anderen Elemente m�ssen aus dem Publisher �bernommen werden.
			
		Filterung von Messages
			Theoretisch k�nnen sehr viele Multicast-Telegramme von verschiedenen Publishern an der Sps eintreffen.
			Durch die Parameter der Subscriber-Konfiguration wird die Filterung der uninteressanten Messages vorgenommen. Diese
			wird in zwei Stufen durchgef�hrt:
				1. Die Firmware der Ethernet-Schnittstelle filtert auf die generellen Parameter, also auf Network-Interface,
						Multicast-Ip-Adresse und Port. Nur Telegramme, die diesen Parametern entsprechen, werden an das Betriebssystem
						weitergeleitet.
				2. Das Betriebssystem filtert auf alle unterliegenden Parameter von ReaderGroups und Reader, also auf
						PublisherId und WriterGroupId. Nur wenn dieser Filter passiert wurde, werden die enthaltenen
						DataSets ausgewertet und deren Werte �bernommen.
			Daraus ergibt sich logischerweise: Wenn auch nur ein Parameter nicht mit den im gew�nschten Publisher parametrierten
			Wert �bereinstimmt, werden die Werte nicht �bernommen! Es empfiehlt sich daher, die Konfiguration des Subscribers am
			Besten �ber die Import-Funktion zu machen (siehe 'Import' unten).
		
		Tasks
			-Subscriber
				Dieser Task enth�lt keinen Code, sondern stellt nur die Variablen zur Verf�gung, auf welche die empfangenen Werte
				kopiert werden. 
				Hinweis: Es k�nnten auch globale Variablen verwendet werden. Es ist nur wichtig, dass die Variablen im Server-Adressraum
				freigegeben sind.
			-SubDiag
				Dieser Task enth�lt die Aufrufe zum Ermitteln der Subscriber-Diagnose-Z�hler (siehe) unten. Da hier nur
				einfache Funktionsaufrufe ben�tigt werden, gibt es den Task nur in ANSI-C, nicht in StructuredText.
				
		Diagnose
			Der Subscriber kann optional durch Z�hler diagnostiziert werden (siehe Task 'SubDiag'), die �ber Funktionen der
			System-Bibliothek 'ArPubSubD' ermittelt werden. Sie z�hlen jeweils die empfangenen Messages (Telegramme) und DataSets,
			wobei immer die Gesamtanzahl und die Anzahl, bei denen Fehler aufgetreten sind, mitgez�hlt werden.
			Hinweis: Beim Hochlauf des Systems k�nnen immer ein paar Fehler gez�hlt werden.
			Treten im zyklischen Betrieb immer noch Fehler auf, sollte die Konfigurationen auf Parametrier-Fehler untersucht werden.
			Da die Diagnose im Betriebsystem stattfindet, umfasst sie auch nur Telegramme, welche den 1. Filter-Level (siehe oben)
			passiert haben.
			Achtung: Bei einer ArSim mit Ip 127.0.0.1 werden keine Telegramme vom Publisher ver�ffentlicht (siehe
			PubSub/ReadMe.txt) und vom Subscriber auch nicht empfangen. Deshalb z�hlen die Diagnose-Z�hler in diesem Beispiel nicht
			hoch.

		Import
			Durch den Kontext-Men�-Punkt 'Import datatsets from *.uabinary' k�nnen die Konfigurationen eines Publishers importiert
			werden (es werden immer alle DataSets importiert; nicht ben�tigte k�nnen einfach wieder gel�scht werden).
			Achtung: Der Kontext-Men�-Punkt ist nur dann sichtbar, wenn der Knoten 'ReaderGroups' einer PubSub-Konfiguration
			angew�hlt ist!
			Generell ist diese Art der Konfiguration empfohlen, da sie Fehler ausschlie�t. Au�erdem gibt es Parameter, die nicht
			so einfach zu ermitteln sind (z.B. DataSetOffset). Diese sind aber im Import enthalten und werden somit automatisch
			richtig gesetzt.
				