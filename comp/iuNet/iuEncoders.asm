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
	?debug	S "C:\src\IS2\comp\iuNet\iuEncoders.cpp"
	?debug	T "C:\src\IS2\comp\iuNet\iuEncoders.cpp"
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
_DATA	segment dword public use32 'DATA'
_DATA	ends
_BSS	segment dword public use32 'BSS'
_BSS	ends
 ?debug  C FB0C0100600000
DGROUP	group	_BSS,_DATA
_DATA	segment dword public use32 'DATA'
@_$DCTF$@EncodeBase64$qqr17System@AnsiString	segment virtual
	align	2
@@_$DCTF$@EncodeBase64$qqr17System@AnsiString	label	dword
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-8
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-8
	dd	0
	dd	@@$xt$p17System@AnsiString
	dd	20
	dd	-12
	dd	0
	dd	@@$xt$p17System@AnsiString
	dd	52
	dd	-12
	dd	0
@_$DCTF$@EncodeBase64$qqr17System@AnsiString	ends
_DATA	ends
_DATA	segment dword public use32 'DATA'
@_$ECTUF$@EncodeBase64$qqr17System@AnsiString	segment virtual
	align	2
@@_$ECTUF$@EncodeBase64$qqr17System@AnsiString	label	dword
	dd	0
	dd	-48
	dw	0
	dw	5
	dd	1
	dd	@@_$DCTF$@EncodeBase64$qqr17System@AnsiString
	dw	8
	dw	5
	dd	2
	dd	@@_$DCTF$@EncodeBase64$qqr17System@AnsiString+28
	dw	8
	dw	5
	dd	3
	dd	@@_$DCTF$@EncodeBase64$qqr17System@AnsiString+44
	dw	32
	dw	5
	dd	3
	dd	@@_$DCTF$@EncodeBase64$qqr17System@AnsiString+60
@_$ECTUF$@EncodeBase64$qqr17System@AnsiString	ends
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@EncodeBase64$qqr17System@AnsiString	segment virtual
	align	2
@@EncodeBase64$qqr17System@AnsiString	proc	near
?live16385@0:
@1:
	push      ebp
	mov       ebp,esp
	add       esp,-48
	mov       dword ptr [ebp-12],edx
	mov       dword ptr [ebp-4],eax
	mov       eax,offset @@_$ECTUF$@EncodeBase64$qqr17System@AnsiString
	call      @__InitExceptBlockLDTC
	mov       dword ptr [ebp-20],1
	lea       edx,dword ptr [ebp-4]
	lea       eax,dword ptr [ebp-4]
	call      @@System@AnsiString@$bctr$qqrrx17System@AnsiString
	inc       dword ptr [ebp-20]
	mov       edx,offset s@
	mov       word ptr [ebp-32],8
	mov       word ptr [ebp-32],20
	lea       eax,dword ptr [ebp-8]
	call      @@System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-20]
	lea       edx,dword ptr [ebp-8]
	mov       word ptr [ebp-32],8
	mov       word ptr [ebp-32],32
	mov       eax,dword ptr [ebp-12]
	call      @@System@AnsiString@$basg$qqrrx17System@AnsiString
	mov       eax,dword ptr [ebp-12]
	mov       edx,2
	mov       word ptr [ebp-32],44
	push      eax
	lea       eax,dword ptr [ebp-8]
	dec       dword ptr [ebp-20]
	call      @@System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-20]
	lea       eax,dword ptr [ebp-4]
	mov       edx,2
	call      @@System@AnsiString@$bdtr$qqrv
	pop       eax
	mov       word ptr [ebp-32],32
	inc       dword ptr [ebp-20]
	mov       edx,dword ptr [ebp-48]
	mov       dword ptr fs:[0],edx
@3:
@2:
	mov       esp,ebp
	pop       ebp
	ret 
@@EncodeBase64$qqr17System@AnsiString	endp
@EncodeBase64$qqr17System@AnsiString	ends
_TEXT	ends
_BSS	segment dword public use32 'BSS'
	align	4
$einpmjia	label	dword
	db	4	dup(?)
_BSS	ends
_DATA	segment dword public use32 'DATA'
@_$DCVF$@DecodeBase64$qqr17System@AnsiString	segment virtual
	align	2
