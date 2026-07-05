//
// Created by Filip Olczyk on 24/05/2026.
//

#include "model/Client.h"

#include <format>

Client::Client(unsigned int id, std::string firstName, std::string lastName, std::string email)
: id(id), firstName(firstName), lastName(lastName), email(email){}


std::string Client::getInfo() const {
    return std::format("[Client] ID: {}, {} {} ({})", std::to_string(id), firstName, lastName, email);
}

unsigned int Client::getId() const {
    return id;
}

const std::string &Client::getFirstName() const {
    return firstName;
}

const std::string &Client::getLastName() const {
    return lastName;
}

const std::string &Client::getEmail() const {
    return email;
}

