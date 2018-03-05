#include "stdafx.h"
#include "JcDemuraEDC.h"

JcDemuraEDC::JcDemuraEDC(QWidget *parent)
	: QMainWindow(parent)
{
	m_JcEDCFormUI.setupUi(this);
	//m_nIndex = 1;
	
	//m_pJcQueueThread = NULL;
	//m_pJcQueueThread = new JcQueueThread(m_nIndex);    //JCMotorThread(int nChannelIndex, int nType)  后者表电机型号，前者
	m_nChannelIndex = 1;
	MemberInit();

	QString strExeName = QCoreApplication::applicationFilePath();       //获取可执行文件的文件路径
	QString strVersion = QtGlobarFunction::GetFileVertion(strExeName);  //获取可执行文件的版本信息
	m_strModuleDirPath = QCoreApplication::applicationDirPath() + "/system/module/";  //模组文件的路径
	setWindowTitle("EDC_V" + strVersion);
	QtGlobarFunction::CreateDir("/log");		//调用creatDirection实现，创建文件夹
	DMJcLog::Ref().WriteLog(eGUI, 0, eInfo, ("GUI Start, Version = " + strVersion).toStdString(), true); //all.log
	DMMessage::Ref().RegisterSignal(this);
	DMMessage::Ref().InitAllMember();

	InitModuleUI();
	SignalConnect();


	PlcInit();
	TcpSvrSocketInit();


	//MotorStateListen();
}


JcDemuraEDC::~JcDemuraEDC()
{
	//delete m_pJcMotor;
}

void JcDemuraEDC::MemberInit()
{
//	m_pJcQueueThread->AddRecvFunction(PLC_INIT, (RecvFunction)&JcDemuraEDC::ReceiveMessage);
	//m_pJcQueueThread->AddRecvFunction(MOTOR_OPENDONE, (RecvFunction)&JcDemuraEDC::ReceiveMessage);
	//m_pJcQueueThread->AddRecvFunction(MOTOR_HOMEDONE, (RecvFunction)&JcDemuraEDC::ReceiveMessage);
	//m_pJcQueueThread->AddRecvFunction(MOTOR_MOVEDONE, (RecvFunction)&JcDemuraEDC::ReceiveMessage);
	//m_pJcQueueThread->AddRecvFunction(MOTOR_CLOSE, (RecvFunction)&JcDemuraEDC::ReceiveMessage);
	//m_pJcQueueThread->AddRecvFunction(MOTOR_STATELISTEN, (RecvFunction)&JcDemuraEDC::ReceiveMessage);

}

#if 0
DWORD JcDemuraEDC::RecvMsgThread(PVOID lpParameter)
{
	JcDemuraEDC* pThis = (JcDemuraEDC*)lpParameter;

	while (true)
	{
		//pThis->ReceiveMessage(JcDemuraMessage& tMessage);
	}
	CloseHandle(pThis->m_hRecvMsg);
	return 0;
}
#endif

void JcDemuraEDC::SignalConnect()
{
	//connect(m_JcEDCFormUI.pushButton_Close, SIGNAL(clicked()), this, SLOT(reject()));
	connect(m_JcEDCFormUI.pushButton_DeleteModule, SIGNAL(clicked()), this, SLOT(Slot_DeleteModule()));
	connect(m_JcEDCFormUI.pushButton_SaveModule, SIGNAL(clicked()), this, SLOT(Slot_SaveModule()));
	connect(m_JcEDCFormUI.pushButton_Outport, SIGNAL(clicked()), this, SLOT(Slot_Outport()));
	connect(m_JcEDCFormUI.pushButton_Import, SIGNAL(clicked()), this, SLOT(Slot_Import()));
	connect(m_JcEDCFormUI.pushButton_Apply, SIGNAL(clicked()), this, SLOT(Slot_Apply()));
	connect(m_JcEDCFormUI.pushButtonCopy, SIGNAL(clicked()), this, SLOT(Slot_pushButtonCopy_click()));
	connect(m_JcEDCFormUI.twModuleList, SIGNAL(itemSelectionChanged()), this, SLOT(Slot_ModuleIndexChange()));

	connect(m_JcEDCFormUI.pbMotorInit,SIGNAL(clicked()),this,SLOT(Slot_pbMotorInit_click()));
	connect(m_JcEDCFormUI.pbMotorHome,SIGNAL(clicked()),this,SLOT(Slot_pbMotorHome_click()));
	connect(m_JcEDCFormUI.pbMotorClose, SIGNAL(clicked()), this, SLOT(Slot_pbMotorClose_click()));
	connect(m_JcEDCFormUI.pbMotorStop, SIGNAL(clicked()), this, SLOT(Slot_pbMotorStop_click()));
	connect(m_JcEDCFormUI.pbMotorPosMove, SIGNAL(clicked()), this, SLOT(Slot_pbMotorPosMove_click()));
	connect(m_JcEDCFormUI.pbMotorNegMove, SIGNAL(clicked()), this, SLOT(Slot_pbMotorNegMove_click()));
}

void JcDemuraEDC::Slot_pbMini_click()
{
	this->showMinimized();
	m_nWindowShowType = eWindowMinimize;
}

void JcDemuraEDC::Slot_pbMaxNormal_click()
{
	if (m_nWindowShowType == eWindowNormal)
	{
		this->showMaximized();
		m_nWindowShowType = eWindowMaximize;
	}
	else
	{
		m_nWindowShowType = eWindowNormal;
		this->showNormal();
	}
}

void JcDemuraEDC::Slot_pbClose_click()
{
	//进行相关提示
	//if (!CheckDeviceStatus(CHECKDEVICETYPE::eExitApp))
	//{
	//	return;
	//}

	//SaveLanguageSetting();

	this->close();
}

void JcDemuraEDC::PlcInit()
{
	JcDemuraMessage tMessage;
	tMessage.m_nChannelId = 1;
	tMessage.m_nMessageId = PLC_INIT;
	DMMessage::Ref().IssueMessge(DEMURA_PLC_MODULE, tMessage);
}


void JcDemuraEDC::TcpSvrSocketInit()
{
	JcDemuraMessage tMessage;
	tMessage.m_nChannelId = 1;
	tMessage.m_nMessageId = BURNSERVER_SOCKETINIT;
	DMMessage::Ref().IssueMessge(DEMURA_BURNSERVER_MODULE, tMessage);
}

//======================================================================================================
/**************************************消息处理函数****************************************************/
//======================================================================================================
void JcDemuraEDC::ReceiveMessage(JcDemuraMessage& tMessage)
{
	if (!tMessage.ExistBaseData())
	{
		return;
	}
	switch (tMessage.m_nMessageId)
	{
	case PLC_INIT:
		break;
	case BURNSERVER_SOCKETINIT:
		RecvServerInit(tMessage);
		break;
	case MOTOR_OPENDONE:
		RecvMotorInitDone(tMessage);
		break;
	case MOTOR_HOMEDONE:
		RecvMotorHomeDone(tMessage);
		break;
	case MOTOR_MOVEDONE:
		break;
	case MOTOR_CLOSE:
		break;
	case MOTOR_STATELISTEN:
		RecvMotorState(tMessage);
		break;
	case PLC_READ:
		RecvPlcRead(tMessage);
		break;
	default:
		{}
		break;
	}
	if (NULL != tMessage.m_pDemuraBaseData)
	{
		tMessage.m_pDemuraBaseData->SubDeleteIndex();
	}
}

void JcDemuraEDC::RecvServerInit(JcDemuraMessage& tMessage)
{
	if (0 == tMessage.m_nResult)
	{
		//SetLogText(tr("Burn server start success!"), eGUI, 1, eInfo);
	}
	else
	{
		//SetLogText(tr("Burn server start failed!"), eGUI, 1, eError);
	}
}

