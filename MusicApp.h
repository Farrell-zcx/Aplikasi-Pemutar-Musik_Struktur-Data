#ifndef MUSIC_APP_H
#define MUSIC_APP_H

#include <map>
#include <string>
#include <vector>

struct Song {
  std::string id;
  std::string title;
  std::string artist;
  std::string album;
  std::string genre;
  int year;
  int durationMin;
  int durationSec;
};

struct NodeLagu {
  Song dataLagu;
  NodeLagu *next;
  NodeLagu *prev;
};

// MUSIC LIBRARY (ADMIN)
class MusicLibrary {
private:
  NodeLagu *head;
  NodeLagu *tail;

  std::map<std::string, std::vector<NodeLagu *>> artistIndex;
  std::map<std::string, std::vector<NodeLagu *>> genreIndex;

  NodeLagu *cariNode(std::string idLagu);
  void removeFromIndex(NodeLagu *node);

public:
  MusicLibrary();
  ~MusicLibrary();

  void tambahLagu(Song dataBaru);
  void tampilkanSemuaLagu();
  void updateLagu(std::string idLagu, Song dataUpdate);
  void hapusLagu(std::string idLagu);
  void cariLagu(std::string query);

  NodeLagu *getPointerLagu(std::string idLagu);
  NodeLagu *getSimilarLagu(NodeLagu *currentSong);
};

// PLAYLIST (USER)
class Playlist {
private:
  struct NodePlaylist {
    NodeLagu *dataPtr;
    NodePlaylist *next;
    NodePlaylist *prev;
  };

  std::string namaPlaylist;
  NodePlaylist *head;
  NodePlaylist *tail;
  NodePlaylist *currentTrack;

public:
  Playlist(std::string nama);
  ~Playlist();

  void tambahLaguKePlaylist(NodeLagu *pointerKeLagu);
  void hapusLaguDariPlaylist(NodeLagu *pointerKeLagu);

  void tampilkanIsiPlaylist(bool showStatus = true);

  void start(); 
  void play();  
  void pause(); 
  void stop();  

  bool next();
  void prev();
  bool playByTitle(std::string judul);

  NodeLagu *getCurrentTrackPointer();
};

#endif