package com.concessionaria.controllers;

import com.concessionaria.anunciante.DadosListagemAnunciante;
import com.concessionaria.carro.*;
import jakarta.validation.Valid;
import jakarta.transaction.Transactional;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;


@RestController
@RequestMapping("carros")
public class CarroController {

  @Autowired
  private CarroRepository repository;
  
  @PostMapping
  @Transactional
  public void cadastrar(@RequestBody @Valid DadosCadastroCarro dados){
    System.out.println("Adicionando carro ao banco: "+dados);
    repository.save(new Carro(dados));
  }

  @GetMapping
  public Page<DadosListagemCarro> listar(Pageable paginacao) {
    return repository.findAll(paginacao).map(DadosListagemCarro::new);
  }

  
}
