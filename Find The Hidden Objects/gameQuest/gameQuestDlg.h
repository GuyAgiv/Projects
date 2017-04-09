
// gameQuestDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "resource.h"
#include "user.h"

// CgameQuestDlg dialog
class CgameQuestDlg : public CDialogEx
{

// Construction
public:
	CgameQuestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_GAMEQUEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	User *MPlayer;
	CEdit m_inputName;
	CStatic m_mapContainer;
	CStatic item_1;
	CStatic item_2;
	CStatic item_3;
	CStatic item_4;
	CStatic item_5;
	afx_msg void OnBnClickedHint0();
	afx_msg void OnBnClickedHint1();
	afx_msg void OnBnClickedHint3();
	afx_msg void OnBnClickedHint4();
	afx_msg void OnBnClickedHint5();
	afx_msg void OnBnClickedHint2();
	afx_msg void OnStnClickedMap();
	int clicks_left;
	int Timer;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton5();
	int found;
};
