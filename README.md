 CAPSTONE-PROJECT
It's all about a bus system which includes operations such as adding, deleting, and modifying bus schedules, viewing available seats, booking seats, canceling bookings, and viewing booking history. The system stores data persistently in three separate files for buses, bookings, and employees.

< Files>

- main.c: Contains the main logic of the Bus Booking System.
- buses.dat: File to store bus data.
- bookings.dat: File to store booking data.
- employees.dat: File to store employee data.

< Structures>
Bus Structure;

- `int busID`: Unique identifier for each bus.
- `char source[50]`: Source location of the bus.
- `char destination[50]`: Destination location of the bus.
- `int totalSeats`: Total seats available on the bus.
- `int availableSeats`: Number of seats currently available on the bus.
- `float fare_per_seat`: Fare per seat for the bus.

 Booking Structure;
- `int bookingID`: Unique identifier for each booking.
- `int busID`: Identifier of the bus for which the booking is made.
- `int employeeID`: Identifier of the employee who made the booking.
- `char customerName[100]`: Name of the customer who made the booking.
- `int numSeats`: Number of seats booked.
- `float farePaid`: Total fare paid for the booking.

 Employee Structure;
- `int employeeID`: Unique identifier for each employee.
- `char username[50]`: Username for employee login.
- `char password[50]`: Password for employee login.

<Functions>
loadData();
- Loads data from files (`buses.dat`, `bookings.dat`, `employees.dat`) into program variables.

saveData();
- Saves program variables into files (`buses.dat`, `bookings.dat`, `employees.dat`).

registerUser();
- Allows users to register as employees by providing a username and password.

 login();
- Allows users (both employees and customers) to log in using a username and password.

authenticate();
- Handles the authentication process, allowing users to log in or register.

addBus();
- Adds a new bus schedule to the system.

deleteBus(int busID);
- Deletes a bus schedule based on the provided bus ID.

modifyBus(int busID);
- Modifies details of a bus schedule based on the provided bus ID.

displayBuses();
- Displays a list of all bus schedules.

searchBuses(char source[], char destination[]);
- Searches for bus schedules based on source and destination locations.

displayAvailableSeats(int busID);
- Displays the available seats for a specific bus.

 bookSeats(int busID, char customerName[], int numSeats);
- Allows customers to book seats on a specific bus.

 cancelBooking(int bookingID);
- Cancels a booking based on the provided booking ID.

viewBookingHistory();
- Displays the booking history, showing successful bookings made by the logged-in employee.

displayTitle(const char *title), displayMenuOption(const char *option), displayMessage(const char *message)
- Helper functions to display styled text.

 hasUppercase(const char *str), hasLowercase(const char *str), hasDigit(const char *str), hasSymbol(const char *str)
- Helper functions to check password complexity.

 displayMenu(), displayMenuOption();
- Displays the main menu and menu options for employees and customers.

saveDataAfterOperation();

- Saves data to files after each operation.

 issueTicket(int bookingID)

- Issues a ticket after a successful booking.

handleEmployeeActions(), handleCustomerActions()

- Main functions to handle employee and customer actions within the system.

Running the Program

1. Compile the code using a C compiler.
2. Run the compiled executable.
3. Follow the prompts to log in or register.
4. Interact with the system by choosing from the available options.

 

- The system differentiates between employees and customers based on their login.
- Data is stored persistently in files, allowing information to be retained between program executions.
-------------------------------------------------------
