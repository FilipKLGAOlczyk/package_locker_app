//
// Created by Filip Olczyk on 06/06/2026.
//

#include "managers/ClientManager.h"

#include "model/Client.h"


bool ClientManager::registerClient(int id, std::string firstName, std::string lastName, std::string email) {
    ClientPtr existingClientEmail = getClient(email);
    ClientPtr existingClientId = getClient(id);
    if (existingClientEmail) {
        return false;
    }
    if (existingClientId) {
        return false;
    }
    ClientPtr newClient = std::make_shared<Client>(id, firstName, lastName, email);
    clientRepo.add(newClient);
    return true;
}

ClientPtr ClientManager::getClient(std::string email) {
    return clientRepo.findBy([&email](const ClientPtr &client){return client->getEmail()==email;});
}

ClientPtr ClientManager::getClient(unsigned int id) {
    return clientRepo.findBy([&id](const ClientPtr &client){return client->getId()==id;});
}

std::vector<ClientPtr> ClientManager::getAllClients() {
    return clientRepo.findAllBy([] (ClientPtr) {return true;});
}

void ClientManager::saveToFile(const std::string &path) const {
    clientRepo.saveToFile(path);
}
