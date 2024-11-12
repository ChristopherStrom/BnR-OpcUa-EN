
Beispiel zum anwenderseitigen Feuern eines Events.

Gefeuert wird in diesem Beispiel das Event 'ProgressEventType'. Es wird normalerweise dazu verwendet, den
Fortschritt eines Prozesses zu melden.
Da es direkt von 'BaseEventType' abgeleitet ist, besitzt es dessen Felder 'EventId', 'EventType', 'LocalTime',
'Message', 'ReceiveTime', 'Severity', 'SourceName', 'SourceNode' und 'Time'.
Im Task besetzt werden davon nur 'Message' und 'Severity'. Die anderen werden nicht �bergeben und daher
automatisch vom Betriebssystem besetzt:
'EventId' enth�lt eine automatisch erstellte, eindeutige GUID.
'EventType' enth�lt 'ns=0;i=11436'. Das ist der Knoten von 'ProgressEventType'.
'LocalTime' enth�lt die Differenz der lokalen Server-Zeit zur UTC-Zeit.
'ReceiveTime' enth�lt die UTC-Zeit, wann das Event vom Server empfangen wurde, falls der Server nicht der Erzeuger
	des Events ist. In diesem Fall wird sie nicht besetzt und ist daher gleich 'Time'.
'SourceName' enth�lt den DisplayName des Knotens, der bei 'SourceNode' angegeben ist.
'SourceNode' enth�lt die NodeId des Knotens, der der Ausl�ser des Events ist. Da sie hier nicht applikativ besetzt wird,
	wird sie vom System automatisch als "i=0" besetzt.
'Time' enth�lt die UTC-Zeit, wann das Event aufgetreten ist.

Bei jedem Feuern werden anwenderseitig folgende BaseEvent-Felder besetzt:
'Message' sollte einen LocalizedText enthalten, welcher das Event durch einen Klartext beschreibt.
'Severity' sollte die Priorit�t des Events (1=Info; 1000=Katastrophe) enthalten. In diesem Beispiel wird er als
	Zufallszahl	zwischen 1 und 500 gebildet.

Das gefeuerte Event 'ProgressEventType' enth�lt aber auch noch die eigenen Felder 'Context' und 'Progress':
'Context' hat als Datentypen 'BaseDataType'. Damit ist es ein Variant und kann alle Datentypen aufnehmen.
	In diesem Beispiel wird der Wert in Form der benutzerdefinierten Struktur 'FieldContext_TYP' �bergeben.
	Es w�re aber auch m�glich, eine Variable vom Datentyp 'REAL' oder 'UDINT' usw. anzugeben.
	Achtung: Damit ein Client diese als ExtensionObject (Byte-Array) gesendete Struktur wieder aufl�sen kann,
	ist es unbedingt erforderlich, dass mindestens eine Instanz dieses Datentyps am Server freigegeben ist
	(siehe OpcUaMap.uad). Nur so ver�ffentlicht der Server automatisch die Definition dieser Struktur!
	Achtung: Fehler in einigen AR-Versionen (A4.90 bis D4.90)
		Leider liefert der FB den Fehler 0x803D0000 = 'Bad_NotSupported' zur�ck, wenn eine Struktur an diesem Feld
		angebunden ist, deren Typ-Defintion global angelegt ist. Ab E4.90 ist dieser Fehler behoben.
		Muss eine dieser fehlerhaften Versionen verwendet werden, so kann als Workaround die Definition der Struktur
		lokal gemacht werden.
	
'Progress' enth�lt den Wert des Fortschritts als UINT und wird in diesem Beispiel bei jedem Feuern hochgez�hlt.
	Der Fortschritt wird hier als % interpretiert und daher nach 100% also wieder auf 0 gesetzt.

Prinzipiell muss die an das Feld gebundene Variable dem Datentyp des Feldes entsprechen. Ist das Feld vom Datentyp
'BaseDataType' (Variant), so kann jeder Datentyp angebunden werden.

Ablauf der Schrittkette:
	eSTEP_INIT:								Start der Schrittkette
	eSTEP_GET_NS_ORG:					Ermitteln des NamespaceIndex f�r 'http://opcfoundation.org/UA/'
	eSTEP_GET_NS_BR_PV:				Ermitteln des NamespaceIndex f�r 'http://br-automation.com/OpcUa/PLC/PV/'
	eSTEP_DELAY:							Warten auf Timer
	eSTEP_SET_FIELD_VALUES:		Anwenderseitiges Besetzen der Event-Felder
	eSTEP_FIRE:								Feuern des Events

Die Namespace-Uris sind fest vergeben und �ndern sich nicht. Die zugeh�rigen Namespace-Indizes werden beim Hochlauf
	des Servers vergeben und m�ssen daher ermittelt werden.
Durch einen Timer wird das Event jede 5 Sekunden gefeuert. Durch die Variable 'bSuspendTimer' kann dies verhindert
	werden. Durch die Variable 'bFire' kann das Event dann manuell gefeuert werden.
	
Um clientseitig das Event emfpangen zu k�nnen, muss der Knoten 'ns=0;i=2253' (Root/Objects/Server) in einer
Subscription abonniert werden. Ausserdem muss der Filter des EventItems die zu schickenden Felder enthalten.
Hinweis: Beim frei erh�ltlichen Test-Client 'UaExpert' ist beim Abonnieren des Knotens der Filter automatisch so
gesetzt, dass er alle Felder enth�lt.
Bei anderen Test-Client (z.B. RnCommTest) k�nnen der Filter und damit die Felder evtl. parametriert werden.
Im Task 'Client' ist ein Beispiel enthalten, wie auf der Sps dieses Event empfangen werden kann.

Da sowohl der ANSIC-Task als auch der ST-Task unabh�ngig voneinander arbeiten, w�rde das Event immer von beiden Tasks
gefeuert. Aus diesem Grund sollte immer einer der Tasks disabled sein. Hier ist es der Task 'SrvEvntST'.
