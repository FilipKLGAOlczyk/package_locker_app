//
// Created by Filip Olczyk on 24/05/2026.
//

#ifndef MKAR_PT_1015_04_CLIENT_H
#define MKAR_PT_1015_04_CLIENT_H
#include <string>

/**
 * @class Client
 * @brief Represents a client in the system.
 *
 * This class stores the personal details of a client, such as their
 * unique ID, first name, last name, and contact email. It provides
 * read-only access to these properties through getter methods.
 */
class Client {
private:
    unsigned int id;
    std::string firstName;
    std::string lastName;
    std::string email;
public:
    /**
     * @brief Constructs a new Client object.
     * * @param id The unique identifier to assign to the client.
     * @param first_name The first name of the client.
     * @param last_name The last name of the client.
     * @param email The email address of the client.
     */
    Client(unsigned int id, std::string first_name, std::string last_name, std::string email);
    /**
     * @brief Default destructor.
     */
    ~Client() = default;
    /**
     * @brief Retrieves the client's unique identifier.
     * * @return unsigned int The ID of the client.
     */
    unsigned int getId() const;
    /**
     * @brief Retrieves the client's first name.
     * * @return const std::string& A constant reference to the client's first name.
     */
    const std::string &getFirstName() const;
    /**
     * @brief Retrieves the client's last name.
     * * @return const std::string& A constant reference to the client's last name.
     */
    const std::string &getLastName() const;
    /**
     * @brief Retrieves the client's email address.
     * * @return const std::string& A constant reference to the client's email address.
     */
    const std::string &getEmail() const;
    /**
     * @brief Generates a formatted string containing the client's information.
     * * @return std::string A formatted string detailing the client's ID, full name, and email.
     */
    std::string getInfo() const;
};



#endif //MKAR_PT_1015_04_CLIENT_H
