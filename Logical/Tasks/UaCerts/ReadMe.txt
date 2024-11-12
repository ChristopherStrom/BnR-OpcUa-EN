
Hier wird demonstriert, wie OpcUa-Zertifikate zur Laufzeit verwaltet werden k�nnen.
Urspr�nglich sind die Zertifikate im Projekt hinterlegt. Beispiel Server:
	Unter 'Configuration View/PC/AccessAndSecurity/CertificateStore/OwnCertificates' ist sowohl das
		�ffentliche Zertifikat 'MyOpcUaServerCert.cer' sowie der dazugeh�rige Schl�ssel
		'MyOpcUaServerKey.key' hinterlegt.
		Diese sind in der SSL-Konfiguration unter 
		'Configuration View/PC/AccessAndSecurity/TransportLayerSecurity/OpcUaCfg.sslcfg' in dem Eintrag
		'SslCfgOpcUaServer' angegeben, welcher wiederum bei der Server-Konfiguration unter
		'OPC-UA System/Activate OPC-UA-System/Security/Authentication/Software Certificates' zugewiesen wurde.
		Nach dem Projekt-Download verwendet der Server somit das angegebene Zertifikat mit dessen Schl�ssel.

Die Verwaltung von Zertifikaten im Zertifikats-Store zur Laufzeit geschieht mit der Bibliothek 'ArCert'.
Die Verwaltung von SSL-Konfigurationen zur Laufzeit geschieht mit der Bibliothek 'ArSsl'.
In diesem Task werden bestimmte Funktionen dieser Bibliotheken �ber OpcUa-Methoden nach aussen gelegt.
Daf�r wurden eigens OpcUa-Methoden implementiert, welche die Funktionsbl�cke mit den �bergebenen Eingangs-
Argumenten besetzen und aufrufen.
Hinweis: Wie eine OpcUa-Methode generell implementiert wird, wird hier nicht mehr eigens erkl�rt.
	Dies ist im Beispiel-Task 'ServerMethods' zu dokumentiert.
