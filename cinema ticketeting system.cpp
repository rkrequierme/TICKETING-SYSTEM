#include <iostream>
#include <queue>
#include <string>
using namespace std;

const int g_kArraySize = 8;

// CustomerQueue Class Definition
class CustomerQueue {
private:
    queue<int> q;

public:
    // Add a customer request (number of tickets) to the queue
    void enqueue(int value) {
        q.push(value);
    }

    // Remove and serve the customer request at the front of the queue
    void dequeue() {
        if (!q.empty()) {
            q.pop();
        } else {
            cout << "Queue is empty!" << endl;
        }
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return q.empty();
    }

    // Display the customer request currently being served
    int peek() const {
        if (!q.empty()) {
            return q.front();
        } else {
            cout << "Queue is empty!" << endl;
            return -1;  // Indicates empty queue
        }
    }

    // Display all customer requests in the queue
    void display() const {
        if (q.empty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        queue<int> temp = q;
        while (!temp.empty()) {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << endl;
    }
};

// Movie Class Definition
class Movie {
private:
    string movie_name;
    int tickets_available;
    double ticket_price;

public:
    Movie();
    Movie(string my_movie_name, int my_tickets_available, double my_ticket_price);
    ~Movie();

    string get_movie_name();
    int get_tickets_available();
    double get_ticket_price();

    void set_movie_name(string new_movie_name);
    void set_tickets_available(int new_tickets_available);
    void set_ticket_price(double new_ticket_price);

    double PurchaseTicket(int purchase_tickets_available);
    void Display();
};

// Default constructor
Movie::Movie() {
    movie_name = "";
    tickets_available = 0;
    ticket_price = 0.0;
}

// Parameterized constructor
Movie::Movie(string my_movie_name, int my_tickets_available, double my_ticket_price) {
    movie_name = my_movie_name;
    tickets_available = my_tickets_available;
    ticket_price = my_ticket_price;
}

// Destructor
Movie::~Movie() {
    cout << movie_name << " is no longer showing.." << endl;
}

// Getter for movie name
string Movie::get_movie_name() {
    return movie_name;
}

// Getter for tickets available
int Movie::get_tickets_available() {
    return tickets_available;
}

// Getter for ticket price
double Movie::get_ticket_price() {
    return ticket_price;
}

// Setter for movie name
void Movie::set_movie_name(string new_movie_name) {
    movie_name = new_movie_name;
}

// Setter for tickets available
void Movie::set_tickets_available(int new_tickets_available) {
    tickets_available = new_tickets_available;
}

// Setter for ticket price
void Movie::set_ticket_price(double new_ticket_price) {
    ticket_price = new_ticket_price;
}

// Purchase a given number of tickets
double Movie::PurchaseTicket(int purchase_tickets_available) {
    double total_price;

    // Check if enough tickets are available
    if (purchase_tickets_available <= tickets_available) {
        total_price = purchase_tickets_available * ticket_price;
        tickets_available = tickets_available - purchase_tickets_available;
        return total_price;
    } else {
        return -1;
    }
}

// Display movie details
void Movie::Display() {
    cout.setf(ios::fixed, ios::floatfield);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << endl << "\t\t\t\tMovie name: " << movie_name << endl
         << "\n\t\t\t\tTickets available: " << tickets_available << endl
         << "\n\t\t\t\tPrice per ticket: " << ticket_price << endl << endl;
}

// MovieTicketMaster Class Definition
class MovieTicketMaster {
private:
    Movie* p_MovieList;
    CustomerQueue customerQueue;  // Add customer queue

public:
    MovieTicketMaster();
    ~MovieTicketMaster();

    void Init(Movie* p_my_MovieList, int array_size);
    void Run();
    void DisplayMenu();
    void ViewMovies();
    Movie* SearchMovie();
    Movie* FindMovie(string find_movie_name);
    void PurchaseTicket();
    void ProcessQueue();  // Add method to process queue
};

// Default constructor
MovieTicketMaster::MovieTicketMaster() {
    p_MovieList = NULL;
}

// Destructor
MovieTicketMaster::~MovieTicketMaster() {
    cout << "Theater has been closed.." << endl;
}

// Initialize the movie list
void MovieTicketMaster::Init(Movie* p_my_MovieList, int array_size) {
    string movie_titles[g_kArraySize] = { "Iron Man", "Black Panther", "Thor", "Superman", "The Flash", "Fantastic Beast", "Pokemon", "Deadpool" };

    int theater_tickets[g_kArraySize] = { 85,75,90,90,75,100,65,50 };

    double movie_price[g_kArraySize] = { 11.5,11.5,11.5,11.5,11.5,13.5,13.5,14.0 };

    Movie* p = p_my_MovieList;

    for (int i = 0; i <= g_kArraySize - 1; i++) {
        p->set_movie_name(movie_titles[i]);
        p->set_tickets_available(theater_tickets[i]);
        p->set_ticket_price(movie_price[i]);
        p++;
    }

    p_MovieList = p_my_MovieList;
}

// Run the main loop
void MovieTicketMaster::Run() {
    int option;

    do {
        DisplayMenu();

        cout << endl << "\t\t\t\tPlease select an option: ";
        cin >> option;

        switch (option) {
        case 1:
            ViewMovies();
            system("PAUSE");
            system("CLS");
            break;

        case 2:
            SearchMovie();
            system("PAUSE");
            system("CLS");
            break;

        case 3:
            PurchaseTicket();
            break;

        case 4:
            cout << "\nThank You!\n" << endl;
            break;

        default:
            cout << "Please choose a valid option:" << endl
                 << "=============================" << endl;
            cin.ignore();
        }
    } while (option != 4);
}

// Display the main menu
void MovieTicketMaster::DisplayMenu() {
    cout << "\t\t\t\tTheater Ticketing System" << endl
         << "\n\t\t\t\t  ***********************  " << endl
         << "\t\t\t\t===========================" << endl
         << "\t\t\t\t\tMAIN MENU: " << endl
         << "\t\t\t\t1=> View all movies" << endl
         << "\t\t\t\t2=> Search a movie" << endl
         << "\t\t\t\t3=> Purchase tickets" << endl
         << "\t\t\t\t4=> Exit Application" << endl;
}

// View all movies
void MovieTicketMaster::ViewMovies() {
    Movie* p_view_movies = p_MovieList;
    system("CLS");
    cout << endl
         << "Here are the movies that are showing " << endl
         << "=========================" << endl << endl;

    for (int i = 0; i < g_kArraySize; i++) {
        cout << "Movie showing at theater " << i + 1 << ": " << endl;
        p_view_movies->Display();
        ++p_view_movies;
    }
}

// Search for a movie by name
Movie* MovieTicketMaster::SearchMovie() {
    string search_movie_name;

    cout << "\n\t\t\t\tPlease enter a movie name: ";
    cin.sync();
    std::getline(std::cin, search_movie_name);

    Movie* p = FindMovie(search_movie_name);

    if (p != NULL) {
        p->Display();
    } else {
        cout << endl << "\n\t\t\t\tError: Movie not found." << endl << endl;
        return NULL;
    }
    return p;
}

// Find a movie by name
Movie* MovieTicketMaster::FindMovie(string find_movie_name) {
    Movie* p_find_movie = p_MovieList;
    for (int i = 0; i < g_kArraySize; i++) {
        if (p_find_movie->get_movie_name() == find_movie_name) {
            cout << endl << "\n\t\t\t\tMovie found" << endl;
            return p_find_movie;
        } else {
            p_find_movie++;
        }
    }
    return NULL;
}

// Purchase tickets for a movie
void MovieTicketMaster::PurchaseTicket() {
    string purchase_movie_name;
    int total_tickets;
    system("CLS");
    cout << "\n\n\t\t\t\tPlease enter a movie name: ";
    cin.sync();
    std::getline(std::cin, purchase_movie_name);

    cout << "\n\t\t\t\tPlease enter the total amount of tickets you wish to purchase: ";
    cin >> total_tickets;

    Movie* p = FindMovie(purchase_movie_name);

    if (p != NULL) {
        double total_cost = p->PurchaseTicket(total_tickets);
        if (total_cost == -1) {
            cout << "\n\t\t\t\tThis movie has been sold out or there are" << endl
                 << "\n\t\t\t\tnot enough tickets available per your request" << endl << endl;
        } else {
            cout << "\n\t\t\t\tYour total bill is : " << total_cost << endl;
        }
        customerQueue.enqueue(total_tickets);  // Enqueue the customer request
        ProcessQueue();  // Process the queue
        cout << "\n\n\n\n\t\t\t\t";
        system("PAUSE");
        system("CLS");
    } else {
        cout << "No movie has been found" << endl;
    }
}

// Process the customer queue
void MovieTicketMaster::ProcessQueue() {
    cout << "\n\t\t\t\tProcessing Queue:" << endl;
    customerQueue.display();  // Display the queue
    while (!customerQueue.isEmpty()) {
        cout << "\n\t\t\t\tServing customer request: " << customerQueue.peek() << endl;
        customerQueue.dequeue();
    }
}

// Main Function
int main() {
    Movie movie_objects[g_kArraySize];

    MovieTicketMaster* p_MovieTicketMaster = new MovieTicketMaster();
    p_MovieTicketMaster->Init(movie_objects, g_kArraySize);
    p_MovieTicketMaster->Run();

    delete p_MovieTicketMaster;
    return 0;
}

/*
Explanation:
- The CustomerQueue class simulates a queue of customer requests, where each request is an integer representing the number of tickets a customer wants to purchase.
- The Movie class represents a movie with a name, available tickets, and ticket price. It includes methods to purchase tickets and display movie information.
- The MovieTicketMaster class manages the movie ticketing system, including initializing movie data, displaying menus, viewing movies, searching for a movie, purchasing tickets, and processing the customer queue.
- In the PurchaseTicket function, customer requests (number of tickets) are enqueued into the CustomerQueue, and then the queue is processed to simulate serving the customers.
- The main function initializes the movie data and runs the MovieTicketMaster system.
*/

