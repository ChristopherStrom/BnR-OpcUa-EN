#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

void _INIT Init(void)
{
	// Ablöschen der Funktionsblöcke und Strukturen 
	brsmemset((UDINT)&fbUaSrv_GetNamespaceIndex, 0, sizeof(fbUaSrv_GetNamespaceIndex));
	brsmemset((UDINT)&fbUaSrv_FireEvent, 0, sizeof(fbUaSrv_FireEvent));
	brsmemset((UDINT)&Fields, 0, sizeof(Fields));
	
	// Setzen des Events 'ProgressEventType'
	fbUaSrv_FireEvent.EventType.NamespaceIndex = 0; // Wird in der Schrittkette ermittelt
	fbUaSrv_FireEvent.EventType.IdentifierType = UAIdentifierType_Numeric;
	brsstrcpy((UDINT)&fbUaSrv_FireEvent.EventType.Identifier, (UDINT)&"11436"); // ProgressEventType
	
	//Parametrieren der anwenderseitigen Felder
	UINT nFieldIndex = 0;
	brsstrcpy((UDINT)&Fields.FieldCfg[nFieldIndex].BrowsePath, (UDINT)&"/Message");
	brsstrcpy((UDINT)&Fields.FieldCfg[nFieldIndex].Variable, (UDINT)&"::SrvEvntC:Fields.Message");
	nFieldIndex += 1;
	brsstrcpy((UDINT)&Fields.FieldCfg[nFieldIndex].BrowsePath, (UDINT)&"/Severity");
	brsstrcpy((UDINT)&Fields.FieldCfg[nFieldIndex].Variable, (UDINT)&"::SrvEvntC:Fields.nSeverity");
	nFieldIndex += 1;
	brsstrcpy((UDINT)&Fields.FieldCfg[nFieldIndex].BrowsePath, (UDINT)&"/Context");
	brsstrcpy((UDINT)&Fields.FieldCfg[nFieldIndex].Variable, (UDINT)&"::SrvEvntC:Fields.Context"); // Hier könnte auch eine Variable eines anderen Standard-Datentyps angebunden werden
	nFieldIndex += 1;
	brsstrcpy((UDINT)&Fields.FieldCfg[nFieldIndex].BrowsePath, (UDINT)&"/Progress");
	brsstrcpy((UDINT)&Fields.FieldCfg[nFieldIndex].Variable, (UDINT)&"::SrvEvntC:Fields.nProgress");
	// Die Felder 'EventId', 'EventType', 'LocalTime', 'ReceiveTime', 'SourceName', 'SourceNode' und 'Time'
	// werden nicht übergeben und daher automatisch vom Betriebssystem besetzt

	fbUaSrv_FireEvent.EventFieldCount = nFieldIndex + 1;
	fbUaSrv_FireEvent.EventFields = (UaSrv_FireEventFieldType*)&Fields.FieldCfg;
	
	// Sonstige Initialisierung
	fbDelay.PT = 5000; // = 5s
	bSuspendTimer = 0;

	// Initialisierung der Schrittkette
	Step.eStepNr = eSTEP_INIT;
	
}

