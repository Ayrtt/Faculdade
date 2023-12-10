package com.concessionaria.controllers;

import com.concessionaria.anunciante.*;
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
@RequestMapping("anunciantes")
public class AnuncianteController {
  @Autowired
  private AnuncianteRepository repository;

  @PostMapping
  @Transactional
  public void cadastrar(@RequestBody @Valid DadosCadastroAnunciante dados){
    System.out.println("Adicionando anunciante ao banco: " + dados);
    repository.save(new Anunciante(dados));
  }

  @GetMapping
  public Page<DadosListagemAnunciante> listar(Pageable paginacao) {
    return repository.findAll(paginacao).map(DadosListagemAnunciante::new);
  }
}