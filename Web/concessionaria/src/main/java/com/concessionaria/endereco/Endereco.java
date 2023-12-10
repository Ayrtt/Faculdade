package com.concessionaria.endereco;

import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.AllArgsConstructor;
import jakarta.persistence.Embeddable;

@Embeddable
@Getter
@NoArgsConstructor
@AllArgsConstructor

public class Endereco {
  
  private String rua;
  private String numero;
  private String bairro;

  public Endereco(DadosEndereco endereco) {
  }
}
