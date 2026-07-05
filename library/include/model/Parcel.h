//
// Created by Filip Olczyk on 24/05/2026.
//

#ifndef MKAR_PT_1015_04_PARCEL_H
#define MKAR_PT_1015_04_PARCEL_H
#include "typedefs.h"

/**
 * @enum ParcelStatus
 * @brief Represents the current tracking lifecycle stage of a parcel.
 */
enum class ParcelStatus {
    registered,
    dispatched,
    enRoute,
    deliveredToLocker,
    collected
};
/**
 * @class Parcel
 * @brief Abstract base class representing a generic parcel in the delivery system.
 *
 * This class encapsulates the core data of a shipment, including its routing
 * (origin, destination), stakeholders (sender, recipient), tracking status,
 * and base pricing. It inherits from std::enable_shared_from_this to allow
 * safe creation of shared pointers to itself.
 *
 * @note This is an abstract class. Derived classes (e.g., Express, Standard)
 * must implement the `getActualPrice()` method to provide specific pricing logic.
 */
class Parcel : public std::enable_shared_from_this<Parcel>{
private:
    unsigned int id;
    ParcelStatus status;
    ClientPtr sender;
    ClientPtr recipient;
    LockerPtr origin;
    LockerPtr destination;
    double basePrice;
public:
    /**
     * @brief Constructs a new Parcel object.
     *
     * @param id The unique identifier for the parcel.
     * @param status The initial status of the parcel (typically 'registered').
     * @param sender Smart pointer to the sending client.
     * @param recipient Smart pointer to the receiving client.
     * @param origin Smart pointer to the origin locker.
     * @param destination Smart pointer to the destination locker.
     * @param base_price The base cost for shipping this parcel.
     * @throws std::invalid_argument If the base_price is less than 0.0.
     */
    Parcel(unsigned int id, ParcelStatus status, const ClientPtr &sender, const ClientPtr &recipient, const LockerPtr &origin,
        const LockerPtr &destination, double base_price);
    /**
     * @brief Default virtual destructor.
     */
    virtual ~Parcel() = default;
    /**
     * @brief Generates a brief formatted string with basic parcel information.
     * @return std::string A single-line summary of the parcel's routing and base price.
     */
    virtual std::string getInfo() const;
    /**
     * @brief Generates a detailed formatted string of the parcel and its stakeholders.
     * @return std::string A multi-line string containing details of the parcel, sender, recipient, and lockers.
     */
    virtual std::string getFullInfo() const;
    /**
     * @brief Retrieves the parcel's unique identifier.
     * @return unsigned int The ID of the parcel.
     */
    [[nodiscard]] unsigned int getId() const;
    /**
     * @brief Retrieves the current tracking status of the parcel.
     * @return ParcelStatus The current status enum value.
     */
    [[nodiscard]] ParcelStatus getStatus() const;
    /**
     * @brief Retrieves the current tracking status as a readable string.
     * @return std::string A string representation of the current ParcelStatus.
     */
    [[nodiscard]] std::string getStatusString() const;
    /**
     * @brief Retrieves the sender of the parcel.
     * @return ClientPtr A smart pointer to the sending client.
     */
    [[nodiscard]] ClientPtr getSender() const;
    /**
     * @brief Retrieves the recipient of the parcel.
     * @return ClientPtr A smart pointer to the receiving client.
     */
    [[nodiscard]] ClientPtr getRecipient() const;
    /**
     * @brief Retrieves the origin locker.
     * @return LockerPtr A smart pointer to the origin locker.
     */
    [[nodiscard]] LockerPtr getOrigin() const;
    /**
     * @brief Retrieves the destination locker.
     * @return LockerPtr A smart pointer to the destination locker.
     */
    [[nodiscard]] LockerPtr getDestination() const;
    /**
     * @brief Retrieves the base shipping price.
     * @return double The unadjusted base price.
     */
    [[nodiscard]] double getBasePrice() const;
    /**
     * @brief Calculates the final price of the parcel.
     *
     * Pure virtual function. Derived classes must implement this to calculate
     * the final cost, applying any specific multipliers or flat fees (e.g., insurance, express fees).
     *
     * @return double The fully calculated, final price.
     */
    virtual double getActualPrice() const = 0;
    /**
     * @brief Updates the tracking status of the parcel.
     * @param status The new status to apply.
     */
    void setStatus(const ParcelStatus status);
};



#endif //MKAR_PT_1015_04_PARCEL_H
