// Connect.cpp: implementation of the CConnect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FiveChess.h"
#include "Connect.h"
#include "FiveChessDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConnect::CConnect()
{

}

CConnect::~CConnect()
{

}

void CConnect::OnAccept( int nErrorCode )//主机建立连接成功响应函数
		{
		CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
		pDlg->Accept();//调用主对话框中的处理函数
		pDlg->SetMenuState(FALSE);
}

void CConnect::OnClose( int nErrorCode )//关闭端口时响应函数
		{
		CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
		
		pDlg->MessageBox( _T("对方已经离开游戏，改日再较量不迟。"), _T("五子棋"), MB_ICONINFORMATION);//弹出提示对话框
		
		pDlg->SetMenuState(TRUE);
		
		pDlg->m_board.SetWait(TRUE);//设置等待状态
		
		pDlg->m_conncet.Close();//关闭监听连接端口
		
		pDlg->m_sock.Close();//关闭连接端口
		
		pDlg->m_bIsConnect = FALSE;//设置连接状态变量
    
}

void CConnect::OnConnect( int nErrorCode )//客户端建立连接成功响应函数
		{
		CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
		pDlg->Connect();//调用主对话框的连接处理函数
		pDlg->SetMenuState(FALSE);    
}

void CConnect::OnReceive( int nErrorCode )//接收响应函数
		{
		
    CBoard *pBoard = (CBoard *)AfxGetMainWnd()->GetDlgItem( IDC_BOARD );
    pBoard->Receive();//调用棋盘类的接收处理函数来处理
}