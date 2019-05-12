
// MyMemSearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyMemSearch.h"
#include "MyMemSearchDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include <windows.h>
#include<TlHelp32.h>
#include <process.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL CompareAPage(DWORD dwBaseAddr, DWORD dwValue);  //匹配对应的值
BOOL FindFirst(DWORD dwValue);	//目标进程空间进行第一次查找
BOOL FindNext(DWORD dwValue);	//在目标进程地址空间第2、3、4 ...次查找

DWORD GetProcessID(char* FileName);

DWORD g_addrList[10240];			//地址列表
int g_nListCnt;					//有效地址的个数
HANDLE g_hProcess;				//目标进程句柄



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyMemSearchDlg 对话框


IMPLEMENT_DYNAMIC(CMyMemSearchDlg, CDialogEx);

CMyMemSearchDlg::CMyMemSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYMEMSEARCH_DIALOG, pParent)
	, m_ProcessName(_T(""))
	, SearchValue(0)
	, m_addrvalue(_T(""))
	, m_writeval(0)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CMyMemSearchDlg::~CMyMemSearchDlg()
{
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CMyMemSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PROCESS_LIST, m_ProcsList);
	DDX_CBString(pDX, IDC_COMBO_PROCESS_LIST, m_ProcessName);
	DDX_Control(pDX, IDC_LIST4, m_CtrAddrList);
	DDX_Text(pDX, IDC_EDIT_Value, SearchValue);
	DDX_Text(pDX, IDC_EDIT2, m_addrvalue);
	DDX_Control(pDX, IDC_EDIT2, m_ctraddrval);
	DDX_Text(pDX, IDC_EDIT3, m_writeval);
}

BEGIN_MESSAGE_MAP(CMyMemSearchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FLASH, &CMyMemSearchDlg::OnBnClickedButtonFlash)
	ON_BN_CLICKED(IDC_BUTTON_FINDFIRST, &CMyMemSearchDlg::OnBnClickedButtonFindfirst)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CMyMemSearchDlg::OnHdnItemclickList4)
	ON_NOTIFY(NM_CLICK, IDC_LIST4, &CMyMemSearchDlg::OnNMClickList4)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST4, &CMyMemSearchDlg::OnLvnItemActivateList4)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyMemSearchDlg::OnBnClickedFindNext)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyMemSearchDlg::OnBnClickedChange)
END_MESSAGE_MAP()


// CMyMemSearchDlg 消息处理程序

BOOL CMyMemSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	
	PROCESSENTRY32 pe32 = { 0 };//进程快照信息

	pe32.dwSize = sizeof(pe32);//设置机构体大小

	HANDLE hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//创建快照

	BOOL  bmore = Process32First(hprocess, &pe32);//寻找,通过指针改变外部变量
	while (bmore)
	{
		m_ProcsList.AddString(pe32.szExeFile);

		bmore = Process32Next(hprocess, &pe32);
	}


	DWORD dwStyle = m_CtrAddrList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ）   
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ）   
								//dwStyle |= LVS_EX_CHECKBOXES;//item 前生成checkbox 控件   
	m_CtrAddrList.SetExtendedStyle(dwStyle); // 设置扩展风格   
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ）  

	m_CtrAddrList.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);  //设置列表控件的报表显示方式  							
	m_CtrAddrList.SetExtendedStyle(LVS_EX_GRIDLINES);  //设置列表控件显示网格线  
									
	//m_CtrAddrList.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 50);//在列表控件中插入列  
	m_CtrAddrList.InsertColumn(0, _T("双击以选择"), LVCFMT_LEFT, 200);





	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyMemSearchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyMemSearchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyMemSearchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。  这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void CMyMemSearchDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CMyMemSearchDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CMyMemSearchDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CMyMemSearchDlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。

	::CloseHandle(g_hProcess);
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CMyMemSearchDlg::OnBnClickedButtonFlash()//刷新进程列表
{
	int i;
	for (i = m_ProcsList.GetCount() - 1; i >= 0;i--)
	{
		m_ProcsList.DeleteString(i);
	}

	PROCESSENTRY32 pe32 = { 0 };//进程快照信息

	pe32.dwSize = sizeof(pe32);//设置机构体大小

	HANDLE hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//创建快照

	BOOL  bmore = Process32First(hprocess, &pe32);//寻找,通过指针改变外部变量
	while (bmore)
	{
		m_ProcsList.AddString(pe32.szExeFile);

		bmore = Process32Next(hprocess, &pe32);
	}

	// TODO: 在此添加控件通知处理程序代码
}



