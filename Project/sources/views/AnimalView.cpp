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
    std::cout << "0. Voltar\n";

    return Utils::getNumber("Escolha uma opcao: ");
}

AnimalInDTO AnimalView::getAnimal() {
    AnimalInDTO dto{};

    dto.id = Utils::getNumber("ID: ");
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