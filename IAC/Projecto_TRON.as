;-----------------------------------------------------------------------------------------;
;	2014/2015																		  	  ;
;	Projecto de Introducao a Arquitetura de Computadores							  	  ;
;	TRON																			  	  ;
;	Turno: 13																		 	  ;
;	Grupo: 24																	 	 	  ;
;		   Daniel Correia, aluno 80967													  ;
;		   Ines Leite, aluna 81328														  ;
;	       Joao Palma, aluno 81212 										     			  ;
;-----------------------------------------------------------------------------------------;
===========================================================================================
;									Constantes										  	  ;
===========================================================================================
SP_INICIAL		EQU		FDFFh		;Stack pointer inicial
IO_WRITE		EQU		FFFEh		;Endereco para escrever na janela de texto
IO_CONTROL		EQU		FFFCh		;Endereco para posicionar o cursor na janela de texto
Inicial			EQU		0110h		;Posicao onde se comeca a escrever o mapa 
Final			EQU		1610h		;Posicao onde se escreve a ultima linha do mapa
Fim				EQU		'@'			;Simbolo para detetar o fim de uma string
Posicao1		EQU		0C18h		;Posicao inicial do jogador 1
Posicao2		EQU		0C38h		;Posicao inicial do jogador 2
Bemvindo_P1		EQU		0C21H		;Posicao da primeira linha de Bem-vindo
Bemvindo_P2		EQU		0D1Dh		;Posicao da segunda linha de Bem-vindo
FimJogo_P1		EQU		0C24h		;Posicao da primeira linha de Fim Jogo
FimJogo_P2		EQU		0D1Ch		;Posicao da segunda linha de Fim Jogo
Baixo			EQU		000Bh		;Associado a direcao para baixo
Cima			EQU		000Ch		;Associado a direcao para cima
Direita			EQU		000Dh		;Associado a direcao para a direita
Esquerda		EQU		000Eh		;Associado a direcao para a esquerda
INT_MASK_ADDR   EQU     FFFAh				;Endereco onde e colocada a INT_MASK 
INT_MASK        EQU     1000101010000011b 	;Mascara das interrupcoes
TIMER_CONTROL	EQU		FFF7h		;Endereco do temporizador 
TIMER_VALUE		EQU		FFF6h   	;Endereco para colocar o valor do temporizador
IO_DISPLAY      EQU     FFF0h		;Endereco para ativar o Display
NIBBLE_MASK     EQU     000fh
NUM_NIBBLES     EQU     4
BITS_PER_NIBBLE EQU     4 
LED_DISPLAY		EQU		FFF8h		;Endereco para ativar os LEDs
LCD_WRITE		EQU		FFF5h		;Endereco para escrever no LCD
LCD_CURSOR		EQU		FFF4h		;Endereco para posicionar o cursor no LCD
LCD_CURSOR_MJ1	EQU		8010h		;Posicao da string "J1: " no LCD
LCD_CURSOR_MJ2	EQU		801ah		;Posicao da string "J2: " no LCD
LCD_MTEMPOMAX	EQU		8000h		;Posicao da string "TEMPO MAX:     s" no LCD
LCD_CURSOR_J1	EQU		8015h		;Posicao da pontuacao do jogador 1 no LCD
LCD_CURSOR_J2	EQU		801fh		;Posicao da pontuacao do jogador 2 no LCD
LCD_TEMPOMAX	EQU		800eh		;Posicao do valor do tempo maximo no LCD
Interruptores	EQU		FFF9h		;Endereco associado aos interruptores
===========================================================================================
;									Variaveis										      ;
===========================================================================================
				ORIG	8020h
linha1			STR		'+------------------------------------------------+', Fim
linha2			STR		'|                                                |', Fim
limpajanela		STR		'                                                                           ', Fim
jogador1		STR		'X', Fim
jogador2		STR		'#', Fim
Bemvindo_M1		STR		'Bem-vindo ao TRON', Fim
Bemvindo_M2		STR		'Pressione I1 para comecar', Fim 
FimJogo_M1		STR		'Fim do Jogo', Fim 
FimJogo_M2		STR		'Pressione I1 para recomecar', Fim 
LCD_Tempo		STR		'TEMPO MAX:     s', Fim
LCD_J1			STR		'J1: ', Fim
LCD_J2			STR		'J2: ', Fim
Posicao_J1		WORD	0C18h		;Posicao do jogador 1 durante o jogo
Posicao_J2		WORD	0C38h		;Posicao do jogador 2 durante o jogo
Direcao_J1		WORD	000Dh		;Direcao do jogador 1 durante o jogo
Direcao_J2		WORD	000Eh		;Direcao do jogador 2 durante o jogo
FlagI1			WORD	0			;Interrupcao para comecar ou recomecar o jogo
FlagI0			WORD	0			;Interrupcao para o jogador 1 virar a esquerda
FlagIB			WORD	0			;Interrupcao para o jogador 1 virar a direita
FlagI7			WORD	0			;Interrupcao para o jogador 2 virar a esquerda
FlagI9			WORD	0			;Interrupcao para o jogador 2 virar a direita
Flag_Colisao_J1	WORD	0			;Flag que ativa quando o jogador 1 colide
Flag_Colisao_J2	WORD	0			;Flag que ativa quando o jogador 2 colide
Flag_Colisao	WORD	0			;Flag que ativa quando ocorre uma colisao 
Pontuacao_J1	WORD	00h			;Pontuacao do jogador 1
Pontuacao_J2	WORD	00h			;Pontuacao do jogador 2
Tempo		    WORD    0000h		;Tempo de jogo mostrado no display
Tempo_Max		WORD	0000h		;Tempo maximo de jogo
Temp_Jogo		WORD	0			
Temp_Velocidade	WORD	0
Velocidade		WORD	7h			;Velocidade dos jogadores
LEDS			WORD	0000h		;LEDS que devem estar ligados
Conta_Rasto_J1	WORD	0			;Contador de posicoes do rasto do jogador 1
Conta_Rasto_J2	WORD	0			;Contador de posicoes do rasto do jogador 2
Rasto_J1		TAB		500d		;Posicoes de memoria para guardar o rasto do jogador 1
Rasto_J2		TAB		500d		;Posicoes de memoria para guardar o rasto do jogador 1
===========================================================================================
;							    Tabela de Interrupcoes								   	  ;
===========================================================================================
				ORIG	FE00h