@@_$DCVF$@DecodeBase64$qqr17System@AnsiString	label	dword
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-8
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-8
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-12
	dd	0
	dd	@@$xt$p17System@AnsiString
	dd	20
	dd	-16
	dd	0
	dd	@@$xt$p17System@AnsiString
	dd	52
	dd	-16
	dd	0
@_$DCVF$@DecodeBase64$qqr17System@AnsiString	ends
_DATA	ends
_DATA	segment dword public use32 'DATA'
@_$ECTWF$@DecodeBase64$qqr17System@AnsiString	segment virtual
	align	2
@@_$ECTWF$@DecodeBase64$qqr17System@AnsiString	label	dword
	dd	0
	dd	-52
	dw	0
	dw	5
	dd	1
	dd	@@_$DCVF$@DecodeBase64$qqr17System@AnsiString
	dw	8
	dw	5
	dd	2
	dd	@@_$DCVF$@DecodeBase64$qqr17System@AnsiString+28
	dw	8
	dw	5
	dd	3
	dd	@@_$DCVF$@DecodeBase64$qqr17System@AnsiString+44
	dw	8
	dw	5
	dd	3
	dd	@@_$DCVF$@DecodeBase64$qqr17System@AnsiString+60
	dw	44
	dw	5
	dd	3
	dd	@@_$DCVF$@DecodeBase64$qqr17System@AnsiString+76
@_$ECTWF$@DecodeBase64$qqr17System@AnsiString	ends
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@DecodeBase64$qqr17System@AnsiString	segment virtual
	align	2
@@DecodeBase64$qqr17System@AnsiString	proc	near
?live16390@0:
@4:
	push      ebp
	mov       ebp,esp
	add       esp,-52
	push      ebx
	mov       dword ptr [ebp-16],edx
	mov       dword ptr [ebp-4],eax
	mov       eax,offset @@_$ECTWF$@DecodeBase64$qqr17System@AnsiString
	call      @__InitExceptBlockLDTC
	mov       dword ptr [ebp-24],1
	lea       edx,dword ptr [ebp-4]
	lea       eax,dword ptr [ebp-4]
	call      @@System@AnsiString@$bctr$qqrrx17System@AnsiString
	inc       dword ptr [ebp-24]
	mov       edx,offset s@
	mov       word ptr [ebp-36],8
	mov       word ptr [ebp-36],20
	lea       eax,dword ptr [ebp-8]
	call      @@System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-24]
	mov       word ptr [ebp-36],8
	mov       edx,dword ptr [ebp-4]
	test      edx,edx
	je        short @5
	mov       ecx,dword ptr [ebp-4]
	mov       eax,dword ptr [ecx-4]
	jmp       short @6
@5:
	xor       eax,eax
@6:
	push      eax
	call      @$bnwa$qui
	pop       ecx
	mov       ebx,eax
?live16390@80: ; EBX = decodedBlock
	mov       eax,dword ptr [ebp-4]
	test      eax,eax
	je        short @8
	mov       edx,dword ptr [ebp-4]
	mov       ecx,dword ptr [edx-4]
	jmp       short @9
@8:
	xor       ecx,ecx
@9:
	push      ecx
	mov       eax,dword ptr [ebp-4]
	test      eax,eax
	je        short @10
	mov       ecx,dword ptr [ebp-4]
	jmp       short @11
@10:
	mov       ecx,offset s@
@11:
	mov       edx,offset $einpmjia
	mov       eax,ebx
	call      @@R_DecodePEMBlock$qqrpucpuit1ui
	test      eax,eax
	jne       short @7
	mov       word ptr [ebp-36],32
	lea       eax,dword ptr [ebp-12]
	mov       ecx,dword ptr [$einpmjia]
	mov       edx,ebx
	call      @@System@AnsiString@$bctr$qqrpxcui
	mov       edx,eax
	inc       dword ptr [ebp-24]
	lea       eax,dword ptr [ebp-8]
	call      @@System@AnsiString@$basg$qqrrx17System@AnsiString
	dec       dword ptr [ebp-24]
	lea       eax,dword ptr [ebp-12]
	mov       edx,2
	call      @@System@AnsiString@$bdtr$qqrv
@7:
	push      ebx
	call      @$bdla$qpv
	pop       ecx
