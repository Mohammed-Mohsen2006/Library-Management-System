#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

/*
	Improvements Added:
	1. Capitalized struct name 'Book' (as per C++ classes naming convention)
	2. Created new class 'Library' to help manage book objects
	3. Moved functions (methods) inside class 'Library'
	4. Added comments for better code organization and debugging (for future implementations)
	5. Created a 'Book' constructor to help create 'Book' objects
	6. Redefined methods (e.g. searchBookByID, searchBookByTitle) for better UI and functionality
	7. 'Encapsulated' book attributes to follow principles of 'Object-Oriented Programming'
	8. Improved error handling

	Further Suggestions:
	1. When project gets larger, remove namespace global (using namespace std;) and specify std namespaces
	2. Use classes to organize code and follow the principle of 'separation of concern'
*/

// [ UTILITY FUNCTION ]: Prompt the user to press any key before navigating
void pressEnterToContinue() {
	cout << "Press any key to continue...";
	cin.get();
}

class Book {
	// Attributes
	string title, author;
	int ID, price, currentStock;

public:
	// Default Constructor - create an instance of 'Book'
	Book() {}

	// Parameterized Constructor - create an instance of 'Book' with set values
	Book(string title, string author, int ID, int price, int currentStock) :
	title(title), author(author), ID(ID), price(price), currentStock(currentStock) {}
	
	// Getters & Setters
	string getTitle() const { return this->title; }
	string getAuthor() const { return this->author; }	
	int getID() const { return this->ID; }	
	int getPrice() const { return this->price; }	
	int getCurrentStocks() const { return this->currentStock; }

	void setTitle(string title) { this->title = title; }
	void setAuthor(string author) { this->author = author; }
	void setID(int ID) { this->ID = ID; }
	void setPrice(int price) { this->price = price; }
	void setCurrentStock(int currentStock) { this->currentStock = currentStock; }

	// Methods
	void displayBookDetails() {
		cout << "[ BOOK DETAILS ]\n";
		cout << "Title: " << getTitle() << '\n';
		cout << "Author: " << getAuthor() << '\n';
		cout << "ID: " << getID() << '\n';
		cout << "Price: $" << getPrice() << '\n';
		cout << "Current Stocks: " << getCurrentStocks() << '\n';
	}
};

// Created class 'Library' to store books created
class Library {
	// Attributes
	int currentID, profit;
	vector<Book> books; // To store list of books

	// Getters & Setters
	int getCurrentID() { return this->currentID++; }
	int getCurrentProfit() const { return this->profit; }	

	void setCurrentID(int currentID) { this->currentID = currentID; }
	void setProfit(int profit) { this->profit = profit; }

public:
	// Default Constructor - create an instance of 'Library' with default values
	Library () { currentID = 1; }

	// Methods
	// [ METHOD ]: Search for a book in the library via title
	Book* searchBookByTitle(const string& bookTitle) {
		Book* foundBook = nullptr;
		bool bookFound = false;

		// Iterate through each book until book with same title is found
		for (auto& book : books) {
			if (book.getTitle() == bookTitle) {
				return &book;
			}
		}

		// ERROR: Non-existing book
		cout << "Book not found!\n";
		return nullptr;
	}

	// [ METHOD ]: Search for a book in the library via ID
	Book* searchBookByID(const int& id) {
		Book* foundBook = nullptr;

		// Iterate through each book until book with same title is found
		for (auto& book : books) {
			if (book.getID() == id) {
				return &book;
			}
		}

		// ERROR: Non-existing book
		cout << "Book not found!\n";
		return nullptr;
	}

	// [ METHOD ]: Remove a book from the library via ID
	bool removeBookByID(int id) {
		for (auto it = books.begin(); it != books.end(); ++it) {
			if (it->getID() == id) {
				books.erase(it); // erase by iterator
				return true;
			}
		}
		return false; // not found
	}

	// [ METHOD ]: Add a book to the library
	void addBook() {
		string title, author;
		int ID, price, currentStock;

		// SUGGESTION: Only create the 'Book' object after all user input for book details have been stored
		// This loop runs indefinitely until the user enters a valid choice
		while (true) {
			// Prompt user to enter a book title or cancel operation
			cout << "Enter Book Title (0 to return): ";
			getline(cin, title);

			if (title == "0") {
				cout << "Cancel adding book...\n";
				return;
			} else if (title == "") { // ERROR: Empty input
				cout << "ERROR: Book title must not be blank\n";
				pressEnterToContinue();
			} else { // Check whether book already exists in the library
				Book* foundBook = searchBookByTitle(title);
				if (foundBook) {
					cout << "ERROR: Book with the same title already exists\n";
				pressEnterToContinue();
				} else break;
			}
		}

		// Automatically assigna new ID to the book
		ID = getCurrentID();

		// This loop runs indefinitely until the user enters a valid author
		while (true) {
			// Prompt user to enter the books author
			cout << "Enter Author: ";
			getline(cin, author);

			// If blank author, set it to 'N/A'
			if (author == "") author = "N/A";
			break;
		}

		// This loop runs indefinitely until the user enters a valid number for book's price
		while (true) {
			// Prompt user to enter a price
			cout << "Enter Book Price: $";
			cin >> price;

			// ERROR: Input mismatch
			if (cin.fail()) {
				cin.clear(); // Clear error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
			} else if (price < 1) {
				cout << "ERROR: Invalid input, price must be positive\n";
				pressEnterToContinue();
			} else break;
		}

		// This loop runs indefinitely until the user enters a valid number for book's current stock
		while (true) {
			// Prompt user to enter book's current stock
			cout << "Enter Current Stock: ";
			cin >> currentStock;

			// ERROR: Input mismatch
			if (cin.fail()) {
				cin.clear(); // Clear error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
			} else if (currentStock < 1) {
				cout << "ERROR: Invalid input, current stock must be positive\n";
				pressEnterToContinue();
			} else break;
		}

		// Create 'Book' object
		books.emplace_back(title, author, ID, price, currentStock);
		cout << "Book '" + title + "' successfully created!\n";

		pressEnterToContinue();
	}

