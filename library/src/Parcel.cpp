//
// Created by Filip Olczyk on 24/05/2026.
//

#include "model/Parcel.h"

#include "model/Client.h"
#include "model/Locker.h"


Parcel::Parcel(unsigned int id, ParcelStatus status, const ClientPtr &sender, const ClientPtr &recipient, const LockerPtr &origin, const LockerPtr &destination, double base_price)
    : id(id), status(status), sender(sender), recipient(recipient), origin(origin), destination(destination), basePrice(base_price){
    if (base_price < 0.0) throw std::invalid_argument("Base price cannot be negative");
}

std::string Parcel::getStatusString() const {
    switch (this->status) {
        case::ParcelStatus::registered:
            return "registered";
        case::ParcelStatus::dispatched:
            return "dispatched";
        case::ParcelStatus::enRoute:
            return "enRoute";
        case::ParcelStatus::deliveredToLocker:
            return "deliveredToLocker";
        case::ParcelStatus::collected:
            return "collected";
        default:
            return "unknown";

    }
}

std::string Parcel::getInfo() const {
    return std::format("[Parcel] ID: {}, Sender: {}, Origin: {}, Recipient: {}, Destination: {}, basePrice: {}", getId(), sender->getEmail(), origin->getLocation(), recipient->getEmail(), destination->getLocation(), getBasePrice());
}

std::string Parcel::getFullInfo() const {
    std::stringstream ss;
    ss << std::format("[Parcel] ID: {}, basePrice: {}\n", getId(), getBasePrice());
    ss << std::format("  Sender: {}\n", sender->getInfo());
    ss << std::format("  Origin: {}\n", origin->getInfo());
    ss << std::format("  Recipient: {}\n", recipient->getInfo());
    ss << std::format("  Destination: {}\n", destination->getInfo());
    return ss.str();
}

unsigned int Parcel::getId() const {
    return id;
}

ParcelStatus Parcel::getStatus() const {
    return status;
}

void Parcel::setStatus(const ParcelStatus status) {
    this->status = status;
}

ClientPtr Parcel::getSender() const {
    return sender;
}

ClientPtr Parcel::getRecipient() const {
    return recipient;
}

LockerPtr Parcel::getOrigin() const {
    return origin;
}

LockerPtr Parcel::getDestination() const {
    return destination;
}

double Parcel::getBasePrice() const {
    return basePrice;
}
