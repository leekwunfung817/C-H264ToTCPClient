
// CPosVideoDemoDlg.cpp : implementation file
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
using  std::string;
using  std::wstring;

#include "stdafx.h"
#include "CPosVideoDemo.h"
#include "CPosVideoDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define ONTIMER_UINT UINT
#include "NetSdk.h"
#pragma comment (lib, "NetSdk.lib") 
#include "H264Play.h"
#pragma comment (lib, "H264Play.lib") 

#define DIB_BUFFER_SIZE 10000000 //定义抓取图像的内在大小, 10MB

// CCPosVideoDemoDlg dialog


std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	std::wstring buf;
	buf.resize(len);
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength,
		const_cast<wchar_t*>(buf.c_str()), len);
	return buf;
}


void CCPosVideoDemoDlg::debug(const std::string& msg)
{
	m_edit_debug.SetWindowTextW(s2ws(msg).c_str());
}


CCPosVideoDemoDlg::CCPosVideoDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCPosVideoDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_iPlayhandle = -1;
	m_videoIndex = -1;
	m_nDecodeHandle = -1;


	//m_capture_dib_buffer = NULL;
	//m_capture_dib_len = 0;
	//m_capture_dib_buffer_len = 0;
}

void CCPosVideoDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, EditCtrl_IPCamIPAddress, m_edit_url);
	DDX_Control(pDX, EditCtrl_PyServerIP, m_edit_pyIP);
	DDX_Control(pDX, EditCtrl_PyServerPort, m_edit_pyPort);

	DDX_Control(pDX, EditDebug, m_edit_debug);

	DDX_Control(pDX, IDC_CHECK_CLOUD, m_check_coud_id);
	DDX_Control(pDX, IDC_STATIC_VIDEO, m_static_video);
}

BEGIN_MESSAGE_MAP(CCPosVideoDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_B_PREVIEW, &CCPosVideoDemoDlg::OnBnClickedBPreview)
	ON_BN_CLICKED(IDC_B_FRAME, &CCPosVideoDemoDlg::OnBnClickedBFrame)
	ON_WM_CLOSE()
END_MESSAGE_MAP()




//message callback function
bool __stdcall MessCallBack(long lLoginID, unsigned char *pBuf, unsigned long dwBufLen, long dwUser, int nType, void * pDataInfo)
{
	if (nType == ALARM_TYPE)
	{
		SDK_AlarmInfo alarmInfo;
		memcpy(&alarmInfo, pBuf, dwBufLen);
		//alarm information

	}
	else
	{

	}

	return true;
}

//device disconnect callback
void __stdcall DisConnectBackCallFunc(long lLoginID, char *pchDVRIP, long nDVRPort, unsigned long dwUser)
{

	CCPosVideoDemoDlg* pThis = (CCPosVideoDemoDlg*)dwUser;
	if (pThis == NULL)
	{
		ASSERT(FALSE);
		return;
	}
	pThis->ReConnect(lLoginID, pchDVRIP, nDVRPort);
}

//initialize the SDK
BOOL CCPosVideoDemoDlg::InitSDK()
{
	//initialize
	BOOL bResult = H264_DVR_Init(DisConnectBackCallFunc, (DWORD)this);

	//he messages received in SDK from DVR which need to upload， such as alarm information，diary information，may do through callback function
	H264_DVR_SetDVRMessCallBack(MessCallBack, (DWORD)this);

	H264_DVR_SetConnectTime(1000, 3);

	return bResult;
}

BOOL CCPosVideoDemoDlg::ExitSDk()
{
	H264_DVR_Cleanup();

	return true;
}






// CCPosVideoDemoDlg message handlers

