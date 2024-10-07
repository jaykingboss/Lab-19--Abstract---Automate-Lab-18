#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Review {
    float rating;
    string comment;
    Review* next;
};

class LinkedList {
public:
    LinkedList() : head(nullptr), tail(nullptr), totalRating(0.0f), reviewCount(0) {}

    void addHead(float rating, const string& comment) {
        Review* newReview = new Review{rating, comment, head};
        head = newReview;
        if (!tail) tail = head;
        totalRating += rating;
        reviewCount++;
    }

    void printReviews(const string& title) const {
        cout << "Reviews for \"" << title << "\":" << endl;
        Review* current = head;
        int index = 1;
        while (current) {
            cout << "> Review #" << index++ << ": " << current->rating << ": " << current->comment << endl;
            current = current->next;
        }
        if (reviewCount > 0) {
            cout << "> Average: " << totalRating / reviewCount << endl;
        }
        cout << endl;
    }

    ~LinkedList() {
        while (head) {
            Review* temp = head;
            head = head->next;
            delete temp;
        }
    }

private:
    Review* head;
    Review* tail;
    float totalRating;
    int reviewCount;
};

class Movie {
public:
    Movie(const string& title) : title(title) {}

    void addReview(float rating, const string& comment) {
        reviews.addHead(rating, comment);
    }

    void printReviews() const {
        reviews.printReviews(title);
    }

    string getTitle() const {
        return title;
    }

private:
    string title;
    LinkedList reviews;
};

float generateRandomRating() {
    return 1.0f + static_cast<float>(rand() % 40) / 10.0f;
}

int main() {
    vector<Movie> movies;

    movies.emplace_back("Movie Title 1");
    movies.back().addReview(generateRandomRating(), "This is a great movie!");
    movies.back().addReview(generateRandomRating(), "I loved the acting.");
    movies.back().addReview(generateRandomRating(), "The plot was fantastic.");

    movies.emplace_back("Movie Title 2");
    movies.back().addReview(generateRandomRating(), "Not my cup of tea.");
    movies.back().addReview(generateRandomRating(), "Great cinematography.");

    movies.emplace_back("Movie Title 3");
    movies.back().addReview(generateRandomRating(), "A masterpiece!");
    movies.back().addReview(generateRandomRating(), "I would watch it again.");

    movies.emplace_back("Movie Title 4");
    movies.back().addReview(generateRandomRating(), "Very interesting concept.");
    movies.back().addReview(generateRandomRating(), "The pacing was off.");

    for (const auto& movie : movies) {
        movie.printReviews();
    }

    return 0;
}
