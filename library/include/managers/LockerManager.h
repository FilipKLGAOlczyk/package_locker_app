//
// Created by Filip Olczyk on 06/06/2026.
//

#ifndef PROGRAM_LOCKERMANAGER_H
#define PROGRAM_LOCKERMANAGER_H
#include "repositories/LockerRepo.h"

/**
 * @class LockerManager
 * @brief Class managing operations on parcel lockers.
 *
 * This manager acts as a service layer handling the business logic for locker
 * entities. It acts as an intermediary between the application and the
 * LockerRepo, ensuring data integrity (e.g., preventing duplicate IDs)
 * before interacting with the repository.
 */
class LockerManager {
    private:
    LockerRepo lockerRepo;
public:
    /**
     * @brief Registers a new locker in the system.
     *
     * This method checks if a locker with the specified identifier (id) already
     * exists. If the ID is unique, it creates a new Locker object and adds it
     * to the repository.
     *
     * @param id Unique identifier for the new locker.
     * @param location The physical address or location name of the locker.
     * @param lockerCount The total number of individual compartments in the locker.
     * @return true If the locker was successfully created and added.
     * @return false If registration failed (e.g., a locker with this ID already exists).
     */
    bool registerLocker(unsigned int id, std::string location, int lockerCount);
    /**
     * @brief Finds a locker based on its unique identifier (id).
     *
     * Utilizes a predicate to search the repository for a locker with an exact ID match.
     *
     * @param id The numerical identifier of the locker to find.
     * @return LockerPtr A smart pointer to the found locker, or nullptr if not found.
     */
    LockerPtr getLocker(unsigned int id);
    /**
     * @brief Retrieves a list of all lockers stored in the system.
     *
     * @return std::vector<LockerPtr> A vector of smart pointers containing all lockers.
     */
    std::vector<LockerPtr> getAllLockers();
    /**
     * @brief Saves the current state of all lockers to a file.
     *
     * Delegates the data persistence operation to the internal repository (LockerRepo).
     *
     * @param path The path to the destination file where the data will be saved.
     */
    void saveToFile(const std::string& path) const;

};


#endif //PROGRAM_LOCKERMANAGER_H
