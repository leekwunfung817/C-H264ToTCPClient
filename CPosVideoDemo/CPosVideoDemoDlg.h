
// CPosVideoDemoDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include <string>
using namespace std;
using  std::string;


// CCPosVideoDemoDlg dialog
class CCPosVideoDemoDlg : public CDialogEx
{
// Construction
public:
	CCPosVideoDemoDlg(CWnd* pParent = NULL);	// standard constructor


	BOOL InitSDK();
	BOOL ExitSDk();
	void ReConnect(LONG lLoginID, char *pchDVRIP, LONG nDVRPort);
	int ConnectRealPlay(int nIndex, bool bOsd, int nChannel, CString strIP, int nPort, CString strUserName, CString strPassword, int bCloud, HWND hWnd);
	int CameraLogin(CString strIP, int nPort, CString strUserName, CString strPassword, int bCloud);
	void StopRealPlay();
	void Disconnct();
	int CaptureBmpToRam(char *pBuf, int len);
	//char *m_capture_dib_buffer;//ץͼ����
	//int m_capture_dib_buffer_len;//�����ڴ��С
	//int m_capture_dib_len;//ץ����ͼ��ʵ�ʴ�С


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

	char  m_videoCloud;//1��ʾip��ַΪ��id
	HWND  m_videoWnd;//���ھ��


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
	CEdit m_edit_debug;
	DWORD m_dwSenderThreadId; //�����߳�ID
	void CCPosVideoDemoDlg::debug(const std::string& msg);
	void CCPosVideoDemoDlg::sendFrameLoop(LPVOID lpParam);
	static DWORD WINAPI SendFrameThread(LPVOID lpParam);

	CButton m_check_coud_id;
	CStatic m_static_video;
	afx_msg void OnClose();
};
