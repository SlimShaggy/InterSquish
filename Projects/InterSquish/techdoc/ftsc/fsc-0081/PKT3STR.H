/* Structures for TYPE-3 in C */

/* You may have to change the order of the components in the bitfields */
/* You probably have to if using a Motorola CPU, this is for Intel */

typedef unsigned char   Byte;
typedef unsigned short  Word;
typedef unsigned long   Longword;

typedef struct
{
	Word    Zone;       /* Zone address */
	Word    Net;        /* Net address */
	Word    Node;       /* Node address */
	Word    Point;      /* Point address or 0 if boss */
} TAddress;

typedef struct
{
	unsigned    Type2  :1;
	unsigned    Type3  :1;
	unsigned    Type4  :1;
	unsigned    Type5  :1;
	unsigned    Type6  :1;
	unsigned    Type7  :1;
	unsigned    Type8  :1;
	unsigned    Type9  :1;
	unsigned    Type10 :1;
	unsigned    Type11 :1;
	unsigned    Type12 :1;
	unsigned    Type13 :1;
	unsigned    Type14 :1;
	unsigned    Type15 :1;
	unsigned    Type16 :1;
	unsigned    RFC822 :1;
} CapabilityWord;

typedef Longword    TTimeStamp;

typedef struct
{
	unsigned    Pvt        :1;   /* Private message */
	unsigned    FileAttach :1;   /* File attach message */
	unsigned    FileReq    :1;   /* File request message */
	unsigned    UpdReq     :1;   /* File update request message */
	unsigned    Direct     :1;   /* Do not route this message */
	unsigned    Crash      :1;   /* High-priority mail */
	unsigned    Hold       :1;   /* Hold for pickup */
	unsigned    IMM        :1;   /* Immediate mail */
	unsigned    RRQ        :1;   /* Return receipt request */
	unsigned    CRQ        :1;   /* Confirm receipt request */
	unsigned    IRR        :1;   /* Is return receipt */
	unsigned    Machine    :1;   /* Message to a program */
	unsigned    NoForCC    :1;   /* CC in NetMail, NoForward in EchoMail */
	unsigned    Permanent  :1;   /* Message should not be pruged by age */
	unsigned    Foreign    :1;   /* Message is from other organization */
	unsigned    reserved15 :1;    /* Reserved for future extension */
} TMsgFlags;

typedef struct
{
	unsigned    Local     :1;   /* Message is created localy */
	unsigned    InTransit :1;   /* Message is not destinated for this system */
	unsigned    Orphan    :1;   /* Unknown destination */
	unsigned    KillSent  :1;   /* Remove message after it has been sent */
	unsigned    DelSent   :1;   /* Delete attached file(s) after have been sent */
	unsigned    TruncSent :1;   /* Truncate attached file(s) after have been sent */
	unsigned    Sent      :1;   /* Message has been sent */
	unsigned    IsRead    :1;   /* Message has been read by the SysOp */
	unsigned    Rcvd      :1;   /* Message has been read by its addressee */
	unsigned    LockMsg   :1;   /* Lock the message for further access */
	unsigned    DontSend  :1;   /* Do not send the actual message */
	unsigned    unused11  :1;   /* Reserved for future extension */
	unsigned    unused12  :1;   /* Reserved for future extension */
	unsigned    unused13  :1;   /* Reserved for future extension */
	unsigned    unused14  :1;   /* Reserved for future extension */
	unsigned    unused15  :1;    /* Reserved for future extension */
} TLocalFlags;

typedef struct
{
	TAddress       PktOrig;      /* The node who created this packet */
	TAddress       PktDest;      /* The node who should receive this packet */
	Word           SubTupe;      /* Packet contents */
	Word           PktType;      /* Always 3 */
	TTimeStamp     PktDate;      /* When the packet was created */
	Word           ProdCode;     /* FTSC Product Code */
	Byte           MajorVer;     /* Major product version */
	Byte           MinorVer;     /* Minor product version */
	Byte           Org[16];      /* Organization */
	CapabilityWord CapWord;      /* Capability Word */
	Byte           Password[8];  /* Packet password */
	Byte           ExtraInfo[4]; /* Reserved for future extension */
} PKTheader;

typedef struct
{
	Word       HeadSize;     /* Size of the message header */
	TMsgFlags  MsgFlags;     /* Message flags */
	TTimeStamp MsgDate;      /* When the message was created */
	Longword   MsgID;        /* Unique message identifier */
	Longword   ReplyID;      /* Reply linkage information */
	Longword   MsgLength;    /* Length of the message in bytes */
	TAddress   MsgOrig;      /* The node who created this message */
	TAddress   MsgDest;      /* The node who should receive this message */
	Byte       CharSet;      /* Character set */
	Byte       MsgType;      /* Type of MsgData */
} PackedMSGheader;

typedef struct
{
	TTimeStamp      SRdate;          /* When message was sent/recived */
	TLocalFlags     LocalFlags;      /* Local flags */
	Longword        ReplyTo;         /* Message which this replies */
	Longword        Reply1st;        /* First message which replies to this */
	Longword        ReplyNext;       /* Next reply */
	Word            Cost;            /* In the lowest currency unit */
	PackedMSGheader PMH;             /* Same as packed MSG */
} StoredMSGheader;

typedef struct
{
	Word    LastRead;       /* The last message read */
	Word    HighRead;       /* The highest message read */
	Word    HighWater;      /* High-water mark */
} ControlFileStr;

/* Text attributes etc */
#define TurnOff     0x03
#define Bold        0x04
#define Italic      0x05
#define Underline   0x06
#define AllCaps     0x17
#define Subscript   0x19
#define Superscript 0x1A
#define Blinking    0x1C
#define Inverted    0x1D
#define Concealed   0x1E
#define Quote       0x1F
#define BinExtShort 0x15
#define BinExtLong  0x00
#define ExtLine     0x01
