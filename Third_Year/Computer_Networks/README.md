# RC_Project
LEIC Computer Networks (RC) project

Notas de Utilização
---------------------------------------
Aplicacao distribuida simples que permite aos utilizadores submeter pedidos de traducao textual e pedidos de traducao usando uma imagem de texto, recebendo do servidor as respostas correspondentes.

Especificacoes
---------------------------------------
make clean and make
Invocar o TCS: ./TCS.py [-p TCSport]
Invocar o TRS dentro da pasta correspondente a linguagem pretendids: ./TRS.py language [-p TRSport] [-n TCSname] [-e TCSport]
Invocar o User: ./user.py [-n TCSname] [-p TCSport]