?live16390@128: ; 
	lea       edx,dword ptr [ebp-8]
	mov       word ptr [ebp-36],44
	mov       eax,dword ptr [ebp-16]
	call      @@System@AnsiString@$basg$qqrrx17System@AnsiString
	mov       eax,dword ptr [ebp-16]
	mov       edx,2
	mov       word ptr [ebp-36],56
	push      eax
	lea       eax,dword ptr [ebp-8]
	dec       dword ptr [ebp-24]
	call      @@System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-24]
	lea       eax,dword ptr [ebp-4]
	mov       edx,2
	call      @@System@AnsiString@$bdtr$qqrv
	pop       eax
	mov       word ptr [ebp-36],44
	inc       dword ptr [ebp-24]
	mov       edx,dword ptr [ebp-52]
	mov       dword ptr fs:[0],edx
@13:
@12:
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
@@DecodeBase64$qqr17System@AnsiString	endp
@DecodeBase64$qqr17System@AnsiString	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
@_$DCXF$@UUEncodeFile$qqri	segment virtual
	align	2
@@_$DCXF$@UUEncodeFile$qqri	label	dword
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-8
	dd	0
	dd	@@$xt$p17System@AnsiString
	dd	20
	dd	-12
	dd	0
	dd	@@$xt$p17System@AnsiString
	dd	52
	dd	-12
	dd	0
@_$DCXF$@UUEncodeFile$qqri	ends
_DATA	ends
_DATA	segment dword public use32 'DATA'
@_$ECTYF$@UUEncodeFile$qqri	segment virtual
	align	2
@@_$ECTYF$@UUEncodeFile$qqri	label	dword
	dd	0
	dd	-48
	dw	0
	dw	5
	dd	0
	dd	@@_$DCXF$@UUEncodeFile$qqri
	dw	8
	dw	5
	dd	0
	dd	@@_$DCXF$@UUEncodeFile$qqri+16
	dw	8
	dw	5
	dd	1
	dd	@@_$DCXF$@UUEncodeFile$qqri+32
	dw	8
	dw	5
	dd	1
	dd	@@_$DCXF$@UUEncodeFile$qqri+48
	dw	44
	dw	5
	dd	1
	dd	@@_$DCXF$@UUEncodeFile$qqri+64
@_$ECTYF$@UUEncodeFile$qqri	ends
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@UUEncodeFile$qqri	segment virtual
	align	2
@@UUEncodeFile$qqri	proc	near
?live16393@0:
@14:
	push      ebp
	mov       ebp,esp
	add       esp,-300
	push      ebx
	push      esi
	mov       dword ptr [ebp-12],edx
	mov       dword ptr [ebp-52],eax
	mov       eax,offset @@_$ECTYF$@UUEncodeFile$qqri
	call      @__InitExceptBlockLDTC
	mov       word ptr [ebp-32],20
	mov       edx,offset s@
	lea       eax,dword ptr [ebp-4]
	call      @@System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-20]
	mov       word ptr [ebp-32],8
@15:
	push      45
	lea       edx,dword ptr [ebp-140]
	push      edx
	mov       ecx,dword ptr [ebp-52]
	push      ecx
	call      @_read
	mov       word ptr [ebp-58],ax
	add       esp,12
	cmp       word ptr [ebp-58],0
	je        short @16
	mov       al,byte ptr [ebp-58]
	and       al,63
	add       al,32
	jmp       short @17
@16:
	mov       al,96
@17:
	mov       byte ptr [ebp-300],al
	mov       word ptr [ebp-54],0
	mov       word ptr [ebp-56],1
	mov       dx,word ptr [ebp-54]
	cmp       dx,word ptr [ebp-58]
	jge       @19
@18:
	movsx     ecx,word ptr [ebp-54]
	lea       eax,dword ptr [ebp-140]
	add       ecx,eax
	movsx     esi,word ptr [ebp-56]
	lea       eax,dword ptr [ebp-300]
	add       esi,eax
	mov       dl,byte ptr [ecx]
	mov       al,byte ptr [ecx+1]
	mov       cl,byte ptr [ecx+2]
	mov       byte ptr [ebp-59],cl
	movsx     ecx,dl
	sar       ecx,2
	test      cl,cl
	je        short @20
	movsx     ecx,dl
	sar       ecx,2
	and       cl,63
	add       cl,32
	jmp       short @21
@20:
	mov       cl,96
