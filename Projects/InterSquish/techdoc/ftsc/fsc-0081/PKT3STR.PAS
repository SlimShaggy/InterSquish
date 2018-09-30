(* Structures for TYPE-3 in Pascal *)

/* You may have to change the order of the components in the sets */
/* You probably have to if using a Motorola CPU, this is for Intel */

TYPE
    Longword = Longint; (* Please note that Longint in Pascal is signed, *)
                        (* it should be unsigned. *)

	TAddress = RECORD
		Zone: Word; (* Zone address *)
		Net: Word; (* Net address *)
		Node: Word; (* Node address *)
		Point: Word; (* Point address or zero if boss *)
	END;

    CWtype =
	(Type2, Type3, Type4, Type5, Type6, Type7, Type8, Type9,
	 Type10, Type11, Type12, Type13, Type14, Type15, Type16, RFC822);

	CapabilityWord = SET OF CWtype;

	TTimeStamp = Longword;

	FlagType =
		(Pvt (* Private message *),
		 FileAttach (* File attach message *),
		 FileReq (* File request message *),
		 UpdReq (* File update request message *),
		 Direct (* Do not route this message *),
		 Crash  (* High-priority mail *),
		 Hold (* Hold for pickup *),
		 IMM (* Immediate mail *),
		 RRQ (* Return receipt request *),
		 CRQ (* Confirm receipt request *),
		 IRR (* Is return receipt *),
		 Machine (* Message to a program *),
		 NoForCC (* CC in NetMail, NoForward in EchoMail *),
		 Permanent (* Message should not be pruged by age *),
		 Foreign (* Message is from another organization *),
		 reserved15 (* Reserved for future extension *));

	TMsgFlags = SET OF FlagType;

	LocalFlagType =
		(Local (* Message is created localy *),
		 InTransit (* Message is not destinated for this system *),
		 Orphan (* Unknown destination *),
		 KillSent (* Remove message after it has been sent *),
		 DelSent (* Delete attached file(s) after they have been sent *),
		 TruncSent (* Truncate attached file(s) after they have been sent *),
		 Sent (* Message has been sent *),
		 IsRead (* Message has been read by the SysOp *),
		 Rcvd (* Message has been read by its addressee *),
		 LockMsg (* Lock the message for further access *),
		 DontSend (* Do not send the actual message *),
		 unused11 (* Reserved for future extension *),
		 unused12 (* Reserved for future extension *),
		 unused13 (* Reserved for future extension *),
		 unused14 (* Reserved for future extension *),
		 unused15 (* Reserved for future extension *));

	TLocalFlags = SET OF LocalFlagType;

	TPKTheader = RECORD
		PktOrig: TAddress; (* The node who created this packet *)
		PktDest: TAddress; (* The node who should receive this packet *)
		SubType: Word; (* Packet contents *)
		PktType: Word; (* Always 3 *)
		PktDate: TTimeStamp; (* When the packet was created *)
		ProdCode: Word; (* FTSC Product Code *)
		MajorVer: Byte; (* Major product version *)
		MinorVer: Byte; (* Minor product version *)
		Org: ARRAY[0..15] OF Char; (* Organization *)
		CapWord: CapabilityWord; (* Capability Word *)
		Password: ARRAY[0..7] OF Char; (* Packet password *)
		ExtraInfo: ARRAY[1..4] OF Char; (* Reserved for future extension *)
	END;

	TPackedMSGheader = RECORD
		HeadSize: Word; (* Size of the message header *)
		MsgFlags: TMsgFlags; (* Message flags *)
		MsgDate: TTimeStamp; (* When the message was created *)
		MsgID: Longword; (* Unique message identifier *)
		ReplyID: Longword; (* Reply linkage information *)
		MsgLength: Longword; (* Length of the message in bytes *)
		MsgOrig: TAddress; (* The node who created this message *)
		MsgDest: TAddress; (* The node who should receive this message *)
		CharSet: Byte; (* Character set *)
		MsgType: Byte; (* Type of MsgData *)
	END;

	TStoredMSGheader = RECORD
		SRdate: TTimeStamp; (* When the message was sent or recived *)
		LocalFlags: TLocalFlags; (* Local flags *)
		ReplyTo: Longword; (* Message which this replies *)
		Reply1st: Longword; (* First message which replies to this *)
		ReplyNext: Longword; (* Next reply *)
		Cost: Word; (* In the lowest currency unit *)
		PMH: TPackedMSGheader; (* Same as packed MSG *)
	END;

	TControlFileStr = RECORD
		LastRead: Word; (* The last message read *)
		HighRead: Word; (* The highest message read *)
		HighWater: Word; (* High-water mark *)
	END;

CONST (* Text attributes etc *)
	TurnOff = $03;
	Bold = $04;
	Italic = $05;
	Underline = $06;
	AllCaps = $17;
	Subscript = $19;
	Superscript = $1A;
	Blinking = $1C;
	Inverted = $1D;
	Concealed = $1E;
	Quote = $1F;
	BinExtShort = $15;
	BinExtLong = $00;
	ExtLine = $01;

(* Typed constants *)

CONST CWname: ARRAY[CWtype] OF STRING[7] =
	('Type-2','Type-3','Type-4','Type-5','Type-6','Type-7','Type-8',
	 'Type-9','Type-10','Type-11','Type-12','Type-13','Type-14',
	 'Type-15','Type-16','RFC822');

CONST FlagsName: ARRAY[FlagType] OF STRING[10] =
	('Pvt' (* Private message *),
	 'FileAttach' (* File attach message *),
	 'FileReq' (* File request message *),
	 'UpdReq' (* File update request message *),
	 'Direct' (* Do not route this message *),
	 'Crash'  (* High-priority mail *),
	 'Hold' (* Hold for pickup *),
	 'IMM' (* Immediate mail *),
	 'RRQ' (* Return receipt request *),
	 'CRQ' (* Confirm receipt request *),
	 'IRR' (* Is return receipt *),
	 'Machine' (* Message to a program *),
	 'NoForCC' (* CC in NetMail, NoForward in EchoMail *),
	 'Permanent' (* Message should not be pruged by age *),
	 'Foreign' (* Message is from an other organization *),
	 'reserved15' (* Reserved for future extension *));

CONST LoaclFlagName: ARRAY[LocalFlagType] OF STRING[9] =
	('Local' (* Message is created localy *),
	 'InTransit' (* Message is not destinated for this system *),
	 'Orphan' (* Unknown destination *),
	 'KillSent' (* Remove message after it has been sent *),
	 'DelSent' (* Delete attached file(s) after they have been sent *),
	 'TruncSent' (* Truncate attached file(s) after they have been sent *),
	 'Sent' (* Message has been sent *),
	 'IsRead' (* Message has been read by the SysOp *),
	 'Rcvd' (* Message has been read by its addressee *),
	 'LockMsg' (* Lock the message for further access *),
	 'DontSend' (* Do not send the actual message *),
	 'unused11' (* Reserved for future extension *),
	 'unused12' (* Reserved for future extension *),
	 'unused13' (* Reserved for future extension *),
	 'unused14' (* Reserved for future extension *),
	 'unused15' (* Reserved for future extension *));