void JcDemuraEDC::RecvMotorInitDone(JcDemuraMessage & tMessage)
{
	if (0 == tMessage.m_nResult)
	{
		//SetLogText(tr("Motor Init success!"), eGUI, 1, eInfo);
		DMJcLog::Ref().WriteLog(1, 1, eInfo, "enter JcDemuraEDC RecvMotorInit success()");
	}
	else
	{
		//SetLogText(tr("Burn server start failed!"), eGUI, 1, eError);
	}
}

void JcDemuraEDC::RecvMotorHomeDone(JcDemuraMessage & tMessage)
{
	if (0 == tMessage.m_nResult)
	{
	}
	else
	{
	}
}

void JcDemuraEDC::RecvMotorState(JcDemuraMessage & tMessage)
{
	if (0 == tMessage.m_nResult)
	{
		MotorOutData* pData = (MotorOutData*)tMessage.m_pDemuraBaseData;
		double CurrentPos = pData->m_nPos;
		m_JcEDCFormUI.lbCurPosShow->setText(QString("%1").arg(CurrentPos));
	}
	else
	{
	}
}

void JcDemuraEDC::RecvPlcRead(JcDemuraMessage & tMessage)
{
	//------
}
//================================================================================================
/*=================模组文件编辑==================================================================*/
//================================================================================================
#if 1
void JcDemuraEDC::InitModuleUI()
{
	//QDesktopWidget* pDesktop = QApplication::desktop();
	//move((pDesktop->width() - this->width()) / 2, (pDesktop->height() - this->height()) / 2);
	//this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏  

	//ConnectSignal();
	//m_JcChangeModuleUi.twModuleName->setColumnWidth(0, 410);
	QStringList strList = QtGlobarFunction::GetDirectoryFiles(m_strModuleDirPath);  //获取模组文件的所有名称
	QString strModuleName = "";
	int nIndex = 0;
	int nCurrentIndex = -1;
	QString strCurrentModuleName = QString::fromStdString(DMSysParams::Ref().m_tModuleSetting.m_strCurrentModuleName);

	QtGlobarFunction::CreateDir("/system/module");
	//QtGlobarFunction::CreateDir("/system/images");
	//QtGlobarFunction::CreateDir("/system/camera");
	QtGlobarFunction::CreateDir("/system/config");

	m_JcEDCFormUI.twModuleList->setColumnWidth(0, 220);
	LoadModuleFile();
}

void JcDemuraEDC::LoadModuleFile()
{
	QStringList strList = QtGlobarFunction::GetDirectoryFiles(m_strModuleDirPath);
	m_JcEDCFormUI.twModuleList->setRowCount(0);
	QString strModuleName = "";
	QString strCurrentModuleName = QString::fromStdString(DMSysParams::Ref().m_tModuleSetting.m_strCurrentModuleName);
	int nCurentIndex = -1;
	for (int i = 0; i < strList.length(); i++)
	{
		if (strList.at(i).endsWith(".ts", Qt::CaseInsensitive))
		{
			strModuleName = strList.at(i).mid(0, strList.at(i).length() - 3);
			m_JcEDCFormUI.twModuleList->insertRow(m_JcEDCFormUI.twModuleList->rowCount());
			m_JcEDCFormUI.twModuleList->setItem(m_JcEDCFormUI.twModuleList->rowCount() - 1,
				0, new QTableWidgetItem(strModuleName));
			if (strModuleName == strCurrentModuleName)
			{
				nCurentIndex = m_JcEDCFormUI.twModuleList->rowCount() - 1;
			}
		}
	}
	if (nCurentIndex != -1)
	{
		m_JcEDCFormUI.twModuleList->setCurrentCell(nCurentIndex, 0);
	}
}

void JcDemuraEDC::ChangeModule(QString strModuleName)
{
	if (strModuleName.trimmed().isEmpty())
	{
		return;
	}

	XmlConfigMap tConfigMap;
	XmlMap tMap;
	tMap["CurrentModuleName"] = strModuleName.toStdString();

	if (0 != DMSysParams::Ref().m_tModuleSetting.m_strCurrentModuleName.compare(strModuleName.toStdString().c_str()))
	{
		tMap["bNeedCheckAutoMachine"] = "1";
		DMSysParams::Ref().m_tPublicSetting.m_bNeedCheckAutoMachine = true;
	}

	tConfigMap["SYSTEM"] = tMap;

	QString strPath = QCoreApplication::applicationDirPath() + "/system/config/systemconfig.ts";
	JcSystemXmlHandle tHandle(strPath);
	tHandle.SaveParams(tConfigMap);

	m_strCurTestName = strModuleName;
	DMSysParams::Ref().m_tModuleSetting.m_strCurrentModuleName = strModuleName.toStdString();
	//QDialog::accept();
}

void JcDemuraEDC::Slot_ModuleIndexChange()
{
	int nRowIndex = m_JcEDCFormUI.twModuleList->currentRow();
	if (nRowIndex == -1)
	{
		return;
	}
	QString strModuleName = m_JcEDCFormUI.twModuleList->item(nRowIndex, 0)->text();
	m_JcEDCFormUI.leModuleName->setText(strModuleName);
	QString strModulePath = m_strModuleDirPath + "/" + strModuleName + ".ts";
	JcModuleXMLHandle tModuleXMLHandle;
	tModuleXMLHandle.LoadParams(strModulePath, m_tXmlConfigMap, m_tCameraConfigMap);

	SetModuleParamsToUI(m_tCameraConfigMap, m_tXmlConfigMap);
}

