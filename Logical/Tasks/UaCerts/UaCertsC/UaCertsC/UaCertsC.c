
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

void _INIT ProgramInit(void)
{
	brsmemset((UDINT)&Opc, 0, sizeof(Opc));
	brsstrcpy((UDINT)&Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.MethodName, (UDINT)&"OwnGetCertificateList"); // Name der Methode wie in 'Methods.uam' angegeben
	brsstrcpy((UDINT)&Opc.OwnGenerate.fbUaSrv_MethodOperate.MethodName, (UDINT)&"OwnGenerate"); // Name der Methode wie in 'Methods.uam' angegeben
	brsstrcpy((UDINT)&Opc.OwnImport.fbUaSrv_MethodOperate.MethodName, (UDINT)&"OwnImport"); // Name der Methode wie in 'Methods.uam' angegeben
	brsstrcpy((UDINT)&Opc.OwnDelete.fbUaSrv_MethodOperate.MethodName, (UDINT)&"OwnDelete"); // Name der Methode wie in 'Methods.uam' angegeben

	brsstrcpy((UDINT)&Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.MethodName, (UDINT)&"ForeignGetCertificateList"); // Name der Methode wie in 'Methods.uam' angegeben
	brsstrcpy((UDINT)&Opc.ForeignImport.fbUaSrv_MethodOperate.MethodName, (UDINT)&"ForeignImport"); // Name der Methode wie in 'Methods.uam' angegeben
	brsstrcpy((UDINT)&Opc.ForeignDelete.fbUaSrv_MethodOperate.MethodName, (UDINT)&"ForeignDelete"); // Name der Methode wie in 'Methods.uam' angegeben

	brsstrcpy((UDINT)&Opc.SslGetCfgList.fbUaSrv_MethodOperate.MethodName, (UDINT)&"SslGetCfgList"); // Name der Methode wie in 'Methods.uam' angegeben
	brsstrcpy((UDINT)&Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.MethodName, (UDINT)&"SslGetTrustedCertList"); // Name der Methode wie in 'Methods.uam' angegeben

	brsstrcpy((UDINT)&Opc.Warmstart.fbUaSrv_MethodOperate.MethodName, (UDINT)&"Warmstart"); // Name der Methode wie in 'Methods.uam' angegeben
}

