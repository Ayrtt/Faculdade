package com.concessionaria.carro;

public record DadosListagemCarro(String marca, String modelo, int ano, 
                                 double preco) {

  public DadosListagemCarro(Carro carro){
    this( carro.getMarca(), carro.getModelo(), carro.getAno(),
          carro.getPreco() );
  }
}