	// [ METHOD ]: Search for a book
	void searchBook() {
		Book* foundBook = nullptr;
		string title;

		// This loop runs indefinitely until the user enters a valid choice
		while (true) {
			// Prompt user to enter a book title or cancel operation
			cout << "Enter Book Title (0 to return): ";
			getline(cin, title);

			if (title == "0") {
				cout << "Cancel searching book...\n";
				return;
			} else if (title == "") { // ERROR: Empty input
				cout << "ERROR: Book title must not be blank\n";
				pressEnterToContinue();
			} else { // Check whether book already exists in the library
				foundBook = searchBookByTitle(title);

				// ERROR: Non-existing book 
				if (!foundBook) {
					cout << "ERROR: Book does not exist\n";
					pressEnterToContinue();
				} else break;
			}
		}

		cout << "Book found!\n";

		char choice;
		// This loop runs indefinitely until user enters a valid choice
		while (true) {
			cout << "Show contents of '" << foundBook->getTitle() << "'? [ y | n ]: ";
			cin >> choice;

			// Do operation based on user choice
			if (choice == 'y') break;
			else if (choice == 'n') return;
		}

		// Display book contents
		foundBook->displayBookDetails();
		pressEnterToContinue();
	}

	// [ METHOD ]: Update book details
	void updateBookDetails() {
		Book* foundBook = nullptr;
		int id;

		// This loop runs indefinitely until user enters a valid choice
		while (true) {
			cout << "Enter Book's ID (0 to return): ";
			cin >> id;

			if (cin.fail()) {
				cin.clear(); // Clear error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
			} else if (id == 0) {
				cout << "Cancel adding book...\n";
				return;
			} else { // Check whether book exists in the library
				foundBook = searchBookByID(id); // Search if book with specified ID exists

				// ERROR: Non-existing book
				if (!foundBook) {
					cout << "ERROR: Book with ID '" << id << "' does not exist in the library\n";
					pressEnterToContinue();
				} else break;
			}
		}

		// Update book's details
		string title, author;
		int ID, price, currentStock;

		// This loop runs indefinitely until the user enters a valid choice
		while (true) {
			// Prompt user to enter a book title or cancel operation
			cout << "Enter New Book Title: ";
			getline(cin, title);

			if (title == "") { // ERROR: Empty input
				cout << "ERROR: Book title must not be blank\n";
				pressEnterToContinue();
			} else break;
		}

		// NOTE: ID is not updatable since it is automatically assigned

		// This loop runs indefinitely until the user enters a valid author
		while (true) {
			// Prompt user to enter the books author
			cout << "Enter New Author: ";
			getline(cin, author);

			// If blank author, set it to 'N/A'
			if (author == "") author = "N/A";
			break;
		}

		// This loop runs indefinitely until the user enters a valid number for book's price
		while (true) {
			// Prompt user to enter a price
			cout << "Enter New Book Price: $";
			cin >> price;

			// ERROR: Input mismatch
			if (cin.fail()) {
				cin.clear(); // Clear error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
			} else if (price < 1) {
				cout << "ERROR: Invalid input, price must be positive\n";
				pressEnterToContinue();
			} else break;
		}

		// This loop runs indefinitely until the user enters a valid number for book's current stock
		while (true) {
			// Prompt user to enter book's current stock
			cout << "Enter Updated Current Stock: ";
			cin >> currentStock;

			// ERROR: Input mismatch
			if (cin.fail()) {
				cin.clear(); // Clear error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
			} else if (price < 1) {
				cout << "ERROR: Invalid input, current stock must be positive\n";
				pressEnterToContinue();
			} else break;
		}

		// Update details
		foundBook->setTitle(title);
		foundBook->setAuthor(author);
		foundBook->setPrice(price);
		foundBook->setCurrentStock(currentStock);

		cout << "Book '" + title + "' successfully updated!\n";

		pressEnterToContinue();
	}

