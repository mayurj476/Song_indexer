#pragma once
#include <string>
#include <vector>
using namespace std;

class IDbFactory
{
public:
    virtual bool openDatabase(string path) = 0;
    virtual void closeDatabase() = 0;
    virtual void executequery(string query) = 0;

    virtual void getTrackId(string songpath, int &Id) {};
    virtual void getAllSongs(vector<songinfo> &songs) {};
    virtual string getTrackPath(const string &songName) {return "";};

    virtual void toggeleTrackFavstate(const int id, bool state) {};
    virtual void insertSongdetail(tableData &t) {};
};