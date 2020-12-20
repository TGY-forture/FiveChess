// FiveChessDlg.h : header file
//

#if !defined(AFX_FIVECHESSDLG_H__701CFC4E_0440_4DFB_A079_586D3F3C811C__INCLUDED_)
#define AFX_FIVECHESSDLG_H__701CFC4E_0440_4DFB_A079_586D3F3C811C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFiveChessDlg dialog

#include "SetupDlg.h"
#include "Connect.h"
//#include "ConnectData.h"
#include "Board.h"

#define MSG_PUTSTEP 0x01
#define MSG_DRAW 0x02
#define MSG_AGREE_DRAW 0x03
#define MSG_REFUSE_DRAW 0x04
#define MSG_EXTERN 0x05

typedef struct _tagMsgStruct {
    USHORT len;
		// ��ϢID
    BYTE msgType;
    // ������Ϣ
    int x;
    int y;
    int color;
    // ������Ϣ����
    BYTE byMsg[128];
} MSGSTRUCT;

class CFiveChessDlg : public CDialog
{
// Construction
public:
	void NewGameStart(BOOL isHost);
	void SetMenuState(BOOL bEnable);		//���ò˵�״̬
	void Accept();							//�������˿��������ӳɹ�ʱ����
	void Connect();							//�ͻ����������ӳɹ�����
	void Send(MSGSTRUCT * pmsg);			//��������
	void Restart();							//���¿�ʼ��Ϸ
	CFiveChessDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFiveChessDlg)
	enum { IDD = IDD_FIVECHESS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFiveChessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
			CConnect m_conncet;			//�����׽���
			CConnect m_sock;			//ʹ���׽���
			BOOL     m_bIsConnect;		//���ӱ�־
			CBoard	 m_board;
protected:
	
	HICON m_hIcon;
	CMenu m_main_menu;			//���˵�����
	CSetupDlg m_setup_dlg;		//���öԻ������


	// Generated message map functions
	//{{AFX_MSG(CFiveChessDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDrawGameMenu();
	afx_msg void OnExitGameMenu();
	afx_msg void OnNewGameMenu();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIVECHESSDLG_H__701CFC4E_0440_4DFB_A079_586D3F3C811C__INCLUDED_)
