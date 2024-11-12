
Hier wird demonstriert, wie OpcUa-Zertifikate zur Laufzeit verwaltet werden können.
Ursprünglich sind die Zertifikate im Projekt hinterlegt. Beispiel Server:
	Unter 'Configuration View/PC/AccessAndSecurity/CertificateStore/OwnCertificates' ist sowohl das
		öffentliche Zertifikat 'MyOpcUaServerCert.cer' sowie der dazugehörige Schlüssel
		'MyOpcUaServerKey.key' hinterlegt.
		Diese sind in der SSL-Konfiguration unter 
		'Configuration View/PC/AccessAndSecurity/TransportLayerSecurity/OpcUaCfg.sslcfg' in dem Eintrag
		'SslCfgOpcUaServer' angegeben, welcher wiederum bei der Server-Konfiguration unter
		'OPC-UA System/Activate OPC-UA-System/Security/Authentication/Software Certificates' zugewiesen wurde.
		Nach dem Projekt-Download verwendet der Server somit das angegebene Zertifikat mit dessen Schlüssel.

Die Verwaltung von Zertifikaten im Zertifikats-Store zur Laufzeit geschieht mit der Bibliothek 'ArCert'.
Die Verwaltung von SSL-Konfigurationen zur Laufzeit geschieht mit der Bibliothek 'ArSsl'.
In diesem Task werden bestimmte Funktionen dieser Bibliotheken über OpcUa-Methoden nach aussen gelegt.
Dafür wurden eigens OpcUa-Methoden implementiert, welche die Funktionsblöcke mit den übergebenen Eingangs-
Argumenten besetzen und aufrufen.
Hinweis: Wie eine OpcUa-Methode generell implementiert wird, wird hier nicht mehr eigens erklärt.
	Dies ist im Beispiel-Task 'ServerMethods' zu dokumentiert.
