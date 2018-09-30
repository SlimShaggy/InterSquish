/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                                                                          */
/*      ------------         Bit-Bucket Software, Co.                       */
/*      \ 10001101 /         Writers and Distributors of                    */
/*       \ 011110 /          Freely Available<tm> Software.                 */
/*        \ 1011 /                                                          */
/*         ------                                                           */
/*                                                                          */
/*  (C) Copyright 1987-91, Bit Bucket Software Co., a Delaware Corporation. */
/*                                                                          */
/*                                                                          */
/*               This module was written by Vince Perriello                 */
/*                                                                          */
/*                                                                          */
/*                     BinkleyTerm "YooHoo" Processor                       */
/*                                                                          */
/*                                                                          */
/*    For complete  details  of the licensing restrictions, please refer    */
/*    to the License  agreement,  which  is published in its entirety in    */
/*    the MAKEFILE and BT.C, and also contained in the file LICENSE.250.    */
/*                                                                          */
/*    USE  OF THIS FILE IS SUBJECT TO THE  RESTRICTIONS CONTAINED IN THE    */
/*    BINKLEYTERM  LICENSING  AGREEMENT.  IF YOU DO NOT FIND THE TEXT OF    */
/*    THIS  AGREEMENT IN ANY OF THE  AFOREMENTIONED FILES,  OR IF YOU DO    */
/*    NOT HAVE THESE FILES,  YOU  SHOULD  IMMEDIATELY CONTACT BIT BUCKET    */
/*    SOFTWARE CO.  AT ONE OF THE  ADDRESSES  LISTED BELOW.  IN NO EVENT    */
/*    SHOULD YOU  PROCEED TO USE THIS FILE  WITHOUT HAVING  ACCEPTED THE    */
/*    TERMS  OF  THE  BINKLEYTERM  LICENSING  AGREEMENT,  OR  SUCH OTHER    */
/*    AGREEMENT AS YOU ARE ABLE TO REACH WITH BIT BUCKET SOFTWARE, CO.      */
/*                                                                          */
/*                                                                          */
/* You can contact Bit Bucket Software Co. at any one of the following      */
/* addresses:                                                               */
/*                                                                          */
/* Bit Bucket Software Co.        FidoNet  1:104/501, 1:132/491             */
/* P.O. Box 460398                AlterNet 7:491/0                          */
/* Aurora, CO 80046               BBS-Net  86:2030/1                        */
/*                                Internet f491.n132.z1.fidonet.org         */
/*                                                                          */
/* Please feel free to contact us at any time to share your comments about  */
/* our software and/or licensing policies.                                  */
/*                                                                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/

/* Include this file before any other includes or defines! */

#include "includes.h"


int Send_Hello_Packet (int);
int Recv_Hello_Packet (int);

/*
 * Data structure used by all YooHoo state machine functions.
 * Contains all data which needs to be passed between various states.
 *
 */

typedef struct {
   long timer1;                         /* Outermost timer                  */
   long timer2;                         /* Next inner timer                 */
   long timer3;                         /* Next inner timer                 */
   struct _Hello Hello;                 /* Data packet                      */
   word crc;                            /* CRC of data packet               */
   word hiscrc;                         /* other's CRC of data packet       */
   int sender;                          /* Set to 1 if we're calling him    */
   int result;                          /* Result we want to send out       */
   int retries;                         /* Number of retries                */
   int count;                           /* Number of characters received    */
} YHARGS, *YHARGSP;

int YRInit (YHARGSP, int);              /* Called by state machine at start */
int YRExit (YHARGSP, int);              /* Called by state machine at end   */
int YRGetHello (YHARGSP);               /* YR1 state processing function    */
int YRWaitResp (YHARGSP);               /* YR2 state processing function    */
int YRPollPeer (YHARGSP);               /* YR3 state processing function    */
int YRSndHello (YHARGSP);               /* YR4 state processing function    */

int YSInit (YHARGSP, int);              /* Called by state machine at start */
int YSExit (YHARGSP, int);              /* Called by state machine at end   */
int YSSndHello (YHARGSP);               /* YS1 state processing function    */
int YSWaitResp (YHARGSP);               /* YS2 state processing function    */
int YSGetHello (YHARGSP);               /* YS3 state processing function    */

