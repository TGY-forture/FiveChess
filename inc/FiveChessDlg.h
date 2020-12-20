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
		// 消息ID
    BYTE msgType;
    // 落子信息
    int x;
    int y;
    int color;
    // 其他消息内容
    BYTE byMsg[128];
} MSGSTRUCT;

class CFiveChessDlg : public CDialog
{
// Construction
public:
	void NewGameStart(BOOL isHost);
	void SetMenuState(BOOL bEnable);		//设置菜单状态
	void Accept();							//服务器端口申请连接成功时调用
	void Connect();							//客户机申请连接成功调用
	void Send(MSGSTRUCT * pmsg);			//发送数据
	void Restart();							//重新开始游戏
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
			CConnect m_conncet;			//监听套接字
			CConnect m_sock;			//使用套接字
			BOOL     m_bIsConnect;		//连接标志
			CBoard	 m_board;
protected:
	
	HICON m_hIcon;
	CMenu m_main_menu;			//主菜单对象
	CSetupDlg m_setup_dlg;		//设置对话框对象


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
