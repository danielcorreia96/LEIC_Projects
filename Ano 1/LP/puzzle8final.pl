%Projecto LP - 2014/2015 Semestre 2
%Grupo 20
%Daniel Correia aluno 80967
%Pedro Caldeira aluno 81888

%escreve1puzzle/1 - escreve1puzzle(Tabuleiro).
%Recebe um tabuleiro e escreve-o no output.
escreve1puzzle([]):-nl.
escreve1puzzle([X,Y,Z|R]):-tab(1),escreve(X),tab(2),escreve(Y),tab(2),escreve(Z),tab(1), nl, escreve1puzzle(R),!.

%escreve/1 - escreve(Elemento).
%Recebe um elemento do tabuleiro e escreve-o no output.

escreve(X):- X =:= 0, write(' ').
escreve(X):- write(X).

%escreve_transformação/2 - escreve_transformacao(Inicial,Final).
%Recebe dois tabuleiros (inicial e final) e escreve a representacao da transformacao no output.

escreve_transformacao([A1,B1,C1,D1,E1,F1,G1,H1,I1],[A2,B2,C2,D2,E2,F2,G2,H2,I2]):-writeln('Transformacao desejada:'),
	tab(1),escreve(A1),tab(2),escreve(B1),tab(2),escreve(C1),tab(6),escreve(A2),tab(2),escreve(B2),tab(2),escreve(C2),tab(1),nl,
	tab(1),escreve(D1),tab(2),escreve(E1),tab(2),escreve(F1),write('  ->  '),escreve(D2),tab(2),escreve(E2),tab(2),escreve(F2),tab(1),nl,
	tab(1),escreve(G1),tab(2),escreve(H1),tab(2),escreve(I1),tab(6),escreve(G2),tab(2),escreve(H2),tab(2),escreve(I2),tab(1),nl.

%indice/3 - indice(Lista, Elemento, Posicao).
%Recebe um tabuleiro e um elemento e devolve a posicao do elemento no tabuleiro.

indice(L,X,I):- indice(L,X,I,0),!.
indice([E|R],X,I,Ac):- E=\=X, Ac1 is Ac+1, indice(R,X,I,Ac1).
indice([E|_],E,I,I).

%elemento/3 - elemento(Lista, Elemento, Posicao).
%Recebe um tabuleiro e um indice e devolve o elemento dessa posicao do tabuleiro.

elemento([E|_],E,0).
elemento([_|R],E,I):- I1 is I-1, elemento(R,E,I1),!.

%substitui/4 - substitui(Lista, Elemento, Posicao, Resultado).
%Recebe um tabuleiro, um elemento e um posicao e devolve o tabuleiro alterado com o novo elemento na posicao do tabuleiro.

substitui([_|R],E,0,[E|R]).
substitui([P|R1],E,I,[P|R2]):-	I > 0, I1 is I-1,
								substitui(R1,E,I1,R2),!.

%mov_legal/4 - mov_legal(Configuração 1, Movimento, Peça Movido, Configuração 2 Resultante).
%Afirma que o tabuleiro C2 é obtido do tabuleiro C1 fazendo o movimento M com a peça P.

mov_legal(C1,c,P,C2):-	mov_cima(C1,P,C2).
mov_legal(C1,b,P,C2):-	mov_baixo(C1,P,C2).
mov_legal(C1,e,P,C2):-	mov_esquerda(C1,P,C2).
mov_legal(C1,d,P,C2):-	mov_direita(C1,P,C2).

%mov_direcao/3 - mov_direcao(Tabuleiro C1, Peca P, Tabuleiro C2).
%Recebe um tabuleiro C1 e a peca P e devolve o tabuleiro C2 resultante de mover a peca P na direcao correspondente.

mov_cima(C1,P,C2):-	indice(C1,0,I), I < 6, I1 is I + 3,
						elemento(C1,P,I1), altera_lista(C1,I,I1,P,C2).
