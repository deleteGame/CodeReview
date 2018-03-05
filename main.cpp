#include"stdafx.h"
#include "DemuraEDC.h"
#include <QtWidgets/QApplication>
#include <Windows.h>

bool CheckOnly()
{
	//创建互斥量
	HANDLE m_hMutex;
	m_hMutex = CreateMutex(NULL, FALSE, L"DemuraEDC");

	//检查错误代码
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		//如果已有互斥量存在则释放句柄并复位互斥量
		CloseHandle(m_hMutex);
		m_hMutex = NULL;
		//程序退出
		return  false;
	}
	else
	{
		return true;
	}
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	if (!CheckOnly())
	{
		return 0;
	}
	DemuraEDC w;
	w.show();
	return a.exec();
}
