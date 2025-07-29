#include <DbInserter.hpp>
#include <vector>
using namespace std;

DbInserter *DbInserter::getDbInserter(string path)
{
    lock_guard<mutex> lg(m_Imutex);
    if (m_DbIserter == nullptr)
        m_DbIserter = new DbInserter(path);
    return m_DbIserter;
}

DbInserter::DbInserter(string path) : m_dbPath(path), m_dbConnection(nullptr)
{
    if (!openDatabase(m_dbPath))
    {
        cout << "Failed to open database at " << m_dbPath << endl;
    }
    createTables();
}

DbInserter::~DbInserter()
{
    closeDatabase();
}

bool DbInserter::openDatabase(string path)
{
    /* Open database */
    int result = sqlite3_open(path.c_str(), &m_dbConnection);

    if (result)
    {
        cout << " Can't open database: " << sqlite3_errmsg(m_dbConnection) << "\n";
        return false;
    }

    cout << "Opened database successfully\n";
    return true;
};
void DbInserter::closeDatabase()
{

    sqlite3_close(m_dbConnection);
    m_dbConnection = nullptr;
};

void DbInserter::insertSongdetail(tableData &t)
{

    string sql("INSERT or REPLACE INTO Audio VALUES(" + to_string(t.Id) + ",'" + t.trackPath + "','" +
        t.trackName + "','" + t.FileName + "','" + t.artist + "','" + t.genre +
        "','" + t.album + "'," + to_string(t.year) + ",'" + t.albumart + "'," +
        to_string(t.length) + "," + to_string(t.isFav) + ");");
    if (m_dbConnection)
    {
        executequery(sql);
    }
    else
    {
        cout << "Database is not initialised\n";
    }
}

void DbInserter::createTables()
{

    vector<string> queries = {"CREATE TABLE IF NOT EXISTS Audio (	Id INTEGER PRIMARY KEY,"
                              "FullPath TEXT NOT NULL,"
                              "TrackName TEXT,"
                              "FileName TEXT,"
                              "Artist TEXT,"
                              "Genre TEXT,"
                              "Album TEXT,"
                              "Year INTEGER DEFAULT 0,"
                              "AlbumArt TEXT,"
                              "Length INTEGER DEFAULT 0,"
                              "isFav INTEGER DEFAULT 0);",

                              "CREATE TABLE IF NOT EXISTS Video (	Id INTEGER PRIMARY KEY,"
                              "FullPath TEXT NOT NULL,"
                              "Lenght INTEGER DEFAULT 0);"};

    // for (auto query : queries)
    // {
    //     executequery(queries[0]);
    // }
    executequery(queries[0]);
}

void DbInserter::executequery(string query)
{
    char *zErrMsg;
    int result = sqlite3_exec(m_dbConnection, query.c_str(), nullptr, nullptr, &zErrMsg);
    if (result != SQLITE_OK)
    {
        cout << "SQL error: " << zErrMsg << "\n";
        sqlite3_free(zErrMsg);
    }
}

void DbInserter::toggeleTrackFavstate(const int id, bool state)
{

    string query = {"UPDATE OR IGNORE Audio Set isFav=" + to_string(state) + "WHERE Id=" + to_string(id)};

    executequery(query);
}

DbInserter *DbInserter::m_DbIserter = nullptr;