void JcDemuraEDC::SetModuleParamsToUI(CameraConfigMap tCameraConfigMap, XmlConfigMap tXmlConfigMap)
{
	//根据模组的图片数据 初始化combox
	QString strTemp = "";
	QStringList strList;
	int nPatternCount = tCameraConfigMap.size();
	QComboBox* pcbItem = NULL;
	XmlConfigMap::iterator xmlIter = tXmlConfigMap.find("PARAM");
#if 0
	if (xmlIter != tXmlConfigMap.end())
	{
		m_JcEDCFormUI.chEngineCutPatternUsed->setChecked(QString::fromStdString(xmlIter->second["bEngineCutPatternUsed"]) == "1" ? true : false);
		m_JcEDCFormUI.cbBit->setCurrentText(QString::fromStdString(xmlIter->second["nBit"]));
		m_JcEDCFormUI.chbSaveCSV->setChecked(QString::fromStdString(xmlIter->second["bSaveCSV"]) == "1" ? true : false);
		m_JcEDCFormUI.chbSaveMat->setChecked(QString::fromStdString(xmlIter->second["bSaveMAT"]) == "1" ? true : false);
		m_JcEDCFormUI.chbSaveRoi->setChecked(QString::fromStdString(xmlIter->second["bSaveROI"]) == "1" ? true : false);
		m_JcEDCFormUI.le_PreProcessCount->setText(QString::fromStdString(xmlIter->second["uPreProcessNum"]));
		m_JcEDCFormUI.chIgnoreCorner->setChecked(QString::fromStdString(xmlIter->second["bIgnoreCornerStop"]) == "1" ? true : false);
		strTemp = QString::fromStdString(xmlIter->second["uLCDRes"]);
		strList.clear();
		if (!strTemp.isEmpty())
		{
			strList = strTemp.split(",");
		}
		if (0 == strList.size())
		{
			m_JcEDCFormUI.le_LCDWidth->setText("");
			m_JcEDCFormUI.le_LCDHeight->setText("");
		}
		else
		{
			m_JcEDCFormUI.le_LCDWidth->setText(strList.at(0));
			m_JcEDCFormUI.le_LCDHeight->setText(strList.at(1));
		}
		strTemp = QString::fromStdString(xmlIter->second["uRoiOffset"]);
		m_JcEDCFormUI.le_ROIOffset->setText(strTemp);
		strTemp = QString::fromStdString(xmlIter->second["bKillIDMark"]);
		m_JcModuleEditUi.chIDMark->setChecked("1" == strTemp ? true : false);
		strTemp = QString::fromStdString(xmlIter->second["uIDMarkRegion"]);
		m_JcModuleEditUi.le_IDMarkRegion->setText(strTemp);
		strTemp = QString::fromStdString(xmlIter->second["bKillFilmMark"]);
		m_JcModuleEditUi.chFilmMark->setChecked("1" == strTemp ? true : false);
		strTemp = QString::fromStdString(xmlIter->second["uFilmMarkRegion"]);
		m_JcModuleEditUi.le_FilmMark->setText(strTemp);
		strTemp = QString::fromStdString(xmlIter->second["bKillIgnore"]);
		m_JcModuleEditUi.chIgnore->setChecked("1" == strTemp ? true : false);
		strTemp = QString::fromStdString(xmlIter->second["uIgnoreRegion"]);
		m_JcModuleEditUi.le_IgnoreRegion->setText(strTemp);
		strTemp = QString::fromStdString(xmlIter->second["bKillParticle"]);
		m_JcModuleEditUi.chParticle->setChecked("1" == strTemp ? true : false);
		m_JcModuleEditUi.chLightParticle->setChecked("2" == strTemp ? true : false);
		strTemp = QString::fromStdString(xmlIter->second["bFindRepeatedParticle"]);
		m_JcModuleEditUi.chbFindRepeatedParticle->setChecked("1" == strTemp ? true : false);
		strTemp = QString::fromStdString(xmlIter->second["uParticleRegion"]);
		m_JcModuleEditUi.le_ParticleRegion->setText(strTemp);
		strTemp = QString::fromStdString(xmlIter->second["uParticleThreshold"]);
		m_JcModuleEditUi.le_ParticleThreshold->setText(strTemp);
		strTemp = QString::fromStdString(xmlIter->second["uParticleNum"]);
		m_JcModuleEditUi.le_ParticleNum->setText(strTemp);
		strTemp = QString::fromStdString(xmlIter->second["dAngle"]);
		m_JcModuleEditUi.chUDLRShift->setChecked("180" == strTemp ? true : false);
		strTemp = QString::fromStdString(xmlIter->second["bIsUDShift"]);
		m_JcModuleEditUi.chUDShift->setChecked("1" == strTemp ? true : false);
		strTemp = QString::fromStdString(xmlIter->second["bIsLRShift"]);
		m_JcModuleEditUi.chLRShift->setChecked("1" == strTemp ? true : false);
		m_JcModuleEditUi.leBlockSize->setText(QString::fromStdString(xmlIter->second["nBlockSize"]));
		strTemp = QString::fromStdString(xmlIter->second["bKillToucPoint"]);
		m_JcModuleEditUi.chbToucPoint->setChecked("1" == strTemp ? true : false);
	}

	m_JcModuleEditUi.twPatternList->setRowCount(nPatternCount);
	for (int i = 1; i <= nPatternCount; i++)
	{
		CameraConfigMap::iterator camIter = tCameraConfigMap.find(i);
		if (camIter != tCameraConfigMap.end())
		{
			m_JcModuleEditUi.twPatternList->setItem(i - 1, ePatternName,
				new QTableWidgetItem(QString::fromStdString(camIter->second["strPatternName"])));
			m_JcModuleEditUi.twPatternList->setItem(i - 1, ePatternRename,
				new QTableWidgetItem(QString::fromStdString(camIter->second["strPatternReName"])));
			m_JcModuleEditUi.twPatternList->setItem(i - 1, ePatternResolution,
				new QTableWidgetItem(QString::fromStdString(camIter->second["strResolution"])));
			m_JcModuleEditUi.twPatternList->setItem(i - 1, ePatternType,
				new QTableWidgetItem(QString::fromStdString(camIter->second["strPatternType"])));
			m_JcModuleEditUi.twPatternList->setItem(i - 1, ePatternExporseTime,
				new QTableWidgetItem(QString::fromStdString(camIter->second["strExposureTime"])));
			m_JcModuleEditUi.twPatternList->setItem(i - 1, ePatternGain,
				new QTableWidgetItem(QString::fromStdString(camIter->second["strGain"])));
			m_JcModuleEditUi.twPatternList->setItem(i - 1, ePatternLevel,
				new QTableWidgetItem(QString::fromStdString(camIter->second["strLevel"])));
			pcbItem = new QComboBox();
			pcbItem->setStyleSheet("background-color: rgb(255, 255, 255);");
			pcbItem->addItems(m_strCutType);
			pcbItem->setCurrentIndex(QString::fromStdString(camIter->second["nCutType"]).toInt());
			m_JcModuleEditUi.twPatternList->setCellWidget(i - 1, ePatternCutLevelUsed,
				pcbItem);
			m_JcModuleEditUi.twPatternList->setItem(i - 1, ePatternDelayTime,
				new QTableWidgetItem(QString::fromStdString(camIter->second["nDelayCutpattern"])));
			m_JcModuleEditUi.twPatternList->setItem(i - 1, ePatternCoeff,
				new QTableWidgetItem(QString::fromStdString(camIter->second["dCoeff"])));
			pcbItem = new QComboBox();
			pcbItem->setStyleSheet("background-color: rgb(255, 255, 255);");
			pcbItem->addItems(m_strEvaluateType);
			pcbItem->setCurrentIndex(QString::fromStdString(camIter->second["nEvaluateType"]).toInt());
			m_JcModuleEditUi.twPatternList->setItem(i - 1, ePatternCCDLevel,
				new QTableWidgetItem(QString::fromStdString(camIter->second["nCCDLevel"])));
			m_JcModuleEditUi.twPatternList->setCellWidget(i - 1, ePatternEvaluate,
				pcbItem);

			pcbItem = new QComboBox();
			pcbItem->setStyleSheet("background-color: rgb(255, 255, 255);");
			pcbItem->addItems(m_strLCDGamType);
			pcbItem->setCurrentIndex(QString::fromStdString(camIter->second["nLCDGammaType"]).toInt());
			m_JcModuleEditUi.twPatternList->setCellWidget(i - 1, ePatternLcdGam,
				pcbItem);
		}
	}
	//设置其他参
	xmlIter = tXmlConfigMap.find("ENGINEINIT");
	if (xmlIter != tXmlConfigMap.end())
	{
		m_JcModuleEditUi.cbICName->setCurrentIndex(
			m_JcModuleEditUi.cbICName->findText(QString::fromStdString(xmlIter->second["strIcName"])));
		m_JcModuleEditUi.le_hactive->setText(QString::fromStdString(xmlIter->second["nHActive"]));
		m_JcModuleEditUi.le_hback->setText(QString::fromStdString(xmlIter->second["nHBack"]));
		m_JcModuleEditUi.le_hfront->setText(QString::fromStdString(xmlIter->second["nHFront"]));
		m_JcModuleEditUi.le_hhsync->setText(QString::fromStdString(xmlIter->second["nHHsync"]));
		m_JcModuleEditUi.le_htotal->setText(QString::fromStdString(xmlIter->second["nHTotal"]));

		m_JcModuleEditUi.le_vactive->setText(QString::fromStdString(xmlIter->second["nVActive"]));
		m_JcModuleEditUi.le_vback->setText(QString::fromStdString(xmlIter->second["nVBack"]));
		m_JcModuleEditUi.le_vfront->setText(QString::fromStdString(xmlIter->second["nVFront"]));
		m_JcModuleEditUi.le_vhsync->setText(QString::fromStdString(xmlIter->second["nVHsync"]));
		m_JcModuleEditUi.le_vtotal->setText(QString::fromStdString(xmlIter->second["nVTotal"]));
		m_JcModuleEditUi.le_clock->setText(QString::number((QString::fromStdString(xmlIter->second["nPixelClock"]).toInt() / 1000000.0)));
		m_JcModuleEditUi.leScreenSize->setText(QString::fromStdString(xmlIter->second["nScreenSize"]));
	}

	xmlIter = tXmlConfigMap.find("UI");
	if (xmlIter != tXmlConfigMap.end())
	{
		//V2新增参数
		m_JcModuleEditUi.cbRepairType->setCurrentIndex(QString::fromStdString(xmlIter->second["nRepairType"]).toInt());
		m_JcModuleEditUi.chbEvaluate->setChecked(QString::fromStdString(xmlIter->second["bOLEDEvaluate"]) == "1" ? true : false);
		m_JcModuleEditUi.chbSaveSim->setChecked(QString::fromStdString(xmlIter->second["bOLEDMakeSim"]) == "1" ? true : false);
		m_JcModuleEditUi.le_TemsCutPatternFirstIndex->setText(QString::fromStdString(xmlIter->second["nTemsCutPatternFirstIndex"]));
		m_JcModuleEditUi.chAOIUsed->setChecked(QString::fromStdString(xmlIter->second["bAOIUsed"]) == "1" ? true : false);
		m_JcModuleEditUi.chAOIDemuraPatternShared->setChecked(
			QString::fromStdString(xmlIter->second["bAOIDemuraPatternShared"]) == "1" ? true : false);
		m_JcModuleEditUi.le_AOIPatternCount->setText(QString::fromStdString(xmlIter->second["nAOIPatternCount"]));
		m_JcModuleEditUi.cbEvaluateType->setCurrentIndex(QString::fromStdString(xmlIter->second["nEvaluateType"]).toInt());
		strTemp = QString::fromStdString(xmlIter->second["dHVas"]);
		m_JcModuleEditUi.le_HVas->setText(strTemp);
		strTemp = QString::fromStdString(xmlIter->second["dVVas"]);
		m_JcModuleEditUi.le_VVas->setText(strTemp);
		strTemp = QString::fromStdString(xmlIter->second["dJND"]);
		m_JcModuleEditUi.le_JND->setText(strTemp);
		strTemp = QString::fromStdString(xmlIter->second["nDemuraFirstPatternIndex"]);
		m_JcModuleEditUi.le_DemuraFirstIndex->setText(strTemp);
	}

	xmlIter = tXmlConfigMap.find("BIN");
	if (xmlIter != tXmlConfigMap.end())
	{
		m_JcModuleEditUi.leLowBound->setText(QString::fromStdString(xmlIter->second["nLowBound"]));
		m_JcModuleEditUi.leHighBound->setText(QString::fromStdString(xmlIter->second["nHighBound"]));
	}
#endif
}


