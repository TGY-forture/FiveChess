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
		virtual void OnAccept( int nErrorCode );//主机建立连接成功响应函数
		virtual void OnConnect( int nErrorCode );//客户端建立连接成功响应函数
		virtual void OnReceive( int nErrorCode );//接收数据响应函数
		virtual void OnClose( int nErrorCode );//关闭端口时响应函数
};

#endif // !defined(AFX_CONNECT_H__BB1EF917_3FD7_459C_95CB_24878CC6ACEF__INCLUDED_)
