#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

const int MAX_TWEETS = 10; 
const int MAX_TWEET_LENGTH = 180;
const string USERS_FILENAME = "users.txt";
const string TWEETS_FILENAME = "tweets.txt";
const string FOLLOWERS_FILENAME = "followers.txt";

struct User {
    string name;
    string username;
    string password;
    string bio;
    string tweets[MAX_TWEETS];
    string followedUsers[100];
};

bool valid(string username, string password);
void addTweet(string twt, string username);
void viewTweets(string username, User& currentUser);
void followUser(string username, User& currentUser);
bool IsUserFollowed(string username, string followed_username);
bool isTweetLonger(string tweet);
void split(const string& str, char delimiter, string fields[], int numFields);

int main() {
    int choice, exit = 0;
    string twt;
    User currentUser;
    cout << "_______________Welcome to our Tweetland!_______________\n";
    cout << endl;
    cout << "____________________" << endl;
    cout << endl;
    bool logged_in = false;

    while (!logged_in) {
        cout << "Choose one option:\n1. SignIn/LogIn\n2. SignUp/Register\n3. Exit\n";
        cout << endl;
        cout << "____________________" << endl;
        cin >> choice;
        if (choice == 1) {
            system("cls");
            cout << "Enter your username:";
            cin >> currentUser.username;
            cout << "Enter your password:";
            cin >> currentUser.password;
            if (valid(currentUser.username, currentUser.password)) {
                cout << "You are successfully logged in.\n";
                logged_in = true;
                system("cls");
            }

            else {
                cout << "Wrong username or password! Please try Again.\n";
            }
        }
        else if (choice == 2) {
            cout << "Enter a username: ";
            cin >> currentUser.username;
            if (valid(currentUser.username, "")) {
                cout << "Sorry, that username is already taken." << endl;
            }
            else {
                cout << endl;
                cout << "____________________";
                cout << endl;
                cout << endl << "Enter your name: ";
                cout << endl;
                cout << "____________________";
                cout << endl;
                cin >> currentUser.name;
                cout << "Enter a password: ";
                cout << endl;
                cout << "____________________";
                cout << endl;
                cin >> currentUser.password;
                cout << "Enter your bio (optional): ";
                cout << endl;
                cout << "____________________";
                cout << endl;
                cin >> currentUser.bio;

                fstream usersFile(USERS_FILENAME, ios::app);
                usersFile << currentUser.username << "," << currentUser.name << "," << currentUser.password << "," << currentUser.bio << endl;
                usersFile.close();
                cout << "You are successfully registered!" << endl;
                cout << endl;
                cout << "____________________";
                cout << endl;
            }
        }
        else if (choice == 3) {
            cout << endl;
            cout << "____________________";
            cout << endl;
            cout << "exiting program....";
            cout << endl;
            cout << "____________________";
            cout << endl;
            goto label;
        }
        else
        {
            cout << endl;
            cout << "____________________";
            cout << endl;
            cout << "\nInvalid choice!\n";
            cout << endl;
            cout << "____________________";
            cout << endl;
            system("pause");
            continue;
        }
  
    }
    cout << endl ;
    while (exit == 0) {
        cout << endl;
        cout << "____________________";
        cout << endl;
        cout << "Choose one option:\n3. Add a Tweet:\n4. View Tweets\n5. Follow a User\n6. Exit\n";
        cout << endl;
        cout << "____________________";
        cout << endl;
        cin >> choice;
        if (choice == 3) {
            cout << endl;
            cout << "____________________";
            cout << endl;
            cout << "\nEnter your tweet: ";
            cout << endl;
            cout << endl;
            cin.ignore();
            getline(cin, twt);
            if (isTweetLonger(twt)) {
                cout << "Tweet is too long. Truncating to 180 characters. Are you sure you want to continue (y/n)? ";
                string ans;
                cin >> ans;
                if (ans == "y") {
                    twt = twt.substr(0, MAX_TWEET_LENGTH);
                    addTweet(twt, currentUser.username);
                    cout << "Tweet added successfully!" << endl;
                }
            }
            else {
                addTweet(twt, currentUser.username);
                cout << "Tweet added successfully!" << endl;
            }
        }
        else if (choice == 4) {
            viewTweets(currentUser.username, currentUser);
        }
        else if (choice == 5) {
            cout << "Enter the username of the user you want to follow: ";
            string username;
            cin >> username;
            followUser(username, currentUser);
        }
        else if (choice == 6) {
            cout << "Exiting program..." << endl;
            goto label;
        }
        else {
            cout << "\nInvalid choice!\n";
            system("pause");
            continue;
        }
    }
    label:
    return 0;
}

bool valid(string username, string password) {
    string line;
    fstream usersFile(USERS_FILENAME);
    while (getline(usersFile, line)) {
        string fields[4];
        split(line, ',', fields, 4);
        if (fields[0] == username) {
            if (password == "") {
                return true;
            }
            else if (fields[2] == password) {
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}


void addTweet(string twt, string username) {
    ofstream tweetsFile(TWEETS_FILENAME, ios::app);
    tweetsFile << username << "," << twt << endl;
    tweetsFile.close();
}

void viewTweets(string username, User& currentUser) {
    fstream tweetsFile(TWEETS_FILENAME);
    string line;
    int count = 0;
    while (getline(tweetsFile, line) && count < 10) {
        string fields[3];
        split(line, ',', fields, 3);
        if (IsUserFollowed(username, fields[0])) {
            cout << fields[0] << ": " << fields[1] << endl;
            count++;
        }
    }
   
    while (getline(tweetsFile, line) && count < 10) {
        string fields[3];
        split(line, ',', fields, 3);
        if (!IsUserFollowed(username, fields[0])) {
            cout << fields[0] << ": " << fields[1] << endl;
            count++;
        }
    }
    tweetsFile.close();
}


void followUser(string username, User& currentUser) {
    if (valid(username, "")) {
        for (int i = 0; i < 100; i++) {
            if (currentUser.followedUsers[i] == "") {
                currentUser.followedUsers[i] = username;
                break;
            }
        }

        ofstream followersFile(FOLLOWERS_FILENAME, ios::app);
        followersFile << currentUser.username << "," << username << endl;
        followersFile.close();
        cout << "You are now following " << username << endl;
    }
    else if (IsUserFollowed(username, currentUser.username)) {
        cout << "You are already following this user" << endl;
    }
    else
    {
        cout << "Error!" << endl;
    }
}

bool IsUserFollowed(string username, string followed_username) {
    ifstream followersFile(FOLLOWERS_FILENAME);
    string line;
    while (getline(followersFile, line)) {
        int pos = line.find(",");
        string user = line.substr(0, pos);
        if (user == username) {
            string followedUser = line.substr(pos + 1);
            if (followedUser == followed_username) {
                followersFile.close();
                return true;
            }
        }
    }
    followersFile.close();
    return false;
}

bool isTweetLonger(string tweet) {
    if (tweet.length() > MAX_TWEET_LENGTH) {
        return true;
    }
    else {
        return false;
    }
}

void split(const string& str, char delimiter, string fields[], int numFields)
{
    stringstream ss(str);
    string token;
    int i = 0;
    while (getline(ss, token, delimiter))
    {
        fields[i++] = token;
        if (i >= numFields)
            break;
    }
}

