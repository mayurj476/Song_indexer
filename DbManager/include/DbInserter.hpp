#pragma once

#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <DbUtils.hpp>
#include <mutex>
#include "IDbFactory.hpp"

using namespace std;
static mutex m_Imutex;
class DbInserter : public IDbFactory
{

private:
    static DbInserter *m_DbIserter;
    string m_dbPath;
    sqlite3 *m_dbConnection;

    void createTables();

    DbInserter(string path);
    ~DbInserter();

    DbInserter(const DbInserter &) = delete;
    DbInserter &operator=(const DbInserter &) = delete;

    DbInserter(DbInserter &&) = delete;
    DbInserter &operator=(DbInserter &&) = delete;

public:
    static DbInserter *getDbInserter(string path);
    bool openDatabase(string path) override;
    void closeDatabase() override;
    void executequery(string query) override;

    void toggeleTrackFavstate(const int id, bool state)override;
    void insertSongdetail(tableData &t)override;
};
