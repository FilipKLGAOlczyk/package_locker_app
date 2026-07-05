//
// Created by Filip Olczyk on 31/05/2026.
//

#include "repositories/ParcelRepo.h"

#include "Exceptions.h"
#include "model/Client.h"
#include "model/Locker.h"
#include "model/Parcel.h"
#include "model/parcels/Express.h"
#include "model/parcels/Insured.h"

using json = nlohmann::json;

void ParcelRepo::add(ParcelPtr parcel) {
    if (parcel != nullptr) {
        parcels.push_back(parcel);
    }
    else {
        throw std::invalid_argument("Parcel cannot be null");
    }
}

std::string ParcelRepo::report() {
    std::string report = "";
    for (auto parcel : parcels) {
        report += parcel->getInfo() + "\n";
    }
    return report;
}

int ParcelRepo::size() {
    return parcels.size();
}

ParcelPtr ParcelRepo::findBy(ParcelPredicate predicate) {
    for (auto parcel : parcels) {
        if (predicate(parcel)) {
            return parcel;
        }
    }
    return nullptr;
}

std::vector<ParcelPtr> ParcelRepo::findAllBy(ParcelPredicate predicate) {
    std::vector<ParcelPtr> result;
    for (auto parcel : parcels) {
        if (predicate(parcel)) {
            result.push_back(parcel);
        }
    }
    return result;
}

void ParcelRepo::saveToFile(const std::string &path) const {
    json jsonArray = json::array();
    for (auto parcel : parcels) {
        if (parcel != nullptr) {
            json jClient;
            jClient["id"] = parcel->getId();
            jClient["status"] = parcel->getStatusString();
            jClient["sender"] = parcel->getSender()->getId();
            jClient["recipient"] = parcel->getRecipient()->getId();
            jClient["origin"] = parcel->getOrigin()->getId();
            jClient["destination"] = parcel->getDestination()->getId();
            jClient["basePrice"] = parcel->getBasePrice();
            if (std::shared_ptr<Express> expressParcel = std::dynamic_pointer_cast<Express>(parcel)) {
                jClient["type"] = "Express";
                jClient["deadline"] = expressParcel->getDeadlineString();
            }
            else if (std::shared_ptr<Insured> insuredParcel = std::dynamic_pointer_cast<Insured>(parcel)) {
                jClient["type"] = "Insured";
                jClient["fragile"] = insuredParcel->isFragile();
                jClient["directional"] = insuredParcel->isDirectional();
                jClient["declaredValue"] = insuredParcel->getDeclaredValue();
            } else {
                jClient["type"] = "Standard";
            }
            jsonArray.push_back(jClient);
        }
    }
    std::ofstream file(path);
    if (file.is_open()) {
        file << jsonArray.dump(4);
        file.close();
    } else {
        throw Exceptions::FileWriteErrorException(std::format("Could not write to file {} while trying to save Clients to a file.", path));
    }

}