@21:
	mov       byte ptr [esi],cl
	movsx     ecx,dl
	movsx     ebx,al
	sar       ebx,4
	shl       ecx,4
	and       ebx,15
	and       ecx,48
	or        ecx,ebx
	je        short @22
	movsx     ecx,al
	sar       ecx,4
	shl       edx,4
	and       cl,15
	and       dl,48
	or        dl,cl
	and       dl,63
	add       dl,32
	jmp       short @23
@22:
	mov       dl,96
@23:
	mov       byte ptr [esi+1],dl
	movsx     edx,al
	movsx     ecx,byte ptr [ebp-59]
	sar       ecx,6
	shl       edx,2
	and       ecx,3
	and       edx,60
	or        edx,ecx
	je        short @24
	movsx     edx,byte ptr [ebp-59]
	sar       edx,6
	shl       eax,2
	and       dl,3
	and       al,60
	or        al,dl
	and       al,63
	add       al,32
	jmp       short @25
@24:
	mov       al,96
@25:
	mov       byte ptr [esi+2],al
	mov       cl,byte ptr [ebp-59]
	test      cl,cl
	je        short @26
	mov       al,byte ptr [ebp-59]
	and       al,63
	add       al,32
	jmp       short @27
@26:
	mov       al,96
@27:
	mov       byte ptr [esi+3],al
	add       word ptr [ebp-54],3
	add       word ptr [ebp-56],4
	mov       dx,word ptr [ebp-54]
	cmp       dx,word ptr [ebp-58]
	jl        @18
@19:
	movsx     ecx,word ptr [ebp-56]
	lea       edx,dword ptr [ebp-300]
	mov       byte ptr [ebp+ecx-300],10
	inc       word ptr [ebp-56]
	movsx     eax,word ptr [ebp-56]
	mov       byte ptr [ebp+eax-300],0
	mov       word ptr [ebp-32],32
	lea       eax,dword ptr [ebp-8]
	call      @@System@AnsiString@$bctr$qqrpxc
	mov       edx,eax
	inc       dword ptr [ebp-20]
	lea       eax,dword ptr [ebp-4]
	call      @@System@AnsiString@$brplu$qqrrx17System@AnsiString
	dec       dword ptr [ebp-20]
	lea       eax,dword ptr [ebp-8]
	mov       edx,2
	call      @@System@AnsiString@$bdtr$qqrv
	push      0
	call      @Sleep
	cmp       word ptr [ebp-58],0
	jg        @15
	mov       word ptr [ebp-32],44
	lea       edx,dword ptr [ebp-4]
	mov       eax,dword ptr [ebp-12]
	call      @@System@AnsiString@$basg$qqrrx17System@AnsiString
	mov       eax,dword ptr [ebp-12]
	mov       edx,2
	mov       word ptr [ebp-32],56
	push      eax
	lea       eax,dword ptr [ebp-4]
	dec       dword ptr [ebp-20]
	call      @@System@AnsiString@$bdtr$qqrv
	pop       eax
	mov       word ptr [ebp-32],44
	inc       dword ptr [ebp-20]
	mov       edx,dword ptr [ebp-48]
	mov       dword ptr fs:[0],edx
@33:
@32:
	pop       esi
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
@@UUEncodeFile$qqri	endp
@UUEncodeFile$qqri	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
@_$DCZF$@IncludeAttachAsUUE$qqrr17System@AnsiString17System@AnsiString	segment virtual
	align	2
@@_$DCZF$@IncludeAttachAsUUE$qqrr17System@AnsiString17System@AnsiString	label	dword
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-4
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-8
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-12
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-16
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-20
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-24
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-28
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-32
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	-36
	dd	0
@_$DCZF$@IncludeAttachAsUUE$qqrr17System@AnsiString17System@AnsiString	ends
_DATA	ends
_DATA	segment dword public use32 'DATA'
@_$ECTAG$@IncludeAttachAsUUE$qqrr17System@AnsiString17System@AnsiString	segment virtual
	align	2
@@_$ECTAG$@IncludeAttachAsUUE$qqrr17System@AnsiString17System@AnsiString	label	dword
	dd	0
	dd	-72
	dw	0
	dw	5
	dd	1
	dd	@@_$DCZF$@IncludeAttachAsUUE$qqrr17System@AnsiString17System@AnsiString
	dw	8
	dw	5
	dd	2
	dd	@@_$DCZF$@IncludeAttachAsUUE$qqrr17System@AnsiString17System@AnsiString+16
