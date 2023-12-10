create table carros(

  id bigint not null auto_increment,
  marca varchar(100) not null,
  modelo varchar(100) not null,
  ano int not null,
  preco float not null,
  id_anunciante int not null,
  
  foreign key (id_anunciante) references anunciantes(id)
  
  primary key(id)

);