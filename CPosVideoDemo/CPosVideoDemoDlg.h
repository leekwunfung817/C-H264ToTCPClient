
// CPosVideoDemoDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxmt.h"
#include <string>
using namespace std;
using  std::string;

// CCPosVideoDemoDlg dialog
class CCPosVideoDemoDlg : public CDialogEx
{
// Construction
public:
	CCPosVideoDemoDlg(CWnd* pParent = NULL);	// standard constructor

	//CEdit m_edit_server_url;
	// CEdit m_edit_server_port;

	CEdit m_edit_debug;
	void CCPosVideoDemoDlg::debug(const std::string& msg);

	DWORD m_dwSenderThreadId; //播放线程ID
	afx_msg void SendFrame(LPVOID lpParam);
	static DWORD WINAPI SendFrameThread(LPVOID lpParam);
	void CCPosVideoDemoDlg::sendFrameLoop(CString strUrl, CString strPort, LPVOID lpParam);

	BOOL InitSDK();
	BOOL ExitSDk();
	void ReConnect(LONG lLoginID, char *pchDVRIP, LONG nDVRPort);
	int ConnectRealPlay(int nIndex, bool bOsd, int nChannel, CString strIP, int nPort, CString strUserName, CString strPassword, int bCloud, HWND hWnd);
	int CameraLogin(CString strIP, int nPort, CString strUserName, CString strPassword, int bCloud);
	void StopRealPlay();
	void Disconnct();
	int CaptureBmpToRam(char *pBuf, int len);
	//char *m_capture_dib_buffer;//抓图缓冲
	//int m_capture_dib_buffer_len;//缓冲内存大小
	//int m_capture_dib_len;//抓到的图像实际大小


	int m_videonTotalChannel;
	int m_videoChannel;
	int m_videoIndex;
	int m_iPlayhandle;
	int m_nDecodeHandle;
	int m_LoginID;
	int m_LoginPort;

	int m_bCloudId;
	char m_videoIp[33];	//device IP
	char m_videoCloudId[33];	//device Cloud id
	char  m_videoUserName[33];		//user name
	char  m_videoPsw[33];			//pass word
	unsigned short  m_videoPort;				//port number

	char  m_videoCloud;//1表示ip地址为云id
	HWND  m_videoWnd;//窗口句柄


// Dialog Data
	enum { IDD = IDD_CPOSVIDEODEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBPreview();
	afx_msg void OnBnClickedBFrame();
	
	CEdit m_edit_url;

	CEdit m_edit_pyIP;
	CEdit m_edit_pyPort;

	CButton m_check_coud_id;
	CStatic m_static_video;
	afx_msg void OnClose();
};