@_$ECTAG$@IncludeAttachAsUUE$qqrr17System@AnsiString17System@AnsiString	ends
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@IncludeAttachAsUUE$qqrr17System@AnsiString17System@AnsiString	segment virtual
	align	2
@@IncludeAttachAsUUE$qqrr17System@AnsiString17System@AnsiString	proc	near
?live16396@0:
@34:
	push      ebp
	mov       ebp,esp
	add       esp,-72
	push      ebx
	push      esi
	mov       dword ptr [ebp-4],edx
	mov       esi,eax
	mov       eax,offset @@_$ECTAG$@IncludeAttachAsUUE$qqrr17System@AnsiString17System@AnsiString
	call      @__InitExceptBlockLDTC
	mov       dword ptr [ebp-44],1
	lea       edx,dword ptr [ebp-4]
	lea       eax,dword ptr [ebp-4]
	call      @@System@AnsiString@$bctr$qqrrx17System@AnsiString
	inc       dword ptr [ebp-44]
?live16396@16: ; ESI = Msg
	mov       word ptr [ebp-56],8
	push      384
	push      32768
	mov       edx,dword ptr [ebp-4]
	test      edx,edx
	je        short @35
	mov       ecx,dword ptr [ebp-4]
	jmp       short @36
@35:
	mov       ecx,offset s@
@36:
	push      ecx
	call      @_open
	add       esp,12
	mov       ebx,eax
?live16396@48: ; EBX = in, ESI = Msg
	test      ebx,ebx
	jl        @37
	mov       word ptr [ebp-56],20
	xor       eax,eax
	mov       dword ptr [ebp-8],eax
	lea       edx,dword ptr [ebp-8]
	inc       dword ptr [ebp-44]
	mov       eax,dword ptr [ebp-4]
	call      @@Sysutils@ExtractFileName$qqrx17System@AnsiString
	lea       edx,dword ptr [ebp-8]
	xor       ecx,ecx
	mov       dword ptr [ebp-12],ecx
	lea       ecx,dword ptr [ebp-12]
	inc       dword ptr [ebp-44]
	mov       eax,offset s@+1
	call      @@System@$badd$qqrpxcrx17System@AnsiString
	lea       edx,dword ptr [ebp-12]
	push      edx
	mov       edx,offset s@+14
	lea       eax,dword ptr [ebp-16]
	call      @@System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-44]
	xor       eax,eax
	mov       dword ptr [ebp-20],eax
	lea       edx,dword ptr [ebp-16]
	inc       dword ptr [ebp-44]
	lea       ecx,dword ptr [ebp-20]
	pop       eax
	call      @@System@AnsiString@$badd$xqqrrx17System@AnsiString
	lea       edx,dword ptr [ebp-20]
	xor       ecx,ecx
	push      edx
	mov       dword ptr [ebp-24],ecx
	inc       dword ptr [ebp-44]
	lea       edx,dword ptr [ebp-24]
	mov       eax,ebx
	call      @@UUEncodeFile$qqri
	lea       edx,dword ptr [ebp-24]
	xor       eax,eax
	mov       dword ptr [ebp-28],eax
	lea       ecx,dword ptr [ebp-28]
	inc       dword ptr [ebp-44]
	pop       eax
	call      @@System@AnsiString@$badd$xqqrrx17System@AnsiString
	lea       edx,dword ptr [ebp-28]
	push      edx
	mov       edx,offset s@+17
	lea       eax,dword ptr [ebp-32]
	call      @@System@AnsiString@$bctr$qqrpxc
	inc       dword ptr [ebp-44]
	xor       eax,eax
	mov       dword ptr [ebp-36],eax
	lea       edx,dword ptr [ebp-32]
	inc       dword ptr [ebp-44]
	lea       ecx,dword ptr [ebp-36]
	pop       eax
	call      @@System@AnsiString@$badd$xqqrrx17System@AnsiString
	lea       edx,dword ptr [ebp-36]
	mov       eax,esi
	call      @@System@AnsiString@$brplu$qqrrx17System@AnsiString
	dec       dword ptr [ebp-44]
	lea       eax,dword ptr [ebp-36]
	mov       edx,2
	call      @@System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-44]
	lea       eax,dword ptr [ebp-32]
	mov       edx,2
	call      @@System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-44]
	lea       eax,dword ptr [ebp-28]
	mov       edx,2
	call      @@System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-44]
	lea       eax,dword ptr [ebp-24]
	mov       edx,2
	call      @@System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-44]
	lea       eax,dword ptr [ebp-20]
	mov       edx,2
	call      @@System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-44]
	lea       eax,dword ptr [ebp-16]
	mov       edx,2
	call      @@System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-44]
	lea       eax,dword ptr [ebp-12]
	mov       edx,2
	call      @@System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-44]
	lea       eax,dword ptr [ebp-8]
	mov       edx,2
	call      @@System@AnsiString@$bdtr$qqrv
