# IST 2014/2015
# Fundamentos da Programacao
# Dezembro de 2014
# Daniel Correia, 80967
# Ines Leite, 81328
# Grupo 41

# TAD coordenada
# Construtor
def cria_coordenada(l,col):
    '''cria_coordenada: inteiro x inteiro -> coordenada
    funcao que recebe dois argumentos inteiros, verifica a validade dos argumentos e devolve elemento do tipo coordenada (l,col)'''
    if l < 1 or l > 4 or isinstance(l,int) == False:
        raise ValueError("cria_coordenada: argumentos invalidos")
    elif col < 1 or col > 4 or isinstance(col,int) == False:
        raise ValueError("cria_coordenada: argumentos invalidos")
    else:
        return (l,col)
#Seletores
def coordenada_linha(c):
    '''coordenada_linha: coordenada -> inteiro  
    funcao que recebe um elemento do tipo coordenada e devolve a respectiva linha'''     
    return c[0]


def coordenada_coluna(c):
    '''coordenada_linha: coordenada -> inteiro  
    funcao que recebe um elemento do tipo coordenada e devolve a respectiva coluna'''    
    return c[1]    

# Reconhecedor
coordenadas = [cria_coordenada(1,1),cria_coordenada(1,2),cria_coordenada(1,3),cria_coordenada(1,4),
                 cria_coordenada(2,1),cria_coordenada(2,2),cria_coordenada(2,3),cria_coordenada(2,4),
                 cria_coordenada(3,1),cria_coordenada(3,2),cria_coordenada(3,3),cria_coordenada(3,4),
                 cria_coordenada(4,1),cria_coordenada(4,2),cria_coordenada(4,3),cria_coordenada(4,4)]

def e_coordenada(x):
    '''e_coordenada: universal -> logico
    funcao que recebe um unico argumento e devolve True caso esse argumento seja do tipo coordenada, e False em caso contrario'''      
    if x in coordenadas:
        return True
    else:
        return False
 
# Teste   
def coordenadas_iguais(c1,c2):
    '''coordenadas_iguais: coordenada x coordenada ->logico
    funcao que recebe como argumentos dois elementos do tipo coordenada, devolve True caso esses argumentos correspondam a mesma posicao (l,c) do tabuleiro, e False em caso contrario'''    
    if e_coordenada(c1) and e_coordenada(c2):    
        return (c1==c2)
    else:
        return False

#-------------------------------------------------------------------------------#
#-------------------------------------------------------------------------------#
#-------------------------------------------------------------------------------#
# TAD tabuleiro
# Construtor
def cria_tabuleiro():
    '''cria_tabuleiro: {} -> tabuleiro 
    funcao que nao recebe qualquer argumento, devolve um tabuleiro vazio do tipo dicionario'''
    tabuleiro = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0],0]
    return tabuleiro

# Seletores
def tabuleiro_posicao(t,c):
    '''tabuleiro_posicao: tabuleiro x coordenada -> inteiro
    funcao que recebe como argumentos um elemento t do tipo tabuleiro, e um elemento c do tipo coordenada ,devolve um elemento do tipo inteiro, que corresponde ao valor na posicao do tabuleiro correspondente a coordenada c'''    
    if e_coordenada(c):
        linha = coordenada_linha(c) - 1
        coluna = coordenada_coluna(c) - 1
        return t[linha][coluna]
    else:
        raise ValueError("tabuleiro_posicao: argumentos invalidos")
    
def tabuleiro_pontuacao(t):
    '''tabuleiro_pontuacao: tabuleiro -> inteiro 
    funcao que recebe como argumento um elemento t do tipo tabuleiro e devolve a pontuacao atual para o tabuleiro t'''    
    return t[4]

def tabuleiro_posicoes_vazias(t):
    '''tabuleiro_posicoes_vazias: tabuleiro -> lista
    funcao que recebe como argumento um elemento t do tipo tabuleiro devolve uma lista contendo as coordenadas de todas as posicoes vazias do tabuleiro t'''     
    lista=[]
    for lin in range(1,5):
        for col in range(1,5):
            coord = cria_coordenada(lin,col)
            if tabuleiro_posicao(t,coord)==0:
                lista = lista + [coord]
    return lista

# Modificadores
def tabuleiro_preenche_posicao(t,c,inteiro):
    '''tabuleiro_preenche_posicao: tabuleiro x coordenada x inteiro -> tabuleiro 
    funcao que recebe como argumentos um elemento t do tipo tabuleiro, um elemento c do tipo coordenada e um inteiro e modifica o tabuleiro t, colocando o valor inteiro na posicao correspondente a coordenada c'''   
    if isinstance(inteiro,int) and e_coordenada(c):
        linha = coordenada_linha(c) - 1
        coluna = coordenada_coluna(c) - 1
        t[linha][coluna] = inteiro
        return t
    else:
        raise ValueError('tabuleiro_preenche_posicao: argumentos invalidos')