INT0			WORD	Interrupcao0
INT1			WORD	Interrupcao1
				ORIG	FE07h
INT7			WORD	Interrupcao7
				ORIG	FE09h
INT9			WORD	Interrupcao9
				ORIG	FE0Bh
INTB			WORD	InterrupcaoB
				ORIG	FE0Fh
Int10			WORD	Temporizador
===========================================================================================
;									 Codigo											   	  ;
===========================================================================================
				ORIG	0000h
				MOV		R7, SP_INICIAL
				MOV		SP,R7
				MOV     R7, INT_MASK
				MOV     M[INT_MASK_ADDR], R7
				MOV		R7,FFFFh
				MOV		M[IO_CONTROL], R7
				ENI
				JMP		Inicio
===========================================================================================
;						  Rotinas de Apoio a Interrupcao							  	  ;
===========================================================================================			
Interrupcao0:	INC		M[FlagI0]
				RTI
Interrupcao1:	INC		M[FlagI1]
				RTI
Interrupcao7:	INC		M[FlagI7]
				RTI
Interrupcao9:	INC		M[FlagI9]
				RTI
InterrupcaoB:	INC		M[FlagIB]
				RTI
Temporizador:	MOV		R3,1h
				RTI		

===========================================================================================
;					  Rotinas de Escrita na Janela de Texto					 			  ;
===========================================================================================					
;-----------------------------------------------------------------------------------------;
;	EscreveCar																  		  	  ;
;	Entradas: R2(posicao), R3(caracter)												  	  ;
;	Efeitos: Escreve caracter na posicao.											   	  ;
;-----------------------------------------------------------------------------------------;
EscreveCar:		PUSH	R2
				PUSH	R3
				MOV		M[IO_CONTROL], R2	;posicao
				MOV		M[IO_WRITE],R3		;car a escrever
				POP		R3
				POP		R2
				RET
;-----------------------------------------------------------------------------------------;
;	EscreveStr																		  	  ;
;	Entradas: R1(string), R2(posicao), R3(caracter da string)						  	  ;
;	Efeitos: Escreve a string na posicao.											  	  ;
;-----------------------------------------------------------------------------------------;
EscreveStr:		PUSH	R3
				PUSH	R1
				PUSH	R2
CicloEscString:	MOV		R3,M[R1]
				CMP		R3,Fim
				BR.Z	FimEscString
				CALL	EscreveCar
				INC		R1
				INC		R2
				BR		CicloEscString
FimEscString:	POP		R2
				POP		R1
				POP		R3
				RET			
;-----------------------------------------------------------------------------------------;
;	Bemvindo															 			  	  ;
;	Entradas: R1(mensagem), R2(posicao)									   			  	  ;
;	Efeitos: Escreve as mensagens do inicio do jogo.								  	  ;	 							   
;-----------------------------------------------------------------------------------------;
Bemvindo:		PUSH	R1
				PUSH	R2
				MOV		R2, Bemvindo_P1
				MOV		R1, Bemvindo_M1
				CALL	EscreveStr
				MOV		R2, Bemvindo_P2
				MOV		R1, Bemvindo_M2
				CALL	EscreveStr
				POP		R2
				POP		R1
				RET		
;-----------------------------------------------------------------------------------------;
;	Fim_Jogo																	  	  	  ;
;	Entradas: R1(linha em branco), R2(posicao)										  	  ;
;	Efeitos: Escreve a mensagem de fim de jogo										   	  ;
;-----------------------------------------------------------------------------------------;
Fim_Jogo:		PUSH	R1
				PUSH	R2
				MOV		R1, FimJogo_M1
				MOV		R2, FimJogo_P1
				CALL	EscreveStr
				MOV		R1, FimJogo_M2
				MOV		R2, FimJogo_P2
				CALL	EscreveStr
				POP		R2
				POP		R1
				RET
