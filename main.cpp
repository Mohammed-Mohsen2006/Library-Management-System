#include<iostream>
#include<string>
#include<vector>
using namespace std;
struct book{
	string title, author;
	int id, price, stock;
};
vector<book>books;
int nxtid = 1, profit = 0;
void addbook(){
	book b;
	b.id = nxtid++;
	cin.ignore();
	cout << "Enter Title or 0 to return : ";
	getline(cin, b.title);
	if (b.title == "0")return;
	cout << "Enter author : ";
	getline(cin, b.author);
	cout << "Enter Price : ";
	cin >> b.price;
	cout << "Enter Stock : ";
	cin >> b.stock;
	books.push_back(b);
	cout << "Book added successfully \n";
}
void displaybooks() {
	if (books.empty()) {
		cout << "No books available \n";
		return;
	}
	for (int i = 0; i < books.size(); i++) {
		cout << "ID : " << books[i].id << " || Title : " << books[i].title << " || author : " << books[i].author;
		cout << " || Price : " << books[i].price << "$ || Stock : " << books[i].stock << endl;
	}
}
void searchbook() {
	string s;
	cout << "Enter title or author to search or 0 to return : ";
	cin.ignore();
	getline(cin, s);
	if (s == "0")return;
	bool f = 0;
	for (int i = 0; i < books.size(); i++) {
		if (books[i].title == s || books[i].author == s) {
			cout << "ID : " << books[i].id << " || Title : " << books[i].title << " || author : " << books[i].author;
			cout << " || Price : " << books[i].price << "$ || Stock : " << books[i].stock << endl;
			f = 1;
		}
	}
	if (f == 0)cout << "Book not found\n";
}
void buybook() {
	int id, qua;
	cout << "Enter ID or 0 to return : ";
	cin >> id;
	if (id == 0)return;
	cout << "Enter quantity : ";
	cin >> qua;
	bool f = 0;
	for (int i = 0; i < books.size(); i++) {
		if (books[i].id == id) {
			f = 1;
			if (qua <= books[i].stock) {
				books[i].stock -= qua;
				int total = books[i].price * qua;
				profit += total;
				cout << "Enough stock/  Total : " << total << "$ \n";
			}
			else {
				cout << "Not enough stock.\n";
			}
			break;
		}
	}
	if (f == 0) cout << "Book not found \n";
}
void updateBook() {
	int id;
	cout << "Enter book ID to update or 0 to return : ";
	cin >> id;
	if (id == 0)return;
	bool f = 0;
	for (int i = 0; i < books.size(); i++) {
		if (books[i].id == id) {
			f = 1;
			cout << "Enter new title : ";
			cin.ignore();
			getline(cin, books[i].title);
			cout << "Enter new author : ";
			getline(cin, books[i].author);
			cout << "Enter new price : ";
			cin >> books[i].price;
			cout << "Enter new stock : ";
			cin >> books[i].stock;
			cout << "Book updated \n";
			break;
		}
	}
	if (f == 0) cout << "Book not found \n";
}
void deletebook() {
	int id;
	cout << "Enter book ID to delete or 0 to return : ";
	cin >> id;
	if (id == 0)return;
	bool f = 0;
	for (int i = 0; i < books.size(); i++) {
		if (books[i].id == id) {
			f = 1;
			books.erase(books.begin() + i);
			cout << "Book deleted \n";
			break;
		}
	}
	if (f == 0)cout << "Book not found \n";
}
void report() {
	cout << "Total number of books : " << books.size() << endl;
	int totalvalue = 0;
	for (int i = 0; i < books.size(); i++) {
		totalvalue += (books[i].price * books[i].stock);
	}
	cout << "Total stock value : " << totalvalue << "$" << endl;
	cout << "Out of stock books : ";
	bool f = 0;
	for (int i = 0; i < books.size(); i++) {
		if (books[i].stock == 0) {
			f = 1;
			cout << "ID : " << books[i].id << " || Title : " << books[i].title << " || author : " << books[i].author << endl;
		}
	}
	if (f == 0) cout << "All books in stock \n";
	cout << "Total profit : " << profit << "$" << endl;
}
int main() {
	int choice;
	do {
		cout << "\n******** Library Management System **********\n";
		cout << "1. Add Book\n";
		cout << "2. Display All Books\n";
		cout << "3. Search Book\n";
		cout << "4. Buy Book\n";
		cout << "5. Update Book\n";
		cout << "6. Delete Book\n";
		cout << "7. Report\n";
		cout << "8. Exit\n";
		cout << "*****************************************\n";
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			addbook();
			break;
		case 2:
			displaybooks();
			break;
		case 3:
			searchbook();
			break;
		case 4:
			buybook();
			break;
		case 5:
			updateBook();
			break;
		case 6:
			deletebook();
			break;
		case 7:
			report();
			break;
		case 8:
			cout << "Exiting... \n";
			break;
		default:
			cout << "Invalid choice \n";
		}
	} while (choice!=8);
	return 0;
}