def tabuleiro_actualiza_pontuacao(t,v):
    '''tabuleiro_actualiza_pontuacao: tabuleiro x inteiro -> tabuleiro
    funcao que recebe como argumentos um elemento t do tipo tabuleiro e um inteiro v, nao negativo e multiplo de 4. Modifica o tabuleiro t, acrescentando ao valor da respectiva pontuacao v pontos'''    
    if isinstance(v,int) and v >= 0 and v % 4 == 0:
        t[4] = t[4] + v
        return t
    else:
        raise ValueError('tabuleiro_actualiza_pontuacao: argumentos invalidos')

def tabuleiro_reduz(t,d):
    '''tabuleiro_reduz: tabuleiro x cadeia de caracteres -> tabuleiro
    funcao que recebe como argumento um elemento t do tipo tabuleiro e uma cadeia de caracteres d correspondente a uma das 4 acoes possiveis. Modifica o tabuleiro t, reduzindo-o na direcao '''
    # Algoritmo: 1.puxa o tabuleiro onde existirem zeros 
    #            2.soma posicoes do tabuleiro
    #            3.puxa o tabuleiro novamente para eliminar os zeros resultantes das somas    
    
    direccoes = {"N":(range(1,5),range(4,1,-1),range(1,4),(-1,1)), 
             "S":(range(1,5),range(1,4),range(4,1,-1),(1,-1)),
             "W":(range(1,5),range(4,1,-1),range(1,4),(-1,1)),
             "E":(range(1,5),range(1,4),range(4,1,-1),(1,-1))}    
    def reduz_vertical(t,d):
        def posicoes_vazias_vertical(t,d):          
            for col in direccoes[d][0]:
                for lin in direccoes[d][1]:
                    if tabuleiro_posicao(t,cria_coordenada(lin + direccoes[d][3][0],col)) == 0:
                        tabuleiro_preenche_posicao(t,cria_coordenada(lin + direccoes[d][3][0],col),tabuleiro_posicao(t,cria_coordenada(lin,col)))
                        tabuleiro_preenche_posicao(t,cria_coordenada(lin,col),0)
            return t
        posicoes_vazias_vertical(t,d)
        posicoes_vazias_vertical(t,d)
        posicoes_vazias_vertical(t,d)
        for col in direccoes[d][0]:
            for lin in direccoes[d][2]:
                if tabuleiro_posicao(t,cria_coordenada(lin,col)) == tabuleiro_posicao(t,cria_coordenada(lin+direccoes[d][3][1],col)):
                    tabuleiro_preenche_posicao(t,cria_coordenada(lin+direccoes[d][3][1],col),0)
                    tabuleiro_preenche_posicao(t,cria_coordenada(lin,col),tabuleiro_posicao(t,cria_coordenada(lin,col))*2)
                    tabuleiro_actualiza_pontuacao(t,tabuleiro_posicao(t,cria_coordenada(lin,col)))
        posicoes_vazias_vertical(t,d)
        posicoes_vazias_vertical(t,d)
        return t
    
    def reduz_horizontal(t,d):
        def posicoes_vazias_horizontal(t,d):
            for lin in direccoes[d][0]:
                for col in direccoes[d][1]:
                    if tabuleiro_posicao(t,cria_coordenada(lin,col+direccoes[d][3][0])) == 0:
                        tabuleiro_preenche_posicao(t,cria_coordenada(lin,col+direccoes[d][3][0]),tabuleiro_posicao(t,cria_coordenada(lin,col)))
                        tabuleiro_preenche_posicao(t,cria_coordenada(lin,col),0)
            return t
        posicoes_vazias_horizontal(t,d)
        posicoes_vazias_horizontal(t,d)
        posicoes_vazias_horizontal(t,d)
        for lin in direccoes[d][0]:
            for col in direccoes[d][2]:
                if tabuleiro_posicao(t,cria_coordenada(lin,col)) == tabuleiro_posicao(t,cria_coordenada(lin,col+direccoes[d][3][1])):
                    tabuleiro_preenche_posicao(t,cria_coordenada(lin,col+direccoes[d][3][1]),0)
                    tabuleiro_preenche_posicao(t,cria_coordenada(lin,col),tabuleiro_posicao(t,cria_coordenada(lin,col))*2) 
                    tabuleiro_actualiza_pontuacao(t,tabuleiro_posicao(t,cria_coordenada(lin,col))) 
        posicoes_vazias_horizontal(t,d)
        posicoes_vazias_horizontal(t,d)        
        return t        

    if d in ("N","S"):
        return reduz_vertical(t,d)
    elif d in("E","W"):
        return reduz_horizontal(t,d)                                       
    else:
        raise ValueError("tabuleiro_reduz: argumentos invalidos")

