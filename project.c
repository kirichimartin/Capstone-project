#include <stdio.h>
#include <string.h>

// Structure to represent a user's credentials (ID and password).
struct User {
    char id[50];
    char password[50];
};

// Function to search for a user's credentials in the database.
int searchUser(const struct User* database, int size, const char* enteredId, const char* enteredPassword) {
    int i;
	for (i = 0; i < size; i++) {
        if (strcmp(database[i].id, enteredId) == 0 && strcmp(database[i].password, enteredPassword) == 0) {
            return 1; // Match found
        }
    }
    return 0; // No match found
}

// Function to display a menu and get user's choice.
int displayMenu() {
    int choice;
    printf("Choose an option:\n");
    printf("1. Bus Information Management\n");
    printf("2. Booking Management\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    return choice;
}

// Initialize the bus reservations
#define MAX_SEATS 50

struct Reservation {
    int seat_number;
    char passenger_name[50];
    int is_reserved;
};

struct Reservation bus[MAX_SEATS];

void initializeBus() {
    int i;
	for (i = 0; i < MAX_SEATS; i++) {
        bus[i].seat_number = i + 1;
        bus[i].is_reserved = 0;
        strcpy(bus[i].passenger_name, "Available");
    }
}

void displayBus() {
    printf("Seat Number\tPassenger Name\n");
    int i;
    for (i = 0; i < MAX_SEATS; i++) {
        printf("%d\t\t%s\n", bus[i].seat_number, bus[i].passenger_name);
    }
}

void reserveSeat() {
    int seat;
    printf("Enter the seat number you want to reserve: ");
    scanf("%d", &seat);

    if (seat < 1 || seat > MAX_SEATS) {
        printf("Invalid seat number. Please choose a seat between 1 and %d.\n", MAX_SEATS);
        return;
    }

    if (bus[seat - 1].is_reserved) {
        printf("Seat %d is already reserved.\n", seat);
    } else {
        printf("Enter passenger name: ");
        scanf("%s", bus[seat - 1].passenger_name);
        bus[seat - 1].is_reserved = 1;
        printf("Seat %d reserved for %s.\n", seat, bus[seat - 1].passenger_name);
    }
}

void busInformationManagement() {
    struct Bus {
        int busNumber;
        char busName[50];
        char source[50];
        char destination[50];
        float price;
    };

    struct Bus buses[10];
    int count = 0;

    void addBus() {
        printf("Enter bus number: ");
        scanf("%d", &buses[count].busNumber);
        printf("Enter bus name: ");
        scanf("%s", buses[count].busName);
        printf("Enter source: ");
        scanf("%s", buses[count].source);
        printf("Enter destination: ");
        scanf("%s", buses[count].destination);
        printf("Enter price: ");
        scanf("%f", &buses[count].price);

        count++;

        printf("Bus added successfully!\n");
    }

    void deleteBus(int busNumber) {
        int i, found = 0;

        for (i = 0; i < count; i++) {
            if (buses[i].busNumber == busNumber) {
                found = 1;
                break;
            }
        }

        if (found) {
            int j;
            for (j = i; j < count - 1; j++) {
                buses[j] = buses[j + 1];
            }

            count--;

            printf("Bus deleted successfully!\n");
        } else {
            printf("Bus not found!\n");
        }
    }

    void modifyBus(int busNumber) {
        int i, found = 0;

        for (i = 0; i < count; i++) {
            if (buses[i].busNumber == busNumber) {
                found = 1;
                break;
            }
        }

        if (found) {
            printf("Enter new bus name: ");
            scanf("%s", buses[i].busName);
            printf("Enter new source: ");
            scanf("%s", buses[i].source);
            printf("Enter new destination: ");
            scanf("%s", buses[i].destination);
            printf("Enter new price: ");
            scanf("%f", &buses[i].price);

            printf("Bus modified successfully!\n");
        } else {
            printf("Bus not found!\n");
        }
    }

    void viewBuses() {
        if (count == 0) {
            printf("No buses available!\n");
        } else {
            printf("Bus Number\tBus Name\tSource\t\tDestination\tPrice\n");
            int i;
			for (i = 0; i < count; i++) {
                printf("%d\t\t%s\t\t%s\t\t%s\t\t%.2f\n", buses[i].busNumber, buses[i].busName, buses[i].source, buses[i].destination, buses[i].price);
            }
        }
    }

    int busChoice;

    do {
        printf("1. Add new bus\n");
        printf("2. Delete bus\n");
        printf("3. Modify bus\n");
        printf("4. View all buses\n");
        printf("0. Exit Bus Information Management\n");
        printf("Enter your choice: ");
        scanf("%d", &busChoice);

        switch (busChoice) {
        	 int busNumber;
        	  int modifyBusNumber;
        	  
            case 1:
                addBus();
                break;
            case 2:
                printf("Enter bus number to delete: ");
                scanf("%d", &busNumber);
                deleteBus(busNumber);
                break;
            case 3:
               
                printf("Enter bus number to modify: ");
                scanf("%d", &modifyBusNumber);
                modifyBus(modifyBusNumber);
                break;
            case 4:
                viewBuses();
                break;
            case 0:
                printf("Exiting Bus Information Management...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (busChoice != 0);
}

int main() {
    // Create a small database with user credentials.
    struct User database[] = {
        {"user1", "password1"},
        {"user2", "password2"},
        {"user3", "password3"}
    };
    int databaseSize = sizeof(database) / sizeof(database[0]);

    char enteredId[50];
    char enteredPassword[50];

    printf("Welcome to Kirichi corp\n\n");
    printf("Enter your ID: ");
    scanf("%s", enteredId);
    printf("Enter your password: ");
    scanf("%s", enteredPassword);

    if (searchUser(database, databaseSize, enteredId, enteredPassword)) {
        printf("####### Login successful. Welcome, %s ####### !\n\n", enteredId);

        int userChoice = displayMenu();
        switch (userChoice) {
            case 1:
                printf("You chose Bus Information Management.\n");
                busInformationManagement(); // Call the Bus Information Management function
                break;
            case 2:
                printf("You chose Booking Management.\n");
                initializeBus();

                int choice;
             

                do {
                    printf("\nWelcome to the Bus Reservation System Menu:\n\n");
                    printf("1. Display Available Seats\n");
                    printf("2. Reserve a Seat\n");
                    printf("3. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            displayBus();
                            break;
                        case 2:
                            reserveSeat();
                            break;
                        case 3:
                            printf("Thank you for using the Bus Reservation System.\n");
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                            break;
                    }
                } while (choice != 3);
                break;
            default:
                printf("Invalid choice.\n");
        }
    } else {
        printf("Login failed. Invalid ID or password.\n");
    }

    return 0;
}