Hinweis: Die verwendeten System-Bibliotheken sind in der AS-Hilfe im Detail beschrieben.
Hier die Beschreibung der einzelnen Methoden:

	OwnGetCertificateList
		Eingänge: 					Keine.
		Ausgänge:
			CertificateList:	Dynamische Liste der eigenen Zertifikate.
			ErrorId:					Fehler aus den Funktionsblöcken (siehe AS-Hilfe), 0=Ok.
		Beschreibung:
			Mithilfe des Funktionsblock 'ArCertGetOwnDetails' wird die Liste der eigenen Zertifikate 
			unter '../OwnCertificates/Cerificates' ausgelesen und in das Ausgangs-Argument 
			'CertificateList' eingetragen, welches ein dynamisches Struktur-Array ist.
			Hinweis: Die Erklärung zu dynamischen Arrays siehe Task 'ServerData'.
			Jeder Eintrag stellt ein Zertifikat dar. Er enthält dabei folgende Angaben:
				Name:					Dateiname, unter dem das Zertifikat auf der SPS gespeichert wird.
				Issuer:				Angaben zum Herausgeber
				Subject:			Angaben zum zertifizierten Objekt
				ValidFrom:		Anfang des Gültigkeits-Zeitraums
				ValidTo:			Ende des Gültigkeits-Zeitraums
				SerialNumber:	Seriennummer
		
	OwnGenerate
		Eingänge:
			Parameter:	Struktur mit den zur Erzeugung notwendigen Daten.
		Ausgänge:
			ErrorId:		Fehler aus den Funktionsblöcken (siehe AS-Hilfe), 0=Ok.
		Beschreibung:
			Mithilfe des Funktionsblock 'ArCertGenerateOpcUA' wird ein neues Zertifikat sowie dessen 
			Schlüssel erzeugt.
		
	OwnImport
		Eingänge:
			Name:						Dateiname, unter dem das Zertifikat auf der SPS gespeichert wird.
			Certificate:		Zertifikat als ByteString.
			PrivateKeyName:	Dateiname, unter dem der Schlüssel auf der SPS gespeichert wird.
			PrivateKey:			Schlüssel als ByteString.
			Overwrite:			Wenn true, werden vorhandenen Zertifikate/Schlüssel mit demselben Namen gelöscht,
											bevor sie importiert werden. So können Fehlermeldungen verhindert werden.
		Ausgänge:
			ErrorId: 				Fehler aus den Funktionsblöcken (siehe AS-Hilfe), 0=Ok.
		Beschreibung:
			Mithilfe der Funktionsblöcke 'ArCertDeleteOwn', 'ArCertImportOwn', 'ArCertDeletePrivateKey' und
			'ArCertImportPrivateKey' werden Zertifikate/Schlüssel zuerst gelöscht und dann neu importiert.
			Sie werden als ByteString, also als dynamische USINT-Arrays übergeben. Da die Zertifikats- bzw.
			Schlüssel-Dateien sowieso Binär-Dateien sind, können sie leicht Byte für Byte geladen und in das 
			Argument eingetragen werden. Einige Test-Clients (z.B. UaExpert) bieten dafür eine eigene Funktion
			('Load file' o.ä.) an.
			Wenn das Zertifikat unter dem Namen 'MyOpcUaServerCert.cer' und der Schlüssel unter dem Namen
			'MyOpcUaServerKey.key' importiert werden, sind das die ursprünglichen Namen, die auch in der SSL-
			Konfiguration angegeben sind. Somit muss die SSL-Config nicht geändert werden, sondern es reicht
			ein Neustart des Systems.
		
	OwnDelete	
		Eingänge:
			Name:										Dateiname, unter dem das Zertifikat auf der SPS gespeichert ist.
			PrivateKeyName:					Dateiname, unter dem der Schlüssel auf der SPS gespeichert ist.
			SuppressNotExistsError:	Unterdrückt eine Fehlermeldung, wenn eine Datei nicht vorhanden ist.
		Ausgänge:
			ErrorId: 								Fehler aus den Funktionsblöcken (siehe AS-Hilfe), 0=Ok.
		Beschreibung:
			Mithilfe der Funktionsblöcke 'ArCertDeleteOwn' und 'ArCertDeletePrivateKey' werden die angegebenen
			Zertifikate/Schlüssel gelöscht.
			
	ForeignGetCertificateList
	ForeignImport
	ForeignDelete
		Diese Methoden führen analog zu den obigen 'Own'-Methoden die Funktionalität für die Zetifikate in der
		Sektion 'ThirdPartyCertificates' aus, welche zum Beispiel für Trusted-Lists benötigt werden. Da es sich 
		hier um Zertifikate von Fremd-Teilnehmern handelt, werden keine Schlüssel-Angaben benötigt.
		In der Projektierung sind nur Zertifikate 'RnCommTest [xxx].der' vorhanden, welche nur zum Auslesen
		beigefügt wurden, aber in der Konfiguration nicht verwendet werden.

	SslGetCfgList
		Eingänge: 	Keine.
		Ausgänge:
			CfgList:	Dynamische Liste der SSL-Konfigurationen.
			ErrorId:	Fehler aus den Funktionsblöcken (siehe AS-Hilfe), 0=Ok.
		Beschreibung:
			Mithilfe des Funktionsblock 'ArSslGetCfgDetails' wird die Liste der SSL-Konfigurationen 
			ausgelesen und in das Ausgangs-Argument 'CfgList' eingetragen, welches ein dynamisches Struktur-Array 
			ist. Hinweis: Die Erklärung zu dynamischen Arrays siehe Task 'ServerData'.
			Jeder Eintrag stellt eine Konfiguration dar. Er enthält dabei folgende Angaben:
				Name:											Name der Konfiguration.
				OwnCertificate:						Dateiname des Zertifikats und Schlüssels.
				SslVersion:								Version, z.B. 'SSL 3.0' oder 'TLS 1.0'.
				CipherCount:							Anzahl der Verschlüsselungsalgorithmen.
				TrustedCertificatesCount:	Anzahl der vertrauenswürdigen Zertifikate.
				CRLCount:									Anzahl der Zertifikats-Sperrlisten.
			In dieser Projektierung gibt es zwei Konfigurationen:
					-'SslCfgOpcUaServer' für den Server
					-'SslCfgOpcUaClient' für die Clients

	SslGetTrustedCertList
		Eingänge:
			CfgName:							Name der SSL-Konfiguration, z.B. 'SslCfgOpcUaServer'
		Ausgänge:
			TrustedCertNameList:	Dynamische Liste der vertrauenswürdigen Zertifikate.
			ErrorId:							Fehler aus den Funktionsblöcken (siehe AS-Hilfe), 0=Ok.
		Beschreibung:
			Mithilfe des Funktionsblock 'ArSslGetCertificate' wird die Liste der vertrauenswürdigen Zertifikate
			einer SSL-Konfiguration ausgelesen und deren Dateinamen in das Ausgangs-Argument 'TrustedCertNameList' 
			eingetragen, welches ein dynamisches String-Array ist. 
			Hinweis: Die Erklärung zu dynamischen Arrays siehe Task 'ServerData'.
			In dieser Projektierung sind weder für den Server noch für die Clients vertrauenswürdigen Zertifikate
			konfiguriert, daher wird diese Methode für beide ein leeres String-Array liefern.
	
	Warmstart
		Eingänge:	Keine
		Ausgänge:	Keine
		Beschreibung:
			Mithilfe der Funktions 'SYSreset' wird ein Warmstart ausgelöst. Damit der Server noch genügend
			Zeit hat, um dem Client die Ausführung der Methode zurückzumelden, wird der Warmstart um 2s verzögert.
		

Es wurden nicht alle Funktionen der beiden Bibliotheken 'ArCert' und 'ArSsl' nach aussen gelegt.
Es sollte nur exemplarisch gezeigt werden, wie man dies implementiert.
Mit diesen Beispielen sollte es möglich sein, eine auf die jeweilige Applikation zugeschnittene Verwaltung
der Zertifikate zur Laufzeit zu entwickeln.
Je nach Anforderung kann der Austausch eines Zertifikats durch mehr oder weniger komplexe Konzepte erfolgen:

1. Einfache Variante
	Ein altes Zertifikat wird durch Import mit einem neuen ersetzt. Der Dateiname bleibt dabei unverändert. Da 
	in der SSL-Konfig lediglich der Dateiname angegeben ist, braucht diese nicht verändert zu werden. Nach einem 
	Warmstart der SPS wird das neue Zertifikat verwendet.
	Dieses Konzept kann mit den hier implementierten Methoden schon getestet werden.
	Vorteil: Keine Änderung der SSL-Konfig nötig.

2. Komplexe Variante
	Die Zertifikate haben unterschiedliche Namen. Mithilfe der Bibliothek 'ArSsl' muss dann auch die SSL-Konfig 
	angepasst werden.
	Dieses Konzept wurde in diesem Beispiel nicht implementiert.
	
ACHTUNG:
Da durch den ungewollten Austausch von Zertifikaten auch Hacker-Angriffe möglich sind, sollte dieses Konzept nur 
auf Servern verwirklicht werden, mit denen nur verschlüsselte Kommunikation möglich ist (SignAndEncrypt)!
