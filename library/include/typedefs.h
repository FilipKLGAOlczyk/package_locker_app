//
// Created by Filip Olczyk on 26/05/2026.
//

#ifndef PROGRAM_TYPEDEFS_H
#define PROGRAM_TYPEDEFS_H
/**
 * @file typedefs.h
 * @brief Defines common type aliases, smart pointers, and functional predicates used throughout the application.
 *
 * This header centralizes the type definitions to ensure consistency across models,
 * repositories, and managers. It relies heavily on `std::shared_ptr` for safe memory
 * management and `std::function` for flexible, functional-style querying.
 */
#include <functional>
#include <memory>
#include <algorithm>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
// Forward declarations to avoid circular dependencies
class Client;
class Locker;
class Parcel;
/**
 * @typedef ClientPtr
 * @brief Type alias for a shared pointer to a Client object.
 * Facilitates safe, reference-counted memory management for clients.
 */
typedef std::shared_ptr<Client> ClientPtr;
/**
 * @typedef LockerPtr
 * @brief Type alias for a shared pointer to a Locker object.
 * Facilitates safe, reference-counted memory management for parcel lockers.
 */
typedef std::shared_ptr<Locker> LockerPtr;
/**
 * @typedef ParcelPtr
 * @brief Type alias for a shared pointer to a Parcel object.
 * Facilitates safe, reference-counted memory management for parcels.
 */
typedef std::shared_ptr<Parcel> ParcelPtr;
/**
 * @typedef ClientPredicate
 * @brief Type alias for a lambda or function evaluating a Client.
 * Takes a `ClientPtr` and returns a boolean. Used primarily in repositories
 * to filter or find specific clients based on dynamic conditions.
 */
typedef std::function<bool(ClientPtr)> ClientPredicate;
/**
 * @typedef LockerPredicate
 * @brief Type alias for a lambda or function evaluating a Locker.
 * Takes a `LockerPtr` and returns a boolean. Used primarily in repositories
 * to filter or find specific lockers based on dynamic conditions.
 */
typedef std::function<bool(LockerPtr)> LockerPredicate;
/**
 * @typedef ParcelPredicate
 * @brief Type alias for a lambda or function evaluating a Parcel.
 * Takes a `ParcelPtr` and returns a boolean. Used primarily in repositories
 * to filter or find specific parcels based on dynamic conditions.
 */
typedef std::function<bool(ParcelPtr)> ParcelPredicate;
#endif //PROGRAM_TYPEDEFS_H
