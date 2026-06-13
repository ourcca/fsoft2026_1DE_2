/*
AnimalView.cpp

Created on: 15/05/2026
*/
#include "views/AnimalView.h"
#include "views/Utils.h"

#include <iostream>

int AnimalView::menu() {
    std::cout << "\n========== Gestão de Animais ==========\n";
    std::cout << "1. Registar Animal\n";
    std::cout << "2. Listar Animais\n";
    std::cout << "3. Consultar Animal por ID\n";
    std::cout << "4. Editar Animal\n";
    std::cout << "0. Voltar\n";

    return Utils::getNumber("Escolha uma opção: ");
}

std::string AnimalView::getName() {
    return Utils::getString("Nome: ");
}

std::string AnimalView::getSpecies() {
    return Utils::getString("Espécie: ");
}

std::string AnimalView::getBreed() {
    return Utils::getString("Raça: ");
}

float AnimalView::getWeight() {
    return Utils::getFloat("Peso: ");
}

int AnimalView::getAge() {
    return Utils::getNumber("Idade: ");
}

void AnimalView::showAnimalCreated() {
    std::cout << "Animal registado com sucesso.\n";
}

int AnimalView::getAnimalId() {
    return Utils::getNumber("ID do animal: ");
}

void AnimalView::showAnimalUpdated() {
    std::cout << "Animal editado com sucesso.\n";
}

void AnimalView::printAnimals(const std::vector<AnimalOutDTO>& animals) {
    if (animals.empty()) {
        std::cout << "Não existem animais registados.\n";
        return;
    }

    std::cout << "\n========== Lista de Animais ==========\n";

    for (const AnimalOutDTO& animal : animals) {
        std::cout << "ID: " << animal.id << "\n";
        std::cout << "Nome: " << animal.name << "\n";
        std::cout << "Espécie: " << animal.species << "\n";
        std::cout << "Raça: " << animal.breed << "\n";
        std::cout << "Peso: " << animal.weight << "\n";
        std::cout << "Idade: " << animal.age << "\n";
        std::cout << "--------------------------------------\n";
    }
}



void AnimalView::printAnimal(const AnimalOutDTO& animal) {
    std::cout << "\n========== Dados do Animal ==========\n";
    std::cout << "ID: " << animal.id << "\n";
    std::cout << "Nome: " << animal.name << "\n";
    std::cout << "Espécie: " << animal.species << "\n";
    std::cout << "Raça: " << animal.breed << "\n";
    std::cout << "Peso: " << animal.weight << "\n";
    std::cout << "Idade: " << animal.age << "\n";
    std::cout << "------------------------------------\n";
}

void AnimalView::showAnimalNotFound() {
    std::cout << "Animal não encontrado.\n";
}
