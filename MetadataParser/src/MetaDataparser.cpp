#include "MetaDataparser.hpp"
#include <unordered_set>
#include <thread>

bool MetadataParser::isValidFile(string extension)
{
    static const unordered_set<string> validExtensions = {
        ".mp3", ".wav", ".mkv", ".aac", ".m4a", ".mp4"};
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    return validExtensions.count(extension) > 0;
}

MetadataParser::MetadataParser() : m_dbInserter(Dbmanager::getDabase(DATABASE_PATH, Dbmanager::DbType::INSERTER)),
                                   m_dbSelector(Dbmanager::getDabase(DATABASE_PATH, Dbmanager::DbType::SELECTOR))
{
}

MetadataParser::~MetadataParser()
{
    DbInserter::destroyInstance();
    DbSelector::destroyInstance();
}

void MetadataParser::getMetaData(string songpath, string file)
{
    hash<string> hashFn;
    int id = hashFn(songpath) % 1000000; // Simple hash to
    TagLib::FileRef f(songpath.c_str());
    if (!f.isNull() && f.tag())
    {
        TagLib::Tag *tag = f.tag();

        cout << "-- TAG (basic) --" << endl;
        cout << "title   - \"" << tag->title() << "\"" << endl;
        cout << "artist  - \"" << tag->artist() << "\"" << endl;
        cout << "album   - \"" << tag->album() << "\"" << endl;
        cout << "year    - \"" << tag->year() << "\"" << endl;
        cout << "comment - \"" << tag->comment() << "\"" << endl;
        cout << "track   - \"" << tag->track() << "\"" << endl;
        cout << "genre   - \"" << tag->genre() << "\"" << endl;

        // Prepare data for database insertion
        tableData t;
        t.Id = id; // Use the hash as ID
        t.trackPath = songpath;
        t.trackName = tag->title().to8Bit(true);
        t.FileName = file;
        t.albumart = ""; // Placeholder for album art
        t.length = f.audioProperties() ? f.audioProperties()->lengthInSeconds() : 0;
        t.isFav = false; // Default value, can be changed later
        t.artist = tag->artist().to8Bit(true);
        t.genre = tag->genre().to8Bit(true);
        t.album = tag->album().to8Bit(true);
        t.year = tag->year();

        m_dbInserter->insertSongdetail(t);
    }
}

void MetadataParser::getPseudoMetaData(string songpath)
{
    TagLib::FileRef f(songpath.c_str());
    if (!f.isNull() && f.audioProperties())
    {
        TagLib::AudioProperties *properties = f.audioProperties();

        int seconds = properties->lengthInSeconds() % 60;
        int minutes = properties->lengthInSeconds() / 60;

        cout << "-- AUDIO --" << endl;
        cout << "bitrate     - " << properties->bitrate() << endl;
        cout << "sample rate - " << properties->sampleRate() << endl;
        cout << "channels    - " << properties->channels() << endl;
        cout << "length      - " << minutes << ":" << setfill('0') << setw(2) << seconds << endl;
    }
}

void MetadataParser::startIndexing(string path)
{
    fs::path dirPath(path);
    if (!fs::exists(dirPath) || !fs::is_directory(dirPath))
    {
        cout << "Invalid directory path\n";
        return;
    }

    for (const auto &entry : fs::recursive_directory_iterator(dirPath))
    {
        if (entry.path().filename().has_extension() && isValidFile(entry.path().extension()))
        {
            getMetaData(entry.path().c_str(), entry.path().filename().c_str());
            getPseudoMetaData(entry.path().c_str());
        }
    }
    cout << "Indexing completed.\n";
    m_indexingComplete= true;
    m_cv.notify_all(); // Notify that indexing is complete

}

void MetadataParser::listaudioFiles()
{
    vector<songinfo> songs;
    unique_lock<mutex> lock(m_mutex);
    m_cv.wait(lock, [this] { return m_indexingComplete; }); // Wait
    m_dbSelector->getAllSongs(songs); 

    cout << "Listing all audio files:"<<songs.size() << " files found." << endl;
        for (const auto &song : songs)
        {
            cout << "Full Path: " << song.fullpath << endl;
            cout << "Track Name: " << song.trackname << endl;
            cout << "File Name: " << song.fileName << endl;
            cout << "Album Art: " << song.albumart << endl;
            cout << "------------------------" << endl;
        }
   
}
