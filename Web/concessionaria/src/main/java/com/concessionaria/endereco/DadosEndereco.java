package com.concessionaria.endereco;

import jakarta.validation.constraints.NotBlank;

public record DadosEndereco(
  
  @NotBlank String rua, 
  @NotBlank String numero, 
  @NotBlank String bairro

){}
