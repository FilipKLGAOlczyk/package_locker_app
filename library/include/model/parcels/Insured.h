//
// Created by jopala on 31.05.2026.
//

#ifndef PROGRAM_INSURED_H
#define PROGRAM_INSURED_H
#include "model/Parcel.h"

/**
 * @class Insured
 * @brief Represents a parcel with declared value and insurance.
 *
 * This class inherits from the abstract `Parcel` base class. It adds specific
 * properties such as fragility, directional handling requirements, and a declared
 * financial value. These properties are used to calculate an additional insurance
 * premium added to the base shipping cost.
 */
class Insured : public Parcel {
private:
    const bool fragile;
    const bool directional;
    const double declaredValue;
public:
    /**
     * @brief Constructs a new Insured parcel object.
     *
     * @param id The unique identifier for the parcel.
     * @param status The initial tracking status of the parcel.
     * @param sender Smart pointer to the sending client.
     * @param recipient Smart pointer to the receiving client.
     * @param origin Smart pointer to the origin locker.
     * @param destination Smart pointer to the destination locker.
     * @param base_price The standard shipping cost before insurance is added.
     * @param fragile Set to true if the contents are fragile.
     * @param directional Set to true if the parcel requires specific directional handling.
     * @param declared_value The financial value to insure the parcel for.
     */
    Insured(int id, ParcelStatus status, const ClientPtr &sender, const ClientPtr &recipient, const LockerPtr &origin,
        const LockerPtr &destination, double base_price, bool fragile, bool directional, double declared_value)
        : Parcel(id, status, sender, recipient, origin, destination, base_price),
          fragile(fragile),
          directional(directional),
          declaredValue(declared_value) {
    }
    /**
     * @brief Default destructor.
     */
    ~Insured() override = default;
    /**
     * @brief Generates a brief formatted string with basic insured parcel information.
     * @return std::string A summary including base parcel info, flags, declared value, and pricing.
     */
    std::string getInfo() const override;
    /**
     * @brief Generates a detailed formatted string of the insured parcel.
     * @return std::string A multi-line string containing all base details plus specific insurance attributes.
     */
    std::string getFullInfo() const override;
    /**
     * @brief Calculates the final price of the insured parcel.
     *
     * Implements the pure virtual function from the `Parcel` base class.
     * The final cost is the sum of the base price and the calculated insurance price.
     *
     * @return double The final calculated price.
     */
    double getActualPrice() const override;
    /**
     * @brief Checks if the parcel is marked as fragile.
     * @return true If the parcel is fragile.
     * @return false Otherwise.
     */
    bool isFragile() const;
    /**
     * @brief Checks if the parcel has specific directional requirements.
     * @return true If the parcel is directional.
     * @return false Otherwise.
     */
    bool isDirectional() const;
    /**
     * @brief Retrieves the declared financial value of the parcel.
     * @return double The declared value.
     */
    double getDeclaredValue() const;
    /**
     * @brief Calculates the cost of the insurance premium.
     *
     * The insurance cost is calculated as a percentage of the declared value:
     * - Base insurance rate: 0.5%
     * - Fragile surcharge: +1.0%
     * - Directional surcharge: +0.5%
     *
     * @return double The calculated cost of the insurance.
     */
    double getInsurancePrice() const;
};

#endif //PROGRAM_INSURED_H