void JcDemuraEDC::Slot_SaveModule()
{
#if 0
	QString strModuleName = m_JcEDCFormUI.leModuleName->text();
	if (strModuleName.trimmed().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("Module name is empty."));
		return;
	}
	//判断调试是否符合
	bool bSaveEnable = true;
	QTableWidgetItem* twItem = NULL;
	for (int i = 0; i < m_JcEDCFormUI.twPatternList->rowCount(); i++)
	{
		twItem = m_JcEDCFormUI.twPatternList->item(i, ePatternLevel);
		if (NULL == twItem || twItem->text().isEmpty())
		{
			QMessageBox::warning(this, tr("Warning"), tr("Pattern level is empty."));
			return;
		}
		/*twItem = m_JcModuleEditUi.twPatternList->item(i, ePatternCCDLevel);
		if (NULL == twItem || twItem->text().isEmpty())
		{
		QMessageBox::warning(this, tr("Warning"), tr("CCD level is empty."));
		return;
		}*/
	}
	//判断文件是否已经存在	
	bool bFileExist = false;
	QString strTemp = "";
	for (int i = 0; i < m_JcEDCFormUI.twModuleList->rowCount(); i++)
	{
		strTemp = m_JcModuleEditUi.twModuleList->item(i, 0)->text();
		if (QString::compare(strTemp, strModuleName, Qt::CaseInsensitive) == 0)
		{
			bFileExist = true;
			break;
		}
	}
	JcModuleXMLHandle tModuleXmlHandle;
	m_tCameraConfigMap.clear();
	QComboBox* tcbItem = NULL;
	XmlConfigMap::iterator xmlIter;
	QString strCoeff = "";
	QString strGammaPredict = "";
	int nLCDGammaPredictCount = 0;
	bool bOLEDParticleUsed = false;
	//保存图片数据流程	
	for (int i = 0; i < m_JcModuleEditUi.twPatternList->rowCount(); i++)
	{
		XmlMap tXmlMap;
		tXmlMap["strPatternName"] = m_JcModuleEditUi.twPatternList->item(i, ePatternName)->text().toStdString().c_str();
		twItem = m_JcModuleEditUi.twPatternList->item(i, ePatternRename);
		if (twItem != NULL)
		{
			tXmlMap["strPatternReName"] = m_JcModuleEditUi.twPatternList->item(i, ePatternRename)->text().toStdString().c_str();
		}
		else
		{
			tXmlMap["strPatternReName"] = "";
		}
		tXmlMap["strResolution"] = m_JcModuleEditUi.twPatternList->item(i, ePatternResolution)->text().toStdString().c_str();
		tXmlMap["strPatternType"] = m_JcModuleEditUi.twPatternList->item(i, ePatternType)->text().toStdString().c_str();
		twItem = m_JcModuleEditUi.twPatternList->item(i, ePatternExporseTime);
		if (twItem != NULL && !twItem->text().isEmpty())
		{
			tXmlMap["strExposureTime"] = twItem->text().toStdString();
		}
		else
		{
			tXmlMap["strExposureTime"] = "1";
		}
		twItem = m_JcModuleEditUi.twPatternList->item(i, ePatternGain);
		if (twItem != NULL && !twItem->text().isEmpty())
		{
			tXmlMap["strGain"] = twItem->text().toStdString().c_str();
		}
		else
		{
			tXmlMap["strGain"] = "0";
		}

		twItem = m_JcModuleEditUi.twPatternList->item(i, ePatternLevel);
		if (twItem != NULL)
		{
			tXmlMap["strLevel"] = twItem->text().toStdString().c_str();
		}
		else
		{
			tXmlMap["strLevel"] = "";
		}

		tcbItem = (QComboBox*)m_JcModuleEditUi.twPatternList->cellWidget(i, ePatternCutLevelUsed);
		if (tcbItem != NULL)
		{
			tXmlMap["nCutType"] = QString::number(tcbItem->currentIndex()).toStdString();
		}
		else
		{
			tXmlMap["nCutType"] = "0";
		}
		if (i == m_JcModuleEditUi.twPatternList->rowCount() - 1)
		{
			bOLEDParticleUsed = (eAOIUpPartical == QString::fromStdString(tXmlMap["nCutType"]).toInt() ? true : false);
		}

		twItem = m_JcModuleEditUi.twPatternList->item(i, ePatternDelayTime);
		if (twItem != NULL)
		{
			tXmlMap["nDelayCutpattern"] = twItem->text().toStdString();
		}
		else
		{
			tXmlMap["nDelayCutpattern"] = "0";
		}

		twItem = m_JcModuleEditUi.twPatternList->item(i, ePatternCoeff);
		if (twItem != NULL)
		{
			tXmlMap["dCoeff"] = twItem->text().toStdString();
		}
		else
		{
			tXmlMap["dCoeff"] = "0";
		}

		tcbItem = (QComboBox*)m_JcModuleEditUi.twPatternList->cellWidget(i, ePatternEvaluate);
		if (tcbItem != NULL)
		{
			tXmlMap["nEvaluateType"] = QString::number(tcbItem->currentIndex()).toStdString();
		}
		else
		{
			tXmlMap["nEvaluateType"] = "0";
		}

		tcbItem = (QComboBox*)m_JcModuleEditUi.twPatternList->cellWidget(i, ePatternLcdGam);
		if (tcbItem != NULL)
		{
			int nLCDGamma = tcbItem->currentIndex();
			tXmlMap["nLCDGammaType"] = QString::number(tcbItem->currentIndex()).toStdString();
			if (nLCDGamma == 1)
			{
				nLCDGammaPredictCount++;
				if (!strGammaPredict.isEmpty())
				{
					strGammaPredict += ",";
				}
				strGammaPredict += QString::fromStdString(tXmlMap["strLevel"]);
			}
		}
		else
		{
			tXmlMap["nLCDGammaType"] = "0";
		}
		twItem = m_JcModuleEditUi.twPatternList->item(i, ePatternCCDLevel);
		if (twItem != NULL)
		{
			if (!twItem->text().isEmpty())
			{
				tXmlMap["nCCDLevel"] = twItem->text().toStdString();
			}
			else
			{
				tXmlMap["nCCDLevel"] = "130";
			}
		}
		else
		{
			tXmlMap["nCCDLevel"] = "130";
		}
		m_tCameraConfigMap[i + 1] = tXmlMap;
	}
	//加载界面其他参数
	//设置其他参数
	if (!bFileExist)
	{
		QString strPath = QCoreApplication::applicationDirPath() + "/system/config/";
		QString strPathTemp = strPath;
		if (DMSysParams::Ref().m_tPublicSetting.m_strModuleType == "OLED")
		{
			strPathTemp = strPath + "defaultoledconfig.ts";
		}
		else
		{
			strPathTemp = strPath + "defaultlcdconfig.ts";
		}
		if (!QFile::exists(strPathTemp))
		{
			strPathTemp = strPath + "defaultdemuraconfig.ts";
		}
		tModuleXmlHandle.GetDefaultParams(m_tXmlConfigMap, strPathTemp);
	}

	xmlIter = m_tXmlConfigMap.find("UI");
	if (xmlIter == m_tXmlConfigMap.end())
	{
		XmlMap tMap;
		m_tXmlConfigMap["UI"] = tMap;
		xmlIter = m_tXmlConfigMap.find("UI");
	}

	//V2新增参数
	xmlIter->second["nRepairType"] = QString::number(m_JcModuleEditUi.cbRepairType->currentIndex()).toStdString();
	xmlIter->second["nTemsCutPatternFirstIndex"] = m_JcModuleEditUi.le_TemsCutPatternFirstIndex->text().toStdString();
	xmlIter->second["bOLEDEvaluate"] = m_JcModuleEditUi.chbEvaluate->isChecked() ? "1" : "0";
	xmlIter->second["bOLEDMakeSim"] = m_JcModuleEditUi.chbSaveSim->isChecked() ? "1" : "0";
	xmlIter->second["bAOIUsed"] = m_JcModuleEditUi.chAOIUsed->isChecked() ? "1" : "0";
	xmlIter->second["bAOIDemuraPatternShared"] = m_JcModuleEditUi.chAOIDemuraPatternShared->isChecked() ? "1" : "0";
	xmlIter->second["nAOIPatternCount"] = m_JcModuleEditUi.le_AOIPatternCount->text().toStdString();
	xmlIter->second["nEvaluateType"] = QString::number(m_JcModuleEditUi.cbEvaluateType->currentIndex()).toStdString();
	xmlIter->second["dHVas"] = m_JcModuleEditUi.le_HVas->text().toStdString();
	xmlIter->second["dVVas"] = m_JcModuleEditUi.le_VVas->text().toStdString();
	xmlIter->second["dJND"] = m_JcModuleEditUi.le_JND->text().toStdString();
	xmlIter->second["nDemuraFirstPatternIndex"] = m_JcModuleEditUi.le_DemuraFirstIndex->text().toStdString();

	xmlIter = m_tXmlConfigMap.find("PARAM");
	if (xmlIter == m_tXmlConfigMap.end())
	{
		XmlMap tMap;
		m_tXmlConfigMap["PARAM"] = tMap;
		xmlIter = m_tXmlConfigMap.find("PARAM");
	}
	xmlIter->second["bEngineCutPatternUsed"] = m_JcModuleEditUi.chEngineCutPatternUsed->isChecked() ? "1" : "0";
	xmlIter->second["nBit"] = m_JcModuleEditUi.cbBit->currentText().toStdString();
	xmlIter->second["bIgnoreCornerStop"] = m_JcModuleEditUi.chIgnoreCorner->isChecked() ? "1" : "0";
	int nPreCount = m_JcModuleEditUi.le_PreProcessCount->text().toInt();
	nPreCount = nPreCount <= 1 ? 1 : nPreCount;
	if (DMSysParams::Ref().m_tPublicSetting.m_strModuleType != "OLED")
	{
		nPreCount = 2;
	}
	xmlIter->second["uLcdGammaNum"] = QString::number(nLCDGammaPredictCount).toStdString();
	xmlIter->second["uPredictGrayLevel"] = strGammaPredict.toStdString();
	xmlIter->second["uPreProcessNum"] = QString::number(nPreCount).toStdString();
	int nDemuraFirstPatternCount = m_JcModuleEditUi.le_DemuraFirstIndex->text().toInt();
	if (0 >= nDemuraFirstPatternCount)
	{
		nDemuraFirstPatternCount = 1;
	}
	nDemuraFirstPatternCount += nPreCount;
	nDemuraFirstPatternCount -= 1;

	int nPatternCount = m_JcModuleEditUi.twPatternList->rowCount();
	int nPannelNum = nPatternCount - nDemuraFirstPatternCount;
	if (0 >= nPannelNum)
	{
		QMessageBox::warning(this, tr("Warning"), tr("Demura Pattern number smaller than 0!"));
		return;
	}
	xmlIter->second["uPanelNum"] = QString::number(nPannelNum).toStdString();
	QString strGrayLevel = "";
	QString strExporseTime = "";
	QString strGain = "";
	//保存Pre处理参数
	for (int i = 0; i < nDemuraFirstPatternCount; i++)
	{
		if (i != nDemuraFirstPatternCount - 1)
		{
			strGrayLevel += m_JcModuleEditUi.twPatternList->item(i, ePatternLevel)->text() + ",";
			strExporseTime += m_JcModuleEditUi.twPatternList->item(i, ePatternExporseTime)->text() + ",";
			strGain += m_JcModuleEditUi.twPatternList->item(i, ePatternGain)->text() + ",";
		}
		else
		{
			strGrayLevel += m_JcModuleEditUi.twPatternList->item(i, ePatternLevel)->text();
			strExporseTime += m_JcModuleEditUi.twPatternList->item(i, ePatternExporseTime)->text();
			strGain += m_JcModuleEditUi.twPatternList->item(i, ePatternGain)->text();
		}
	}
	xmlIter->second["uPreGrayLevel"] = strGrayLevel.toStdString();
	xmlIter->second["uPreExptime"] = strExporseTime.toStdString();
	xmlIter->second["dPreGain"] = strGain.toStdString();
	strGrayLevel = "";
	strCoeff = "";
	strExporseTime = "";
	strGain = "";
	//保存算法的其他参数
	for (int i = nDemuraFirstPatternCount; i < nPatternCount; i++)
	{
		if (i != nPatternCount - 1)
		{
			strGrayLevel += m_JcModuleEditUi.twPatternList->item(i, ePatternLevel)->text() + ",";
			strCoeff += m_JcModuleEditUi.twPatternList->item(i, ePatternCoeff)->text() + ",";
			strExporseTime += m_JcModuleEditUi.twPatternList->item(i, ePatternExporseTime)->text() + ",";
			strGain += m_JcModuleEditUi.twPatternList->item(i, ePatternGain)->text() + ",";
		}
		else
		{
			strGrayLevel += m_JcModuleEditUi.twPatternList->item(i, ePatternLevel)->text();
			strCoeff += m_JcModuleEditUi.twPatternList->item(i, ePatternCoeff)->text();
			strExporseTime += m_JcModuleEditUi.twPatternList->item(i, ePatternExporseTime)->text();
			strGain += m_JcModuleEditUi.twPatternList->item(i, ePatternGain)->text();
		}
	}
	xmlIter->second["uGrayLevel"] = strGrayLevel.toStdString();
	xmlIter->second["dGrayCoeff"] = strCoeff.toStdString();
	xmlIter->second["uExptime"] = strExporseTime.toStdString();
	xmlIter->second["dGain"] = strGain.toStdString();
	xmlIter->second["uLCDRes"] = m_JcModuleEditUi.le_LCDWidth->text().toStdString() + ","
		+ m_JcModuleEditUi.le_LCDHeight->text().toStdString();
	xmlIter->second["uRoiOffset"] = m_JcModuleEditUi.le_ROIOffset->text().toStdString();
	xmlIter->second["bKillIDMark"] = m_JcModuleEditUi.chIDMark->isChecked() ? "1" : "0";
	xmlIter->second["uIDMarkRegion"] = m_JcModuleEditUi.le_IDMarkRegion->text().toStdString();
	xmlIter->second["bKillFilmMark"] = m_JcModuleEditUi.chFilmMark->isChecked() ? "1" : "0";
	xmlIter->second["uFilmMarkRegion"] = m_JcModuleEditUi.le_FilmMark->text().toStdString();
	xmlIter->second["bKillIgnore"] = m_JcModuleEditUi.chIgnore->isChecked() ? "1" : "0";
	xmlIter->second["uIgnoreRegion"] = m_JcModuleEditUi.le_IgnoreRegion->text().toStdString();
	int nOLEDParticalEnable = 0;
	if (m_JcModuleEditUi.chParticle->isChecked())
	{
		nOLEDParticalEnable = 1;
	}
	else if (m_JcModuleEditUi.chLightParticle->isChecked())
	{
		nOLEDParticalEnable = 2;
	}
	xmlIter->second["bKillParticle"] = QString::number(nOLEDParticalEnable).toStdString();
	xmlIter->second["bFindRepeatedParticle"] = m_JcModuleEditUi.chbFindRepeatedParticle->isChecked() ? "1" : "0";
	xmlIter->second["uParticleRegion"] = m_JcModuleEditUi.le_ParticleRegion->text().toStdString();
	xmlIter->second["uParticleThreshold"] = m_JcModuleEditUi.le_ParticleThreshold->text().toStdString();
	xmlIter->second["uParticleNum"] = m_JcModuleEditUi.le_ParticleNum->text().toStdString();
	xmlIter->second["dAngle"] = m_JcModuleEditUi.chUDLRShift->isChecked() ? "180" : "0";
	xmlIter->second["bIsUDShift"] = m_JcModuleEditUi.chUDShift->isChecked() ? "1" : "0";
	xmlIter->second["bIsLRShift"] = m_JcModuleEditUi.chLRShift->isChecked() ? "1" : "0";
	xmlIter->second["bSaveCSV"] = m_JcModuleEditUi.chbSaveCSV->isChecked() ? "1" : "0";
	xmlIter->second["bSaveMAT"] = m_JcModuleEditUi.chbSaveMat->isChecked() ? "1" : "0";
	xmlIter->second["bSaveROI"] = m_JcModuleEditUi.chbSaveRoi->isChecked() ? "1" : "0";
	xmlIter->second["bKillToucPoint"] = m_JcModuleEditUi.chbToucPoint->isChecked() ? "1" : "0";


	xmlIter = m_tXmlConfigMap.find("ENGINEINIT");
	if (xmlIter == m_tXmlConfigMap.end())
	{
		XmlMap tMap;
		m_tXmlConfigMap["ENGINEINIT"] = tMap;
		xmlIter = m_tXmlConfigMap.find("ENGINEINIT");
	}

	xmlIter->second["strIcName"] = m_JcModuleEditUi.cbICName->currentText().toStdString();
	//Timming部分
	xmlIter->second["nHActive"] = m_JcModuleEditUi.le_hactive->text().toStdString();
	xmlIter->second["nHBack"] = m_JcModuleEditUi.le_hback->text().toStdString();
	xmlIter->second["nHFront"] = m_JcModuleEditUi.le_hfront->text().toStdString();
	xmlIter->second["nHHsync"] = m_JcModuleEditUi.le_hhsync->text().toStdString();
	xmlIter->second["nHTotal"] = m_JcModuleEditUi.le_htotal->text().toStdString();
	xmlIter->second["nVActive"] = m_JcModuleEditUi.le_vactive->text().toStdString();
	xmlIter->second["nVBack"] = m_JcModuleEditUi.le_vback->text().toStdString();
	xmlIter->second["nVFront"] = m_JcModuleEditUi.le_vfront->text().toStdString();
	xmlIter->second["nVHsync"] = m_JcModuleEditUi.le_vhsync->text().toStdString();
	xmlIter->second["nVTotal"] = m_JcModuleEditUi.le_vtotal->text().toStdString();
	xmlIter->second["nPixelClock"] = QString::number((int)(m_JcModuleEditUi.le_clock->text().toDouble() * 1000000)).toStdString();
	xmlIter->second["nScreenSize"] = m_JcModuleEditUi.leScreenSize->text().toStdString();

	//OLED 添加图形数为3的倍数的相关提示
	if (DMSysParams::Ref().m_tPublicSetting.m_strModuleType == "OLED")
	{
		if (bOLEDParticleUsed)
		{
			nPannelNum -= 1;
		}
		if (0 != (nPannelNum % 3))
		{
			if (QMessageBox::StandardButton::Ok != QMessageBox::information(this, tr("Information"),
				tr("OLED repair pattern not a multiple of 3, are you contiune?"), QMessageBox::Ok | QMessageBox::Cancel))
			{
				return;
			}
		}
	}

	//存储
	QString strModulePath = m_strModuleDirPath + "/" + strModuleName + ".ts";
	tModuleXmlHandle.SaveParams(strModulePath, m_tXmlConfigMap, m_tCameraConfigMap);
	if (!bFileExist)
	{
		int nRowCount = m_JcModuleEditUi.twModuleList->rowCount();
		m_JcModuleEditUi.twModuleList->setRowCount(nRowCount + 1);
		m_JcModuleEditUi.twModuleList->setItem(nRowCount, 0, new QTableWidgetItem(strModuleName));
	}