# Transformador
def escreve_tabuleiro(t):
    '''escreve_tabuleiro: tabuleiro -> {}
    funcao que recebe como argumento um elemento t do tipo tabuleiro e escreve para o ecra a representacao externa de um tabuleiro de 2048'''    
    if e_tabuleiro(t):
        for i in range (1,5):
            linha=''
            for j in range (1,5):
                linha=linha + "[ " + str(tabuleiro_posicao(t,cria_coordenada(i,j))) +" ] "
            print (linha)     
        print("Pontuacao:", tabuleiro_pontuacao(t))
    else:
        raise ValueError("escreve_tabuleiro: argumentos invalidos")

# Reconhecedores
def e_tabuleiro(x):
    '''e_tabuleiro : universal -> logico
    funcao que recebe um unico argumento, devolvendo True se o seu argumento for do tipo tabuleiro, e False em caso contrario'''
    if isinstance(x,list) and len(x) == 5 and isinstance(x[4],int):
        for i in range(1,4):
            if len(x[i]) != 4:
                return False
        return True
    else:
        return False
                
def tabuleiros_iguais(t1,t2):  
    '''tabuleiros_iguais:tabuleiro x tabuleiro -> logico
    funcao que recebe como argumentos dois elementos t1 e t2 do tipo tabuleiro e devolve True caso t1 e t2 correspondam a dois tabuleiros com a mesma configuracao e pontuacao, e False em caso contrario '''    
    return (t1==t2)

# Testes
def tabuleiro_terminado(t):
    '''tabuleiro_terminado: tabuleiro -> logico
    funcao que recebe como argumento um elemento t do tipo tabuleiro e devolve True caso o tabuleiro t esteja terminado, ou seja, caso esteja cheio e nao existam movimentos possiveis, e False em caso contrario'''    
    t_teste = copia_tabuleiro(t)
    for d in ("N","E","W","S"):
        t_teste = tabuleiro_reduz(t_teste,d)
        if tabuleiros_iguais(t,t_teste) == False:
            return False
    return True
    
#Funcoes adicionais
def copia_tabuleiro(t):
    '''copia_tabuleiro: tabuleiro -> tabuleiro
    funcao que recebe como argumento um elemento do tipo tabuleiro e devolve uma copia do mesmo'''
    copia_t = []
    for i in range (1,5):
        linha=[]
        for j in range (1,5):
            linha=linha + [tabuleiro_posicao(t,cria_coordenada(i,j))]
        copia_t = copia_t + [linha] 
    copia_t += [tabuleiro_pontuacao(t)]    
    return copia_t

from random import random
def preenche_posicao_aleatoria(t):
    '''preenche_posicao_aleatoria: tabuleiro -> tabuleiro
    funcao que recebe um elemento do tipo tabuleiro e preenche uma posicao livre, escolhida aleatoriamente com um dos numeros 2 ou 4'''    
    x = random()
    posicao = int(x*len(tabuleiro_posicoes_vazias(t)))
    probabilidade = int(x*100)
    if probabilidade < 80:
        return tabuleiro_preenche_posicao(t,tabuleiro_posicoes_vazias(t)[posicao],2)       
    else:
        return tabuleiro_preenche_posicao(t,tabuleiro_posicoes_vazias(t)[posicao],4) 
 

def pede_jogada():
    '''pede_jogada: {} -> cadeia de carateres
    funcao que nao recebe qualquer argumento, limitando-se a pedir ao utilizador para introduzir uma direcao (N, S, E ou W)'''    
    jogada = input("Introduza uma jogada (N, S, E, W): ")
    if jogada in ("N", "S", "E", "W"):
        return jogada
    else:
        print("Jogada invalida.")
        return pede_jogada()
    
def jogo_2048():
    '''jogo_2048: {} -> {}
    funcao que nao recebe qualquer argumento,e permite a um utilizador jogar um jogo completo de 2048'''    
    t = cria_tabuleiro()
    preenche_posicao_aleatoria(t)
    preenche_posicao_aleatoria(t)    
    escreve_tabuleiro(t)
    while not tabuleiro_terminado(t):
        d = pede_jogada()
        while tabuleiros_iguais(t,tabuleiro_reduz(copia_tabuleiro(t),d)):
            escreve_tabuleiro(t)
            d = pede_jogada()
        tabuleiro_reduz(t,d)
        preenche_posicao_aleatoria(t)
        escreve_tabuleiro(t)
    print("Jogo Terminado")