//
// Created by jopala on 31.05.2026.
//

#ifndef PROGRAM_STANDARD_H
#define PROGRAM_STANDARD_H
#include "model/Parcel.h"
/**
 * @class Standard
 * @brief Represents a standard delivery parcel.
 *
 * This class inherits from the abstract `Parcel` base class. It represents
 * the default, baseline shipping option. Unlike Express or Insured parcels,
 * a Standard parcel incurs no additional fees or multipliers, meaning its
 * final cost is exactly equal to its base price.
 */
class Standard : public Parcel {
public:
    /**
     * @brief Constructs a new Standard parcel object.
     *
     * @param id The unique identifier for the parcel.
     * @param status The initial tracking status of the parcel.
     * @param sender Smart pointer to the sending client.
     * @param recipient Smart pointer to the receiving client.
     * @param origin Smart pointer to the origin locker.
     * @param destination Smart pointer to the destination locker.
     * @param base_price The standard shipping cost.
     */
    Standard(int id, ParcelStatus status, const ClientPtr &sender, const ClientPtr &recipient, const LockerPtr &origin,
        const LockerPtr &destination, double base_price)
        : Parcel(id, status, sender, recipient, origin, destination, base_price) {
    }
    /**
     * @brief Default destructor.
     */
    ~Standard() override = default;
    /**
     * @brief Generates a brief formatted string with basic standard parcel information.
     * @return std::string A summary including base parcel info and identifying it as "Standard".
     */
    std::string getInfo() const override;
    /**
     * @brief Generates a detailed formatted string of the standard parcel.
     * @return std::string A multi-line string containing all base details and the final actual price.
     */
    std::string getFullInfo() const override;
    /**
     * @brief Calculates the final price of the standard parcel.
     *
     * Implements the pure virtual function from the `Parcel` base class.
     * For standard parcels, no extra fees are applied, so this simply returns the base price.
     *
     * @return double The final calculated price (equal to base price).
     */
    double getActualPrice() const override;
};

#endif //PROGRAM_STANDARD_H