Hinweis: Die verwendeten System-Bibliotheken sind in der AS-Hilfe im Detail beschrieben.
Hier die Beschreibung der einzelnen Methoden:

	OwnGetCertificateList
		Eing�nge: 					Keine.
		Ausg�nge:
			CertificateList:	Dynamische Liste der eigenen Zertifikate.
			ErrorId:					Fehler aus den Funktionsbl�cken (siehe AS-Hilfe), 0=Ok.
		Beschreibung:
			Mithilfe des Funktionsblock 'ArCertGetOwnDetails' wird die Liste der eigenen Zertifikate 
			unter '../OwnCertificates/Cerificates' ausgelesen und in das Ausgangs-Argument 
			'CertificateList' eingetragen, welches ein dynamisches Struktur-Array ist.
			Hinweis: Die Erkl�rung zu dynamischen Arrays siehe Task 'ServerData'.
			Jeder Eintrag stellt ein Zertifikat dar. Er enth�lt dabei folgende Angaben:
				Name:					Dateiname, unter dem das Zertifikat auf der SPS gespeichert wird.
				Issuer:				Angaben zum Herausgeber
				Subject:			Angaben zum zertifizierten Objekt
				ValidFrom:		Anfang des G�ltigkeits-Zeitraums
				ValidTo:			Ende des G�ltigkeits-Zeitraums
				SerialNumber:	Seriennummer
		
	OwnGenerate
		Eing�nge:
			Parameter:	Struktur mit den zur Erzeugung notwendigen Daten.
		Ausg�nge:
			ErrorId:		Fehler aus den Funktionsbl�cken (siehe AS-Hilfe), 0=Ok.
		Beschreibung:
			Mithilfe des Funktionsblock 'ArCertGenerateOpcUA' wird ein neues Zertifikat sowie dessen 
			Schl�ssel erzeugt.
		
	OwnImport
		Eing�nge:
			Name:						Dateiname, unter dem das Zertifikat auf der SPS gespeichert wird.
			Certificate:		Zertifikat als ByteString.
			PrivateKeyName:	Dateiname, unter dem der Schl�ssel auf der SPS gespeichert wird.
			PrivateKey:			Schl�ssel als ByteString.
			Overwrite:			Wenn true, werden vorhandenen Zertifikate/Schl�ssel mit demselben Namen gel�scht,
											bevor sie importiert werden. So k�nnen Fehlermeldungen verhindert werden.
		Ausg�nge:
			ErrorId: 				Fehler aus den Funktionsbl�cken (siehe AS-Hilfe), 0=Ok.
		Beschreibung:
			Mithilfe der Funktionsbl�cke 'ArCertDeleteOwn', 'ArCertImportOwn', 'ArCertDeletePrivateKey' und
			'ArCertImportPrivateKey' werden Zertifikate/Schl�ssel zuerst gel�scht und dann neu importiert.
			Sie werden als ByteString, also als dynamische USINT-Arrays �bergeben. Da die Zertifikats- bzw.
			Schl�ssel-Dateien sowieso Bin�r-Dateien sind, k�nnen sie leicht Byte f�r Byte geladen und in das 
			Argument eingetragen werden. Einige Test-Clients (z.B. UaExpert) bieten daf�r eine eigene Funktion
			('Load file' o.�.) an.
			Wenn das Zertifikat unter dem Namen 'MyOpcUaServerCert.cer' und der Schl�ssel unter dem Namen
			'MyOpcUaServerKey.key' importiert werden, sind das die urspr�nglichen Namen, die auch in der SSL-
			Konfiguration angegeben sind. Somit muss die SSL-Config nicht ge�ndert werden, sondern es reicht
			ein Neustart des Systems.
		
	OwnDelete	
		Eing�nge:
			Name:										Dateiname, unter dem das Zertifikat auf der SPS gespeichert ist.
			PrivateKeyName:					Dateiname, unter dem der Schl�ssel auf der SPS gespeichert ist.
			SuppressNotExistsError:	Unterdr�ckt eine Fehlermeldung, wenn eine Datei nicht vorhanden ist.
		Ausg�nge:
			ErrorId: 								Fehler aus den Funktionsbl�cken (siehe AS-Hilfe), 0=Ok.
		Beschreibung:
			Mithilfe der Funktionsbl�cke 'ArCertDeleteOwn' und 'ArCertDeletePrivateKey' werden die angegebenen
			Zertifikate/Schl�ssel gel�scht.
			
	ForeignGetCertificateList
	ForeignImport
	ForeignDelete
		Diese Methoden f�hren analog zu den obigen 'Own'-Methoden die Funktionalit�t f�r die Zetifikate in der
		Sektion 'ThirdPartyCertificates' aus, welche zum Beispiel f�r Trusted-Lists ben�tigt werden. Da es sich 
		hier um Zertifikate von Fremd-Teilnehmern handelt, werden keine Schl�ssel-Angaben ben�tigt.
		In der Projektierung sind nur Zertifikate 'RnCommTest [xxx].der' vorhanden, welche nur zum Auslesen
		beigef�gt wurden, aber in der Konfiguration nicht verwendet werden.

	SslGetCfgList
		Eing�nge: 	Keine.
		Ausg�nge:
			CfgList:	Dynamische Liste der SSL-Konfigurationen.
			ErrorId:	Fehler aus den Funktionsbl�cken (siehe AS-Hilfe), 0=Ok.
		Beschreibung:
			Mithilfe des Funktionsblock 'ArSslGetCfgDetails' wird die Liste der SSL-Konfigurationen 
			ausgelesen und in das Ausgangs-Argument 'CfgList' eingetragen, welches ein dynamisches Struktur-Array 
			ist. Hinweis: Die Erkl�rung zu dynamischen Arrays siehe Task 'ServerData'.
			Jeder Eintrag stellt eine Konfiguration dar. Er enth�lt dabei folgende Angaben:
				Name:											Name der Konfiguration.
				OwnCertificate:						Dateiname des Zertifikats und Schl�ssels.
				SslVersion:								Version, z.B. 'SSL 3.0' oder 'TLS 1.0'.
				CipherCount:							Anzahl der Verschl�sselungsalgorithmen.
				TrustedCertificatesCount:	Anzahl der vertrauensw�rdigen Zertifikate.
				CRLCount:									Anzahl der Zertifikats-Sperrlisten.
			In dieser Projektierung gibt es zwei Konfigurationen:
					-'SslCfgOpcUaServer' f�r den Server
					-'SslCfgOpcUaClient' f�r die Clients

	SslGetTrustedCertList
		Eing�nge:
			CfgName:							Name der SSL-Konfiguration, z.B. 'SslCfgOpcUaServer'
		Ausg�nge:
			TrustedCertNameList:	Dynamische Liste der vertrauensw�rdigen Zertifikate.
			ErrorId:							Fehler aus den Funktionsbl�cken (siehe AS-Hilfe), 0=Ok.
		Beschreibung:
			Mithilfe des Funktionsblock 'ArSslGetCertificate' wird die Liste der vertrauensw�rdigen Zertifikate
			einer SSL-Konfiguration ausgelesen und deren Dateinamen in das Ausgangs-Argument 'TrustedCertNameList' 
			eingetragen, welches ein dynamisches String-Array ist. 
			Hinweis: Die Erkl�rung zu dynamischen Arrays siehe Task 'ServerData'.
			In dieser Projektierung sind weder f�r den Server noch f�r die Clients vertrauensw�rdigen Zertifikate
			konfiguriert, daher wird diese Methode f�r beide ein leeres String-Array liefern.
	
	Warmstart
		Eing�nge:	Keine
		Ausg�nge:	Keine
		Beschreibung:
			Mithilfe der Funktions 'SYSreset' wird ein Warmstart ausgel�st. Damit der Server noch gen�gend
			Zeit hat, um dem Client die Ausf�hrung der Methode zur�ckzumelden, wird der Warmstart um 2s verz�gert.
		

