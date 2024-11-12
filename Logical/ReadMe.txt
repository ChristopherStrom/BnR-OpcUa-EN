In diesem Beispiel wird die Implementierung von OpcUa-Funktionalitäten gezeigt.
Es ist KEIN offizielles Beispiel und daher besteht für den Anwender kein Anspruch auf
Erweiterung, Fehlerbehebung, Schulung oder Support. Auch die Fehlerfreiheit kann nicht
garantiert werden.

Tasks
	Template:				Ist ein Muster, um schneller neue Tasks im selben Format implementieren zu können.
									Es wird für das Beispiel nicht benötigt.
	ServerData: 		Stellt Variablen zur Verfügung, die am eigenen Server veröffentlicht werden und Variablen, welche
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
	AirCondC:				Funktionelle Implementierung für das Beispiel eines eigenen Datenmodells in der Sprache ANSI-C.
	AirCondST:			Funktionelle Implementierung für das Beispiel eines eigenen Datenmodells in der Sprache StructuredText.
	PubSub:					Exemplarische Konfiguration einer PubSub-Verbindung.

In jedem Task ist ebenfalls eine ReadMe.txt enthalten, die ihn näher beschreibt.
Der Task 'SrvEvntST' ist disabled, damit das Event nicht vom ANSIC- und vom ST-Task gefeuert wird.

Um dieses Beispiel zu verstehen, ist es zwingend notwendig, die AS-Hilfe zu studieren. Ausserdem sollte sich der
Anwender Wissen über Konzepte und die allgemeine Funktionsweise von OpcUa aneignen. B&R bietet hierfür auch Kurse an.

Ab AS4.4 kann als Ersatz für den Library-Client der OpcUa_Any-Client verwendet werden, welcher im HW-Baum
eingefügt wird und nur parametriert statt programmiert werden muss.

Ab AS4.9 kann ein Library-Client mit sehr viel weniger Aufwand mithilfe der Bibliothek BrbLibUa implementiert werden.
Auch hier ist ein Beispiel vorhanden.
	
WICHTIG:
Wird kein jeweils eigenes Zertifikat für Server/Client angelegt, werden beim erstmaligem Starten der SPS
automatisch Zertifikate erzeugt, welche aber nur einen Gültigkeitszeitraum von 10 Jahren haben.
Bei einer Verbindung zwischen B&R-Teilnehmern ist das unkritisch, da dann der Gültigkeitszeitraum nicht
geprüft wird. Bei einer Verbindung zu einem externen Teilnehmer (also nicht B&R) muss ermittelt werden, ob
dieser den Gültigkeitszeitraum prüft und gegebenenfalls eine Verbindugn zurückweist!
Ist das der Fall, sollten also unbedingt eigene Zertifikate angelegt und verwendet werden.
Siehe dazu AS-Hilfe GUID 'f83f9b82-60fe-4f7c-b101-504cb81ffc44' (='Access & Security/TLS/SSL(SSL bei B&R') sowie
GUID '2c919423-08bb-4895-88b8-afcf6114d0a2' (='Programmierung/Editoren/Konfigurationseditoren/
Hardwarekonfiguration/CPU Konfiguration/SG4/OPC UA Server').
In diesem Beispiel wurde jeweils ein Zertifikat für Server und Client unter
'ConfigurationView/AccessAndSecurity/CertificateStore/OwnCertifcates' mit einer Laufzeit von 50 Jahren 
angelegt.
Dazu wurde die Konfiguration 'ConfigurationView/AccessAndSecurity/TransortLayerSecurity/OpcUaCfg.sslcfg' 
angelegt, in welcher die Einträge konfiguriert sind.
Die Konfiguration 'SslCfgOpcUaServer' wurde dem Server in der System-Konfiguration zugewiesen.
Die Konfiguration 'SslCfgOpcUaClient' wird dem Client am FB 'UA_Connect' zugewiesen.
Siehe dazu auch Package 'UACerts'.