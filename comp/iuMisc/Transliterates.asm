	.586p
	ifdef ??version
	if    ??version GT 500H
	.mmx
	endif
	endif
	model flat
	ifndef	??version
	?debug	macro
	endm
	endif
	?debug	S "C:\src\IS2\comp\iuMisc\Transliterates.cpp"
	?debug	T "C:\src\IS2\comp\iuMisc\Transliterates.cpp"
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
_DATA	segment dword public use32 'DATA'
_DATA	ends
_BSS	segment dword public use32 'BSS'
_BSS	ends
 ?debug  C FB0C0100600000
DGROUP	group	_BSS,_DATA
_DATA	segment dword public use32 'DATA'
_cINET2FTN	label	byte
	db	0
	db	1
	db	2
	db	3
	db	4
	db	5
	db	6
	db	7
	db	8
	db	9
	db	10
	db	11
	db	12
	db	13
	db	14
	db	15
	db	16
	db	17
	db	18
	db	19
	db	20
	db	21
	db	22
	db	23
	db	24
	db	25
	db	26
	db	27
	db	28
	db	29
	db	30
	db	31
	db	32
	db	33
	db	34
	db	35
	db	36
	db	37
	db	38
	db	39
	db	40
	db	41
	db	42
	db	43
	db	44
	db	45
	db	46
	db	47
	db	48
	db	49
	db	50
	db	51
	db	52
	db	53
	db	54
	db	55
	db	56
	db	57
	db	58
	db	59
	db	60
	db	61
	db	62
	db	63
	db	64
	db	65
	db	66
	db	67
	db	68
	db	69
	db	70
	db	71
	db	72
	db	73
	db	74
	db	75
	db	76
	db	77
	db	78
	db	79
	db	80
	db	81
	db	82
	db	83
	db	84
	db	85
	db	86
	db	87
	db	88
	db	89
	db	90
	db	91
	db	92
	db	93
	db	94
	db	95
	db	96
	db	97
	db	98
	db	99
	db	100
	db	101
	db	102
	db	103
	db	104
	db	105
	db	106
	db	107
	db	108
	db	109
	db	110
	db	111
	db	112
	db	113
	db	114
	db	115
	db	116
	db	117
	db	118
	db	119
	db	120
	db	121
	db	122
	db	123
	db	124
	db	125
	db	126
	db	127
	db	196
	db	179
	db	218
	db	191
	db	192
	db	217
	db	195
	db	180
	db	194
	db	193
	db	197
	db	223
	db	220
	db	219
	db	221
	db	222
	db	176
	db	177
	db	178
	db	244
	db	254
	db	249
	db	251
	db	247
	db	243
	db	242
	db	255
	db	245
	db	248
	db	253
	db	250
	db	246
	db	205
	db	186
	db	213
	db	241
	db	214
	db	201
	db	184
	db	183
	db	187
	db	212
	db	211
	db	200
	db	190
	db	189
	db	188
	db	198
	db	199
	db	204
	db	181
	db	240
	db	182
	db	185
	db	209
	db	210
	db	203
	db	207
	db	208
	db	202
	db	216
	db	215
	db	206
	db	252
	db	238
	db	160
	db	161
	db	230
	db	164
	db	165
	db	228
	db	163
	db	229
	db	168
	db	169
	db	170
	db	171
	db	172
	db	173
	db	174
	db	175
	db	239
	db	224
	db	225
	db	226
	db	227
	db	166
	db	162
	db	236
	db	235
	db	167
	db	232
	db	237
	db	233
	db	231
	db	234
	db	158
	db	128
	db	129
	db	150
	db	132
	db	133
	db	148
	db	131
	db	149
	db	136
	db	137
	db	138
	db	139
	db	140
	db	141
	db	142
	db	143
	db	159
	db	144
	db	145
	db	146
	db	147
	db	134
	db	130
	db	156
	db	155
	db	135
	db	152
	db	157
	db	153
	db	151
	db	154
