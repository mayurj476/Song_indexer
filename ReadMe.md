# 🎵 Media Indexer in C++

A lightweight C++ tool that recursively scans local folders for audio/video files, extracts metadata using **TagLib**, and stores it into an **SQLite** database.

## ✨ Features

- 🎧 Support for audio formats (MP3, FLAC, etc.) and video formats (MP4, MKV, etc.)
- 🔍 Extracts metadata (Title, Artist, Album, Length, Album Art, etc.)
- 🗂️ Indexes and stores data in an SQLite3 database
- ⚡ Fast and lightweight — written in C++17
- 🧩 Modular and extendable with CMake

## 📐 Design Patterns Used
This project follows clean modular principles and leverages classic object-oriented design patterns for extensibility and maintainability:

- 🏭 **Factory Pattern**
The DbManager module uses a Factory Pattern to create database components like the Inserter and Selector.
This allows switching between different database backends or behaviors without changing client code.

- 🔁 **Singleton Pattern**
The DbInserter and DbSelector are implemented as Singletons, ensuring only one instance exists per application.

This avoids multiple concurrent writes or reads from different parts of the app, keeping SQLite interactions safe and consistent.

## 📦 Dependencies

- [TagLib](https://taglib.org/)
- SQLite3
- CMake ≥ 3.10
- C++17 compatible compiler (e.g. GCC 9+ or Clang 9+)

##📌 To-Do
- [ ] Add support for embedded album art
- [ ] Simple GUI using Qt 

## 🚀 Build Instructions

```bash
git clone https://github.com/mayurj476/Song_indexer.git
cd media-indexer
mkdir build && cd build
cmake ..
make
```
