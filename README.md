# Sistema de Gestão de Clínica Veterinária

Aplicação de consola desenvolvida em C++ para a gestão básica de uma clínica veterinária.

O sistema permite registar, consultar, editar e remover animais, veterinários, serviços e prescrições, seguindo uma arquitetura inspirada no exemplo da aplicação *School Application*, com separação entre View, Controller, Services, DTOs, Mappers, Model, Containers, Repository e Exceptions.

---

<!-- INDICE -->

<details>
  <summary>Índice</summary>
  <ol>
    <li><a href="#sobre-o-projeto">Sobre o Projeto</a></li>
    <li><a href="#arquitetura">Arquitetura</a></li>
    <li><a href="#persistência-de-dados">Persistência de Dados</a></li>
    <li><a href="#testes">Testes</a></li>
    <li><a href="#estrutura-do-projeto">Estrutura do Projeto</a></li>
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

## Sobre o Projeto

Este projeto tem como objetivo desenvolver uma aplicação de software para gerir uma clínica veterinária.

A aplicação permite gerir informação relacionada com:

* Animais registados na clínica
* Veterinários
* Serviços realizados ou agendados
* Prescrições emitidas para animais

O sistema utiliza uma interface baseada em consola e permite guardar os dados em ficheiro binário, de forma a manter a informação entre execuções da aplicação.

---

## Arquitetura

A aplicação está organizada em camadas, seguindo uma estrutura semelhante ao exemplo da *School Application*.

* **View**: responsável pela interação com o utilizador através da consola.
* **Controller**: coordena os menus e chama os serviços necessários.
* **Services**: contêm a lógica principal da aplicação e validações.
* **DTOs**: transportam dados entre camadas.
* **Mappers**: convertem objetos do Model em DTOs.
* **Model**: contém as entidades principais do domínio.
* **Containers**: gerem coleções de objetos do Model.
* **Repository**: responsável por guardar e carregar os dados da aplicação.
* **Exceptions**: usadas para representar erros e situações inválidas.

A classe `Clinic` funciona como objeto principal do domínio, agregando os vários containers da aplicação:

* `AnimalContainer`
* `VeterinarianContainer`
* `ServiceContainer`
* `PrescriptionContainer`

O `Controller` utiliza um `ClinicRepositoryBinary`, e os `Services` acedem à `Clinic` através de `repository.getClinic()`.

No `Model`, as relações entre entidades são representadas através de apontadores/referências para objetos. Por exemplo, um `Service` guarda apontadores para o `Animal` e para o `Veterinarian` associados, em vez de guardar apenas os seus IDs.

Os IDs continuam a existir como identificadores das entidades e são usados na interface/DTOs para o utilizador selecionar objetos existentes.

Para evitar problemas com apontadores inválidos, os containers de `Animal` e `Veterinarian` usam `std::deque`, permitindo maior estabilidade dos objetos em memória quando são adicionados novos elementos.

---

## Persistência de Dados

A persistência foi implementada através da camada `Repository`.

Atualmente existem as seguintes classes:

* `IClinicRepository`
* `ClinicRepositoryMemory`
* `ClinicRepositoryBinary`

A aplicação utiliza o `ClinicRepositoryBinary`, que guarda e carrega os dados através de um ficheiro binário.

O ficheiro usado para guardar os dados é:

```text
clinic.dat
```

Quando a aplicação inicia, o repository chama `load()` para carregar os dados existentes. Sempre que é criada, editada ou removida uma entidade, o `Controller` chama `save()` para guardar o estado atual da clínica.

A persistência inclui:

* Animais
* Veterinários
* Serviços
* Prescrições

Para entidades simples, como `Animal` e `Veterinarian`, os campos são guardados diretamente no ficheiro.

Para entidades com relações, como `Service` e `Prescription`, não são guardados os apontadores em ficheiro. Em vez disso, são guardados os IDs do animal e do veterinário associados. Durante o `load()`, estes IDs são usados para reconstruir os apontadores em memória.

Assim, em memória as relações continuam orientadas a objetos, mas no ficheiro são guardados dados simples e seguros.

---

## Testes

Foi criado um projeto separado para testes, usando Google Test, inspirado no tester da *School Application*.

O tester cobre atualmente:

* `Animal`
* `AnimalContainer`
* `Veterinarian`
* `VeterinarianContainer`
* `Service`
* `ServiceContainer`
* `Prescription`
* `PrescriptionContainer`
* `Date`
* `Time`
* `AnimalService`
* `VeterinarianService`
* `ServiceService`
* `PrescriptionService`
* `ClinicRepositoryBinary`
* Situações com exceptions e regras de consistência

