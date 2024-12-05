#include <iostream>
#include <string>
#include <time.h>
#include <vector>
using namespace std;

class Song
{
public:
    string title;
    string artist;
    int duration; // duration in seconds

    Song(string t, string a, int d) : title(t), artist(a), duration(d) {}
};

class Node
{
public:
    Song *song;
    Node *next;

    Node(Song *s) : song(s), next(NULL) {}
};

class Playlist
{
private:
    Node *head;

public:
    Playlist() : head(NULL) {}

    // Add a song
    void addSong(string title, string artist, int duration)
    {
        Song *newSong = new Song(title, artist, duration);
        Node *temp = new Node(newSong);

        if (head == NULL)
        {
            // If the list is empty
            head = temp;
            return;
        }

        Node *curr = head;
        Node *prev = NULL;
        while (curr)
        {
            prev = curr;
            curr = curr->next;
        }
        if (prev == NULL)
        {
            // Insert at the head
            temp->next = head;
            head = temp;
        }
        else
        {
            prev->next = temp;
            temp->next = curr;
        }
    }

    // Remove a song by title
    void removeSong(string title)
    {
        if (head == NULL)
        {
            cout << "Playlist is empty!" << endl;
            return;
        }

        Node *curr = head;
        Node *prev = NULL;

        while (curr != NULL)
        {
            if (curr->song->title == title)
            {
                if (prev == NULL)
                {
                    head = curr->next; // Remove head
                }
                else
                {
                    prev->next = curr->next;
                }
                delete curr->song;
                delete curr;
                cout << "Song removed successfully!" << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        cout << "Song not found!" << endl;
    }

    // Display the playlist
    void display()
    {
        if (head == NULL)
        {
            cout << "Playlist is empty!" << endl;
            return;
        }

        Node *curr = head;
        int index = 1;
        int totalDuration = 0;

        while (curr != NULL)
        {
            cout << index++ << ". " << curr->song->title << " by " << curr->song->artist
                 << " (" << curr->song->duration << " seconds)" << endl;
            totalDuration += curr->song->duration;
            curr = curr->next;
        }
        cout << "Total Duration: " << totalDuration << " seconds" << endl;
    }

    // Reverse the playlist
    void rev_playlist()
    {
        Node *prev = NULL;
        Node *curr = head;
        Node *next = NULL;

        while (curr != NULL)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
        cout << "Playlist reversed!" << endl;
    }

    // shuffle playlist

    void shuffle_playlist()
    {
        if (!head || !head->next)
        {
            cout << "Playlist is too small to shuffle!" << endl;
            return;
        }

        srand(static_cast<unsigned int>(time(0)));

        vector<Node *> nodes;
        Node *curr = head;
        while (curr)
        {
            nodes.push_back(curr);
            curr = curr->next;
        }

        for (int i = nodes.size() - 1; i > 0; --i)
        {
            int j = rand() % (i + 1);
            swap(nodes[i], nodes[j]);
        }

        head = nodes[0];
        curr = head;
        for (int i = 1; i < nodes.size(); ++i)
        {
            curr->next = nodes[i];
            curr = curr->next;
        }
        curr->next = NULL;

        cout << "Playlist shuffled!" << endl;
    }

    // Search for a song by title
    void search(string title)
    {
        if (head == NULL)
        {
            cout << "Playlist is empty!" << endl;
            return;
        }

        Node *curr = head;

        while (curr != NULL)
        {
            if (curr->song->title == title)
            {
                cout << "Song found " << ": " << curr->song->title
                     << " by " << curr->song->artist << endl;
                return;
            }
            curr = curr->next;
        }
        cout << "Song not found!" << endl;
    }

    void Repeat_on()
    {
        if (!head)
        {
            cout << "Playlist is empty!" << endl;
            return;
        }

        Node *curr = head;
        while (curr->next)
        {
            curr = curr->next;
        }
        curr->next = head; // Create a circular linked list
        cout << "Repeat mode enabled!" << endl;
    }

    // To break the repeat mode
    void Repeat_off()
    {
        if (!head)
        {
            cout << "Playlist is empty!" << endl;
            return;
        }

        Node *curr = head;
        while (curr->next && curr->next != head)
        {
            curr = curr->next;
        }
        curr->next = NULL; // Break the circular reference
        cout << "Repeat mode disabled!" << endl;
    }

    // Destructor to free memory
    ~Playlist()
    {
        Node *curr = head;
        while (curr != NULL)
        {
            Node *temp = curr;
            curr = curr->next;
            delete temp->song;
            delete temp;
        }
    }
};

int main()
{
    Playlist playlist;
    int choice;

    do
    {
        cout << "\n--- Music Playlist Manager ---\n";
        cout << "1. Add Song\n";
        cout << "2. Remove Song\n";
        cout << "3. Display Playlist\n";
        cout << "4. Reverse Playlist\n";
        cout << "5. Shuffle Playlist\n";
        cout << "6. Search Song\n";
        cout << "7. Enable Repeat Mode\n";
        cout << "8. Disable Repeat Mode\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string title, artist;
            int duration;
            cout << "Enter song title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter artist name: ";
            getline(cin, artist);
            cout << "Enter duration (in seconds): ";
            cin >> duration;
            playlist.addSong(title, artist, duration);
            cout << "Song added successfully!" << endl;
            break;
        }
        case 2:
        {
            string title;
            cout << "Enter the title of the song to remove: ";
            cin.ignore();
            getline(cin, title);
            playlist.removeSong(title);
            break;
        }
        case 3:
            playlist.display();
            break;
        case 4:
            playlist.rev_playlist();
            break;
        case 5:
            playlist.shuffle_playlist();
            break;
        case 6:
        {
            string title;
            cout << "Enter the title of the song to search: ";
            cin.ignore();
            getline(cin, title);
            playlist.search(title);
            break;
        }
        case 7:
            playlist.Repeat_on();
            break;
        case 8:
            playlist.Repeat_off();
            break;
        case 9:
            cout << "Exiting... Thank you for using the playlist manager!" << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}
