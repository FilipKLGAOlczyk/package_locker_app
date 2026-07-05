//
// Created by jopala on 31.05.2026.
//

#ifndef PROGRAM_EXPRESS_H
#define PROGRAM_EXPRESS_H
#include "model/Parcel.h"

/**
 * @enum ExpressParcelDeadline
 * @brief Represents the required delivery timeframe for an express parcel.
 *
 * The underlying integer values of this enum correspond to the price
 * percentage multiplier applied to the base price of the parcel.
 * For example, a value of 120 translates to a 1.2x multiplier.
 */
enum class ExpressParcelDeadline {
    weekendDelivery = 120,
    nextDay = 150,
    sameDay = 250
};
/**
 * @class Express
 * @brief Represents an express delivery parcel.
 *
 * This class inherits from the abstract `Parcel` base class. It introduces
 * the concept of delivery deadlines, which directly affect the final cost
 * of the shipment through a specific pricing multiplier.
 */
class Express : public Parcel {
private:
    const ExpressParcelDeadline deadline;
public:
    /**
     * @brief Constructs a new Express parcel object.
     *
     * @param id The unique identifier for the parcel.
     * @param status The initial tracking status of the parcel.
     * @param sender Smart pointer to the sending client.
     * @param recipient Smart pointer to the receiving client.
     * @param origin Smart pointer to the origin locker.
     * @param destination Smart pointer to the destination locker.
     * @param base_price The standard shipping cost before the express multiplier is applied.
     * @param deadline The required delivery timeframe, dictating the price multiplier.
     */
    Express(int id, ParcelStatus status, const ClientPtr &sender, const ClientPtr &recipient, const LockerPtr &origin,
        const LockerPtr &destination, double base_price, ExpressParcelDeadline deadline)
        : Parcel(id, status, sender, recipient, origin, destination, base_price),
          deadline(deadline) {
    }
    /**
     * @brief Default destructor.
     */
    ~Express() override = default;
    /**
     * @brief Generates a brief formatted string with basic express parcel information.
     * @return std::string A summary including base parcel info, deadline type, multiplier, and actual price.
     */
    std::string getInfo() const override;
    /**
     * @brief Generates a detailed formatted string of the express parcel.
     * @return std::string A multi-line string containing all base details plus specific express attributes.
     */
    std::string getFullInfo() const override;
    /**
     * @brief Calculates the final price of the express parcel.
     *
     * Implements the pure virtual function from the `Parcel` base class.
     * The cost is calculated by multiplying the base price by the deadline multiplier.
     *
     * @return double The final calculated price.
     */
    double getActualPrice() const override;
    /**
     * @brief Retrieves the assigned deadline enum value.
     * @return ExpressParcelDeadline The delivery deadline of the parcel.
     */
    ExpressParcelDeadline getDeadline();
    /**
     * @brief Retrieves the deadline as a readable string.
     * @return std::string A string representation of the deadline (e.g., "nextDay").
     */
    std::string getDeadlineString() const;
    /**
     * @brief Calculates the decimal multiplier based on the deadline enum.
     *
     * Converts the underlying integer value of the enum (e.g., 150) into
     * a decimal multiplier (e.g., 1.5).
     *
     * @return double The price multiplier associated with the deadline.
     */
    double getDeadlineMultiplier() const;
};

#endif //PROGRAM_EXPRESS_H
