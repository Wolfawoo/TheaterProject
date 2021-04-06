// CSC114-4C2
// Group Project
// Justin Weaver

#include <iostream>
#include <iomanip>
using namespace std;

/*void storeRowPrices();
void totalTicketSale();
void numTicketSold();
void rowAvailability();
void auditoriumAvailability();*/

//Sets the size of the array used to print out the seating arrangements. 16x31 used to fit the full 15x30 seating arrangement, while later skipping the 0x0 rows and columns.
const int ROWS = 16;
const int COLS = 31;


//Displays both the current purchased and unpurchased seats in the theater when used.
void displaySeating(char seating[ROWS][COLS]) {

	cout << "Current Theater Arrangement\n\n";
	for (int i = 1; i < ROWS; i++) { //Loop prints out current contents of seating array.
		for (int j = 1; j < COLS; j++) {
			cout << seating[i][j];
		}
		cout << '\n';
	}
}

//Asks the user for a seat row and column, will 'purchase' the seat and change the character in the array to symbol for purchased seats.
void purchaseTicket(char seating[ROWS][COLS]) {

	int row;
	int seatcolumn;
	bool emptyseat = true; //Used in loop to check if selected seat is empty or not.

	
	do { //Do-While loop that asks the user for a seat row and column to purchase. Will check and repeat if selected seat is already occupied.
		cout << "Enter desired seat row (Pick 1-15): ";
		cin >> row;
		while (row > 15 || row <= 0) { //Loop checks and repeats if selected seat row is 0 or negative, and larger than 15.
			cout << "This seat row is invalid. Enter desired seat row. (Pick 1-15): ";
			cin >> row;
		}
		cout << "Enter the desired seat in row " << row << " (Pick 1-30): ";
		cin >> seatcolumn;
		while (seatcolumn > 30 || seatcolumn <= 0) { //Loop checks and repeats if selected seat column is 0 or negative, and larger than 30.
			cout << "This seat is invalid. Enter the desired seat in row " << row << " (Pick 1-30): ";
			cin >> seatcolumn;
		}
		cout << endl;

		for (int i = 1; i < ROWS; i++) { //Loop that checks if selected seat is purchased already. If it is not, it will change the seat values in array to the purchased character.
			for (int j = 1; j < COLS; j++) {
				if (i == seatrow && j == seatcolumn) { //The array will iterate through until the 'i' and 'j' matches both the selected row and col values for the seat.
					if (seating[i][j] == '*') { //Here it checks current array value if it matches the '*' symbol. If it matches, the user will be prompted to enter a new seat.
						cout << "This seat has been purchased already. Please choose a different seat selection.\n";
						emptyseat = false;
					}
					else {
						seating[i][j] = '*'; //If not purchased, the seat character changes to the '*' symbol.
						emptyseat = true;
					}
				}
			}
		}
	} while (emptyseat == false);

	//Function for calculating price of chosen seat can go here
}

//Displays a menu of multiple options to the user to select. Calls multiple other functions as needed from within.
void displayMenu(char seating[ROWS][COLS]) {
	char choice;

	displaySeating(seating);
	cout << "\nWelcome to the Movies!\n";

	
	while (true) { //While loop keeps the program running until the user decides to stop.
		cout << "\nMain Menu\n";
		cout << "1. Purchase Tickets\n";
		cout << "2. Total Ticket Sales in Dollars\n";
		cout << "3. Total Num of Tickets Sold\n";
		cout << "4. Seat Availability in Each Row\n";
		cout << "5. Seat Availability in Auditorium\n";
		cout << "6. Exit Menu\n";
		cout << "Please enter your choice: ";

		cin >> choice;
		switch (choice) { //Switch cases that display the main menu options to the user.
		case '1':
			cout << "\nThis option would purchase tickets.\n\n";
			purchaseTicket(seating);
			break;
		case '2':
			cout << "\nThis option would display prices.\n\n"; //katherine
			break;
		case '3':
			cout << "\nThis option would display tickets sold.\n\n"; //katherine
			break;
		case '4':
			cout << "\nThis option would display row availability.\n\n"; //erin
			break;
		case '5':
			cout << "\nThis option would display theater availability.\n\n"; //erin
			displaySeating(seating); //Displays the current theater setup with each pass.
			break;
		case '6':
			cout << "\nThis option would exit the menu and program.\n\n";
			system("pause");
			exit(0);
		default:
			cout << "\nInvalid Menu option. Please try again.\n";
			continue;
		}
		

	}
}


//Main function that initializes the seating array and begins the main menu.
int main() {
	char seating[ROWS][COLS];

	for (int i = 1; i < ROWS; i++) { //Loop that creates the seating array, and fills it with a symbol to denote unpurchased seats that will display to the user.
		for (int j = 1; j < COLS; j++) {
			seating[i][j] = '#';
		}
	}

	displayMenu(seating);

	system("pause");
	return 0;
}