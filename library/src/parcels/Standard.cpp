//
// Created by jopala on 31.05.2026.
//

#include "model/parcels/Standard.h"

std::string Standard::getInfo() const {
    return std::format("{} [Standard]", Parcel::getInfo());
}

double Standard::getActualPrice() const {
    return Parcel::getBasePrice();
}

std::string Standard::getFullInfo() const {
    std::stringstream ss;
    ss << Parcel::getFullInfo();
    ss << "  Type: Standard\n";
    ss << std::format("  Actual price: {}\n", getActualPrice());
    return ss.str();
}
