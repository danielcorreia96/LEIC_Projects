segment	.text
align	4
global	_main:function
_main:
align	4
xpl:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
segment	.rodata
align	4
_L1:
	dq	1.50000
segment	.text
	push	dword $_L1
	pop	eax
	push	dword [eax+4]
	push	dword [eax]
	call	printd
	add	esp, 8
	call	println
segment	.rodata
align	4
_L2:
	dq	25.0000
segment	.text
	push	dword $_L2
	pop	eax
	push	dword [eax+4]
	push	dword [eax]
	call	printd
	add	esp, 8
	call	println
segment	.rodata
align	4
_L3:
	dq	1.50000
segment	.text
	push	dword $_L3
	pop	eax
	push	dword [eax+4]
	push	dword [eax]
segment	.rodata
align	4
_L4:
	dq	25.0000
segment	.text
	push	dword $_L4
	pop	eax
	push	dword [eax+4]
	push	dword [eax]
	fld	qword [esp]
	add	esp, byte 8
	fld	qword [esp]
	faddp	st1
	fstp	qword [esp]
	call	printd
	add	esp, 8
	call	println
	push	dword 2
	fild	dword [esp]
	sub	esp, byte 4
	fstp	qword [esp]
segment	.rodata
align	4
_L5:
	dq	2.50000
segment	.text
	push	dword $_L5
	pop	eax
	push	dword [eax+4]
	push	dword [eax]
	fld	qword [esp]
	add	esp, byte 8
	fld	qword [esp]
	faddp	st1
	fstp	qword [esp]
	call	printd
	add	esp, 8
	call	println
segment	.rodata
align	4
_L6:
	dq	3.33000
segment	.text
	push	dword $_L6
	pop	eax
	push	dword [eax+4]
	push	dword [eax]
	push	dword 1
	fild	dword [esp]
	sub	esp, byte 4
	fstp	qword [esp]
	fld	qword [esp]
	add	esp, byte 8
	fld	qword [esp]
	faddp	st1
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
