//
// Created by Filip Olczyk on 31/05/2026.
//

#include "repositories/LockerRepo.h"
#include "model/Locker.h"
#include "model/Parcel.h"
#include "Exceptions.h"

using json = nlohmann::json;

void LockerRepo::add(LockerPtr locker) {
    if (locker==nullptr) throw std::invalid_argument("Locker cannot be null");
    lockers.push_back(locker);
}

void LockerRepo::remove(LockerPtr locker) {
    if (locker==nullptr) throw std::invalid_argument("Locker cannot be null");
    std::erase(lockers, locker);
}

std::string LockerRepo::report() {
    std::string report = "";
    for (auto locker : lockers) {
        report += locker->getInfo() + "\n";
    }
    return report;
}

int LockerRepo::size() {
    return lockers.size();
}

LockerPtr LockerRepo::findBy(LockerPredicate predicate) {
    for (auto locker : lockers) {
        if (predicate(locker)) {
            return locker;
        }
    }
    return nullptr;
}

std::vector<LockerPtr> LockerRepo::findAllBy(LockerPredicate predicate) {
    std::vector<LockerPtr> result;
    for (auto locker : lockers) {
        if (predicate(locker)) {
            result.push_back(locker);
        }
    }
    return result;
}

void LockerRepo::saveToFile(const std::string &path) const {
    json jsonArray = json::array();
    for (auto locker : lockers) {
        if (locker != nullptr) {
            json jClient;
            jClient["id"] = locker->getId();
            jClient["location"] = locker->getLocation();
            jClient["lockerCount"] = locker->getLockerCount();
            std::vector<int> parcel_ids;
            for (const auto& parcel : locker->getCurrentParcels()) {
                parcel_ids.push_back(parcel->getId());
            }
            jClient["currentParcels"] = parcel_ids;
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
