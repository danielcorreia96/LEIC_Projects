SELECT * FROM posto
WHERE morada = "Avenida da Republica, Lisboa"


SELECT  max(numero)+1 FROM  reserva;

SELECT * FROM reserva where reserva.numero not in (select numero from paga);

SELECT *
FROM espaco NATURAL JOIN aluga NATURAL JOIN oferta NATURAL JOIN paga;

SELECT (data_fim - data_inicio) as intervalo
FROM espaco NATURAL JOIN aluga NATURAL JOIN oferta NATURAL JOIN paga;

SELECT morada, codigo, SUM(tarifa*(data_fim - data_inicio)) as total
FROM espaco NATURAL JOIN aluga NATURAL JOIN oferta NATURAL JOIN paga
GROUP BY morada,codigo
HAVING morada = "Avenida da Boavista, Porto";


SHOW TRIGGERS;

SELECT * FROM oferta;

SELECT * FROM oferta
WHERE data_inicio >= (
  SELECT MIN(data_inicio)
  FROM oferta
);

SELECT MIN(data_inicio)
  FROM oferta;


SELECT posto.morada, posto.codigo_espaco, (SUM(tarifa*(data_fim - data_inicio) + totalEspaco)) as total
FROM posto NATURAL JOIN aluga NATURAL JOIN oferta NATURAL JOIN paga,
  (SELECT morada, codigo, SUM(tarifa*(data_fim - data_inicio)) as totalEspaco
          FROM espaco NATURAL JOIN aluga NATURAL JOIN oferta NATURAL JOIN paga
          GROUP BY morada, codigo
          HAVING morada = 'Avenida da Boavista, Porto') AS C
GROUP BY posto.morada, posto.codigo_espaco;


SELECT morada, codigo, SUM(tarifa*(data_fim - data_inicio)) as total
                    FROM espaco NATURAL JOIN aluga NATURAL JOIN oferta NATURAL JOIN paga
                    WHERE morada = 'Avenida da Boavista, Porto' AND codigo = '1';

SELECT morada, codigo_espaco, SUM(total) as totalRealizado
FROM (
  (SELECT morada, codigo as codigo_espaco, SUM(tarifa*(data_fim - data_inicio)) as total
  FROM espaco NATURAL JOIN aluga NATURAL JOIN oferta NATURAL JOIN paga
  GROUP BY morada, codigo
  HAVING morada = 'Avenida da Boavista, Porto')
  UNION
  (SELECT morada, codigo_espaco, SUM(tarifa*(data_fim - data_inicio)) as total
  FROM posto NATURAL JOIN aluga NATURAL JOIN oferta NATURAL JOIN paga
  GROUP BY morada, codigo_espaco
  HAVING morada = 'Avenida da Boavista, Porto')
) AS Res
GROUP BY morada, codigo_espaco;


/* testes da RI-2
  numero de reserva: 2016-12
  ultimo estado: 2016-12	2016-01-01 01:33:19	Aceite

  casos possiveis:
  1. pagamento com data valida
  INSERT INTO paga VALUES ('2016-12',	'2016-01-01 01:33:29', 'Cartão Crédito');

  2. pagamento com data inferior/invalida
  INSERT INTO paga VALUES ('2016-12',	'2016-01-01 01:33:10', 'Cartão Crédito');

  3. pagamento com data sobreposta
  INSERT INTO paga VALUES ('2016-12',	'2016-01-01 01:33:19', 'Cartão Crédito');

);
*/
SELECT *
FROM estado
WHERE numero = '2016-12'
      AND
      '2016-01-01 01:33:10' <= (
        SELECT MAX(time_stamp)
        FROM estado
        WHERE numero = '2016-12');