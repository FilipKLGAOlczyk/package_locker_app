//
// Created by Filip Olczyk on 24/05/2026.
//

#include "model/Locker.h"

#include "model/Parcel.h"

Locker::Locker(unsigned int id, std::string location, unsigned int lockerCount) : id(id), location(location), lockerCount(lockerCount){
}

unsigned int Locker::getId() const {
    return id;
}

std::string Locker::getLocation() const {
    return location;
}

unsigned int Locker::getLockerCount() const {
    return lockerCount;
}

std::vector<ParcelPtr> Locker::getCurrentParcels() const {
    return currentParcels;
}

void Locker::addParcel(ParcelPtr parcel) {
    if (parcel==nullptr) throw std::invalid_argument("Parcel cannot be null");
    if (isFull()) throw std::length_error("Locker is full");
    currentParcels.push_back(parcel);
}

void Locker::removeParcel(ParcelPtr parcel) {
    if (parcel==nullptr) throw std::invalid_argument("Parcel cannot be null");
    std::erase(currentParcels, parcel);
}

bool Locker::isFull() const {
    return currentParcels.size() == lockerCount;
}

std::string Locker::getInfo() const {
    return std::format("[Locker] ID: {}, Location: {}, Parcel#: {}/{}", id, location, currentParcels.size(), lockerCount);
}

std::string Locker::getFullInfo() const {
    std::stringstream ss;
    ss << std::format("{}\n", getInfo());
    ss << " Current parcels:\n";
    for (auto parcel : currentParcels) {
        ss << std::format("  {}\n", parcel->getInfo());
    }
    return ss.str();
}
