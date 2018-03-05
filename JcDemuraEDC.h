#ifndef JcDemuraEDC_H
#define JcDemuraEDC_H

#include <QtWidgets/QMainWindow>
#include <QCoreApplication>
#include <QTableWidgetItem>
#include <QDesktopWidget>
#include "ui_JcDemuEDC.h"
#include "qsystemtrayicon.h"
//#include <QDialog>
#include "JcSystemXmlHandle.h"
#include "JcModuleXMLHandle.h"
#include "zip.h"
#include "unzip.h"
#include "JCMotorDMCThread.h"
#include "JcGuAnPLCCtrl.h"

class JcDemuraEDC : public QMainWindow
{
	Q_OBJECT

public:
	JcDemuraEDC(QWidget *parent = 0);
	~JcDemuraEDC();

public:
	void SignalConnect();
	void MemberInit();
	void PlcInit();
	void TcpSvrSocketInit();
	void InitModuleUI();
	void LoadModuleFile();
	void ChangeModule(QString strModuleName);
	void SetModuleParamsToUI(CameraConfigMap tCameraConfigMap, XmlConfigMap tXmlConfigMap);
	void MotorStateListen();
	void ReceiveMessage(JcDemuraMessage& tMessage);

	static DWORD WINAPI RecvMsgThread(PVOID lpParameter);

private slots:
    void Slot_SaveModule();
    void Slot_DeleteModule();
    void Slot_Import();
    void Slot_Outport();
	void Slot_Apply();
	void Slot_ModuleIndexChange();
	void Slot_pushButtonCopy_click();
	void Slot_pbMini_click();
	void Slot_pbMaxNormal_click();
	void Slot_pbClose_click();
	//void ReceiveMessage(JcDemuraMessage& tMessage);
	void Slot_pbMotorInit_click();
	void Slot_pbMotorHome_click();
	void Slot_pbMotorStop_click();
	void Slot_pbMotorClose_click();
	void Slot_pbMotorPosMove_click();
	void Slot_pbMotorNegMove_click();
	void Slot_pbPLCWriteMessage();


private:
	void RecvServerInit(JcDemuraMessage& tMessage);
	void RecvMotorInitDone(JcDemuraMessage& tMessage);
	void RecvMotorHomeDone(JcDemuraMessage& tMessage);
	void RecvMotorState(JcDemuraMessage& tMessage);

	void RecvPlcRead(JcDemuraMessage& tMessage);

private:
	Ui::JcDemuEDC    m_JcEDCFormUI;
	int		         m_nWindowShowType;
	QString          m_strModuleDirPath;
	QString          m_strCurTestName;
	QString          m_strImageDirPath;
	CameraConfigMap  m_tCameraConfigMap;
	XmlConfigMap     m_tXmlConfigMap;
	int              m_nIndex;
	int				 m_nChannelIndex;
	JCMotorThread    *m_pJcMotor;
	JcQueueThread    *m_pJcQueueThread;
	HANDLE			 m_hRecvMsg;
};

#endif // JcDemuraEDC_H
