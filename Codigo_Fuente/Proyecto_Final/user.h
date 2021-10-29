#ifndef USER_H
#define USER_H
#include <iostream>

using namespace std;

class User{
public:
    User();
    User(string Username_, string Password_, int Lives_, int Time_, int Score_);

    string username() const;
    void setUsername(const string &username);

    string password() const;
    void setPassword(const string &password);

    int lives() const;
    void setLives(int lives);

    int time() const;
    void setTime(int time);

    int score() const;
    void setScore(int score);

    int scoreLevel() const;
    void setScoreLevel(int scoreLevel);

    int timeLevel() const;
    void setTimeLevel(int timeLevel);

private:
    //Declaracion de atributos de usuarios
    string mUsername         = "";
    string mPassword         = "";
    int    mLives            =  0;
    int    mTime             =  0;
    int    mTimeLevel        =  0;
    int    mScore            =  0;
    int    mScoreLevel       =  0;
};

#endif // USER_H