BOOL CCPosVideoDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//m_edit_url.SetWindowTextW(_T("192.168.1.10"));


	int nArgs = 0;

	LPWSTR* szAarglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	CString strArg1(szAarglist[0]);
	CString strArg2(szAarglist[1]);
	CString strArg3(szAarglist[2]);
	CString strArg4(szAarglist[3]);
	CT2CA psz_app(strArg1);
	CT2CA psz_ipv4(strArg2);
	CT2CA psz_port(strArg3);
	CT2CA psz_rtsp_url(strArg4);
	std::string exeName(psz_app);
	std::string py_ip(psz_ipv4);
	std::string py_port(psz_port);
	std::string ipcam_ip(psz_rtsp_url);
	char buff[100];
	sprintf_s(buff, "szAarglist[0]=%s,%s,%s,%s length %d\n", szAarglist[0], szAarglist[1], szAarglist[2], szAarglist[3], nArgs);
	debug(buff);
	m_edit_pyIP.SetWindowTextW(s2ws(py_ip).c_str());
	m_edit_pyPort.SetWindowTextW(s2ws(py_port).c_str());
	m_edit_url.SetWindowTextW(s2ws(ipcam_ip).c_str());
	
	InitSDK();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCPosVideoDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCPosVideoDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCPosVideoDemoDlg::ReConnect(LONG lLoginID, char *pchDVRIP, LONG nDVRPort)
{
	
	
}


void CCPosVideoDemoDlg::sendFrameLoop(LPVOID lpParam)
{
	CCPosVideoDemoDlg* pThis = (CCPosVideoDemoDlg*)lpParam;

	CString strUrl;
	CString strPort;
	m_edit_pyIP.GetWindowTextW(strUrl);
	m_edit_pyPort.GetWindowTextW(strPort);

	char buff[100];
	debug("while true sendFrameLoop");
	while (true) {
		//sprintf_s(buff, "Start sendFrameLoop\n");
		//debug(buff);
		SOCKET sockClient;
		SOCKADDR_IN addrServer;
		//debug("socket");
		sockClient = socket(AF_INET, SOCK_STREAM, 0);
		char chServer[256] = { 0 };
		char chClientId[256] = { 0 };
		//debug("WideCharToMultiByte");
		WideCharToMultiByte(CP_ACP, 0, strUrl, -1, chServer, sizeof(chServer) - 1, NULL, NULL);
		int timeout = 30;
		if (timeout < 1) timeout = 1;
		addrServer.sin_addr.s_addr = inet_addr((const char*)chServer);
		// inet_pton(AF_INET, (const char*)chServer, buff);
		addrServer.sin_family = AF_INET;
		addrServer.sin_port = htons(_wtoi(strPort));
		struct timeval timeoutRecv = { 0 };
		timeoutRecv.tv_sec = timeout * 1000;
		//debug("setsockopt");
		setsockopt(sockClient, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeoutRecv, sizeof(timeoutRecv));
		setsockopt(sockClient, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeoutRecv, sizeof(timeoutRecv));

		debug("Connect to Python");
		int iResult = connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
		Sleep(3);


		char* buf = 0;
		buf = new char[DIB_BUFFER_SIZE];
		int size = 0;
		debug("CaptureBmpToRam");
		size = CaptureBmpToRam(buf, DIB_BUFFER_SIZE);


		if (iResult == NO_ERROR)
		{
			debug("Python connect success");
			WSADATA wsaData;
			WSAStartup(MAKEWORD(2, 2), &wsaData);
			int rc = 0;
			size_t count = 0;


			rc = send(sockClient, buf, size, 0);
			if (rc < 0)
			{
				//OutputDebugStringW(L"Sent complete\n");
			}
			char* ptr = 0;
			do {
				if (size <= 0)
				{
					break;
				}
				ptr = buf;
				int zero_cnt = 0;
				do {
					rc = send(sockClient, ptr, size, 0);
					if (rc < 0)
					{
						break;
					}
					if (rc == 0)
					{
						zero_cnt++;
						if (zero_cnt >= 3) break;
					}
					else
					{
						zero_cnt = 0;
					}

					ptr += rc;
					count += size;
					size -= rc;
				} while (size);
			} while (rc > 0);
			rc = send(sockClient, buf, 1, 0);

			WSACleanup();
			debug("End sendFrameLoop");
		}
		else {
			debug("Python Connect fail");
			Sleep(1000);
		}

		delete[]buf;

		closesocket(sockClient);
		shutdown(sockClient, SD_SEND);
	}
}

