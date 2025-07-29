#pragma once
#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <vector>
#include <DbUtils.hpp>
#include <mutex>
#include "IDbFactory.hpp"

using namespace std;
static mutex m_Smutex;
class DbSelector : public IDbFactory
{

private:
    static DbSelector *m_DbSelector;
    string m_dbPath;
    sqlite3 *m_dbConnection;
    DbSelector(string path);

    DbSelector(const DbSelector &) = delete;
    DbSelector &operator=(const DbSelector &) = delete;

    DbSelector(DbSelector &&) = delete;
    DbSelector &operator=(DbSelector &&) = delete;

public:
    static DbSelector *getDbSelector(string path);
    static void destroyInstance();

    bool openDatabase(string path) override;
    void closeDatabase() override;
    void executequery(string query) override;

    void getTrackId(string songpath, int &Id) override;
    void getAllSongs(vector<songinfo> &songs) override;
    string getTrackPath(const string &songName) override;

    virtual ~DbSelector();
};
