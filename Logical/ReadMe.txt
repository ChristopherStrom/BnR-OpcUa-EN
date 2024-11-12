In diesem Beispiel wird die Implementierung von OpcUa-Funktionalit�ten gezeigt.
Es ist KEIN offizielles Beispiel und daher besteht f�r den Anwender kein Anspruch auf
Erweiterung, Fehlerbehebung, Schulung oder Support. Auch die Fehlerfreiheit kann nicht
garantiert werden.

Tasks
	Template:				Ist ein Muster, um schneller neue Tasks im selben Format implementieren zu k�nnen.
									Es wird f�r das Beispiel nicht ben�tigt.
	ServerData: 		Stellt Variablen zur Verf�gung, die am eigenen Server ver�ffentlicht werden und Variablen, welche
									von den Clients beschrieben werden.
	SrvDt64C:				Die Implementierung von 64-Bit-Werten in der Sprache ANSI-C;
	SrvDt64ST:			Die Implementierung von 64-Bit-Werten in der Sprache StructuredText;
	SrvMethC:				Die Implementierung benutzerdefinierten Server-Methoden in der Sprache ANSI-C.
	SrvMethST:			Die Implementierung benutzerdefinierten Server-Methoden in der Sprache StructuredText.
	SrvEvntC:				Anwenderseitiges Feuern eines Events in der Sprache ANSI-C.
	SrvEvntST:			Anwenderseitiges Feuern eines Events in der Sprache StructuredText. Dieser Task ist disabled.
	ClientC:				Die Implementierung des Clients in der Sprache ANSI-C.
	ClientST:				Die Implementierung des Clients in der Sprache StructuredText.
	BrbUaCltC:			Die Implementierung des Clients mithilfe der Bibiothk BrbLibUa in der Sprache ANSI-C.
	BrbUaCltST:			Die Implementierung des Clients mithilfe der Bibiothk BrbLibUa in der StructuredText.
	OpcUaAny:				Stellt lediglich Variablen bereit, welche am OpcUaAny-Client gemappt sind. 
	BrbUaSrvC:			Die Implementierung des Servers mithilfe der Bibiothk BrbLibUa in der Sprache ANSI-C.
	BrbUaSrvST:			Die Implementierung des Servers mithilfe der Bibiothk BrbLibUa in der StructuredText.
	UaCertsC:				Beispiel zur Laufzeit-Verwaltung von Zertifikaten in der Sprache ANSI-C.
	UaCertsST:			Beispiel zur Laufzeit-Verwaltung von Zertifikaten in der Sprache StructuredText.
	AirCondC:				Funktionelle Implementierung f�r das Beispiel eines eigenen Datenmodells in der Sprache ANSI-C.
	AirCondST:			Funktionelle Implementierung f�r das Beispiel eines eigenen Datenmodells in der Sprache StructuredText.
	PubSub:					Exemplarische Konfiguration einer PubSub-Verbindung.

In jedem Task ist ebenfalls eine ReadMe.txt enthalten, die ihn n�her beschreibt.
Der Task 'SrvEvntST' ist disabled, damit das Event nicht vom ANSIC- und vom ST-Task gefeuert wird.

Um dieses Beispiel zu verstehen, ist es zwingend notwendig, die AS-Hilfe zu studieren. Ausserdem sollte sich der
Anwender Wissen �ber Konzepte und die allgemeine Funktionsweise von OpcUa aneignen. B&R bietet hierf�r auch Kurse an.

Ab AS4.4 kann als Ersatz f�r den Library-Client der OpcUa_Any-Client verwendet werden, welcher im HW-Baum
eingef�gt wird und nur parametriert statt programmiert werden muss.

Ab AS4.9 kann ein Library-Client mit sehr viel weniger Aufwand mithilfe der Bibliothek BrbLibUa implementiert werden.
Auch hier ist ein Beispiel vorhanden.
	
WICHTIG:
Wird kein jeweils eigenes Zertifikat f�r Server/Client angelegt, werden beim erstmaligem Starten der SPS
automatisch Zertifikate erzeugt, welche aber nur einen G�ltigkeitszeitraum von 10 Jahren haben.
Bei einer Verbindung zwischen B&R-Teilnehmern ist das unkritisch, da dann der G�ltigkeitszeitraum nicht
gepr�ft wird. Bei einer Verbindung zu einem externen Teilnehmer (also nicht B&R) muss ermittelt werden, ob
dieser den G�ltigkeitszeitraum pr�ft und gegebenenfalls eine Verbindugn zur�ckweist!
Ist das der Fall, sollten also unbedingt eigene Zertifikate angelegt und verwendet werden.
Siehe dazu AS-Hilfe GUID 'f83f9b82-60fe-4f7c-b101-504cb81ffc44' (='Access & Security/TLS/SSL(SSL bei B&R') sowie
GUID '2c919423-08bb-4895-88b8-afcf6114d0a2' (='Programmierung/Editoren/Konfigurationseditoren/
Hardwarekonfiguration/CPU Konfiguration/SG4/OPC UA Server').
In diesem Beispiel wurde jeweils ein Zertifikat f�r Server und Client unter
'ConfigurationView/AccessAndSecurity/CertificateStore/OwnCertifcates' mit einer Laufzeit von 50 Jahren 
angelegt.
Dazu wurde die Konfiguration 'ConfigurationView/AccessAndSecurity/TransortLayerSecurity/OpcUaCfg.sslcfg' 
angelegt, in welcher die Eintr�ge konfiguriert sind.
Die Konfiguration 'SslCfgOpcUaServer' wurde dem Server in der System-Konfiguration zugewiesen.
Die Konfiguration 'SslCfgOpcUaClient' wird dem Client am FB 'UA_Connect' zugewiesen.
Siehe dazu auch Package 'UACerts'.