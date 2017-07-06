
// ASRServerDlg.h : 头文件
//

#pragma once

#include "Config.h"
#include "BaseSocket.h"
#include "Log.h"
#include "ClientList.h"
#include "ClientASRDataReq.h"
#include "ClientASRDataReqList.h"
#include "ASRThreadData.h"
#include <list>
#include "afxcmn.h"
#include "afxwin.h"


// CASRServerDlg 对话框
class CASRServerDlg : public CDialog
{
// 构造
public:
	CASRServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ASRSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//配置属性
	Config * pConfig;
	//服务端SOCKET
	CBaseSocket ServerSocket;
	//日志类
	Log m_WriteLog;
	//客户端列表
	ClientList clientList;
	ClientASRDataReqList clientReqList;
	list<ASRThreadData *> asrThreadList;
public:
	//侦听服务器
	BOOL OnListen();
	//ASRServer Socket 消息处理
	LONG OnASRServerSocketMsg(UINT wParam, long lParam);
	//客户端连接
	void Accept();
	//客户端断开连接
	void ClientDisConnect(SOCKET clientSocket);
	//关闭SOCKET，清除SOCKET资源
	void ClientClose(Client * pClient);
	//接收到数据
	void ReadData(SOCKET  clientSocket);
	//处理接收到的数据
	void ProcData(Client * pClient,char * szBuffer);
	//向客户端发送数据
	void SendData(SOCKET clientSocket,const char * szBuffer,int nSize);
	//分割数据
	void SplitData(int m,char* pmsg,CString ip);
	//写日志及在界面显示日志
	void Log(Log::LogLevel level,CString log);
	static unsigned __stdcall ASRThread(void *info);
	virtual void OnOK();
public:
	CTreeCtrl mTreeClient;
	CString listenPort;
	CListBox mListMessage;
	CButton bt_Exit;
	CString m_Message;
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonDisclient();
	afx_msg void OnLbnDblclkListMessage();
};
