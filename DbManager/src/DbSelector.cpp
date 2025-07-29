
#include <DbSelector.hpp>

using namespace std;

DbSelector *DbSelector::getDbSelector(string path)
{
   lock_guard<mutex> lg(m_Smutex);
   if (m_DbSelector == nullptr)
      m_DbSelector = new DbSelector(path);
   return m_DbSelector;
}

DbSelector::DbSelector(string path) : m_dbPath(path), m_dbConnection(nullptr)
{
   if (!openDatabase(m_dbPath))
   {
      cout << "Failed to open database at " << m_dbPath << endl;
   }
}

DbSelector::~DbSelector()
{
   closeDatabase();
}

void DbSelector::getAllSongs(vector<songinfo>&songs)
{
   
   string query = "SELECT FullPath,TrackName,FileName,AlbumArt FROM Audio  ORDER by TrackName"; 
   sqlite3_stmt *statement;
   songinfo song;
int result = sqlite3_prepare_v2(m_dbConnection, query.c_str(), static_cast<int>(query.length()), &statement, nullptr);
  if (result == SQLITE_OK)
   {
      while ((result != SQLITE_DONE) && (result != SQLITE_ERROR))
      {
         result = sqlite3_step(statement);

         if (result == SQLITE_ROW)
         {        
             song.fullpath=reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
             song.trackname=reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
             song.fileName=reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
             song.albumart=reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));
             songs.push_back(song);
           
         }
      }
   }
   else
   {

      cout<< "select query error:"<<sqlite3_errmsg(m_dbConnection)<<"\n";
   }

   sqlite3_finalize(statement);
}



void DbSelector::getTrackId(string songName, int &Id)
{

   string query = "SELECT Id FROM Audio WHERE TrackName ='" + songName + "';";
   
     
   sqlite3_stmt *statement;

   int result = sqlite3_prepare_v2(m_dbConnection, query.c_str(), static_cast<int>(query.length()), &statement, nullptr);
   if (result == SQLITE_OK)
   {
      while ((result != SQLITE_DONE) && (result != SQLITE_ERROR))
      {
         result = sqlite3_step(statement);

         if (result == SQLITE_ROW)
         {
            Id = static_cast<long>(sqlite3_column_int64(statement, 0));
            cout<<"TrackId=:"<<Id<<endl;
         }
      }
   }
   else
   {

      cout<< "select query error:"<<sqlite3_errmsg(m_dbConnection)<<"\n";
   }

   sqlite3_finalize(statement);
}


string DbSelector::getTrackPath(const string &songName)
{

   string query = "SELECT FullPath FROM Audio WHERE FileName ='"  + songName + "';";
   cout<<"query: "<<query<<endl;
   
   string path=""; 
   sqlite3_stmt *statement;

   int result = sqlite3_prepare_v2(m_dbConnection, query.c_str(), static_cast<int>(query.length()), &statement, nullptr);
   if (result == SQLITE_OK)
   {
      while ((result != SQLITE_DONE) && (result != SQLITE_ERROR))
      {
         result = sqlite3_step(statement);

         if (result == SQLITE_ROW)
         {
            path=reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
          
             cout<<"Fullpath=:"<<path<<endl;
            
         }
      }
   }
   else
   {

      
      cout<< "select query error:"<<sqlite3_errmsg(m_dbConnection)<<"\n";
   }

   sqlite3_finalize(statement);
   return path;
}

void DbSelector::executequery(string query)
{

   sqlite3_stmt *statement;

   int result = sqlite3_prepare_v2(m_dbConnection, query.c_str(), static_cast<int>(query.length()), &statement, nullptr);
   if (result == SQLITE_OK)
   {
      while ((result != SQLITE_DONE) && (result != SQLITE_ERROR))
      {
         result = sqlite3_step(statement);

         if (result == SQLITE_ROW)
         {
            auto returnValue = static_cast<long>(sqlite3_column_int64(statement, 0));
           
            cout << "Return Value: " << returnValue << endl;
         }
      }
   }
   else
   {

      
      cout << "select query error:" << sqlite3_errmsg(m_dbConnection) << "\n";
   }

   sqlite3_finalize(statement);
}

bool DbSelector::openDatabase(string path)
{
   int result;
   /* Open database */
   result = sqlite3_open(path.c_str(), &m_dbConnection);

   if (result)
   {
      
      cout << " Can't open database: " << sqlite3_errmsg(m_dbConnection) << "\n";
      return false;
   }
   cout << "Opened database successfully\n";
   return true;
};
void DbSelector::closeDatabase()
{

   sqlite3_close(m_dbConnection);
   m_dbConnection = nullptr;
};




DbSelector *DbSelector::m_DbSelector = nullptr;