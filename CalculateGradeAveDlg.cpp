
// CalculateGradeAveDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CalculateGradeAve.h"
#include "CalculateGradeAveDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCalculateGradeAveDlg 대화 상자



CCalculateGradeAveDlg::CCalculateGradeAveDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATEGRADEAVE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculateGradeAveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCalculateGradeAveDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CAL_GRADE_BTN, &CCalculateGradeAveDlg::OnBnClickedCalGradeBtn)
	ON_BN_CLICKED(IDC_RESET_BTN, &CCalculateGradeAveDlg::OnBnClickedResetBtn)
END_MESSAGE_MAP()


// CCalculateGradeAveDlg 메시지 처리기

BOOL CCalculateGradeAveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CComboBox* m_Combo1;
	for (int i = 0; i < 7; i++) {
		m_Combo1 = (CComboBox*)GetDlgItem(IDC_COMBO1 + i);

		m_Combo1->AddString(L"A+");
		m_Combo1->AddString(L"A0");
		m_Combo1->AddString(L"A-");
		m_Combo1->AddString(L"B+");
		m_Combo1->AddString(L"B0");
		m_Combo1->AddString(L"B-");
		m_Combo1->AddString(L"C+");
		m_Combo1->AddString(L"C0");
		m_Combo1->AddString(L"C-");
		m_Combo1->AddString(L"D+");
		m_Combo1->AddString(L"D0");
		m_Combo1->AddString(L"D-");
		m_Combo1->AddString(L"F");
		m_Combo1->AddString(L" ");

		SetDlgItemInt(IDC_EDIT1 + i, 0);
	}
	SetDlgItemInt(IDC_SHOW_AVE_EDIT, 0);
	SetDlgItemInt(IDC_SHOW_TOTAL_EDIT, 0);












	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCalculateGradeAveDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCalculateGradeAveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculateGradeAveDlg::OnBnClickedCalGradeBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CComboBox* m_Combo1;

	int iGetSelect;   //콤보박스 선택 항목 index
	CString sGetSelect;
	int iGetGrade;    //입력된 학점 수
	int iTotalGetGrade = 0;   //총 수강 학점 수
	double dTotalGrade = 0; //총 성적 * 학점 수
	CString sTotalGetGrade;
	
	double dGradeAve = 0; //평균 학점
	CString sGradeAve;

	for (int i = 0; i < 7; i++) {
		m_Combo1 = (CComboBox*)GetDlgItem(IDC_COMBO1 + i);
		iGetSelect = m_Combo1->GetCurSel();                 //선택된 항목의 index 가져오기

		if (iGetSelect != CB_ERR) {                         //1. 학점을 선택한 콤보박스의 경우
			m_Combo1->GetLBText(iGetSelect, sGetSelect);    //index에 해당하는 성적 문자열 가져오기

			if (sGetSelect != L" ") {						//2. 빈칸 말고 성적을 누른 경우 Edit 박스에 입력된 학점 값 가져오기
				iGetGrade = GetDlgItemInt(IDC_EDIT1 + i);  
	
				if(iGetGrade != 0) {                        //3. 입력값이 0이 아니거나 문자가 아닌 경우
					if (0 <= iGetGrade && iGetGrade <= 5) { //4. 입력값이 0 ~ 5인 경우
						switch (iGetSelect) {               //선택한 성적에 따라 총 성적*학점수에 구해서 더하기
						case 0:
							dTotalGrade += 4.3 * iGetGrade;
							break;
						case 1: //A
							dTotalGrade += 4 * iGetGrade;
							break;
						case 2:
							dTotalGrade += 3.7 * iGetGrade;
							break;
						case 3:
							dTotalGrade += 3.3 * iGetGrade;
							break;
						case 4: //B
							dTotalGrade += 3 * iGetGrade;
							break;
						case 5:
							dTotalGrade += 2.7 * iGetGrade;
							break;
						case 6:
							dTotalGrade += 2.3 * iGetGrade;
							break;
						case 7:   //C
							dTotalGrade += 2 * iGetGrade;
							break;
						case 8:
							dTotalGrade += 1.7 * iGetGrade;
							break;
						case 9:
							dTotalGrade += 1.3 * iGetGrade;
							break;
						case 10:   //D
							dTotalGrade += 1 * iGetGrade;
							break;
						case 11:
							dTotalGrade += 0.7 * iGetGrade;
							break;
						case 12:  //F
							dTotalGrade += 0 * iGetGrade;
							break;
						default:
							break;
						}
						iTotalGetGrade += iGetGrade;               //총 수강학점 수에 더하기
						SetDlgItemInt(IDC_EDIT1 + i, iGetGrade);   //내림한 값 띄우기
					}
					else {									       //숫자인데 0 ~ 5를 벗어난 경우
							MessageBox(_T("0에서 5 사이의 정수를 입력하십시오."), _T("학점 계산기"), MB_ICONWARNING);
							SetDlgItemInt(IDC_EDIT1 + i, 0);       //0으로 초기화
							break;
					}
				}
				else {                                          
					CString str;
					GetDlgItemText(IDC_EDIT1 + i, str);
					
					if (str != L"0"){					    //0이거나 문자를 입력한건데 0이 아닌 경우
						MessageBox(_T("정수를 입력하십시오."), _T("학점 계산기"), MB_ICONWARNING);
						SetDlgItemInt(IDC_EDIT1 + i, 0);    //0으로 초기화
						break;
					}
				}
			}
		}


		if (iTotalGetGrade != 0) {							//총 학점 수가 0이 아닌 경우
			dGradeAve = dTotalGrade / iTotalGetGrade;
			sGradeAve.Format(L"%.2f", dGradeAve);
		}
		else {												//총 학점 수가 0인 경우
			dGradeAve = 0;
			sGradeAve.Format(L"0");
		}

		sTotalGetGrade.Format(L"%d", iTotalGetGrade);
		SetDlgItemText(IDC_SHOW_TOTAL_EDIT, sTotalGetGrade);
		SetDlgItemText(IDC_SHOW_AVE_EDIT, sGradeAve);
	}
}


void CCalculateGradeAveDlg::OnBnClickedResetBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CComboBox* m_Combo1;

	for (int i = 0; i < 7; i++) {
		m_Combo1 = (CComboBox*)GetDlgItem(IDC_COMBO1 + i);
		m_Combo1->SetCurSel(13);		 //콤보박스 항목을 빈칸(index 13)으로 두기
		SetDlgItemInt(IDC_EDIT1 + i, 0); //Edit 박스 0으로 초기화
	}
	SetDlgItemInt(IDC_SHOW_TOTAL_EDIT, 0); //평균 표시 0으로 초기화
	SetDlgItemInt(IDC_SHOW_AVE_EDIT, 0);   //이수 학점 표시 0으로 초기화

}

