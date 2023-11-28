#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 50

// User structure to store credentials
struct User {
    char id[20];
    char password[15];
};

// Reservation structure to represent a seat reservation
struct Reservation {
    int seat_number;
    char passenger_name[20];
    int is_reserved;
};

// Bus structure to store information about a bus
struct Bus {
    int busNumber;
    char busName[15];
    char source[20];
    char destination[20];
    char departure_time[10];
    char arrival_time[10];
    float price;
    struct Reservation seats[MAX_SEATS];
};

// Database of users
struct User database[] = {
    {"manager", "@manager20"},
    {"supervisor", "supervisor@23"},
    {"secretary", "secretary19!"}
};

int totalBuses = 0;
struct Bus buses[10];

// Function prototypes
int searchUser(const struct User* database, int size, const char* enteredId, const char* enteredPassword);
int displayMenu();
void initializeBus(struct Bus* bus);
void displayBus(const struct Bus* bus);
void reserveSeat(struct Bus* bus);
void busInformationManagement();

void addBus();
void deleteBus(int busNumber);
void modifyBus(int busNumber);
void viewBuses();
void saveDataToFile();
void readDataFromFile();

int main() {
    readDataFromFile();

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

        // Display available buses immediately after login
        viewBuses();

        int userChoice = displayMenu();
        switch (userChoice) {
            case 1:
                printf("You chose Bus Information Management.\n");
                busInformationManagement(); // Call the Bus Information Management function
                break;
            case 2:
                printf("You chose Booking Management.\n");
                // ... (unchanged part of the code)
                break;
            default:
                printf("Invalid choice.\n");
        }
    } else {
        printf("Login failed. Invalid ID or password.\n");
    }

    saveDataToFile(); // Save the data to file before exiting

    return 0;
}

// Function to search for a user's credentials in the database
int searchUser(const struct User* database, int size, const char* enteredId, const char* enteredPassword) {
    int i;
    for (i = 0; i < size; i++) {
        if (strcmp(database[i].id, enteredId) == 0 && strcmp(database[i].password, enteredPassword) == 0) {
            return 1; // Login successful
        }
    }
    return 0; // Login failed
}

// Function to display the main menu and get user's choice
int displayMenu() {
    int choice;
    printf("Choose an option:\n");
    printf("1. Bus Information Management\n");
    printf("2. Booking Management\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

// Function to initialize bus reservations
void initializeBus(struct Bus* bus) {
    int i;
    for (i = 0; i < MAX_SEATS; i++) {
        bus->seats[i].seat_number = i + 1;
        bus->seats[i].is_reserved = 0;
        strcpy(bus->seats[i].passenger_name, "Available");
    }
}

// Function to display information about bus seats
void displayBus(const struct Bus* bus) {
    printf("Seat Number\tPassenger Name\n");
    int i;
    for (i = 0; i < MAX_SEATS; i++) {
        printf("%d\t\t%s\n", bus->seats[i].seat_number, bus->seats[i].passenger_name);
    }
}

// Function to reserve a seat on a bus
void reserveSeat(struct Bus* bus) {
    int seat;
    printf("Enter the seat number you want to reserve: ");
    scanf("%d", &seat);

    if (seat < 1 || seat > MAX_SEATS) {
        printf("Invalid seat number. Please choose a seat between 1 and %d.\n", MAX_SEATS);
        return;
    }

    if (bus->seats[seat - 1].is_reserved) {
        printf("Seat %d is already reserved.\n", seat);
    } else {
        printf("Enter passenger name: ");
        scanf("%s", bus->seats[seat - 1].passenger_name);
        bus->seats[seat - 1].is_reserved = 1;
        printf("Seat %d reserved for %s.\n", seat, bus->seats[seat - 1].passenger_name);
    }
}

// Function to manage bus information
void busInformationManagement() {
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
            case 1:
                addBus();
                break;
            case 2: {
                int busNumber;
                printf("Enter bus number to delete: ");
                scanf("%d", &busNumber);
                deleteBus(busNumber);
                break;
            }
            case 3: {
                int modifyBusNumber;
                printf("Enter bus number to modify: ");
                scanf("%d", &modifyBusNumber);
                modifyBus(modifyBusNumber);
                break;
            }
            case 4:
                viewBuses();
                break;
            case 0:
                printf("Exit\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (busChoice != 0);
}

// Function to add a new bus
void addBus() {
    if (totalBuses < 10) {
        printf("Enter bus number: ");
        scanf("%d", &buses[totalBuses].busNumber);
        printf("Enter bus name: ");
        scanf("%s", buses[totalBuses].busName);
        printf("Enter source: ");
        scanf("%s", buses[totalBuses].source);
        printf("Enter destination: ");
        scanf("%s", buses[totalBuses].destination);
        printf("Enter departure time: ");
        scanf("%s", buses[totalBuses].departure_time);
        printf("Enter arrival time: ");
        scanf("%s", buses[totalBuses].arrival_time);
        printf("Enter price: ");
        scanf("%f", &buses[totalBuses].price);

        initializeBus(&buses[totalBuses]);

        totalBuses++;

        printf("Bus added successfully!\n");
    } else {
        printf("Maximum number of buses reached!\n");
    }
}

// Function to delete a bus
void deleteBus(int busNumber) {
    int i, found = 0;

    for (i = 0; i < totalBuses; i++) {
        if (buses[i].busNumber == busNumber) {
            found = 1;
            break;
        }
    }

    if (found) {
        // Delete logic (similar to your original code)
        printf("Bus deleted successfully!\n");
    } else {
        printf("Bus not found!\n");
    }
}

// Function to modify bus information
void modifyBus(int busNumber) {
    int i, found = 0;

    for (i = 0; i < totalBuses; i++) {
        if (buses[i].busNumber == busNumber) {
            found = 1;
            break;
        }
    }

    if (found) {
        // Modify logic (similar to your original code)
        printf("Bus modified successfully!\n");
    } else {
        printf("Bus not found!\n");
    }
}

// Function to view all available buses
void viewBuses() {
    if (totalBuses == 0) {
        printf("No buses available!\n");
    } else {
        printf("Bus Number\tBus Name\tSource\t\tDestination\tDeparture Time\tArrival Time\tPrice\n");
        int i;
        for (i = 0; i < totalBuses; i++) {
            printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%.2f\n", buses[i].busNumber, buses[i].busName,
                   buses[i].source, buses[i].destination, buses[i].departure_time, buses[i].arrival_time,
                   buses[i].price);
        }
    }
}

// Function to save data to a file
void saveDataToFile() {
    FILE* file = fopen("data.txt", "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d\n", totalBuses);
    int i;
    for (i = 0; i < totalBuses; ++i) {
        fprintf(file, "%d %s %s %s %s %s %f\n", buses[i].busNumber, buses[i].busName, buses[i].source,
                buses[i].destination, buses[i].departure_time, buses[i].arrival_time, buses[i].price);
    }

    fclose(file);
}

// Function to read data from a file
void readDataFromFile() {
    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    fscanf(file, "%d", &totalBuses);
    int i;
    for (i = 0; i < totalBuses; ++i) {
        fscanf(file, "%d %s %s %s %s %s %f", &buses[i].busNumber, buses[i].busName, buses[i].source,
               buses[i].destination, buses[i].departure_time, buses[i].arrival_time, &buses[i].price);
        initializeBus(&buses[i]);
    }

    fclose(file);
}