;-----------------------------------------------------------------------------------------;
;	DesenhaMapa															 			  	  ;
;	Entradas: R1(linha a escrever), R2(posicao)										 	  ;
;	Efeitos: Desenha a moldura na janela de texto.									   	  ;	 							   
;-----------------------------------------------------------------------------------------;
DesenhaMapa:	PUSH	R1				;desenha linhas "+-----+"
				PUSH	R2
				MOV		R2, Inicial		;posicao inicial
				MOV		R1, linha1	;"+"
				CALL	EscreveStr
Colunas:		ADD		R2, 0100h
				MOV		R1, linha2
				CALL 	EscreveStr
				CMP		R2, Final
				BR.NZ	Colunas
				MOV		R1, linha1
				CALL	EscreveStr
				POP		R2
				POP		R1
				RET			
;-----------------------------------------------------------------------------------------;
;	PosicoesIni															  			  	  ;
;	Entradas: R1(simbolo do jogador), R2(posicao do jogador)						   	  ;
;	Efeitos: Coloca os jogadores nas suas posicoes iniciais.						   	  ;
;-----------------------------------------------------------------------------------------;
PosicoesIni:	PUSH	R1
				PUSH	R2
				PUSH	R3
				MOV		R1, jogador1
				MOV		R2, Posicao1
				MOV		R3, Rasto_J1
				MOV		M[Posicao_J1], R2
				MOV		M[R3], R2
				CALL	EscreveStr
				MOV		R1, jogador2
				MOV		R2, Posicao2
				MOV		R3, Rasto_J2
				CALL	EscreveStr
				MOV		M[Posicao_J2], R2
				MOV		M[R3], R2
				POP		R3
				POP		R2
				POP		R1
				RET
;-----------------------------------------------------------------------------------------;
;	MudaPosicao																		   	  ;
;	Entradas: R1(simbolo do jogador), R2(posicao), R3(contador de ciclos), R4(direcao) 	  ;
;	Efeitos: Escreve o simbolo dos jogadores na posicao seguinte					   	  ;
;-----------------------------------------------------------------------------------------;
MudaPosicao:	PUSH	R1
				PUSH	R2
				PUSH	R3
				PUSH	R4
				PUSH	R5
				PUSH	R6
				MOV		M[Temp_Velocidade], R0
				CALL	VerificaDirecao
				MOV		R6, Rasto_J1
				MOV		R5, M[Conta_Rasto_J1]
				MOV		R4, M[Direcao_J1]
				MOV		R2, M[Posicao_J1]
				MOV		R3, R0
				MOV		R1, jogador1
CicloMuda:		CMP		R4, Baixo
				JMP.Z	MudaBaixo
				CMP		R4, Cima
				JMP.Z	MudaCima
				CMP		R4, Direita
				JMP.Z	MudaDireita
				CMP		R4, Esquerda
				JMP.Z	MudaEsquerda
MudaPosicao2:	CMP		R3, 2h
				JMP.Z	MudaFim
				MOV		M[Conta_Rasto_J1], R5
				ADD		R6,R5
				MOV		R5,R0
				MOV		M[R6], R2 
				MOV		M[Posicao_J1], R2	;atualizar a posicao do jogador 1 antes de mover o jogador 2
				MOV		R6, Rasto_J2
				MOV		R5, M[Conta_Rasto_J2]
				MOV		R4, M[Direcao_J2]
				MOV		R2, M[Posicao_J2]
				MOV		R1, jogador2
				JMP		CicloMuda
MudaBaixo:		ADD		R2,0100h
				BR		EscreveNovo
MudaCima:		SUB		R2,0100h
				BR		EscreveNovo
MudaDireita:	INC		R2
				BR		EscreveNovo
MudaEsquerda:	DEC		R2
				BR		EscreveNovo

EscreveNovo:	CALL	EscreveStr
				INC 	R3
				INC		R5
				JMP		MudaPosicao2
				
MudaFim:		MOV		M[Conta_Rasto_J2], R5
				ADD		R6,R5 
				MOV     M[R6], R2
				MOV		M[Posicao_J2], R2		;no MudaFim, R2 tem o valor da nova posicao do jogador 2
				POP		R6
				POP		R5
				POP		R4
				POP		R3
				POP		R2
				POP		R1
				RET		
===========================================================================================
;						  Rotinas de Controlo da Direcao							      ;
===========================================================================================	
;-----------------------------------------------------------------------------------------;
;	VerificaDirecao																	   	  ;
;	Entradas: R1 (direcao do jogador)								   				   	  ;
;	Efeitos: Verifica a direcao do jogador com base nas acoes dos utilizadores		   	  ;
;-----------------------------------------------------------------------------------------;
VerificaDirecao:PUSH	R1
				MOV		R1, M[Direcao_J1]
				CMP		M[FlagI0],R0
				CALL.NZ	ViraEsquerda
				CMP		M[FlagIB],R0
				CALL.NZ	ViraDireita
				MOV		M[Direcao_J1], R1
				MOV		R1, M[Direcao_J2]
				CMP		M[FlagI7],R0
				CALL.NZ	ViraEsquerda
				CMP		M[FlagI9],R0
				CALL.NZ	ViraDireita
				MOV		M[Direcao_J2],R1