mov_baixo(C1,P,C2):-	indice(C1,0,I), I > 2, I1 is I - 3,
						elemento(C1,P,I1), altera_lista(C1,I,I1,P,C2).
mov_esquerda(C1,P,C2):-	indice(C1,0,I), I mod 3 =\= 2, I1 is I + 1,
						elemento(C1,P,I1), altera_lista(C1,I,I1,P,C2).
mov_direita(C1,P,C2):-	indice(C1,0,I), I mod 3 =\= 0, I1 is I - 1,
						elemento(C1,P,I1), altera_lista(C1,I,I1,P,C2).

%altera_lista/5 - altera_lista(Tabuleiro C1, Indice, Indice1, P, C2).
%Recebe um tabuleiro C1, duas posicoes I e I1 E e a peca P e devolve o tabuleiro C2 resultante de colocar a peca P na posicao I e a peca 0 na posicao I1.

altera_lista(C1,I,I1,P,C2):-	substitui(C1,P,I,C3),
								substitui(C3,0,I1,C2).

%resolve_manual/2 - resolve_manual(Tabuleiro C1, Tabuleiro C2 Final).
%	Este predicado origina um ciclo que pede ao utilizador que introduza um movimento,
%		verifica se este é um movimento legal, e executa o movimento desejado.
%		Este ciclo termina quando for obtido o Tabuleiro C2 Final.

resolve_manual(C1,C2):- transformacao_possivel(C1,C2),escreve_transformacao(C1,C2),
						resolve(C1,C2),!.

resolve(C1,C1):- writeln('Parabens!'),!.
resolve(C1,C2):- writeln('Qual o seu movimento?'),
				 read(M), mov_legal(C1,M,_,C3),nl,
				 escreve1puzzle(C3), resolve(C3,C2).

resolve(C1,C2):- writeln('Movimento ilegal'),
				 resolve(C1,C2),!.

%lista_configuracoes/2 - lista_configuracoes(Lista Ltab, Tabuleiro C1).
%Recebe uma lista de tabuleiros Ltab e um tabuleiro C1 e devolve True se C1 pertence a lista Ltab.

lista_configuracoes([C|_],C).
lista_configuracoes([_|R],C):- lista_configuracoes(R,C).

%escreve_movimentos/1 - escreve_movimentos(Lista de Movimentos).
%Recebe uma lista de movimentos e escreve-os no output.

escreve_movimentos([M, P| []]) :-escreve_mov(M,P),write('.'),nl.
escreve_movimentos([M,P|R]):- escreve_mov(M,P),nl, escreve_movimentos(R).

escreve_mov(c, P):- write('mova a peca '),write(P),write(' para cima').
escreve_mov(b, P):- write('mova a peca '),write(P),write(' para baixo').
escreve_mov(d, P):- write('mova a peca '),write(P),write(' para a direita').
escreve_mov(e, P):- write('mova a peca '),write(P),write(' para a esquerda').

%inverte_lista/2 - inverte_lista(Lista Li, Lista Ordenada Lo).
%Recebe uma lista Li e devolve a lista Lo resultante de inverter a ordem dos elementos de Li.

inverte_lista(L,Lo):- inverte_lista(L,[],Lo).
inverte_lista([],L,L).
inverte_lista([M,P|R],T,Lo):- inverte_lista(R,[M,P|T],Lo).

%resolve_cego/2 - resolve_cego(Tabuleiro C1, Tabuleiro C2 Final)
%	Este predicado origina um ciclo que gera movimentos possiveis de forma "aleatoria" e vai alterando o tabuleiro.
%		Este ciclo termina quando for obtido o Tabuleiro C2 Final.

resolve_cego(C1,C1):-escreve_transformacao(C1,C1),!.

resolve_cego(C1,C2):-  transformacao_possivel(C1,C2),escreve_transformacao(C1,C2),
						  resolve_c(C1,C2,[],[C1],_),!.

