
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_BUS_SCHEDULES 100
#define MAX_EMPLOYEES 100
#define MAX_BOOKINGS 100
#define FILENAME_BUSES "buses.dat"
#define FILENAME_BOOKINGS "bookings.dat"
#define FILENAME_EMPLOYEES "employees.dat"


// Structure for Bus
typedef struct {
    int busID;
    char source[50];
    char destination[50];
    int totalSeats;
    int availableSeats;
    float fare_per_seat;
} Bus;

// Structure for Booking
typedef struct {
    int bookingID;
    int busID;
       int employeeID;  // New field to store the ID of the employee who made the booking
    char customerName[100];
    int numSeats;
    float farePaid;
} Booking;

// Structure for Employee
typedef struct {
    int employeeID;
    char username[50];
    char password[50];
} Employee;



// Global variables
int employeeCount = 0;
int busCount = 0;
int bookingCount = 0;
int lastEmployeeID = -1;  // New variable to store the ID of the last logged-in employee
int loggedInUserRole; // 0 for employee, 1 for customer
Bus buses[MAX_BUS_SCHEDULES];
Booking bookings[MAX_BOOKINGS];
Employee employees[MAX_EMPLOYEES];
// Forward declarations
void loadData();
void saveData();
void registerUser();
bool login();
bool authenticate();
void addBus();
void deleteBus(int busID);
void modifyBus(int busID);
void displayBuses();
void searchBuses(char source[], char destination[]);
void displayAvailableSeats(int busID);
void bookSeats(int busID, char customerName[], int numSeats);
void cancelBooking(int bookingID);
void viewBookingHistory();

// Function to display a styled title
void displayTitle(const char *title) {
    printf("\033[1;34m%s\033[0m\n", title);  // Bold and blue text
}

// Function to display a styled menu option
void displayMenuOption(const char *option) {
    printf("\033[1;33m%s\033[0m\n", option);  // Bold and yellow text
}

// Function to display a styled message
void displayMessage(const char *message) {
    printf("\033[1;32m%s\033[0m\n", message);  // Bold and green text
}

// Function to load data from files
void loadData() {
    FILE *file;

    // Load Bus data
    file = fopen(FILENAME_BUSES, "rb");
    if (file != NULL) {
        size_t read_size = fread(buses, sizeof(Bus), MAX_BUS_SCHEDULES, file);
        fclose(file);

        if (read_size == MAX_BUS_SCHEDULES) {
            busCount = MAX_BUS_SCHEDULES;
        } else {
            printf("Error reading bus data from file.\n");
        }
    }

    // Load Booking data
   file = fopen(FILENAME_BOOKINGS, "rb");
    if (file != NULL) {
        size_t read_size = fread(bookings, sizeof(Booking), MAX_BOOKINGS, file);
        fclose(file);

        if (read_size == MAX_BOOKINGS) {
            bookingCount = MAX_BOOKINGS;
        } else {
            printf("Error reading booking data from file.\n");
        }
    }

    // Load Employee data
     file = fopen(FILENAME_EMPLOYEES, "rb");
    if (file != NULL) {
        size_t read_size = fread(employees, sizeof(Employee), MAX_EMPLOYEES, file);
        fclose(file);

        if (read_size == MAX_EMPLOYEES) {
            employeeCount = MAX_EMPLOYEES;
              // Find the last employee ID
              int i;
    int maxEmployeeID = -1;
    for ( i = 0; i < employeeCount; ++i) {
        if (employees[i].employeeID > maxEmployeeID) {
            maxEmployeeID = employees[i].employeeID;
        }
    }
    lastEmployeeID = maxEmployeeID;
        } else {
            printf("Error reading employee data from file.\n");
        }
    }
}

// Function to save data to files
void saveData() {
    FILE *file;

    // Save Bus data
      file = fopen(FILENAME_BUSES, "wb");
    if (file != NULL) {
        size_t write_size = fwrite(buses, sizeof(Bus), MAX_BUS_SCHEDULES, file);
        fclose(file);

        if (write_size != MAX_BUS_SCHEDULES) {
            printf("Error writing bus data to file.\n");
        }
    }

    // Save Booking data
     file = fopen(FILENAME_BOOKINGS, "wb");
    if (file != NULL) {
        size_t write_size = fwrite(bookings, sizeof(Booking), MAX_BOOKINGS, file);
        fclose(file);

        if (write_size != MAX_BOOKINGS) {
            printf("Error writing booking data to file.\n");
        }
    }

    // Save Employee data
     file = fopen(FILENAME_EMPLOYEES, "wb");
    if (file != NULL) {
        size_t write_size = fwrite(employees, sizeof(Employee), MAX_EMPLOYEES, file);
        fclose(file);

        if (write_size != MAX_EMPLOYEES) {
            printf("Error writing employee data to file.\n");
        }
    }
}

