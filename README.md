# Sistema de Gestão de Clínica Veterinária

Aplicação de consola desenvolvida em C++ para a gestão básica de uma clínica veterinária.

O sistema permite registar e consultar animais, veterinários, serviços e prescrições, seguindo uma arquitetura inspirada no exemplo da aplicação *School Application*, com separação entre View, Controller, Services, DTOs, Mappers, Model e Containers.

---

<!-- INDICE -->
<details>
  <summary>Índice</summary>
  <ol>
    <li>
      <a href="#sobre-o-projeto">Sobre o Projeto</a>
    </li>
    <li>
      <a href="#arquitetura">Arquitetura</a>
    </li>
    <li>
      <a href="#estrutura-do-projeto">Estrutura do Projeto</a>
    </li>
    <li>
      <a href="#como-executar">Como Executar</a>
      <ul>
        <li><a href="#requisitos">Requisitos</a></li>
        <li><a href="#instalação">Instalação</a></li>
      </ul>
    </li>
    <li><a href="#como-usar">Como Usar</a></li>
    <li><a href="#progresso">Progresso</a></li>
    <li><a href="#melhoriasalterações-adicionais">Melhorias/Alterações Adicionais</a></li>
    <li><a href="#créditos">Créditos</a></li>
  </ol>
</details>

---

<!-- SOBRE O PROJETO -->
## Sobre o Projeto

Este projeto tem como objetivo desenvolver uma aplicação de software para gerir uma clínica veterinária.

A aplicação permite gerir informação relacionada com:

- Animais registados na clínica
- Veterinários
- Serviços realizados ou agendados
- Prescrições emitidas para animais

O sistema utiliza uma interface baseada em consola. Nesta fase, os dados são mantidos em memória durante a execução da aplicação. Numa fase futura, será implementada persistência em ficheiros binários.

---

<!-- ARQUITETURA -->
## Arquitetura

A aplicação está organizada em camadas, seguindo uma estrutura semelhante ao exemplo da *School Application*.

- **View**: responsável pela interação com o utilizador através da consola.
- **Controller**: coordena os menus e chama os serviços necessários.
- **Services**: contêm a lógica principal da aplicação.
- **DTOs**: transportam dados entre camadas.
- **Mappers**: convertem objetos do Model em DTOs.
- **Model**: contém as entidades principais do domínio.
- **Containers**: gerem coleções de objetos do Model.

Atualmente, os `Services` acedem diretamente à classe `Clinic`. Numa fase futura, será adicionada uma camada `Repository` para tratar da persistência dos dados.

No `Model`, as relações entre entidades são representadas através de apontadores/referências para objetos. Por exemplo, um `Service` guarda apontadores para o `Animal` e para o `Veterinarian` associados, em vez de guardar apenas os seus IDs.

Os IDs continuam a existir como identificadores das entidades e são usados na interface/DTOs para o utilizador selecionar objetos existentes.

---

<!-- ESTRUTURA DO PROJETO -->
## Estrutura do Projeto

```text
Project/
│
├── headers/
│   ├── controllers/
│   ├── dto/
│   ├── exceptions/
│   ├── mappers/
│   ├── model/
│   ├── repo/
│   ├── services/
│   └── views/
│
├── sources/
│   ├── controllers/
│   ├── exceptions/
│   ├── mappers/
│   ├── model/
│   ├── repo/
│   ├── services/
│   └── views/
│
├── main.cpp
└── CMakeLists.txt
````

---

<!-- COMO EXECUTAR -->

## Como Executar

### Requisitos

Para compilar e executar o projeto é necessário ter:

* C++17 ou superior
* CMake
* CLion ou outro IDE/editor compatível com CMake
* Git

### Instalação

1. Clonar o repositório:

```bash
git clone https://github.com/ourcca/fsoft2026_1DE_2.git
```

2. Entrar na pasta do projeto:

```bash
cd fsoft2026_1DE_2/Project
```

3. Abrir o projeto no CLion ou compilar com CMake.

No CLion:

* Abrir a pasta `Project`
* Fazer reload do CMake
* Executar o target `VeterinaryClinic`

---

<!-- COMO USAR -->

## Como Usar

A aplicação apresenta um menu principal com várias opções:

```text
====================================
 Sistema de Gestao Clinica Veterinaria