#endif
	QMessageBox::warning(this, tr("Information"), tr("Save module file success!"));
}


void JcDemuraEDC::Slot_DeleteModule()
{
	if (QMessageBox::StandardButton::Ok != QMessageBox::information(this, tr("Information"),
		tr("Are you sure delete?"), QMessageBox::Ok | QMessageBox::Cancel))
	{
		return;
	}
	QList<int> PatternRowVector;
	QList<QTableWidgetItem *>  PatternIndexList;
	PatternIndexList = m_JcEDCFormUI.twModuleList->selectedItems();
	for (int k = 0; k < PatternIndexList.count(); k++)
	{
		if (!PatternRowVector.contains(PatternIndexList.at(k)->row()))
		{
			PatternRowVector.append(PatternIndexList.at(k)->row());
		}
	}
	qSort(PatternRowVector.begin(), PatternRowVector.end());
	QString strFilePath = "";
	for (int i = PatternRowVector.length() - 1; i >= 0; i--)
	{
		strFilePath = m_strModuleDirPath + "/" + m_JcEDCFormUI.twModuleList->item(PatternRowVector.at(i), 0)->text() + ".ts";
		QFile::remove(strFilePath);
		m_JcEDCFormUI.twModuleList->removeRow(PatternRowVector.at(i));
	}
}
void JcDemuraEDC::Slot_Import()
{
	//导入
	QString path = QCoreApplication::applicationDirPath();
	QString strFilter;
	strFilter = "Module File(*.zip );;Binary File(*.txt)";
	QStringList FilePathList = QFileDialog::getOpenFileNames(this, tr("open file dialog"), path, strFilter);
	QString strDecDir = QCoreApplication::applicationDirPath() + "/system";
	QString strTemp = "";
	QString strModuleName = "";
	strDecDir.replace("/", "\\");
	int nCurrentIndex = -1;
	for (int i = 0; i < FilePathList.length(); i++)
	{
		HZIP hz = OpenZip(QStringToTCHAR(FilePathList.at(i)), 0);
		ZIPENTRY ze;
		GetZipItem(hz, -1, &ze);
		int numitems = ze.index;
		for (int i = 0; i<numitems; i++)
		{
			GetZipItem(hz, i, &ze);
			strTemp = strDecDir + "\\" + TCHARToQString(ze.name);
			strTemp.replace("/", "\\");
			if (strTemp.endsWith(".ts"))
			{
				int nIndex = strTemp.lastIndexOf("\\");
				strModuleName = strTemp.mid(nIndex + 1);
				strModuleName = strModuleName.left(strModuleName.length() - 3);
			}
			UnzipItem(hz, i, QStringToTCHAR(strTemp));
		}
		CloseZip(hz);
		nCurrentIndex = -1;
		for (int i = 0; i < m_JcEDCFormUI.twModuleList->rowCount(); i++)
		{
			if (QString::compare(strModuleName, m_JcEDCFormUI.twModuleList->item(i, 0)->text(), Qt::CaseInsensitive) == 0)
			{
				nCurrentIndex = i;
				break;
			}
		}
		if (nCurrentIndex == -1)
		{
			nCurrentIndex = m_JcEDCFormUI.twModuleList->rowCount();
			m_JcEDCFormUI.twModuleList->insertRow(nCurrentIndex);
			m_JcEDCFormUI.twModuleList->setItem(nCurrentIndex, 0, new QTableWidgetItem(strModuleName));
		}
	}
	m_JcEDCFormUI.twModuleList->setCurrentCell(nCurrentIndex, 0);
	QMessageBox::warning(this, tr("Information"), tr("Import module file success!"));
}