Atualmente, o tester executa com sucesso:

```text
62 tests passed
```

Além dos testes automáticos, foi também feito teste manual da aplicação e da persistência binária:

1. Criar animal
2. Criar veterinário
3. Criar serviço
4. Criar prescrição
5. Fechar a aplicação
6. Abrir a aplicação novamente
7. Confirmar que os dados continuam disponíveis
8. Listar animais, veterinários, serviços e prescrições
9. Consultar serviços de um veterinário
10. Consultar prescrições de um animal
11. Editar dados existentes
12. Remover entidades e confirmar a atualização dos dados associados

---

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
```

---

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
4. Editar Animal
5. Remover Animal
0. Voltar
```

Exemplo do menu de veterinários:

```text
========== Gestao de Veterinarios ==========
1. Registar Veterinario
2. Listar Veterinarios
3. Consultar Servicos de Veterinario
4. Editar Veterinario
5. Remover Veterinario
0. Voltar
```

Exemplo do menu de serviços:

```text
========== Gestao de Servicos ==========
1. Registar Servico
2. Listar Servicos
3. Editar Servico
4. Remover Servico
0. Voltar
```

Exemplo do menu de prescrições:

```text
========== Gestao de Prescricoes ==========
1. Emitir Prescricao
2. Listar Prescricoes
3. Consultar Prescricoes de Animal
4. Editar Prescricao
5. Remover Prescricao
0. Voltar
```

---

## Progresso

| UC                                          | Estado                    | Comentários                                                                 |
| ------------------------------------------- | ------------------------- | --------------------------------------------------------------------------- |
| UC1 - Registar Animal                       | Implementado              | Registo com ID automático, validações básicas e persistência binária        |
| UC2 - Registar Veterinário                  | Implementado              | Registo com ID automático, validações básicas e persistência binária        |
| UC3 - Definir Serviço                       | Implementado              | Serviço pode ser registado, listado, editado, removido e persistido         |
| UC4 - Marcar Consulta / Serviço             | Implementado              | A marcação foi simplificada como um serviço com data e hora                 |
| UC5 - Consultar Marcações / Serviços        | Implementado              | É possível listar serviços e consultar serviços de um veterinário           |
| UC6 - Consultar Histórico Geral de Serviços | Implementado              | É possível listar todos os serviços                                         |
| UC7 - Consultar Serviços de um Veterinário  | Implementado              | Consulta feita através do ID do veterinário                                 |
| UC8 - Emitir Prescrição                     | Implementado              | Prescrição associada a animal e veterinário, com persistência binária       |
| UC9 - Consultar Prescrições                 | Implementado              | É possível listar todas as prescrições e consultar prescrições de um animal |
| UC10 - Consultar Animal                     | Implementado              | Consulta feita através do ID do animal                                      |

---

## Melhorias/Alterações Adicionais

Funcionalidades implementadas:

* Geração automática de IDs.
* Relações no Model através de apontadores/referências.
* DTOs para transportar dados entre camadas.
* Mappers para converter objetos do Model em DTOs.
* Containers para gerir coleções de entidades.
* Exceptions principais:
  * `InvalidDataException`
  * `DuplicatedDataException`
  * `NoDataException`
  * `DataConsistencyException`
* Validação da existência de objetos associados ao criar serviços e prescrições.
* Validação de serviços de acordo com a especialidade do veterinário.
* Persistência em ficheiros binários.
* Camada `Repository`.
* Reconstrução de apontadores no carregamento dos dados.
* Edição de animais.
* Edição de veterinários.
* Edição de serviços.
* Edição de prescrições.
* Remoção de animais, veterinários, serviços e prescrições.
* Remoção de dados associados quando necessário.
* Tester com Google Test.
* Testes ao Repository.
* Alteração de containers de `Animal` e `Veterinarian` para `std::deque`, para melhorar a estabilidade dos apontadores.

Funcionalidades que podem ser melhoradas futuramente:

* Melhorar validações finais dos dados introduzidos.
* Melhorar mensagens de erro na interface.
* Melhorar a interface da aplicação.
* Expandir testes automáticos para mais cenários de edição e remoção.
* Atualizar e melhorar diagramas técnicos conforme futuras alterações.
* Implementar uma interface gráfica.

---

## Créditos

Projeto desenvolvido no âmbito da unidade curricular de Fundamentos de Desenvolvimento de Software.

Recursos usados como referência:

* Material disponibilizado pelo docente
* Exemplo *School Application*
* Google Test
* Documentação de C++ sobre ficheiros binários
* https://github.com/othneildrew/Best-README-Template
