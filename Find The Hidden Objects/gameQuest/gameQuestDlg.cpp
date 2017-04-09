// gameQuestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gameQuest.h"
#include "gameQuestDlg.h"
#include "user.h"
#include "afxdialogex.h"
#include "WELCOM_DLG.h"
#include "abstractMap.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//Global
Map *MGame;
int total_count;

//Message Box
int DisplayResourceNAMessageBox(CString msg1, CString title)
{	
	//CWELCOM_DLG Dlg;
    int msgboxID = MessageBox(
        NULL,
        (LPCWSTR)msg1,
        (LPCWSTR)title,
        MB_ICONWARNING | MB_OK | MB_DEFBUTTON1 | MB_TASKMODAL
    );

    switch (msgboxID)
    {
    case IDCANCEL:
        // TODO: add code
        break;
	case IDOK:
        // TODO: add code
		exit(1);
    }

    return msgboxID;
}

void checkCount(){
	if(total_count >= 5) {
		CString msg = L":) YOU WON  Dr. Nodelman";
		CString title = L"CONGRATULATIONS !!!";
		DisplayResourceNAMessageBox(msg,title);
	};
}
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CgameQuestDlg dialogs

CgameQuestDlg::CgameQuestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CgameQuestDlg::IDD, pParent)
	, clicks_left(0)
	, Timer(45)
	, found(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgameQuestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAP, m_mapContainer);
	DDX_Control(pDX, IDC_ITEMMAP1, item_1);
	DDX_Control(pDX, IDC_ITEMMAP2, item_2);
	DDX_Control(pDX, IDC_ITEMMAP3, item_3);
	DDX_Control(pDX, IDC_ITEMMAP4, item_4);
	DDX_Control(pDX, IDC_ITEMMAP5, item_5);
	DDX_Text(pDX, IDC_TIMER, Timer);
	DDX_Text(pDX, IDC_ITEMS_FOUND, found);
}

BEGIN_MESSAGE_MAP(CgameQuestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_HINT_1, &CgameQuestDlg::OnBnClickedHint1)
	ON_BN_CLICKED(IDC_HINT_3, &CgameQuestDlg::OnBnClickedHint3)
	ON_BN_CLICKED(IDC_HINT_4, &CgameQuestDlg::OnBnClickedHint4)
	ON_BN_CLICKED(IDC_HINT_5, &CgameQuestDlg::OnBnClickedHint5)
	ON_BN_CLICKED(IDC_HINT_2, &CgameQuestDlg::OnBnClickedHint2)
	ON_STN_CLICKED(IDC_MAP, &CgameQuestDlg::OnStnClickedMap)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON5, &CgameQuestDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CgameQuestDlg message handlers

