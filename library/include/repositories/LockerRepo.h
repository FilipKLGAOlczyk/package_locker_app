//
// Created by Filip Olczyk on 31/05/2026.
//

#ifndef PROGRAM_LOCKERREPO_H
#define PROGRAM_LOCKERREPO_H
#include "typedefs.h"

/**
 * @class LockerRepo
 * @brief Repository class for managing a collection of parcel lockers.
 *
 * This class acts as an in-memory database for `Locker` objects. It provides
 * standard operations to add, remove, and query lockers using functional
 * predicates. It also supports serializing the current state of all lockers
 * (including the IDs of their stored parcels) into a JSON file.
 */
class LockerRepo {
private:
    std::vector<LockerPtr> lockers;
public:
    /**
     * @brief Adds a new locker to the repository.
     * @param locker A smart pointer to the locker to be added.
     * @throws std::invalid_argument If the provided locker pointer is null.
     */
    void add(LockerPtr locker);
    /**
     * @brief Removes a specific locker from the repository.
     * @param locker A smart pointer to the locker to be removed.
     * @throws std::invalid_argument If the provided locker pointer is null.
     */
    void remove(LockerPtr locker);
    /**
     * @brief Generates a consolidated report of all lockers in the repository.
     * @return std::string A multi-line string containing the basic info of every locker.
     */
    std::string report();
    /**
     * @brief Retrieves the current number of lockers in the repository.
     * @return int The total count of stored lockers.
     */
    int size();
    /**
     * @brief Finds a single locker based on a specific condition.
     * * Iterates through the repository and returns the first locker that
     * satisfies the provided predicate function.
     *
     * @param predicate A functional object or lambda evaluating a LockerPtr and returning a boolean.
     * @return LockerPtr A smart pointer to the found locker, or nullptr if no match is found.
     */
    LockerPtr findBy(LockerPredicate predicate);
    /**
     * @brief Finds all lockers that match a specific condition.
     * * Iterates through the repository and collects every locker that
     * satisfies the provided predicate function.
     *
     * @param predicate A functional object or lambda evaluating a LockerPtr and returning a boolean.
     * @return std::vector<LockerPtr> A vector containing all matching lockers.
     */
    std::vector<LockerPtr> findAllBy(LockerPredicate predicate);
    /**
     * @brief Serializes the repository data and saves it to a JSON file.
     * * Converts all valid locker objects into JSON format using the `nlohmann::json`
     * library. To prevent circular dependencies, nested parcels are serialized
     * strictly as an array of their integer IDs.
     *
     * @param path The destination file path where the JSON data will be saved.
     * @throws Exceptions::FileWriteErrorException If the file cannot be opened for writing.
     */
    void saveToFile(const std::string& path) const;
};


#endif //PROGRAM_LOCKERREPO_H
