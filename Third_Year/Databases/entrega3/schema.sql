/* Bloco de limpeza da base de dados */
/*
	drop table aluga ;
	drop table paga ;
	drop table estado ;
	drop table reserva ;
	drop table arrenda ;
	drop table fiscaliza ;
	drop table oferta ;
	drop table espaco ;
	drop table posto ;
	drop table alugavel ;
	
  drop table user ;
	drop table fiscal ;
	drop table edificio ;
	drop table reserva ;
*/
/* Criaçao das tabelas do esquema da base de dados */
create table user(
	nif     integer		not null unique,
	nome	 	varchar(255)	not null,
	telefone	 	integer		not null,
	primary key(nif)
);

/*tamanho correcto ?*/
create table fiscal(
	id		 	integer		not null unique,
	empresa	 	varchar(255)	not null,
	primary key(id)
);

create table edificio(
	morada 		varchar(255)	not null unique,
	primary key(morada)
);

create table reserva(
	numero	 	integer		not null unique,
	primary key(numero)
);

create table alugavel(
	morada	 	varchar(255)	not null,
	codigo	 	integer  	not null,
	foto		varchar(255) not null,
	primary key(morada, codigo),
	foreign key(morada) references edificio(morada) ON DELETE CASCADE
);

create table arrenda(
	morada 		varchar(255)	not null,
	codigo		integer	not null,
	nif 		integer		not null,
	primary key(morada, codigo),
	foreign key(morada,codigo) references alugavel(morada,codigo) ON DELETE CASCADE ,
	foreign key(nif) 	references user(nif)
);

create table fiscaliza(
	id		 	integer		not null,
	morada	 	varchar(255)	not null,
	codigo		integer	not null,
	primary key(id, morada, codigo),
	foreign key(id) references fiscal(id),
	foreign key(morada,codigo) references arrenda(morada,codigo) ON DELETE CASCADE
);

create table espaco(
	morada	 	varchar(255)	not null,
	codigo		integer	not null,
	primary key(morada, codigo),
	foreign key(morada,codigo) references alugavel(morada,codigo) ON DELETE CASCADE
);

create table posto(
	morada	 	varchar(255)	not null,
	codigo		integer	not null,
	codigo_espaco	integer	not null,
	primary key(morada, codigo),
	foreign key(morada,codigo_espaco) references espaco(morada,codigo) ON DELETE CASCADE ,
	foreign key(morada, codigo) references alugavel(morada,codigo) ON DELETE CASCADE
);

create table oferta(
	morada	 	varchar(255)	not null,
	codigo		integer	not null,
	data_inicio		date		not null,
	data_fim		date		not null,
	tarifa		numeric(20,2)	not null,
	primary key(morada, codigo, data_inicio),
	foreign key(morada,codigo) references alugavel(morada,codigo) ON DELETE CASCADE
) ;

create table aluga(
	morada	 	varchar(255)	not null,
	codigo		integer	  not null,
	data_inicio		date		not null,
	nif			integer		not null,
	numero		integer		not null,
	primary key(morada, codigo, data_inicio, nif, numero),
	foreign key(morada,codigo,data_inicio) references oferta(morada,codigo,data_inicio) ON DELETE CASCADE ,
	foreign key(nif) references user(nif),
	foreign key(numero) references reserva(numero)
);

create table paga(
	numero	 	integer		not null,
	data		date		not null,
	metodo		varchar(255)	not null,
	primary key(numero),
	foreign key(numero) references reserva(numero)
);

create table estado(
	numero	 	integer		not null,
	timestamp		date		not null,
	estado		varchar(255)	not null,
	primary key(numero,timestamp),
	foreign key(numero) references reserva(numero)
);
