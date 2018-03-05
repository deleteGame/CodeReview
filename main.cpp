#include"stdafx.h"
#include "DemuraEDC.h"
#include <QtWidgets/QApplication>
#include <Windows.h>

bool CheckOnly()
{
	//����������
	HANDLE m_hMutex;
	m_hMutex = CreateMutex(NULL, FALSE, L"DemuraEDC");

	//���������
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		//������л������������ͷž������λ������
		CloseHandle(m_hMutex);
		m_hMutex = NULL;
		//�����˳�
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
