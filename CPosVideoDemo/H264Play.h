
#ifndef __DECODE_H264PLAY_H__
#define __DECODE_H264PLAY_H__

#ifdef WIN32
#include <time.h>
#define H264_PLAY_API extern "C" __declspec(dllexport)
#define CALLMETHOD __stdcall
#define CALLBACK __stdcall
#else
#define H264_PLAY_API  
#define CALLMETHOD 
#define CALLBACK 
#define WORD	unsigned short
#define DWORD	unsigned long
#define LPDWORD	DWORD*
#define BOOL	int
#define TRUE	0x01
#define FALSE	0x00
#define BYTE	unsigned char
#define LONG	long
#define UINT	unsigned int
#define HDC		void*
#define HWND	void*
#define LPVOID	void*
#define VOID	void
#define NULL	0
#define LPBYTE  unsigned char*
#define LPSTR	char*
#define LPCSTR	char*
#define PBYTE	unsigned char*

typedef struct  _SYSTEMTIME
{
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
}	SYSTEMTIME;

#ifndef RECT
typedef struct
{
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
}RECT;
#endif

typedef DWORD COLORREF;
typedef int HFONT;
#endif


#define  FUNC_MAX_PORT 500              //��󲥷�ͨ����

#define TALK_PORT	499
#define TALK_PCM_PORT 500

//Wave coef range;
#define MIN_WAVE_COEF -100
#define MAX_WAVE_COEF 100

//Timer type
#define TIMER_1 1 //Only 16 timers for every process.Default TIMER;
#define TIMER_2 2 //Not limit;But the precision less than TIMER_1; 

//��������
#define BUF_VIDEO_SRC 1    //��ƵԴ����        
#define BUF_AUDIO_SRC 2    //��ƵԴ����
#define BUF_VIDEO_RENDER 3  //�������Ƶ���ݻ���
#define BUF_AUDIO_RENDER 4  //�������Ƶ���ݻ���

//��������
#define	H264_PLAY_NOERROR               0           //û�д���
#define H264_PLAY_PARA_OVER             1           //��������Ƿ���
#define H264_PLAY_ORDER_ERROR           2           //����˳�򲻶ԣ�
#define H264_PLAY_TIMER_ERROR           3           //��ý��ʱ������ʧ�ܣ�
#define H264_PLAY_DEC_VIDEO_ERROR       4	          //��Ƶ����ʧ�ܣ�
#define H264_PLAY_DEC_AUDIO_ERROR       5	          //��Ƶ����ʧ�ܣ�
#define H264_PLAY_ALLOC_MEMORY_ERROR    6		       	//�����ڴ�ʧ�ܣ�
#define H264_PLAY_OPEN_FILE_ERROR       7			   		//�ļ�����ʧ�ܣ�
#define H264_PLAY_CREATE_OBJ_ERROR      8	          //�����߳��¼���ʧ�ܣ�
#define H264_PLAY_CREATE_DDRAW_ERROR		9		       	//����directDrawʧ�ܣ�
#define H264_PLAY_CREATE_OFFSCREEN_ERROR	10		    //������˻���ʧ�ܣ�
#define H264_PLAY_BUF_OVER              11	        //����������������ʧ�ܣ�
#define H264_PLAY_CREATE_SOUND_ERROR    12		      //������Ƶ�豸ʧ�ܣ�
#define H264_PLAY_SET_VOLUME_ERROR      13	        //��������ʧ�ܣ�
#define H264_PLAY_SUPPORT_FILE_ONLY     14		      //ֻ���ڲ����ļ�ʱ����ʹ�ô˽ӿڣ�
#define H264_PLAY_SUPPORT_STREAM_ONLY   15		      //ֻ���ڲ�����ʱ����ʹ�ô˽ӿڣ�
#define H264_PLAY_SYS_NOT_SUPPORT       16		      //ϵͳ��֧�֣�������ֻ�ܹ�����Pentium 3���ϣ�
#define H264_PLAY_FILEHEADER_UNKNOWN    17		      //û���ļ�ͷ��
#define H264_PLAY_VERSION_INCORRECT     18	        //�������ͱ������汾����Ӧ��
#define H264_PLAY_INIT_DECODER_ERROR    19		      //��ʼ��������ʧ�ܣ�
#define H264_PLAY_CHECK_FILE_ERROR      20		      //�ļ�̫�̻������޷�ʶ��
#define H264_PLAY_INIT_TIMER_ERROR      21		      //��ʼ����ý��ʱ��ʧ�ܣ�
#define H264_PLAY_BLT_ERROR             22		      //λ����ʧ�ܣ�
#define H264_PLAY_UPDATE_ERROR          23			   	//��ʾoverlayʧ�ܣ�


