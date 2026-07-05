//
// Created by Filip Olczyk on 06/06/2026.
//

#include "managers/LockerManager.h"

#include "model/Locker.h"

bool LockerManager::registerLocker(unsigned int id, std::string location, int lockerCount) {
    LockerPtr existingLocker = getLocker(id);
    if (existingLocker) {
        return false;
    }
    LockerPtr newLocker = std::make_shared<Locker>(id, location,lockerCount);
    lockerRepo.add(newLocker);
    return true;
}

LockerPtr LockerManager::getLocker(unsigned int id) {
    return lockerRepo.findBy([&id](const LockerPtr &locker){return locker->getId()==id;});
}

std::vector<LockerPtr> LockerManager::getAllLockers() {
    return lockerRepo.findAllBy([](LockerPtr){return true;});
}

void LockerManager::saveToFile(const std::string &path) const {
    lockerRepo.saveToFile(path);
}