ResetFlags:		MOV		M[FlagI0],R0
				MOV		M[FlagI7],R0
				MOV		M[FlagI9],R0
				MOV		M[FlagIB],R0
				POP		R1
				RET
;-----------------------------------------------------------------------------------------;
;	ViraEsquerda																	   	  ;
;	Entradas: R1(direcao inicial)													   	  ;
;	Saidas:	R1 (nova direcao)														   	  ;
;	Efeitos: Altera a direcao do jogador para a esquerda							   	  ;
;-----------------------------------------------------------------------------------------;	
ViraEsquerda:	CMP		R1, Baixo
				BR.Z	DirecaoDireitaE
				CMP		R1, Cima
				BR.Z	DirecaoEsqE
				CMP		R1, Direita
				BR.Z	DirecaoCimaE
				CMP		R1, Esquerda
				BR.Z	DirecaoBaixoE
				
DirecaoBaixoE:	MOV		R1,Baixo
				BR		FimViraEsq
DirecaoCimaE:	MOV		R1,Cima
				BR		FimViraEsq
DirecaoDireitaE:MOV		R1,Direita
				BR		FimViraEsq
DirecaoEsqE:	MOV		R1,Esquerda
				BR		FimViraEsq
				
FimViraEsq:		RET
;-----------------------------------------------------------------------------------------;
;	ViraDireita																		   	  ;
;	Entradas: R1(direcao inicial)													   	  ;
;	Saidas:	R1 (nova direcao)														   	  ;
;	Efeitos: Altera a direcao do jogador para a direita								   	  ;
;-----------------------------------------------------------------------------------------;				
ViraDireita:	CMP		R1, Baixo
				BR.Z	DirecaoEsqD
				CMP		R1, Cima
				BR.Z	DirecaoDireitaD
				CMP		R1, Direita
				BR.Z	DirecaoBaixoD
				CMP		R1, Esquerda
				BR.Z	DirecaoCimaD
				
DirecaoBaixoD:	MOV		R1,Baixo
				BR		FimViraDir
DirecaoCimaD:	MOV		R1,Cima
				BR		FimViraDir
DirecaoDireitaD:MOV		R1,Direita
				BR		FimViraDir
DirecaoEsqD:	MOV		R1,Esquerda
				BR		FimViraDir

FimViraDir:		RET		
===========================================================================================
;								Rotinas de Colisao										  ;
===========================================================================================		
;-----------------------------------------------------------------------------------------;
;	VerificaColisao																	   	  ;
;	Entradas: R1(posicao do jogador), R3(auxiliar das flags de colisao)				   	  ;
;	Efeitos: Verifica se ocorreu colisao e altera a pontuacao do jogo				   	  ;
;-----------------------------------------------------------------------------------------;
VerificaColisao:PUSH	R1
				PUSH	R3
				MOV		R1, M[Posicao_J1]
				MOV		R3,R0
				CALL	ColisaoLinhas
				CALL	ColisaoColunas
				CALL	ColisaoRastoJ2
				CALL	ColisaoRastoJ1
				MOV		M[Flag_Colisao_J1], R3
				MOV		R3,R0
				MOV		R1, M[Posicao_J2]
				CALL	ColisaoLinhas
				CALL	ColisaoColunas
				CALL	ColisaoRastoJ1
				CALL	ColisaoRastoJ2
				MOV		M[Flag_Colisao_J2],R3
				POP		R3
				POP		R1
				RET			
;-----------------------------------------------------------------------------------------;
;	ColisaoLinhas																	  	  ;
;	Entradas: R1(posicao do jogador)												   	  ;
;	Efeitos: Verifica se ocorreu colisao com o topo ou base do mapa					  	  ;
;-----------------------------------------------------------------------------------------;			
ColisaoLinhas:	PUSH	R1
				AND		R1, FF00h
				CMP		R1, 1600h
				BR.Z	ColisaoMapaLin
				CMP		R1, 0100h
				BR.Z	ColisaoMapaLin
ColisaoLinFim:	POP		R1
				RET

ColisaoMapaLin: MOV		R3,1
				MOV		M[Flag_Colisao],R3
				JMP		ColisaoLinFim
;-----------------------------------------------------------------------------------------;
;	ColisaoColunas																	 	  ;
;	Entradas: R1(posicao do jogador)												  	  ;
;	Efeitos: Verifica se ocorreu colisao com o topo ou base do mapa					  	  ;
;-----------------------------------------------------------------------------------------;
ColisaoColunas:	PUSH	R1
				AND		R1, 00FFh
				CMP		R1, 0010h
				BR.Z	ColisaoMapaCol
				CMP		R1, 0041h
				BR.Z	ColisaoMapaCol
ColisaoColFim:	POP		R1
				RET

ColisaoMapaCol:	MOV		R3,1
				MOV		M[Flag_Colisao],R3
				JMP		ColisaoColFim
