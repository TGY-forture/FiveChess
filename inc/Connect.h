// Connect.h: interface for the CConnect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONNECT_H__BB1EF917_3FD7_459C_95CB_24878CC6ACEF__INCLUDED_)
#define AFX_CONNECT_H__BB1EF917_3FD7_459C_95CB_24878CC6ACEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConnect : public CAsyncSocket  
{
public:
	CConnect();
	virtual ~CConnect();
protected:
		virtual void OnAccept( int nErrorCode );//�����������ӳɹ���Ӧ����
		virtual void OnConnect( int nErrorCode );//�ͻ��˽������ӳɹ���Ӧ����
		virtual void OnReceive( int nErrorCode );//����������Ӧ����
		virtual void OnClose( int nErrorCode );//�رն˿�ʱ��Ӧ����
};

#endif // !defined(AFX_CONNECT_H__BB1EF917_3FD7_459C_95CB_24878CC6ACEF__INCLUDED_)
