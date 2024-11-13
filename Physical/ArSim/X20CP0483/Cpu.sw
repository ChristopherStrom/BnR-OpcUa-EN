<?xml version="1.0" encoding="utf-8"?>
<?AutomationStudio FileVersion="4.9"?>
<SwConfiguration CpuAddress="SL1" xmlns="http://br-automation.co.at/AS/SwConfiguration">
  <TaskClass Name="Cyclic#1">
    <Task Name="ClientC" Source="Tasks.Clients.ClientC.ClientC.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="ClientST" Source="Tasks.Clients.ClientST.ClientST.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="SrvMethC" Source="Tasks.ServerMethods.SrvMethC.SrvMethC.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="SrvMethST" Source="Tasks.ServerMethods.SrvMethST.SrvMethST.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="SrvEvntC" Source="Tasks.ServerEvents.SrvEvntC.SrvEvntC.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="SrvEvntST" Source="Tasks.ServerEvents.SrvEvntST.SrvEvntST.prg" Memory="UserROM" Language="IEC" Debugging="true" Disabled="true" />
    <Task Name="BrbUaCltC" Source="Tasks.BrbUa.BrbUaClient.BrbUaCltC.BrbUaCltC.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="BrbUaCltST" Source="Tasks.BrbUa.BrbUaClient.BrbUaCltST.BrbUaCltST.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="BrbUaSrvC" Source="Tasks.BrbUa.BrbUaServer.BrbUaSrvC.BrbUaSrvC.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="BrbUaSrvST" Source="Tasks.BrbUa.BrbUaServer.BrbUaSrvST.BrbSrvDatST.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="UaCertsC" Source="Tasks.UaCerts.UaCertsC.UaCertsC.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="UaCertsST" Source="Tasks.UaCerts.UaCertsST.UaCertsST.prg" Memory="UserROM" Language="IEC" Debugging="true" />
  </TaskClass>
  <TaskClass Name="Cyclic#2" />
  <TaskClass Name="Cyclic#3" />
  <TaskClass Name="Cyclic#4">
    <Task Name="AirCondC" Source="Tasks.AirCond.AirCondC.AirCondC.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="AirCondST" Source="Tasks.AirCond.AirCondST.AirCondST.prg" Memory="UserROM" Language="IEC" Debugging="true" />
  </TaskClass>
  <TaskClass Name="Cyclic#5" />
  <TaskClass Name="Cyclic#6" />
  <TaskClass Name="Cyclic#7">
    <Task Name="ServerData" Source="Tasks.ServerData.ServerData.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="SrvDt64C" Source="Tasks.ServerDt64.SrvDt64C.SrvDt64C.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="SrvDt64ST" Source="Tasks.ServerDt64.ServerDt64ST.SrvDt64ST.prg" Memory="UserROM" Language="IEC" Debugging="true" />
    <Task Name="OpcUaAny" Source="Tasks.OpcUaAny.OpcUaAny.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="PubDiag" Source="Tasks.PubSub.Publisher.PubDiag.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="Subscriber" Source="Tasks.PubSub.Subscriber.Subscriber.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="SubDiag" Source="Tasks.PubSub.Subscriber.SubDiag.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
  </TaskClass>
  <TaskClass Name="Cyclic#8">
    <Task Name="UtBrbTempl" Source="UnitTests.UtBrbUaTemplate.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="UtBrbUaSta" Source="UnitTests.UtBrbLibUa.UtBrbUaStatus.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="UtBrbUaNod" Source="UnitTests.UtBrbLibUa.UtBrbUaNodes.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="UtBrbUaAtt" Source="UnitTests.UtBrbLibUa.UtBrbUaAttributes.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="UtBrbUaVar" Source="UnitTests.UtBrbLibUa.UtBrbUaVariantValues.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="UtBrbUaByt" Source="UnitTests.UtBrbLibUa.UtBrbUaByteStrings.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="UtBrbUaLoc" Source="UnitTests.UtBrbLibUa.UtBrbUaLocalizedTexts.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="UtBrbUaQua" Source="UnitTests.UtBrbLibUa.UtBrbUaQualifiedNames.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="UtBrbUaTim" Source="UnitTests.UtBrbLibUa.UtBrbUaTimeAndDate.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="UtBrbUaAdd" Source="UnitTests.UtBrbLibUa.UtBrbUaAdditional.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="UtBrbUaCli" Source="UnitTests.UtBrbLibUa.UtBrbUaClient.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="UtBrbUaSer" Source="UnitTests.UtBrbLibUa.UtBrbUaServer.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
  </TaskClass>
  <DataObjects>
    <DataObject Name="BrbCltDatC" Source="Tasks.BrbUa.BrbUaClient.BrbUaCltC.BrbCltDatC.dob" Memory="UserROM" Language="Simple" />
    <DataObject Name="BrbCltDatS" Source="Tasks.BrbUa.BrbUaClient.BrbUaCltST.BrbCltDatST.dob" Memory="UserROM" Language="Simple" />
    <DataObject Name="BrbSrvDatC" Source="Tasks.BrbUa.BrbUaServer.BrbUaSrvC.BrbSrvDatC.dob" Memory="UserROM" Language="Simple" />
    <DataObject Name="BrbSrvDatS" Source="Tasks.BrbUa.BrbUaServer.BrbUaSrvST.BrbSrvDatS.dob" Memory="UserROM" Language="Simple" />
  </DataObjects>
  <Binaries>
    <BinaryObject Name="TCData" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="udbdef" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="TCLang" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="TC" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="OpcUaCfg" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="ashwac" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="Role" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="User" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="ashwd" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="asfw" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="arconfig" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="sysconf" Source="" Memory="SystemROM" Language="Binary" />
    <BinaryObject Name="iomap" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="OpcUa" Source="" Memory="UserROM" Language="Binary" />
    <BinaryObject Name="OpcUaMap" Source="" Memory="UserROM" Language="Binary" />
  </Binaries>
  <Libraries>
    <LibraryObject Name="UnitTest" Source="UnitTests.UnitTestLibraries.UnitTest.lby" Memory="None" Language="ANSIC" Debugging="true" />
    <LibraryObject Name="UtMgr" Source="UnitTests.UnitTestLibraries.UtMgr.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="UtWs" Source="UnitTests.UnitTestLibraries.UtWs.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="BrbAsserts" Source="UnitTests.UnitTestLibraries.BrbAsserts.lby" Memory="None" Language="ANSIC" Debugging="true" />
    <LibraryObject Name="ArCert" Source="Libraries.ArCert.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="ArEventLog" Source="Libraries.ArEventLog.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="ArPubSubD" Source="Libraries.ArPubSubD.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="ArSsl" Source="Libraries.ArSsl.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="AsBrStr" Source="Libraries.AsBrStr.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsBrWStr" Source="Libraries.AsBrWStr.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="AsIecCon" Source="Libraries.AsIecCon.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsOpcUac" Source="Libraries.AsOpcUac.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsOpcUas" Source="Libraries.AsOpcUas.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsTime" Source="Libraries.AsTime.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="AsUSB" Source="Libraries.AsUSB.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="BrbLib" Source="Libraries.BrbLib.lby" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <LibraryObject Name="BrbLibUa" Source="Libraries.BrbLibUa.lby" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <LibraryObject Name="Runtime" Source="Libraries.Runtime.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="standard" Source="Libraries.standard.lby" Memory="UserROM" Language="Binary" Debugging="true" />
    <LibraryObject Name="sys_lib" Source="Libraries.sys_lib.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="FileIO" Source="Libraries.FileIO.lby" Memory="UserROM" Language="binary" Debugging="true" />
    <LibraryObject Name="DataObj" Source="Libraries.DataObj.lby" Memory="UserROM" Language="binary" Debugging="true" />
  </Libraries>
</SwConfiguration>