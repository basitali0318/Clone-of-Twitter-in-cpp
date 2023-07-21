# Clone-of-Twitter-in-cpp
The task is to design and develop a Console-based Twitter clone using Functions, Arrays and
File Handling in C++. This application will work like Twitter, i.e. allow user to sign-up and log in to
the system. You do not have to implement any networking code as this will be an offline
application where only a single user can log in at a time. The user will be able to Add a Tweet,
View Tweets (Only last 10 Tweets for the user will be shown), Follow a User or log out of the
application. A description of each of these functions is as follows:
1. Login: The user will be prompted for a Username. If the username the user types in exists
in Users.txt file then the user will be asked for the password. If their password (matched
with password from Users.txt) for the given username is correct, they will be logged in,
otherwise they will receive an Error message.
2. Add a Tweet: To add a Tweet a user will only be allowed 180 characters. If the length of
the Tweet added by the user is greater than this, they will be warned about their Tweet
being truncated (cut short) to 180 characters only. If the user accepts this, then his Tweet
will be saved in the Tweets.txt file along with this username. The Tweets.txt file will contain
tweets from all the users of the system.
3. View Tweets: If the user follows someone then they will be shown tweets from those users
first and then the rest of the Tweets from the file. Remember the user only sees 10 Tweets
maximum.
4. Follow a User: The user can choose to follow another user. They will need to provide the
username for the user they wish to follow. If the username exists in the Users.txt file, then
they will be added as followers in the Followers.txt file