//Max display regions.
#define MAX_DISPLAY_WND 4

//Display type
#define DISPLAY_NORMAL  1   
#define DISPLAY_QUARTER 2	

//Display buffers
#define MAX_DIS_FRAMES 50
#define MIN_DIS_FRAMES 6

//Locate by
#define BY_FRAMENUM  1
#define BY_FRAMETIME 2

//Source buffer
#define SOURCE_BUF_MAX	1024*100000
#define SOURCE_BUF_MIN	1024*50

//Stream type
#define STREAME_REALTIME 0
#define STREAME_FILE	 1

//frame type
#define T_AUDIO16	101
#define T_AUDIO8	100

#define T_UYVY		1
#define T_YV12		3
#define T_RGB32		7

//ϵͳ֧�ֵĹ��ܣ����ڰ�λ��ʾϵͳ����
#define SUPPORT_DDRAW		1			// ֧��DIRECTDRAW�������֧�֣��򲥷������ܹ�����
#define SUPPORT_BLT         2			// �Կ�֧��BLT�����������֧�֣��򲥷������ܹ���
#define SUPPORT_BLTFOURCC   4			// �Կ�BLT֧����ɫת����
#define SUPPORT_BLTSHRINKX  8			// �Կ�BLT֧��X����С��
#define SUPPORT_BLTSHRINKY  16		// �Կ�BLT֧��Y����С��
#define SUPPORT_BLTSTRETCHX 32		// �Կ�BLT֧��X��Ŵ�
#define SUPPORT_BLTSTRETCHY 64		// �Կ�BLT֧��Y��Ŵ�
#define SUPPORT_SSE         128		// CPU֧��SSEָ��,Intel Pentium3����֧��SSEָ�
#define SUPPORT_MMX			256		// CPU֧��MMXָ���

typedef enum _MEDIA_FILE_TYPE
{
	MEDIA_FILE_NONE = 0,
	MEDIA_FILE_H264 = 1,
	MEDIA_FILE_AVI = 2,
	MEDIA_FILE_RMVB = 3,
	MEDIA_FILE_MPG4 = 4,
	MEDIA_FILE_NUM
}MEDIA_FILE_TYPE;
typedef enum _PICTURE_FILE_TYPE
{
	PICTURE_FILE_BMP = 0,
	PICTURE_FILE_JPG = 1
		
}PICTURE_FILE_TYPE;

//Frame position
typedef struct{
	long nFilePos;
	long nFrameNum;
	long nFrameTime;
	long nErrorFrameNum;
	SYSTEMTIME *pErrorTime;
	long nErrorLostFrameNum;
	long nErrorFrameSize;
}FRAME_POS,*PFRAME_POS;

// Frame Info
typedef struct{
	long nWidth;		// ��������λ���ء��������Ƶ������Ϊ0��
	long nHeight;		// ����ߡ��������Ƶ������Ϊ0��
	long nStamp;		// ʱ����Ϣ����λ���롣
	long nType;			// �������ͣ�T_AUDIO16��T_RGB32�� T_YV12������궨��˵����
	long nFrameRate;	// ����ʱ������ͼ��֡�ʡ�
}FRAME_INFO;

typedef struct 
{
	char *pDataBuf;
	long nSize;
	long nFrameNum;
	BOOL bIsAudio;
	long nReserved;
}FRAME_TYPE;

/// ��������
enum ENCODE_TYPE
{
	StreamTypeEmpty = 0,
	StreamTypeH264 = 2,
	StreamTypeJpeg = 3,
	StreamTypeGeneral = 4,
	StreamTypePCM8 = 7,
	StreamTypeStd = 8
};

/// ͼ��֡����
enum VIDEO_FRAME_TYPE
{
	FrameTypeUnknown = 0,
	FrameTypeVideo = 1,
	FrameTypeAudio = 2,
	FrameTypeData = 3,
};

/// ͼ��֡������
enum VIDEO_FRAME_SUB_TYPE
{
	FrameSubTypeIFrame = 0,
	FrameSubTypePFrame = 1,
	FrameSubTypeBFrame = 2,
	FrameSubTypeSFrame = 3,
	FrameSubTypeDataText = 5,
	FrameSubTypeDataIntl = 6,
};

