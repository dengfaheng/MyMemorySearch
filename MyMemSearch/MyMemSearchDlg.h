
// MyMemSearchDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

class CMyMemSearchDlgAutoProxy;


// CMyMemSearchDlg 对话框
class CMyMemSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyMemSearchDlg);
	friend class CMyMemSearchDlgAutoProxy;

// 构造
public:
	CMyMemSearchDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CMyMemSearchDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYMEMSEARCH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CMyMemSearchDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	// 列出所有进程
	CComboBox m_ProcsList;
	afx_msg void OnBnClickedButtonFlash();
	// 进程名称
	CString m_ProcessName;
	// 目标地址列表
	CListCtrl m_CtrAddrList;
	afx_msg void OnBnClickedButtonFindfirst();
	int SearchValue;
	afx_msg void OnHdnItemclickList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemActivateList4(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_addrvalue;
	CEdit m_ctraddrval;
	afx_msg void OnBnClickedFindNext();
	afx_msg void OnBnClickedChange();
	int m_writeval;
};