BOOL CompareAPage(DWORD dwBaseAddr, DWORD dwValue)
{
	BYTE arBytes[4096];
	if (!::ReadProcessMemory(g_hProcess, (LPVOID)dwBaseAddr, arBytes, 4096, NULL))
	{
		return false;
	}
	DWORD * pdw;
	for (int i = 0; i < (int)4 * 1024 - 3; i++)
	{
		pdw = (DWORD*)&arBytes[i];
		if (pdw[0] == dwValue)//等于要查找的值
		{
			if (g_nListCnt >= 10240)
			{
				return FALSE;
			}
			else
			{
				g_addrList[g_nListCnt++] = dwBaseAddr + i;
			}
		}
	}



	return true;
}
BOOL FindFirst(DWORD dwVal)
{
	const DWORD dwOneGB = 1024 * 1024 * 1024;
	const DWORD dwOnePage = 4 * 1024;
	if (g_hProcess == NULL)
	{
		//return FALSE;
	}
	//查看操作系统类型,以决定开始地址
	DWORD dwBase;
	OSVERSIONINFO vi = { sizeof(vi)
	};
	::GetVersionEx(&vi);
	if (vi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
	{
		dwBase = 4 * 1024 * 1024;//windows98系列,4mb
	}
	else
	{
		dwBase = 640 * 1024;//windowsNT系列,64kb
	}
	//在开始地址到2GB的地址空间进行查找
	for (; dwBase < 2 * dwOneGB; dwBase += dwOnePage)
	{
		CompareAPage(dwBase, dwVal);
	}
	return TRUE;
}

BOOL FindNext(DWORD dwValue)
{
	//保存m_addrList数组中有效地址的个数,初始化新的m_nListCnt值
	int nOrgCnt = g_nListCnt;
	g_nListCnt = 0;

	//在m_addrList数组记录的地址处查找
	BOOL bRet = FALSE;//假设失败
	DWORD dwReadValue;
	for (int i = 0; i < nOrgCnt; i++)
	{
		if (::ReadProcessMemory(g_hProcess, (LPVOID)g_addrList[i], &dwReadValue, sizeof(DWORD), NULL))
		{
			//AfxMessageBox("lll");
			if (dwValue == dwReadValue)
			{
				//AfxMessageBox("www");
				g_addrList[g_nListCnt++] = g_addrList[i];
				bRet = TRUE;
			}
		}
	}
	return bRet;
}
BOOL WriteMemory(DWORD dwAddr, DWORD dwValue)
{
	return ::WriteProcessMemory(g_hProcess, (LPVOID)dwAddr, &dwValue, sizeof(DWORD), NULL);
}

void CMyMemSearchDlg::OnBnClickedButtonFindfirst()
{

	m_CtrAddrList.SetExtendedStyle(m_CtrAddrList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	DWORD proID;
	UpdateData(TRUE); 
	char *exename = m_ProcessName.GetBuffer();
	proID = GetProcessID(exename);
	g_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, proID);

	FindFirst(SearchValue);
	

	m_CtrAddrList.DeleteAllItems();
	CString addr;


	for (int i = 0; i < g_nListCnt; i++)
	{
		addr.Format("0x%p", g_addrList[i]);

		m_CtrAddrList.InsertItem(i, addr);
	}

	// TODO: 在此添加控件通知处理程序代码
}


DWORD GetProcessID(char *FileName)
{
	HANDLE myhProcess;
	PROCESSENTRY32 mype;
	mype.dwSize = sizeof(PROCESSENTRY32);
	BOOL mybRet;
	//进行进程快照
	myhProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //TH32CS_SNAPPROCESS快照所有进程
																  //开始进程查找
	mybRet = Process32First(myhProcess, &mype);
	//循环比较，得出ProcessID
	while (mybRet)
	{
		if (strcmp(FileName, mype.szExeFile) == 0)
			return mype.th32ProcessID;
		else
			mybRet = Process32Next(myhProcess, &mype);
	}
	return 0;
}

void CMyMemSearchDlg::OnHdnItemclickList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//AfxMessageBox("www");

	*pResult = 0;
}


void CMyMemSearchDlg::OnNMClickList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//AfxMessageBox("www");
	*pResult = 0;
}


void CMyMemSearchDlg::OnLvnItemActivateList4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码


	CString str;
	int nId;
	//首先得到点击的位置
	POSITION pos = m_CtrAddrList.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox("请至少选择一项", "提示", MB_ICONEXCLAMATION);
		return;
	}
	//得到行号，通过POSITION转化
	nId = (int)m_CtrAddrList.GetNextSelectedItem(pos);
	str = m_CtrAddrList.GetItemText(nId, 0);
	m_ctraddrval.SetWindowText(str);

	*pResult = 0;
}


void CMyMemSearchDlg::OnBnClickedFindNext()
{
	UpdateData(TRUE);

	FindNext(SearchValue);
	m_CtrAddrList.DeleteAllItems();
	CString addr;


	for (int i = 0; i < g_nListCnt; i++)
	{
		addr.Format("0x%p", g_addrList[i]);

		m_CtrAddrList.InsertItem(i, addr);
	}

	// TODO: 在此添加控件通知处理程序代码
}


void CMyMemSearchDlg::OnBnClickedChange()
{
	UpdateData(TRUE);
	if (WriteMemory(g_addrList[0], m_writeval))
	{
		AfxMessageBox("修改内存值成功！");
	}


	// TODO: 在此添加控件通知处理程序代码
}