void _CYCLIC Cyclic(void)
{
	// Schrittkette
	switch(Step.eStepNr)
	{
		case eSTEP_INIT:
			// Start
			nNamespaceIndexBrPv = 0;
			bFire = 0;
			Step.eStepNr = eSTEP_GET_NS_ORG;
			break;

		case eSTEP_GET_NS_ORG:
			// Ermitteln des Namespace-Index für Foundation-Adressbereich am B&R-Server
			fbUaSrv_GetNamespaceIndex.Execute = 1;
			brsstrcpy((UDINT)&fbUaSrv_GetNamespaceIndex.NamespaceUri, (UDINT)&"http://opcfoundation.org/UA/");
			if(fbUaSrv_GetNamespaceIndex.Done == 1)
			{
				fbUaSrv_GetNamespaceIndex.Execute = 0;
				nNamespaceIndexFoundation = fbUaSrv_GetNamespaceIndex.NamespaceIndex;
				fbUaSrv_FireEvent.EventType.NamespaceIndex = nNamespaceIndexFoundation;
				Step.eStepNr = eSTEP_GET_NS_BR_PV;
			}
			else if(fbUaSrv_GetNamespaceIndex.Error == 1)
			{
				fbUaSrv_GetNamespaceIndex.Execute = 0;
				Step.eErrorStep = eSTEP_GET_NS_ORG;
				Step.nErrorId = fbUaSrv_GetNamespaceIndex.ErrorID;
				Step.nFieldIndex = -1;
				Step.eStepNr = eSTEP_GET_NS_ORG;
			}
			break;

		case eSTEP_GET_NS_BR_PV:
			// Ermitteln des Namespace-Index für PV-Adressbereich am B&R-Server
			fbUaSrv_GetNamespaceIndex.Execute = 1;
			brsstrcpy((UDINT)&fbUaSrv_GetNamespaceIndex.NamespaceUri, (UDINT)&"http://br-automation.com/OpcUa/PLC/PV/");
			if(fbUaSrv_GetNamespaceIndex.Done == 1)
			{
				fbUaSrv_GetNamespaceIndex.Execute = 0;
				nNamespaceIndexBrPv = fbUaSrv_GetNamespaceIndex.NamespaceIndex;
				Step.eStepNr = eSTEP_DELAY;
			}
			else if(fbUaSrv_GetNamespaceIndex.Error == 1)
			{
				fbUaSrv_GetNamespaceIndex.Execute = 0;
				Step.eErrorStep = eSTEP_GET_NS_BR_PV;
				Step.nErrorId = fbUaSrv_GetNamespaceIndex.ErrorID;
				Step.nFieldIndex = -1;
				Step.eStepNr = eSTEP_GET_NS_BR_PV;
			}
			break;

		case eSTEP_DELAY:
			// Warten, bis Event gefeuert werden soll
			fbDelay.IN = !bSuspendTimer;
			if(fbDelay.Q == 1)
			{
				fbDelay.IN = 0;
				bFire = 1;
			}
			if(bFire == 1)
			{
				bFire = 0;
				Step.eStepNr = eSTEP_SET_FIELD_VALUES;
			}
			break;

		case eSTEP_SET_FIELD_VALUES:
			// Fortschritt erhöhen
			Fields.nProgress += 1;
			if(Fields.nProgress > 100)
			{
				Fields.nProgress = 0;
			}
			// Besetzen der anwenderseitigen Felder. Sie können bei jedem Feuern anders besetzt werden.
			brsstrcpy((UDINT)&Fields.Message.Locale, (UDINT)&"en");
			brsstrcpy((UDINT)&Fields.Message.Text, (UDINT)&"Progress at Task 'SrvEvntC' has changed to '");
			brsitoa((DINT)Fields.nProgress, (UDINT)&sHelp);
			brsstrcat((UDINT)&Fields.Message.Text, (UDINT)&sHelp);
			brsstrcat((UDINT)&Fields.Message.Text, (UDINT)&"'.");
			Fields.nSeverity = (UINT)BrbGetRandomUdint(1, 500);
			Fields.Context.nUsint = (USINT)BrbGetRandomUdint(0,255);
			Fields.Context.rReal = BrbGetRandomPercent();
			BrbUsintToHex(Fields.Context.nUsint, Fields.Context.sString, sizeof(Fields.Context.sString), 0);
			Step.eStepNr = eSTEP_FIRE;
			break;

		case eSTEP_FIRE:
			fbUaSrv_FireEvent.Execute = 1;
			if(fbUaSrv_FireEvent.Done == 1)
			{
				fbUaSrv_FireEvent.Execute = 0;
				Step.eStepNr = eSTEP_DELAY;
			}
			else if(fbUaSrv_FireEvent.Error == 1)
			{
				fbUaSrv_FireEvent.Execute = 0;
				if(fbUaSrv_FireEvent.ErrorID > 0)
				{
					Step.eErrorStep = eSTEP_FIRE;
					Step.nErrorId = fbUaSrv_FireEvent.ErrorID;
					Step.nFieldIndex = -1;
				}
				else
				{
					// Fehler in einem der Fields
					for(nFieldIndex=0; nFieldIndex<fbUaSrv_FireEvent.EventFieldCount; nFieldIndex++)
					{
						if(Fields.FieldCfg[nFieldIndex].ErrorID > 0)
						{
							Step.eErrorStep = eSTEP_FIRE;
							Step.nErrorId = Fields.FieldCfg[nFieldIndex].ErrorID;
							Step.nFieldIndex = (INT)nFieldIndex;
						}
					}
				}
				Step.eStepNr = eSTEP_DELAY;
			}
			break;

	}

	// Aufruf des FB's
	UaSrv_GetNamespaceIndex(&fbUaSrv_GetNamespaceIndex);
	TON(&fbDelay);
	UaSrv_FireEvent(&fbUaSrv_FireEvent);

}

void _EXIT Exit(void)
{
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)
