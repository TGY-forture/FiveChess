#if !defined(AFX_SETUPDLG_H__E6907958_EA69_45FE_91E9_8CE3169E0662__INCLUDED_)
#define AFX_SETUPDLG_H__E6907958_EA69_45FE_91E9_8CE3169E0662__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog

class CSetupDlg : public CDialog
{
// Construction
public:
	CSetupDlg(CWnd* pParent = NULL);   // standard constructor
public:
	BOOL m_isHost; //主机类型，TRUE: 主机FALSE:客户机
	CString m_strHostIP;//IP 地址
// Dialog Data
	//{{AFX_DATA(CSetupDlg)
	enum { IDD = IDD_SETUP_DLG };
	CIPAddressCtrl	m_ip_addr;
	UINT	m_net_port;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetupDlg)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnHostOption();
	afx_msg void OnClientOption();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPDLG_H__E6907958_EA69_45FE_91E9_8CE3169E0662__INCLUDED_)
