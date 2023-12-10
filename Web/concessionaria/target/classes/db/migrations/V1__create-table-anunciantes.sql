create table anunciantes(

  id bigint auto_increment primary key,
  nome varchar(50) not null,
  email varchar(50) not null,
  cpf varchar(50) not null,
  telefone varchar(50) not null,
  rua varchar(50) not null,
  numero varchar(50) not null,
  bairro varchar(50) not null,
  funcao int

);