====================================
1. Gestao de Animais
2. Gestao de Veterinarios
3. Gestao de Servicos
4. Gestao de Prescricoes
0. Sair
```

Cada menu permite aceder às funcionalidades relacionadas com essa entidade.

Exemplo do menu de animais:

```text
========== Gestao de Animais ==========
1. Registar Animal
2. Listar Animais
3. Consultar Animal por ID
0. Voltar
```

Exemplo do menu de veterinários:

```text
========== Gestao de Veterinarios ==========
1. Registar Veterinario
2. Listar Veterinarios
3. Consultar Servicos de Veterinario
0. Voltar
```

Exemplo do menu de serviços:

```text
========== Gestao de Servicos ==========
1. Registar Servico
2. Listar Servicos
0. Voltar
```

Exemplo do menu de prescrições:

```text
========== Gestao de Prescricoes ==========
1. Emitir Prescricao
2. Listar Prescricoes
0. Voltar
```

---

<!-- PROGRESSO -->

## Progresso

| UCs                                         | Estado                    | Comentários                                                                 |
| ------------------------------------------- | ------------------------- | --------------------------------------------------------------------------- |
| UC1 - Registar Animal                       | Implementado              | Falta adicionar exceptions, validações completas e persistência de dados    |
| UC2 - Registar Veterinário                  | Implementado              | Falta adicionar exceptions, validações completas e persistência de dados    |
| UC3 - Definir Serviço                       | Implementado              | Serviço já pode ser registado e listado                                     |
| UC4 - Marcar Consulta / Serviço             | Parcialmente implementado | A marcação foi simplificada como um tipo de serviço com data e hora         |
| UC5 - Consultar Marcações / Serviços        | Parcialmente implementado | Atualmente é possível listar serviços                                       |
| UC6 - Consultar Histórico Geral de Serviços | Parcialmente implementado | Atualmente é possível listar todos os serviços                              |
| UC7 - Consultar Serviços de um Veterinário  | Implementado              | Consulta feita através do ID do veterinário introduzido na interface        |
| UC8 - Emitir Prescrição                     | Implementado              | Falta melhorar validações e tratamento de erros                             |
| UC9 - Consultar Prescrições                 | Parcialmente implementado | Atualmente é possível listar todas as prescrições; falta filtrar por animal |
| UC10 - Consultar Animal                     | Implementado              | Consulta feita através do ID do animal introduzido na interface             |

---

### Melhorias/Alterações Adicionais

Funcionalidades e melhorias planeadas:

* Implementar persistência em ficheiros binários.
* Implementar a camada `Repository`.
* Adicionar exceptions:

  * `InvalidDataException`
  * `DuplicatedDataException`
  * `NoDataException`
  * `DataConsistencyException`
* Validar dados introduzidos pelo utilizador.
* Validar se os objetos associados existem ao criar serviços e prescrições.
* Implementar geração automática de IDs.
* Garantir que as relações no Model usam apontadores/referências, e não IDs.
* Melhorar mensagens de erro na interface.
* Adicionar filtros nas listagens.
* Consultar prescrições de um animal específico.
* Atualizar os diagramas de classes conforme a implementação final.

---

<!-- CREDITOS -->

## Créditos

Projeto desenvolvido no âmbito da unidade curricular de Fundamentos de Desenvolvimento de Software.

Recursos usados como referência:

* Material disponibilizado pelo docente
* Exemplo *School Application*
* [https://github.com/othneildrew/Best-README-Template](https://github.com/othneildrew/Best-README-Template)
