#include "user.h"

User::User(){}

User::User(string Username_, string Password_, int Level_, int Lives_, int Score1_, int Score2_, int Score3_){
    /** Inicializacion de atributos de usario **/
    mUsername         = Username_;
    mPassword         = Password_;
    mLevel            =    Level_;
    mLives            =    Lives_;
    mScoreFirstLevel  =   Score1_;
    mScoreSecondLevel =   Score2_;
    mScoreThirdLevel  =   Score3_;
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

int User::level() const
{
    return mLevel;
}

void User::setLevel(int level){
    mLevel = level;
}

int User::scoreFirstLevel() const
{
    return mScoreFirstLevel;
}

void User::setScoreFirstLevel(int scoreFirstLevel){
    mScoreFirstLevel = scoreFirstLevel;
}

int User::scoreSecondLevel() const{
    return mScoreSecondLevel;
}

void User::setScoreSecondLevel(int scoreSecondLevel){
    mScoreSecondLevel = scoreSecondLevel;
}

int User::scoreThirdLevel() const{
    return mScoreThirdLevel;
}

void User::setScoreThirdLevel(int scoreThirdLevel){
    mScoreThirdLevel = scoreThirdLevel;
}

int User::lives() const
{
    return mLives;
}

void User::setLives(int lives)
{
    mLives = lives;
}