_cFTN2INET	label	byte
	db	0
	db	1
	db	2
	db	3
	db	4
	db	5
	db	6
	db	7
	db	8
	db	9
	db	10
	db	11
	db	12
	db	13
	db	14
	db	15
	db	16
	db	17
	db	18
	db	19
	db	20
	db	21
	db	22
	db	23
	db	24
	db	25
	db	26
	db	27
	db	28
	db	29
	db	30
	db	31
	db	32
	db	33
	db	34
	db	35
	db	36
	db	37
	db	38
	db	39
	db	40
	db	41
	db	42
	db	43
	db	44
	db	45
	db	46
	db	47
	db	48
	db	49
	db	50
	db	51
	db	52
	db	53
	db	54
	db	55
	db	56
	db	57
	db	58
	db	59
	db	60
	db	61
	db	62
	db	63
	db	64
	db	65
	db	66
	db	67
	db	68
	db	69
	db	70
	db	71
	db	72
	db	73
	db	74
	db	75
	db	76
	db	77
	db	78
	db	79
	db	80
	db	81
	db	82
	db	83
	db	84
	db	85
	db	86
	db	87
	db	88
	db	89
	db	90
	db	91
	db	92
	db	93
	db	94
	db	95
	db	96
	db	97
	db	98
	db	99
	db	100
	db	101
	db	102
	db	103
	db	104
	db	105
	db	106
	db	107
	db	108
	db	109
	db	110
	db	111
	db	112
	db	113
	db	114
	db	115
	db	116
	db	117
	db	118
	db	119
	db	120
	db	121
	db	122
	db	123
	db	124
	db	125
	db	126
	db	127
	db	225
	db	226
	db	247
	db	231
	db	228
	db	229
	db	246
	db	250
	db	233
	db	234
	db	235
	db	236
	db	237
	db	238
	db	239
	db	240
	db	242
	db	243
	db	244
	db	245
	db	230
	db	232
	db	227
	db	254
	db	251
	db	253
	db	255
	db	249
	db	248
	db	252
	db	224
	db	241
	db	193
	db	194
	db	215
	db	199
	db	196
	db	197
	db	214
	db	218
	db	201
	db	202
	db	203
	db	204
	db	205
	db	206
	db	207
	db	208
	db	144
	db	145
	db	146
	db	129
	db	135
	db	178
	db	180
	db	167
	db	166
	db	181
	db	161
	db	168
	db	174
	db	173
	db	172
	db	131
	db	132
	db	137
	db	136
	db	134
	db	128
	db	138
	db	175
	db	176
	db	171
	db	165
	db	187
	db	184
	db	177
	db	160
	db	190
	db	185
	db	186
	db	182
	db	183
	db	170
	db	169
	db	162
	db	164
	db	189
	db	188
	db	133
	db	130
	db	141
	db	140
	db	142
	db	143
	db	139
	db	210
	db	211
	db	212
	db	213
	db	198
	db	200
	db	195
	db	222
	db	219
	db	221
	db	223
	db	217
	db	216
	db	220
	db	192
	db	209
	db	179
	db	163
	db	153
	db	152
	db	147
	db	155
	db	159
	db	151
	db	156
	db	149
	db	158
	db	150
	db	191
	db	157
	db	148
	db	154
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@Transliterate$qqrpct1t1	segment virtual
	align	2
@@Transliterate$qqrpct1t1	proc	near
?live16385@0:
	push      ebx
@1:
	mov	   ebx,ecx
	mov	   ecx,eax
@2:
l1:
	mov	   al,[ecx]
	or	    al,al
	je        short @3
	xlat	
	mov	   [edx],al
	inc	   edx
	inc	   ecx
	jmp       @2
@3:
done:
@4:
	pop       ebx
	ret 
@@Transliterate$qqrpct1t1	endp
@Transliterate$qqrpct1t1	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@N2H$qqrpct1	segment virtual
	align	2
@@N2H$qqrpct1	proc	near
?live16386@0:
	push      ebx
@5:
	mov	   ebx,ecx
	mov	   ecx,eax
@6:
n1:
	mov	   al,[ecx]
	or	    al,al
	je        @7
	cmp	   al,08dH
	jne       short @8
	mov	   al,'H'
@8:
n2:
	mov	   [edx],al
	inc	   edx
	inc	   ecx
	jmp       @6
@7:
n_done:
@9:
	pop       ebx
	ret 
@@N2H$qqrpct1	endp
@N2H$qqrpct1	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@OEM2KOI$qqrpct1	segment virtual
	align	2
@@OEM2KOI$qqrpct1	proc	near
?live16387@0:
@10:
	mov       ecx,offset _cFTN2INET
	call      @@Transliterate$qqrpct1t1
@11:
	ret 
@@OEM2KOI$qqrpct1	endp
@OEM2KOI$qqrpct1	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@KOI2OEM$qqrpct1	segment virtual
	align	2
@@KOI2OEM$qqrpct1	proc	near
?live16388@0:
@12:
	mov       ecx,offset _cINET2FTN
	call      @@Transliterate$qqrpct1t1
@13:
	ret 
@@KOI2OEM$qqrpct1	endp
@KOI2OEM$qqrpct1	ends
_TEXT	ends
_BSS	segment dword public use32 'BSS'
	align	4
$ikfpdgia	label	dword
	db	4	dup(?)
	align	4
$aofpdgia	label	dword
	db	4	dup(?)
_BSS	ends
_TEXT	segment dword public use32 'CODE'
@LoadTransTable$qqrpct1	segment virtual
	align	2
@@LoadTransTable$qqrpct1	proc	near
?live16389@0:
@14:
	push      ebx
	push      esi
	push      edi
	push      ebp
	mov       edi,edx
?live16389@16: ; EAX = FileName, EDI = Table
	xor       ebx,ebx
?live16389@32: ; EBX = ucTableIndex, EAX = FileName, EDI = Table
	push      offset s@
	push      eax
	call      @_fopen
	add       esp,8
	mov       esi,eax