%resolve_c/5 - resolve_c(Tabuleiro C1, Tabuleiro Final C2, Lista de jogadas (movimento e peca) Lj, Lista de tabuleiros Lc, Direcao).
%Auxiliar do ciclo do resolve cego que testa se um movimento e possivel e se chama recursivamente ate obter o tabuleiro C2.
resolve_c(C1,C1,Lj,_,_):-	inverte_lista(Lj,Ls),
							escreve_movimentos(Ls),!.

resolve_c(C1,C2,Lj,Lc,c):-	mov_legal(C1,c,P,C3),
							not(lista_configuracoes(Lc,C3)),
							resolve_c(C3,C2,[c,P|Lj],[C3|Lc],_),!.

resolve_c(C1,C2,Lj,Lc,b):-	mov_legal(C1,b,P,C3),
							not(lista_configuracoes(Lc,C3)),
							resolve_c(C3,C2,[b,P|Lj],[C3|Lc],_),!.

resolve_c(C1,C2,Lj,Lc,e):-	mov_legal(C1,e,P,C3),
							\+ lista_configuracoes(Lc,C3),
							resolve_c(C3,C2,[e,P|Lj],[C3|Lc],_),!.

resolve_c(C1,C2,Lj,Lc,d):-	mov_legal(C1,d,P,C3),
							\+ lista_configuracoes(Lc,C3),
							resolve_c(C3,C2,[d,P|Lj],[C3|Lc],_),!.

%no/5 - estrutura que armazena as informacoes necessarias para o resolve_info_h.
%Tabuleiro C.
%Valor F - soma de G com H.
%Valor G - numero de jogadas efetuadas.
%Valor H - numero de pecas erradas.
%Lista de movimentos M.
%cria_no/5 - cria_no(Tabuleiro C, Valor F, Valor G, Valor H, Lista de Movimentos M, no).
%Recebe um tabuleiro C, um valor F, um valor G, um valor H e uma lista de movimentos M e devolve um no que contem estas informacoes.

cria_no(C, F, G, H, M,no(C,F,G,H,M)).

%calculaH/3 - calculaH(Tabuleiro C2, Tabuleiro C, Valor H).
%Recebe dois tabuleiros C2 e C e devolve o valor H resultante de calcular o numero de inversoes de C em relacao a C2.

calculaH([],[],0).
calculaH([_|R1],[E2|R2],N):- E2=:=0,!,calculaH(R1,R2,N).
calculaH([E1|R1],[E2|R2],N):- E2\=E1,!,calculaH(R1,R2,N1),N is N1+1.
calculaH([E1|R1],[E2|R2],N):- E2=:=E1,!,calculaH(R1,R2,N).

%buscafmenor/3 - buscafmenor(Lista de nos Bag, No com valor F menor Res, Tabuleiro Final C2).
%Recebe uma lista de nos Bag e devolve o no Res com valor F menor existente na Bag.

buscafmenor([no(C,F,G,H,M)|Bag],Res,Fechados):- buscafmenor(Bag,F,Res,no(C,F,G,H,M),Fechados),!.
buscafmenor([no(C,F1,G,H,M)|Bag],F,Res,_,Fechados):-	F1 < F,
											not(lista_configuracoes(no(C,F1,G,H,M),Fechados)),!,
											buscafmenor(Bag,F1,Res,no(C,F1,G,H,M),Fechados).
buscafmenor([no(_,_,_,_,_)|Bag],F,Res,Ac,_):- buscafmenor(Bag,F,Res,Ac,_),!.
buscafmenor([],_,Res,Res,_).

%comparabag/3 - comparabag(Lista de nos Bag, Lista de nos fechados Fechados, Lista de nos resultante Bag2)
%Recebe uma lista de nos Bag e compara os seus elementos com Fechados e devolve a lista de nos Bag2 resultante de retirar os elementos em comum com Fechados.

