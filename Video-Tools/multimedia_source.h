﻿#ifndef I_MULTIMEDIASOURCE
#define I_MULTIMEDIASOURCE

#include "Compression.h"
#include "TitleSet.h"
#include <vector>
#include <string>

#define INT64_MAX 0x7FFFFFFFFFFFFFFF

const int MMS_INVALID	= 0x00;
const int MMS_VIDEO		= 0x01;
const int MMS_AUDIO		= 0x02;
const int MMS_SUBTITLES = 0x03;

const int MMS_UNKNOWN   = -0x7FFFFFFF;

struct MULTIMEDIASOURCE_INFO
{
		__int64				iCurrentTimecode;	// contains timecode of last read frame			
		__int64				iMaxLength;			// contains maximum length of stream
		__int64				iBias;				// value to be added to each timestamp
		__int64				iTimecodeScale;		// scale for any timecodes
		double				dStretchFactor;
		bool				bDoStretch;
		bool				bSeamless;
		bool				bAVIOutputPossible;
		bool				bDefault;
		
		int					iCompression;
} ;


struct ADVANCEDREAD_INFO
{
// duration
	__int64		iDuration;
	__int64		iNextTimecode;
// for lacing
	int			iFramecount;
	int*		iFramesizes;
	int			iFileEnds;
} ;


/* Make up a universal read structure here. This structure
   is supposed to represent one data item that cannot be
   easily split apart, like one mp3 frame or a bunch of
   vorbis frames. */
struct MULTIMEDIA_DATA_PACKET
{
	/* Start timecode of a packet in nanoseconds */
	__int64		timecode;

	/* Duration of a packet in nanoseconds */
	__int64		duration;

	/* Start timecode of next packet if known; there could 
	   be a gap */
	__int64		nextTimecode;

	/* some flags; yet to be defined */
	int			flags;

	/* if there are several frames, the sizes of each frame */
	std::vector<int> frameSizes;

	/* relative timecodes of referenced frames */
	std::vector<int> referencedFrames;

	/* information about compression */
	std::vector<CCompressionInfo> compressionInfo;
	
	/* entire size of this packet */
	int			totalDataSize;

	/* usage counter; when 0 it's not used anymore and data can
	   be free()ed */
	int			usageCounter;

//	std::vector<unsigned char> data;
	/* raw data */
	union {
		void*		data;
		char*		cData;
	};
} ;

void createMultimediaDataPacket(MULTIMEDIA_DATA_PACKET** packet);
void freeMultimediaDataPacket(MULTIMEDIA_DATA_PACKET* packet);
void useMultimediaDataPacket(MULTIMEDIA_DATA_PACKET* packet);

const int TIMECODE_UNSCALED = 0x01;
//const __int64 TIMECODE_UNDEFINED = 0x7FFFFFFFFFFFFFFF;
const __int64 TIMECODE_UNKNOWN = -1;
const __int64 TIMECODE_UNINITIALIZED = -2;
const __int64 DURATION_UNKNOWN = -1;

const int BIAS_ABSOLUTE = 0x01;
const int BIAS_RELATIVE = 0x02;
const int BIAS_UNSCALED = 0x04;

const int MMT_UNDEFINED = 0x00;
const int MMT_AUDIO = 0x01;
const int MMT_VIDEO = 0x02;
const int MMT_SUBS  = 0x03;

const int MMS_COMPATIBLE            =  0x00000001;


const int MMSIC_TYPE				= -0x00000001;
const int MMSIC_VIDEORESOLUTION		= -0x00000002;
const int MMSIC_SAMPLERATE          = -0x00000003;

const int MMSIC_BITRATE				= -0x00000010;
const int MMSIC_FORMATTAG			= -0x00000011;
const int MMSIC_IDSTRING			= -0x00000012;
const int MMSIC_CHANNELS			= -0x00000013;
const int MMSIC_COMPRESSION			= -0x00000014;
const int MMSIC_MPEG_LAYERVERSION   = -0x00000015;
const int MMSIC_MPEG_VERSION        = -0x00000016;