?live16389@48: ; ESI = fTbl, EBX = ucTableIndex, EDI = Table
	test      esi,esi
	je        short @16
	xor       eax,eax
	mov       al,bl
	lea       ebp,dword ptr [edi+eax]
	jmp       short @18
?live16389@64: ; ESI = fTbl, EBX = ucTableIndex, EBP = @temp3
@17:
	push      offset $aofpdgia
	push      offset s@+2
	push      esi
	call      @_fscanf
	add       esp,12
	mov       edi,eax
	mov       dword ptr [$ikfpdgia],edi
?live16389@80: ; EDI = @temp0, ESI = fTbl, EBX = ucTableIndex, EBP = @temp3
	cmp       edi,-1
	je        short @20
?live16389@96: ; ESI = fTbl
	test      edi,edi
	je        short @21
?live16389@112: ; ESI = fTbl, EBX = ucTableIndex, EBP = @temp3
	mov       al,byte ptr [$aofpdgia]
	inc       ebx
	mov       byte ptr [ebp+0],al
	inc       ebp
	test      bl,bl
	je        short @20
?live16389@192: ; ESI = fTbl
@21:
@18:
	test      byte ptr [esi+18],32
	je        short @17
@20:
	push      esi
	call      @_fclose
	pop       ecx
?live16389@224: ; 
@16:
@24:
	pop       ebp
	pop       edi
	pop       esi
	pop       ebx
	ret 
@@LoadTransTable$qqrpct1	endp
@LoadTransTable$qqrpct1	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@Load_INET2FTN_Table$qqrpc	segment virtual
	align	2
@@Load_INET2FTN_Table$qqrpc	proc	near
?live16390@0:
@25:
	mov       edx,offset _cINET2FTN
	call      @@LoadTransTable$qqrpct1
@26:
	ret 
@@Load_INET2FTN_Table$qqrpc	endp
@Load_INET2FTN_Table$qqrpc	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@Load_FTN2INET_Table$qqrpc	segment virtual
	align	2
@@Load_FTN2INET_Table$qqrpc	proc	near
?live16391@0:
@27:
	mov       edx,offset _cFTN2INET
	call      @@LoadTransTable$qqrpct1
@28:
	ret 
@@Load_FTN2INET_Table$qqrpc	endp
@Load_FTN2INET_Table$qqrpc	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
s@	label	byte
	;	s@+0:
	db	"r",0
	;	s@+2:
	db	"%x",0
	align	4
_DATA	ends
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
	public	_cINET2FTN
	public	_cFTN2INET
@_fopen equ _fopen
 extrn   _fopen:near
@_fscanf equ _fscanf
 extrn   _fscanf:near
@_fclose equ _fclose
 extrn   _fclose:near
 ?debug  C FB0A5472616E736C697465726174657300
 ?debug  C 9F76636C6535302E6C6962
 ?debug  C 9F757569642E6C6962
 ?debug  C 9F757569642E6C6962
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\wintrust.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\Windows.hpp" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\sysvari.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\sysopen.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\sysdyn.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\systvar.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\sysset.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\syscomp.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\syscurr.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\systdate.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\systobj.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\wstring.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\sysmac.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\dstring.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\sysclass.H" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\basetyps.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\sysmac.H" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\System.hpp" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\SysInit.hpp" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\SysConst.hpp" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\sysutils.hpp" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\imm.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\mcx.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winsvc.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\commdlg.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\oleauto.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\propidl.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\oaidl.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\msxml.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\servprov.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\oleidl.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\urlmon.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\cguid.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\objidl.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\unknwn.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\search.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\stdlib.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\objbase.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\ole2.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\prsht.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winspool.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winsmcrd.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winioctl.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcnsip.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcndr.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\wtypes.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winscard.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winefs.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\wincrypt.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\qos.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winsock2.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winperf.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\shellapi.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcasync.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcnterr.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcnsi.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcdcep.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcdce.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpc.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\nb30.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\mmsystem.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\lzexpand.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\dlgs.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\ddeml.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\dde.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\cderr.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winnetwk.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winreg.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winver.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\wincon.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winnls.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\tvout.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winuser.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\pshpack1.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\wingdi.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winerror.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winbase.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\pshpack8.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\pshpack2.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\poppack.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\pshpack4.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\guiddef.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\basetsd.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\mbctype.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\ctype.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winnt.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\windef.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\stdarg.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\excpt.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\windows.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\time.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\mem.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_loc.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\locale.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_str.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\string.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\tchar.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\dir.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\stdio.h" 10303 12288
	?debug	D "IULOGS\LOG.H" 10900 41258
	?debug	D "C:\src\IS2\comp\iuMisc\TRANSLITERATES.H" 10507 46292
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_nfile.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_null.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_defs.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_stddef.h" 10303 12288
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\STDIO.H" 10303 12288
	?debug	D "C:\src\IS2\comp\iuMisc\Transliterates.cpp" 10537 30916
	end