enum DATA_FRAME_SUB_TYPE
{
	DataFrameSubType_Normal,
	DataFrameSubType_VehicleInfo,							//������Ϣ
	DataFrameSubType_StorageV4_IndexInfo,		//StorageV4��������Ϣ
	DataFrameSubType_FishEyeHardAdjust,			//�����豸(ӲУ��)
	DataFrameSubType_FishEyeSoftAdjust,			//���۾�ͷ��������У����
	DataFrameSubType_DistortAdjust,						//����У������
	DataFrameSubType_VirtualIFrameMask,				//����I֡��ʶ
	DataFrameSubType_VideoAnalyseRule,				//���ܷ�������
	DataFrameSubType_VideoAnalyseAlarm,			//���ܷ�������
	DataFrameSubType_FaceAreaInfo,						//����λ����Ϣ
	DataFrameSubType_Num,
};

typedef struct 
{
	unsigned char *pHeader;				///< ֡���ݻ�����ʼ��ַ
	unsigned char *pContent;
	unsigned long nLength;
	unsigned long nFrameLength;

	unsigned int nType;                ///< ��VIDEO_FRAME_TYPE
	unsigned int nSubType;             ///< ��VIDEO_FRAME_SUB_TYPE

	unsigned int nEncodeType;          ///< ��ENCODE_TYPE

	unsigned long nYear;				///< ֡ʱ���
	unsigned long nMonth;
	unsigned long nDay;
	unsigned long nHour;
	unsigned long nMinute;
	unsigned long nSecond;
	unsigned long nTimeStamp;	

	unsigned int  nFrameRate;			///< ��Ƶͼ��֡��
	int nWidth;							///< ��Ƶͼ���С����Ⱥ͸߶�
	int nHeight;
	unsigned long nRequence;

	unsigned int nChannels;
	unsigned int nBitsPerSample;		///< ��Ƶ����λ��
	unsigned int nSamplesPerSecond;		///< ��Ƶ������

	unsigned long nParam1;		// ��չ��
	unsigned long nParam2;		// ��չ��
} VIDEO_FRAME_INFO;


//�������ͣ�Ŀǰֻ֧����Щ
typedef enum 
{
	OSD_TXT_FONT_ARIAL = 1,
	OSD_TXT_FONT_SERIF,
	OSD_TXT_FONT_SANS,
	
	OSD_TXT_FONT_SIMSUN = 101,  // �������壬����
	OSD_TXT_FONT_SIMHEI
} DEFAULT_OSD_TXT_FONT;

typedef struct
{
	int pos_x;			//���λ��(�ٷֱ�)
	int pos_y;
	COLORREF color;		//������ɫ
	char text[256];
	DEFAULT_OSD_TXT_FONT font_type;
	int font_size;		//�Դ��ڵİٷֱ�����ʾ
	HFONT out_ft;		//�������������
	int isBold;			//�Ƿ����
	int isTransparent;	//�Ƿ�͸����ɫ
	COLORREF bkColor;	//����ɫ
} OSD_INFO_TXT;

typedef enum 
{
	STD_FILE_HEAD =	0,	    		// �ļ�ͷ
		STD_VIDEO_I_FRAME = 1,			// ��ƵI֡
		STD_VIDEO_B_FRAME =	2,			// ��ƵB֡
		STD_VIDEO_P_FRAME = 3,			// ��ƵP֡
		STD_VIDEO_BP_FRAME = 4,			// ��ƵBP֡
		STD_VIDEO_BBP_FRAME	= 5,		// ��ƵB֡B֡P֡
		STD_VIDEO_J_FRAME = 6,			// ͼƬ֡
		STD_AUDIO_PACKET = 10,			// ��Ƶ��
}MEDIA_DATA_TYPE;

typedef struct
{
	int		nPacketType;				// ������,MEDIA_DATA_TYPE
	char*	pPacketBuffer;				// ��������ַ
	unsigned int	dwPacketSize;				// ���Ĵ�С
	
	// ����ʱ��
	int		nYear;						// ʱ��:��		
	int		nMonth;						// ʱ��:��
	int		nDay;						// ʱ��:��
	int		nHour;						// ʱ��:ʱ
	int		nMinute;					// ʱ��:��
	int		nSecond;					// ʱ��:��
	unsigned int 	dwTimeStamp;					// ���ʱ���λ����λΪ����	
	unsigned int   dwFrameNum;             //֡���
	unsigned int   dwFrameRate;            //֡��
	unsigned short uWidth;              //ͼ����
	unsigned short uHeight;             //ͼ��߶�
	unsigned int   nAudioEncodeType;          //��Ƶ��������IMA	 9 PCM8_VWIS 12 MS_ADPCM 13 G711A 14
	unsigned int   nBitsPerSample;			//��Ƶ����λ��
	unsigned int   nSamplesPerSecond;       // ��Ƶ������
	unsigned int       Reserved[6];            //����
} STDH264_PACKET_INFO;
//������λ�ã���������8192
typedef struct AreaRect
{
	unsigned short x;		
	unsigned short y;
	unsigned short w;
	unsigned short h;
}AreaRect;

