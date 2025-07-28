#include "MetaDataparser.hpp"
#include <unordered_set>

bool MetadataParser::isValidFile(string extension)
{
    static const unordered_set<string> validExtensions = {
        ".mp3", ".wav", ".mkv", ".aac", ".m4a"};
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    return validExtensions.count(extension) > 0;
}

void MetadataParser::getMetaData(string songpath, string file)
{
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
        throw std::runtime_error("Invalid directory path");
    }

    for (const auto &entry : fs::recursive_directory_iterator(dirPath))
    {
        if (entry.path().filename().has_extension() && isValidFile(entry.path().extension()))
        {
            getMetaData(entry.path().c_str(), entry.path().filename().c_str());
            getPseudoMetaData(entry.path().c_str());
        }
    }
}
