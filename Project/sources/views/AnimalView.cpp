/*
AnimalView.cpp

Created on: 15/05/2026
*/
#include "views/AnimalView.h"
#include "views/Utils.h"

#include <iostream>

int AnimalView::menu() {
    std::cout << "\n========== Gestao de Animais ==========\n";
    std::cout << "1. Registar Animal\n";
    std::cout << "2. Listar Animais\n";
    std::cout << "3. Consultar Animal por ID\n";
    std::cout << "4. Editar Animal\n";
    std::cout << "0. Voltar\n";

    return Utils::getNumber("Escolha uma opcao: ");
}

AnimalInDTO AnimalView::getAnimal() {
    AnimalInDTO dto{};

    dto.name = Utils::getString("Nome: ");
    dto.species = Utils::getString("Especie: ");
    dto.breed = Utils::getString("Raca: ");

    dto.weight = static_cast<float>(Utils::getNumber("Peso: "));
    dto.age = Utils::getNumber("Idade: ");

    return dto;
}

void AnimalView::showAnimalCreated() {
    std::cout << "Animal registado com sucesso.\n";
}

void AnimalView::printAnimals(const std::vector<AnimalOutDTO>& animals) {
    if (animals.empty()) {
        std::cout << "Nao existem animais registados.\n";
        return;
    }

    std::cout << "\n========== Lista de Animais ==========\n";

    for (const AnimalOutDTO& animal : animals) {
        std::cout << "ID: " << animal.id << "\n";
        std::cout << "Nome: " << animal.name << "\n";
        std::cout << "Especie: " << animal.species << "\n";
        std::cout << "Raca: " << animal.breed << "\n";
        std::cout << "Peso: " << animal.weight << "\n";
        std::cout << "Idade: " << animal.age << "\n";
        std::cout << "--------------------------------------\n";
    }
}

int AnimalView::getAnimalId() {
    return Utils::getNumber("ID do animal: ");
}

void AnimalView::printAnimal(const AnimalOutDTO& animal) {
    std::cout << "\n========== Dados do Animal ==========\n";
    std::cout << "ID: " << animal.id << "\n";
    std::cout << "Nome: " << animal.name << "\n";
    std::cout << "Especie: " << animal.species << "\n";
    std::cout << "Raca: " << animal.breed << "\n";
    std::cout << "Peso: " << animal.weight << "\n";
    std::cout << "Idade: " << animal.age << "\n";
    std::cout << "------------------------------------\n";
}

void AnimalView::showAnimalNotFound() {
    std::cout << "Animal nao encontrado.\n";
}