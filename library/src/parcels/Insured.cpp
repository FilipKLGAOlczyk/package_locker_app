//
// Created by jopala on 31.05.2026.
//

#include "model/parcels/Insured.h"

std::string Insured::getInfo() const {
    return std::format("{} [Insured] Fragile: {:s} Directional: {:s} declaredValue: {} InsurancePrice: {} ActualPrice: {}", Parcel::getInfo(), isFragile(), isDirectional(), getDeclaredValue(), getInsurancePrice(), getActualPrice());
}

std::string Insured::getFullInfo() const {
    std::stringstream ss;
    ss << Parcel::getFullInfo();
    ss << "  Type: Insured\n";
    ss << std::format("  Fragile: {:s}\n", isFragile());
    ss << std::format("  Directional: {:s}\n", isDirectional());
    ss << std::format("  Declared value: {}\n", getDeclaredValue());
    ss << std::format("  Insurance price: {}\n", getInsurancePrice());
    ss << std::format("  Actual price: {}\n", getActualPrice());
    return ss.str();
}


double Insured::getActualPrice() const {
    return Parcel::getBasePrice() + getInsurancePrice();
}

bool Insured::isFragile() const {
    return fragile;
}

bool Insured::isDirectional() const {
    return directional;
}

double Insured::getDeclaredValue() const {
    return declaredValue;
}

double Insured::getInsurancePrice() const {
    double multiplier = 0.005;
    if (isFragile()) {
        multiplier += 0.010;
    }
    if (isDirectional()) {
        multiplier += 0.005;
    }
    return multiplier * getDeclaredValue();
}
