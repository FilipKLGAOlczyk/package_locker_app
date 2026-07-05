//
// Created by Filip Olczyk on 30/05/2026.
//

#include "repositories/ClientRepo.h"
#include "model/Client.h"
#include <typedefs.h>
#include <algorithm>
#include <format>

#include "Exceptions.h"


using json = nlohmann::json;


void ClientRepo::add(ClientPtr client) {
    if (client==nullptr)throw std::invalid_argument("Client cannot be null");
    clients.push_back(client);
}

void ClientRepo::remove(ClientPtr client) {
    if (client==nullptr)throw std::invalid_argument("Client cannot be null");
    clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());
}

std::string ClientRepo::report() {
    std::string report = "";
    for (auto client : clients) {
        report += client->getInfo() + "\n";
    }
    return report;
}

int ClientRepo::size() {
    return clients.size();
}

ClientPtr ClientRepo::findBy(ClientPredicate predicate) {
    for (auto client : clients) {
        if (predicate(client)) {
            return client;
        }
    }
    return nullptr;
}

std::vector<ClientPtr> ClientRepo::findAllBy(ClientPredicate predicate) {
    std::vector<ClientPtr> result;
    for (auto client : clients) {
        if (predicate(client)) {
            result.push_back(client);
        }
    }
    return result;
}

void ClientRepo::saveToFile(const std::string &path) const {
    json jsonArray = json::array();
    for (auto client : clients) {
        if (client != nullptr) {
            json jClient;
            jClient["id"] = client->getId();
            jClient["firstName"] = client->getFirstName();
            jClient["lastName"] = client->getLastName();
            jClient["email"] = client->getEmail();
            jsonArray.push_back(jClient);
        }
    }
    std::ofstream file(path);
    if (file.is_open()) {
        file << jsonArray.dump(4);
        file.close();
    } else {
        throw Exceptions::FileWriteErrorException(std::format("Could not write to file {} while trying to save Clients to a file.", path));
    }

}


