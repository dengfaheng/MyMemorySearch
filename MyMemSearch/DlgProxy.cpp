
// DlgProxy.cpp : 实现文件
//

#include "stdafx.h"
#include "MyMemSearch.h"
#include "DlgProxy.h"
#include "MyMemSearchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyMemSearchDlgAutoProxy

IMPLEMENT_DYNCREATE(CMyMemSearchDlgAutoProxy, CCmdTarget)

CMyMemSearchDlgAutoProxy::CMyMemSearchDlgAutoProxy()
{
	EnableAutomation();
	
	// 为使应用程序在自动化对象处于活动状态时一直保持 
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。  设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CMyMemSearchDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMyMemSearchDlg)))
		{
			m_pDialog = reinterpret_cast<CMyMemSearchDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CMyMemSearchDlgAutoProxy::~CMyMemSearchDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CMyMemSearchDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMyMemSearchDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMyMemSearchDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IMyMemSearch 的支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {C3DC7F87-C104-4D90-9B0F-4E5C18476527}
static const IID IID_IMyMemSearch =
{ 0xC3DC7F87, 0xC104, 0x4D90, { 0x9B, 0xF, 0x4E, 0x5C, 0x18, 0x47, 0x65, 0x27 } };

BEGIN_INTERFACE_MAP(CMyMemSearchDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMyMemSearchDlgAutoProxy, IID_IMyMemSearch, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {0449ED02-8B9D-4AF9-A3C5-689786FC7AA3}
IMPLEMENT_OLECREATE2(CMyMemSearchDlgAutoProxy, "MyMemSearch.Application", 0x449ed02, 0x8b9d, 0x4af9, 0xa3, 0xc5, 0x68, 0x97, 0x86, 0xfc, 0x7a, 0xa3)


// CMyMemSearchDlgAutoProxy 消息处理程序
