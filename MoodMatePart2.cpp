#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// =====================================
// MoodEntry Class
// =====================================
class MoodEntry
{
private:
    string date;
    int rating;
    string note;

public:
    // Constructors
    MoodEntry();
    MoodEntry(string date, int rating, string note);

    // Mutators
    void setDate(string date);
    void setRating(int rating);
    void setNote(string note);

    // Accessors
    string getDate() const;
    int getRating() const;
    string getNote() const;
    string getMoodLabel() const;

    // Display function
    void printEntry() const;
};

// Default constructor
MoodEntry::MoodEntry()
{
    date = "Unspecified";
    rating = 3;
    note = "No note";
}

// Parameterized constructor
MoodEntry::MoodEntry(string date, int rating, string note)
{
    setDate(date);
    setRating(rating);
    setNote(note);
}

// Set date
void MoodEntry::setDate(string date)
{
    if (!date.empty())
        this->date = date;
    else
        this->date = "Unspecified";
}

// Set rating with validation
void MoodEntry::setRating(int rating)
{
    if (rating >= 1 && rating <= 5)
        this->rating = rating;
    else
        this->rating = 3;
}

// Set note
void MoodEntry::setNote(string note)
{
    if (!note.empty())
        this->note = note;
    else
        this->note = "No note";
}

// Get date
string MoodEntry::getDate() const
{
    return date;
}

// Get rating
int MoodEntry::getRating() const
{
    return rating;
}

// Get note
string MoodEntry::getNote() const
{
    return note;
}

// Get mood label
string MoodEntry::getMoodLabel() const
{
    switch (rating)
    {
        case 1: return "Very Bad";
        case 2: return "Bad";
        case 3: return "Okay";
        case 4: return "Good";
        case 5: return "Great";
        default: return "Unknown";
    }
}

// Print one mood entry
void MoodEntry::printEntry() const
{
    cout << "Date: " << date << endl;
    cout << "Mood Rating: " << rating << endl;
    cout << "Mood: " << getMoodLabel() << endl;
    cout << "Note: " << note << endl;
}

// =====================================
// MoodTracker Class
// =====================================
class MoodTracker
{
private:
    MoodEntry entries[20];
    int entryCount;

public:
    MoodTracker();

    void addEntry(const MoodEntry& entry);
    void displayEntries() const;
    double calculateAverage() const;
    MoodEntry getHighestMood() const;
    MoodEntry getLowestMood() const;
    int getEntryCount() const;
};

// Constructor
MoodTracker::MoodTracker()
{
    entryCount = 0;
}

// Add an entry
void MoodTracker::addEntry(const MoodEntry& entry)
{
    if (entryCount < 20)
    {
        entries[entryCount] = entry;
        entryCount++;
    }
    else
    {
        cout << "Mood tracker is full. "
             << "Maximum of 20 entries allowed." << endl;
    }
}

// Display all entries
void MoodTracker::displayEntries() const
{
    if (entryCount == 0)
    {
        cout << "No mood entries available." << endl;
        return;
    }

    for (int i = 0; i < entryCount; i++)
    {
        cout << "\n----- Mood Entry "
             << i + 1 << " -----" << endl;

        entries[i].printEntry();
    }
}

// Calculate average rating
double MoodTracker::calculateAverage() const
{
    if (entryCount == 0)
        return 0.0;

    int total = 0;

    for (int i = 0; i < entryCount; i++)
    {
        total += entries[i].getRating();
    }

    return static_cast<double>(total) / entryCount;
}

// Find highest mood
MoodEntry MoodTracker::getHighestMood() const
{
    MoodEntry highest = entries[0];

    for (int i = 1; i < entryCount; i++)
    {
        if (entries[i].getRating() > highest.getRating())
        {
            highest = entries[i];
        }
    }

    return highest;
}

// Find lowest mood
MoodEntry MoodTracker::getLowestMood() const
{
    MoodEntry lowest = entries[0];

    for (int i = 1; i < entryCount; i++)
    {
        if (entries[i].getRating() < lowest.getRating())
        {
            lowest = entries[i];
        }
    }

    return lowest;
}

// Get entry count
int MoodTracker::getEntryCount() const
{
    return entryCount;
}

// =====================================
// Main Function
// =====================================
int main()
{
    MoodTracker tracker;
    int choice;

    do
    {
        cout << "\n=========================" << endl;
        cout << "       MOODMATE" << endl;
        cout << "=========================" << endl;
        cout << "1. Add Mood Entry" << endl;
        cout << "2. View All Entries" << endl;
        cout << "3. View Average Mood" << endl;
        cout << "4. View Highest Mood" << endl;
        cout << "5. View Lowest Mood" << endl;
        cout << "6. Exit" << endl;
        cout << "=========================" << endl;
        cout << "Enter choice: ";

        // Validate menu input
        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number."
                 << endl;

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
            continue;
        }

        cin.ignore(
            numeric_limits<streamsize>::max(), '\n'
        );

        switch (choice)
        {
            case 1:
            {
                if (tracker.getEntryCount() >= 20)
                {
                    cout << "Mood tracker is full. "
                         << "No more entries can be added."
                         << endl;
                    break;
                }

                string date;
                string note;
                int rating;

                cout << "Enter date: ";
                getline(cin, date);

                // Validate rating input
                while (true)
                {
                    cout << "Enter mood rating (1-5): ";

                    if (cin >> rating &&
                        rating >= 1 && rating <= 5)
                    {
                        break;
                    }

                    cout << "Invalid rating. "
                         << "Please enter a number from 1 to 5."
                         << endl;

                    cin.clear();
                    cin.ignore(
                        numeric_limits<streamsize>::max(), '\n'
                    );
                }

                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );

                cout << "Enter note: ";
                getline(cin, note);

                MoodEntry today(date, rating, note);
                tracker.addEntry(today);

                cout << "\nMood entry added!" << endl;
                break;
            }

            case 2:
            {
                tracker.displayEntries();
                break;
            }

            case 3:
            {
                if (tracker.getEntryCount() == 0)
                {
                    cout << "No mood entries available."
                         << endl;
                }
                else
                {
                    cout << fixed << setprecision(1);
                    cout << "\nAverage Mood: "
                         << tracker.calculateAverage()
                         << endl;
                }
                break;
            }

            case 4:
            {
                if (tracker.getEntryCount() == 0)
                {
                    cout << "No mood entries available."
                         << endl;
                }
                else
                {
                    cout << "\n----- Highest Mood -----"
                         << endl;

                    tracker.getHighestMood().printEntry();
                }
                break;
            }

            case 5:
            {
                if (tracker.getEntryCount() == 0)
                {
                    cout << "No mood entries available."
                         << endl;
                }
                else
                {
                    cout << "\n----- Lowest Mood -----"
                         << endl;

                    tracker.getLowestMood().printEntry();
                }
                break;
            }

            case 6:
            {
                cout << "\nThank you for using MoodMate!"
                     << endl;
                break;
            }

            default:
            {
                cout << "Invalid choice. "
                     << "Please select 1-6." << endl;
            }
        }

    } while (choice != 6);

    return 0;
}