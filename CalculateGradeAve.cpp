
// CalculateGradeAve.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "CalculateGradeAve.h"
#include "CalculateGradeAveDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCalculateGradeAveApp

BEGIN_MESSAGE_MAP(CCalculateGradeAveApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCalculateGradeAveApp 생성

CCalculateGradeAveApp::CCalculateGradeAveApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CCalculateGradeAveApp 개체입니다.

CCalculateGradeAveApp theApp;


// CCalculateGradeAveApp 초기화

BOOL CCalculateGradeAveApp::InitInstance()
{
	CWinApp::InitInstance();

	CCalculateGradeAveDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	
	return FALSE;
}

