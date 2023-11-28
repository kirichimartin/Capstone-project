Bus Reservation System by Martin Kirichi BSE-01-0287/2023
Overview
This C program implements a simple Bus Reservation System that allows employees to manage information about buses, make seat reservations, and view booking details. The system supports multiple users with different roles, such as manager, supervisor, and secretary, each with their unique login credentials.

Features
Employees Authentication: Employees must log in with valid credentials to access the system.
Bus Information Management: Allows adding, deleting, modifying, and viewing information about buses.
Booking Management: Enables users to view available seats on a bus, reserve a seat, and view booking details.
Program Structure
The program consists of several structures representing users, reservations, buses, and customers. Key functions include user authentication, menu display, bus information management, seat reservation, and file I/O for data persistence.

Usage
Login: Enter valid user credentials to access the system.
Menu: Choose an option from the main menu:
1.Bus Information Management:
  Add new bus
  Delete bus
  Modify bus
  View all buses
2.Booking Management:
  Display available seats
  Book a seat
Data Persistence: The program saves bus and booking information to files (data.txt and customer.txt) to ensure data persistence between program executions.

User Credentials
The program comes with predefined user credentials:
  Manager: ID - "manager", Password - "@manager20"
  Supervisor: ID - "supervisor", Password - "supervisor@23"
  Secretary: ID - "secretary", Password - "secretary19!"
  
File Structure
bus_reservation_system.c: The main source code file.
data.txt: File to store bus information.
customer.txt: File to store booking information.

How to Compile and Run
Compile the program using a C compiler.

Note
  The system has a maximum capacity of 10 buses and 50 seats per bus.
  Data is saved automatically before exiting the program.

  