;-----------------------------------------------------------------------------------------;
;	ColisaoRastoJ1																	  	  ;
;	Entradas: R1(posicao do jogador), R2 (rasto do jogador 1),						  	  ;
;			  R4 (contador), R5 (numero de posicoes do rasto)						  	  ;
;	Efeitos: Verifica se ocorreu colisao com o rasto do jogador 1					  	  ;
;-----------------------------------------------------------------------------------------;				
ColisaoRastoJ1:	PUSH	R1
				PUSH	R2
				PUSH	R4
				PUSH	R5
				MOV		R4,R0
				MOV		R2, Rasto_J1
				MOV		R5, M[Conta_Rasto_J1]
CicloRastoJ1:	CMP		R1, M[R2]
				BR.Z	ColisaoRasto1
				INC		R2
				INC		R4
				CMP		R4,R5
				BR.NZ	CicloRastoJ1
				JMP		FimCicloRastoJ1
				
ColisaoRasto1:	MOV		R3,1
				MOV		M[Flag_Colisao],R3
				JMP		FimCicloRastoJ1

FimCicloRastoJ1:POP		R5
				POP		R4
				POP		R2
				POP		R1
				RET	
;-----------------------------------------------------------------------------------------;
;	ColisaoRastoJ2																	  	  ;
;	Entradas: R1(posicao do jogador), R2 (rasto do jogador 2),						 	  ;
;			  R4 (contador), R5 (numero de posicoes do rasto)						  	  ;
;	Efeitos: Verifica se ocorreu colisao com o rasto do jogador 2					  	  ;
;-----------------------------------------------------------------------------------------;				
ColisaoRastoJ2:	PUSH	R1
				PUSH	R2
				PUSH	R4
				PUSH	R5
				MOV		R4,R0
				MOV		R5, M[Conta_Rasto_J2]
				MOV		R2, Rasto_J2
CicloRastoJ2:	CMP		R1, M[R2]
				BR.Z	ColisaoRasto2
				INC		R2
				INC 	R4
				CMP		R4,R5
				BR.NZ	CicloRastoJ2
				JMP		FimCicloRastoJ2
				
ColisaoRasto2:	MOV		R3,1
				MOV		M[Flag_Colisao],R3
				JMP		FimCicloRastoJ2

FimCicloRastoJ2:POP		R5
				POP		R4
				POP		R2
				POP		R1
				RET					
===========================================================================================
;							 Rotinas do Temporizador								  	  ;
===========================================================================================
;-----------------------------------------------------------------------------------------;
;	Temp																		  	  	  ;
;	Entradas: R1(intervalo de contagem), R2(controlo do temporizador), 				  	  ;
;			  R3 (registo auxiliar associado a rotina de interrupcao) 				  	  ;
;	Efeitos: Utiliza o temporizador para contar 0,1s								  	  ;
;-----------------------------------------------------------------------------------------;
Temp:         	PUSH	R1
				PUSH	R2
				PUSH	R3
				MOV		R3,R0
				MOV		R1, 1
				MOV		R2, 1
				MOV		M[TIMER_VALUE], R1
				MOV 	M[TIMER_CONTROL], R2
Temp_Ciclo:		CMP		R3,R2
				BR.NZ  	Temp_Ciclo
				POP		R3
				POP		R2
				POP		R1
				RET					
