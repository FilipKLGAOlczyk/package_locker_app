//
// Created by Filip Olczyk on 31/05/2026.
//

#ifndef PROGRAM_PARCELREPO_H
#define PROGRAM_PARCELREPO_H
#include <vector>

#include "typedefs.h"

/**
 * @class ParcelRepo
 * @brief Repository class for managing a collection of parcels.
 *
 * This class serves as an in-memory database for `Parcel` objects. It provides
 * standard methods to add, count, and query parcels using functional predicates.
 * Additionally, it handles polymorphic JSON serialization, ensuring that specific
 * parcel subtypes (Express, Insured, Standard) are correctly saved with their
 * unique attributes.
 */
class ParcelRepo {
private:
    std::vector<ParcelPtr> parcels;
public:
    /**
     * @brief Adds a new parcel to the repository.
     * @param parcel A smart pointer to the parcel to be added.
     * @throws std::invalid_argument If the provided parcel pointer is null.
     */
    void add(ParcelPtr parcel);
    /**
     * @brief Generates a consolidated report of all parcels in the repository.
     * @return std::string A multi-line string containing the basic info of every parcel.
     */
    std::string report();
    /**
     * @brief Retrieves the current number of parcels in the repository.
     * @return int The total count of stored parcels.
     */
    int size();
    /**
     * @brief Finds a single parcel based on a specific condition.
     * * Iterates through the repository and returns the first parcel that
     * satisfies the provided predicate function.
     *
     * @param predicate A functional object or lambda evaluating a ParcelPtr and returning a boolean.
     * @return ParcelPtr A smart pointer to the found parcel, or nullptr if no match is found.
     */
    ParcelPtr findBy(ParcelPredicate predicate);
    /**
     * @brief Finds all parcels that match a specific condition.
     * * Iterates through the repository and collects every parcel that
     * satisfies the provided predicate function.
     *
     * @param predicate A functional object or lambda evaluating a ParcelPtr and returning a boolean.
     * @return std::vector<ParcelPtr> A vector containing all matching parcels.
     */
    std::vector<ParcelPtr> findAllBy(ParcelPredicate predicate);
    /**
     * @brief Serializes the repository data and saves it to a JSON file.
     * * Converts all valid parcel objects into JSON format. It uses dynamic casting
     * to identify the specific subtype of the parcel (Express, Insured, or Standard)
     * and serializes subclass-specific fields accordingly. Related entities (sender,
     * recipient, origin, destination) are saved strictly by their numeric IDs.
     *
     * @param path The destination file path where the JSON data will be saved.
     * @throws Exceptions::FileWriteErrorException If the file cannot be opened for writing.
     */
    void saveToFile(const std::string& path) const;
};


#endif //PROGRAM_PARCELREPO_H
