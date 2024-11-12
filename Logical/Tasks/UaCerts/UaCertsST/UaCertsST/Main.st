
PROGRAM _INIT
	brsmemset(ADR(Opc), 0, SIZEOF(Opc));
	Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.MethodName := 'OwnGetCertificateList'; // Name der Methode wie in 'Methods.uam' angegeben
	Opc.OwnGenerate.fbUaSrv_MethodOperate.MethodName := 'OwnGenerate'; // Name der Methode wie in 'Methods.uam' angegeben
	Opc.OwnImport.fbUaSrv_MethodOperate.MethodName := 'OwnImport'; // Name der Methode wie in 'Methods.uam' angegeben
	Opc.OwnDelete.fbUaSrv_MethodOperate.MethodName := 'OwnDelete'; // Name der Methode wie in 'Methods.uam' angegeben

	Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.MethodName := 'ForeignGetCertificateList'; // Name der Methode wie in 'Methods.uam' angegeben
	Opc.ForeignImport.fbUaSrv_MethodOperate.MethodName := 'ForeignImport'; // Name der Methode wie in 'Methods.uam' angegeben
	Opc.ForeignDelete.fbUaSrv_MethodOperate.MethodName := 'ForeignDelete'; // Name der Methode wie in 'Methods.uam' angegeben

	Opc.SslGetCfgList.fbUaSrv_MethodOperate.MethodName := 'SslGetCfgList'; // Name der Methode wie in 'Methods.uam' angegeben
	Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.MethodName := 'SslGetTrustedCertList'; // Name der Methode wie in 'Methods.uam' angegeben

	Opc.Warmstart.fbUaSrv_MethodOperate.MethodName := 'Warmstart'; // Name der Methode wie in 'Methods.uam' angegeben
END_PROGRAM