	// [ METHOD ]: Display library's booklist
	void displayBooks() {
		// ERROR: Empty booklist
		if (books.empty()) {
			char choice;

			cout << "There are currently no books in the library.\n";

			// If booklist is empty, suggest to user to create a new book
			cout << "Would you like to add one? [ y | n ]: ";
			cin >> choice;

			// Do operation based on user choice
			if (choice == 'y') addBook();
			else if (choice == 'n') return;
		}

		// Iterate over every book and display its information
		for (int i = 0; i < books.size(); i++) {
			cout << "ID: " << books[i].getID() << " || Title: " << books[i].getTitle() << " || author: " << books[i].getAuthor();
			cout << " || Price: " << books[i].getPrice() << "$ || Current Stocks: " << books[i].getCurrentStocks() << endl;
		}

		pressEnterToContinue();
	}

	// [ METHOD ]: Buy a book from the library
	void buyBook() {
		int id, bookQuantityToPurchase;
		Book* foundBook = nullptr;

		// Display bookilst first before asking for the book ID
		displayBooks();

		// This loop runs indefinitely until user enters a valid choice
		while (true) {
			cout << "Enter the ID of the book to buy (or 0 to cancel): ";
			cin >> id;

			if (cin.fail()) {
				cin.clear(); // Clear error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
			} else if (id == 0) {
				cout << "Cancel adding book...\n";
				return;
			} else { // Check whether book exists in the library
				foundBook = searchBookByID(id); // Search if book with specified ID exists

				// ERROR: Non-existing book
				if (!foundBook) {
					cout << "ERROR: Book with ID '" << id << "' does not exist in the library\n";
					pressEnterToContinue();
				} else break;
			}
		}

		// This loop runs indefinitely until user enters a valid book quantity
		while (true) {
			cout << foundBook->getTitle() << "(Current Stocks: " << foundBook->getCurrentStocks() << ")\n";
			cout << "Enter # of Books: ";
			cin >> bookQuantityToPurchase;

			if (cin.fail()) {
				cin.clear(); // Clear error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
			} else if (bookQuantityToPurchase < 1) {
				cout << "ERROR: # of books to purchase must be positive\n";
				pressEnterToContinue();
				return;
			} else break;
		}

		
		// Calculate & display total
		int total = foundBook->getPrice() * bookQuantityToPurchase;

		cout << "[ RECEIPT ]\n";
		foundBook->displayBookDetails();
		cout << "\nx" << bookQuantityToPurchase << " \'" << foundBook->getTitle() << "' = $" << total << '\n';
		
		// Ask user to confirm book purchsae
		char choice;
		// This loop runs indefinitely until user enters a valid choice
		while (true) {
			cout << "Continue purchase? [ y | n ]: ";
			cin >> choice;

			// Do operation based on user choice
			if (choice == 'y') {
				break;
			} else if (choice == 'n') {
				cout << "Cancelling purchase...\n";
				pressEnterToContinue();
				return;
			} else {
				cout << "ERROR: Invalid choice, please enter 'y' to continue purchaes or 'n' to cancel\n";
				pressEnterToContinue();
			}
		}

		// Add total to profit
		profit += total;

		cout << "Book successfully purchased!\n";
		pressEnterToContinue();
	}

	// [ METHOD ]: Remove a book from the library
	void removeBook() {
		Book* foundBook = nullptr;
		int id;

		// This loop runs indefinitely until user enters a valid choice
		while (true) {
			cout << "Enter the ID of the book to remove (or 0 to cancel): ";
			cin >> id;

			if (cin.fail()) {
				cin.clear(); // Clear error flag
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
			} else if (id == 0) {
				cout << "Cancel removing book...\n";
				return;
			} else { // Check whether book exists in the library
				foundBook = searchBookByID(id); // Search if book with specified ID exists

				// ERROR: Non-existing book
				if (!foundBook) {
					cout << "ERROR: Book with ID '" << id << "' does not exist in the library\n";
					pressEnterToContinue();
				} else {
					// Remove book from the library
					removeBookByID(id);
					cout << "Book removed successfully!\n";
					pressEnterToContinue();
					break;
				}
			}
		}
	}

	// [ METHOD ]: Display library main menu
	void displayMenu() {
		int choice;
		do {
			cout << "\n******** Library Management System **********\n";
			cout << "Total Profit: $" << profit << '\n';	
			cout << "***********************************************\n";
			cout << "1. Add Book\n";
			cout << "2. Display Books\n";
			cout << "3. Search Book\n";
			cout << "4. Buy a Book\n";
			cout << "5. Update Book Details\n";
			cout << "6. Remove Book from Library\n";
			cout << "7. Exit\n";
			cout << "***********************************************\n";

			cout << "Enter choice: ";
			cin >> choice;

			// Navigate based on user choice
			switch (choice)
			{
			case 1:
				addBook();
				break;
			case 2:
				displayBooks();
				break;
			case 3:
				searchBook();
				break;
			case 4:
				buyBook();
				break;
			case 5:
				updateBookDetails();
				break;
			case 6:
				removeBook();
				break;
			case 7:
				cout << "Exiting system... \n";
				break;
			default:
				cout << "ERROR: Invalid choice \n";
			}
		} while (choice != 7);
	}
};

int main() {
	// Create instance of 'Library'
	Library library = Library();
	library.displayMenu();
	return 0;
}