DWORD WINAPI CCPosVideoDemoDlg::SendFrameThread(LPVOID lpParam)
{
	CCPosVideoDemoDlg* pThis = (CCPosVideoDemoDlg*)lpParam;
	while (1) {
		pThis->sendFrameLoop(lpParam);
	}
	return 1;
}


void CCPosVideoDemoDlg::OnBnClickedBPreview()
{
	//m_check_coud_id
	CString strip;
	int port = 34567;
	m_edit_url.GetWindowTextW(strip);


	ConnectRealPlay(0, 0, 0, strip, port, _T("admin"), _T(""), m_check_coud_id.GetCheck(), m_static_video.m_hWnd);
	CreateThread(NULL, 0, SendFrameThread, this, 0, &m_dwSenderThreadId);

}


void CCPosVideoDemoDlg::OnBnClickedBFrame()
{
	char *buf = 0;
	buf = new char[DIB_BUFFER_SIZE];
	int size = 0;
	size = CaptureBmpToRam(buf, DIB_BUFFER_SIZE);

	if (size)
	{
		CString str = _T("bmp(*.bmp)|*.bmp|All Files (*.*)|*.*||");
		CFileDialog dlgOpen(FALSE, _T(".bmp"), _T(""), NULL, str);

		if (dlgOpen.DoModal() == IDOK)
		{
			CString strFile = dlgOpen.GetPathName();
			//保存到文件中
			CFile f;
			BOOL r = FALSE;
			if (f.Open(strFile, CFile::modeCreate | CFile::modeWrite))
			{

				f.Write(buf, size);
				f.Close();
			}

		}
	}


	delete[]buf;


}




//检查用户名密码等是否可以登录成功
//bCloud 1-云ip登录
int CCPosVideoDemoDlg::CameraLogin(CString strIP, int nPort, CString strUserName, CString strPassword, int bCloud)
{
	H264_DVR_DEVICEINFO OutDev;
	memset(&OutDev, 0, sizeof(OutDev));

	int nError = H264_DVR_ILLEGAL_PARAM;


	if (strIP.IsEmpty()) return nError;


	WideCharToMultiByte(CP_ACP, 0, strIP, -1, m_videoIp, sizeof(m_videoIp)-1, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, strUserName, -1, m_videoUserName, sizeof(m_videoUserName)-1, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, strPassword, -1, m_videoPsw, sizeof(m_videoPsw)-1, NULL, NULL);

	m_bCloudId = bCloud;


	//设置尝试连接设备次数和等待时间
	H264_DVR_SetConnectTime(3000, 1);//设置尝试连接1次，等待时间3s
	long lLogin = 0;
	if (m_bCloudId)
	{
		lLogin = H264_DVR_Login_Cloud(m_videoIp, nPort, m_videoUserName,
			m_videoPsw, &OutDev, &nError, NULL);
	}
	else
	{
		lLogin = H264_DVR_Login(m_videoIp, nPort, m_videoUserName,
			m_videoPsw, &OutDev, &nError);
	}
	if (lLogin <= 0)
	{
		CString strErr;
		switch (nError)
		{
		case H264_DVR_PASSWORD_NOT_VALID:
			strErr = _T("Error.PwdErr");
			break;
		case H264_DVR_NOPOWER:
			strErr = _T("Error.NoPower");
			break;
		case H264_DVR_LOGIN_USER_NOEXIST:
			strErr = _T("Error.UserNotExisted");
			break;
		case H264_DVR_USER_LOCKED:
			strErr = _T("Login.Locked");
			break;
		case H264_DVR_USER_IN_BLACKLIST:
			strErr = _T("Error.InBlackList");
			break;
		case H264_DVR_USER_HAS_USED:
			strErr = _T("Error.HasLogined");
			break;
		case H264_DVR_CONNECT_DEVICE_ERROR:
			strErr = _T("Error.NotFound");
			break;
		default:
		{

				   strErr = _T("Log.Error");
		}

			break;
		}
		//AFXMessageBox(strErr);
		return nError;
	}
	m_videonTotalChannel = OutDev.byChanNum + OutDev.iDigChannel;
	m_LoginID = lLogin;
	m_LoginPort = nPort;



	if (m_bCloudId)
	{
		m_videoIp[0] = 0;
		_snprintf_s(m_videoCloudId, sizeof(m_videoCloudId), "%s", m_videoIp);// ip addr == cloud id
	}
	else
	{
		_snprintf_s(m_videoCloudId, sizeof(m_videoCloudId), "%s", OutDev.sSerialNumber);
	}


	H264_DVR_SetupAlarmChan(lLogin);//注册登录id到报警消息, 产生警报时发到相应的登录设备上


	if (lLogin > 0)
	{
		return lLogin;
	}

	if (nError <= 0) return nError;

	return H264_DVR_SDK_UNKNOWNERROR;
}
int __stdcall RealDataCallBack_V2(long lRealHandle, const PACKET_INFO_EX *pFrame, long dwUser)
{
	CCPosVideoDemoDlg *pDataChnl = (CCPosVideoDemoDlg*)dwUser;

	BOOL ret = H264_PLAY_InputData(pDataChnl->m_nDecodeHandle, (unsigned char*)pFrame->pPacketBuffer, pFrame->dwPacketSize);

	return ret;
}

