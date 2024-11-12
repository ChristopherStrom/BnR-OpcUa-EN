
TYPE
	Step_TYP : 	STRUCT 
		nStepNr : DINT;
		nErrorStep : DINT;
		eAction : UaMethodOperateAction;
		nErrorId : DWORD;
	END_STRUCT;
	OpcUaCertList_TYP : 	STRUCT 
		nLength : UAArrayLength;
		Data : ARRAY[0..9]OF ArCertDetailsType; (*OPCUA_CERTS_INDEX_MAX*)
	END_STRUCT;
	OwnGetCertificateList_TYP : 	STRUCT 
		Step : Step_TYP;
		fbUaSrv_MethodOperate : UaSrv_MethodOperate;
		nCallCount : UDINT;
		fbArCertGetOwnDetails : ArCertGetOwnDetails;
		Out_CertificatesList : OpcUaCertList_TYP;
		Out_ErrorId : DINT;
	END_STRUCT;
	OwnGenerateCertificatePar_TYP : 	STRUCT 
		sName : STRING[255];
		sPrivateKeyName : STRING[255];
		sPrivateKeyPassword : STRING[255];
		eKeySize : ArCertKeySizeEnum;
		sCountryCode : STRING[9];
		sStateProvince : STRING[513];
		sLocality : STRING[513];
		sOrganization : STRING[255];
		sOrganizationUnit : STRING[255];
		sContactEmail : STRING[513];
		sCommonName : STRING[255];
		nValidTimeSeconds : UDINT;
		sUri : STRING[513];
		sDnsName : STRING[513];
		sIp : STRING[513];
	END_STRUCT;
	OwnGenerateCertificate_TYP : 	STRUCT 
		Step : Step_TYP;
		fbUaSrv_MethodOperate : UaSrv_MethodOperate;
		nCallCount : UDINT;
		fbArCertGenerateX : ArCertGenerateX;
		In_Parameter : OwnGenerateCertificatePar_TYP;
		Out_ErrorId : DINT;
	END_STRUCT;
	UAByteString5k_TYP : 	STRUCT 
		Length : DINT;
		Data : ARRAY[0..4999]OF USINT;
	END_STRUCT;
	OwnImportCertificate_TYP : 	STRUCT 
		Step : Step_TYP;
		fbUaSrv_MethodOperate : UaSrv_MethodOperate;
		nCallCount : UDINT;
		fbArCertDeleteOwn : ArCertDeleteOwn;
		fbArCertImportOwn : ArCertImportOwn;
		fbArCertDeletePrivateKey : ArCertDeletePrivateKey;
		fbArCertImportPrivateKey : ArCertImportPrivateKey;
		In_Name : STRING[255];
		In_Certificate : UAByteString5k_TYP;
		In_PrivateKeyName : STRING[255];
		In_PrivateKey : UAByteString5k_TYP;
		In_Overwrite : BOOL;
		Out_ErrorId : DINT;
	END_STRUCT;
	OwnDeleteCertificate_TYP : 	STRUCT 
		Step : Step_TYP;
		fbUaSrv_MethodOperate : UaSrv_MethodOperate;
		nCallCount : UDINT;
		fbArCertDeleteOwn : ArCertDeleteOwn;
		fbArCertDeletePrivateKey : ArCertDeletePrivateKey;
		In_Name : STRING[255];
		In_PrivateKeyName : STRING[255];
		In_SuppressNotExistsError : BOOL;
		Out_ErrorId : DINT;
	END_STRUCT;
	ForeignGetCertificateList_TYP : 	STRUCT 
		Step : Step_TYP;
		fbUaSrv_MethodOperate : UaSrv_MethodOperate;
		nCallCount : UDINT;
		fbArCertGetThirdPartyDetails : ArCertGetThirdPartyDetails;
		Out_CertificatesList : OpcUaCertList_TYP;
		Out_ErrorId : DINT;
	END_STRUCT;
	ForeignImportCertificate_TYP : 	STRUCT 
		Step : Step_TYP;
		fbUaSrv_MethodOperate : UaSrv_MethodOperate;
		nCallCount : UDINT;
		fbArCertDeleteThirdParty : ArCertDeleteThirdParty;
		fbArCertImportThirdParty : ArCertImportThirdParty;
		In_Name : STRING[255];
		In_Certificate : UAByteString5k_TYP;
		In_Overwrite : BOOL;
		Out_ErrorId : DINT;
	END_STRUCT;
	ForeignDeleteCertificate_TYP : 	STRUCT 
		Step : Step_TYP;
		fbUaSrv_MethodOperate : UaSrv_MethodOperate;
		nCallCount : UDINT;
		fbArCertDeleteThirdParty : ArCertDeleteThirdParty;
		In_Name : STRING[255];
		In_SuppressNotExistsError : BOOL;
		Out_ErrorId : DINT;
	END_STRUCT;
	OpcUaSslCfgList_TYP : 	STRUCT 
		nLength : UAArrayLength;
		Data : ARRAY[0..9]OF ArSslCfgDetailsType; (*OPCUA_SSLCFG_INDEX_MAX*)
	END_STRUCT;
	SslGetCfgList_TYP : 	STRUCT 
		Step : Step_TYP;
		fbUaSrv_MethodOperate : UaSrv_MethodOperate;
		nCallCount : UDINT;
		fbArSslGetCfgDetails : ArSslGetCfgDetails;
		Out_CfgList : OpcUaSslCfgList_TYP;
		Out_ErrorId : DINT;
	END_STRUCT;
	OpcUaCertNameList_TYP : 	STRUCT 
		nLength : UAArrayLength;
		Data : ARRAY[0..9]OF STRING[255]; (*OPCUA_CERTS_INDEX_MAX*)
	END_STRUCT;
	SslGetTrustedCertList_TYP : 	STRUCT 
		Step : Step_TYP;
		fbUaSrv_MethodOperate : UaSrv_MethodOperate;
		nCallCount : UDINT;
		fbArSslGetCertificate : ArSslGetCertificate;
		In_CfgName : STRING[255];
		Out_TrustedCertNameList : OpcUaCertNameList_TYP;
		Out_ErrorId : DINT;
	END_STRUCT;
	Warmstart_TYP : 	STRUCT 
		Step : Step_TYP;
		fbUaSrv_MethodOperate : UaSrv_MethodOperate;
		nCallCount : UDINT;
		fbTon : TON;
	END_STRUCT;
	Opc_TYP : 	STRUCT 
		OwnGetCertificateList : OwnGetCertificateList_TYP;
		OwnGenerate : OwnGenerateCertificate_TYP;
		OwnImport : OwnImportCertificate_TYP;
		OwnDelete : OwnDeleteCertificate_TYP;
		ForeignGetCertificateList : ForeignGetCertificateList_TYP;
		ForeignImport : ForeignImportCertificate_TYP;
		ForeignDelete : ForeignDeleteCertificate_TYP;
		SslGetCfgList : SslGetCfgList_TYP;
		SslGetTrustedCertList : SslGetTrustedCertList_TYP;
		Warmstart : Warmstart_TYP;
	END_STRUCT;
END_TYPE
