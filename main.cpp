#include "include/manager.h"
#include <iostream>
#include <limits>

void printMenu() {
    std::cout << "\n--- Score Management System ---" << std::endl;
    std::cout << "1. Add Participant" << std::endl;
    std::cout << "2. Delete Participant" << std::endl;
    std::cout << "3. Update Participant" << std::endl;
    std::cout << "4. Find Participant" << std::endl;
    std::cout << "5. List All Participants" << std::endl;
    std::cout << "6. Clear All Participants" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    ScoreManager manager;
    int choice;

    do {
        printMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        int id;
        std::string name;
        double score;

        switch (choice) {
            case 1:
                std::cout << "Enter ID, Name (use_for_spaces), Score: ";
                std::cin >> id >> name >> score;
                manager.addParticipant(id, name, score);
                break;
            case 2:
                std::cout << "Enter ID to delete: ";
                std::cin >> id;
                manager.deleteParticipant(id);
                break;
            case 3:
                std::cout << "Enter ID to update, new Name (use_for_spaces), new Score: ";
                std::cin >> id >> name >> score;
                manager.updateParticipant(id, name, score);
                break;
            case 4: {
                int findChoice;
                std::cout << "Find by: 1. ID, 2. Name: ";
                std::cin >> findChoice;
                if (findChoice == 1) {
                    std::cout << "Enter ID to find: ";
                    std::cin >> id;
                    manager.findParticipantById(id);
                } else if (findChoice == 2) {
                    std::cout << "Enter Name to find (use_for_spaces): ";
                    std::cin >> name;
                    manager.findParticipantByName(name);
                } else {
                    std::cout << "Invalid choice." << std::endl;
                }
                break;
            }
            case 5:
                manager.listAllParticipants();
                break;
            case 6:
                manager.clear();
                std::cout << "All participants cleared." << std::endl;
                break;
            case 0:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 0);

    return 0;
}
