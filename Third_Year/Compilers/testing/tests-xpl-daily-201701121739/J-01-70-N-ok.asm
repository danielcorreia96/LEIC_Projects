segment	.text
align	4
f:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
segment	.rodata
align	4
_L1:
	db	"ola", 0
segment	.text
	push	dword $_L1
	call	prints
	add	esp, 4
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
	call	f
	add	esp, 0
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
