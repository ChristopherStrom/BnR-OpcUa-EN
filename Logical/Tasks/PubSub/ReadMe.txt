Hier wird die Konfiguration von Publisher/Subscriber gezeigt.

Allgemeines zu PubSub
	PubSub ist eine alternative OpcUa-Kommunikation zu einer Client-Server-Verbindung.
	Bei PubSub ist es im Gegensatz zu Client/Server nicht notwendig, eine explizite Verbindung aufzubauen. Der Publisher
	schickt die Daten autark durch ein Udp-Multicast-Telegramm ins Netzwerk. Dieses	Telegramm kann dann von einem oder
	mehreren Subscribern empfangen und ausgewertet werden. Der Publisher weiss nicht, ob und welche Subscriber zuhören.
	Eine B&R-Sps kann Publisher sein (und mehrere Datenblöcke in verschiedenen Intervallen publishen) und gleichzeitig
	Subscriber auf mehrere andere Publisher enthalten. Sie kann sich nur nicht auf einen Datenblock des eigenen Publishers
	abonnieren (Hintergrund siehe 'Zu diesem Beispiel' unten).

	Theoretisch muss ein Publisher oder ein Subscriber nicht gleichzeitig ein Server oder Client sein. Beide Kommunkationsarten
	haben lt. Spezifikation nichts miteinander zu tun.
	Praktisch ist es aber oft so, dass ein Publisher Knoten aus einem Adressraum veröffentlicht, der bequemerweise von einem
	Server bereitgestellt wird. Auch ein Subscriber benötigt einen Adressraum, auf dessen Knoten die empfangenen Daten kopiert
	werden können. Eine B&R-Sps braucht deshalb eine Adressraum-Konfiguration und auch das OpcUa-System muss in der System-
	Konfiguration aktiviert sein.

	PubSub wird oft zusammen mit TSN (TimeSensitiveNetwork, also echtzeitfähiges Ethernet) genannt. Tatsächlich wird PubSub
	von OpcUa-TSN verwendet. Trotzdem kann PubSub auch autaurk in nicht echtzeitfähigen Ethernet-Netzwerken eingesetzt
	werden. Dies ist hier der Fall, da TSN noch nicht veröffentlicht ist. Deshalb müssen auch die Parameter unter 'Activate VLAN'
	in der PubSub-Konfiguration noch nicht gesetzt werden (sie sind später für TSN wichtig).

	Laut Spezifikation hängt der Aufbau eines Publisher-Multicast-Telegramms (einer sogenannten NetworkMessage) von sehr
	vielen Optionen ab. Viele Parameter	werden nur optional im Telegramm mitgesendet. Es gibt auch einige spezifizierte
	Formate, sogenannte 'HeaderLayouts', welche den Aufbau zu großen Teilen festlegen. So kann die sonst sehr aufwändige
	Konfiguration stark vereinfacht	ausfallen. B&R nutzt das HeaderLayout 'UADP-Periodic-Fixed', mit dem viele Parameter
	fix gesetzt sind und so die	Konfiguration überschaubar macht.
	Es gibt auch einige Einschränkungen, welche in der AS-Hilfe genauer beschrieben sind:
		-Nur skalare Werte und 1-dimensionale Arrays
		-Keine Strukturen, Enumerationen, Pointer, Konstanten
		-Noch keine Security (Verschlüsselung)
		-Der Publisher wird nicht synchron zu den Taskklassen ausgeführt. Somit ist eine Konsistenz der Daten zueinander, auch
			wenn sie in einem DataSet sind, nicht gewährleistet. Diese Funktionalität wird erst durch TSN abgebildet werden
			können.
			
Zu diesem Beispiel
	Leider kann in einer ArSim (Sps-Simulation auf einem PC), wie sie für dieses Beispiel-Projekt verwendet wird, keine
	funktionierende PubSub-Verbindung gezeigt werden. Dafür gibt es mehrere Gründe:
		1. Eine Sps kann sich nicht selber zuhören, also auf den eigenen Publisher subscriben.
				Grund: Ethernet-Sockets sind auf der Sps so eingestellt, dass sie ihre gesendeteten Telegramme nicht gleichzeitig
				auch empfangen (auch nicht, wenn es Multicast-Telegramme sind). Dies hat performance-technische Gründe:
				Müsste ein Socket auch die selber gesendeten Telegramme empfangen und auswerten, würde dies die Hardware zu sehr
				durch Interrupts belasten.
		2. Eine ArSim hat normalerweise (wie hier auch) eine virtuelle Ethernet-Verbindung über die Adresse 127.0.0.1.
				Aufgrund des virtuellen Netzwerkes werden keine Telegramme vom Publisher veröffentlicht.
				
	Aus diesem Grund kann hier nur die exemplarische Konfiguration gezeigt werden. Würde dieses Beispiel auf zwei Hardware-
	Sps angepasst, so würde die Kommunikation funktionieren.

	Es gibt zumindest einen Trick, wie die Publisher-Multicast-Telegramme einer ArSim in ein äußeres Netzwerk des PC's gebracht
	werden können: Die Ip-Adresse der einzigen ArSim-Ethernet-Schnittstelle IF3, welche normalerweise auf 127.0.0.1 eingestellt
	ist, muss auf die Ip-Adresse des PC's zu dem Netzwerk eingestellt werden. Dann werden die Telegramme über Windows automatisch
	an diese Ethernet-Schnittstelle und somit in das Netzwerk geschickt. Sie können dann sogar mit Wireshark aufgezeichnet
	oder von einem Subscriber im Netzwerk empfangen werden. Leider funktioniert dies in Windows nur in diese Richtung. Von Windows
	empfangene Telegramme werden nicht auf die ArSim	weitergeleitet und können deshalb auch nicht von einem ArSim-Subscriber
	empfangen werden.
	Hinweis: Trotz dieses Tricks kann eine ArSim sich nicht selber zuhören (siehe oben).
			
	Eine PubSub-Configuration kann jeweils einen Publisher (in den WriterGrops) und einen Subscriber (in den ReaderGroups)
	enthalten. In diesem Beispiel sind sie der Übersichtlichkeit halber aber auf zwei separate PubSub-Konfigurationen
	('ExamplePublisher' und 'ExampleSubscriber') aufgeteilt.