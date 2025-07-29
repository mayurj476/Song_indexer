#include <iostream>
#include "MetaDataparser.hpp"
#include <thread>
#include <memory>

int main(int, char **)
{
    unique_ptr<MetadataParser> indexer = make_unique<MetadataParser>();

    std::string path = "/home/mayur/music/";                                   // Path to the directory to index
    thread indexerThread(&MetadataParser::startIndexing, indexer.get(), path); //.get() to get raw pointer

    thread getterthread(&MetadataParser::listaudioFiles, indexer.get()); // Thread to list audio files
    indexerThread.join();
    getterthread.join(); // Wait for the listing thread to finish
}