PROGRAM _CYCLIC
	// Methode 'OwnGetCertificateList'
	CASE Opc.OwnGetCertificateList.Step.nStepNr OF
		0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Execute := 1;
			Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Action := UaMoa_CheckIsCalled;
			IF Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Execute := 0;
				IF Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.IsCalled = 1 THEN
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.OwnGetCertificateList.nCallCount := Opc.OwnGetCertificateList.nCallCount + 1;	// Nur zur Diagnose
					Opc.OwnGetCertificateList.Out_ErrorId := 0;
					Opc.OwnGetCertificateList.Step.nStepNr := Opc.OwnGetCertificateList.Step.nStepNr + 1;
				END_IF
			ELSIF Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Error = 1 THEN
					Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Execute := 0;
				Opc.OwnGetCertificateList.Step.nErrorStep := Opc.OwnGetCertificateList.Step.nStepNr;
				Opc.OwnGetCertificateList.Step.eAction := Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Action;
				Opc.OwnGetCertificateList.Step.nErrorId := Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.ErrorID;
			END_IF

		1:	// Vorbereitung zum Auslesen der Liste
			Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Execute := 0;
			Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Name := '';
			Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Index := 0;
			brsmemset(ADR(Opc.OwnGetCertificateList.Out_CertificatesList), 0, SIZEOF(Opc.OwnGetCertificateList.Out_CertificatesList));
			Opc.OwnGetCertificateList.Step.nStepNr := Opc.OwnGetCertificateList.Step.nStepNr + 1;

		2:	// Nächsten Eintrag auslesen
			IF Opc.OwnGetCertificateList.Out_CertificatesList.nLength <= OPCUA_CERTS_INDEX_MAX THEN
				Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Execute := 1;
				IF Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Busy = 0 THEN
					IF Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Done = 1 THEN
						// Eintrag auf Ausgangs-Argument übertragen
						brsmemcpy(ADR(Opc.OwnGetCertificateList.Out_CertificatesList.Data[Opc.OwnGetCertificateList.Out_CertificatesList.nLength]), ADR(Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Details), SIZEOF(ArCertDetailsType));
						// Nächsten Eintrag lesen
						Opc.OwnGetCertificateList.Out_CertificatesList.nLength := Opc.OwnGetCertificateList.Out_CertificatesList.nLength + 1;
						Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Index := Opc.OwnGetCertificateList.Out_CertificatesList.nLength;
						Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Execute := 0;
					ELSIF Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Error = 1 THEN
						IF Opc.OwnGetCertificateList.fbArCertGetOwnDetails.StatusID = arCERT_ERR_CERTIFICATE_NOT_FOUND THEN
							// Alle Einträge sind gelesen
							Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Execute := 0;
							Opc.OwnGetCertificateList.Step.nStepNr := Opc.OwnGetCertificateList.Step.nStepNr + 1;
						ELSE
							// Fehler beim Auslesen
							Opc.OwnGetCertificateList.fbArCertGetOwnDetails.Execute := 0;
							Opc.OwnGetCertificateList.Out_ErrorId := Opc.OwnGetCertificateList.fbArCertGetOwnDetails.StatusID;
							Opc.OwnGetCertificateList.Step.nStepNr := Opc.OwnGetCertificateList.Step.nStepNr + 1;
						END_IF
					END_IF
				END_IF
			ELSE
				// Das SPS-Array ist nicht genügend groß, um weitere Einträge aufzunehmen
				Opc.OwnGetCertificateList.Out_ErrorId := 12189696; // := 0x00BA0000 := Good_ResultsMayBeIncomplete
				Opc.OwnGetCertificateList.Step.nStepNr := Opc.OwnGetCertificateList.Step.nStepNr + 1;
			END_IF

		3:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Execute := 1;
			Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Action := UaMoa_Finished;
			IF Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Execute := 0;
				Opc.OwnGetCertificateList.Step.nStepNr := 0;
			ELSIF Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Error = 1 THEN
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Execute := 0;
				Opc.OwnGetCertificateList.Step.nErrorStep := Opc.OwnGetCertificateList.Step.nStepNr;
				Opc.OwnGetCertificateList.Step.eAction := Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.Action;
				Opc.OwnGetCertificateList.Step.nErrorId := Opc.OwnGetCertificateList.fbUaSrv_MethodOperate.ErrorID;
				Opc.OwnGetCertificateList.Step.nStepNr := 0;
			END_IF

	END_CASE
	Opc.OwnGetCertificateList.fbUaSrv_MethodOperate();
	Opc.OwnGetCertificateList.fbArCertGetOwnDetails();

		// Methode 'OwnGenerate'
	CASE Opc.OwnGenerate.Step.nStepNr OF
		0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.OwnGenerate.fbUaSrv_MethodOperate.Execute := 1;
			Opc.OwnGenerate.fbUaSrv_MethodOperate.Action := UaMoa_CheckIsCalled;
			IF Opc.OwnGenerate.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.OwnGenerate.fbUaSrv_MethodOperate.Execute := 0;
				IF Opc.OwnGenerate.fbUaSrv_MethodOperate.IsCalled = 1 THEN
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.OwnGenerate.nCallCount := Opc.OwnGenerate.nCallCount + 1;	// Nur zur Diagnose
					Opc.OwnGenerate.Out_ErrorId := 0;
					Opc.OwnGenerate.Step.nStepNr := Opc.OwnGenerate.Step.nStepNr + 1;
				END_IF
			ELSIF Opc.OwnGenerate.fbUaSrv_MethodOperate.Error = 1 THEN
				Opc.OwnGenerate.fbUaSrv_MethodOperate.Execute := 0;
				Opc.OwnGenerate.Step.nErrorStep := Opc.OwnGenerate.Step.nStepNr;
				Opc.OwnGenerate.Step.eAction := Opc.OwnGenerate.fbUaSrv_MethodOperate.Action;
				Opc.OwnGenerate.Step.nErrorId := Opc.OwnGenerate.fbUaSrv_MethodOperate.ErrorID;
			END_IF

		1:	// Vorbereitung zum Erzeugen des OpcUa-Zertifikats
			Opc.OwnGenerate.fbArCertGenerateX.Execute := 0;
			Opc.OwnGenerate.fbArCertGenerateX.Name := Opc.OwnGenerate.In_Parameter.sName;
			Opc.OwnGenerate.fbArCertGenerateX.PrivateKeyName := Opc.OwnGenerate.In_Parameter.sPrivateKeyName;
			Opc.OwnGenerate.fbArCertGenerateX.PrivateKeyPassword := Opc.OwnGenerate.In_Parameter.sPrivateKeyPassword;
			Opc.OwnGenerate.fbArCertGenerateX.KeySize := Opc.OwnGenerate.In_Parameter.eKeySize;
			Opc.OwnGenerate.fbArCertGenerateX.CountryCode := Opc.OwnGenerate.In_Parameter.sCountryCode;
			Opc.OwnGenerate.fbArCertGenerateX.StateProvince := Opc.OwnGenerate.In_Parameter.sStateProvince;
			Opc.OwnGenerate.fbArCertGenerateX.Locality := Opc.OwnGenerate.In_Parameter.sLocality;
			Opc.OwnGenerate.fbArCertGenerateX.Organization := Opc.OwnGenerate.In_Parameter.sOrganization;
			Opc.OwnGenerate.fbArCertGenerateX.OrganizationUnit := Opc.OwnGenerate.In_Parameter.sOrganizationUnit;
			Opc.OwnGenerate.fbArCertGenerateX.ContactEmail := Opc.OwnGenerate.In_Parameter.sContactEmail;
			Opc.OwnGenerate.fbArCertGenerateX.CommonName := Opc.OwnGenerate.In_Parameter.sCommonName;
			Opc.OwnGenerate.fbArCertGenerateX.ValidTimeSeconds := Opc.OwnGenerate.In_Parameter.nValidTimeSeconds;
			Opc.OwnGenerate.fbArCertGenerateX.URI := Opc.OwnGenerate.In_Parameter.sUri;
			Opc.OwnGenerate.fbArCertGenerateX.DnsName := Opc.OwnGenerate.In_Parameter.sDnsName;
			Opc.OwnGenerate.fbArCertGenerateX.IP := Opc.OwnGenerate.In_Parameter.sIp;
			Opc.OwnGenerate.Step.nStepNr := Opc.OwnGenerate.Step.nStepNr + 1;

		2:	// Erzeugen des OpcUa-Zertifikats
			Opc.OwnGenerate.fbArCertGenerateX.Execute := 1;
			IF Opc.OwnGenerate.fbArCertGenerateX.Busy = 0 THEN
				IF Opc.OwnGenerate.fbArCertGenerateX.Done = 1 THEN
					// Zertifikat wurde erstellt
					Opc.OwnGenerate.fbArCertGenerateX.Execute := 0;
					Opc.OwnGenerate.Step.nStepNr := Opc.OwnGenerate.Step.nStepNr + 1;
				ELSIF Opc.OwnGenerate.fbArCertGenerateX.Error = 1 THEN
					// Fehler beim Erstellen
					Opc.OwnGenerate.fbArCertGenerateX.Execute := 0;
					Opc.OwnGenerate.Out_ErrorId := Opc.OwnGenerate.fbArCertGenerateX.StatusID;
					Opc.OwnGenerate.Step.nStepNr := Opc.OwnGenerate.Step.nStepNr + 1;
				END_IF
			END_IF

		3:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.OwnGenerate.fbUaSrv_MethodOperate.Execute := 1;
			Opc.OwnGenerate.fbUaSrv_MethodOperate.Action := UaMoa_Finished;
			IF Opc.OwnGenerate.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.OwnGenerate.fbUaSrv_MethodOperate.Execute := 0;
				Opc.OwnGenerate.Step.nStepNr := 0;
			ELSIF Opc.OwnGenerate.fbUaSrv_MethodOperate.Error = 1 THEN
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.OwnGenerate.fbUaSrv_MethodOperate.Execute := 0;
				Opc.OwnGenerate.Step.nErrorStep := Opc.OwnGenerate.Step.nStepNr;
				Opc.OwnGenerate.Step.eAction := Opc.OwnGenerate.fbUaSrv_MethodOperate.Action;
				Opc.OwnGenerate.Step.nErrorId := Opc.OwnGenerate.fbUaSrv_MethodOperate.ErrorID;
				Opc.OwnGenerate.Step.nStepNr := 0;
			END_IF

	END_CASE
	Opc.OwnGenerate.fbUaSrv_MethodOperate();
	Opc.OwnGenerate.fbArCertGenerateX();

	// Methode 'OwnImport'
	CASE Opc.OwnImport.Step.nStepNr OF
		0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.OwnImport.fbUaSrv_MethodOperate.Execute := 1;
			Opc.OwnImport.fbUaSrv_MethodOperate.Action := UaMoa_CheckIsCalled;
			IF Opc.OwnImport.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.OwnImport.fbUaSrv_MethodOperate.Execute := 0;
				IF Opc.OwnImport.fbUaSrv_MethodOperate.IsCalled = 1 THEN
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.OwnImport.nCallCount := Opc.OwnImport.nCallCount + 1;	// Nur zur Diagnose
					Opc.OwnImport.Out_ErrorId := 0;
					Opc.OwnImport.Step.nStepNr := Opc.OwnImport.Step.nStepNr + 1;
				END_IF
			ELSIF Opc.OwnImport.fbUaSrv_MethodOperate.Error = 1 THEN
				Opc.OwnImport.fbUaSrv_MethodOperate.Execute := 0;
				Opc.OwnImport.Step.nErrorStep := Opc.OwnImport.Step.nStepNr;
				Opc.OwnImport.Step.eAction := Opc.OwnImport.fbUaSrv_MethodOperate.Action;
				Opc.OwnImport.Step.nErrorId := Opc.OwnImport.fbUaSrv_MethodOperate.ErrorID;
			END_IF

		1:	// Vorbereitung zum Löschen des öffentlichen Zertifikats
			Opc.OwnImport.fbArCertDeleteOwn.Execute := 0;
			IF Opc.OwnImport.In_Overwrite = 1 THEN
				Opc.OwnImport.fbArCertDeleteOwn.Name := Opc.OwnImport.In_Name;
				Opc.OwnImport.Step.nStepNr := Opc.OwnImport.Step.nStepNr + 1;
			ELSE
				Opc.OwnImport.Step.nStepNr := Opc.OwnImport.Step.nStepNr + 2;
			END_IF

		2:	// Löschen des öffentlichen Zertifikats
			Opc.OwnImport.fbArCertDeleteOwn.Execute := 1;
			IF Opc.OwnImport.fbArCertDeleteOwn.Busy = 0 THEN
				IF Opc.OwnImport.fbArCertDeleteOwn.Done = 1 THEN
					// Zertifikat wurde gelöscht
					Opc.OwnImport.fbArCertDeleteOwn.Execute := 0;
					Opc.OwnImport.Step.nStepNr := Opc.OwnImport.Step.nStepNr + 1;
				ELSIF Opc.OwnImport.fbArCertDeleteOwn.Error = 1 THEN
					// Zertifikat ist nicht vorhanden. Fehler wird übergangen
					Opc.OwnImport.fbArCertDeleteOwn.Execute := 0;
					Opc.OwnImport.Step.nStepNr := Opc.OwnImport.Step.nStepNr + 1;
				END_IF
			END_IF

		3:	// Vorbereitung zum Importieren des öffentlichen Zertifikats
			Opc.OwnImport.fbArCertImportOwn.Execute := 0;
			Opc.OwnImport.fbArCertImportOwn.Name := Opc.OwnImport.In_Name;
			Opc.OwnImport.fbArCertImportOwn.Data := ADR(Opc.OwnImport.In_Certificate.Data);
			Opc.OwnImport.fbArCertImportOwn.DataSize := Opc.OwnImport.In_Certificate.Length;
			Opc.OwnImport.Step.nStepNr := Opc.OwnImport.Step.nStepNr + 1;

		4:	// Importieren des öffentlichen Zertifikats
			Opc.OwnImport.fbArCertImportOwn.Execute := 1;
			IF Opc.OwnImport.fbArCertImportOwn.Busy = 0 THEN
				IF Opc.OwnImport.fbArCertImportOwn.Done = 1 THEN
					// Zertifikat wurde importiert
					Opc.OwnImport.fbArCertImportOwn.Execute := 0;
					Opc.OwnImport.Step.nStepNr := Opc.OwnImport.Step.nStepNr + 1;
				ELSIF Opc.OwnImport.fbArCertImportOwn.Error = 1 THEN
					// Fehler beim Importieren
					Opc.OwnImport.fbArCertImportOwn.Execute := 0;
					Opc.OwnImport.Out_ErrorId := Opc.OwnImport.fbArCertImportOwn.StatusID;
					Opc.OwnImport.Step.nStepNr := Opc.OwnImport.Step.nStepNr + 1;
				END_IF
			END_IF

		5:	// Vorbereitung zum Löschen des privaten Keys
			Opc.OwnImport.fbArCertDeletePrivateKey.Execute := 0;
			IF Opc.OwnImport.In_Overwrite = 1 THEN
				Opc.OwnImport.fbArCertDeletePrivateKey.Name := Opc.OwnImport.In_PrivateKeyName;
				Opc.OwnImport.Step.nStepNr := Opc.OwnImport.Step.nStepNr + 1;
			ELSE
				Opc.OwnImport.Step.nStepNr := Opc.OwnImport.Step.nStepNr + 2;
			END_IF

		6:	// Löschen des privaten Keys
			Opc.OwnImport.fbArCertDeletePrivateKey.Execute := 1;
			IF Opc.OwnImport.fbArCertDeletePrivateKey.Busy = 0 THEN
				IF Opc.OwnImport.fbArCertDeletePrivateKey.Done = 1 THEN
					// Key wurde gelöscht
					Opc.OwnImport.fbArCertDeletePrivateKey.Execute := 0;
					Opc.OwnImport.Step.nStepNr := Opc.OwnImport.Step.nStepNr + 1;
				ELSIF Opc.OwnImport.fbArCertDeletePrivateKey.Error = 1 THEN
				// Key ist nicht vorhanden. Fehler wird übergangen
					Opc.OwnImport.fbArCertDeleteOwn.Execute := 0;
					Opc.OwnImport.Step.nStepNr := Opc.OwnImport.Step.nStepNr + 1;
				END_IF
			END_IF

		7:	// Vorbereitung zum Importieren des privaten Keys
			Opc.OwnImport.fbArCertImportPrivateKey.Execute := 0;
			Opc.OwnImport.fbArCertImportPrivateKey.Name := Opc.OwnImport.In_PrivateKeyName;
			Opc.OwnImport.fbArCertImportPrivateKey.Data := ADR(Opc.OwnImport.In_PrivateKey.Data);
			Opc.OwnImport.fbArCertImportPrivateKey.DataSize := Opc.OwnImport.In_PrivateKey.Length;
			Opc.OwnImport.Step.nStepNr := Opc.OwnImport.Step.nStepNr + 1;

		8:	// Importieren des privaten Keys
			Opc.OwnImport.fbArCertImportPrivateKey.Execute := 1;
			IF Opc.OwnImport.fbArCertImportPrivateKey.Busy = 0 THEN
				IF Opc.OwnImport.fbArCertImportPrivateKey.Done = 1 THEN
				// Key wurde importiert
					Opc.OwnImport.fbArCertImportPrivateKey.Execute := 0;
					Opc.OwnImport.Step.nStepNr := Opc.OwnImport.Step.nStepNr + 1;
				ELSIF Opc.OwnImport.fbArCertImportPrivateKey.Error = 1 THEN
				// Fehler beim Importieren
					Opc.OwnImport.fbArCertImportPrivateKey.Execute := 0;
					Opc.OwnImport.Out_ErrorId := Opc.OwnImport.fbArCertImportPrivateKey.StatusID;
					Opc.OwnImport.Step.nStepNr := Opc.OwnImport.Step.nStepNr + 1;
				END_IF
			END_IF

		9:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.OwnImport.fbUaSrv_MethodOperate.Execute := 1;
			Opc.OwnImport.fbUaSrv_MethodOperate.Action := UaMoa_Finished;
			IF Opc.OwnImport.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.OwnImport.fbUaSrv_MethodOperate.Execute := 0;
				Opc.OwnImport.Step.nStepNr := 0;
			ELSIF Opc.OwnImport.fbUaSrv_MethodOperate.Error = 1 THEN
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.OwnImport.fbUaSrv_MethodOperate.Execute := 0;
				Opc.OwnImport.Step.nErrorStep := Opc.OwnImport.Step.nStepNr;
				Opc.OwnImport.Step.eAction := Opc.OwnImport.fbUaSrv_MethodOperate.Action;
				Opc.OwnImport.Step.nErrorId := Opc.OwnImport.fbUaSrv_MethodOperate.ErrorID;
				Opc.OwnImport.Step.nStepNr := 0;
			END_IF

	END_CASE
	Opc.OwnImport.fbUaSrv_MethodOperate();
	Opc.OwnImport.fbArCertDeleteOwn();
	Opc.OwnImport.fbArCertImportOwn();
	Opc.OwnImport.fbArCertDeletePrivateKey();
	Opc.OwnImport.fbArCertImportPrivateKey();

	// Methode 'OwnDelete'
	CASE Opc.OwnDelete.Step.nStepNr OF
		0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.OwnDelete.fbUaSrv_MethodOperate.Execute := 1;
			Opc.OwnDelete.fbUaSrv_MethodOperate.Action := UaMoa_CheckIsCalled;
			IF Opc.OwnDelete.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.OwnDelete.fbUaSrv_MethodOperate.Execute := 0;
				IF Opc.OwnDelete.fbUaSrv_MethodOperate.IsCalled = 1 THEN
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.OwnDelete.nCallCount := Opc.OwnDelete.nCallCount + 1;	// Nur zur Diagnose
					Opc.OwnDelete.Out_ErrorId := 0;
					Opc.OwnDelete.Step.nStepNr := Opc.OwnDelete.Step.nStepNr + 1;
				END_IF
			ELSIF Opc.OwnDelete.fbUaSrv_MethodOperate.Error = 1 THEN
				Opc.OwnDelete.fbUaSrv_MethodOperate.Execute := 0;
				Opc.OwnDelete.Step.nErrorStep := Opc.OwnDelete.Step.nStepNr;
				Opc.OwnDelete.Step.eAction := Opc.OwnDelete.fbUaSrv_MethodOperate.Action;
				Opc.OwnDelete.Step.nErrorId := Opc.OwnDelete.fbUaSrv_MethodOperate.ErrorID;
			END_IF

		1:	// Vorbereitung zum Löschen des öffentlichen Zertifikats
			Opc.OwnDelete.fbArCertDeleteOwn.Execute := 0;
			IF brsstrlen(ADR(Opc.OwnDelete.In_Name)) > 0 THEN
				Opc.OwnDelete.fbArCertDeleteOwn.Name := Opc.OwnDelete.In_Name;
				Opc.OwnDelete.Step.nStepNr := Opc.OwnDelete.Step.nStepNr + 1;
			ELSE
				Opc.OwnDelete.Step.nStepNr := Opc.OwnDelete.Step.nStepNr + 2;
			END_IF

		2:	// Löschen des öffentlichen Zertifikats
			Opc.OwnDelete.fbArCertDeleteOwn.Execute := 1;
			IF Opc.OwnDelete.fbArCertDeleteOwn.Busy = 0 THEN
				IF Opc.OwnDelete.fbArCertDeleteOwn.Done = 1 THEN
					// Zertifikat wurde gelöscht
					Opc.OwnDelete.fbArCertDeleteOwn.Execute := 0;
					Opc.OwnDelete.Step.nStepNr := Opc.OwnDelete.Step.nStepNr + 1;
				ELSIF Opc.OwnDelete.fbArCertDeleteOwn.Error = 1 THEN
					IF Opc.OwnDelete.fbArCertDeleteOwn.StatusID = arCERT_ERR_CERTIFICATE_NOT_FOUND AND Opc.OwnDelete.In_SuppressNotExistsError = 1 THEN
						// Fehler 'Certificate not found' soll unterdrückt werden
						Opc.OwnDelete.fbArCertDeleteOwn.Execute := 0;
						Opc.OwnDelete.Step.nStepNr := Opc.OwnDelete.Step.nStepNr + 1;
					ELSE
						// Fehler beim Löschen
						Opc.OwnDelete.fbArCertDeleteOwn.Execute := 0;
						Opc.OwnDelete.Out_ErrorId := Opc.OwnDelete.fbArCertDeleteOwn.StatusID;
						Opc.OwnDelete.Step.nStepNr := Opc.OwnDelete.Step.nStepNr + 1;
					END_IF
				END_IF
			END_IF

		3:	// Vorbereitung zum Löschen des privaten Keys
			Opc.OwnDelete.fbArCertDeletePrivateKey.Execute := 0;
			IF brsstrlen(ADR(Opc.OwnDelete.In_PrivateKeyName)) > 0 THEN
				Opc.OwnDelete.fbArCertDeletePrivateKey.Name := Opc.OwnDelete.In_PrivateKeyName;
				Opc.OwnDelete.Step.nStepNr := Opc.OwnDelete.Step.nStepNr + 1;
			ELSE
				Opc.OwnDelete.Step.nStepNr := Opc.OwnDelete.Step.nStepNr + 2;
			END_IF

		4:	// Löschen des privaten Keys
			Opc.OwnDelete.fbArCertDeletePrivateKey.Execute := 1;
			IF Opc.OwnDelete.fbArCertDeletePrivateKey.Busy = 0 THEN
				IF Opc.OwnDelete.fbArCertDeletePrivateKey.Done = 1 THEN
					// Zertifikat wurde gelöscht
					Opc.OwnDelete.fbArCertDeletePrivateKey.Execute := 0;
					Opc.OwnDelete.Step.nStepNr := Opc.OwnDelete.Step.nStepNr + 1;
				ELSIF Opc.OwnDelete.fbArCertDeletePrivateKey.Error = 1 THEN
					IF Opc.OwnDelete.fbArCertDeletePrivateKey.StatusID = arCERT_ERR_CERTIFICATE_NOT_FOUND AND Opc.OwnDelete.In_SuppressNotExistsError = 1 THEN
						// Fehler 'Certificate not found' soll unterdrückt werden
						Opc.OwnDelete.fbArCertDeletePrivateKey.Execute := 0;
						Opc.OwnDelete.Step.nStepNr := Opc.OwnDelete.Step.nStepNr + 1;
					ELSE
						// Fehler beim Löschen
						Opc.OwnDelete.fbArCertDeletePrivateKey.Execute := 0;
						Opc.OwnDelete.Out_ErrorId := Opc.OwnDelete.fbArCertDeletePrivateKey.StatusID;
						Opc.OwnDelete.Step.nStepNr := Opc.OwnDelete.Step.nStepNr + 1;
					END_IF
				END_IF
			END_IF

		5:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.OwnDelete.fbUaSrv_MethodOperate.Execute := 1;
			Opc.OwnDelete.fbUaSrv_MethodOperate.Action := UaMoa_Finished;
			IF Opc.OwnDelete.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.OwnDelete.fbUaSrv_MethodOperate.Execute := 0;
				Opc.OwnDelete.Step.nStepNr := 0;
			ELSIF Opc.OwnDelete.fbUaSrv_MethodOperate.Error = 1 THEN
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.OwnDelete.fbUaSrv_MethodOperate.Execute := 0;
				Opc.OwnDelete.Step.nErrorStep := Opc.OwnDelete.Step.nStepNr;
				Opc.OwnDelete.Step.eAction := Opc.OwnDelete.fbUaSrv_MethodOperate.Action;
				Opc.OwnDelete.Step.nErrorId := Opc.OwnDelete.fbUaSrv_MethodOperate.ErrorID;
				Opc.OwnDelete.Step.nStepNr := 0;
			END_IF

	END_CASE
	Opc.OwnDelete.fbUaSrv_MethodOperate();
	Opc.OwnDelete.fbArCertDeleteOwn();
	Opc.OwnDelete.fbArCertDeletePrivateKey();

	// Methode 'ForeignGetCertificateList'
	CASE Opc.ForeignGetCertificateList.Step.nStepNr OF
		0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Execute := 1;
			Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Action := UaMoa_CheckIsCalled;
			IF Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Execute := 0;
				IF Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.IsCalled = 1 THEN
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.ForeignGetCertificateList.nCallCount := Opc.ForeignGetCertificateList.nCallCount + 1;	// Nur zur Diagnose
					Opc.ForeignGetCertificateList.Out_ErrorId := 0;
					Opc.ForeignGetCertificateList.Step.nStepNr := Opc.ForeignGetCertificateList.Step.nStepNr + 1;
				END_IF
			ELSIF Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Error = 1 THEN
				Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Execute := 0;
				Opc.ForeignGetCertificateList.Step.nErrorStep := Opc.ForeignGetCertificateList.Step.nStepNr;
				Opc.ForeignGetCertificateList.Step.eAction := Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Action;
				Opc.ForeignGetCertificateList.Step.nErrorId := Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.ErrorID;
			END_IF

		1:	// Vorbereitung zum Auslesen der Liste
			Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Execute := 0;
			Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Name := '';
			Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Index := 0;
			brsmemset(ADR(Opc.ForeignGetCertificateList.Out_CertificatesList), 0, SIZEOF(Opc.ForeignGetCertificateList.Out_CertificatesList));
			Opc.ForeignGetCertificateList.Step.nStepNr := Opc.ForeignGetCertificateList.Step.nStepNr + 1;

		2:	// Nächsten Eintrag auslesen
			IF Opc.ForeignGetCertificateList.Out_CertificatesList.nLength <= OPCUA_CERTS_INDEX_MAX THEN
				Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Execute := 1;
				IF Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Busy = 0 THEN
					IF Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Done = 1 THEN
						// Eintrag auf Ausgangs-Argument übertragen
						brsmemcpy(ADR(Opc.ForeignGetCertificateList.Out_CertificatesList.Data[Opc.ForeignGetCertificateList.Out_CertificatesList.nLength]), ADR(Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Details), SIZEOF(ArCertDetailsType));
						// Nächsten Eintrag lesen
						Opc.ForeignGetCertificateList.Out_CertificatesList.nLength := Opc.ForeignGetCertificateList.Out_CertificatesList.nLength + 1;
						Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Index := Opc.ForeignGetCertificateList.Out_CertificatesList.nLength;
						Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Execute := 0;
					ELSIF Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Error = 1 THEN
						IF Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.StatusID = arCERT_ERR_CERTIFICATE_NOT_FOUND THEN
							// Alle Einträge sind gelesen
							Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Execute := 0;
							Opc.ForeignGetCertificateList.Step.nStepNr := Opc.ForeignGetCertificateList.Step.nStepNr + 1;
						ELSE
							// Fehler beim Auslesen
							Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.Execute := 0;
							Opc.ForeignGetCertificateList.Out_ErrorId := Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails.StatusID;
							Opc.ForeignGetCertificateList.Step.nStepNr := Opc.ForeignGetCertificateList.Step.nStepNr + 1;
						END_IF
					END_IF
				END_IF
			ELSE
				// Das SPS-Array ist nicht genügend groß, um weitere Einträge aufzunehmen
				Opc.ForeignGetCertificateList.Out_ErrorId := 12189696; // := 0x00BA0000 := Good_ResultsMayBeIncomplete
				Opc.ForeignGetCertificateList.Step.nStepNr := Opc.ForeignGetCertificateList.Step.nStepNr + 1;
			END_IF

		3:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Execute := 1;
			Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Action := UaMoa_Finished;
			IF Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Execute := 0;
				Opc.ForeignGetCertificateList.Step.nStepNr := 0;
			ELSIF Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Error = 1 THEN
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Execute := 0;
				Opc.ForeignGetCertificateList.Step.nErrorStep := Opc.ForeignGetCertificateList.Step.nStepNr;
				Opc.ForeignGetCertificateList.Step.eAction := Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.Action;
				Opc.ForeignGetCertificateList.Step.nErrorId := Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate.ErrorID;
				Opc.ForeignGetCertificateList.Step.nStepNr := 0;
			END_IF

	END_CASE
	Opc.ForeignGetCertificateList.fbUaSrv_MethodOperate();
	Opc.ForeignGetCertificateList.fbArCertGetThirdPartyDetails();

	// Methode 'ForeignImport'
	CASE Opc.ForeignImport.Step.nStepNr OF
		0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.ForeignImport.fbUaSrv_MethodOperate.Execute := 1;
			Opc.ForeignImport.fbUaSrv_MethodOperate.Action := UaMoa_CheckIsCalled;
			IF Opc.ForeignImport.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.ForeignImport.fbUaSrv_MethodOperate.Execute := 0;
				IF Opc.ForeignImport.fbUaSrv_MethodOperate.IsCalled = 1 THEN
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.ForeignImport.nCallCount := Opc.ForeignImport.nCallCount + 1;	// Nur zur Diagnose
					Opc.ForeignImport.Out_ErrorId := 0;
					Opc.ForeignImport.Step.nStepNr := Opc.ForeignImport.Step.nStepNr + 1;
				END_IF
			ELSIF Opc.ForeignImport.fbUaSrv_MethodOperate.Error = 1 THEN
				Opc.ForeignImport.fbUaSrv_MethodOperate.Execute := 0;
				Opc.ForeignImport.Step.nErrorStep := Opc.ForeignImport.Step.nStepNr;
				Opc.ForeignImport.Step.eAction := Opc.ForeignImport.fbUaSrv_MethodOperate.Action;
				Opc.ForeignImport.Step.nErrorId := Opc.ForeignImport.fbUaSrv_MethodOperate.ErrorID;
			END_IF

		1:	// Vorbereitung zum Löschen des öffentlichen Zertifikats
			Opc.ForeignImport.fbArCertDeleteThirdParty.Execute := 0;
			IF Opc.ForeignImport.In_Overwrite = 1 THEN
				Opc.ForeignImport.fbArCertDeleteThirdParty.Name := Opc.ForeignImport.In_Name;
				Opc.ForeignImport.Step.nStepNr := Opc.ForeignImport.Step.nStepNr + 1;
			ELSE
				Opc.ForeignImport.Step.nStepNr := Opc.ForeignImport.Step.nStepNr + 2;
			END_IF

		2:	// Löschen des öffentlichen Zertifikats
			Opc.ForeignImport.fbArCertDeleteThirdParty.Execute := 1;
			IF Opc.ForeignImport.fbArCertDeleteThirdParty.Busy = 0 THEN
				IF Opc.ForeignImport.fbArCertDeleteThirdParty.Done = 1 THEN
					// Zertifikat wurde gelöscht
					Opc.ForeignImport.fbArCertDeleteThirdParty.Execute := 0;
					Opc.ForeignImport.Step.nStepNr := Opc.ForeignImport.Step.nStepNr + 1;
				ELSIF Opc.ForeignImport.fbArCertDeleteThirdParty.Error = 1 THEN
					// Zertifikat ist nicht vorhanden. Fehler wird übergangen
					Opc.ForeignImport.fbArCertDeleteThirdParty.Execute := 0;
					Opc.ForeignImport.Step.nStepNr := Opc.ForeignImport.Step.nStepNr + 1;
				END_IF
			END_IF

		3:	// Vorbereitung zum Importieren des öffentlichen Zertifikats
			Opc.ForeignImport.fbArCertImportThirdParty.Execute := 0;
			Opc.ForeignImport.fbArCertImportThirdParty.Name := Opc.ForeignImport.In_Name;
			Opc.ForeignImport.fbArCertImportThirdParty.Data := ADR(Opc.ForeignImport.In_Certificate.Data);
			Opc.ForeignImport.fbArCertImportThirdParty.DataSize := Opc.ForeignImport.In_Certificate.Length;
			Opc.ForeignImport.Step.nStepNr := Opc.ForeignImport.Step.nStepNr + 1;

		4:	// Importieren des öffentlichen Zertifikats
			Opc.ForeignImport.fbArCertImportThirdParty.Execute := 1;
			IF Opc.ForeignImport.fbArCertImportThirdParty.Busy = 0 THEN
				IF Opc.ForeignImport.fbArCertImportThirdParty.Done = 1 THEN
					// Zertifikat wurde importiert
					Opc.ForeignImport.fbArCertImportThirdParty.Execute := 0;
					Opc.ForeignImport.Step.nStepNr := Opc.ForeignImport.Step.nStepNr + 1;
				ELSIF Opc.ForeignImport.fbArCertImportThirdParty.Error = 1 THEN
					// Fehler beim Importieren
					Opc.ForeignImport.fbArCertImportThirdParty.Execute := 0;
					Opc.ForeignImport.Out_ErrorId := Opc.ForeignImport.fbArCertImportThirdParty.StatusID;
					Opc.ForeignImport.Step.nStepNr := Opc.ForeignImport.Step.nStepNr + 1;
				END_IF
			END_IF

		5:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.ForeignImport.fbUaSrv_MethodOperate.Execute := 1;
			Opc.ForeignImport.fbUaSrv_MethodOperate.Action := UaMoa_Finished;
			IF Opc.ForeignImport.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.ForeignImport.fbUaSrv_MethodOperate.Execute := 0;
				Opc.ForeignImport.Step.nStepNr := 0;
			ELSIF Opc.ForeignImport.fbUaSrv_MethodOperate.Error = 1 THEN
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.ForeignImport.fbUaSrv_MethodOperate.Execute := 0;
				Opc.ForeignImport.Step.nErrorStep := Opc.ForeignImport.Step.nStepNr;
				Opc.ForeignImport.Step.eAction := Opc.ForeignImport.fbUaSrv_MethodOperate.Action;
				Opc.ForeignImport.Step.nErrorId := Opc.ForeignImport.fbUaSrv_MethodOperate.ErrorID;
				Opc.ForeignImport.Step.nStepNr := 0;
			END_IF

	END_CASE
	Opc.ForeignImport.fbUaSrv_MethodOperate();
	Opc.ForeignImport.fbArCertDeleteThirdParty();
	Opc.ForeignImport.fbArCertImportThirdParty();

	// Methode 'ForeignDelete'
	CASE Opc.ForeignDelete.Step.nStepNr OF
		0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.ForeignDelete.fbUaSrv_MethodOperate.Execute := 1;
			Opc.ForeignDelete.fbUaSrv_MethodOperate.Action := UaMoa_CheckIsCalled;
			IF Opc.ForeignDelete.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.ForeignDelete.fbUaSrv_MethodOperate.Execute := 0;
				IF Opc.ForeignDelete.fbUaSrv_MethodOperate.IsCalled = 1 THEN
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.ForeignDelete.nCallCount := Opc.ForeignDelete.nCallCount + 1;	// Nur zur Diagnose
					Opc.ForeignDelete.Out_ErrorId := 0;
					Opc.ForeignDelete.Step.nStepNr := Opc.ForeignDelete.Step.nStepNr + 1;
				END_IF
			ELSIF Opc.ForeignDelete.fbUaSrv_MethodOperate.Error = 1 THEN
				Opc.ForeignDelete.fbUaSrv_MethodOperate.Execute := 0;
				Opc.ForeignDelete.Step.nErrorStep := Opc.ForeignDelete.Step.nStepNr;
				Opc.ForeignDelete.Step.eAction := Opc.ForeignDelete.fbUaSrv_MethodOperate.Action;
				Opc.ForeignDelete.Step.nErrorId := Opc.ForeignDelete.fbUaSrv_MethodOperate.ErrorID;
			END_IF

		1:	// Vorbereitung zum Löschen des öffentlichen Zertifikats
			Opc.ForeignDelete.fbArCertDeleteThirdParty.Execute := 0;
			IF brsstrlen(ADR(Opc.ForeignDelete.In_Name)) > 0 THEN
				Opc.ForeignDelete.fbArCertDeleteThirdParty.Name := Opc.ForeignDelete.In_Name;
				Opc.ForeignDelete.Step.nStepNr := Opc.ForeignDelete.Step.nStepNr + 1;
			ELSE
				Opc.ForeignDelete.Step.nStepNr := Opc.ForeignDelete.Step.nStepNr + 2;
			END_IF

		2:	// Löschen des öffentlichen Zertifikats
			Opc.ForeignDelete.fbArCertDeleteThirdParty.Execute := 1;
			IF Opc.ForeignDelete.fbArCertDeleteThirdParty.Busy = 0 THEN
				IF Opc.ForeignDelete.fbArCertDeleteThirdParty.Done = 1 THEN
					// Zertifikat wurde gelöscht
					Opc.ForeignDelete.fbArCertDeleteThirdParty.Execute := 0;
					Opc.ForeignDelete.Step.nStepNr := Opc.ForeignDelete.Step.nStepNr + 1;
				ELSIF Opc.ForeignDelete.fbArCertDeleteThirdParty.Error = 1 THEN
					IF Opc.ForeignDelete.fbArCertDeleteThirdParty.StatusID = arCERT_ERR_CERTIFICATE_NOT_FOUND AND Opc.ForeignDelete.In_SuppressNotExistsError = 1 THEN
						// Fehler 'Certificate not found' soll unterdrückt werden
						Opc.ForeignDelete.fbArCertDeleteThirdParty.Execute := 0;
						Opc.ForeignDelete.Step.nStepNr := Opc.ForeignDelete.Step.nStepNr + 1;
					ELSE
					// Fehler beim Löschen
						Opc.ForeignDelete.fbArCertDeleteThirdParty.Execute := 0;
						Opc.ForeignDelete.Out_ErrorId := Opc.ForeignDelete.fbArCertDeleteThirdParty.StatusID;
						Opc.ForeignDelete.Step.nStepNr := Opc.ForeignDelete.Step.nStepNr + 1;
					END_IF
				END_IF
			END_IF

		3:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.ForeignDelete.fbUaSrv_MethodOperate.Execute := 1;
			Opc.ForeignDelete.fbUaSrv_MethodOperate.Action := UaMoa_Finished;
			IF Opc.ForeignDelete.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.ForeignDelete.fbUaSrv_MethodOperate.Execute := 0;
				Opc.ForeignDelete.Step.nStepNr := 0;
			ELSIF Opc.ForeignDelete.fbUaSrv_MethodOperate.Error = 1 THEN
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.ForeignDelete.fbUaSrv_MethodOperate.Execute := 0;
				Opc.ForeignDelete.Step.nErrorStep := Opc.ForeignDelete.Step.nStepNr;
				Opc.ForeignDelete.Step.eAction := Opc.ForeignDelete.fbUaSrv_MethodOperate.Action;
				Opc.ForeignDelete.Step.nErrorId := Opc.ForeignDelete.fbUaSrv_MethodOperate.ErrorID;
				Opc.ForeignDelete.Step.nStepNr := 0;
			END_IF

	END_CASE
	Opc.ForeignDelete.fbUaSrv_MethodOperate();
	Opc.ForeignDelete.fbArCertDeleteThirdParty();

	// Methode 'SslGetCfgList'
	CASE Opc.SslGetCfgList.Step.nStepNr OF
		0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.SslGetCfgList.fbUaSrv_MethodOperate.Execute := 1;
			Opc.SslGetCfgList.fbUaSrv_MethodOperate.Action := UaMoa_CheckIsCalled;
			IF Opc.SslGetCfgList.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.SslGetCfgList.fbUaSrv_MethodOperate.Execute := 0;
				IF Opc.SslGetCfgList.fbUaSrv_MethodOperate.IsCalled = 1 THEN
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.SslGetCfgList.nCallCount := Opc.SslGetCfgList.nCallCount + 1;	// Nur zur Diagnose
					Opc.SslGetCfgList.Out_ErrorId := 0;
					Opc.SslGetCfgList.Step.nStepNr := Opc.SslGetCfgList.Step.nStepNr + 1;
				END_IF
			ELSIF Opc.SslGetCfgList.fbUaSrv_MethodOperate.Error = 1 THEN
				Opc.SslGetCfgList.fbUaSrv_MethodOperate.Execute := 0;
				Opc.SslGetCfgList.Step.nErrorStep := Opc.SslGetCfgList.Step.nStepNr;
				Opc.SslGetCfgList.Step.eAction := Opc.SslGetCfgList.fbUaSrv_MethodOperate.Action;
				Opc.SslGetCfgList.Step.nErrorId := Opc.SslGetCfgList.fbUaSrv_MethodOperate.ErrorID;
			END_IF

		1:	// Vorbereitung zum Auslesen der Cfg-Liste
			Opc.SslGetCfgList.fbArSslGetCfgDetails.Execute := 0;
			Opc.SslGetCfgList.fbArSslGetCfgDetails.Name := '';
			Opc.SslGetCfgList.fbArSslGetCfgDetails.Index := 0;
			brsmemset(ADR(Opc.SslGetCfgList.Out_CfgList), 0, SIZEOF(Opc.SslGetCfgList.Out_CfgList));
			Opc.SslGetCfgList.Step.nStepNr := Opc.SslGetCfgList.Step.nStepNr + 1;

		2:	// Nächsten Cfg-Eintrag auslesen
			IF Opc.SslGetCfgList.Out_CfgList.nLength <= OPCUA_SSLCFG_INDEX_MAX THEN
				Opc.SslGetCfgList.fbArSslGetCfgDetails.Execute := 1;
				IF Opc.SslGetCfgList.fbArSslGetCfgDetails.Busy = 0 THEN
					IF Opc.SslGetCfgList.fbArSslGetCfgDetails.Done = 1 THEN
						// Cfg-Eintrag auf Ausgangs-Argument übertragen
						brsmemcpy(ADR(Opc.SslGetCfgList.Out_CfgList.Data[Opc.SslGetCfgList.Out_CfgList.nLength]), ADR(Opc.SslGetCfgList.fbArSslGetCfgDetails.Details), SIZEOF(ArSslCfgDetailsType));
						// Nächsten Eintrag lesen
						Opc.SslGetCfgList.Out_CfgList.nLength := Opc.SslGetCfgList.Out_CfgList.nLength + 1;
						Opc.SslGetCfgList.fbArSslGetCfgDetails.Index := Opc.SslGetCfgList.Out_CfgList.nLength;
						Opc.SslGetCfgList.fbArSslGetCfgDetails.Execute := 0;
					ELSIF Opc.SslGetCfgList.fbArSslGetCfgDetails.Error = 1 THEN
						IF Opc.SslGetCfgList.fbArSslGetCfgDetails.StatusID = arSSL_ERR_SSL_CFG_NOT_FOUND THEN
							// Alle Cfg-Einträge sind gelesen
							Opc.SslGetCfgList.fbArSslGetCfgDetails.Execute := 0;
							Opc.SslGetCfgList.Step.nStepNr := Opc.SslGetCfgList.Step.nStepNr + 1;
						ELSE
							// Fehler beim Auslesen
							Opc.SslGetCfgList.fbArSslGetCfgDetails.Execute := 0;
							Opc.SslGetCfgList.Out_ErrorId := Opc.SslGetCfgList.fbArSslGetCfgDetails.StatusID;
							Opc.SslGetCfgList.Step.nStepNr := Opc.SslGetCfgList.Step.nStepNr + 1;
						END_IF
					END_IF
				END_IF
			ELSE
				// Das SPS-Array ist nicht genügend groß, um weitere Einträge aufzunehmen
				Opc.SslGetCfgList.Out_ErrorId := 12189696; // := 0x00BA0000 := Good_ResultsMayBeIncomplete
				Opc.SslGetCfgList.Step.nStepNr := Opc.SslGetCfgList.Step.nStepNr + 1;
			END_IF

		3:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.SslGetCfgList.fbUaSrv_MethodOperate.Execute := 1;
			Opc.SslGetCfgList.fbUaSrv_MethodOperate.Action := UaMoa_Finished;
			IF Opc.SslGetCfgList.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.SslGetCfgList.fbUaSrv_MethodOperate.Execute := 0;
				Opc.SslGetCfgList.Step.nStepNr := 0;
			ELSIF Opc.SslGetCfgList.fbUaSrv_MethodOperate.Error = 1 THEN
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.SslGetCfgList.fbUaSrv_MethodOperate.Execute := 0;
				Opc.SslGetCfgList.Step.nErrorStep := Opc.SslGetCfgList.Step.nStepNr;
				Opc.SslGetCfgList.Step.eAction := Opc.SslGetCfgList.fbUaSrv_MethodOperate.Action;
				Opc.SslGetCfgList.Step.nErrorId := Opc.SslGetCfgList.fbUaSrv_MethodOperate.ErrorID;
				Opc.SslGetCfgList.Step.nStepNr := 0;
			END_IF

	END_CASE
	Opc.SslGetCfgList.fbUaSrv_MethodOperate();
	Opc.SslGetCfgList.fbArSslGetCfgDetails();

	// Methode 'SslGetTrustedCertList'
	CASE Opc.SslGetTrustedCertList.Step.nStepNr OF
		0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Execute := 1;
			Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Action := UaMoa_CheckIsCalled;
			IF Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Execute := 0;
				IF Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.IsCalled = 1 THEN
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.SslGetTrustedCertList.nCallCount := Opc.SslGetTrustedCertList.nCallCount + 1;	// Nur zur Diagnose
					Opc.SslGetTrustedCertList.Out_ErrorId := 0;
					Opc.SslGetTrustedCertList.Step.nStepNr := Opc.SslGetTrustedCertList.Step.nStepNr + 1;
				END_IF
			ELSIF Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Error = 1 THEN
				Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Execute := 0;
				Opc.SslGetTrustedCertList.Step.nErrorStep := Opc.SslGetTrustedCertList.Step.nStepNr;
				Opc.SslGetTrustedCertList.Step.eAction := Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Action;
				Opc.SslGetTrustedCertList.Step.nErrorId := Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.ErrorID;
			END_IF

		1:	// Vorbereitung zum Auslesen der Liste
			Opc.SslGetTrustedCertList.fbArSslGetCertificate.Execute := 0;
			Opc.SslGetTrustedCertList.fbArSslGetCertificate.Name := Opc.SslGetTrustedCertList.In_CfgName;
			Opc.SslGetTrustedCertList.fbArSslGetCertificate.Index := 0;
			brsmemset(ADR(Opc.SslGetTrustedCertList.Out_TrustedCertNameList), 0, SIZEOF(Opc.SslGetTrustedCertList.Out_TrustedCertNameList));
			Opc.SslGetTrustedCertList.Step.nStepNr := Opc.SslGetTrustedCertList.Step.nStepNr + 1;

		2:	// Nächsten Eintrag auslesen
			IF Opc.SslGetTrustedCertList.Out_TrustedCertNameList.nLength <= OPCUA_CERTS_INDEX_MAX THEN
				Opc.SslGetTrustedCertList.fbArSslGetCertificate.Execute := 1;
				IF Opc.SslGetTrustedCertList.fbArSslGetCertificate.Busy = 0 THEN
					IF Opc.SslGetTrustedCertList.fbArSslGetCertificate.Done = 1 THEN
						// Eintrag auf Ausgangs-Argument übertragen
						Opc.SslGetTrustedCertList.Out_TrustedCertNameList.Data[Opc.SslGetTrustedCertList.Out_TrustedCertNameList.nLength] := Opc.SslGetTrustedCertList.fbArSslGetCertificate.TrustedCertificate;
						// Nächsten Eintrag lesen
						Opc.SslGetTrustedCertList.Out_TrustedCertNameList.nLength := Opc.SslGetTrustedCertList.Out_TrustedCertNameList.nLength + 1;
						Opc.SslGetTrustedCertList.fbArSslGetCertificate.Index := Opc.SslGetTrustedCertList.Out_TrustedCertNameList.nLength;
						Opc.SslGetTrustedCertList.fbArSslGetCertificate.Execute := 0;
					ELSIF Opc.SslGetTrustedCertList.fbArSslGetCertificate.Error = 1 THEN
						IF Opc.SslGetTrustedCertList.fbArSslGetCertificate.StatusID = arSSL_ERR_INDEX_OUT_OF_RANGE THEN
							// Alle Einträge sind gelesen
							Opc.SslGetTrustedCertList.fbArSslGetCertificate.Execute := 0;
							Opc.SslGetTrustedCertList.Step.nStepNr := Opc.SslGetTrustedCertList.Step.nStepNr + 1;
						ELSE
							// Fehler beim Auslesen
							Opc.SslGetTrustedCertList.fbArSslGetCertificate.Execute := 0;
							Opc.SslGetTrustedCertList.Out_ErrorId := Opc.SslGetTrustedCertList.fbArSslGetCertificate.StatusID;
							Opc.SslGetTrustedCertList.Step.nStepNr := Opc.SslGetTrustedCertList.Step.nStepNr + 1;
						END_IF
					END_IF
				END_IF
			ELSE
				// Das SPS-Array ist nicht genügend groß, um weitere Einträge aufzunehmen
				Opc.SslGetTrustedCertList.Out_ErrorId := 12189696; // := 0x00BA0000 := Good_ResultsMayBeIncomplete
				Opc.SslGetTrustedCertList.Step.nStepNr := Opc.SslGetTrustedCertList.Step.nStepNr + 1;
			END_IF

		3:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Execute := 1;
			Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Action := UaMoa_Finished;
			IF Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Execute := 0;
				Opc.SslGetTrustedCertList.Step.nStepNr := 0;
			ELSIF Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Error = 1 THEN
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Execute := 0;
				Opc.SslGetTrustedCertList.Step.nErrorStep := Opc.SslGetTrustedCertList.Step.nStepNr;
				Opc.SslGetTrustedCertList.Step.eAction := Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.Action;
				Opc.SslGetTrustedCertList.Step.nErrorId := Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate.ErrorID;
				Opc.SslGetTrustedCertList.Step.nStepNr := 0;
			END_IF

	END_CASE
	Opc.SslGetTrustedCertList.fbUaSrv_MethodOperate();
	Opc.SslGetTrustedCertList.fbArSslGetCertificate();

	// Methode 'Warmstart'
	CASE Opc.Warmstart.Step.nStepNr OF
		0:	// Prüfen, ob Methode von einem Client aufgerufen wurde
			Opc.Warmstart.fbUaSrv_MethodOperate.Execute := 1;
			Opc.Warmstart.fbUaSrv_MethodOperate.Action := UaMoa_CheckIsCalled;
			IF Opc.Warmstart.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.Warmstart.fbUaSrv_MethodOperate.Execute := 0;
				IF Opc.Warmstart.fbUaSrv_MethodOperate.IsCalled = 1 THEN
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Opc.Warmstart.nCallCount := Opc.Warmstart.nCallCount + 1;	// Nur zur Diagnose
					Opc.Warmstart.Step.nStepNr := Opc.Warmstart.Step.nStepNr + 1;
				END_IF
			ELSIF Opc.Warmstart.fbUaSrv_MethodOperate.Error = 1 THEN
				Opc.Warmstart.fbUaSrv_MethodOperate.Execute := 0;
				Opc.Warmstart.Step.nErrorStep := Opc.Warmstart.Step.nStepNr;
				Opc.Warmstart.Step.eAction := Opc.Warmstart.fbUaSrv_MethodOperate.Action;
				Opc.Warmstart.Step.nErrorId := Opc.Warmstart.fbUaSrv_MethodOperate.ErrorID;
			END_IF

		1:	// Verzögerung für das Auslösen des Warmstarts starten
			// Der Warmstart wird verzögert ausgelöst, damit vom Server die Rückmeldung noch geschickt werden kann
			Opc.Warmstart.fbTon.PT := t#2s; 
			Opc.Warmstart.fbTon.IN := 1;
			Opc.Warmstart.Step.nStepNr := Opc.Warmstart.Step.nStepNr + 1;

		2:	// Rückmelden, dass Methode ausgeführt wurde
			Opc.Warmstart.fbUaSrv_MethodOperate.Execute := 1;
			Opc.Warmstart.fbUaSrv_MethodOperate.Action := UaMoa_Finished;
			IF Opc.Warmstart.fbUaSrv_MethodOperate.Done = 1 THEN
				Opc.Warmstart.fbUaSrv_MethodOperate.Execute := 0;
				Opc.Warmstart.Step.nStepNr := 0;
			ELSIF Opc.Warmstart.fbUaSrv_MethodOperate.Error = 1 THEN
				// Fehler eintragen, aber trotzdem weiter machen
				Opc.Warmstart.fbUaSrv_MethodOperate.Execute := 0;
				Opc.Warmstart.Step.nErrorStep := Opc.Warmstart.Step.nStepNr;
				Opc.Warmstart.Step.eAction := Opc.Warmstart.fbUaSrv_MethodOperate.Action;
				Opc.Warmstart.Step.nErrorId := Opc.Warmstart.fbUaSrv_MethodOperate.ErrorID;
				Opc.Warmstart.Step.nStepNr := 0;
			END_IF

	END_CASE
	Opc.Warmstart.fbUaSrv_MethodOperate();
	Opc.Warmstart.fbTon();
	IF Opc.Warmstart.fbTon.Q = 1 THEN
		Opc.Warmstart.fbTon.IN := 0;
		SYSreset(1, 1); // Warmstart auslösen
	END_IF
END_PROGRAM

PROGRAM _EXIT
END_PROGRAM

