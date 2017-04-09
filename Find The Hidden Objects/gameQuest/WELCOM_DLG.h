#pragma once
#include "user.h"
#include "abstractMap.h"
#include "afxwin.h"

// CWELCOM_DLG dialog

class CWELCOM_DLG : public CDialog
{
	DECLARE_DYNAMIC(CWELCOM_DLG)

// Dialog Data
	enum { IDD = IDD_WELCOME };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CWELCOM_DLG(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWELCOM_DLG();

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	User player;
	Map *game;
	CButton m_radio_noob;
	afx_msg void OnBnClickedButton1();
};