void JcDemuraEDC::Slot_Outport()
{
	//导出 
	int nCurrentRow = m_JcEDCFormUI.twModuleList->currentRow();
	if (nCurrentRow == -1)
	{
		//return;
	}
	QString strModuleName = m_JcEDCFormUI.twModuleList->item(nCurrentRow, 0)->text();
	QString strFilePath = QFileDialog::getSaveFileName(this, tr("Save File"), strModuleName + ".zip", tr("Module File (*.zip)"));
	if (strFilePath.isEmpty())
	{
		//return;
	}
	QString strModulePath = m_strModuleDirPath + "/" + strModuleName + ".ts";
	JcModuleXMLHandle tModuleXMLHandle;
	XmlConfigMap tXmlConifgMap;
	CameraConfigMap tCameraConfigMap;
	tModuleXMLHandle.LoadParams(strModulePath, tXmlConifgMap, tCameraConfigMap);
	if (tCameraConfigMap.size() <= 0)
	{
		return;
	}
	CameraConfigMap::iterator  itor;
	QString strSrcTemp = "";
	QString strDecTemp = "";
	strModulePath.replace("/", "\\");
	HZIP hz = CreateZip(QStringToTCHAR(strFilePath), 0);
	strDecTemp = "module\\" + strModuleName + ".ts";
	ZipAdd(hz, QStringToTCHAR(strDecTemp),
		QStringToTCHAR(strModulePath));
	for (int i = 1; i <= tCameraConfigMap.size(); i++)
	{
		itor = tCameraConfigMap.find(i);
		strDecTemp = QString::fromStdString(itor->second["strResolution"]) + "\\" +
			QString::fromStdString(itor->second["strPatternName"]) + "." +
			QString::fromStdString(itor->second["strPatternType"]);
		strSrcTemp = m_strImageDirPath + "/" + strDecTemp;
		strSrcTemp.replace("/", "\\");
		strDecTemp = "images\\" + strDecTemp;
		ZipAdd(hz, QStringToTCHAR(strDecTemp),
			QStringToTCHAR(strSrcTemp));
	}
	CloseZip(hz);
	QMessageBox::warning(this, tr("Information"), tr("Ouput module file success!"));
}

