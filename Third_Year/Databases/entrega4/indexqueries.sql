
show profiles;
set PROFILING = 1;

explain select A.nif
from arrenda A
inner join fiscaliza F
on A.morada = F.morada and A.codigo = F.codigo
group by A.nif
having count(distinct F.id)=1;

drop index morada on fiscaliza;

drop index nif on arrenda;

show index from alugavel;

create index fiscalizaid_idx on fiscaliza(id);
drop index fiscalizaid_idx on fiscaliza;


create index fiscalizamorcod_idx on fiscaliza(morada,codigo);
drop index fiscalizamorcod_idx on fiscaliza;


create index arrenda_idx on arrenda(morada, codigo, nif);
drop index arrenda_idx on arrenda;

create index fiscaliza_codmoridx on fiscaliza(codigo,morada);

explain select distinct P.morada, P.codigo_espaco
from posto P
where (P.morada, P.codigo_espaco) not in (
  select P.morada, P.codigo_espaco
  from posto P natural join aluga A natural join estado E
  where E.estado = 'aceite');

show profiles;
show index from posto;
show index from aluga;
show index from estado;

create index estado_idx on estado(estado);
drop index morada on posto;

create index postomorcod_idx on posto(morada,codigo);

create index postomorcodesp_idx on posto(morada, codigo_espaco);

create index postomorcodcodesp_idx on posto(morada,codigo, codigo_espaco);


