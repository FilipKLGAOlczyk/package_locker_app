//
// Created by Filip Olczyk on 06/06/2026.
//

#ifndef PROGRAM_CLIENTMANAGER_H
#define PROGRAM_CLIENTMANAGER_H
#include "repositories/ClientRepo.h"
#include "typedefs.h"

/**
 * @class ClientManager
 * @brief Class managing operations on clients.
 *
 * The manager acts as a service layer. It serves as an intermediary between the
 * application and the client repository (ClientRepo). It is responsible for
 * business logic validation (e.g., preventing duplicates) as well as finding
 * and saving data.
 */
class ClientManager {
private:
    ClientRepo clientRepo;
public:
    /**
    * @brief Registers a new client in the system.
    *
    * This method verifies whether a client with the provided identifier (id)
    * or email address already exists in the repository. If a duplicate is detected,
    * the method catches a std::invalid_argument exception, prints an error message
    * to std::cerr, and aborts the creation process.
    *
    * @param id Unique identifier for the new client.
    * @param firstName Client's first name.
    * @param lastName Client's last name.
    * @param email Client's email address (must be unique system-wide).
    * @return true If the client was successfully created and added to the repository.
    * @return false If the registration failed (e.g., the client already exists).
    */
    bool registerClient(int id, std::string firstName, std::string lastName, std::string email);
    /**
     * @brief Finds a client based on their email address.
     *
     * Utilizes a predicate to find a client in the repository with an exact email match.
     *
     * @param email The email address of the client to find.
     * @return ClientPtr A smart pointer to the found client, or nullptr if not found.
     */
    ClientPtr getClient(std::string email);
    /**
     * @brief Finds a client based on their unique identifier (id).
     *
     * Utilizes a predicate to find a client in the repository with an exact ID match.
     *
     * @param id The numerical identifier of the client to find.
     * @return ClientPtr A smart pointer to the found client, or nullptr if not found.
     */
    ClientPtr getClient(unsigned int id);
    /**
     * @brief Retrieves a list of all clients stored in the system.
     *
     * @return std::vector<ClientPtr> A vector of smart pointers containing all clients.
     */
    std::vector<ClientPtr> getAllClients();
    /**
     * @brief Saves the current state of all clients to a file.
     *
     * Delegates the save operation to the internal repository object (ClientRepo).
     *
     * @param path The path to the destination file where the data will be saved.
     */
    void saveToFile(const std::string& path) const;

};


#endif //PROGRAM_CLIENTMANAGER_H