Es wurden nicht alle Funktionen der beiden Bibliotheken 'ArCert' und 'ArSsl' nach aussen gelegt.
Es sollte nur exemplarisch gezeigt werden, wie man dies implementiert.
Mit diesen Beispielen sollte es m�glich sein, eine auf die jeweilige Applikation zugeschnittene Verwaltung
der Zertifikate zur Laufzeit zu entwickeln.
Je nach Anforderung kann der Austausch eines Zertifikats durch mehr oder weniger komplexe Konzepte erfolgen:

1. Einfache Variante
	Ein altes Zertifikat wird durch Import mit einem neuen ersetzt. Der Dateiname bleibt dabei unver�ndert. Da 
	in der SSL-Konfig lediglich der Dateiname angegeben ist, braucht diese nicht ver�ndert zu werden. Nach einem 
	Warmstart der SPS wird das neue Zertifikat verwendet.
	Dieses Konzept kann mit den hier implementierten Methoden schon getestet werden.
	Vorteil: Keine �nderung der SSL-Konfig n�tig.

2. Komplexe Variante
	Die Zertifikate haben unterschiedliche Namen. Mithilfe der Bibliothek 'ArSsl' muss dann auch die SSL-Konfig 
	angepasst werden.
	Dieses Konzept wurde in diesem Beispiel nicht implementiert.
	
ACHTUNG:
Da durch den ungewollten Austausch von Zertifikaten auch Hacker-Angriffe m�glich sind, sollte dieses Konzept nur 
auf Servern verwirklicht werden, mit denen nur verschl�sselte Kommunikation m�glich ist (SignAndEncrypt)!
