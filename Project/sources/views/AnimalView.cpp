/*
AnimalView.cpp

Created on: 15/05/2026
*/
#include "views/AnimalView.h"
#include "views/Utils.h"
#include "services/AnimalCatalog.h"
#include <iostream>

int AnimalView::menu() {
    std::cout << "\n========== Gestão de Animais ==========\n";
    std::cout << "1. Registar Animal\n";
    std::cout << "2. Listar Animais\n";
    std::cout << "3. Consultar Animal por ID\n";
    std::cout << "4. Editar Animal\n";
    std::cout << "5. Remover Animal\n";
    std::cout << "0. Voltar\n";

    return Utils::getNumber("Escolha uma opção: ");
}

std::string AnimalView::getName() {
    return Utils::getString("Nome: ");
}

std::string AnimalView::getSpecies() {
    std::cout << "\nEspécies comuns disponíveis:\n";

    for (const std::string& species : AnimalCatalog::getCommonPetSpecies()) {
        std::cout << "- " << species << "\n";
    }

    std::cout << "\nEspécies exóticas disponíveis:\n";

    for (const std::string& species : AnimalCatalog::getExoticSpecies()) {
        std::cout << "- " << species << "\n";
    }

    return Utils::getString("Espécie: ");
}

std::string AnimalView::getBreed() {
    return Utils::getString("Raça: ");
}

std::string AnimalView::getBreed(const std::string& species) {
    if (AnimalCatalog::isExoticSpecies(species)) {
        std::cout << "Animal exótico selecionado. A raça não será pedida.\n";
        return "";
    }

    std::cout << "\nRaças disponíveis para esta espécie:\n";

    for (const std::string& breed : AnimalCatalog::getBreedsForSpecies(species)) {
        std::cout << "- " << breed << "\n";
    }

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

void AnimalView::showAnimalRemoved() {
    std::cout << "Animal removido com sucesso.\n";
}

void AnimalView::showAnimalRemoveCancelled() {
    std::cout << "Remocao do animal cancelada.\n";
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

bool AnimalView::confirmRemoveAssociatedData(int prescriptionCount, int serviceCount) {
    std::cout << "Este animal tem " << prescriptionCount << " prescrição(ões) e "
              << serviceCount << " serviço(s) associado(s).\n";

    std::string answer;

    do {
        answer = Utils::getString("Quer remover também as prescrições e serviços associados? (s/n): ");

        if (answer != "s" && answer != "S" && answer != "n" && answer != "N") {
            std::cout << "Opção inválida. Escreva s ou n.\n";
        }

    } while (answer != "s" && answer != "S" && answer != "n" && answer != "N");

    return answer == "s" || answer == "S";
}