typedef struct FaceAreaInfo
{
	unsigned short frameId;	//֡���
	unsigned char areaNum; //�����������
	AreaRect* pAreaRect;	//���������������
}FaceAreaInfo;

// �ص���������
typedef void (CALLBACK *AudioCaptureCallBack)(LPBYTE pDataBuffer, DWORD DataLength, long nUser);
typedef void (CALLBACK *DrawCallBack)(LONG nPort,HDC hDc,LONG nUser);
typedef void (CALLBACK *DecodeCallBack)(LONG nPort, LPCSTR pBuf,LONG nSize,FRAME_INFO * pFrameInfo, LONG nPlayedFrames);
typedef void (CALLBACK *DisplayCallBack)(LONG nPort,LPCSTR pBuf,LONG nSize,LONG nWidth,LONG nHeight, LONG nStamp,LONG nType,LONG nUser);
typedef void (CALLBACK *FileCallBack)(LONG nPort, LONG nUser);
typedef void (CALLBACK *VerifyCallBack)(LONG nPort, FRAME_POS * pFilePos, DWORD bIsVideo, LONG nUser);
typedef void (CALLBACK *AudioCallBack)(LONG nPort, PBYTE pAudioBuf, LONG nSize, LONG nStamp, LONG nType, LONG nUser);
typedef void (CALLBACK *DemuxCallBack)(LONG nPort, VIDEO_FRAME_INFO *pFrameInfo,LONG nUser);
typedef void (CALLBACK *SourceBufCallBack)(LONG nPort,DWORD nBufSize, LONG nUser);
typedef void (CALLBACK *ImageSizeChangeCallBack)(LONG nPort, LONG nUser);

typedef void (CALLBACK *CoverFileCallBack) (DWORD CurrentPos, DWORD TotoalPos,long dwUser);//ת������

//��Ϣ֡�ص�
typedef void (CALLBACK *InfoFramCallBack)(LONG nPort, LONG nType, LPCSTR pBuf,LONG nSize, LONG nUser);

//��Ϣ֡�ص�V2����
typedef void (CALLBACK *InfoFramCallBack_V2)(LONG nPort, LONG nType,LONG nSubType, LPCSTR pBuf,LONG nSize, LONG nUser);

//����Ϊ����ӿڣ����û������ο�������

