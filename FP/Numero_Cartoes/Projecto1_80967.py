#80967 Daniel Correia
#Projecto 1

def calc_soma(numero):
    """calc_soma: str -> int
    Funcao que soma os digitos do numero de acordo com o algoritmo de Luhn
    e devolve o valor dessa soma"""
    digitos_total = len(str(numero))
    numero_invertido = ""
    #Vou inverter o numero
    for digito in numero:
        numero_invertido = digito + numero_invertido
        
    #Agora vou somar os digitos do invertido de acordo com o algoritmo de Luhn
    soma_final = 0
    for i in range(0,digitos_total) :
        if i % 2 == 0:
            digito = eval(numero_invertido[i]) * 2
            if digito > 9:
                digito = digito - 9
            soma_final = soma_final + digito
        else:
            soma_final = soma_final + eval(numero_invertido[i])
    
    return soma_final  

def luhn_verifica(numero):  
    """luhn_verifica: str -> bool
    Funcao que verifica o numero do cartao pelo algoritmo de Luhn e 
    devolve True se o cartao for valido e False no caso contrario"""
    #Retiro o ultimo digito para aplicar no ultima parte do algoritmo.
    digito_final = eval(numero) % 10
    numero = eval(numero) // 10
    total = calc_soma(str(numero)) + digito_final
    if total % 10 == 0:
        return True
    else:
        return False
    
def comeca_por(cad1, cad2):
    """comeca_por: str, str -> bool
    Funcao que verifica se cad1 comeca por cad2 e devolve True 
    se isso acontecer e False em caso contrario"""
    if cad2 == cad1[0:len(cad2)]:
        return True
    else:
        return False
    
def comeca_por_um(cad, t_cads):
    """comeca_por_um: str, tuple -> bool
    Funcao que verifica se cad comeca por algum dos elementos do tuplo t_cads 
    e que devolve True se isso acontecer e False em caso contrario"""
    for cad2 in t_cads:
        if comeca_por(cad, cad2) == True:
            return True
    return False

#Lista de redes emissoras: prefixo, comprimento, nome e abreviatura
rede_bancaria =((("34", "37"), (15,), "American Express", "AE"), 
                (("36", "38", "39", "309"), (14,), "Diners Club International", "DCI"),
                (("65"), (16,), "Discover Card", "DC"),
                (("5018", "5020", "5038"), (13, 19), "Maestro", "M"),
                (("50","51","52","53","54","19"), (16,), "Master Card", "MC"),
                (("4026","4405","4508", "426"), (16,), "Visa Electron", "VE"),
                (("4024", "4532", "4556"), (13,16), "Visa", "V"))

def valida_iin(numero):
    """valida_iin(numero): str -> str
    Funcao que avalia o prefixo e o comprimento e que devolve a rede emissora do cartao"""
    digitos_total = len(str(numero))
    for i in range(2,5):
        for rede in rede_bancaria:
            if str(numero)[0:i] in rede[0] and digitos_total in rede[1]:
                return rede[2]
    return ""

def categoria(numero):
    """categoria(numero): str -> str
    Funcao que indica a categoria da entidade correspondente ao numero do cartao"""
    primeiro_digito = numero[0]
    categorias = (("1","Companhias aereas"),("3","Viagens e entretenimento e bancario / financeiro"),("4","Servicos bancarios e financeiros"),("5","Servicos bancarios e financeiros"),("6","Merchandising e bancario / financeiro")) 
    for tuplo in categorias:
        if primeiro_digito in tuplo[0]:    
            return tuplo[1]

def verifica_cc(numero):
    """verifica_cc(numero): int -> tuple
    Funcao que verifica o numero do cartao, indicando a categoria e a rede emissora"""
    numero_final = str(numero)
    if luhn_verifica(numero_final) == True:
        categor = categoria(numero_final)
        rede_cartao = valida_iin(numero_final)
        if rede_cartao == "":
            return "cartao invalido"
        else:
            return (categor, rede_cartao)
    else:
        return "cartao invalido"
    
from random import random
def gera_num_cc(rede):
    """gera_num_cc(rede): str -> int
    Funcao que gera um numero valido de uma entidade de forma aleatoria"""
    digitos_total = 0
    numero = ""
    for tuplo in rede_bancaria:
    #Cada tuplo contem os prefixos, o comprimento e a abreviatura de uma entidade
        if rede == tuplo[3]:
            if tuplo[3] == "M" or tuplo[3] == "V":
                digitos_total = tuplo[1][int(random()*2)]
                numero = tuplo[0][int(random()*3)]
            elif tuplo[3] == "DC":
                digitos_total = tuplo[1][0]
                numero = tuplo[0]
            else:
                digitos_total = tuplo[1][0]
                numero = tuplo[0][int(random()*len(tuplo[0]))]
                        
    while len(numero) < (digitos_total - 1):
        numero = numero + str(int(random()*10))
            
    numero = numero + digito_verificacao(numero)
    return eval(numero)
    
def digito_verificacao(numero):  
    """digito_verificacao(numero): str -> str
    Funcao que determina o ultimo digito do cartao para que o numero seja valido"""
    numero = calc_soma(numero)
    resto = numero % 10
    if resto == 0:
        return str(0)
    else:
        return str(10 - resto)