;-----------------------------------------------------------------------------------------;
; ContDec:																				  ;
;       Entradas: R1(tempo de jogo), R2 e R3 (operadores da conversao para segundos		  ;
;       Efeitos: Incrementa o tempo de jogo e devolve-o em segundos em 4bits			  ;
;-----------------------------------------------------------------------------------------;
ContDec:		PUSH	R1
				PUSH	R2
				PUSH	R3
				MOV		R1,M[Tempo]
				MOV		R2,000Fh		
				MOV		R3,R2
				AND		R1,R3
				CMP		R1,0009h		;teste para ultimo bit igual a 9
				JMP.NZ	Soma
				MOV		R2, FFF0h
				AND		M[Tempo], R2
				MOV     R2, 00F0h
				MOV     R3, R2	
				AND		R2, M[Tempo]
				CMP		R2,0090h
				JMP.NZ	Soma
				MOV		R2, FF0Fh
				AND		M[Tempo], R2
				MOV     R2, 0F00h
				MOV     R3,R2	
				AND		R2, M[Tempo]
				CMP		R2,0900h
				JMP.NZ	Soma
				MOV		R2, F0FFh
				AND		M[Tempo], R2
				MOV     R2, F000h
				MOV     R3, R2	
				AND		R2, M[Tempo]
				CMP		R2, 9000h
				JMP.NZ	Soma
				MOV		R4,R0
				
FimCont:		POP		R3
				POP		R2
				POP		R1
				RET
				
Soma:			MOV     R1, 1111h
				AND 	R1, R3
				ADD		M[Tempo], R1
				JMP		FimCont
;-----------------------------------------------------------------------------------------;
;	EscCont																		   	   	  ;
;	Entradas: R1 (tempo de jogo), R2(numero de nibbles), R3(endereco do display)	   	  ;
;	Efeitos: Efetua a escrita do tempo de jogo no display 							   	  ;
;-----------------------------------------------------------------------------------------;
EscCont:        PUSH    R1
                PUSH    R2
                PUSH    R3
                DSI
                MOV     R2, NUM_NIBBLES
                MOV     R3, IO_DISPLAY
CicloEsc:       MOV     R1, M[Tempo]
                AND     R1, NIBBLE_MASK
                MOV     M[R3], R1
                ROR     M[Tempo], BITS_PER_NIBBLE
                INC     R3
                DEC     R2
                JMP.NZ   CicloEsc
                ENI
                POP     R3
                POP     R2
                POP     R1
                RET
;-----------------------------------------------------------------------------------------;
;	VerNivelLEDSVel																  	  	  ;
;	Entradas: R1(tempo de jogo), R2(velocidade), R3(LEDS a ligar)					  	  ;
;	Efeitos: Verifica o nivel em funcao do tempo de jogo							  	  ;
;			 Altera a velocidade dos jogadores e os LEDS a ligar					  	  ;
;-----------------------------------------------------------------------------------------;				
VerNivelLEDSVel:PUSH	R1
				PUSH	R2
				PUSH	R3
				MOV		R1, M[Tempo]
				MOV		R2, M[Velocidade]
				MOV		 R3, M[LEDS]
				CMP		R1,10
				BR.N	Nivel1
				CMP		R1,20h
				BR.N	Nivel2
				CMP		R1,40h
				BR.N	Nivel3
				CMP		R1,60h
				BR.N	Nivel4
				BR.NN	Nivel5
				
Nivel1:			MOV		R2, 7h
				JMP		NivelFim
Nivel2:			MOV		R2, 5h
				MOV		R3, 000Fh
				JMP		NivelFim				
Nivel3:			MOV		R2, 3h
				MOV		R3, 00FFh
				JMP		NivelFim				
Nivel4:			MOV		R2, 2h
				MOV		R3, 0FFFh
				JMP		NivelFim				
Nivel5:			MOV		R2, 1h
				MOV		R3, FFFFh
				JMP		NivelFim				

NivelFim:		MOV		M[Tempo], R1
				MOV		M[Velocidade], R2
				MOV		M[LED_DISPLAY],R3
				MOV		M[LEDS], R3
				POP		R3
				POP		R2
				POP		R1
				RET	
===========================================================================================
;								 Rotinas do LCD											  ;
===========================================================================================
;-----------------------------------------------------------------------------------------;
;	EscreveCarLCD																	  	  ;
;	Entradas: R1(caracter a escrever), R2(posicao no LCD)							  	  ;
;	Efeitos: Escreve o caracter na posicao do LCD									  	  ;
;-----------------------------------------------------------------------------------------;
EscreveCarLCD:	PUSH	R2
				PUSH	R3
				MOV		M[LCD_CURSOR], R2	;posicao
				MOV		M[LCD_WRITE],R3		;car a escrever
				POP		R3
				POP		R2
				RET
;-----------------------------------------------------------------------------------------;
;	EscreveStrLCD																	  	  ;
;	Entradas: R1(string a escrever), R2(posicao no LCD), R3(caracter da string)		  	  ;
;	Efeitos: Escreve a string na posicao do LCD										  	  ;
;-----------------------------------------------------------------------------------------;				
EscreveStrLCD:	PUSH	R3
				PUSH	R1
				PUSH	R2
CicloEscStrLCD:	MOV		R3,M[R1]
				CMP		R3,Fim
				BR.Z	FimEscStringLCD
				CALL	EscreveCarLCD
				INC		R1
				INC		R2
				BR		CicloEscStrLCD
FimEscStringLCD:POP		R2
				POP		R1
				POP		R3
				RET		
;-----------------------------------------------------------------------------------------;
;	TextoLCD															  			  	  ;
;	Entradas: R1(texto a escrever), R2(posicao no LCD)								 	  ;
;	Efeitos: Escreve o tempo maximo no LCD											  	  ;
;-----------------------------------------------------------------------------------------;
TextoLCD:		PUSH	R1
				PUSH	R2
				MOV		R2, LCD_MTEMPOMAX
				MOV		R1, LCD_Tempo
				CALL	EscreveStrLCD
				MOV		R2, LCD_CURSOR_MJ1
				MOV		R1, LCD_J1
				CALL	EscreveStrLCD
				MOV		R2, LCD_CURSOR_MJ2
				MOV		R1, LCD_J2
				CALL	EscreveStrLCD
				POP		R2
				POP		R1
				RET			
;-----------------------------------------------------------------------------------------;
;	EscContLCD															  			  	  ;
;	Entradas: R1(tempo maximo de jogo), R2(auxiliar), R3(posicao no LCD)			  	  ;
;	Efeitos: Escreve o tempo maximo no LCD											   	  ;
;-----------------------------------------------------------------------------------------;				
EscContLCD:     PUSH    R1
                PUSH    R2
                PUSH    R3
                MOV     R2, 4
                MOV     R3, LCD_TEMPOMAX
CicloEscLCD:    MOV     R1, M[Tempo_Max]
                AND     R1, 000fh
				ADD		R1, 0030h
				MOV		M[LCD_CURSOR], R3
				MOV		M[LCD_WRITE], R1
                MOV     M[R3], R1
                ROR     M[Tempo_Max], 4
                DEC     R3
                DEC     R2
                JMP.NZ   CicloEscLCD
                POP     R3
                POP     R2
                POP     R1
                RET
;-----------------------------------------------------------------------------------------;
;	PontosJ1_LCD																  	  	  ;
;	Entradas: R1(pontuacao do jogador 1), R2(auxiliar), R3(posicao no LCD)			  	  ;
;	Efeitos: Escreve a pontuacao do jogador 1 no LCD								  	  ;
;-----------------------------------------------------------------------------------------;				
PontosJ1_LCD:	PUSH    R1
                PUSH    R2
                PUSH    R3
                MOV     R2,4
                MOV     R3, LCD_CURSOR_J1
CicloPontosJ1: 	MOV     R1, M[Pontuacao_J1]
				AND     R1, 000fh
				ADD		R1, 0030h
				MOV		M[LCD_CURSOR], R3
				MOV		M[LCD_WRITE], R1
                MOV     M[R3], R1
                ROR     M[Pontuacao_J1], 4
                DEC     R3
                DEC     R2
                JMP.NZ   CicloPontosJ1
                POP     R3
                POP     R2
                POP     R1
                RET
;-----------------------------------------------------------------------------------------;
;	PontosJ2_LCD																  	 	  ;
;	Entradas: R1(pontuacao do jogador 2), R2(auxiliar), R3(posicao no LCD)			  	  ;
;	Efeitos: Escreve a pontuacao do jogador 2 no LCD								  	  ;
;-----------------------------------------------------------------------------------------;
PontosJ2_LCD:	PUSH    R1
                PUSH    R2
                PUSH    R3
                MOV     R2,4
                MOV     R3, LCD_CURSOR_J2
CicloPontosJ2: 	MOV     R1, M[Pontuacao_J2]
				AND     R1, 000fh
				ADD		R1, 0030h
				MOV		M[LCD_CURSOR], R3
				MOV		M[LCD_WRITE], R1
                MOV     M[R3], R1
                ROR     M[Pontuacao_J2], 4
                DEC     R3
                DEC     R2
                JMP.NZ   CicloPontosJ2
                POP     R3
                POP     R2
                POP     R1
                RET
				
===========================================================================================
;							 Rotinas de Fim de Jogo									  	  ;
===========================================================================================				
;-----------------------------------------------------------------------------------------;
;	Pontuacoes																		  	  ;
;	Entradas: Flag_Colisao_J1,Flag_Colisao_J2,Pontuacao_J1,Pontuacao_J2				   	  ;
;	Efeitos: Altera as pontuacoes dos jogadores	em funcao do resultado do jogo		  	  ; 												   						
;-----------------------------------------------------------------------------------------;				
Pontuacoes:		CMP		M[Flag_Colisao_J1], R0
				BR.Z	VitoriaJ1		
				CMP		M[Flag_Colisao_J2], R0
				BR.Z	VitoriaJ2
Empate:			RET

VitoriaJ1:		INC		M[Pontuacao_J1]
				RET
			
VitoriaJ2:		INC		M[Pontuacao_J2]
				RET

;-----------------------------------------------------------------------------------------;
;	TempoMaximo																	  	  	  ;
;	Entradas: R1(tempo de jogo)														  	  ;
;	Efeitos: Altera o valor do tempo maximo de jogo.								  	  ;
;-----------------------------------------------------------------------------------------;				
TempoMaximo:	PUSH	R1
				MOV		R1, M[Tempo]
				CMP		R1, M[Tempo_Max]
				BR.NP	FimTempoMax
				MOV		M[Tempo_Max], R1
FimTempoMax:	POP		R1
				RET
				
===========================================================================================
;							Rotinas de Reset do Jogo								 	  ;
===========================================================================================
;-----------------------------------------------------------------------------------------;
;	LimpaJanela																		  	  ;
;	Entradas: R1(linha em branco), R2(posicao)										  	  ;
;	Efeitos: Limpa a janela de texto.												  	  ;
;-----------------------------------------------------------------------------------------;
LimpaJanela:	PUSH 	R1 
				PUSH	R2
				MOV 	R1, limpajanela 
				MOV		R2, 0000h 
CicloLimpa:		CALL 	EscreveStr
				MOV		R1, limpajanela 
				AND 	R2,	ff00h
				ADD		R2,0100h 
				CMP		R2,1800h 
				BR.NZ	CicloLimpa 
				POP	R1 
				POP	R2 
				RET	
;-----------------------------------------------------------------------------------------;
;	LimpaRastos																		   	  ;
;	Entradas: R1(rasto), R2(posicao)												  	  ;
;	Efeitos: Limpa as posicoes do rasto guardadas em memoria.						  	  ;
;-----------------------------------------------------------------------------------------;				
LimpaRastos:	PUSH	R1
				PUSH	R2
				MOV		R1, Rasto_J1
				MOV		R2,R0
Ciclo_Limpa:	MOV		M[R1],R0
				INC		R1
				INC		R2
				CMP		R2,999h
				BR.NZ	Ciclo_Limpa
				POP		R2
				POP		R1
				RET
;-----------------------------------------------------------------------------------------;
;	ResPosDirecao																	  	  ;
;	Entradas: R1(registo auxiliar)												  	  	  ;
;	Efeitos: Reset das posicoes e direcoes dos jogadores para os valores iniciais.	   	  ;
;-----------------------------------------------------------------------------------------;	
ResPosDirecao:	PUSH	R1
				MOV		R1,Posicao1
				MOV		M[Posicao_J1],R1
				MOV		R1,Direita
				MOV		M[Direcao_J1],R1
				MOV		R1,Posicao2
				MOV		M[Posicao_J2],R1
				MOV		R1,Esquerda
				MOV		M[Direcao_J2],R1
				POP		R1
				RET
;-----------------------------------------------------------------------------------------;
;	ResetFlagsJogo																	  	  ;
;	Efeitos: Reset das flags de jogo e dos contadores associados ao temporizador	  	  ;
;-----------------------------------------------------------------------------------------;
ResetFlagsJogo:	MOV		M[FlagI1], R0
				MOV		M[FlagI0],R0
				MOV		M[FlagI7],R0
				MOV		M[FlagI9],R0
				MOV		M[FlagIB],R0
				MOV		M[Flag_Colisao], R0
				MOV		M[Flag_Colisao_J1], R0
				MOV		M[Flag_Colisao_J2], R0
				MOV		M[Temp_Velocidade], R0
				MOV		M[Temp_Jogo], R0
				RET
;-----------------------------------------------------------------------------------------;
;	ResTempo																		  	  ;
;	Entradas: R1(registo auxiliar)												  	   	  ;
;	Efeitos: Reset do tempo de jogo, velocidade, LEDS e  contador de posicoes do rasto 	  ;
;-----------------------------------------------------------------------------------------;
ResetTempo:		PUSH	R1
				MOV		R1,0000h
				MOV		M[Tempo], R1
				MOV		M[LEDS], R1
				MOV		R1,7h
				MOV		M[Velocidade], R1
				MOV		M[Conta_Rasto_J1], R0
				MOV		M[Conta_Rasto_J2], R0
				POP		R1
				RET
===========================================================================================
;						Rotinas do Programa Principal								  	  ;
===========================================================================================				
;-----------------------------------------------------------------------------------------;
;	AtualizaTempo																	  	  ;
;	Efeitos: Altera o valor do tempo de jogo										  	  ;
;-----------------------------------------------------------------------------------------;				
AtualizaTempo:	MOV		M[Temp_Jogo], R0
				CALL	ContDec
				CALL	EscCont
				RET
;-----------------------------------------------------------------------------------------;
;	Movimentos																	  	  	  ;
;	Efeitos: Movimenta os jogadores e verifica se ocorreram colisoes				  	  ;
;-----------------------------------------------------------------------------------------;
Movimentos:		CALL	MudaPosicao
				CALL	VerificaColisao
				RET
;-----------------------------------------------------------------------------------------;
;	FimJogo																	  	   	  	  ;
;	Efeitos: Escreve mensagem de fim de jogo 										  	  ;
;			 Atualiza as pontuacoes e o tempo maximo no LCD 						  	  ;
;-----------------------------------------------------------------------------------------;				
FimJogo:		CALL	Fim_Jogo
				CALL	Pontuacoes
				CALL	TempoMaximo
				CALL	PontosJ1_LCD
				CALL	PontosJ2_LCD
				CALL	TextoLCD
				CALL	EscContLCD
				RET
===========================================================================================
;								 Codigo Principal									  	  ;
===========================================================================================				
Inicio:			MOV		M[FFFCh], R2
				CALL	Bemvindo
				CALL	TextoLCD
				ENI
Comecar:		CMP		M[FlagI1],R0
				BR.Z	Comecar
Base_Jogo:		CALL	LimpaJanela
				CALL	LimpaRastos
				CALL	ResPosDirecao
				CALL	ResetFlagsJogo
				CALL	ResetTempo
				CALL	DesenhaMapa
				CALL 	PosicoesIni
Ciclo_Temp:		ENI
Pausa:			MOV		R4, M[Interruptores]
				TEST	R4, 0080h
				BR.NZ	Pausa
				CALL	Temp
				INC		M[Temp_Jogo]
				INC		M[Temp_Velocidade]
				MOV		R4,M[Temp_Jogo]
				CMP		R4, 10d
				CALL.Z	AtualizaTempo
				CALL	VerNivelLEDSVel
				MOV		R4, M[Temp_Velocidade]
				CMP		R4, M[Velocidade]
				CALL.Z	Movimentos
				MOV		R4, M[Flag_Colisao]
				CMP		R4,1h
				JMP.Z	Ciclo1
				JMP		Ciclo_Temp
Ciclo1:			CALL	FimJogo
				ENI
				JMP		Comecar