H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_OpenFile(LONG nPort, LPCSTR sFileName);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_CloseFile(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_Play(LONG nPort, HWND hWnd);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_Stop(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_Pause(LONG nPort,DWORD nPause);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_Fast(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_Slow(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_NextFrame(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_PrevFrame(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetPlayPos(LONG nPort, float fRelativePos);
H264_PLAY_API float CALLMETHOD 	H264_PLAY_GetPlayPos(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetFileEndMsg(LONG nPort,HWND hWnd,UINT nMsg);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetFileEndCallBack(LONG nPort, FileCallBack pProc,LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetVolume(LONG nPort,WORD nVolume);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_StopSound();
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_PlaySound(LONG nPort);
H264_PLAY_API BOOL	CALLMETHOD 	H264_PLAY_OpenStream(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_InputData(LONG nPort,PBYTE pBuf,DWORD nSize);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_CloseStream(LONG nPort);
H264_PLAY_API LONG  CALLMETHOD 	H264_PLAY_GetCaps();
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetFileTime(LONG nPort);
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetPlayedTime(LONG nPort);
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetPlayedFrames(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_Back(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetDecCallBack(LONG nPort, DecodeCallBack pProc);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetDisplayCallBack(LONG nPort, DisplayCallBack pProc, LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_ConvertToBmpFile(PBYTE pBuf,LONG nSize,LONG nWidth,LONG nHeight, LPCSTR sFileName,char*pDstBuf=NULL);
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetFileTotalFrames(LONG nPort);
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetPlayedTimeEx(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetPlayedTimeEx(LONG nPort,DWORD nTime);
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetCurrentFrameNum(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetStreamOpenMode(LONG nPort,DWORD nMode);
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetSdkVersion();
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetLastError(LONG nPort);
//H264_PLAY_RefreshPlay�Ѳ�ʹ�ã������ڲ��Զ�ˢ��
H264_PLAY_API BOOL  CALLMETHOD 	H264_PLAY_RefreshPlay(LONG nPort);
H264_PLAY_API BOOL  CALLMETHOD 	H264_PLAY_SetOverlayMode(LONG nPort,BOOL bOverlay,COLORREF colorKey);
H264_PLAY_API BOOL  CALLMETHOD 	H264_PLAY_GetPictureSize(LONG nPort,LONG *pWidth,LONG *pHeight);
H264_PLAY_API BOOL  CALLMETHOD 	H264_PLAY_SetPicQuality(LONG nPort,BOOL bHighQuality);
H264_PLAY_API BOOL  CALLMETHOD 	H264_PLAY_PlaySoundShare(LONG nPort);
H264_PLAY_API BOOL  CALLMETHOD 	H264_PLAY_StopSoundShare(LONG nPort);
H264_PLAY_API LONG 	CALLMETHOD 	H264_PLAY_GetStreamOpenMode(LONG nPort);
H264_PLAY_API LONG 	CALLMETHOD 	H264_PLAY_GetOverlayMode(LONG nPort);
H264_PLAY_API WORD 	CALLMETHOD 	H264_PLAY_GetVolume(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_GetPictureQuality(LONG nPort,BOOL *bHighQuality);
H264_PLAY_API DWORD CALLMETHOD	H264_PLAY_GetSourceBufferRemain(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_ResetSourceBuffer(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetSourceBufCallBack(LONG nPort,DWORD nThreShold, SourceBufCallBack pProc, LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_ResetSourceBufFlag(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetDisplayBuf(LONG nPort,DWORD nNum);
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetDisplayBuf(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetFileRefCallBack(LONG nPort, FileCallBack pProc, LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetCurrentFrameNum(LONG nPort,DWORD nFrameNum);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_GetKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_GetNextKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_InitDDrawDevice();
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_ReleaseDDrawDevice();
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetDDrawDeviceTotalNums();

H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetDisplayType(LONG nPort,LONG nType);
H264_PLAY_API LONG 	CALLMETHOD 	H264_PLAY_GetDisplayType(LONG nPort);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetDecCBStream(LONG nPort,DWORD nStream);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetDisplayRegion(LONG nPort,DWORD nRegionNum, RECT *pSrcRect, HWND hDestWnd, BOOL bEnable);
//H264_PLAY_RefreshPlayEx�Ѳ�ʹ�ã������ڲ��Զ�ˢ��
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_RefreshPlayEx(LONG nPort,DWORD nRegionNum);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_GetRefValue(LONG nPort,BYTE *pBuffer, DWORD *pSize);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetRefValue(LONG nPort,BYTE *pBuffer, DWORD nSize);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_InputVideoData(LONG nPort,PBYTE pBuf,DWORD nSize);

H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_RigisterDrawFun(LONG nPort, DrawCallBack pProc,LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetTimerType(LONG nPort,DWORD nTimerType);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_GetTimerType(LONG nPort,DWORD *pTimerType);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_ResetBuffer(LONG nPort,DWORD nBufType);
H264_PLAY_API DWORD CALLMETHOD 	H264_PLAY_GetBufferValue(LONG nPort,DWORD nBufType);

H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_AdjustWaveAudio(LONG nPort,LONG nCoefficient);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetVerifyCallBack(LONG nPort, DWORD nBeginTime, DWORD nEndTime, VerifyCallBack pProc, LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetAudioCallBack(LONG nPort, AudioCallBack pProc, LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetImageSizeChangeCallBack(LONG nPort,ImageSizeChangeCallBack pProc,LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD	H264_PLAY_SetImageSizeChangeMsg(LONG nPort,HWND hWnd,UINT nMsg);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetColor(LONG nPort, DWORD nRegionNum, LONG nBrightness, LONG nContrast, LONG nSaturation, LONG nHue);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_GetColor(LONG nPort, DWORD nRegionNum, LONG *pBrightness, LONG *pContrast, LONG *pSaturation, LONG *pHue);

H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_CatchPic(LONG nPort, LPCSTR sFileName,long ntype=0 ) ;
H264_PLAY_API LONG  CALLMETHOD 	H264_PLAY_CatchPicBuf(LONG nPort, char* pBuf,LONG len,LONG *width,LONG *height,long ntype=0) ;

H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_StartDataRecord(LONG nPort,  LPCSTR sFileName, LONG nType);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_StopDataRecord(LONG nPort);
//level 1������ 7��ʵʱ��Ĭ��Ϊ4
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_AdjustFluency(LONG nPort, int level);
//H264_PLAY_AdjustFluencyEx���ڲ�ʹ��
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_AdjustFluencyEx(LONG nPort, int time);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetPlayFPS(LONG nPort, LONG nFPS);
H264_PLAY_API LONG 	CALLMETHOD 	H264_PLAY_GetPlayFPS(LONG nPort);

H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetDemuxCallBack(LONG nPort, DemuxCallBack pProc, LONG nUser);

H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_StartAudioCapture(AudioCaptureCallBack pProc, LONG nBitsPerSample, LONG nSamplesPerSec, LONG nLength, LONG nUser);
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_StopAudioCapture();
H264_PLAY_API BOOL  CALLMETHOD	H264_PLAY_GetPort(LONG* nPort);
H264_PLAY_API BOOL	CALLMETHOD	H264_PLAY_FreePort(LONG nPort);
H264_PLAY_API COLORREF 	CALLMETHOD	H264_PLAY_GetColorKey(LONG nPort);
H264_PLAY_API LONG	CALLMETHOD	H264_PLAY_GetFileHeadLength();
H264_PLAY_API DWORD CALLMETHOD H264_PLAY_GetCurTimeStamp(LONG nPort);

//����osd������Ϣ,������openstream��play֮ǰ���ã�������Ч
H264_PLAY_API int CALLMETHOD H264_PLAY_SetOsdTex(LONG nPort, OSD_INFO_TXT * txt);
//ɾ��osd������Ϣ,nIndex��H264_PLAY_SetOsdTex�ķ���ֵ
H264_PLAY_API int CALLMETHOD H264_PLAY_DeleteOsdTex(LONG nPort, int nIndex);
//H264¼���ļ�תAvi¼���ļ�
H264_PLAY_API int CALLMETHOD H264_PLAY_ConvertFile(const char* pSourceFile,const char* pDestFile,  LONG nType, CoverFileCallBack coverPosCallback, DWORD dwUser);

//��Ϣ֡�ص�
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetInfoFrameCallBack(LONG nPort, InfoFramCallBack pProc, LONG nUser);

//ֻ����I֡
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_OnlyIFrame(LONG nPort, bool bPlayOnlyIFrame);

//��׼H264����д��
H264_PLAY_API BOOL CALLMETHOD H264_PLAY_InputStdH264Data(LONG nPort,STDH264_PACKET_INFO *infor);

//��Ϣ֡�ص�V2
H264_PLAY_API BOOL 	CALLMETHOD 	H264_PLAY_SetInfoFrameCallBack_V2(LONG nPort, InfoFramCallBack_V2 pProc, LONG nUser);

/// ���Ų�������
enum PLAY_PARAM_TYPE
{
	PLAY_PARAM_OrgRate = 0,
	PLAY_PARAM_Render,
};

//��ԭʼ��������
typedef struct _H264_PLAY_ORG_RATE
{
	int bOrgRate;//0�������������ڣ�1��ԭʼ������ʾ
}H264_PLAY_ORG_RATE;

typedef struct _H264_PLAY_Render
{
	int bEnable;
}H264_PLAY_Render;
//���ò��Ų�������iTypeΪPLAY_PARAM_OrgRate��pParam����ṹ��H264_PLAY_ORG_RATE
H264_PLAY_API BOOL CALLMETHOD H264_PLAY_SetParam(LONG nPort, PLAY_PARAM_TYPE iType, VOID * pParam);

H264_PLAY_API BOOL CALLMETHOD H264_PLAY_RenderYUV420(LONG nPort,unsigned char* pData, int width, int height);

//�������ʱʹ��
H264_PLAY_API BOOL CALLMETHOD H264_PLAY_SetMaxWnd(LONG nPort, bool bMax);

//�Ƿ�����빦��
H264_PLAY_API BOOL CALLMETHOD H264_PLAY_OpenNoiseSuppression(LONG nPort, bool bOpen);

//���ý���ȼ�(Lv0-Lv3)
H264_PLAY_API BOOL CALLMETHOD H264_PLAY_SetNoiseSuppressionLevel(LONG nPort, int nlevel);

#endif

