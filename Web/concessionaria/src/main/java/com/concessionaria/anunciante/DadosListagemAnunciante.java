package com.concessionaria.anunciante;

public record DadosListagemAnunciante(String nome, String telefone,
  String rua, String numero, String bairro) {

  public DadosListagemAnunciante(Anunciante anunciante){
    this( anunciante.getNome(), anunciante.getTelefone(), 
    anunciante.getRua(), anunciante.getNumero(),
    anunciante.getBairro() );
  }
}
