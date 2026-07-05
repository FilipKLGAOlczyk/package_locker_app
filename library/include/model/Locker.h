//
// Created by Filip Olczyk on 24/05/2026.
//

#ifndef MKAR_PT_1015_04_LOCKER_H
#define MKAR_PT_1015_04_LOCKER_H
#include <string>

#include "typedefs.h"

/**
 * @class Locker
 * @brief Represents a physical parcel locker machine.
 *
 * This class stores information about a parcel locker, including its location
 * and maximum capacity. It also manages the current inventory of parcels
 * currently housed within the locker's compartments.
 */
class Locker {
private:
    unsigned int id;
    std::string location;
    unsigned int lockerCount;
    std::vector<std::shared_ptr<Parcel>> currentParcels;
public:
    /**
     * @brief Constructs a new Locker object.
     * * @param id The unique identifier for the locker.
     * @param location The physical address or description of the location.
     * @param lockerCount The total capacity (number of compartments) of the locker.
     */
    Locker(unsigned int id, std::string location, unsigned int lockerCount);
    /**
     * @brief Default destructor.
     */
    ~Locker() = default;
    /**
     * @brief Retrieves the locker's unique identifier.
     * * @return unsigned int The ID of the locker.
     */
    [[nodiscard]] unsigned int getId() const;
    /**
     * @brief Retrieves the location of the locker.
     * * @return std::string The location string.
     */
    [[nodiscard]] std::string getLocation() const;
    /**
     * @brief Retrieves the maximum capacity of the locker.
     * * @return unsigned int The total number of compartments.
     */
    [[nodiscard]] unsigned int getLockerCount() const;
    /**
     * @brief Retrieves the list of parcels currently stored in the locker.
     * * @return std::vector<ParcelPtr> A vector containing smart pointers to the stored parcels.
     */
    [[nodiscard]] std::vector<ParcelPtr> getCurrentParcels() const;
    /**
     * @brief Adds a parcel to the locker's inventory.
     * * @param parcel A smart pointer to the parcel to be added.
     * @throws std::invalid_argument If the provided parcel pointer is null.
     * @throws std::length_error If the locker is already at maximum capacity.
     */
    void addParcel(ParcelPtr parcel);
    /**
     * @brief Removes a specific parcel from the locker's inventory.
     * * @param parcel A smart pointer to the parcel to be removed.
     * @throws std::invalid_argument If the provided parcel pointer is null.
     */
    void removeParcel(ParcelPtr parcel);
    /**
     * @brief Checks if the locker has reached its maximum capacity.
     * * @return true If the number of current parcels equals the locker's capacity.
     * @return false If there is still space available in the locker.
     */
    bool isFull() const;
    /**
     * @brief Generates a brief formatted string with basic locker information.
     * * @return std::string A string detailing the ID, location, and current capacity status.
     */
    std::string getInfo() const;
    /**
     * @brief Generates a detailed formatted string including all stored parcels.
     * * @return std::string A multi-line string with the locker's basic info followed by
     * the details of every parcel currently inside it.
     */
    std::string getFullInfo() const;
};



#endif //MKAR_PT_1015_04_LOCKER_H
