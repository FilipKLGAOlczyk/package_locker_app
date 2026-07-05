#include<typedefs.h>
#include <iostream>

#include "managers/ClientManager.h"
#include "managers/LockerManager.h"
#include "managers/ParcelManager.h"
#include "model/Client.h"
#include "model/Locker.h"
#include "model/parcels/Insured.h"
#include "model/parcels/Standard.h"

void printMenu() {
    std::cout << "--------------------\n";
    std::cout << "        Menu\n";
    std::cout << "--------------------\n";
    std::cout << "[0] Menu\n";
    std::cout << "\n";
    std::cout << "[1] Lista klientow\n";
    std::cout << "[2] Zarejestruj klienta\n";
    std::cout << "\n";
    std::cout << "[3] Lista paczkomatow\n";
    std::cout << "[4] Zarejestruj paczkomat\n";
    std::cout << "\n";
    std::cout << "[5] Lista przesylek\n";
    std::cout << "[6] Zarejestruj przesylke\n";
    std::cout << "[7] Pelne informacje o przesylce\n";
    std::cout << "\n";
    std::cout << "[w] Zapisz dane (json)\n";
    std::cout << "[q] Wyjdz (bez zapisywania danych)\n";
}

int main() {
    ClientManager clientManager;
    LockerManager lockerManager;
    ParcelManager parcelManager;



    char choice;
    bool running = true;

    printMenu();

    while (running) {

        std::cout << ": ";
        std::cin >> choice;

        switch (choice) {

            case '0': {
                printMenu();
                break;
            }

            case '1': {
                for (const auto& client : clientManager.getAllClients()) {
                    std::cout << client->getInfo() << std::endl;
                }
                break;
            }

            case '2': {
                int id;
                std::string firstName, lastName, email;

                std::cout << "Rejestrowanie klienta:\n";
                std::cout << " Identyfikator: ";
                std::cin >> id;
                std::cout << " Imie: ";
                std::cin >> firstName;
                std::cout << " Nazwisko: ";
                std::cin >> lastName;
                std::cout << " Adres e-mail: ";
                std::cin >> email;

                if (clientManager.registerClient(id, firstName, lastName, email)) {
                    std::cout << std::format("Pomyslnie zarejestrowano klienta: {}\n",clientManager.getClient(id)->getInfo());
                } else {
                    std::cout << std::format("Nie udalo sie zarejestrowac klienta.\n");
                }

                break;
            }

            case '3': {
                for (const auto& locker : lockerManager.getAllLockers()) {
                    std::cout << locker->getInfo() << std::endl;
                }
                break;
            }

            case '4': {
                int id, lockerCount;
                std::string location;

                std::cout << "Rejestrowanie paczkomatu:\n";
                std::cout << " Identyfikator: ";
                std::cin >> id;
                std::cout << " Lokalizacja: ";
                std::cin >> location;
                std::cout << " Ilosc skrytek: ";
                std::cin >> lockerCount;

                if (lockerManager.registerLocker(id, location, lockerCount)) {
                    std::cout << std::format("Pomyslnie zarejestrowano paczkomat: {}\n",lockerManager.getLocker(id)->getInfo());
                } else {
                    std::cout << std::format("Nie udalo sie zarejestrowac paczkomatu.\n");
                }

                break;
            }

            case '5': {
                for (const auto& parcel : parcelManager.getAllParcels()) {
                    std::cout << parcel->getInfo() << std::endl;
                }
                break;
            }

            case '6': {
                unsigned int id, originId, destinationId;
                double basePrice;
                std::string senderEmail, recipientEmail;
                char parcelType;
                bool success;

                std::cout << "Rejestrowanie przesylki:\n";
                std::cout << " Identyfikator paczki: ";
                std::cin >> id;

                std::cout << " Adres e-mail nadawcy: ";
                std::cin >> senderEmail;
                auto sender = clientManager.getClient(senderEmail);
                if (sender == nullptr) {
                    std::cout << "Nie znaleziono klienta o takim adresie e-mail. Przerywam rejestrowanie paczki.\n";
                    break;
                }

                std::cout << " Adres e-mail odbiorcy: ";
                std::cin >> recipientEmail;
                auto recipient = clientManager.getClient(recipientEmail);
                if (recipient == nullptr) {
                    std::cout << "Nie znaleziono klienta o takim adresie e-mail. Przerywam rejestrowanie paczki.\n";
                    break;
                }

                std::cout << " Identyfikator paczkomatu nadawcy: ";
                std::cin >> originId;
                auto origin = lockerManager.getLocker(originId);
                if (origin == nullptr) {
                    std::cout << "Nie znaleziono paczkomatu o takim identyfikatorze. Przerywam rejestrowanie paczki.\n";
                    break;
                }

                std::cout << " Identyfikator paczkomatu odbiorcy: ";
                std::cin >> destinationId;
                auto destination = lockerManager.getLocker(destinationId);
                if (destination == nullptr) {
                    std::cout << "Nie znaleziono paczkomatu o takim identyfikatorze. Przerywam rejestrowanie paczki.\n";
                    break;
                }

                std::cout << " Cena bazowa: ";
                std::cin >> basePrice;

                std::cout << " Dostepne typy paczek:\n";
                std::cout << " [s] Standardowa\n";
                std::cout << " [i] Ubezpieczona\n";
                std::cout << " [e] Ekspresowa\n";
                std::cout << " Podaj typ paczki: ";
                std::cin >> parcelType;

                switch (parcelType) {
                    case 's':
                        success = parcelManager.registerParcel<Standard>(id, sender, recipient, origin, destination, basePrice);
                        break;
                    case 'i':
                        bool fragile, directional;
                        double declaredValue;

                        std::cout << " Przesyłka delikatna [0/1]: ";
                        std::cin >> fragile;
                        std::cout << " Przesyłka kierunkowa [0/1]: ";
                        std::cin >> directional;
                        std::cout << " Wartosc paczki: ";
                        std::cin >> declaredValue;

                        success = parcelManager.registerParcel<Insured>(id, sender, recipient, origin, destination, basePrice, fragile, directional, declaredValue);
                        break;
                    case 'e':
                        char deadlineChar;
                        ExpressParcelDeadline deadline;

                        std::cout << " Terminy do wyboru:\n";
                        std::cout << " [1] Tego samego dnia\n";
                        std::cout << " [2] Nastepnego dnia\n";
                        std::cout << " [3] Przesylka weekendowa\n";
                        std::cout << " Wybierz termin: ";
                        std::cin >> deadlineChar;

                        switch (deadlineChar) {
                            case '1':
                                deadline = ExpressParcelDeadline::sameDay;
                                break;
                            case '2':
                                deadline = ExpressParcelDeadline::nextDay;
                                break;
                            case '3':
                                deadline = ExpressParcelDeadline::weekendDelivery;
                                break;
                        }

                        success = parcelManager.registerParcel<Express>(id, sender, recipient, origin, destination, basePrice, deadline);
                        break;
                }
                if (success) {
                    std::cout << std::format("Pomyslnie zarejestrowano przesylke: {}\n", parcelManager.getParcel(id)->getInfo());
                } else {
                    std::cout << "Nie udalo sie zarejestrowac przesylki.\n";
                }
                break;
            }

            case '7': {
                unsigned int id;
                std::cout << " Podaj identyfikator przesylki: ";
                std::cin >> id;

                auto parcel = parcelManager.getParcel(id);
                if (parcel == nullptr) {
                    std::cout << std::format("Nie znaleziono paczki o identyfikatorze {}\n", id);
                    break;
                }

                std::cout << parcel->getFullInfo();
                break;
            }

            case 'w': {
                std::string pathString;
                std::cout << "Podaj sciezke folderu do zapisania danych: ";
                std::cin >> pathString;

                std::filesystem::path path(pathString);

                try {
                    clientManager.saveToFile(path / "clients.json");
                    lockerManager.saveToFile(path / "lockers.json");
                    parcelManager.saveToFile(path / "parcels.json");
                } catch (std::exception& e) {
                    std::cout << std::format("Zapisywanie danych nie powiodlo sie.\n{}\n", e.what());
                    break;
                }
                std::cout << std::format("Pomyslnie zapisano dane: {}\n", pathString);
                break;
            }

            case 'q': {
                running = false;
                break;
            }

            default: break;

        }

    }

    return 0;
}