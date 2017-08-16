/* TABELA USER */
INSERT INTO user VALUES ('111111111', 'Antonio Silva', '111111111');
INSERT INTO user VALUES ('222222222', 'Filipe Augusto', '222222222');
INSERT INTO user VALUES ('333333333', 'Nuno Mansinho', '333333333');
INSERT INTO user VALUES ('444444444', 'Maria Cardoso', '444444444');

/* TABELA FISCAL */
INSERT INTO fiscal VALUES ('1', 'FiscalLisboa');
INSERT INTO fiscal VALUES ('2', 'FiscalPorto');
INSERT INTO fiscal VALUES ('3', 'FiscalEvora');

/* TABELA EDIFICIO */
INSERT INTO edificio VALUES ('Avenida da Boavista, Porto');
INSERT INTO edificio VALUES ('Avenida da Liberdade, Lisboa');
INSERT INTO edificio VALUES ('Avenida da Republica, Lisboa');
INSERT INTO edificio VALUES ('Avenida dos Aliados, Porto');
INSERT INTO edificio VALUES ('Praca do Giraldo, Evora');

/* TABELA RESERVA */
INSERT INTO reserva VALUES ('1');
INSERT INTO reserva VALUES ('2');
INSERT INTO reserva VALUES ('3');
INSERT INTO reserva VALUES ('4');
INSERT INTO reserva VALUES ('5');
INSERT INTO reserva VALUES ('6');
INSERT INTO reserva VALUES ('7');
INSERT INTO reserva VALUES ('8');
INSERT INTO reserva VALUES ('9');
INSERT INTO reserva VALUES ('10');

/* TABELA ALUGAVEL */
INSERT INTO alugavel VALUES ('Avenida da Boavista, Porto', '1',"foto");
INSERT INTO alugavel VALUES ('Avenida da Boavista, Porto', '2',"foto");
INSERT INTO alugavel VALUES ('Avenida da Liberdade, Lisboa', '2',"foto");
INSERT INTO alugavel VALUES ('Avenida da Liberdade, Lisboa', '3',"foto");
INSERT INTO alugavel VALUES ('Avenida da Republica, Lisboa', '3',"foto");
INSERT INTO alugavel VALUES ('Avenida da Republica, Lisboa', '4',"foto");
INSERT INTO alugavel VALUES ('Avenida dos Aliados, Porto', '4',"foto");
INSERT INTO alugavel VALUES ('Avenida dos Aliados, Porto', '5',"foto");
INSERT INTO alugavel VALUES ('Praca do Giraldo, Evora', '1',"foto");
INSERT INTO alugavel VALUES ('Praca do Giraldo, Evora', '5',"foto");

/* TABELA ARRENDA */
INSERT INTO arrenda VALUES ('Avenida da Boavista, Porto', '1', '111111111');
INSERT INTO arrenda VALUES ('Avenida da Boavista, Porto', '2', '111111111');
INSERT INTO arrenda VALUES ('Avenida da Liberdade, Lisboa', '2', '333333333');
INSERT INTO arrenda VALUES ('Avenida da Liberdade, Lisboa', '3', '444444444');
INSERT INTO arrenda VALUES ('Avenida da Republica, Lisboa', '3', '222222222');
INSERT INTO arrenda VALUES ('Avenida da Republica, Lisboa', '4', '111111111');
INSERT INTO arrenda VALUES ('Avenida dos Aliados, Porto', '4', '222222222');
INSERT INTO arrenda VALUES ('Avenida dos Aliados, Porto', '5', '111111111');
INSERT INTO arrenda VALUES ('Praca do Giraldo, Evora', '1', '333333333');
INSERT INTO arrenda VALUES ('Praca do Giraldo, Evora', '5', '333333333');

/* FISCALIZA */
INSERT INTO fiscaliza VALUES ('2', 'Avenida da Boavista, Porto', '1');
INSERT INTO fiscaliza VALUES ('3', 'Avenida da Boavista, Porto', '2');
INSERT INTO fiscaliza VALUES ('1', 'Avenida da Liberdade, Lisboa', '2');
INSERT INTO fiscaliza VALUES ('1', 'Avenida da Liberdade, Lisboa', '3');
INSERT INTO fiscaliza VALUES ('2', 'Avenida da Republica, Lisboa', '3');
INSERT INTO fiscaliza VALUES ('3', 'Avenida da Republica, Lisboa', '4');
INSERT INTO fiscaliza VALUES ('1', 'Avenida dos Aliados, Porto', '4');
INSERT INTO fiscaliza VALUES ('2', 'Avenida dos Aliados, Porto', '5');
INSERT INTO fiscaliza VALUES ('3', 'Praca do Giraldo, Evora', '1');
INSERT INTO fiscaliza VALUES ('3', 'Praca do Giraldo, Evora', '5');

/* ESPACO */
INSERT INTO espaco VALUES ('Avenida da Boavista, Porto', '1');
INSERT INTO espaco VALUES ('Avenida da Liberdade, Lisboa', '2');
INSERT INTO espaco VALUES ('Avenida da Republica, Lisboa', '3');
INSERT INTO espaco VALUES ('Avenida dos Aliados, Porto', '4');
INSERT INTO espaco VALUES ('Praca do Giraldo, Evora', '5');