void CCPosVideoDemoDlg::StopRealPlay()
{

	if (m_iPlayhandle != -1)
	{
		//H264_DVR_DelRealDataCallBack(m_iPlayhandle, RealDataCallBack, (long)this);
		H264_DVR_DelRealDataCallBack_V2(m_iPlayhandle, RealDataCallBack_V2, (long)this);
		if (!H264_DVR_StopRealPlay(m_iPlayhandle))
		{
			TRACE("H264_DVR_StopRealPlay fail m_iPlayhandle = %d", m_iPlayhandle);
		}
		m_iPlayhandle = -1;
	}

}

void __stdcall videoInfoFramCallback(LONG nPort, LONG nType, LPCSTR pBuf, LONG nSize, LONG nUser)
{
	CCPosVideoDemoDlg *pThis = (CCPosVideoDemoDlg*)nUser;
	//收到信息帧, 0x03 代表GPRS信息
	if (nType == 0x03)
	{
		//pThis->m_strInfoFrame[nPort] = pBuf;
	}
}

void CALLBACK drawVideoOSDCall(LONG nPort, HDC hDc, LONG nUser)
{
	
}

int __stdcall RealVideoDataCallBack(long lRealHandle,
	long dwDataType, unsigned char *pBuffer,
	long lbufsize, long dwUser)
{
	CCPosVideoDemoDlg *pDataChnl = (CCPosVideoDemoDlg*)dwUser;

	//把原始数据输入解码器解码
	H264_PLAY_InputData(pDataChnl->m_nDecodeHandle, pBuffer, lbufsize);

	return 1;
}
int CCPosVideoDemoDlg::ConnectRealPlay(int nIndex, bool bOsd, int nChannel, CString strIP, int nPort, CString strUserName, CString strPassword, int bCloud, HWND hWnd)
{
	m_videoChannel = nChannel ;
	int login = 0;
	//	login = m_rtsp[0].CameraLogin(strIp, strPort, strUsername, strPassword, m_check_cloud_id.GetCheck());
	m_videoIndex = nIndex;
	m_videoWnd = hWnd;

	if (m_LoginID <= 0)
	{
		login = CameraLogin(strIP, nPort, strUserName, strPassword, bCloud); //登录后已得到m_LoginID
		if (login <= 0)
		{
			return 0;
		}
	}



	StopRealPlay();

	if (m_nDecodeHandle == -1)
	{
		//open decoder
		BYTE byFileHeadBuf;
		if (H264_PLAY_OpenStream(m_videoIndex, &byFileHeadBuf, 1, SOURCE_BUF_MIN * 50))
		{
			//设置信息帧回调
			H264_PLAY_SetInfoFrameCallBack(m_videoIndex, videoInfoFramCallback, (DWORD)this);

			//叠加osd信息
			if (bOsd)
			{
				
			}
			else
			{
				//设置osd叠加回调
				H264_PLAY_RigisterDrawFun(m_videoIndex, drawVideoOSDCall, (DWORD)this);
				//OSd信息设置， 单通道
				SDK_OSDInfo Osd;
				Osd.index = 1;
				Osd.nChannel = nChannel;
				Osd.nX = 0;
				Osd.nY = 0;
				strcpy_s(Osd.pOSDStr, 100, "");
				long lret = H264_DVR_SetDevConfig(m_LoginID, E_SDK_SET_OSDINFO, 0, (char *)&Osd, sizeof(SDK_OSDInfo));

			}

			H264_PLAY_SetStreamOpenMode(m_videoIndex, STREAME_REALTIME);
			//只播放I帧,可降低cpu使用率
			//H264_PLAY_OnlyIFrame(m_nIndex, true);
			//	H264_PLAY_SetDisplayCallBack(m_nIndex, DisplayCallBackFun, (LONG)this);
			H264_PLAY_SetDisplayCallBack(m_videoIndex, NULL, NULL);
			//H264_PLAY_SetDecCallBack(m_nIndex, nProc);//设置解码回调, 设置后在回调中自己解码
			if (H264_PLAY_Play(m_videoIndex, m_videoWnd))
			{
				m_nDecodeHandle = m_videoIndex;
			}
		}
	}
	H264_DVR_CLIENTINFO playstru;

	playstru.nChannel = nChannel;
	playstru.nStream = 0;//0主码，1子码
	playstru.nMode = 0;
	m_iPlayhandle = H264_DVR_RealPlay(m_LoginID, &playstru);
	if (m_iPlayhandle <= 0)
	{
		DWORD dwErr = H264_DVR_GetLastError();

	}
	else
	{
		//set callback to decode receiving data

		//设置原始数据回调, 拿到数据后输入到解码器解码
		H264_DVR_SetRealDataCallBack(m_iPlayhandle, RealVideoDataCallBack, (long)this);

		//H264_DVR_MakeKeyFrame(pDev->lLoginID, nChannel, 0);
		//H264_DVR_SetRealDataCallBack_V2(m_iPlayhandle, RealVideoDataCallBack_V2, (long)this);
	}


	return m_iPlayhandle;
}