void JcDemuraEDC::Slot_Apply()
{
	QString strModuleName = m_JcEDCFormUI.leModuleName->text();
	if (strModuleName.trimmed().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("Module name is empty."));
		return;
	}

	ChangeModule(strModuleName);
#if 0
	//导出 
	int nCurrentRow = m_JcEDCFormUI.twModuleList->currentRow();
	if (nCurrentRow == -1)
	{
		return;
	}
	QString strModuleName = m_JcEDCFormUI.twModuleList->item(nCurrentRow, 0)->text();
	QString strFilePath = QFileDialog::getSaveFileName(this, tr("Save File"), strModuleName + ".zip", tr("Module File (*.zip)"));
	if (strFilePath.isEmpty())
	{
		return;
	}
	QString strModulePath = m_strModuleDirPath + "/" + strModuleName + ".ts";
	JcModuleXMLHandle tModuleXMLHandle;
	XmlConfigMap tXmlConifgMap;
	CameraConfigMap tCameraConfigMap;
	tModuleXMLHandle.LoadParams(strModulePath, tXmlConifgMap, tCameraConfigMap);
	if (tCameraConfigMap.size() <= 0)
	{
		return;
	}
	CameraConfigMap::iterator  itor;
	QString strSrcTemp = "";
	QString strDecTemp = "";
	strModulePath.replace("/", "\\");
	HZIP hz = CreateZip(QStringToTCHAR(strFilePath), 0);
	strDecTemp = "module\\" + strModuleName + ".ts";
	ZipAdd(hz, QStringToTCHAR(strDecTemp),
		QStringToTCHAR(strModulePath));
	for (int i = 1; i <= tCameraConfigMap.size(); i++)
	{
		itor = tCameraConfigMap.find(i);
		strDecTemp = QString::fromStdString(itor->second["strResolution"]) + "\\" +
			QString::fromStdString(itor->second["strPatternName"]) + "." +
			QString::fromStdString(itor->second["strPatternType"]);
		strSrcTemp = m_strImageDirPath + "/" + strDecTemp;
		strSrcTemp.replace("/", "\\");
		strDecTemp = "images\\" + strDecTemp;
		ZipAdd(hz, QStringToTCHAR(strDecTemp),
			QStringToTCHAR(strSrcTemp));
	}
	CloseZip(hz);
	QMessageBox::warning(this, tr("Information"), tr("Ouput module file success!"));
#endif
}

