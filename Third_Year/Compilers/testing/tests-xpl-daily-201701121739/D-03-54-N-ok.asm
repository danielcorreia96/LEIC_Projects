segment	.text
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
	push	dword 0
	pop	eax
	cmp	eax, byte 0
	je	near _L1
segment	.rodata
align	4
_L3:
	db	"KO", 0
segment	.text
	push	dword $_L3
	call	prints
	add	esp, 4
	jmp	dword _L2
align	4
_L1:
	push	dword 0
	pop	eax
	cmp	eax, byte 0
	je	near _L4
segment	.rodata
align	4
_L6:
	db	"elsif1", 0
segment	.text
	push	dword $_L6
	call	prints
	add	esp, 4
	jmp	dword _L5
align	4
_L4:
	push	dword 0
	pop	eax
	cmp	eax, byte 0
	je	near _L7
segment	.rodata
align	4
_L9:
	db	"elsif2", 0
segment	.text
	push	dword $_L9
	call	prints
	add	esp, 4
	jmp	dword _L8
align	4
_L7:
	push	dword 0
	pop	eax
	cmp	eax, byte 0
	je	near _L10
segment	.rodata
align	4
_L12:
	db	"elsif3", 0
segment	.text
	push	dword $_L12
	call	prints
	add	esp, 4
	jmp	dword _L11
align	4
_L10:
	push	dword 0
	pop	eax
	cmp	eax, byte 0
	je	near _L13
segment	.rodata
align	4
_L15:
	db	"elsif4", 0
segment	.text
	push	dword $_L15
	call	prints
	add	esp, 4
	jmp	dword _L14
align	4
_L13:
segment	.rodata
align	4
_L16:
	db	"OK", 0
segment	.text
	push	dword $_L16
	call	prints
	add	esp, 4
align	4
_L14:
align	4
_L11:
align	4
_L8:
align	4
_L5:
align	4
_L2:
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