void _CYCLIC ProgramCyclic(void)
{

	// Methode 'OwnGetCertificateList'
	switch(Opc.OwnGetCertificateList.Step.nStepNr)
	{
		case 0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Execute = 1;
			Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Action = UaMoa_CheckIsCalled;
			if(Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Execute = 0;
				if(Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.IsCalled == 1)
				{
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.OwnGetCertificateList.nCallCount += 1;	// Nur zur Diagnose
					Opc.OwnGetCertificateList.Out_ErrorId = 0;
					Opc.OwnGetCertificateList.Step.nStepNr += 1;
				}
			}
			else if(Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Error == 1)
			{
				Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Execute = 0;
				Opc.OwnGetCertificateList.Step.nErrorStep = Opc.OwnGetCertificateList.Step.nStepNr;
				Opc.OwnGetCertificateList.Step.eAction = Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Action;
				Opc.OwnGetCertificateList.Step.nErrorId = Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.ErrorID;
			}
			break;

		case 1:	// Vorbereitung zum Auslesen der Liste
			Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Execute = 0;
			brsstrcpy((UDINT)&Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Name, (UDINT)&"");
			Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Index = 0;
			brsmemset((UDINT)&Opc.OwnGetCertificateList.Out_CertificatesList, 0, sizeof(Opc.OwnGetCertificateList.Out_CertificatesList));
			Opc.OwnGetCertificateList.Step.nStepNr += 1;
			break;

		case 2:	// Nächsten Eintrag auslesen
			if(Opc.OwnGetCertificateList.Out_CertificatesList.nLength <= (DINT)OPCUA_CERTS_INDEX_MAX)
			{
				Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Execute = 1;
				if(Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Busy == 0)
				{
					if(Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Done == 1)
					{
						// Eintrag auf Ausgangs-Argument übertragen
						brsmemcpy((UDINT)&Opc.OwnGetCertificateList.Out_CertificatesList.Data[Opc.OwnGetCertificateList.Out_CertificatesList.nLength], (UDINT)&Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Details, sizeof(ArCertDetailsType));
						// Nächsten Eintrag lesen
						Opc.OwnGetCertificateList.Out_CertificatesList.nLength += 1;
						Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Index = (UDINT)Opc.OwnGetCertificateList.Out_CertificatesList.nLength;
						Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Execute = 0;
					}
					else if(Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Error == 1)
					{
						if(Opc.OwnGetCertificateList.fbArCertGetOwnDetails.StatusID == arCERT_ERR_CERTIFICATE_NOT_FOUND)
						{
							// Alle Einträge sind gelesen
							Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Execute = 0;
							Opc.OwnGetCertificateList.Step.nStepNr += 1;
						}
						else
						{
							// Fehler beim Auslesen
							Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Execute = 0;
							Opc.OwnGetCertificateList.Out_ErrorId = Opc.OwnGetCertificateList.fbArCertGetOwnDetails.StatusID;
							Opc.OwnGetCertificateList.Step.nStepNr += 1;
						}
					}
				}
			}
			else
			{
				// Das SPS-Array ist nicht genügend groß, um weitere Einträge aufzunehmen
				Opc.OwnGetCertificateList.Out_ErrorId = 12189696; // = 0x00BA0000 = Good_ResultsMayBeIncomplete
				Opc.OwnGetCertificateList.Step.nStepNr += 1;
			}
			break;

		case 3:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Execute = 1;
			Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Action = UaMoa_Finished;
			if(Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Execute = 0;
				Opc.OwnGetCertificateList.Step.nStepNr = 0;
			}
			else if(Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Error == 1)
			{
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Execute = 0;
				Opc.OwnGetCertificateList.Step.nErrorStep = Opc.OwnGetCertificateList.Step.nStepNr;
				Opc.OwnGetCertificateList.Step.eAction = Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Action;
				Opc.OwnGetCertificateList.Step.nErrorId = Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.ErrorID;
				Opc.OwnGetCertificateList.Step.nStepNr = 0;
			}
			break;

	}
	UaSrv_MethodOperate(&Opc.OwnGetCertificateList.fbUaSrv_MethodOperate);
	ArCertGetOwnDetails(&Opc.OwnGetCertificateList.fbArCertGetOwnDetails);

	// Methode 'OwnGenerate'
	switch(Opc.OwnGenerate.Step.nStepNr)
	{
		case 0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.OwnGenerate.fbUaSrv_MethodOperate.Execute = 1;
			Opc.OwnGenerate.fbUaSrv_MethodOperate.Action = UaMoa_CheckIsCalled;
			if(Opc.OwnGenerate.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.OwnGenerate.fbUaSrv_MethodOperate.Execute = 0;
				if(Opc.OwnGenerate.fbUaSrv_MethodOperate.IsCalled == 1)
				{
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.OwnGenerate.nCallCount += 1;	// Nur zur Diagnose
					Opc.OwnGenerate.Out_ErrorId = 0;
					Opc.OwnGenerate.Step.nStepNr += 1;
				}
			}
			else if(Opc.OwnGenerate.fbUaSrv_MethodOperate.Error == 1)
			{
				Opc.OwnGenerate.fbUaSrv_MethodOperate.Execute = 0;
				Opc.OwnGenerate.Step.nErrorStep = Opc.OwnGenerate.Step.nStepNr;
				Opc.OwnGenerate.Step.eAction = Opc.OwnGenerate.fbUaSrv_MethodOperate.Action;
				Opc.OwnGenerate.Step.nErrorId = Opc.OwnGenerate.fbUaSrv_MethodOperate.ErrorID;
			}
			break;

		case 1:	// Vorbereitung zum Erzeugen des OpcUa-Zertifikats
			Opc.OwnGenerate.fbArCertGenerateX.Execute = 0;
			brsstrcpy((UDINT)&Opc.OwnGenerate.fbArCertGenerateX.Name, (UDINT)&Opc.OwnGenerate.In_Parameter.sName);
			brsstrcpy((UDINT)&Opc.OwnGenerate.fbArCertGenerateX.PrivateKeyName, (UDINT)&Opc.OwnGenerate.In_Parameter.sPrivateKeyName);
			brsstrcpy((UDINT)&Opc.OwnGenerate.fbArCertGenerateX.PrivateKeyPassword, (UDINT)&Opc.OwnGenerate.In_Parameter.sPrivateKeyPassword);
			Opc.OwnGenerate.fbArCertGenerateX.KeySize = Opc.OwnGenerate.In_Parameter.eKeySize;
			brsstrcpy((UDINT)&Opc.OwnGenerate.fbArCertGenerateX.CountryCode, (UDINT)&Opc.OwnGenerate.In_Parameter.sCountryCode);
			brsstrcpy((UDINT)&Opc.OwnGenerate.fbArCertGenerateX.StateProvince, (UDINT)&Opc.OwnGenerate.In_Parameter.sStateProvince);
			brsstrcpy((UDINT)&Opc.OwnGenerate.fbArCertGenerateX.Locality, (UDINT)&Opc.OwnGenerate.In_Parameter.sLocality);
			brsstrcpy((UDINT)&Opc.OwnGenerate.fbArCertGenerateX.Organization, (UDINT)&Opc.OwnGenerate.In_Parameter.sOrganization);
			brsstrcpy((UDINT)&Opc.OwnGenerate.fbArCertGenerateX.OrganizationUnit, (UDINT)&Opc.OwnGenerate.In_Parameter.sOrganizationUnit);
			brsstrcpy((UDINT)&Opc.OwnGenerate.fbArCertGenerateX.ContactEmail, (UDINT)&Opc.OwnGenerate.In_Parameter.sContactEmail);
			brsstrcpy((UDINT)&Opc.OwnGenerate.fbArCertGenerateX.CommonName, (UDINT)&Opc.OwnGenerate.In_Parameter.sCommonName);
			Opc.OwnGenerate.fbArCertGenerateX.ValidTimeSeconds = Opc.OwnGenerate.In_Parameter.nValidTimeSeconds;
			brsstrcpy((UDINT)&Opc.OwnGenerate.fbArCertGenerateX.URI, (UDINT)&Opc.OwnGenerate.In_Parameter.sUri);
			brsstrcpy((UDINT)&Opc.OwnGenerate.fbArCertGenerateX.DnsName, (UDINT)&Opc.OwnGenerate.In_Parameter.sDnsName);
			brsstrcpy((UDINT)&Opc.OwnGenerate.fbArCertGenerateX.IP, (UDINT)&Opc.OwnGenerate.In_Parameter.sIp);
			Opc.OwnGenerate.Step.nStepNr += 1;
			break;

		case 2:	// Erzeugen des OpcUa-Zertifikats
			Opc.OwnGenerate.fbArCertGenerateX.Execute = 1;
			if(Opc.OwnGenerate.fbArCertGenerateX.Busy == 0)
			{
				if(Opc.OwnGenerate.fbArCertGenerateX.Done == 1)
				{
					// Zertifikat wurde erstellt
					Opc.OwnGenerate.fbArCertGenerateX.Execute = 0;
					Opc.OwnGenerate.Step.nStepNr += 1;
				}
				else if(Opc.OwnGenerate.fbArCertGenerateX.Error == 1)
				{
					// Fehler beim Erstellen
					Opc.OwnGenerate.fbArCertGenerateX.Execute = 0;
					Opc.OwnGenerate.Out_ErrorId = Opc.OwnGenerate.fbArCertGenerateX.StatusID;
					Opc.OwnGenerate.Step.nStepNr += 1;
				}
			}
			break;

		case 3:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.OwnGenerate.fbUaSrv_MethodOperate.Execute = 1;
			Opc.OwnGenerate.fbUaSrv_MethodOperate.Action = UaMoa_Finished;
			if(Opc.OwnGenerate.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.OwnGenerate.fbUaSrv_MethodOperate.Execute = 0;
				Opc.OwnGenerate.Step.nStepNr = 0;
			}
			else if(Opc.OwnGenerate.fbUaSrv_MethodOperate.Error == 1)
			{
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.OwnGenerate.fbUaSrv_MethodOperate.Execute = 0;
				Opc.OwnGenerate.Step.nErrorStep = Opc.OwnGenerate.Step.nStepNr;
				Opc.OwnGenerate.Step.eAction = Opc.OwnGenerate.fbUaSrv_MethodOperate.Action;
				Opc.OwnGenerate.Step.nErrorId = Opc.OwnGenerate.fbUaSrv_MethodOperate.ErrorID;
				Opc.OwnGenerate.Step.nStepNr = 0;
			}
			break;

	}
	UaSrv_MethodOperate(&Opc.OwnGenerate.fbUaSrv_MethodOperate);
	ArCertGenerateX(&Opc.OwnGenerate.fbArCertGenerateX);

	// Methode 'OwnImport'
	switch(Opc.OwnImport.Step.nStepNr)
	{
		case 0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.OwnImport.fbUaSrv_MethodOperate.Execute = 1;
			Opc.OwnImport.fbUaSrv_MethodOperate.Action = UaMoa_CheckIsCalled;
			if(Opc.OwnImport.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.OwnImport.fbUaSrv_MethodOperate.Execute = 0;
				if(Opc.OwnImport.fbUaSrv_MethodOperate.IsCalled == 1)
				{
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.OwnImport.nCallCount += 1;	// Nur zur Diagnose
					Opc.OwnImport.Out_ErrorId = 0;
					Opc.OwnImport.Step.nStepNr += 1;
				}
			}
			else if(Opc.OwnImport.fbUaSrv_MethodOperate.Error == 1)
			{
				Opc.OwnImport.fbUaSrv_MethodOperate.Execute = 0;
				Opc.OwnImport.Step.nErrorStep = Opc.OwnImport.Step.nStepNr;
				Opc.OwnImport.Step.eAction = Opc.OwnImport.fbUaSrv_MethodOperate.Action;
				Opc.OwnImport.Step.nErrorId = Opc.OwnImport.fbUaSrv_MethodOperate.ErrorID;
			}
			break;

		case 1:	// Vorbereitung zum Löschen des öffentlichen Zertifikats
			Opc.OwnImport.fbArCertDeleteOwn.Execute = 0;
			if(Opc.OwnImport.In_Overwrite == 1)
			{
				brsstrcpy((UDINT)&Opc.OwnImport.fbArCertDeleteOwn.Name, (UDINT)&Opc.OwnImport.In_Name);
				Opc.OwnImport.Step.nStepNr += 1;
			}
			else
			{
				Opc.OwnImport.Step.nStepNr += 2;
			}
			break;

		case 2:	// Löschen des öffentlichen Zertifikats
			Opc.OwnImport.fbArCertDeleteOwn.Execute = 1;
			if(Opc.OwnImport.fbArCertDeleteOwn.Busy == 0)
			{
				if(Opc.OwnImport.fbArCertDeleteOwn.Done == 1)
				{
					// Zertifikat wurde gelöscht
					Opc.OwnImport.fbArCertDeleteOwn.Execute = 0;
					Opc.OwnImport.Step.nStepNr += 1;
				}
				else if(Opc.OwnImport.fbArCertDeleteOwn.Error == 1)
				{
					// Zertifikat ist nicht vorhanden. Fehler wird übergangen
					Opc.OwnImport.fbArCertDeleteOwn.Execute = 0;
					Opc.OwnImport.Step.nStepNr += 1;
				}
			}
			break;

		case 3:	// Vorbereitung zum Importieren des öffentlichen Zertifikats
			Opc.OwnImport.fbArCertImportOwn.Execute = 0;
			brsstrcpy((UDINT)&Opc.OwnImport.fbArCertImportOwn.Name, (UDINT)&Opc.OwnImport.In_Name);
			Opc.OwnImport.fbArCertImportOwn.Data = (UDINT)&Opc.OwnImport.In_Certificate.Data;
			Opc.OwnImport.fbArCertImportOwn.DataSize = (UDINT)Opc.OwnImport.In_Certificate.Length;
			Opc.OwnImport.Step.nStepNr += 1;
			break;

		case 4:	// Importieren des öffentlichen Zertifikats
			Opc.OwnImport.fbArCertImportOwn.Execute = 1;
			if(Opc.OwnImport.fbArCertImportOwn.Busy == 0)
			{
				if(Opc.OwnImport.fbArCertImportOwn.Done == 1)
				{
					// Zertifikat wurde importiert
					Opc.OwnImport.fbArCertImportOwn.Execute = 0;
					Opc.OwnImport.Step.nStepNr += 1;
				}
				else if(Opc.OwnImport.fbArCertImportOwn.Error == 1)
				{
					// Fehler beim Importieren
					Opc.OwnImport.fbArCertImportOwn.Execute = 0;
					Opc.OwnImport.Out_ErrorId = Opc.OwnImport.fbArCertImportOwn.StatusID;
					Opc.OwnImport.Step.nStepNr += 1;
				}
			}
			break;

		case 5:	// Vorbereitung zum Löschen des privaten Keys
			Opc.OwnImport.fbArCertDeletePrivateKey.Execute = 0;
			if(Opc.OwnImport.In_Overwrite == 1)
			{
				brsstrcpy((UDINT)&Opc.OwnImport.fbArCertDeletePrivateKey.Name, (UDINT)&Opc.OwnImport.In_PrivateKeyName);
				Opc.OwnImport.Step.nStepNr += 1;
			}
			else
			{
				Opc.OwnImport.Step.nStepNr += 2;
			}
			break;

		case 6:	// Löschen des privaten Keys
			Opc.OwnImport.fbArCertDeletePrivateKey.Execute = 1;
			if(Opc.OwnImport.fbArCertDeletePrivateKey.Busy == 0)
			{
				if(Opc.OwnImport.fbArCertDeletePrivateKey.Done == 1)
				{
					// Key wurde gelöscht
					Opc.OwnImport.fbArCertDeletePrivateKey.Execute = 0;
					Opc.OwnImport.Step.nStepNr += 1;
				}
				else if(Opc.OwnImport.fbArCertDeletePrivateKey.Error == 1)
				{
					// Key ist nicht vorhanden. Fehler wird übergangen
					Opc.OwnImport.fbArCertDeleteOwn.Execute = 0;
					Opc.OwnImport.Step.nStepNr += 1;
				}
			}
			break;

		case 7:	// Vorbereitung zum Importieren des privaten Keys
			Opc.OwnImport.fbArCertImportPrivateKey.Execute = 0;
			brsstrcpy((UDINT)&Opc.OwnImport.fbArCertImportPrivateKey.Name, (UDINT)&Opc.OwnImport.In_PrivateKeyName);
			Opc.OwnImport.fbArCertImportPrivateKey.Data = (UDINT)&Opc.OwnImport.In_PrivateKey.Data;
			Opc.OwnImport.fbArCertImportPrivateKey.DataSize = (UDINT)Opc.OwnImport.In_PrivateKey.Length;
			Opc.OwnImport.Step.nStepNr += 1;
			break;

		case 8:	// Importieren des privaten Keys
			Opc.OwnImport.fbArCertImportPrivateKey.Execute = 1;
			if(Opc.OwnImport.fbArCertImportPrivateKey.Busy == 0)
			{
				if(Opc.OwnImport.fbArCertImportPrivateKey.Done == 1)
				{
					// Key wurde importiert
					Opc.OwnImport.fbArCertImportPrivateKey.Execute = 0;
					Opc.OwnImport.Step.nStepNr += 1;
				}
				else if(Opc.OwnImport.fbArCertImportPrivateKey.Error == 1)
				{
					// Fehler beim Importieren
					Opc.OwnImport.fbArCertImportPrivateKey.Execute = 0;
					Opc.OwnImport.Out_ErrorId = Opc.OwnImport.fbArCertImportPrivateKey.StatusID;
					Opc.OwnImport.Step.nStepNr += 1;
				}
			}
			break;

		case 9:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.OwnImport.fbUaSrv_MethodOperate.Execute = 1;
			Opc.OwnImport.fbUaSrv_MethodOperate.Action = UaMoa_Finished;
			if(Opc.OwnImport.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.OwnImport.fbUaSrv_MethodOperate.Execute = 0;
				Opc.OwnImport.Step.nStepNr = 0;
			}
			else if(Opc.OwnImport.fbUaSrv_MethodOperate.Error == 1)
			{
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.OwnImport.fbUaSrv_MethodOperate.Execute = 0;
				Opc.OwnImport.Step.nErrorStep = Opc.OwnImport.Step.nStepNr;
				Opc.OwnImport.Step.eAction = Opc.OwnImport.fbUaSrv_MethodOperate.Action;
				Opc.OwnImport.Step.nErrorId = Opc.OwnImport.fbUaSrv_MethodOperate.ErrorID;
				Opc.OwnImport.Step.nStepNr = 0;
			}
			break;

	}
	UaSrv_MethodOperate(&Opc.OwnImport.fbUaSrv_MethodOperate);
	ArCertDeleteOwn(&Opc.OwnImport.fbArCertDeleteOwn);
	ArCertImportOwn(&Opc.OwnImport.fbArCertImportOwn);
	ArCertDeletePrivateKey(&Opc.OwnImport.fbArCertDeletePrivateKey);
	ArCertImportPrivateKey(&Opc.OwnImport.fbArCertImportPrivateKey);

	// Methode 'OwnDelete'
	switch(Opc.OwnDelete.Step.nStepNr)
	{
		case 0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.OwnDelete.fbUaSrv_MethodOperate.Execute = 1;
			Opc.OwnDelete.fbUaSrv_MethodOperate.Action = UaMoa_CheckIsCalled;
			if(Opc.OwnDelete.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.OwnDelete.fbUaSrv_MethodOperate.Execute = 0;
				if(Opc.OwnDelete.fbUaSrv_MethodOperate.IsCalled == 1)
				{
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.OwnDelete.nCallCount += 1;	// Nur zur Diagnose
					Opc.OwnDelete.Out_ErrorId = 0;
					Opc.OwnDelete.Step.nStepNr += 1;
				}
			}
			else if(Opc.OwnDelete.fbUaSrv_MethodOperate.Error == 1)
			{
				Opc.OwnDelete.fbUaSrv_MethodOperate.Execute = 0;
				Opc.OwnDelete.Step.nErrorStep = Opc.OwnDelete.Step.nStepNr;
				Opc.OwnDelete.Step.eAction = Opc.OwnDelete.fbUaSrv_MethodOperate.Action;
				Opc.OwnDelete.Step.nErrorId = Opc.OwnDelete.fbUaSrv_MethodOperate.ErrorID;
			}
			break;

		case 1:	// Vorbereitung zum Löschen des öffentlichen Zertifikats
			Opc.OwnDelete.fbArCertDeleteOwn.Execute = 0;
			if(brsstrlen((UDINT)&Opc.OwnDelete.In_Name) > 0)
			{
				brsstrcpy((UDINT)&Opc.OwnDelete.fbArCertDeleteOwn.Name, (UDINT)&Opc.OwnDelete.In_Name);
				Opc.OwnDelete.Step.nStepNr += 1;
			}
			else
			{
				Opc.OwnDelete.Step.nStepNr += 2;
			}
			break;

		case 2:	// Löschen des öffentlichen Zertifikats
			Opc.OwnDelete.fbArCertDeleteOwn.Execute = 1;
			if(Opc.OwnDelete.fbArCertDeleteOwn.Busy == 0)
			{
				if(Opc.OwnDelete.fbArCertDeleteOwn.Done == 1)
				{
					// Zertifikat wurde gelöscht
					Opc.OwnDelete.fbArCertDeleteOwn.Execute = 0;
					Opc.OwnDelete.Step.nStepNr += 1;
				}
				else if(Opc.OwnDelete.fbArCertDeleteOwn.Error == 1)
				{
					if(Opc.OwnDelete.fbArCertDeleteOwn.StatusID == arCERT_ERR_CERTIFICATE_NOT_FOUND && Opc.OwnDelete.In_SuppressNotExistsError == 1)
					{
						// Fehler 'Certificate not found' soll unterdrückt werden
						Opc.OwnDelete.fbArCertDeleteOwn.Execute = 0;
						Opc.OwnDelete.Step.nStepNr += 1;
					}
					else
					{
						// Fehler beim Löschen
						Opc.OwnDelete.fbArCertDeleteOwn.Execute = 0;
						Opc.OwnDelete.Out_ErrorId = Opc.OwnDelete.fbArCertDeleteOwn.StatusID;
						Opc.OwnDelete.Step.nStepNr += 1;
					}
				}
			}
			break;

		case 3:	// Vorbereitung zum Löschen des privaten Keys
			Opc.OwnDelete.fbArCertDeletePrivateKey.Execute = 0;
			if(brsstrlen((UDINT)&Opc.OwnDelete.In_PrivateKeyName) > 0)
			{
				brsstrcpy((UDINT)&Opc.OwnDelete.fbArCertDeletePrivateKey.Name, (UDINT)&Opc.OwnDelete.In_PrivateKeyName);
				Opc.OwnDelete.Step.nStepNr += 1;
			}
			else
			{
				Opc.OwnDelete.Step.nStepNr += 2;
			}
			break;

		case 4:	// Löschen des privaten Keys
			Opc.OwnDelete.fbArCertDeletePrivateKey.Execute = 1;
			if(Opc.OwnDelete.fbArCertDeletePrivateKey.Busy == 0)
			{
				if(Opc.OwnDelete.fbArCertDeletePrivateKey.Done == 1)
				{
					// Zertifikat wurde gelöscht
					Opc.OwnDelete.fbArCertDeletePrivateKey.Execute = 0;
					Opc.OwnDelete.Step.nStepNr += 1;
				}
				else if(Opc.OwnDelete.fbArCertDeletePrivateKey.Error == 1)
				{
					if(Opc.OwnDelete.fbArCertDeletePrivateKey.StatusID == arCERT_ERR_CERTIFICATE_NOT_FOUND && Opc.OwnDelete.In_SuppressNotExistsError == 1)
					{
						// Fehler 'Certificate not found' soll unterdrückt werden
						Opc.OwnDelete.fbArCertDeletePrivateKey.Execute = 0;
						Opc.OwnDelete.Step.nStepNr += 1;
					}
					else
					{
						// Fehler beim Löschen
						Opc.OwnDelete.fbArCertDeletePrivateKey.Execute = 0;
						Opc.OwnDelete.Out_ErrorId = Opc.OwnDelete.fbArCertDeletePrivateKey.StatusID;
						Opc.OwnDelete.Step.nStepNr += 1;
					}
				}
			}
			break;

		case 5:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.OwnDelete.fbUaSrv_MethodOperate.Execute = 1;
			Opc.OwnDelete.fbUaSrv_MethodOperate.Action = UaMoa_Finished;
			if(Opc.OwnDelete.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.OwnDelete.fbUaSrv_MethodOperate.Execute = 0;
				Opc.OwnDelete.Step.nStepNr = 0;
			}
			else if(Opc.OwnDelete.fbUaSrv_MethodOperate.Error == 1)
			{
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.OwnDelete.fbUaSrv_MethodOperate.Execute = 0;
				Opc.OwnDelete.Step.nErrorStep = Opc.OwnDelete.Step.nStepNr;
				Opc.OwnDelete.Step.eAction = Opc.OwnDelete.fbUaSrv_MethodOperate.Action;
				Opc.OwnDelete.Step.nErrorId = Opc.OwnDelete.fbUaSrv_MethodOperate.ErrorID;
				Opc.OwnDelete.Step.nStepNr = 0;
			}
			break;

	}
	UaSrv_MethodOperate(&Opc.OwnDelete.fbUaSrv_MethodOperate);
	ArCertDeleteOwn(&Opc.OwnDelete.fbArCertDeleteOwn);
	ArCertDeletePrivateKey(&Opc.OwnDelete.fbArCertDeletePrivateKey);

	// Methode 'ForeignGetCertificateList'
	switch(Opc.ForeignGetCertificateList.Step.nStepNr)
	{
		case 0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Execute = 1;
			Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Action = UaMoa_CheckIsCalled;
			if(Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Execute = 0;
				if(Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.IsCalled == 1)
				{
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.ForeignGetCertificateList.nCallCount += 1;	// Nur zur Diagnose
					Opc.ForeignGetCertificateList.Out_ErrorId = 0;
					Opc.ForeignGetCertificateList.Step.nStepNr += 1;
				}
			}
			else if(Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Error == 1)
			{
				Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Execute = 0;
				Opc.ForeignGetCertificateList.Step.nErrorStep = Opc.ForeignGetCertificateList.Step.nStepNr;
				Opc.ForeignGetCertificateList.Step.eAction = Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Action;
				Opc.ForeignGetCertificateList.Step.nErrorId = Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.ErrorID;
			}
			break;

		case 1:	// Vorbereitung zum Auslesen der Liste
			Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Execute = 0;
			brsstrcpy((UDINT)&Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Name, (UDINT)&"");
			Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Index = 0;
			brsmemset((UDINT)&Opc.ForeignGetCertificateList.Out_CertificatesList, 0, sizeof(Opc.ForeignGetCertificateList.Out_CertificatesList));
			Opc.ForeignGetCertificateList.Step.nStepNr += 1;
			break;

		case 2:	// Nächsten Eintrag auslesen
			if(Opc.ForeignGetCertificateList.Out_CertificatesList.nLength <= (DINT)OPCUA_CERTS_INDEX_MAX)
			{
				Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Execute = 1;
				if(Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Busy == 0)
				{
					if(Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Done == 1)
					{
						// Eintrag auf Ausgangs-Argument übertragen
						brsmemcpy((UDINT)&Opc.ForeignGetCertificateList.Out_CertificatesList.Data[Opc.ForeignGetCertificateList.Out_CertificatesList.nLength], (UDINT)&Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Details, sizeof(ArCertDetailsType));
						// Nächsten Eintrag lesen
						Opc.ForeignGetCertificateList.Out_CertificatesList.nLength += 1;
						Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Index = (UDINT)Opc.ForeignGetCertificateList.Out_CertificatesList.nLength;
						Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Execute = 0;
					}
					else if(Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Error == 1)
					{
						if(Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.StatusID == arCERT_ERR_CERTIFICATE_NOT_FOUND)
						{
							// Alle Einträge sind gelesen
							Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Execute = 0;
							Opc.ForeignGetCertificateList.Step.nStepNr += 1;
						}
						else
						{
							// Fehler beim Auslesen
							Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Execute = 0;
							Opc.ForeignGetCertificateList.Out_ErrorId = Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.StatusID;
							Opc.ForeignGetCertificateList.Step.nStepNr += 1;
						}
					}
				}
			}
			else
			{
				// Das SPS-Array ist nicht genügend groß, um weitere Einträge aufzunehmen
				Opc.ForeignGetCertificateList.Out_ErrorId = 12189696; // = 0x00BA0000 = Good_ResultsMayBeIncomplete
				Opc.ForeignGetCertificateList.Step.nStepNr += 1;
			}
			break;

		case 3:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Execute = 1;
			Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Action = UaMoa_Finished;
			if(Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Execute = 0;
				Opc.ForeignGetCertificateList.Step.nStepNr = 0;
			}
			else if(Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Error == 1)
			{
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Execute = 0;
				Opc.ForeignGetCertificateList.Step.nErrorStep = Opc.ForeignGetCertificateList.Step.nStepNr;
				Opc.ForeignGetCertificateList.Step.eAction = Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Action;
				Opc.ForeignGetCertificateList.Step.nErrorId = Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.ErrorID;
				Opc.ForeignGetCertificateList.Step.nStepNr = 0;
			}
			break;

	}
	UaSrv_MethodOperate(&Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate);
	ArCertGetThirdPartyDetails(&Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails);

	// Methode 'ForeignImport'
	switch(Opc.ForeignImport.Step.nStepNr)
	{
		case 0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.ForeignImport.fbUaSrv_MethodOperate.Execute = 1;
			Opc.ForeignImport.fbUaSrv_MethodOperate.Action = UaMoa_CheckIsCalled;
			if(Opc.ForeignImport.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.ForeignImport.fbUaSrv_MethodOperate.Execute = 0;
				if(Opc.ForeignImport.fbUaSrv_MethodOperate.IsCalled == 1)
				{
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.ForeignImport.nCallCount += 1;	// Nur zur Diagnose
					Opc.ForeignImport.Out_ErrorId = 0;
					Opc.ForeignImport.Step.nStepNr += 1;
				}
			}
			else if(Opc.ForeignImport.fbUaSrv_MethodOperate.Error == 1)
			{
				Opc.ForeignImport.fbUaSrv_MethodOperate.Execute = 0;
				Opc.ForeignImport.Step.nErrorStep = Opc.ForeignImport.Step.nStepNr;
				Opc.ForeignImport.Step.eAction = Opc.ForeignImport.fbUaSrv_MethodOperate.Action;
				Opc.ForeignImport.Step.nErrorId = Opc.ForeignImport.fbUaSrv_MethodOperate.ErrorID;
			}
			break;

		case 1:	// Vorbereitung zum Löschen des öffentlichen Zertifikats
			Opc.ForeignImport.fbArCertDeleteThirdParty.Execute = 0;
			if(Opc.ForeignImport.In_Overwrite == 1)
			{
				brsstrcpy((UDINT)&Opc.ForeignImport.fbArCertDeleteThirdParty.Name, (UDINT)&Opc.ForeignImport.In_Name);
				Opc.ForeignImport.Step.nStepNr += 1;
			}
			else
			{
				Opc.ForeignImport.Step.nStepNr += 2;
			}
			break;

		case 2:	// Löschen des öffentlichen Zertifikats
			Opc.ForeignImport.fbArCertDeleteThirdParty.Execute = 1;
			if(Opc.ForeignImport.fbArCertDeleteThirdParty.Busy == 0)
			{
				if(Opc.ForeignImport.fbArCertDeleteThirdParty.Done == 1)
				{
					// Zertifikat wurde gelöscht
					Opc.ForeignImport.fbArCertDeleteThirdParty.Execute = 0;
					Opc.ForeignImport.Step.nStepNr += 1;
				}
				else if(Opc.ForeignImport.fbArCertDeleteThirdParty.Error == 1)
				{
					// Zertifikat ist nicht vorhanden. Fehler wird übergangen
					Opc.ForeignImport.fbArCertDeleteThirdParty.Execute = 0;
					Opc.ForeignImport.Step.nStepNr += 1;
				}
			}
			break;

		case 3:	// Vorbereitung zum Importieren des öffentlichen Zertifikats
			Opc.ForeignImport.fbArCertImportThirdParty.Execute = 0;
			brsstrcpy((UDINT)&Opc.ForeignImport.fbArCertImportThirdParty.Name, (UDINT)&Opc.ForeignImport.In_Name);
			Opc.ForeignImport.fbArCertImportThirdParty.Data = (UDINT)&Opc.ForeignImport.In_Certificate.Data;
			Opc.ForeignImport.fbArCertImportThirdParty.DataSize = (UDINT)Opc.ForeignImport.In_Certificate.Length;
			Opc.ForeignImport.Step.nStepNr += 1;
			break;

		case 4:	// Importieren des öffentlichen Zertifikats
			Opc.ForeignImport.fbArCertImportThirdParty.Execute = 1;
			if(Opc.ForeignImport.fbArCertImportThirdParty.Busy == 0)
			{
				if(Opc.ForeignImport.fbArCertImportThirdParty.Done == 1)
				{
					// Zertifikat wurde importiert
					Opc.ForeignImport.fbArCertImportThirdParty.Execute = 0;
					Opc.ForeignImport.Step.nStepNr += 1;
				}
				else if(Opc.ForeignImport.fbArCertImportThirdParty.Error == 1)
				{
					// Fehler beim Importieren
					Opc.ForeignImport.fbArCertImportThirdParty.Execute = 0;
					Opc.ForeignImport.Out_ErrorId = Opc.ForeignImport.fbArCertImportThirdParty.StatusID;
					Opc.ForeignImport.Step.nStepNr += 1;
				}
			}
			break;

		case 5:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.ForeignImport.fbUaSrv_MethodOperate.Execute = 1;
			Opc.ForeignImport.fbUaSrv_MethodOperate.Action = UaMoa_Finished;
			if(Opc.ForeignImport.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.ForeignImport.fbUaSrv_MethodOperate.Execute = 0;
				Opc.ForeignImport.Step.nStepNr = 0;
			}
			else if(Opc.ForeignImport.fbUaSrv_MethodOperate.Error == 1)
			{
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.ForeignImport.fbUaSrv_MethodOperate.Execute = 0;
				Opc.ForeignImport.Step.nErrorStep = Opc.ForeignImport.Step.nStepNr;
				Opc.ForeignImport.Step.eAction = Opc.ForeignImport.fbUaSrv_MethodOperate.Action;
				Opc.ForeignImport.Step.nErrorId = Opc.ForeignImport.fbUaSrv_MethodOperate.ErrorID;
				Opc.ForeignImport.Step.nStepNr = 0;
			}
			break;

	}
	UaSrv_MethodOperate(&Opc.ForeignImport.fbUaSrv_MethodOperate);
	ArCertDeleteThirdParty(&Opc.ForeignImport.fbArCertDeleteThirdParty);
	ArCertImportThirdParty(&Opc.ForeignImport.fbArCertImportThirdParty);

	// Methode 'ForeignDelete'
	switch(Opc.ForeignDelete.Step.nStepNr)
	{
		case 0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.ForeignDelete.fbUaSrv_MethodOperate.Execute = 1;
			Opc.ForeignDelete.fbUaSrv_MethodOperate.Action = UaMoa_CheckIsCalled;
			if(Opc.ForeignDelete.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.ForeignDelete.fbUaSrv_MethodOperate.Execute = 0;
				if(Opc.ForeignDelete.fbUaSrv_MethodOperate.IsCalled == 1)
				{
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.ForeignDelete.nCallCount += 1;	// Nur zur Diagnose
					Opc.ForeignDelete.Out_ErrorId = 0;
					Opc.ForeignDelete.Step.nStepNr += 1;
				}
			}
			else if(Opc.ForeignDelete.fbUaSrv_MethodOperate.Error == 1)
			{
				Opc.ForeignDelete.fbUaSrv_MethodOperate.Execute = 0;
				Opc.ForeignDelete.Step.nErrorStep = Opc.ForeignDelete.Step.nStepNr;
				Opc.ForeignDelete.Step.eAction = Opc.ForeignDelete.fbUaSrv_MethodOperate.Action;
				Opc.ForeignDelete.Step.nErrorId = Opc.ForeignDelete.fbUaSrv_MethodOperate.ErrorID;
			}
			break;

		case 1:	// Vorbereitung zum Löschen des öffentlichen Zertifikats
			Opc.ForeignDelete.fbArCertDeleteThirdParty.Execute = 0;
			if(brsstrlen((UDINT)&Opc.ForeignDelete.In_Name) > 0)
			{
				brsstrcpy((UDINT)&Opc.ForeignDelete.fbArCertDeleteThirdParty.Name, (UDINT)&Opc.ForeignDelete.In_Name);
				Opc.ForeignDelete.Step.nStepNr += 1;
			}
			else
			{
				Opc.ForeignDelete.Step.nStepNr += 2;
			}
			break;

		case 2:	// Löschen des öffentlichen Zertifikats
			Opc.ForeignDelete.fbArCertDeleteThirdParty.Execute = 1;
			if(Opc.ForeignDelete.fbArCertDeleteThirdParty.Busy == 0)
			{
				if(Opc.ForeignDelete.fbArCertDeleteThirdParty.Done == 1)
				{
					// Zertifikat wurde gelöscht
					Opc.ForeignDelete.fbArCertDeleteThirdParty.Execute = 0;
					Opc.ForeignDelete.Step.nStepNr += 1;
				}
				else if(Opc.ForeignDelete.fbArCertDeleteThirdParty.Error == 1)
				{
					if(Opc.ForeignDelete.fbArCertDeleteThirdParty.StatusID == arCERT_ERR_CERTIFICATE_NOT_FOUND && Opc.ForeignDelete.In_SuppressNotExistsError == 1)
					{
						// Fehler 'Certificate not found' soll unterdrückt werden
						Opc.ForeignDelete.fbArCertDeleteThirdParty.Execute = 0;
						Opc.ForeignDelete.Step.nStepNr += 1;
					}
					else
					{
						// Fehler beim Löschen
						Opc.ForeignDelete.fbArCertDeleteThirdParty.Execute = 0;
						Opc.ForeignDelete.Out_ErrorId = Opc.ForeignDelete.fbArCertDeleteThirdParty.StatusID;
						Opc.ForeignDelete.Step.nStepNr += 1;
					}
				}
			}
			break;

		case 3:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.ForeignDelete.fbUaSrv_MethodOperate.Execute = 1;
			Opc.ForeignDelete.fbUaSrv_MethodOperate.Action = UaMoa_Finished;
			if(Opc.ForeignDelete.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.ForeignDelete.fbUaSrv_MethodOperate.Execute = 0;
				Opc.ForeignDelete.Step.nStepNr = 0;
			}
			else if(Opc.ForeignDelete.fbUaSrv_MethodOperate.Error == 1)
			{
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.ForeignDelete.fbUaSrv_MethodOperate.Execute = 0;
				Opc.ForeignDelete.Step.nErrorStep = Opc.ForeignDelete.Step.nStepNr;
				Opc.ForeignDelete.Step.eAction = Opc.ForeignDelete.fbUaSrv_MethodOperate.Action;
				Opc.ForeignDelete.Step.nErrorId = Opc.ForeignDelete.fbUaSrv_MethodOperate.ErrorID;
				Opc.ForeignDelete.Step.nStepNr = 0;
			}
			break;

	}
	UaSrv_MethodOperate(&Opc.ForeignDelete.fbUaSrv_MethodOperate);
	ArCertDeleteThirdParty(&Opc.ForeignDelete.fbArCertDeleteThirdParty);

	// Methode 'SslGetCfgList'
	switch(Opc.SslGetCfgList.Step.nStepNr)
	{
		case 0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.SslGetCfgList.fbUaSrv_MethodOperate.Execute = 1;
			Opc.SslGetCfgList.fbUaSrv_MethodOperate.Action = UaMoa_CheckIsCalled;
			if(Opc.SslGetCfgList.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.SslGetCfgList.fbUaSrv_MethodOperate.Execute = 0;
				if(Opc.SslGetCfgList.fbUaSrv_MethodOperate.IsCalled == 1)
				{
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.SslGetCfgList.nCallCount += 1;	// Nur zur Diagnose
					Opc.SslGetCfgList.Out_ErrorId = 0;
					Opc.SslGetCfgList.Step.nStepNr += 1;
				}
			}
			else if(Opc.SslGetCfgList.fbUaSrv_MethodOperate.Error == 1)
			{
				Opc.SslGetCfgList.fbUaSrv_MethodOperate.Execute = 0;
				Opc.SslGetCfgList.Step.nErrorStep = Opc.SslGetCfgList.Step.nStepNr;
				Opc.SslGetCfgList.Step.eAction = Opc.SslGetCfgList.fbUaSrv_MethodOperate.Action;
				Opc.SslGetCfgList.Step.nErrorId = Opc.SslGetCfgList.fbUaSrv_MethodOperate.ErrorID;
			}
			break;

		case 1:	// Vorbereitung zum Auslesen der Cfg-Liste
			Opc.SslGetCfgList.fbArSslGetCfgDetails.Execute = 0;
			brsstrcpy((UDINT)&Opc.SslGetCfgList.fbArSslGetCfgDetails.Name, (UDINT)&"");
			Opc.SslGetCfgList.fbArSslGetCfgDetails.Index = 0;
			brsmemset((UDINT)&Opc.SslGetCfgList.Out_CfgList, 0, sizeof(Opc.SslGetCfgList.Out_CfgList));
			Opc.SslGetCfgList.Step.nStepNr += 1;
			break;

		case 2:	// Nächsten Cfg-Eintrag auslesen
			if(Opc.SslGetCfgList.Out_CfgList.nLength <= (DINT)OPCUA_SSLCFG_INDEX_MAX)
			{
				Opc.SslGetCfgList.fbArSslGetCfgDetails.Execute = 1;
				if(Opc.SslGetCfgList.fbArSslGetCfgDetails.Busy == 0)
				{
					if(Opc.SslGetCfgList.fbArSslGetCfgDetails.Done == 1)
					{
						// Cfg-Eintrag auf Ausgangs-Argument übertragen
						brsmemcpy((UDINT)&Opc.SslGetCfgList.Out_CfgList.Data[Opc.SslGetCfgList.Out_CfgList.nLength], (UDINT)&Opc.SslGetCfgList.fbArSslGetCfgDetails.Details, sizeof(ArSslCfgDetailsType));
						// Nächsten Eintrag lesen
						Opc.SslGetCfgList.Out_CfgList.nLength += 1;
						Opc.SslGetCfgList.fbArSslGetCfgDetails.Index = (UDINT)Opc.SslGetCfgList.Out_CfgList.nLength;
						Opc.SslGetCfgList.fbArSslGetCfgDetails.Execute = 0;
					}
					else if(Opc.SslGetCfgList.fbArSslGetCfgDetails.Error == 1)
					{
						if(Opc.SslGetCfgList.fbArSslGetCfgDetails.StatusID == arSSL_ERR_SSL_CFG_NOT_FOUND)
						{
							// Alle Cfg-Einträge sind gelesen
							Opc.SslGetCfgList.fbArSslGetCfgDetails.Execute = 0;
							Opc.SslGetCfgList.Step.nStepNr += 1;
						}
						else
						{
							// Fehler beim Auslesen
							Opc.SslGetCfgList.fbArSslGetCfgDetails.Execute = 0;
							Opc.SslGetCfgList.Out_ErrorId = Opc.SslGetCfgList.fbArSslGetCfgDetails.StatusID;
							Opc.SslGetCfgList.Step.nStepNr += 1;
						}
					}
				}
			}
			else
			{
				// Das SPS-Array ist nicht genügend groß, um weitere Einträge aufzunehmen
				Opc.SslGetCfgList.Out_ErrorId = 12189696; // = 0x00BA0000 = Good_ResultsMayBeIncomplete
				Opc.SslGetCfgList.Step.nStepNr += 1;
			}
			break;

		case 3:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.SslGetCfgList.fbUaSrv_MethodOperate.Execute = 1;
			Opc.SslGetCfgList.fbUaSrv_MethodOperate.Action = UaMoa_Finished;
			if(Opc.SslGetCfgList.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.SslGetCfgList.fbUaSrv_MethodOperate.Execute = 0;
				Opc.SslGetCfgList.Step.nStepNr = 0;
			}
			else if(Opc.SslGetCfgList.fbUaSrv_MethodOperate.Error == 1)
			{
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.SslGetCfgList.fbUaSrv_MethodOperate.Execute = 0;
				Opc.SslGetCfgList.Step.nErrorStep = Opc.SslGetCfgList.Step.nStepNr;
				Opc.SslGetCfgList.Step.eAction = Opc.SslGetCfgList.fbUaSrv_MethodOperate.Action;
				Opc.SslGetCfgList.Step.nErrorId = Opc.SslGetCfgList.fbUaSrv_MethodOperate.ErrorID;
				Opc.SslGetCfgList.Step.nStepNr = 0;
			}
			break;

	}
	UaSrv_MethodOperate(&Opc.SslGetCfgList.fbUaSrv_MethodOperate);
	ArSslGetCfgDetails(&Opc.SslGetCfgList.fbArSslGetCfgDetails);

	// Methode 'SslGetTrustedCertList'
	switch(Opc.SslGetTrustedCertList.Step.nStepNr)
	{
		case 0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Execute = 1;
			Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Action = UaMoa_CheckIsCalled;
			if(Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Execute = 0;
				if(Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.IsCalled == 1)
				{
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.SslGetTrustedCertList.nCallCount += 1;	// Nur zur Diagnose
					Opc.SslGetTrustedCertList.Out_ErrorId = 0;
					Opc.SslGetTrustedCertList.Step.nStepNr += 1;
				}
			}
			else if(Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Error == 1)
			{
				Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Execute = 0;
				Opc.SslGetTrustedCertList.Step.nErrorStep = Opc.SslGetTrustedCertList.Step.nStepNr;
				Opc.SslGetTrustedCertList.Step.eAction = Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Action;
				Opc.SslGetTrustedCertList.Step.nErrorId = Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.ErrorID;
			}
			break;

		case 1:	// Vorbereitung zum Auslesen der Liste
			Opc.SslGetTrustedCertList.fbArSslGetCertificate.Execute = 0;
			brsstrcpy((UDINT)&Opc.SslGetTrustedCertList.fbArSslGetCertificate.Name, (UDINT)&Opc.SslGetTrustedCertList.In_CfgName);
			Opc.SslGetTrustedCertList.fbArSslGetCertificate.Index = 0;
			brsmemset((UDINT)&Opc.SslGetTrustedCertList.Out_TrustedCertNameList, 0, sizeof(Opc.SslGetTrustedCertList.Out_TrustedCertNameList));
			Opc.SslGetTrustedCertList.Step.nStepNr += 1;
			break;

		case 2:	// Nächsten Eintrag auslesen
			if(Opc.SslGetTrustedCertList.Out_TrustedCertNameList.nLength <= (DINT)OPCUA_CERTS_INDEX_MAX)
			{
				Opc.SslGetTrustedCertList.fbArSslGetCertificate.Execute = 1;
				if(Opc.SslGetTrustedCertList.fbArSslGetCertificate.Busy == 0)
				{
					if(Opc.SslGetTrustedCertList.fbArSslGetCertificate.Done == 1)
					{
						// Eintrag auf Ausgangs-Argument übertragen
						brsstrcpy((UDINT)&Opc.SslGetTrustedCertList.Out_TrustedCertNameList.Data[Opc.SslGetTrustedCertList.Out_TrustedCertNameList.nLength], (UDINT)&Opc.SslGetTrustedCertList.fbArSslGetCertificate.TrustedCertificate);
						// Nächsten Eintrag lesen
						Opc.SslGetTrustedCertList.Out_TrustedCertNameList.nLength += 1;
						Opc.SslGetTrustedCertList.fbArSslGetCertificate.Index = (UDINT)Opc.SslGetTrustedCertList.Out_TrustedCertNameList.nLength;
						Opc.SslGetTrustedCertList.fbArSslGetCertificate.Execute = 0;
					}
					else if(Opc.SslGetTrustedCertList.fbArSslGetCertificate.Error == 1)
					{
						if(Opc.SslGetTrustedCertList.fbArSslGetCertificate.StatusID == arSSL_ERR_INDEX_OUT_OF_RANGE)
						{
							// Alle Einträge sind gelesen
							Opc.SslGetTrustedCertList.fbArSslGetCertificate.Execute = 0;
							Opc.SslGetTrustedCertList.Step.nStepNr += 1;
						}
						else
						{
							// Fehler beim Auslesen
							Opc.SslGetTrustedCertList.fbArSslGetCertificate.Execute = 0;
							Opc.SslGetTrustedCertList.Out_ErrorId = Opc.SslGetTrustedCertList.fbArSslGetCertificate.StatusID;
							Opc.SslGetTrustedCertList.Step.nStepNr += 1;
						}
					}
				}
			}
			else
			{
				// Das SPS-Array ist nicht genügend groß, um weitere Einträge aufzunehmen
				Opc.SslGetTrustedCertList.Out_ErrorId = 12189696; // = 0x00BA0000 = Good_ResultsMayBeIncomplete
				Opc.SslGetTrustedCertList.Step.nStepNr += 1;
			}
			break;

		case 3:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Execute = 1;
			Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Action = UaMoa_Finished;
			if(Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Execute = 0;
				Opc.SslGetTrustedCertList.Step.nStepNr = 0;
			}
			else if(Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Error == 1)
			{
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Execute = 0;
				Opc.SslGetTrustedCertList.Step.nErrorStep = Opc.SslGetTrustedCertList.Step.nStepNr;
				Opc.SslGetTrustedCertList.Step.eAction = Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Action;
				Opc.SslGetTrustedCertList.Step.nErrorId = Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.ErrorID;
				Opc.SslGetTrustedCertList.Step.nStepNr = 0;
			}
			break;

	}
	UaSrv_MethodOperate(&Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate);
	ArSslGetCertificate(&Opc.SslGetTrustedCertList.fbArSslGetCertificate);

	// Methode 'Warmstart'
	switch(Opc.Warmstart.Step.nStepNr)
	{
		case 0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.Warmstart.fbUaSrv_MethodOperate.Execute = 1;
			Opc.Warmstart.fbUaSrv_MethodOperate.Action = UaMoa_CheckIsCalled;
			if(Opc.Warmstart.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.Warmstart.fbUaSrv_MethodOperate.Execute = 0;
				if(Opc.Warmstart.fbUaSrv_MethodOperate.IsCalled == 1)
				{
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.Warmstart.nCallCount += 1;	// Nur zur Diagnose
					Opc.Warmstart.Step.nStepNr += 1;
				}
			}
			else if(Opc.Warmstart.fbUaSrv_MethodOperate.Error == 1)
			{
				Opc.Warmstart.fbUaSrv_MethodOperate.Execute = 0;
				Opc.Warmstart.Step.nErrorStep = Opc.Warmstart.Step.nStepNr;
				Opc.Warmstart.Step.eAction = Opc.Warmstart.fbUaSrv_MethodOperate.Action;
				Opc.Warmstart.Step.nErrorId = Opc.Warmstart.fbUaSrv_MethodOperate.ErrorID;
			}
			break;

		case 1:	// Verzögerung für das Auslösen des Warmstarts starten
			// Der Warmstart wird verzögert ausgelöst, damit vom Server die Rückmeldung noch geschickt werden kann
			Opc.Warmstart.fbTon.PT = 2000; // = 2s
			Opc.Warmstart.fbTon.IN = 1;
			Opc.Warmstart.Step.nStepNr += 1;
			break;

		case 2:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.Warmstart.fbUaSrv_MethodOperate.Execute = 1;
			Opc.Warmstart.fbUaSrv_MethodOperate.Action = UaMoa_Finished;
			if(Opc.Warmstart.fbUaSrv_MethodOperate.Done == 1)
			{
				Opc.Warmstart.fbUaSrv_MethodOperate.Execute = 0;
				Opc.Warmstart.Step.nStepNr = 0;
			}
			else if(Opc.Warmstart.fbUaSrv_MethodOperate.Error == 1)
			{
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.Warmstart.fbUaSrv_MethodOperate.Execute = 0;
				Opc.Warmstart.Step.nErrorStep = Opc.Warmstart.Step.nStepNr;
				Opc.Warmstart.Step.eAction = Opc.Warmstart.fbUaSrv_MethodOperate.Action;
				Opc.Warmstart.Step.nErrorId = Opc.Warmstart.fbUaSrv_MethodOperate.ErrorID;
				Opc.Warmstart.Step.nStepNr = 0;
			}
			break;

	}
	UaSrv_MethodOperate(&Opc.Warmstart.fbUaSrv_MethodOperate);
	TON(&Opc.Warmstart.fbTon);
	if(Opc.Warmstart.fbTon.Q == 1)
	{
		Opc.Warmstart.fbTon.IN = 0;
		SYSreset(1, 1); // Warmstart auslösen
	}

}

void _EXIT ProgramExit(void)
{

}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)
