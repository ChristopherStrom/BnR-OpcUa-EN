Hier wird die Konfiguration des Publishers erklärt.

	Die Konfiguration ist in der Datei 'UaPubSub.uaPubSub' unter 'ConfigurationView/ArSim/PC/Connectivity/OpcUA' enthalten.
	Hier können theoretisch beliebig viele Publisher konfiguriert werden.
	Achtung: Einige der Parameter werden nur angezeigt, wenn die erweiterte Parameter-Ansicht in der Symbol-Leiste angehakt ist!
	
	In diesem Beispiel ist ein Publisher konfiguriert, der zwei Datenblöcke in unterschiedlichen Intervallen sendet.
	Hierarchischer Aufbau und wichtige Parameter:
		+	ExamplePublisher									Ist gleichzeitig der Name der Publisher-Konfiguration. Dient nur der Unterscheidung
		|																			zu anderen Elementen. Es kann beliebig viele Konfigurationen geben.
		+-	Publisher ID										Dieser Parameter ermöglicht einem Subscriber, Daten eines bestimmten Publishers zu
		|																			abonnieren. Dieser Parameter gilt nur für die WriterGroups einer Publisher-
		|																			Konfiguration.
		+-	Network interface								Auswahl der Ethernet-Schnittstelle, an der gesendet wird.
		+-+	Address													
		|	+-	IP address										Angabe der Multicast-Ip, an die gesendet wird. Sie muss zwischen 224.0.0.0 und
		|	|																		239.255.255.255 liegen. Dieser Bereich ist weltweit für Multicasts reserviert.
		|	|																		Diese Adresse ermöglicht einem Subscriber, bestimmte Publisher zu abonnieren.
		|	+-	Port number										Dieser Port ermöglicht einem Subscriber, bestimmte Publisher zu abonnieren.
		|																			Die Standard-Portnummer für OpcUa ist 4840, es kann jedoch auch eine andere
		|																			verwendet werden.
		+-+	WriterGroups										Es kann beliebig viele WriterGroups geben.
			+-	Name													Der Name dient nur der Unterscheidung zu anderen Elementen.
			+-	WriterGroup ID								Dieser Parameter ermöglicht einem Subscriber, bestimmte Daten eines Publishers zu
			|																		abonnieren.
		  +-	Publishing interval						In diesem Intervall in [ms] werden die unterliegenden Daten versendet.
			|																		Hier sollte bewusst eine Zeit gewählt werden, die ausreicht. Ein zu kleines
			|																		Intervall belastet unnötigerweise den Publisher, das Netzwerk und die Subscriber.
			|																		Das kleinste mögliche Intervall beträgt 10ms.
		  +-+	DataSetWriter									Es kann beliebig viele Writer innerhalb einer WriterGroup geben.
		  	+-	Name												Der Name dient nur der Unterscheidung zu anderen Elementen.
		  	+-	DataSetWriter ID						Dieser Parameter ermöglicht einem Subscriber, bestimmte Daten eines Publishers zu
				|																abonnieren. Ein B&R Subscriber wertet sie nicht aus.
		  	+-+	PublishedDataSet						Es gibt nur 1 DataSet pro Writer.
		  		+-	Name											Der Name dient nur der Unterscheidung zu anderen Elementen.
		  		+-+	DataSet field							Es kann mehrere Fields innerhalb des DataSets geben.
						+-	DataSet field name			Der Name dient nur der Unterscheidung zu anderen Elementen.
						+-	DataSet field ID				Wird vom Editor automatisch erstellt und dient einer zukünftigen Funktionalität.
						+-	Source variable					Stellt die Quelle des Wertes dieses Fields dar. Sie wird als NodeId des Server-
																				Adressraums angegeben.
																				Achtung: Der Knoten muss im Server-Adressraums freigegeben sein. Dabei ist es
																				unwichtig, welche Rechte für welche Rolle vergeben sind.
																				
		Der Name eines Elements sollte aussagekräftig gewählt werden (vor allem bei Fields), da die Konfiguration hier exportiert
		(siehe unten 'Export') und bei einem Subscriber importiert werden kann. Der Projektierer des Subscribers kann dann
		aufgrund der Namen die Bedeutung der Elemente erkennen.
		
		Hier noch Informationen zu bestimmten Parametern:
			WriterGroup/Message settings/GroupVersion
				Die GroupVersion wird bei Änderung relevanter Parameter automatisch neu gesetzt. Sie berechnet sich aus den Sekunden
				seit 01.01.2000 als Uint32. Sie wird im Telegramm mitgeschickt und dient manchen Subscribern als Hinweis, dass ihre
				Konfiguration nicht mehr der des Publishers entspricht. Ein B&R Subscriber wertet sie nicht aus.
			
			Field/FieldMetaData
				Diese Angaben können nicht per Hand verändert werden, weil sie automatisch bei Auswahl der Quelle gesetzt werden.
				
		Notwendigkeit von verschiedenen Elementen
			Eine eigene Konfiguration muss immer dann verwendet werden, wenn unterschiedliche Multicast-Ip oder Ports verwendet
				werden sowie wenn an verschiedenen Ethernet-Schnittstellen gesendet werden soll. In diesem Beispiel wird nur eine
				Publisher-Konfiguration verwendet.
			Eine eigene WriterGroup muss immer dann angelegt werden, wenn Daten in verschiedenen Intervallen gesendet werden
				sollen. In diesem Beispiel wird in zwei Intervallen gesendet (500ms und 1000ms), weshalb auch zwei WriterGroups
				angelegt sind.
			Jeder Writer wird durch eine eigene NetworkMessage (also ein eigenes Multicast-Telegramm) versendet. Die darin
				enthaltene DataSetWriterId ermöglicht dem Subscriber die Filterung der Messages, die für ihn interessant sind.
				Verschiedene Writer sind also dann notwendig, wenn bestimmte Daten nur von bestimmten Subscribern benötigt werden.
				In diesem Beispiel sind in der ersten WriterGroup exemplarisch zwei Writer angelegt.
				
			Achtung: Ein Writer kann nur so viele Fields enthalten, dass die komplette Message nicht mehr als 1400 Bytes benötigt!
		
		Tasks
			-Quelle der Field-Werte
				Für die zu publishenden Werte der Fields werden Variablen aus dem Task 'ServerData' verwendet, welche zyklisch
				hochzählen. Deshalb ist hier kein	eigener Task notwendig.
				Hinweis: Es könnten auch globale Variablen verwendet werden. Es ist nur wichtig, dass die Variablen im Server-Adressraum
				freigegeben sind.
			-PubDiag
				Dieser Task enthält die Aufrufe zum Ermitteln der Publisher-Diagnose-Zähler (siehe unten). Da hier nur
				einfache Funktionsaufrufe benötigt werden, gibt es den Task nur in ANSI-C, nicht in StructuredText.
				
		Diagnose
			Der Publisher kann optional durch Zähler diagnostiziert werden (siehe Task 'PubDiag'), die über Funktionen der
			System-Bibliothek 'ArPubSubD' ermittelt werden. Sie zählen jeweils die gesendeten Messages (Telegramme) und DataSets,
			wobei immer die Gesamtanzahl und die Anzahl, bei denen Fehler aufgetreten sind, mitgezählt werden.
			Hinweis: Beim Hochlauf des Systems können immer ein paar Fehler gezählt werden.
			Treten im zyklischen Betrieb immer noch Fehler auf, sollte die Konfigurationen auf Parametrier-Fehler untersucht werden.
			Achtung: Bei einer ArSim mit Ip 127.0.0.1 werden keine Telegramme vom Publisher veröffentlicht (siehe
			PubSub/ReadMe.txt). Deshalb zählen die Diagnose-Zähler in diesem Beispiel nicht hoch.
			
		Export
			Durch den Kontext-Menü-Punkt 'Export all published datatsets for all connections to *.uabinary' können die gesamten
			Konfigurationen exportiert werden (es werden immer alle Publisher-Konfigurationen exportiert). Dieses Datei-Format ist
			durch die Opc-Foundation standardisiert und kann demnach zum Austausch mit Subscribern verwendet werden.
			Achtung: Der Kontext-Menü-Punkt ist nur dann sichtbar, wenn die PubSub-Konfiguration angewählt ist!
			Wenn ein Subscriber den Import dieses Formats erlaubt (wie z.B. das Automation Studio oder RnCommTest), kann auf
			diese Weise die	Konfiguration des Subscribers sehr stark vereinfacht werden.
			In diesem Beispiel ist die exportierte Datei mit dem Namen 'OpcUaSample49_PublisherExport.uabinary' vorhanden.
		
		Hinweise zu Strings
			Leider sind in der momentanen AS4.9 und der zugehörigen AR A4.90 noch einige Unzulänglichkeiten in Bezug auf den
			Datentyp STRING vorhanden:
				1. Zu publishende Strings oder String-Arrays dürfen nicht mit Konstanten, sondern nur mit Literalen (fixen Zahlen)
						deklariert sein.
				2. Änderung einer String-Deklaration bewirkt nicht automatisch eine Anpassung in der Publisher-Konfiguration.
			Diese Dinge werden wahrscheinlich in einer der nächsten Versionen behoben werden.
			
		