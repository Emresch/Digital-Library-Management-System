#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


class LibraryBook
{
 private:
    string title;
    string author;
    string ISBN;
    bool available; 

 public:
    static int Totalbooks;
    
 LibraryBook(string title, string author, string ISBN, bool available) //Constructor 
    {
        this->title     =title;
        this->author    =author;
        this->ISBN      =ISBN;
        this->available =available;
        Totalbooks++;
    }

 void displayInfo()  //Display funciton for information of book
 {
    cout<<"Title of the book is " << title <<"."<<endl;
    cout<<"Author of the book is " << author <<"."<<endl;
    cout<<"International Standard Book Number is "<< ISBN <<"."<<endl;
    cout<<"The book is "<< (available ? "available.": "not available.")<<endl; //
 }

 void setAvailability(bool Ava) //Setter funciton for availability of the book
 {
    available=Ava;
 }

 string getTitle()   //Getter funciton for title of the book
 {
   return title;
 }
 
 string getAuthor()  //Getter funciton for author of the book
 {
   return author;
 }
 
 string getISBN()    //Getter funciton for ISBN of the book
 {
   return ISBN;
 }

 bool isAvailable()  //Getter funciton for availability of the book
 {
    return available;
 }

 static int getTotalBooks()   //Getter funciton for total number of books
 {
    return Totalbooks;
 }

};

int LibraryBook::Totalbooks = 0;    // Initialize static member of total books

// Abstract base class for library users
class LibraryUser
{
 public:
    string name;
    int userID;

 // Constructor to initialize user details
  LibraryUser(string name, int userID)
 {
    this->name   =name;
    this->userID =userID;
 }

  virtual void displayUserInfo()
 {
    cout<<"Name of the user is "<< name <<endl;
    cout<<"Id of the user is "<< userID <<endl; 
 }

};

class Member : public LibraryUser
{
   private:
    vector<LibraryBook*> borrowedBooks;

   public:
    Member(string name, int userID) : LibraryUser(name, userID){};

 // Borrow a book if available
 void borrowBook(LibraryBook* book) 
 {
   if (book->isAvailable()){
      borrowedBooks.push_back(book);
      book->setAvailability(false);
      cout<<name<<" borrowed "<< book->getTitle() <<endl;
   }
   else 
   {
      cout<<"The book "<<book->getTitle()<< "is not available."<< endl;
   }
 }

 // Return a borrowed book
 void returnBook(LibraryBook* book)
 {
   vector<LibraryBook*>::iterator it= find(borrowedBooks.begin(), borrowedBooks.end(), book);
   if(it != borrowedBooks.end()){
      borrowedBooks.erase(it);
      book-> setAvailability(true);
      cout<< name <<" returned "<< book->getTitle() <<endl;
   }else
   {
      cout<< "The book" << book->getTitle() <<"is not in the borrowed list."<< endl;
   }
 }

 void displayUserInfo() {
   cout << "Member: " << name << ", ID: " << userID << endl;
 }

};

class Librarian : public LibraryUser
{
 private:
  vector<LibraryBook*>& Library;

 public:
  Librarian(string name, int userID, vector<LibraryBook*>& libraryRef) : LibraryUser(name, userID), Library(libraryRef){}
 
 void addBook(LibraryBook* newB){
   Library.push_back(newB);
   cout<<"Librarian "<< name <<" added the book "<<newB->getTitle() <<endl;
 }

 // Remove a book from the library by its ISBN
 void removeBook(string ISBN){
   for(vector<LibraryBook*>::iterator it = Library.begin(); it != Library.end(); ++it){
      if ((*it)->getISBN()==ISBN){
         cout<<"Librarian "<< name <<" removed the book " << (*it)->getTitle() << endl;
         Library.erase(it);
         LibraryBook::Totalbooks--;
         return;  //Exit the loop after removing book form the system
      }
   }
  cout<<"Book with ISBN "<< ISBN <<" not found."<< endl;
 }

 void displayUserInfo() override{
   cout << "Librarian: " << name << ", ID: " << userID << endl;
 }

};

// Class to represent the library system
class LibrarySystem
{
 private:
  vector<LibraryBook*> books;
  vector<LibraryUser*> users;
 
 public:
 // Destructor 
 ~LibrarySystem() {
   for (LibraryBook* book : books) {
   delete book;
   }
   for (LibraryUser* user : users) {
   delete user;
  }
 }

   // Add a new user to the system
   void addUser(LibraryUser* newUser){
      users.push_back(newUser);
      cout<<"User "<< newUser->name <<" added to the library system." <<endl;
   }

   // Add a new book to the system
   void addBook(LibraryBook* newBook){
      books.push_back(newBook);
      cout<<"Book "<<newBook->getTitle() <<" added to the library system." <<endl;
   }

   //Helper funciton for searching book
 LibraryBook* searchBookHelper(const string& title, int index=0)const {
   if(index >= books.size()){
    cout<<"Book not found"<< endl;
    return nullptr;
   }
   if(books[index]->getTitle()== title) return books[index];
   return searchBookHelper(title, index+1 ); 
 }
   //Search for a book by title
 LibraryBook* searchBook(const string& title) const{
   LibraryBook* book = searchBookHelper(title);
   if (book){
      cout<<"Book "<< book->getTitle()<<" found."<< endl;
   }else{
      cout<<"Book "<<title<<" not found"<< endl;
   }
   return book;
 }

 //Display all books in the system
 void displayAllBooks(){
   if (books.empty()){
      cout<<"No books in the library"<<endl;
      return;
   }
   cout<<"All the books in library: "<<endl;
   for(int i = 0; i < books.size(); i ++){
      books[i]->displayInfo();
      cout<<" "<<endl;
   }
   cout<<"Total books in the library is "<<LibraryBook::getTotalBooks()<<endl;
 }

 void displayAllUsers(){
   if(users.empty()){
      cout<<"No users in the library system."<< endl;
      return;
   }
   cout<<"All the users in the system: "<<endl;
   for(int i = 0; i< users.size(); i++){
      users[i]->displayUserInfo();
      cout<<" "<<endl;
   }
 }

};

// Main function
int main(){

   cout << "Library System Initialized."<< endl;
   LibrarySystem LibrarySystem; // Create a librarySystem ojcet

   //Adding a librarian 
   vector<LibraryBook*> LibraryBooks;
   Librarian* librarian = new Librarian("Emre", 1, LibraryBooks);
   LibrarySystem.addUser(librarian);

   //Adding members
   Member* member1 = new Member("john Doe", 101);
   Member* member2 = new Member("Sarah Smith", 102);
   LibrarySystem.addUser(member1);
   LibrarySystem.addUser(member2);

   //adding books
   LibraryBook* book1 = new LibraryBook("1984", "George Orwell", "9780451524935", true);
   cout << "Total books: " << LibraryBook::getTotalBooks() << endl;
   librarian->addBook(book1);
   LibrarySystem.addBook(book1);

   LibraryBook* book2 = new LibraryBook("To Kill a Mockingbird", "Harper Lee", "9780060935467", true);
   librarian->addBook(book2);
   LibrarySystem.addBook(book2);
   cout << "Total books: " << LibraryBook::getTotalBooks() << endl;

   //User borrow and return book
   member1->borrowBook(book1);
   member1->returnBook(book1);

   // Search for a Book
   LibrarySystem.searchBook("1984");

   // Display All Books and Users
   cout << "Displaying all books:" << endl;
   LibrarySystem.displayAllBooks();

   cout << "Displaying all users:" << endl;
   LibrarySystem.displayAllUsers();

   return 0;



};