comparabag(Bag,Fechados,Bag2):- comparabag(Bag,Fechados,Bag2,[]),!.
comparabag([no(C,_,_,_,_)|Bag],Fechados,Bag2,Ac):- member(no(C,_,_,_,_),Fechados),comparabag(Bag,Fechados,Bag2,Ac),!.
comparabag([no(C,F,G,H,M)|Bag],Fechados,Bag2,Ac):- comparabag(Bag,Fechados,Bag2,[no(C,F,G,H,M)|Ac]),!.
comparabag([],_,Bag2,Bag2).

%inverte_bag/2 inverte_bag(Bag Inicial L, Bag Ordenada Lo).
%Recebe uma bag L e devolve a bag Lo resultante de inverter a ordem dos elementos de L.

inverte_bag(L,Lo):- inverte_bag(L,[],Lo).
inverte_bag([],L,L).
inverte_bag([no(C,F,G,H,M)|R],T,Lo):- inverte_bag(R,[no(C,F,G,H,M)|T],Lo).

%resolve_info_h/2 - resolve_info_h(Tabuleiro Inicial C1, Tabuleiro Final C2).
%Recebe dois tabuleiros (inicial C1 e final C2) e aplica a resolucao informada segundo a heuristica de Hamming.

resolve_info_h(C1,C1):-escreve_transformacao(C1,C1),!.

resolve_info_h(C1,C2):- transformacao_possivel(C1,C2),escreve_transformacao(C1,C2), calculaH(C1,C2,H),cria_no(C1,H,0,H,[],No), informada(No,[No],[],C2),!.


informada(_,Abertos,_,C2):-	member(no(C2,_,_,_,M),Abertos), inverte_lista(M,Minv), escreve_movimentos(Minv),!.

informada(no(C1,F,G,H,M),Abertos,Fechados,C2):- findall(no(C,F1,G1,H1,[M1,P|M]),(mov_legal(C1,M1,P,C),calculaH(C2,C,H1),G1 is G + 1,F1 is G1 + H1),Bag),
																	 delete(Abertos,no(C1,F,G,H,M),Aux_abertos),
																	 comparabag(Bag,Fechados,BagAux),
																	 inverte_bag(BagAux,NovosNosAbertos),
																	 append(NovosNosAbertos,Aux_abertos,Novo_Abertos),
																	 buscafmenor(Novo_Abertos,Noexp,C2),
																	 informada(Noexp,Novo_Abertos,[no(C1,F,G,H,M)|Fechados],C2),!.

%transformacao_possivel/2 - transformacao_possivel(Tabuleiro Inicial C1, Tabuleiro Final C2).
%Recebe dois tabuleiros e devolve True se for possivel transformar C1 em C2.

transformacao_possivel(C1,C2):- paridade(C1,P1), paridade(C2,P2), P1 =:= P2.

%paridade/2 - paridade(Tabuleiro C, Paridade P).
%Recebe um tabuleiro C e devolve a sua paridade P.

paridade(C,P):- paridade(C,P,0).
paridade([],P,P):-!.
paridade([E|R],P,Temp):- aux_paridade(E,R,Inv),Temp1 is (Temp + Inv) mod 2, paridade(R,P,Temp1).

%aux_paridade/3 - aux_paridade(Elemento E, Resto do Tabuleiro R, Numero de inversoes Inv).
%Recebe um elemento, o resto do tabuleiro R a partir do elemento E e devolve o numero de inversoes Inv.

aux_paridade(_,[],0):-!.
aux_paridade(0,_,0):-!.
aux_paridade(E,[0|R],Inv):- aux_paridade(E,R,Inv),!.
aux_paridade(E,[S|R],Inv):- E > S, aux_paridade(E,R,Inv1), Inv is Inv1 + 1,!.
aux_paridade(E,[_|R],Inv):- aux_paridade(E,R,Inv),!.  