int SHInit (YHARGSP, int);              /* Called by state machine at start */
int SHExit (YHARGSP, int);              /* Called by state machine at end   */
int SHInitSend (YHARGSP);               /* SH1 state processing function    */
int SHSendHedr (YHARGSP);               /* SH2 state processing function    */
int SHSendCRC (YHARGSP);                /* SH3 state processing function    */
int SHGetResp (YHARGSP);                /* SH4 state processing function    */

int RHInit (YHARGSP, int);              /* Called by state machine at start */
int RHExit (YHARGSP, int);              /* Called by state machine at end   */
int RHSendENQ (YHARGSP);                /* RH1 state processing function    */
int RHWaitHedr (YHARGSP);               /* RH2 state processing function    */
int RHTossJunk (YHARGSP);               /* RH3 state processing function    */
int RHReSynch (YHARGSP);                /* RH4 state processing function    */
int RHHdrSetup (YHARGSP);               /* RH5 state processing function    */
int RHGetHChar (YHARGSP);               /* RH6 state processing function    */
int RHStoHChar (YHARGSP);               /* RH7 state processing function    */
int RHCheckCRC (YHARGSP);               /* RH8 state processing function    */
int RHCountERR (YHARGSP);               /* RH9 state processing function    */
int RHHelloOK (YHARGSP);                /* RH10 state processing function   */

#define YR0    0                        /* Reserved value of 0 for init     */
#define YRexit 0                        /* Slot 1 is exit, but called by 0  */
#define YR1    2                        /* First "user" slot is 2.          */
#define YR2    3                        /* After that, it all maps n : n+1  */
#define YR3    4
#define YR4    5

#define YS0    0                        /* Reserved value of 0 for init     */
#define YSexit 0                        /* Slot 1 is exit, but called by 0  */
#define YS1    2                        /* First "user" slot is 2.          */
#define YS2    3                        /* After that, it all maps n : n+1  */
#define YS3    4

#define SH0    0                        /* Reserved value of 0 for init     */
#define SHexit 0                        /* Slot 1 is exit, but called by 0  */
#define SH1    2                        /* First "user" slot is 2.          */
#define SH2    3                        /* After that, it all maps n : n+1  */
#define SH3    4
#define SH4    5

#define RH0    0                        /* Reserved value of 0 for init     */
#define RHexit 0                        /* Slot 1 is exit, but called by 0  */
#define RH1    2                        /* First "user" slot is 2.          */
#define RH2    3                        /* After that, it all maps n : n+1  */
#define RH3    4
#define RH4    5
#define RH5    6
#define RH6    7
#define RH7    8
#define RH8    9
#define RH9    10
#define RH10   11

STATES YooHoo_Rcvr [] = {               /* Table used by state machine      */
   { "YRInit",     YRInit     },        /* And referred to by 'YRn' defines */
   { "YRExit",     YRExit     },        /* listed above ...                 */
   { "YRGetHello", YRGetHello },
   { "YRWaitResp", YRWaitResp },
   { "YRPollPeer", YRPollPeer },
   { "YRSndHello", YRSndHello },
};

STATES YooHoo_Sndr [] = {               /* Table used by state machine      */
   { "YSInit",     YSInit     },        /* And referred to by 'YRn' defines */
   { "YSExit",     YSExit     },        /* listed above ...                 */
   { "YSSndHello", YSSndHello },
   { "YSWaitResp", YSWaitResp },
   { "YSGetHello", YSGetHello },
};

STATES Snd_Hello [] = {                 /* Table used by state machine      */
   { "SHInit",     SHInit     },        /* And referred to by 'SHn' defines */
   { "SHExit",     SHExit     },        /* listed above ...                 */
   { "SHInitSend", SHInitSend },
   { "SHSendHedr", SHSendHedr },
   { "SHSendCRC",  SHSendCRC  },
   { "SHGetResp",  SHGetResp  },
};

STATES Rcv_Hello [] = {                 /* Table used by state machine      */
   { "RHInit",      RHInit     },       /* And referred to by 'RHn' defines */
   { "RHExit",      RHExit     },       /* listed above ...                 */
   { "RHSendENQ",   RHSendENQ  },
   { "RHWaitHedr",  RHWaitHedr },
   { "RHTossJunk",  RHTossJunk },
   { "RHReSynch",   RHReSynch  },
   { "RHHdrSetup",  RHHdrSetup },
   { "RHGetHChar",  RHGetHChar },
   { "RHStoHChar",  RHStoHChar },
   { "RHCheckCRC",  RHCheckCRC },
   { "RHCountERR",  RHCountERR },
   { "RHHelloOK",   RHHelloOK  },
};

