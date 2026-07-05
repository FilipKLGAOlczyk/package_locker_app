//
// Created by Filip Olczyk on 06/06/2026.
//

#include "managers/ParcelManager.h"
#include "model/Locker.h"
#include "model/Parcel.h"
#include "model/parcels/Express.h"
#include "model/parcels/Insured.h"
#include "model/parcels/Standard.h"

void ParcelManager::dispatchParcel(ParcelPtr parcel) {
    if (parcel->getStatusString()=="registered"){
        parcel->getOrigin()->addParcel(parcel);
        for (auto someParcel : parcel->getOrigin()->getCurrentParcels()) {
            if (someParcel->getId()==parcel->getId()) {
                parcel->setStatus(ParcelStatus::dispatched);
            }
        }
    }
}

void ParcelManager::courierCollectParcel(ParcelPtr parcel) {
    if (parcel->getStatusString()=="dispatched") {
        parcel->getOrigin()->removeParcel(parcel);
        parcel->setStatus(ParcelStatus::enRoute);
    }
}

void ParcelManager::deliverParcel(ParcelPtr parcel) {
    if (parcel->getStatusString()=="enRoute"){
        parcel->getDestination()->addParcel(parcel);
        for (auto someParcel : parcel->getDestination()->getCurrentParcels()) {
            if (someParcel->getId()==parcel->getId()) {
                parcel->setStatus(ParcelStatus::deliveredToLocker);
            }
        }
    }
}

void ParcelManager::collectParcel(ParcelPtr parcel) {
    if (parcel->getStatusString()=="deliveredToLocker"){
        parcel->getDestination()->removeParcel(parcel);
        parcel->setStatus(ParcelStatus::collected);
    }
}

std::vector<ParcelPtr> ParcelManager::getRecipientsParcels(const ClientPtr &recipient) {
    return parcelRepo.findAllBy([&recipient](const ParcelPtr &parcel){return parcel->getRecipient()==recipient;});
}

std::vector<ParcelPtr> ParcelManager::getDestinationsParcels(const LockerPtr &destination) {
    return parcelRepo.findAllBy([&destination](const ParcelPtr &parcel){return parcel->getDestination()==destination;});
}

double ParcelManager::getFinalPrice(ParcelPtr parcel) {
    return parcel->getActualPrice();
}
ParcelPtr ParcelManager::getParcel(int id) {
    return parcelRepo.findBy([&id](const ParcelPtr &parcel){return parcel->getId()==id;});
}

std::vector<ParcelPtr> ParcelManager::getAllParcels() {
    return parcelRepo.findAllBy([](ParcelPtr){return true;});
}

void ParcelManager::saveToFile(const std::string &path) const {
    parcelRepo.saveToFile(path);
}
