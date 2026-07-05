//
// Created by Filip Olczyk on 06/06/2026.
//

#ifndef PROGRAM_PARCELMANAGER_H
#define PROGRAM_PARCELMANAGER_H
#include "model/parcels/Express.h"
#include "repositories/ParcelRepo.h"


enum class ParcelStatus;
/**
 * @class ParcelManager
 * @brief Class managing operations and lifecycle of parcels.
 *
 * This manager acts as a service layer handling the business logic for parcels.
 * It manages the creation of specific parcel types, orchestrates status transitions
 * (dispatch, transit, delivery, collection), and interacts with the ParcelRepo
 * for data persistence and retrieval.
 */
class ParcelManager {
private:
    ParcelRepo parcelRepo;
public:
    /**
     * @brief Registers a new parcel in the system.
     *
     * This template method creates a specific subtype of Parcel (e.g., Standard,
     * Express, Insured) using perfect forwarding for subtype-specific arguments.
     * It verifies if a parcel with the given ID already exists to prevent duplicates.
     *
     * @tparam ParcelType The specific derived class of Parcel to instantiate.
     * @tparam Args Variadic template arguments specific to the ParcelType constructor.
     * @param id Unique identifier for the new parcel.
     * @param sender Smart pointer to the client sending the parcel.
     * @param recipient Smart pointer to the client receiving the parcel.
     * @param origin Smart pointer to the locker where the parcel is dropped off.
     * @param destination Smart pointer to the target locker.
     * @param basePrice The base shipping cost before applying specific parcel type multipliers.
     * @param args Additional arguments required by the specific ParcelType constructor.
     * @return true If the parcel was successfully created and added to the repository.
     * @return false If registration failed (e.g., a parcel with this ID already exists).
     */
    template <typename ParcelType, typename... Args>
    bool registerParcel(int id, const ClientPtr &sender, const ClientPtr &recipient,
                            const LockerPtr &origin, const LockerPtr &destination, double basePrice, Args&&... args) {
        ParcelPtr existingParcel = getParcel(id);
        try {
            if (existingParcel) throw std::invalid_argument("Parcel with id " + std::to_string(id) + " already exists");
        } catch (std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
        ParcelStatus status = ParcelStatus::registered;
        ParcelPtr newParcel = std::make_shared<ParcelType>(id, status, sender,
            recipient, origin, destination, basePrice, std::forward<Args>(args)...);
        parcelRepo.add(newParcel);
        return true;
    }
    /**
     * @brief Dispatches a parcel from the sender to the origin locker.
     *
     * Changes the parcel's status from 'registered' to 'dispatched' and
     * physically assigns it to the origin locker's inventory.
     *
     * @param parcel Smart pointer to the parcel being dispatched.
     */
    void dispatchParcel(ParcelPtr parcel);
    /**
     * @brief Courier collects the parcel from the origin locker.
     *
     * Removes the parcel from the origin locker's inventory and updates
     * its status from 'dispatched' to 'enRoute' (in transit).
     *
     * @param parcel Smart pointer to the parcel being collected by the courier.
     */
    void courierCollectParcel(ParcelPtr parcel);
    /**
     * @brief Courier delivers the parcel to the destination locker.
     *
     * Adds the parcel to the destination locker's inventory and updates
     * its status from 'enRoute' to 'deliveredToLocker'.
     *
     * @param parcel Smart pointer to the parcel being delivered.
     */
    void deliverParcel(ParcelPtr parcel);
    /**
     * @brief Recipient collects the parcel from the destination locker.
     *
     * Removes the parcel from the destination locker's inventory and updates
     * its status from 'deliveredToLocker' to 'collected'. This completes the lifecycle.
     *
     * @param parcel Smart pointer to the parcel being picked up by the recipient.
     */
    void collectParcel(ParcelPtr parcel);
    /**
     * @brief Retrieves all parcels addressed to a specific recipient.
     *
     * @param client Smart pointer to the recipient client.
     * @return std::vector<ParcelPtr> A vector of parcels bound for the specified recipient.
     */
    std::vector<ParcelPtr> getRecipientsParcels(const ClientPtr &client);
    /**
     * @brief Retrieves all parcels bound for a specific destination locker.
     *
     * @param locker Smart pointer to the destination locker.
     * @return std::vector<ParcelPtr> A vector of parcels routing to the specified locker.
     */
    std::vector<ParcelPtr> getDestinationsParcels(const LockerPtr &locker);
    /**
     * @brief Finds a parcel based on its unique identifier.
     *
     * @param id The numerical identifier of the parcel to find.
     * @return ParcelPtr A smart pointer to the found parcel, or nullptr if not found.
     */
    ParcelPtr getParcel(int id);
    /**
     * @brief Retrieves a list of all parcels stored in the system.
     *
     * @return std::vector<ParcelPtr> A vector of smart pointers containing all parcels.
     */
    std::vector<ParcelPtr> getAllParcels();
    /**
     * @brief Calculates and retrieves the final price of a parcel.
     *
     * @param parcel Smart pointer to the parcel.
     * @return double The actual, finalized price of the parcel after all modifiers.
     */
    double getFinalPrice(ParcelPtr parcel);
    /**
     * @brief Saves the current state of all parcels to a file.
     *
     * @param path The path to the destination file where the data will be saved.
     */
    void saveToFile(const std::string& path) const;

};


#endif //PROGRAM_PARCELMANAGER_H
