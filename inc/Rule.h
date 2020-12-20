// Rule.h: interface for the CRule class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RULE_H__29AB65EE_9F1B_4E2B_8694_6E9037E7A840__INCLUDED_)
#define AFX_RULE_H__29AB65EE_9F1B_4E2B_8694_6E9037E7A840__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _WIN 0x00
#define _LOST 0x01
#define _OTHER 0x02


class CRule  
{
public:
	CRule();
	virtual ~CRule();
	int Win(int color, int x, int y);//ʤ���жϽӿں���
	BOOL Ban(int x, int y);//�����жϽӿں���
private:
	BOOL forbid2(int x,int y);		//�����ӽ����ж�
	BOOL forbid1(int x, int y);		//���ӽ����ж�

};

#endif // !defined(AFX_RULE_H__29AB65EE_9F1B_4E2B_8694_6E9037E7A840__INCLUDED_)
