// WELCOM_DLG.cpp : implementation file
//

#include "stdafx.h"
#include "gameQuest.h"
#include "WELCOM_DLG.h"
#include "afxdialogex.h"
#include "abstractMap.h"
#include "levelPro.h"
#include "levelNoob.h"
#include <afxtaskdialog.h>


// CWELCOM_DLG dialog
IMPLEMENT_DYNAMIC(CWELCOM_DLG, CDialog)

CWELCOM_DLG::CWELCOM_DLG(CWnd* pParent /*=NULL*/)
	: CDialog(CWELCOM_DLG::IDD, pParent)
{
}

CWELCOM_DLG::~CWELCOM_DLG()
{
}

BOOL CWELCOM_DLG::OnInitDialog()
{
	//set efault difficult
	CButton *radioButton = (CButton *) GetDlgItem(IDC_RADIO_NOOB);
	radioButton->SetCheck(TRUE);

	//set welcome text
	CFont *font = new CFont();

	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 32;
	lf.lfWeight = FW_BOLD;
	lf.lfQuality = ANTIALIASED_QUALITY;
	_tcscpy(lf.lfFaceName, _T( "Ravie"));

	font->CreateFontIndirect(&lf);
	GetDlgItem(IDC_WELCOME_TEXT)->SetFont(font);


	return TRUE;
}

void CWELCOM_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWELCOM_DLG, CDialog)
	ON_BN_CLICKED(IDOK, &CWELCOM_DLG::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWELCOM_DLG::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CWELCOM_DLG::OnBnClickedButton1)
END_MESSAGE_MAP()


// CWELCOM_DLG message handlers

void CWELCOM_DLG::OnBnClickedOk()
{
	CEdit *name = (CEdit *) GetDlgItem(IDC_PLAYER_NAME);
	CString player_name = _T("");

	if ( name->GetWindowTextLengthW() > 0 ) {
		name->GetWindowTextW(player_name);

		
		//Create new player
		this->player.setUser(player_name);

		//Check difficult selection
		CButton *radioButton = (CButton *) GetDlgItem(IDC_RADIO_NOOB);
		
		if( radioButton->GetCheck() ){
			this->player.setDifficult(1);//noob
		}
		else {
			this->player.setDifficult(2);//pro
		}

		switch( this->player.getDifficult() ){
		case 1:
			this->game = new levelNoob(7,30); 
			break;
		case 2:
			this->game = new levelPro(5,10);
			break;
		default:
			this->game = new levelNoob(7,30); 
			break;
		}

		CDialog::OnOK();
	}
	else { //pop-up window

		CString Content(_T("Please enter Player Name"));

		if(CTaskDialog::IsSupported()){
			CString Title(_T("ERROR"));
			CString Heading(_T("Player name empty!"));

			CTaskDialog dia(Content, Heading, Title, TDCBF_RETRY_BUTTON);
			dia.SetMainIcon(TD_WARNING_ICON);
			dia.DoModal();
		}
	}
	
}


void CWELCOM_DLG::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	exit(1);
}


void CWELCOM_DLG::OnBnClickedButton1() // FOR LOADDDD
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CFile file;

	file.Open(L"PlayerInfo.hse",CFile::modeRead);
	CArchive ar(&file,CArchive::load);

	//User player;
	this->player.Serialize(ar);

	//print user name to CEdit controll
	CEdit *name = (CEdit *) GetDlgItem(IDC_PLAYER_NAME);
	name->SetWindowTextW(this->player.getUser());

	if ( this->player.getDifficult() == 2 ){
		CButton *radioButton = (CButton *) GetDlgItem(IDC_RADIO_PRO);
		CButton *radioButton_noob = (CButton *) GetDlgItem(IDC_RADIO_NOOB);

		radioButton_noob->SetCheck(FALSE);
		radioButton->SetCheck(TRUE);
	}

	// Start the mess
	ar.Close();
	file.Close();


	UpdateData(FALSE);
}