BOOL CgameQuestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here



	//welcome dialog - initialize game class
	CWELCOM_DLG Dlg;
	Dlg.DoModal();

	MGame = Dlg.game;
	MPlayer = new User();
	MPlayer->setUser(Dlg.player.getUser());
	MPlayer->setDifficult(Dlg.player.getDifficult());
	MPlayer->setItemFound(Dlg.player.getItemFound());

	//init name placeholder at the top of the Game:
	CStatic *user_name = (CStatic *) GetDlgItem(IDC_USERNAME);
	user_name->SetWindowTextW(MPlayer->getUser());

	//initialize images
	m_mapContainer.SetBitmap(*MGame->getMap());
	
	item_1.SetBitmap(*MGame->get_single_thumb(0));
	item_2.SetBitmap(*MGame->get_single_thumb(1));
	item_3.SetBitmap(*MGame->get_single_thumb(2));
	item_4.SetBitmap(*MGame->get_single_thumb(3));
	item_5.SetBitmap(*MGame->get_single_thumb(4));

	//poition hit buttons
	CStatic* hint_1 = (CStatic*)GetDlgItem(IDC_HINT_1); 
	CStatic* hint_2 = (CStatic*)GetDlgItem(IDC_HINT_2); 
	CStatic* hint_3 = (CStatic*)GetDlgItem(IDC_HINT_3); 
	CStatic* hint_4 = (CStatic*)GetDlgItem(IDC_HINT_4); 
	CStatic* hint_5 = (CStatic*)GetDlgItem(IDC_HINT_5); 

	//noob positions
	if( MPlayer->getDifficult() == 1 ){
		hint_1->SetWindowPos(NULL, 370, 290, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
		hint_2->SetWindowPos(NULL, 515, 215, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
		hint_3->SetWindowPos(NULL, 215, 310, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
		hint_4->SetWindowPos(NULL, 300, 245, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
		hint_5->SetWindowPos(NULL, 470, 275, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
	}
	//pro positions
	else {
		hint_1->SetWindowPos(NULL, 650, 115, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
		hint_2->SetWindowPos(NULL, 655, 200, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
		hint_3->SetWindowPos(NULL, 275, 225, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
		hint_4->SetWindowPos(NULL, 660, 240, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
		hint_5->SetWindowPos(NULL, 450, 385, 0, 0, SWP_NOZORDER|SWP_NOSIZE);
	}
	
	//loaded progress
	if( MPlayer->getItemFound() > 0 ){
		int num = MPlayer->getItemFound();
		int temp;
		while( num != 0 ){
			temp = num%10;
			num /= 10;
			switch(temp){
				case 1:
					item_1.ShowWindow(FALSE);
					break;
				case 2:
					item_2.ShowWindow(FALSE);
					break;
				case 3:
					item_3.ShowWindow(FALSE);
					break;
				case 4:
					item_4.ShowWindow(FALSE);
					break;
				case 5:
					item_5.ShowWindow(FALSE);
					break;
			}
			total_count++;
		}
		
	}

	//set clicks left text
	this->clicks_left = MGame->getClicks();
	//set time left text


	SetTimer(1,1000,NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CgameQuestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CgameQuestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CgameQuestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CgameQuestDlg::OnBnClickedHint1()
{

	found++;
	MPlayer->setItemFound( MPlayer->getItemFound() * 10 + 1 );

	total_count++;
	item_1.ShowWindow(FALSE);
	checkCount();
	// TODO: Add your control notification handler code here
}

void CgameQuestDlg::OnBnClickedHint2()
{
	found++;
	MPlayer->setItemFound( MPlayer->getItemFound() * 10 + 2 );

	total_count++;
	item_2.ShowWindow(FALSE);
	checkCount();
	// TODO: Add your control notification handler code here
}


void CgameQuestDlg::OnBnClickedHint3()
{
	found++;
	MPlayer->setItemFound( MPlayer->getItemFound() * 10 + 3 );

	total_count++;
	item_3.ShowWindow(FALSE);
	checkCount();
	// TODO: Add your control notification handler code here
}


void CgameQuestDlg::OnBnClickedHint4()
{
	found++;
	MPlayer->setItemFound( MPlayer->getItemFound() * 10 + 4 );

	total_count++;
	item_4.ShowWindow(FALSE);
	checkCount();
	// TODO: Add your control notification handler code here
}


void CgameQuestDlg::OnBnClickedHint5()
{
	found++;
	MPlayer->setItemFound( MPlayer->getItemFound() * 10 + 5 );

	total_count++;
	item_5.ShowWindow(FALSE);
	checkCount();
	
	// TODO: Add your control notification handler code here
}


void CgameQuestDlg::OnStnClickedMap()
{
	// TODO: Add your control notification handler code here
}


void CgameQuestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE);
	
	Timer--;
	
	if(Timer == 0) {
		KillTimer(nIDEvent);
		MessageBeep(0xFFFFFFFF);
		UpdateData(FALSE);

		CString msg = L":( YOU LOSE   Dr. Nodelman";
		CString title = L"GAME OVER !!!";
		DisplayResourceNAMessageBox(msg,title);
	}
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


void CgameQuestDlg::OnBnClickedButton5() // FOR SAVE BUTTON !!!
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	User player;
	CString user_name = MPlayer->getUser();
	CFile file;
	file.Open(L"PlayerInfo.hse",CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file,CArchive::store);
	player.setUser(MPlayer->getUser());
	player.setClicks(MPlayer->getClicks());
	player.setDifficult(MPlayer->getDifficult());
	player.setItemFound(MPlayer->getItemFound());

	player.Serialize(ar);
	ar.Close();
}