/*--------------------------------------------------------------------------*/
/* YOOHOO SENDER    (used when I am the CALLING system)                     */
/*--------------------------------------------------------------------------*/
int YooHoo_Sender (void)
{
   YHARGS args;
   int res;

   args.result = 0;

   res = state_machine (YooHoo_Sndr, &args, 2);
   return (res);
}


int YSInit (YHARGSP args, int start_state)
{

    if (un_attended && fullscreen)
        {
        sb_move (file_hWnd, 2, 2);
        FlLnModeSet (FILE_LN_2, 0);
        sb_puts (GetDlgItem (file_hWnd, FILE_LN_2), "YooHoo");
        sb_show ();
        }
    else
        {
        set_xy ("YooHoo ");
        }

   /*--------------------------------------------------------------------*/
   /* Clean up any mess that may be around                               */
   /*--------------------------------------------------------------------*/

    CLEAR_OUTBOUND ();
    CLEAR_INBOUND ();
    XON_DISABLE ();

    happy_compiler = args->result + start_state;
   
    return (YS1);
}

/*
 * This routine is called by the state machine when the '??exit'
 * state is seen. Its return value is what the state machine
 * will return to its caller as the result of the function.
 *
 */
 
int YSExit (YHARGSP args, int cur_state)
{
    happy_compiler = cur_state;  /* Makes the compiler happy! */
    return (args->result);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | YS1 | SndHello | Successful              | Looks like WaZOO        | YS2 |
 |     | (state   +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |  SH1)    | Not successful          | Repeat whole thing      | exit|
 `-----+----------+-------------------------+-------------------------+-----'
*/
int YSSndHello (YHARGSP args)
{
    if (!Send_Hello_Packet (1))
        {
        status_line (MSG_TXT(M_HE_HUNG_UP));
        return (YSexit);
        }

    happy_compiler = args->result;
    return (YS2);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | YS2 | WaitResp | 30 sec timer expires    | repeat whole thing      | exit|
 |     |          | or lost carrier         |                         |     |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | Received YOOHOO         | Another WaZOO, go       | YS3 |
 |     |          |                         | process receive         |     |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | Received debris         | Repeat whole thing      | YS2 |
 `-----+----------+-------------------------+-------------------------+-----'
*/
int YSWaitResp (YHARGSP args)
{
    long resp_timer = timerset (3000);

    while (TIMED_READ (5) != YOOHOO)
        {
        if (timeup (resp_timer))
            {
            status_line ("!No YOOHOO/2U2");
            status_line (IDUNNO_msg);
            return (YSexit);
            }
        }

    happy_compiler = args->result;
    return (YS3);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | YS3 | GetHello | Information             | Report Success          | exit|
 |     | (state   | Successfully            |                         |     |
 |     |  RH1)    | Exchanged               |                         |     |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | Failure                 | Repeat whole thing      | exit|
 `-----+----------+-------------------------+-------------------------+-----'
*/
int YSGetHello (YHARGSP args)
{
    args->result = Recv_Hello_Packet (1);
    return (YSexit);
}



/*--------------------------------------------------------------------------*/
/* YOOHOO RECEIVER  (Used when I am the CALLED system)                      */
/*--------------------------------------------------------------------------*/

int YooHoo_Receiver (void)
{
    YHARGS args;
    int res;

    args.result = 0;

    res = state_machine (YooHoo_Rcvr, &args, 2);
    return (res);
}

int YRInit (YHARGSP args, int start_state)
{

    if (un_attended && fullscreen)
        {
        sb_move (file_hWnd, 2, 2);
        FlLnModeSet (FILE_LN_2, 0);
        sb_puts (GetDlgItem (file_hWnd, FILE_LN_2), "YooHoo");
        sb_show ();
        }
    else
        {
        set_xy ("YooHoo ");
        }

   /*--------------------------------------------------------------------*/
   /* Clean up any mess that may be around                               */
   /*--------------------------------------------------------------------*/

    CLEAR_OUTBOUND ();
    CLEAR_INBOUND ();
    XON_DISABLE ();

    happy_compiler = args->result + start_state;

    return (YR1);
}

/*
 * This routine is called by the state machine when the '??exit'
 * state is seen. Its return value is what the state machine
 * will return to its caller as the result of the function.
 *
 */

int YRExit (YHARGSP args, int cur_state)
{
    happy_compiler = cur_state;  /* Makes the compiler happy! */
    return (args->result);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | YR1 | GetHello | Information             | Start 20 sec timer      | YR2 |
 |     | (state   | Successfully            | Initialize retry count  |     |
 |     |  RH1)    | Exchanged               | Send YooHoo             |     |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | Failure                 | Repeat whole thing      | exit|
 `-----+----------+-------------------------+-------------------------+-----'
*/
int YRGetHello (YHARGSP args)
{
    if (Recv_Hello_Packet(0) == 0)
        return (YRexit);
    args->timer1 = timerset (2000);
    args->retries = 0;
    SENDBYTE (YOOHOO);
    return (YR2);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | YR2 | WaitResp | 20 sec timeout          | try again               | YR3 |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | Lost carrier            | Failure                 | exit|
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | Received ENQ            | Go send hello           | YR4 |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | Received debris         | Keep looking            | YR2 |
 `-----+----------+-------------------------+-------------------------+-----'
*/
int YRWaitResp (YHARGSP args)
{
    while (TIMED_READ (5) != ENQ)
        {
        if (!CARRIER)
            {
            status_line (MSG_TXT(M_NO_CARRIER));
            return (YRexit);
            }
        if (timeup (args->timer1))
            return (YR3);
        }
    return (YR4);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | YR3 | PollPeer | More than 3 retries     | Give it up              | exit|
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | Less than 3 retries     | Bump retry count        | YR2 |
 |     |          |                         | Clear input buffer      |     |
 |     |          |                         | Send YOOHOO             |     |
 |     |          |                         | Restart 20 sec timer    |     |
 `-----+----------+-------------------------+-------------------------+-----'
*/
int YRPollPeer (YHARGSP args)
{
    if (++(args->retries) > 3)
        {
        status_line (MSG_TXT(M_FUBAR_MSG));
        b_init ();
        return (YRexit);
        }

    CLEAR_INBOUND ();
    SENDBYTE (YOOHOO);
    args->timer1 = timerset (2000);
    return (YR2);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | YR4 | SndHello | Successful              | All done, report success| exit|
 |     | (state   +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |  SH1)    | Not successful          | Repeat whole thing      | exit|
 `-----+----------+-------------------------+-------------------------+-----'
*/
int YRSndHello (YHARGSP args)
{
    if ((args->result = Send_Hello_Packet (0)) == 0)
        b_init ();
    return (YRexit);
}


/*--------------------------------------------------------------------------*/
/* SEND HELLO PACKET                                                        */
/*--------------------------------------------------------------------------*/
int Send_Hello_Packet (int Sender)
{
   YHARGS args;
   int res;

   args.result = 0;
   args.sender = Sender;

   res = state_machine (Snd_Hello, &args, 2);
   return (res);
}

int SHInit (YHARGSP args, int start_state)
{
    happy_compiler = args->result + start_state;
   
    return (SH1);
}

/*
 * This routine is called by the state machine when the '??exit'
 * state is seen. Its return value is what the state machine
 * will return to its caller as the result of the function.
 *
 */
 
int SHExit (YHARGSP args, int cur_state)
{
    happy_compiler = cur_state;  /* Makes the compiler happy! */
    return (args->result);
}

/*
 .-----+----------+-------------------------+-------------------------+-----.
 | SH1 | InitSend |                         | Disable XON/XOFF        | SH2 |
 |     |          |                         | Set retry count to 0    |     |
 `-----+----------+-------------------------+-------------------------+-----'
*/
int SHInitSend (YHARGSP args)
{

   XON_DISABLE ();
   args->retries = 0;

   return (SH2);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | SH2 | SendHedr |                         | Send Hex 1f, then       | SH3 |
 |     |          |                         | Send HELLO struct       |     |
 `-----+----------+-------------------------+-------------------------+-----'
*/
int SHSendHedr (YHARGSP args)
{
    word can_do_domain = 0;
    word crc;
    char *sptr;
    int i;

   /*--------------------------------------------------------------------*/
   /* Setup HELLO structure                                              */
   /*--------------------------------------------------------------------*/

    (void) memset ((char *) &args->Hello, 0, sizeof (struct _Hello));

    args->Hello.signal = 'o';
    args->Hello.hello_version = 1;

    args->Hello.product = PRDCT_CODE;
    args->Hello.product_maj = BINK_MAJVERSION;
    args->Hello.product_min = BINK_MINVERSION;

    (void) strncpy (args->Hello.sysop, sysop, 19);
    args->Hello.sysop[19] = '\0';

    args->Hello.my_zone = alias[assumed].Zone;
    if ((pvtnet >= 0) && (args->sender) &&
        ((called_addr.Zone == boss_addr.Zone) || (called_addr.Zone == 0) || (boss_addr.Zone == 0)) &&
        (called_addr.Net == boss_addr.Net) && (called_addr.Node == boss_addr.Node) &&
        ((called_addr.Domain == boss_addr.Domain) || (boss_addr.Domain == NULL) || (called_addr.Domain == NULL)))
        {
        args->Hello.my_net = boss_addr.Net;
        args->Hello.my_node = boss_addr.Node;
        args->Hello.my_point = alias[assumed].Node;
        }
    else
        {
        args->Hello.my_net = alias[assumed].Net;
        args->Hello.my_node = alias[assumed].Node;
        args->Hello.my_point = alias[assumed].Point;
        }
/*
 * If we are the calling system, turn on all our capabilities.
 * If we are the called system, choose from the set that the
 * caller gave us, and only send the one we prefer.
 */
    can_do_domain = (my_addr.Domain != NULL) ? DO_DOMAIN : 0;
    if (args->sender == 0)
        {
        can_do_domain = remote_capabilities & can_do_domain;
        if (remote_capabilities & my_capabilities & DOES_IANUS)
            args->Hello.capabilities = DOES_IANUS;
        else if (remote_capabilities & my_capabilities & ZED_ZAPPER)
            args->Hello.capabilities = ZED_ZAPPER;
        else if (remote_capabilities & my_capabilities & ZED_ZIPPER)
            args->Hello.capabilities = ZED_ZIPPER;
        else if (remote_capabilities & my_capabilities & Y_DIETIFNA)
            args->Hello.capabilities = Y_DIETIFNA;
        }
    else args->Hello.capabilities = my_capabilities;

    (void) strncpy (args->Hello.my_name, system_name, 58);
    args->Hello.my_name[58] = '\0';
    args->Hello.capabilities |= can_do_domain;
    if (can_do_domain && (alias[assumed].Domain != NULL))
        {
        if (strlen (system_name) + strlen (alias[assumed].Domain) > 57)
            {
            args->Hello.my_name[57 - strlen (alias[assumed].Domain)] = '\0';
            }
        sptr = args->Hello.my_name + strlen (args->Hello.my_name) + 1;
        (void) strcpy (sptr, alias[assumed].Domain);
        }

    if (n_getpassword (&remote_addr))
        {
        (void) strncpy ((char *)(args->Hello.my_password), remote_password, 8);
        }

    if ((matrix_mask & TAKE_REQ) &&
       ((args->sender == 0) || (on_our_nickel)))
        args->Hello.capabilities |= WZ_FREQ;


   /*--------------------------------------------------------------------*/
   /* Send the packet.                                                   */
   /* Load outbound buffer quickly, and get modem busy sending.          */
   /*--------------------------------------------------------------------*/

    SENDBYTE (0x1f);
    sptr = (char *) (&args->Hello);
    SENDCHARS (sptr, 128, 1);

   /*--------------------------------------------------------------------*/
   /* Calculate CRC while modem is sending its buffer                    */
   /*--------------------------------------------------------------------*/

    for (crc = i = 0; i < 128; i++)
        {
        crc = xcrc (crc, (byte) sptr[i]);
        }

    args->crc = crc;
    return (SH3);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | SH3 | SendCRC  |                         | Clear Input Buffer      | SH4 |
 |     |          |                         | Send two-byte CRC of pkt|     |
 |     |          |                         | MSB followed by LSB     |     |
 |     |          |                         | Start 40 second timer   |     |
 `-----+----------+-------------------------+-------------------------+-----'
*/
SHSendCRC (YHARGSP args)
{
    CLEAR_INBOUND ();

    SENDBYTE ((unsigned char) (args->crc >> 8));
    SENDBYTE ((unsigned char) (args->crc & 0xff));

    args->timer1 = timerset (4000);
    return (SH4);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | SH4 | GetResp  | 40 second timer expires | Failed to send packet   | exit|
 |     |          | or carrier lost         |                         |     |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | ACK received            | Successful transmission | exit|
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | '?' received            | Error, try retransmit   | SH2 |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | ENQ received            | Out of sync?            | SH2 |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | other character recvd   | Debris, keep watching   | SH4 |
 `-----+----------+-------------------------+-------------------------+-----'
*/
SHGetResp (YHARGSP args)
{
    int i;
    char junkbuff [80];

    while ((i = TIMED_READ (5)) != ACK)
        {
        if (timeup (args->timer1))
            {
            (void) sprintf (junkbuff, "!%s",MSG_TXT(M_TIMEOUT));
            status_line (junkbuff);
            return (SHexit);
            }

        if (!CARRIER)
            {
            status_line (MSG_TXT(M_NO_CARRIER));
            return (SHexit);
            }

        if (got_ESC ())
            {
            LOWER_DTR ();
            status_line (MSG_TXT(M_KBD_MSG));
            return (SHexit);
            }

        switch (i)
            {
            case '?':
            status_line (MSG_TXT(M_DRATS));

            case ENQ:
            if (++(args->retries) == 10)
                {
                status_line (MSG_TXT(M_FUBAR_MSG));
                return (SHexit);
                }
            CLEAR_INBOUND ();
            return (SH2);
            default:
            break;
            }
        }

   args->result = 1;
   return (SHexit);
}



/*--------------------------------------------------------------------------*/
/* RECEIVE HELLO PACKET                                                     */
/*--------------------------------------------------------------------------*/
int Recv_Hello_Packet (int Sender)
{
   YHARGS args;
   int res;

   args.result = 0;
   args.sender = Sender;

   res = state_machine (Rcv_Hello, &args, 2);
   return (res);
}

int RHInit (YHARGSP args, int start_state)
{
    happy_compiler = args->result + start_state;
   
    return (RH1);
}

/*
 * This routine is called by the state machine when the '??exit'
 * state is seen. Its return value is what the state machine
 * will return to its caller as the result of the function.
 *
 */

int RHExit (YHARGSP args, int cur_state)
{
    happy_compiler = cur_state;  /* Makes the compiler happy! */
    if (args->result == 0)
        b_init ();
    return (args->result);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | RH1 | SendENQ  |                         | Start 2 minute timer    | RH2 |
 |     |          |                         | Send an ENQ character   |     |
 `-----+----------+-------------------------+-------------------------+-----'
*/
int RHSendENQ (YHARGSP args)
{
    if (un_attended && fullscreen)
        {
        sb_move (file_hWnd, 2, 2);
        FlLnModeSet (FILE_LN_2, 0);
        sb_puts (GetDlgItem (file_hWnd, FILE_LN_2), "YooHoo/2U2");
        sb_show ();
        }
    else
        {
        set_xy ("YooHoo/2U2 ");
        }

    SENDBYTE (ENQ);                              /* Let the other system know
                                                  * we heard YooHoo. */

    args->timer1 = timerset (12000);             /* No more than 2 mins! */
    args->timer2 = 0L;
    args->retries = 0;
    return (RH2);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | RH2 | WaitHedr | 2 minute timer expires  | Report failure          | exit|
 |     |          | or carrier lost         |                         |     |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | Received Hex 1f         | Got header, get packet  | RH5 |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | Received other char     | Debris, throw away      | RH3 |
 |     |          |                         | Start 10 sec timer      |     |
 `-----+----------+-------------------------+-------------------------+-----'
*/
int RHWaitHedr (YHARGSP args)
{
    int i;
    char junkbuff [80];

    while ((i = TIMED_READ (5)) != 0x1f)
        {
        if (!CARRIER)
            {
            status_line (MSG_TXT(M_NO_CARRIER));
            return (RHexit);
            }

        if (got_ESC ())
            {
            status_line (MSG_TXT(M_KBD_MSG));
            return (RHexit);
            }

        if (timeup (args->timer1))
            {
            (void) sprintf (junkbuff, "!%s",MSG_TXT(M_TIMEOUT));
            status_line (junkbuff);
            return (RHexit);
            }

        if (i != 0xff)
            {
            if (args->timer2 == 0L)
               args->timer2 = timerset (1000);
            return (RH3);
            }
		}
    return (RH5);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | RH3 | TossJunk | 10 sec timer expires    | Too much noise          | RH4 |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | Received Hex 1f         | Got header, get packet  | RH5 |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | Input buffer empty      | Try to resynch          | RH4 |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | Carrier lost            | Report failure          | exit|
 `-----+----------+-------------------------+-------------------------+-----'
*/
int RHTossJunk (YHARGSP args)
{
    while (!timeup (args->timer2))
        {
        if (got_ESC ())
            {
            status_line (MSG_TXT(M_KBD_MSG));
            return (RHexit);
            }

        if (!CHAR_AVAIL ())
            return (RH4);

        if (TIMED_READ (0) == 0x1f)
            return (RH5);

        if (!CARRIER)
            {
            status_line (MSG_TXT(M_NO_CARRIER));
            return (RHexit);
            }
        }
    return (RH4);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | RH4 | ReSynch  |                         | Clear input buffer      | RH2 |
 |     |          |                         | Send ENQ                |     |
 `-----+----------+-------------------------+-------------------------+-----'
*/
int RHReSynch (YHARGSP args)
{
    CLEAR_INBOUND ();
    SENDBYTE (ENQ);
    args->timer2 = 0L;
    return (RH2);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | RH5 | HdrSetup |                         | Initialize CRC          |     |
 |     |          |                         | Set 30 second timer     | RH6 |
 `-----+----------+-------------------------+-------------------------+-----'
*/
int RHHdrSetup (YHARGSP args)
{
    (void) memset ((char *) &args->Hello, 0, sizeof (struct _Hello));
    args->crc = args->count = 0;
    args->timer3 = timerset (3000);
    return (RH6);
}    
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | RH6 | GetHChar | 30 sec timer expires or |                         |     |
 |     |          | carrier lost            | Report failure          | exit|
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | Character received      | Process character       | RH7 |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | 10 seconds with no char | Error, try resync       | RH9 |
 `-----+----------+-------------------------+-------------------------+-----'
*/
int RHGetHChar (YHARGSP args)
{
    long localtimer;
    char junkbuff [80];

    localtimer = timerset (1000);

    while (PEEKBYTE () < 0)
        {
        if (timeup (args->timer3))
            {
            (void) sprintf (junkbuff, "!%s",MSG_TXT(M_TIMEOUT));
            status_line (junkbuff);
            return (RHexit);
            }

        if (timeup (localtimer))
            return (RH9);
      
        if (got_ESC ())
            {
            status_line (MSG_TXT(M_KBD_MSG));
            return (RHexit);
            }

        if (!CARRIER)
            {
            status_line (MSG_TXT(M_NO_CARRIER));
            return (RHexit);
            }

       time_release ();
       }
    return (RH7);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | RH7 | StoHChar | Buffer and CRC filled   | Compare CRC             | RH8 |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | More characters needed  | Reset 30 sec timer      | RH6 |
 `-----+----------+-------------------------+-------------------------+-----'
*/
int RHStoHChar (YHARGSP args)
{
    int c;
    int i;
    char *sptr = (char *)&(args->Hello);

    while (PEEKBYTE () >= 0)
        {
        c = TIMED_READ (0);
        switch (i = args->count)
            {
            case 128:
            args->hiscrc = c << 8;
            args->count++;
            break;

            case 129:
            args->hiscrc += c;
            return (RH8);

            default:
            sptr [i] = (char)c;
            args->crc = xcrc (args->crc, (byte) c);
            args->count++;
            break;
            }
        }
    args->timer3 = timerset (3000);
    return (RH6);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | RH8 | CheckCRC | CRC matches             | Finish Receive          | RH10|
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | CRC doesn't match       | Handle error            | RH9 |
 `-----+----------+-------------------------+-------------------------+-----'
*/
int RHCheckCRC (YHARGSP args)
{
    char junkbuff [80];

    if (args->crc == args->hiscrc)
        return (RH10);

    (void) sprintf (junkbuff, "!%s", MSG_TXT(M_CRC_MSG));
    status_line (junkbuff);
    return (RH9);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | RH9 | CountERR | Less than 10 errors     | Send '?' (0x3f)         | RH2 |
 |     |          +- - - - - - - - - - - - -+- - - - - - - - - - - - -+- - -|
 |     |          | 10 errors               | Hang up, report failure | exit|
 `-----+----------+-------------------------+-------------------------+-----'
*/
int RHCountERR (YHARGSP args)
{
    if ((args->retries++) < 10)
        {
        CLEAR_INBOUND ();
        SENDBYTE ('?');
        return (RH2);
        }

    status_line (MSG_TXT(M_FUBAR_MSG));
    return (RHexit);
}
/*
 .-----+----------+-------------------------+-------------------------+-----.
 | RH10| HelloOK  |                         | Clear inbound buffer    | exit|
 |     |          |                         | Send ACK                |     |
 `-----+----------+-------------------------+-------------------------+-----'
*/
int RHHelloOK (YHARGSP args)
{
    char *p;
    char junkbuff [128];
    ADDR his_boss;
    int j;

   /* The idea for removing junk characters came from Holger Schurig */
   /* Get rid of junk characters */

    for (p = args->Hello.my_name; *p != '\0'; p++)
        if (*p < ' ')
            *p = ' ';

   /* Get rid of junk characters */
 
    for (p = args->Hello.sysop; *p != '\0'; p++)
        if (*p < ' ')
            *p = ' ';

    remote_addr.Zone = args->Hello.my_zone;
    remote_addr.Net = args->Hello.my_net;
    remote_addr.Node = args->Hello.my_node;
    remote_addr.Point = args->Hello.my_point;

    if ((args->Hello.capabilities & DO_DOMAIN) && (my_addr.Domain != NULL))
        {
        remote_addr.Domain = find_domain (&(args->Hello.my_name[strlen (args->Hello.my_name) + 1]));
        }
    else
        remote_addr.Domain = NULL;


    if (strlen (args->Hello.my_name) > 42)
        args->Hello.my_name[42] = '\0';

    args->Hello.sysop[19] = '\0';

    remote_capabilities = args->Hello.capabilities;

    his_boss = remote_addr;
    his_boss.Point = 0;

    if (nodefind (&his_boss, 0) && !remote_addr.Zone)
        remote_addr.Zone = found_zone;

    (void) sprintf (junkbuff, "*%s (%s)",
             args->Hello.my_name,
             Full_Addr_Str (&remote_addr));
    status_line (junkbuff);

    if ((pvtnet >= 0) &&
        ((remote_addr.Zone == alias[assumed].Zone) || (remote_addr.Zone == 0)) &&
        (remote_addr.Net == boss_addr.Net) && (remote_addr.Node == boss_addr.Node) &&
        (remote_addr.Point > 0))
        {
        remote_addr.Net = pvtnet;
        remote_addr.Node = args->Hello.my_point;
        remote_addr.Point = 0;
        }

    log_product (args->Hello.product, args->Hello.product_maj, args->Hello.product_min);

#ifdef MILQ
    if (isMILQUE == args->Hello.product)
        {
        UsePaths = TRUE;
        status_line (" Paths Will Be Used");
        }
#endif

    if (args->Hello.sysop[0])
        status_line (":Sysop: %s", args->Hello.sysop);

    if ((pvtnet >= 0) && (remote_addr.Point > 0))
        {
        remote_addr.Point = 0;
        remote_addr.Node = (unsigned int) -1;
        }

    if (n_getpassword (&remote_addr))
        {
        if ((j = n_password ((char *)args->Hello.my_password, remote_password)) != 0)
            {
            if ((j == 1) || ((j == 2) && (args->sender == 0)))
                {
                LOWER_DTR ();                          /* He'll never get it right */
                timer (2);                             /* Wait two secs */
                return (RHexit);
                }
            else
                {
                status_line (MSG_TXT(M_PASSWORD_OVERRIDE));
                }
            }
        }

    CLEAR_INBOUND ();
    SENDBYTE (ACK);

    args->result = 1;
    return (RHexit);
}