// Function to check if a string has an uppercase letter
bool hasUppercase(const char *str) {
    while (*str) {
        if (isupper((unsigned char)(*str))) {
            return true;
        }
        str++;
    }
    return false;
}

// Function to check if a string has a lowercase letter
bool hasLowercase(const char *str) {
    while (*str) {
        if (islower((unsigned char)(*str))) {
            return true;
        }
        str++;
    }
    return false;
}

// Function to check if a string has a digit
bool hasDigit(const char *str) {
    while (*str) {
        if (isdigit((unsigned char)*str)) {
            return true;
        }
        str++;
    }
    return false;
}

// Function to check if a string has a symbol
bool hasSymbol(const char *str) {
    while (*str) {
        if (!isalnum((unsigned char)*str)) {
            return true;
        }
        str++;
    }
    return false;
}

// Function to handle user registration
void registerUser() {
    Employee newEmployee;

     
    printf("Enter a new username: ");
    newEmployee.employeeID = ++lastEmployeeID;

    scanf("%s", newEmployee.username);

    printf("Enter a new password: ");
    newEmployee.employeeID = ++lastEmployeeID;

    scanf("%s", newEmployee.password);

    // Check password complexity
    if (!hasUppercase(newEmployee.password) || !hasLowercase(newEmployee.password) ||
        !hasDigit(newEmployee.password) || !hasSymbol(newEmployee.password)) {
        printf("Password must contain at least one uppercase letter, one lowercase letter, one digit, and one symbol.\n");
        return;
    }

    employees[employeeCount] = newEmployee;
    employeeCount++;

    printf("Registration successful!\n");
}

// Function to handle user login
bool login() {
    char username[50];
    char password[50];

    
    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);
    
    int i;
    for (i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].username, username) == 0 && strcmp(employees[i].password, password) == 0)
		 lastEmployeeID = employees[i].employeeID;

		 {
            printf("Login successful!\n");
             lastEmployeeID = employees[i].employeeID;  // Set the ID of the last logged-in employee
            return true;
        }
    }

    printf("Invalid username or password. Please try again.\n");
    return false;
}

