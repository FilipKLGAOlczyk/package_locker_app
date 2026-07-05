//
// Created by Filip Olczyk on 30/05/2026.
//

#ifndef PROGRAM_CLIENTREPO_H
#define PROGRAM_CLIENTREPO_H
#include "typedefs.h"

/**
 * @class ClientRepo
 * @brief Repository class for managing a collection of clients.
 *
 * This class acts as an in-memory database for `Client` objects. It provides
 * standard CRUD-like operations (Create, Read, Delete) and uses functional
 * predicates to allow flexible searching and filtering. It also handles
 * the serialization of client data to a JSON file.
 */
class ClientRepo {
private:
    std::vector<ClientPtr> clients;
public:
    /**
     * @brief Adds a new client to the repository.
     * * @param client A smart pointer to the client to be added.
     * @throws std::invalid_argument If the provided client pointer is null.
     */
    void add(ClientPtr client);
    /**
     * @brief Removes a specific client from the repository.
     * * @param client A smart pointer to the client to be removed.
     * @throws std::invalid_argument If the provided client pointer is null.
     */
    void remove(ClientPtr client);
    /**
     * @brief Generates a consolidated report of all clients in the repository.
     * * @return std::string A multi-line string containing the info of every client.
     */
    std::string report();
    /**
     * @brief Retrieves the current number of clients in the repository.
     * * @return int The total count of stored clients.
     */
    int size();
    /**
     * @brief Finds a single client based on a specific condition.
     * * Iterates through the repository and returns the first client that
     * satisfies the provided predicate function.
     *
     * @param predicate A functional object or lambda evaluating a ClientPtr and returning a boolean.
     * @return ClientPtr A smart pointer to the found client, or nullptr if no match is found.
     */
    ClientPtr findBy(ClientPredicate predicate);
    /**
     * @brief Finds all clients that match a specific condition.
     * * Iterates through the repository and collects every client that
     * satisfies the provided predicate function.
     *
     * @param predicate A functional object or lambda evaluating a ClientPtr and returning a boolean.
     * @return std::vector<ClientPtr> A vector containing all matching clients.
     */
    std::vector<ClientPtr> findAllBy(ClientPredicate predicate);
    /**
     * @brief Serializes the repository data and saves it to a JSON file.
     * * Converts all valid client objects into JSON format using the `nlohmann::json`
     * library and writes the resulting array to the specified file path.
     *
     * @param path The destination file path where the JSON data will be saved.
     * @throws Exceptions::FileWriteErrorException If the file cannot be opened for writing.
     */
    void saveToFile(const std::string& path) const;
};


#endif //PROGRAM_CLIENTREPO_H
