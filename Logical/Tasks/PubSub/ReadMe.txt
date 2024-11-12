Hier wird die Konfiguration von Publisher/Subscriber gezeigt.

Allgemeines zu PubSub
	PubSub ist eine alternative OpcUa-Kommunikation zu einer Client-Server-Verbindung.
	Bei PubSub ist es im Gegensatz zu Client/Server nicht notwendig, eine explizite Verbindung aufzubauen. Der Publisher
	schickt die Daten autark durch ein Udp-Multicast-Telegramm ins Netzwerk. Dieses	Telegramm kann dann von einem oder
	mehreren Subscribern empfangen und ausgewertet werden. Der Publisher weiss nicht, ob und welche Subscriber zuh�ren.
	Eine B&R-Sps kann Publisher sein (und mehrere Datenbl�cke in verschiedenen Intervallen publishen) und gleichzeitig
	Subscriber auf mehrere andere Publisher enthalten. Sie kann sich nur nicht auf einen Datenblock des eigenen Publishers
	abonnieren (Hintergrund siehe 'Zu diesem Beispiel' unten).

	Theoretisch muss ein Publisher oder ein Subscriber nicht gleichzeitig ein Server oder Client sein. Beide Kommunkationsarten
	haben lt. Spezifikation nichts miteinander zu tun.
	Praktisch ist es aber oft so, dass ein Publisher Knoten aus einem Adressraum ver�ffentlicht, der bequemerweise von einem
	Server bereitgestellt wird. Auch ein Subscriber ben�tigt einen Adressraum, auf dessen Knoten die empfangenen Daten kopiert
	werden k�nnen. Eine B&R-Sps braucht deshalb eine Adressraum-Konfiguration und auch das OpcUa-System muss in der System-
	Konfiguration aktiviert sein.

	PubSub wird oft zusammen mit TSN (TimeSensitiveNetwork, also echtzeitf�higes Ethernet) genannt. Tats�chlich wird PubSub
	von OpcUa-TSN verwendet. Trotzdem kann PubSub auch autaurk in nicht echtzeitf�higen Ethernet-Netzwerken eingesetzt
	werden. Dies ist hier der Fall, da TSN noch nicht ver�ffentlicht ist. Deshalb m�ssen auch die Parameter unter 'Activate VLAN'
	in der PubSub-Konfiguration noch nicht gesetzt werden (sie sind sp�ter f�r TSN wichtig).

	Laut Spezifikation h�ngt der Aufbau eines Publisher-Multicast-Telegramms (einer sogenannten NetworkMessage) von sehr
	vielen Optionen ab. Viele Parameter	werden nur optional im Telegramm mitgesendet. Es gibt auch einige spezifizierte
	Formate, sogenannte 'HeaderLayouts', welche den Aufbau zu gro�en Teilen festlegen. So kann die sonst sehr aufw�ndige
	Konfiguration stark vereinfacht	ausfallen. B&R nutzt das HeaderLayout 'UADP-Periodic-Fixed', mit dem viele Parameter
	fix gesetzt sind und so die	Konfiguration �berschaubar macht.
	Es gibt auch einige Einschr�nkungen, welche in der AS-Hilfe genauer beschrieben sind:
		-Nur skalare Werte und 1-dimensionale Arrays
		-Keine Strukturen, Enumerationen, Pointer, Konstanten
		-Noch keine Security (Verschl�sselung)
		-Der Publisher wird nicht synchron zu den Taskklassen ausgef�hrt. Somit ist eine Konsistenz der Daten zueinander, auch
			wenn sie in einem DataSet sind, nicht gew�hrleistet. Diese Funktionalit�t wird erst durch TSN abgebildet werden
			k�nnen.
			
Zu diesem Beispiel
	Leider kann in einer ArSim (Sps-Simulation auf einem PC), wie sie f�r dieses Beispiel-Projekt verwendet wird, keine
	funktionierende PubSub-Verbindung gezeigt werden. Daf�r gibt es mehrere Gr�nde:
		1. Eine Sps kann sich nicht selber zuh�ren, also auf den eigenen Publisher subscriben.
				Grund: Ethernet-Sockets sind auf der Sps so eingestellt, dass sie ihre gesendeteten Telegramme nicht gleichzeitig
				auch empfangen (auch nicht, wenn es Multicast-Telegramme sind). Dies hat performance-technische Gr�nde:
				M�sste ein Socket auch die selber gesendeten Telegramme empfangen und auswerten, w�rde dies die Hardware zu sehr
				durch Interrupts belasten.
		2. Eine ArSim hat normalerweise (wie hier auch) eine virtuelle Ethernet-Verbindung �ber die Adresse 127.0.0.1.
				Aufgrund des virtuellen Netzwerkes werden keine Telegramme vom Publisher ver�ffentlicht.
				
	Aus diesem Grund kann hier nur die exemplarische Konfiguration gezeigt werden. W�rde dieses Beispiel auf zwei Hardware-
	Sps angepasst, so w�rde die Kommunikation funktionieren.

	Es gibt zumindest einen Trick, wie die Publisher-Multicast-Telegramme einer ArSim in ein �u�eres Netzwerk des PC's gebracht
	werden k�nnen: Die Ip-Adresse der einzigen ArSim-Ethernet-Schnittstelle IF3, welche normalerweise auf 127.0.0.1 eingestellt
	ist, muss auf die Ip-Adresse des PC's zu dem Netzwerk eingestellt werden. Dann werden die Telegramme �ber Windows automatisch
	an diese Ethernet-Schnittstelle und somit in das Netzwerk geschickt. Sie k�nnen dann sogar mit Wireshark aufgezeichnet
	oder von einem Subscriber im Netzwerk empfangen werden. Leider funktioniert dies in Windows nur in diese Richtung. Von Windows
	empfangene Telegramme werden nicht auf die ArSim	weitergeleitet und k�nnen deshalb auch nicht von einem ArSim-Subscriber
	empfangen werden.
	Hinweis: Trotz dieses Tricks kann eine ArSim sich nicht selber zuh�ren (siehe oben).
			
	Eine PubSub-Configuration kann jeweils einen Publisher (in den WriterGrops) und einen Subscriber (in den ReaderGroups)
	enthalten. In diesem Beispiel sind sie der �bersichtlichkeit halber aber auf zwei separate PubSub-Konfigurationen
	('ExamplePublisher' und 'ExampleSubscriber') aufgeteilt.