void CCPosVideoDemoDlg::Disconnct()
{
	//H264_DVR_DelRealDataCallBack(m_iPlayhandle, RealVideoDataCallBack, (long)this);

	StopRealPlay();
	//close decoder
	if (m_nDecodeHandle >= 0)
	{
		H264_PLAY_Stop(m_nDecodeHandle);
		H264_PLAY_CloseStream(m_nDecodeHandle);
		m_nDecodeHandle = -1;
		m_LoginID = -1;
	}


}



int CCPosVideoDemoDlg::CaptureBmpToRam(char *pBuf, int len)
{

	if (pBuf == NULL)
	{
		return 0;
	}

	int res = 0;

	long lRetLen = 0;
	if (m_LoginID > 0 && m_iPlayhandle > 0)
	{
		LONG width = 0;
		LONG height = 0;
		char c = 0;
		lRetLen = H264_PLAY_CatchPicBuf(m_nDecodeHandle, &c, 0, &width, &height, 0);//抓取BMP图像到内存
		int dib_length = width * height * 3 + 54;//BMP图像的存储空间

		//H264_PLAY_CatchPic(m_nPlaydecHandle, filename, 0))//直接抓取到文件 ntype:0-bmp, 1-jpg
		lRetLen = H264_PLAY_CatchPicBuf(m_nDecodeHandle, pBuf, dib_length, &width, &height, 0);//抓取BMP图像到内存
		if (lRetLen > 0)//返回存储大小
		{
			
		}
		else
		{
			
			int Errn = H264_DVR_GetLastError();
			if (Errn)
			{
			}
		}

		//	H264_PLAY_ResetSourceBuffer(m_nDecodeHandle);
		//	H264_PLAY_ResetBuffer(m_nDecodeHandle, BUF_VIDEO_RENDER);//BUF_VIDEO_SRC
	}

	return lRetLen;
}




void CCPosVideoDemoDlg::OnClose()
{


	Disconnct();

	ExitSDk();


	CDialogEx::OnClose();
}
