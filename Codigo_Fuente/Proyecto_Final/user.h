#ifndef USER_H
#define USER_H
#include <iostream>

using namespace std;

class User{
public:
    User();
    User(string Username_, string Password_, int Level_, int Lives_, int Score1_, int score2_, int score_3);

    string username() const;
    void setUsername(const string &username);

    string password() const;
    void setPassword(const string &password);

    int level() const;
    void setLevel(int level);

    int scoreFirstLevel() const;
    void setScoreFirstLevel(int scoreFirstLevel);

    int scoreSecondLevel() const;
    void setScoreSecondLevel(int scoreSecondLevel);

    int scoreThirdLevel() const;
    void setScoreThirdLevel(int scoreThirdLevel);

    int lives() const;
    void setLives(int lives);

    int score() const;
    void setScore(int score);

private:
    //Declaracion de atributos de usuarios
    string mUsername         = "";
    string mPassword         = "";
    int    mLevel            =  0;
    int    mLives            =  0;
    int    mScoreFirstLevel  =  0;
    int    mScoreSecondLevel =  0;
    int    mScoreThirdLevel  =  0;
    int    mScore            =  0;
};

#endif // USER_H