void JcDemuraEDC::Slot_pushButtonCopy_click()
{
	int nRow = m_JcEDCFormUI.twModuleList->currentRow();
	if (-1 == nRow)
	{
		QMessageBox::warning(this, tr("Warning"), tr("Please select file first!"));
		return;
	}
	QString strDecName = m_JcEDCFormUI.leModuleName->text();
	if (strDecName.trimmed().isEmpty())
	{
		QMessageBox::warning(this, tr("Warning"), tr("Module name is empty."));
		return;
	}
	QString strSrcName = m_JcEDCFormUI.twModuleList->item(nRow, 0)->text();
	if (0 == strSrcName.compare(strDecName))
	{
		QMessageBox::warning(this, tr("Warning"), tr("Copy name is same."));
		return;
	}
	bool bFileExist = false;
	QString strTemp = "";
	for (int i = 0; i < m_JcEDCFormUI.twModuleList->rowCount(); i++)
	{
		strTemp = m_JcEDCFormUI.twModuleList->item(i, 0)->text();
		if (QString::compare(strTemp, strDecName, Qt::CaseInsensitive) == 0)
		{
			bFileExist = true;
			break;
		}
	}
	if (bFileExist)
	{
		QMessageBox::warning(this, tr("Warning"), tr("File name exist!"));
		return;
	}
	QString strSrcPath = m_strModuleDirPath + "/" + strSrcName + ".ts";
	QString strDecPath = m_strModuleDirPath + "/" + strDecName + ".ts";
	QFile::copy(strSrcPath, strDecPath);
	int nRowCount = m_JcEDCFormUI.twModuleList->rowCount();
	m_JcEDCFormUI.twModuleList->setRowCount(nRowCount + 1);
	m_JcEDCFormUI.twModuleList->setItem(nRowCount, 0, new QTableWidgetItem(strDecName));
	QMessageBox::warning(this, tr("Warning"), tr("Copy file success!"));
}
#endif

//================================================================================================
/*========================================电机控制编辑==========================================*/
//================================================================================================

void JcDemuraEDC::MotorStateListen()
{
	JcDemuraMessage tListenMessage;
	tListenMessage.m_nMessageId = MOTOR_STATELISTEN;
	tListenMessage.m_nChannelId = 1 << (m_nChannelIndex - 1);
	tListenMessage.m_nResult = ALL_SUCCESS;

	MotorOutData* pOutData = new MotorOutData();
	pOutData->m_nAxis = 0;
	pOutData->m_nListenType = 1;
		
	tListenMessage.m_pDemuraBaseData = pOutData;
	
	DMMessage::Ref().IssueMessge(DEMURA_MOTOR_MODULE, tListenMessage);
}

void JcDemuraEDC::Slot_pbMotorInit_click()
{
	JcDemuraMessage tOpenMessage;
	tOpenMessage.m_nMessageId = MOTOR_OPEN;
	tOpenMessage.m_nChannelId = 1 << (m_nChannelIndex - 1);

	DMMessage::Ref().IssueMessge(DEMURA_MOTOR_MODULE, tOpenMessage);
}

void JcDemuraEDC::Slot_pbMotorHome_click()
{
	JcDemuraMessage tMessage;
	tMessage.m_nMessageId = MOTOR_HOME;
	tMessage.m_nChannelId = 1 << (m_nChannelIndex - 1);

	MotorInData* pInData = new MotorInData();
	pInData->m_nAxis = 0;
	pInData->m_nCurVel = m_JcEDCFormUI.leMotorCurvel->text().toInt();
	pInData->m_nMaxVel = m_JcEDCFormUI.leMotorMaxvel->text().toInt();
	pInData->m_nDir = -1;
	tMessage.m_pDemuraBaseData = pInData;

	DMMessage::Ref().IssueMessge(DEMURA_MOTOR_MODULE, tMessage);
	DMJcLog::Ref().WriteMsgIdLog(DEMURA_MOTOR_MODULE, m_nChannelIndex, eRecv, tMessage.m_nMessageId);
}

void JcDemuraEDC::Slot_pbMotorClose_click()
{
	JcDemuraMessage tCloseMessage;
	tCloseMessage.m_nMessageId = MOTOR_CLOSE;
	tCloseMessage.m_nChannelId = 1 << (m_nChannelIndex - 1);

	DMMessage::Ref().IssueMessge(DEMURA_MOTOR_MODULE, tCloseMessage);
}

void JcDemuraEDC::Slot_pbMotorStop_click()
{
	JcDemuraMessage tStopMessage;
	tStopMessage.m_nMessageId = MOTOR_EMGSTOP;
	tStopMessage.m_nChannelId = 1 << (m_nChannelIndex - 1);

	DMMessage::Ref().IssueMessge(DEMURA_MOTOR_MODULE, tStopMessage);
}

void JcDemuraEDC::Slot_pbMotorPosMove_click()
{
	JcDemuraMessage tPosMoveMessage;
	tPosMoveMessage.m_nMessageId = MOTOR_MOVE;
	tPosMoveMessage.m_nChannelId = 1 << (m_nChannelIndex - 1);

	MotorInData* pInData = new MotorInData();
	pInData->m_nAxis = 0;
	pInData->m_nCurVel = m_JcEDCFormUI.leMotorCurvel->text().toInt();
	pInData->m_nMaxVel = m_JcEDCFormUI.leMotorMaxvel->text().toInt();
	pInData->m_nPos = m_JcEDCFormUI.leMotorPos->text().toDouble();
	pInData->m_nDir = 1;

	tPosMoveMessage.m_pDemuraBaseData = pInData;

	DMMessage::Ref().IssueMessge(DEMURA_MOTOR_MODULE, tPosMoveMessage);
}

void JcDemuraEDC::Slot_pbMotorNegMove_click()
{
	JcDemuraMessage tNegMoveMessage;
	tNegMoveMessage.m_nMessageId = MOTOR_MOVE;
	tNegMoveMessage.m_nChannelId = 1 << (m_nChannelIndex - 1);

	MotorInData* pInData = new MotorInData();
	pInData->m_nAxis = 0;
	pInData->m_nCurVel = m_JcEDCFormUI.leMotorCurvel->text().toInt();
	pInData->m_nMaxVel = m_JcEDCFormUI.leMotorMaxvel->text().toInt();
	pInData->m_nPos = m_JcEDCFormUI.leMotorPos->text().toDouble();
	pInData->m_nDir = -1;

	tNegMoveMessage.m_pDemuraBaseData = pInData;

	DMMessage::Ref().IssueMessge(DEMURA_MOTOR_MODULE, tNegMoveMessage);
}

#if 0
class MotorInData :public JcDemuraBaseData
{
public:
	MotorInData() {};
	~MotorInData() {};
	int m_nAxis;
	int m_nCurVel;
	int m_nMaxVel;
	double m_nPos;
	int m_nDir;
};

void JcDemuraEDC::PlcInit()
{
	JcDemuraMessage tMessage;
	tMessage.m_nChannelId = 1;
	tMessage.m_nMessageId = PLC_INIT;
	DMMessage::Ref().IssueMessge(DEMURA_PLC_MODULE, tMessage);

#if 0
	TEST_BIT(index, id) (0 != ((id) & (0x01 << (index - 1))))

		if (!TEST_BIT(m_nChannelIndex, tMessage.m_nChannelId))
		{
			return;
		}
	JcDemuraMessage tRecvMessage;
	tRecvMessage.m_nMessageId = MOTOR_CLOSE;
	tRecvMessage.m_nChannelId = 1 << (m_nChannelIndex - 1);

	int nAxis = 0;
	if (EMGStop(nAxis))
	{
		tRecvMessage.m_nResult = ALL_SUCCESS;
	}
	else
	{
		tRecvMessage.m_nResult = MOTOR_ERROR_EMGSTOP;
	}
	DMMessage::Ref().IssueMessge(DEMURA_GUI_MODULE, tRecvMessage);
#endif
}
#endif

//================================================================================================
/*========================================PLC模组编辑===========================================*/
//================================================================================================

void JcDemuraEDC::Slot_pbPLCWriteMessage()
{
	JcDemuraMessage tMessage;
	tMessage.m_nChannelId = 1;
	tMessage.m_nMessageId = PLC_WRITE;

	PlcInData* pInData = new PlcInData();
	pInData->PlcInPara = 0;
	tMessage.m_pDemuraBaseData = pInData;

	DMMessage::Ref().IssueMessge(DEMURA_PLC_MODULE, tMessage);
}