?live16396@80: ; 
@37:
	dec       dword ptr [ebp-44]
	lea       eax,dword ptr [ebp-4]
	mov       edx,2
	call      @@System@AnsiString@$bdtr$qqrv
	mov       ecx,dword ptr [ebp-72]
	mov       dword ptr fs:[0],ecx
@38:
	pop       esi
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret 
@@IncludeAttachAsUUE$qqrr17System@AnsiString17System@AnsiString	endp
@IncludeAttachAsUUE$qqrr17System@AnsiString17System@AnsiString	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@dummy$qv	segment virtual
	align	2
@@dummy$qv	proc	near
?live16399@0:
@39:
	mov	 ax,ax
@40:
	ret 
@@dummy$qv	endp
@dummy$qv	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$p17System@AnsiString	segment virtual
	align	2
@@$xt$p17System@AnsiString	label	dword
	dd	4
	dw	16
	dw	12
	dd	@@$xt$17System@AnsiString
	db	65
	db	110
	db	115
	db	105
	db	83
	db	116
	db	114
	db	105
	db	110
	db	103
	db	32
	db	42
	db	0
@$xt$p17System@AnsiString	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$17System@AnsiString	segment virtual
	align	2
@@$xt$17System@AnsiString	label	byte
	dd	4
	dw	3
	dw	48
	dd	-1
	dd	3
	dw	68
	dw	72
	dd	0
	dw	0
	dw	0
	dd	0
	dd	1
	dd	1
	dd	@@System@AnsiString@$bdtr$qqrv
	dw	3
	dw	76
	db	83
	db	121
	db	115
	db	116
	db	101
	db	109
	db	58
	db	58
	db	65
	db	110
	db	115
	db	105
	db	83
	db	116
	db	114
	db	105
	db	110
	db	103
	db	0
	db	0
	dd	0
	dd	0
	dd	0
@$xt$17System@AnsiString	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
s@	label	byte
	db	0,13,10
	;	s@+3:
	db	"begin 666 ",0,13,10,0
	;	s@+17:
	db	"end",0
	align	4
_DATA	ends
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
@@System@AnsiString@$bctr$qqrrx17System@AnsiString equ @System@AnsiString@$bctr$qqrrx17System@AnsiString
 extrn   @System@AnsiString@$bctr$qqrrx17System@AnsiString:near
@@System@AnsiString@$bctr$qqrpxc equ @System@AnsiString@$bctr$qqrpxc
 extrn   @System@AnsiString@$bctr$qqrpxc:near
@@System@AnsiString@$basg$qqrrx17System@AnsiString equ @System@AnsiString@$basg$qqrrx17System@AnsiString
 extrn   @System@AnsiString@$basg$qqrrx17System@AnsiString:near
@@System@AnsiString@$bdtr$qqrv equ @System@AnsiString@$bdtr$qqrv
 extrn   @System@AnsiString@$bdtr$qqrv:near
 extrn   __Exception_list:dword
 extrn   @__InitExceptBlockLDTC:near
 extrn   @$bnwa$qui:near
@@R_DecodePEMBlock$qqrpucpuit1ui equ @R_DecodePEMBlock$qqrpucpuit1ui
 extrn   @R_DecodePEMBlock$qqrpucpuit1ui:near
@@System@AnsiString@$bctr$qqrpxcui equ @System@AnsiString@$bctr$qqrpxcui
 extrn   @System@AnsiString@$bctr$qqrpxcui:near
 extrn   @$bdla$qpv:near
@_read equ _read
 extrn   _read:near
@@System@AnsiString@$brplu$qqrrx17System@AnsiString equ @System@AnsiString@$brplu$qqrrx17System@AnsiString
 extrn   @System@AnsiString@$brplu$qqrrx17System@AnsiString:near
