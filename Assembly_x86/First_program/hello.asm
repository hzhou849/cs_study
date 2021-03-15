;------------------------------------------------------------------------------------------------------
; Assembly x86 - Hello World
;
; To compile run:
;		nasm -felf64 <filename.asm> && ld <filename.o> && ./a.out
;------------------------------------------------------------------------------------------------------

			global		-start
			section		.text
_start:		mov			rax, 1			; system call for write
			mov			rdi, 1			; file handle 1 is stdout
			mov			rsi, message;	; address of string to output
			mov			rdx, 13			; number of bytes 
			syscall						; invoke 