const int FRAMEDURATION_UNKNOWN     = -0x00000001;

const int FEATURE_EXTRACTBIN		=  0x00000001;
const int FEATURE_SUB_EXTRACT2TEXT  =  0x00000010;

class CSizeGuesser
{
	private:
		float	fDuration;	// duration of data provided
		float	fTotal;		// duration of total stream
		__int64	iSize;
	public:
		CSizeGuesser();
		void	AddData(float f, __int64 i);
		__int64	GuessSize();
		void	SetTotalDuration(float f);

};

class MULTIMEDIASOURCE : public CHasTitles
{
	private:
		MULTIMEDIASOURCE_INFO info;
		CSizeGuesser*         size_guesser;
		
		MULTIMEDIASOURCE* delayMMS;
		__int64 accumulatedDelay;
	protected:
		char*				lpcName;
		std::string			m_languageCode;
		void		virtual AddSizeData(float f, __int64 i);
		bool		virtual CanAppend(MULTIMEDIASOURCE* pNext);
		int			virtual doClose();
		__int64		virtual DoStretch(__int64 iValue);
		__int64		virtual	GetMaxLength();
		__int64		virtual GuessTotalSize();
		void		virtual	IncCurrentTimecode(__int64 iTime);
		void		virtual	SetCurrentTimecode(__int64 iTime, int iFlags = 0);
		void		virtual UpdateDuration(__int64 iDuration);
	public:
		__int64		virtual GetExactSize();
		void		virtual SetTimecodeScale(__int64 iScale);
		void		virtual AllowAVIOutput(bool bAllow);
		int			virtual Append(MULTIMEDIASOURCE* pNext);
		int			virtual Close();
		int			virtual Enable(int bEnabled);
		int			virtual GetCompressionAlgo();
		int			virtual	GetName(char* lpDest);
		int			virtual GetLanguageCode(std::string& result);
		__int64		virtual GetBias(int iFlags = 0);
		__int64		virtual	GetCurrentTimecode();
		__int64		virtual GetDuration();
		__int64		virtual GetDurationUnscaled();
		__int64		virtual GetFeature(__int64 iFeature);
		__int64		virtual FormatSpecific(__int64 iCode, __int64 iValue = 0);
		__int64		virtual GetFrameDuration();
		char		virtual *GetCodecID();
		__int64		virtual GetTimecodeScale();
		int			virtual GetType();
		int			virtual	GetSourceType();
		__int64		virtual	GetSize();
		__int64		virtual GetUnstretchedDuration(void);
		bool		virtual IsAVIOutputPossible();
		int			virtual IsCompatible (MULTIMEDIASOURCE* m);
		bool		virtual	IsEndOfStream();
		void		virtual ReInit();
		int			virtual Seek(__int64 iTime);
		void		virtual	SetName(char* _lpcName);
		void		virtual SetCompressionAlgo(int algo);

		void		virtual SetLanguageCode(const std::string& languageCode);
		void		virtual	SetBias(__int64 iBias, int iFlags = BIAS_ABSOLUTE);
		void		virtual	SetMaxLength(__int64 iLength, int iFlags = 0);
		void		virtual SetStretchFactor(double dFactor);
		void		virtual SetDefault(int bDefault);

		int			virtual GetStrippableHeaderBytes(void* pBuffer, int max);
		int			virtual IsDefault();

		int			virtual GetPreferredTitle(char** pDest);

		// delay
		__int64		GetAccumulatedDelay();
		void		AddToAccumulatedDelay(__int64 valueToAdd);
		void		SetDelayMMS(MULTIMEDIASOURCE* delayMMS);

		MULTIMEDIASOURCE(void);
		virtual ~MULTIMEDIASOURCE(void);
};


#endif