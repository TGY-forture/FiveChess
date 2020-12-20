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

void CConnect::OnAccept( int nErrorCode )//�����������ӳɹ���Ӧ����
		{
		CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
		pDlg->Accept();//�������Ի����еĴ�����
		pDlg->SetMenuState(FALSE);
}

void CConnect::OnClose( int nErrorCode )//�رն˿�ʱ��Ӧ����
		{
		CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
		
		pDlg->MessageBox( _T("�Է��Ѿ��뿪��Ϸ�������ٽ������١�"), _T("������"), MB_ICONINFORMATION);//������ʾ�Ի���
		
		pDlg->SetMenuState(TRUE);
		
		pDlg->m_board.SetWait(TRUE);//���õȴ�״̬
		
		pDlg->m_conncet.Close();//�رռ������Ӷ˿�
		
		pDlg->m_sock.Close();//�ر����Ӷ˿�
		
		pDlg->m_bIsConnect = FALSE;//��������״̬����
    
}

void CConnect::OnConnect( int nErrorCode )//�ͻ��˽������ӳɹ���Ӧ����
		{
		CFiveChessDlg * pDlg = (CFiveChessDlg*)AfxGetMainWnd();
		pDlg->Connect();//�������Ի�������Ӵ�����
		pDlg->SetMenuState(FALSE);    
}

void CConnect::OnReceive( int nErrorCode )//������Ӧ����
		{
		
    CBoard *pBoard = (CBoard *)AfxGetMainWnd()->GetDlgItem( IDC_BOARD );
    pBoard->Receive();//����������Ľ��մ�����������
}