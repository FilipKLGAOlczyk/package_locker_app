//
// Created by jopala on 31.05.2026.
//

#include "model/parcels/Express.h"

std::string Express::getInfo() const {
    std::string deadlineString;
    switch (deadline) {
        case ExpressParcelDeadline::weekendDelivery:
            deadlineString = "weekendDelivery";
            break;
        case ExpressParcelDeadline::nextDay:
            deadlineString = "nextDay";
            break;
        case ExpressParcelDeadline::sameDay:
            deadlineString = "sameDay";
            break;
        default:
            deadlineString = "unknown";
            break;
    }
    return std::format("{} [Express] Deadline: {} Multiplier: {}x Actual price: {}", Parcel::getInfo(), deadlineString, getDeadlineMultiplier(), getActualPrice());
}

std::string Express::getFullInfo() const {
    std::stringstream ss;
    ss << Parcel::getFullInfo();
    ss << "  Type: Express\n";
    ss << std::format("  Deadline: {}\n", getDeadlineString());
    ss << std::format("  Deadline multiplier: {}\n", getDeadlineMultiplier());
    ss << std::format("  Actual price: {}\n", getActualPrice());

    return ss.str();
}

double Express::getActualPrice() const {
    return Parcel::getBasePrice() * getDeadlineMultiplier();
}

ExpressParcelDeadline Express::getDeadline() {
    return deadline;
}

std::string Express::getDeadlineString() const {
    switch (this->deadline) {
        case ExpressParcelDeadline::weekendDelivery:
            return "weekendDelivery";
        case ExpressParcelDeadline::nextDay:
            return "nextDay";
        case ExpressParcelDeadline::sameDay:
            return "sameDay";
        default:
            return "unknown";
    }
}

double Express::getDeadlineMultiplier() const {
    double multiplier = std::to_underlying(deadline) / 100.0;
    return multiplier;
}
