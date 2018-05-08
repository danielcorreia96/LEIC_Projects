segment	.text
align	4
f:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
segment	.rodata
align	4
_L1:
	dq	6.66000
segment	.text
	push	dword $_L1
	pop	eax
	push	dword [eax+4]
	push	dword [eax]
	push	esp
	pop	eax
	push	dword [eax+4]
	push	dword [eax]
	lea	eax, [ebp+-8]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	pop	eax
	mov	[ecx+4], eax
	add	esp, 8
	lea	eax, [ebp+-8]
	push	eax
	pop	eax
	push	dword [eax+4]
	push	dword [eax]
	fld	qword [esp]
	add	esp, byte 8
	leave
	ret
align	4
g:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	call	f
	add	esp, 0
	sub	esp, byte 8
	fstp	qword [esp]
	push	dword 1
	fild	dword [esp]
	sub	esp, byte 4
	fstp	qword [esp]
	fld	qword [esp]
	add	esp, byte 8
	fld	qword [esp]
	faddp	st1
	fstp	qword [esp]
	push	esp
	pop	eax
	push	dword [eax+4]
	push	dword [eax]
	lea	eax, [ebp+-8]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	pop	eax
	mov	[ecx+4], eax
	add	esp, 8
	lea	eax, [ebp+-8]
	push	eax
	pop	eax
	push	dword [eax+4]
	push	dword [eax]
	fld	qword [esp]
	add	esp, byte 8
	leave
	ret
align	4
global	_main:function
_main:
align	4
xpl:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	call	f
	add	esp, 0
	sub	esp, byte 8
	fstp	qword [esp]
	call	printd
	add	esp, 8
	call	println
	call	g
	add	esp, 0
	sub	esp, byte 8
	fstp	qword [esp]
	call	printd
	add	esp, 8
	call	println
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	pop	eax
	leave
	ret
extern	argc
extern	argv
extern	envp
extern	readi
extern	readd
extern	printi
extern	prints
extern	printd
extern	println