@Sleep equ Sleep
 extrn   Sleep:near
 ?debug  C A002003E40496E636C75646541747461636841735555452471717272313753797374656D40416E7369537472696E67313753797374656D40416E7369537472696E67000000
@_open equ _open
 extrn   _open:near
@@System@AnsiString@$badd$xqqrrx17System@AnsiString equ @System@AnsiString@$badd$xqqrrx17System@AnsiString
 extrn   @System@AnsiString@$badd$xqqrrx17System@AnsiString:near
@@System@$badd$qqrpxcrx17System@AnsiString equ @System@$badd$qqrpxcrx17System@AnsiString
 extrn   @System@$badd$qqrpxcrx17System@AnsiString:near
@@Sysutils@ExtractFileName$qqrx17System@AnsiString equ @Sysutils@ExtractFileName$qqrx17System@AnsiString
 extrn   @Sysutils@ExtractFileName$qqrx17System@AnsiString:near
 ?debug  C FB0A6975456E636F6465727300
 ?debug  C 9F757569642E6C6962
 ?debug  C 9F757569642E6C6962
 ?debug  C 9F757569642E6C6962
 ?debug  C 9F757569642E6C6962
 ?debug  C 9F76636C6535302E6C6962
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\sys/types.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\sys\stat.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\fcntl.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_nfile.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\io.h" 10303 10240
	?debug	D "IURSA\des.h" 9968 28050
	?debug	D "IURSA\md5.h" 9972 19488
	?debug	D "IURSA\md2.h" 9968 29833
	?debug	D "IURSA\global.h" 9972 19552
	?debug	D "IURSA\rsaref.h" 10917 44323
	?debug	D "C:\src\IS2\comp\iuNet\iuEncoders.h" 10567 43793
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\transact.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\comsvcs.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\mtx.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\OleCtrls.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\DocObj.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\dlgs.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\oledlg.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\OleDlg.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\OleCtnrs.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\DBClient.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\Db.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\DBCommon.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\DSIntf.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\Midas.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\Provider.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\databkr.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\ocidl.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\objsafe.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\ComObj.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\StdVCL.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\AxCtrls.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\stddef.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\ole2.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\propidl.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\msxml.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\servprov.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\oleidl.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\urlmon.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\objbase.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\alloc.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\malloc.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\tchar.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\dir.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\cguid.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\extctrls.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\commdlg.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\CommDlg.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\StdCtrls.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\shellapi.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\ShellAPI.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\regstr.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\RegStr.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\wininet.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\WinInet.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\objidl.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\oaidl.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\oleauto.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\ActiveX.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\UrlMon.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\ShlObj.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\dialogs.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\forms.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\multimon.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\MultiMon.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\Contnrs.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\Menus.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\Imm.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\CommCtrl.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\Commctrl.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\ImgList.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\ActnList.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\controls.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\graphics.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\classes.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\SysConst.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\sysutils.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\messages.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\dde.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\wincrypt.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\wintrust.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\SysInit.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\windows.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\unknwn.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\sysvari.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\sysopen.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\search.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\stdlib.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\sysdyn.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\systvar.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\sysset.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\syscomp.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\syscurr.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\systdate.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\systobj.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcnsip.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcndr.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcnterr.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcnsi.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcdcep.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpcdce.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\rpc.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\wtypes.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\wstring.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\sysmac.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\dstring.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\sysclass.H" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\basetyps.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\prsht.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winspool.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\imm.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\mcx.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winsvc.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winnetwk.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winreg.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winver.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\wincon.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winnls.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\tvout.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winuser.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\pshpack1.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\wingdi.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winerror.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winbase.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\pshpack8.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\pshpack2.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\poppack.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\pshpack4.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_loc.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\locale.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_str.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\string.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\guiddef.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\basetsd.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\mbctype.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\ctype.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\winnt.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\windef.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\stdarg.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\excpt.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_null.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_defs.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\_stddef.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\mem.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\windows.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\sysmac.H" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\system.hpp" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\vcl0.h" 10303 10240
	?debug	D "C:\PROGRAM FILES\BORLAND\CBUILDER5\INCLUDE\VCL\VCL2.H" 10303 10240
	?debug	D "C:\src\IS2\comp\iuNet\iuEncoders.cpp" 10568 20005
	end
