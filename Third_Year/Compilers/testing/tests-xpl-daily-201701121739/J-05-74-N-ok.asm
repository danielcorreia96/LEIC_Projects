segment	.text
align	4
pi:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	push	dword 314
	push	dword [esp]
	lea	eax, [ebp+-4]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	add	esp, 4
	lea	eax, [ebp+-4]
	push	eax
	pop	eax
	push	dword [eax]
	pop	eax
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
	push	dword 0
	lea	eax, [ebp+-4]
	push	eax
	pop	ecx
	pop	eax
	mov	[ecx], eax
	call	pi
	add	esp, 0
	push	eax
	call	printi
	add	esp, 4
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