// Function to handle user authentication
bool authenticate() {
    int choice;

    while (1) {
    	displayTitle("***** SAM'S MOMBASA TRIP TRAVEL *****\n");
          displayMessage("Happy to see you! You're very welcomed. Feel free to interact with the system.");

         displayMenuOption("1. Login as Employee");
        displayMenuOption("2. Login as Customer");
        displayMenuOption("3. Register");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
      case 1:
                loggedInUserRole = 0; // Employee
                return login();
            case 2:
                loggedInUserRole = 1; // Customer
                return login();
            case 3:
                registerUser();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to display a styled menu
void displayMenu() {
    printf("\n\033[1;34mWelcome to the Bus Booking System\033[0m\n");  // Bold and blue text
    displayMenuOption("1. Add Bus Schedule");
    displayMenuOption("2. Delete Bus Schedule");
    displayMenuOption("3. Modify Bus Schedule");
    displayMenuOption("4. Display Bus Schedules");
    displayMenuOption("5. Search Bus Schedules");
    displayMenuOption("6. Display Available Seats");
    displayMenuOption("7. Book Seats");
    displayMenuOption("8. Cancel Booking");
    displayMenuOption("9. View Booking History");
    displayMenuOption("10. Exit");
}

// Function to save data to files after each operation
void saveDataAfterOperation() {
    saveData(); // Save buses, bookings, and employees to their respective files
}



// Function to add a new bus schedule
void addBus() {
    if (busCount < MAX_BUS_SCHEDULES) {
        Bus newBus;

        printf("Enter Bus ID: ");
        scanf("%d", &newBus.busID);
         printf("Enter Source: ");
        getchar(); // Consume the newline character left by the previous scanf
        fgets(newBus.source, sizeof(newBus.source), stdin);
        newBus.source[strcspn(newBus.source, "\n")] = '\0'; // Remove the newline character

        printf("Enter Destination: ");
        fgets(newBus.destination, sizeof(newBus.destination), stdin);
        newBus.destination[strcspn(newBus.destination, "\n")] = '\0'; // Remove the newline character

        printf("Enter Total Seats: ");
        scanf("%d", &newBus.totalSeats);

        printf("Enter Available Seats: ");
        scanf("%d", &newBus.availableSeats);

        printf("Enter Fare per Seat: ");
        scanf("%f", &newBus.fare_per_seat);

        buses[busCount] = newBus;
        busCount++;

        printf("Bus schedule added successfully!\n");
    // Save data after the operation
    saveDataAfterOperation();

     } else {
        printf("Bus schedule limit reached. Cannot add more buses.\n");
    }
}

// Function to delete a bus schedule
void deleteBus(int busID) {
    int i;
    for (i = 0; i < busCount; i++) {
        if (buses[i].busID == busID) {
            int j;
            for (j = i; j < busCount - 1; j++) {
                buses[j] = buses[j + 1];
            }
            busCount--;
            printf("Bus deleted successfully.\n");
            // Save data after the operation
    saveDataAfterOperation();

		    return;
        }
    }
    printf("Bus not found.\n");
}

// Function to modify a bus schedule
void modifyBus(int busID) {
    int i;
    for (i = 0; i < busCount; i++) {
        if (buses[i].busID == busID) {
            printf("Modify Bus ID: %d\n", buses[i].busID);
            printf("Enter New Source: ");
            scanf("%s", buses[i].source);
            printf("Enter New Destination: ");
            scanf("%s", buses[i].destination);
            printf("Enter New Total Seats: ");
            scanf("%d", &buses[i].totalSeats);
            printf("Enter New Available Seats: ");
            scanf("%d", &buses[i].availableSeats);
            printf("Enter New Fare per Seat: ");
            scanf("%f", &buses[i].fare_per_seat);
            printf("Bus schedule with Bus ID %d has been modified.\n", busID);
             // Save data after the operation
    saveDataAfterOperation();

			return;
        }
    }
    printf("Bus with Bus ID %d not found.\n", busID);
}

// Function to display all bus schedules
void displayBuses() {
    if (busCount > 0) {
        printf("List of Bus Schedules:\n");
        int i;
        for (i = 0; i < busCount; i++) {
            printf("Bus ID: %d\n", buses[i].busID);
            printf("Source: %s\n", buses[i].source);
            printf("Destination: %s\n", buses[i].destination);
            printf("Total Seats: %d\n", buses[i].totalSeats);
            printf("Available Seats: %d\n", buses[i].availableSeats);
            printf("Fare per Seat: %.2f\n", buses[i].fare_per_seat);
            printf("\n");
        }
    } else {
        printf("No bus schedules available.\n");
    }
}

// Function to search for bus schedules based on source and destination
void searchBuses(char source[], char destination[]) {
    int found = 0;
    printf("Search Results:\n");
    int i;
    for (i = 0; i < busCount; i++) {
        if (strcmp(buses[i].source, source) == 0 && strcmp(buses[i].destination, destination) == 0) {
            printf("Bus ID: %d\n", buses[i].busID);
            printf("Source: %s\n", buses[i].source);
            printf("Destination: %s\n", buses[i].destination);
            printf("Total Seats: %d\n", buses[i].totalSeats);
            printf("Available Seats: %d\n", buses[i].availableSeats);
            printf("Fare per Seat: %.2f\n", buses[i].fare_per_seat);
            printf("\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No matching bus schedules found for the given source and destination.\n");
    }
}

// Function to display available seats for a specific bus
void displayAvailableSeats(int busID) {
    int found = 0;
    int i;
    for (i = 0; i < busCount; i++) {
        if (buses[i].busID == busID) {
            printf("Available Seats on Bus ID %d: %d\n", busID, buses[i].availableSeats);
                  int totalSeats = buses[i].totalSeats;
            int availableSeats = buses[i].availableSeats;

            if (availableSeats > 0) {
            	int seatNumber;
                printf("  ");
                for ( seatNumber = 1; seatNumber <= totalSeats; seatNumber++) {
                    if (seatNumber <= availableSeats) {
                        printf("O ");  // O represents an available seat
                    } else {
                        printf("X ");  // X represents an occupied seat
                    }

                    // Print a newline after every 5 seats for better readability
                    if (seatNumber % 5 == 0) {
                        printf("\n  ");
                    }
                }
                printf("\n");
            } else {
                printf("No available seats on Bus ID %d.\n", busID);
            }
			found = 1;
            break;
        }
    }
    if (!found) {
        printf("Bus with Bus ID %d not found.\n", busID);
    }
}

// Function to view the booking history
void viewBookingHistory() {
    if (bookingCount > 0) {
        printf("\n***** Booking History *****\n");
        int i;
        for (i = 0; i < bookingCount; i++) {
        	   if (bookings[i].farePaid > 0 && bookings[i].employeeID == lastEmployeeID) {
            printf("Booking ID: %d\n", bookings[i].bookingID);
            printf("Bus ID: %d\n", bookings[i].busID);
             printf("Source: %s\n", buses[bookings[i].busID].source);
                printf("Destination: %s\n", buses[bookings[i].busID].destination);
		    printf("Customer Name: %s\n", bookings[i].customerName);
            printf("Number of Seats: %d\n", bookings[i].numSeats);
            printf("Fare Paid: %.2f\n", bookings[i].farePaid);
            printf("*************************\n");
        // Save data after the operation
    saveDataAfterOperation();

	     }
		}
    } else {
        printf("No successful booking history available.\n");
    }
}

// Function to issue a ticket after a successful booking
void issueTicket(int bookingID) {
    int i;
    for (i = 0; i < bookingCount; i++) {
        if (bookings[i].bookingID == bookingID) {
            printf("\n***** Ticket Details *****\n");
            printf("Booking ID: %d\n", bookings[i].bookingID);
		    printf("Bus ID: %d\n", bookings[i].busID);
            printf("Source: %s\n", buses[bookings[i].busID].source);
            printf("Destination: %s\n", buses[bookings[i].busID].destination);
		    printf("Customer Name: %s\n", bookings[i].customerName);
            printf("Number of Seats: %d\n", bookings[i].numSeats);
            printf("Fare Paid: %.2f\n", bookings[i].farePaid);
            printf("*************************\n");
            // Save data after the operation
    saveDataAfterOperation();

		    return;
        }
    }
    printf("Booking with Booking ID %d not found.\n", bookingID);
}

// Function to book seats on a bus
void bookSeats(int busID, char customerName[], int numSeats) {
    int busIndex = -1;
    int i;
    for (i = 0; i < busCount; i++) {
        if (buses[i].busID == busID) {
            busIndex = i;
            break;
        }
    }
    if (busIndex != -1) {
        Bus *bus = &buses[busIndex];
        if (bus->availableSeats >= numSeats) {
            bus->availableSeats -= numSeats;
            float fare = numSeats * bus->fare_per_seat;
            Booking newBooking;
            newBooking.bookingID = bookingCount + 1;
            newBooking.busID = busID;
             newBooking.employeeID = lastEmployeeID;  // Set the ID of the employee who made the booking
            strcpy(newBooking.customerName, customerName);
            newBooking.numSeats = numSeats;
            newBooking.farePaid = fare;
            bookings[bookingCount] = newBooking;
            bookingCount++;
            printf("Booking successful! Booking ID: %d, Total Fare: %.2f\n", newBooking.bookingID, fare);
            // Save data after the operation
    saveDataAfterOperation();

		    // Issue ticket after successful booking
            issueTicket(newBooking.bookingID);
	 // Save data after the operation
    saveDataAfterOperation();

			} else {
            printf("Not enough available seats on Bus ID %d.\n", busID);
        }
    } else {
        printf("Bus with Bus ID %d not found.\n", busID);
    }
}

// Function to cancel a booking
void cancelBooking(int bookingID) {
    int bookingIndex = -1;
    int i;
    for (i = 0; i < bookingCount; i++) {
        if (bookings[i].bookingID == bookingID) {
            bookingIndex = i;
            break;
        }
    }
    if (bookingIndex != -1) {
        Booking booking = bookings[bookingIndex];
        int j;
        for (j = bookingIndex; j < bookingCount - 1; j++) {
            bookings[j] = bookings[j + 1];
        }
        bookingCount--;
        for (i = 0; i < busCount; i++) {
            if (buses[i].busID == booking.busID) {
                buses[i].availableSeats += booking.numSeats;
                break;
            }
        }
        printf("Booking with Booking ID %d has been canceled.\n", bookingID);
    } else {
        printf("Booking with Booking ID %d not found.\n", bookingID);
    }
}

// Function to modify the permanent bus schedule
void modifyPermanentBusSchedule() {
    printf("Modifying Permanent Bus Schedule:\n");
    printf("Enter New Source: ");
    getchar(); // Consume the newline character left by the previous scanf
    fgets(buses[0].source, sizeof(buses[0].source), stdin);
    buses[0].source[strcspn(buses[0].source, "\n")] = '\0'; // Remove the newline character

    printf("Enter New Destination: ");
    fgets(buses[0].destination, sizeof(buses[0].destination), stdin);
    buses[0].destination[strcspn(buses[0].destination, "\n")] = '\0'; // Remove the newline character

    printf("Permanent Bus Schedule modified successfully!\n");
}

// Function to display the employee menu
void displayEmployeeMenu() {
    printf("\n\033[1;34mEmployee Menu\033[0m\n");  // Bold and blue text
    displayMenuOption("1. Add Bus Schedule");
    displayMenuOption("2. Delete Bus Schedule");
    displayMenuOption("3. Modify Bus Schedule");
    displayMenuOption("4. Display Bus Schedules");
    displayMenuOption("5. Search Bus Schedules");
    displayMenuOption("6. Display Available Seats");
    displayMenuOption("7. Cancel Booking");
    displayMenuOption("8. View Booking History");
    displayMenuOption("9. Logout");
}
// Function to handle employee actions
void handleEmployeeActions() {
    int choice;
    int busID;
    char source[50];
    char destination[50];
    int bookingID;

    while (1) {
        displayEmployeeMenu();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBus();
                break;
            case 2:
                printf("Enter Bus ID to delete: ");
                scanf("%d", &busID);
                deleteBus(busID);
                break;
            case 3:
                printf("Enter Bus ID to modify: ");
                scanf("%d", &busID);
                modifyBus(busID);
                break;
            case 4:
                displayBuses();
                break;
            case 5:
                printf("Enter Source: ");
                scanf("%s", source);
                printf("Enter Destination: ");
                scanf("%s", destination);
                searchBuses(source, destination);
                break;
            case 6:
                printf("Enter Bus ID: ");
                scanf("%d", &busID);
                displayAvailableSeats(busID);
                break;
            case 7:
                printf("Enter Booking ID to cancel: ");
                scanf("%d", &bookingID);
                cancelBooking(bookingID);
                break;
            case 8:
                viewBookingHistory();
                break;
            case 9:
                // Save data to files before logging out
                saveData();
                  saveDataAfterOperation();
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
// Function to display the customer menu
void displayCustomerMenu() {
    printf("\n\033[1;34mCustomer Menu\033[0m\n");  // Bold and blue text
    displayMenuOption("1. View Bus Schedules");
    displayMenuOption("2. Display Available Seats");
    displayMenuOption("3. Book Seats");
    displayMenuOption("4. Cancel Booking");
    displayMenuOption("5. View Booking History");
    displayMenuOption("6. Logout");
}

// Function to handle customer actions
void handleCustomerActions() {
    int choice;
    int busID;
    char customerName[100];
    int numSeats;
    int bookingID;

    while (1) {
        displayCustomerMenu();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayBuses();
                break;
            case 2:
                printf("Enter Bus ID: ");
                scanf("%d", &busID);
                displayAvailableSeats(busID);
                break;
            case 3:
                printf("Enter Bus ID: ");
                scanf("%d", &busID);
                printf("Enter Customer Name: ");
                scanf("%s", customerName);
                printf("Enter Number of Seats to Book: ");
                scanf("%d", &numSeats);
                bookSeats(busID, customerName, numSeats);
                break;
            case 4:
                printf("Enter Booking ID to cancel: ");
                scanf("%d", &bookingID);
                cancelBooking(bookingID);
                break;
            case 5:
                viewBookingHistory();
                break;
            case 6:
                // Save data to files before logging out
                saveData();
                  saveDataAfterOperation();
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}



int main() {
	// Load data from files
    loadData();
    
    // Login before accessing the system
      if (!authenticate()) {
        printf("Authentication failed. Exiting the program.\n");
        return 1; // Exit with an error code
    }
    
  // Initialize permanent bus schedule
    Bus permanentBusSchedule = {1, "Nairobi", "Mombasa", 50, 20, 7800};
    buses[0] = permanentBusSchedule;
    busCount = 1;

   // Check if the logged-in user is an employee or customer
    if (loggedInUserRole == 0) {
        // Employee is logged in
        handleEmployeeActions();
    } else {
        // Customer is logged in
        handleCustomerActions();
    }
    // Save data before exiting the program
    saveDataAfterOperation();

    return 0;
}