/* POSTO */
INSERT INTO posto VALUES ('Avenida da Boavista, Porto', '2', '1');
INSERT INTO posto VALUES ('Avenida da Liberdade, Lisboa', '3', '2');
INSERT INTO posto VALUES ('Avenida da Republica, Lisboa', '4', '3');
INSERT INTO posto VALUES ('Avenida dos Aliados, Porto', '5', '4');
INSERT INTO posto VALUES ('Praca do Giraldo, Evora', '1', '5');

/* OFERTA */
INSERT INTO oferta VALUES ('Avenida da Boavista, Porto', '1', '2017/03/01', '2017/03/31', '1250');
INSERT INTO oferta VALUES ('Avenida da Boavista, Porto', '2', '2017/01/01', '2017/01/31', '275');
INSERT INTO oferta VALUES ('Avenida da Liberdade, Lisboa', '2', '2017/01/01', '2017/01/31', '300');
INSERT INTO oferta VALUES ('Avenida da Liberdade, Lisboa', '3', '2017/03/01', '2017/03/31', '350');
INSERT INTO oferta VALUES ('Avenida da Republica, Lisboa', '3', '2017/03/01', '2017/03/31', '250');
INSERT INTO oferta VALUES ('Avenida da Republica, Lisboa', '4', '2017/03/01', '2017/03/31', '300');
INSERT INTO oferta VALUES ('Avenida dos Aliados, Porto', '4', '2017/01/01', '2017/01/31', '425');
INSERT INTO oferta VALUES ('Avenida dos Aliados, Porto', '5', '2017/01/01', '2017/01/31', '435');
INSERT INTO oferta VALUES ('Praca do Giraldo, Evora', '1', '2017/01/01', '2017/01/31', '1000');
INSERT INTO oferta VALUES ('Praca do Giraldo, Evora', '5', '2017/03/01', '2017/03/31', '300');

/* TABELA ALUGA */
INSERT INTO aluga VALUES ('Avenida da Boavista, Porto', '1', '2017/03/01', '333333333', '1');
INSERT INTO aluga VALUES ('Avenida da Boavista, Porto', '2', '2017/01/01', '333333333', '2');
INSERT INTO aluga VALUES ('Avenida da Liberdade, Lisboa', '2', '2017/01/01', '333333333', '3');
INSERT INTO aluga VALUES ('Avenida da Liberdade, Lisboa', '3', '2017/03/01', '333333333', '4');
INSERT INTO aluga VALUES ('Avenida da Republica, Lisboa', '3', '2017/03/01', '333333333', '5');
INSERT INTO aluga VALUES ('Avenida da Republica, Lisboa', '4', '2017/03/01', '333333333', '6');
INSERT INTO aluga VALUES ('Avenida dos Aliados, Porto', '4', '2017/01/01', '444444444', '7');
INSERT INTO aluga VALUES ('Avenida dos Aliados, Porto', '5', '2017/01/01', '444444444', '8');
INSERT INTO aluga VALUES ('Praca do Giraldo, Evora', '1', '2017/01/01', '444444444', '9');
INSERT INTO aluga VALUES ('Praca do Giraldo, Evora', '5', '2017/03/01', '222222222', '10');


/* TABELA ESTADO */
INSERT INTO estado VALUES ('1', CURRENT_TIMESTAMP(), 'ACEITE');
INSERT INTO estado VALUES ('2', CURRENT_TIMESTAMP(), 'ACEITE');
INSERT INTO estado VALUES ('3', CURRENT_TIMESTAMP(), 'PENDENTE');
INSERT INTO estado VALUES ('4', CURRENT_TIMESTAMP(), 'ACEITE');
INSERT INTO estado VALUES ('5', CURRENT_TIMESTAMP(), 'ACEITE');
INSERT INTO estado VALUES ('6', CURRENT_TIMESTAMP(), 'PENDENTE');
INSERT INTO estado VALUES ('7', CURRENT_TIMESTAMP(), 'PENDENTE');
INSERT INTO estado VALUES ('8', CURRENT_TIMESTAMP(), 'ACEITE');
INSERT INTO estado VALUES ('9', CURRENT_TIMESTAMP(), 'PENDENTE');
INSERT INTO estado VALUES ('10',CURRENT_TIMESTAMP(), 'ACEITE');

/* TABELA PAGA */
INSERT INTO paga VALUES ('1', CURRENT_TIMESTAMP(), 'C');
INSERT INTO paga VALUES ('2', CURRENT_TIMESTAMP(), 'M');
INSERT INTO paga VALUES ('4', CURRENT_TIMESTAMP(), 'C');
INSERT INTO paga VALUES ('5', CURRENT_TIMESTAMP(), 'C');
INSERT INTO paga VALUES ('8', CURRENT_TIMESTAMP(), 'C');
INSERT INTO paga VALUES ('10', CURRENT_TIMESTAMP(), 'C');