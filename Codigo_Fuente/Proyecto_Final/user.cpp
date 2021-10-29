#include "user.h"

User::User(){}

User::User(string Username_, string Password_, int Lives_, int Time_, int Score_){
    /** Inicializacion de atributos de usario **/
    mUsername   = Username_;
    mPassword   = Password_;
    mLives      =    Lives_;
    mTime       =     Time_;
    mScore      =    Score_;
    mScoreLevel =         0;
}

string User::username() const{
    return mUsername;
}

void User::setUsername(const string &username){
    mUsername = username;
}

string User::password() const{
    return mPassword;
}

void User::setPassword(const string &password){
    mPassword = password;
}

int User::lives() const{
    return mLives;
}

void User::setLives(int lives){
    mLives = lives;
}

int User::time() const{
    return mTime;
}

void User::setTime(int time){
    mTime = time;
}

int User::score() const{
    return mScore;
}

void User::setScore(int score){
    mScore = score;
}

int User::scoreLevel() const{
    return mScoreLevel;
}

void User::setScoreLevel(int scoreLevel){
    mScoreLevel = scoreLevel;
}

int User::timeLevel() const
{
    return mTimeLevel;
}

void User::setTimeLevel(int timeLevel)
{
    mTimeLevel = timeLevel;
}
