#include "MusicApp.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

// Helper untuk memotong string agar pas di tabel
std::string truncate(std::string str, size_t width) {
  if (str.length() > width) {
    return str.substr(0, width - 3) + "...";
  }
  return str;
}

// IMPLEMENTASI MUSIC LIBRARY (ADMIN)
MusicLibrary::MusicLibrary() {
  head = nullptr;
  tail = nullptr;
}

MusicLibrary::~MusicLibrary() {
  NodeLagu *current = head;
  while (current != nullptr) {
    NodeLagu *next = current->next;
    delete current;
    current = next;
  }
}

NodeLagu *MusicLibrary::cariNode(std::string idLagu) {
  NodeLagu *current = head;
  while (current != nullptr) {
    if (current->dataLagu.id == idLagu) {
      return current;
    }
    current = current->next;
  }
  return nullptr;
}

void MusicLibrary::removeFromIndex(NodeLagu *node) {
  std::string artist = node->dataLagu.artist;
  if (artistIndex.find(artist) != artistIndex.end()) {
    auto &artistVec = artistIndex[artist];
    artistVec.erase(std::remove(artistVec.begin(), artistVec.end(), node),
                    artistVec.end());
    if (artistVec.empty()) {
      artistIndex.erase(artist);
    }
  }

  std::string genre = node->dataLagu.genre;
  if (genreIndex.find(genre) != genreIndex.end()) {
    auto &genreVec = genreIndex[genre];
    genreVec.erase(std::remove(genreVec.begin(), genreVec.end(), node),
                   genreVec.end());
    if (genreVec.empty()) {
      genreIndex.erase(genre);
    }
  }
}

void MusicLibrary::tambahLagu(Song dataBaru) {
  if (cariNode(dataBaru.id) != nullptr) {
    std::cout << "Error: ID Lagu " << dataBaru.id << " sudah ada!\n";
    return;
  }

  NodeLagu *newNode = new NodeLagu;
  newNode->dataLagu = dataBaru;
  newNode->next = nullptr;
  newNode->prev = tail;

  if (head == nullptr) {
    head = newNode;
    tail = newNode;
  } else {
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  }

  artistIndex[dataBaru.artist].push_back(newNode);
  genreIndex[dataBaru.genre].push_back(newNode);

  std::cout << "Lagu berhasil ditambahkan: " << dataBaru.title << "\n";
}

void MusicLibrary::tampilkanSemuaLagu() {
  if (head == nullptr) {
    std::cout << "Library kosong.\n";
    return;
  }

  NodeLagu *current = head;

  // Header Tabel
  std::cout << std::string(96, '=') << "\n";
  std::cout << std::left << std::setw(6) << "ID" << std::setw(25) << "Judul"
            << std::setw(20) << "Artis" << std::setw(20) << "Album"
            << std::setw(10) << "Genre" << std::setw(6) << "Tahun"
            << std::setw(9) << "Durasi" << "\n";
  std::cout << std::string(96, '=') << "\n";

  while (current != nullptr) {
    Song &s = current->dataLagu;
    std::cout << std::left << std::setw(6) << truncate(s.id, 5) << std::setw(25)
              << truncate(s.title, 24) << std::setw(20)
              << truncate(s.artist, 19) << std::setw(20)
              << truncate(s.album, 19) << std::setw(10) << truncate(s.genre, 9)
              << std::setw(6) << s.year << std::setw(2) << s.durationMin << ":"
              << std::setw(2) << std::setfill('0') << s.durationSec
              << std::setfill(' ') << "\n";
    current = current->next;
  }
  std::cout << std::string(96, '-') << "\n";
}

void MusicLibrary::updateLagu(std::string idLagu, Song dataUpdate) {
  NodeLagu *node = cariNode(idLagu);
  if (!node) {
    std::cout << "Lagu tidak ditemukan.\n";
    return;
  }

  removeFromIndex(node);

  node->dataLagu = dataUpdate;
  node->dataLagu.id = idLagu;

  artistIndex[dataUpdate.artist].push_back(node);
  genreIndex[dataUpdate.genre].push_back(node);

  std::cout << "Lagu berhasil diupdate.\n";
}

void MusicLibrary::hapusLagu(std::string idLagu) {
  NodeLagu *node = cariNode(idLagu);
  if (!node) {
    std::cout << "Lagu tidak ditemukan.\n";
    return;
  }

  removeFromIndex(node);

  if (node == head && node == tail) {
    head = nullptr;
    tail = nullptr;
  } else if (node == head) {
    head = node->next;
    head->prev = nullptr;
  } else if (node == tail) {
    tail = node->prev;
    tail->next = nullptr;
  } else {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  delete node;
  std::cout << "Lagu berhasil dihapus.\n";
}

void MusicLibrary::cariLagu(std::string query) {
  bool found = false;
  NodeLagu *current = head;
  std::cout << "Hasil Pencarian '" << query << "':\n";
  while (current != nullptr) {
    Song &s = current->dataLagu;
    if (s.title.find(query) != std::string::npos ||
        s.artist.find(query) != std::string::npos) {
      std::cout << "- " << s.title << " by " << s.artist << " (" << s.id
                << ") [" << s.durationMin << ":" << std::setw(2)
                << std::setfill('0') << s.durationSec << std::setfill(' ')
                << "]\n";
      found = true;
    }
    current = current->next;
  }
  if (!found)
    std::cout << "Tidak ditemukan.\n";
}

NodeLagu *MusicLibrary::getPointerLagu(std::string idLagu) {
  return cariNode(idLagu);
}

NodeLagu *MusicLibrary::getSimilarLagu(NodeLagu *currentSong) {
  if (!currentSong)
    return nullptr;

  std::string artist = currentSong->dataLagu.artist;
  if (artistIndex.find(artist) != artistIndex.end()) {
    std::vector<NodeLagu *> &list = artistIndex[artist];
    for (size_t i = 0; i < list.size(); ++i) {
      if (list[i] == currentSong) {
        if (i + 1 < list.size()) {
          return list[i + 1];
        }
        break;
      }
    }
  }

  std::string genre = currentSong->dataLagu.genre;
  if (genreIndex.find(genre) != genreIndex.end()) {
    std::vector<NodeLagu *> &list = genreIndex[genre];
    for (size_t i = 0; i < list.size(); ++i) {
      if (list[i] == currentSong) {
        if (i + 1 < list.size()) {
          return list[i + 1];
        }
        if (!list.empty() && list[0] != currentSong) {
          return list[0];
        }
      }
    }
  }

  return nullptr;
}

// IMPLEMENTASI PLAYLIST (USER)
Playlist::Playlist(std::string nama) : namaPlaylist(nama) {
  head = nullptr;
  tail = nullptr;
  currentTrack = nullptr;
}

Playlist::~Playlist() {
  NodePlaylist *current = head;
  while (current != nullptr) {
    NodePlaylist *next = current->next;
    delete current;
    current = next;
  }
}

void Playlist::tambahLaguKePlaylist(NodeLagu *pointerKeLagu) {
  if (!pointerKeLagu)
    return;

  NodePlaylist *newNode = new NodePlaylist;
  newNode->dataPtr = pointerKeLagu;
  newNode->next = nullptr;
  newNode->prev = tail;

  if (head == nullptr) {
    head = newNode;
    tail = newNode;
    currentTrack = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
  }
  std::cout << "Ditambahkan ke playlist: " << pointerKeLagu->dataLagu.title
            << "\n";
}

void Playlist::hapusLaguDariPlaylist(NodeLagu *pointerKeLagu) {
  NodePlaylist *current = head;
  while (current != nullptr) {
    if (current->dataPtr == pointerKeLagu) {
      if (current == currentTrack) {
        NodePlaylist *nextTrack = current->next ? current->next : current->prev;
        currentTrack = nextTrack;
        std::cout << "Stop playing current track.\n";
      }

      if (current == head && current == tail) {
        head = nullptr;
        tail = nullptr;
      } else if (current == head) {
        head = current->next;
        head->prev = nullptr;
      } else if (current == tail) {
        tail = current->prev;
        tail->next = nullptr;
      } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
      }
      delete current;
      std::cout << "Dihapus dari playlist.\n";
      return;
    }
    current = current->next;
  }
  std::cout << "Lagu tidak ada di playlist.\n";
}

void Playlist::tampilkanIsiPlaylist(bool showStatus) {
  std::cout << "Playlist: " << namaPlaylist << "\n";
  if (head == nullptr) {
    std::cout << "(Kosong)\n";
    return;
  }
  NodePlaylist *current = head;
  int i = 1;
  while (current != nullptr) {
    std::cout << i++ << ". " << current->dataPtr->dataLagu.title << " - "
              << current->dataPtr->dataLagu.artist << " ("
              << current->dataPtr->dataLagu.durationMin << ":" << std::setw(2)
              << std::setfill('0') << current->dataPtr->dataLagu.durationSec
              << std::setfill(' ') << ")";

    if (showStatus && current == currentTrack)
      std::cout << " [NOW PLAYING]";

    std::cout << "\n";
    current = current->next;
  }
}

void Playlist::start() {
  if (head) {
    currentTrack = head;
    play();
  } else {
    std::cout << "Playlist kosong.\n";
  }
}

void Playlist::play() {
  if (currentTrack) {
    std::cout << "Playing: " << currentTrack->dataPtr->dataLagu.title << " - "
              << currentTrack->dataPtr->dataLagu.artist << " ("
              << currentTrack->dataPtr->dataLagu.durationMin << ":"
              << std::setw(2) << std::setfill('0')
              << currentTrack->dataPtr->dataLagu.durationSec
              << std::setfill(' ') << ")\n";
  } else if (head) {
    currentTrack = head;
    std::cout << "Playing: " << currentTrack->dataPtr->dataLagu.title << " - "
              << currentTrack->dataPtr->dataLagu.artist << " ("
              << currentTrack->dataPtr->dataLagu.durationMin << ":"
              << std::setw(2) << std::setfill('0')
              << currentTrack->dataPtr->dataLagu.durationSec
              << std::setfill(' ') << ")\n";
  } else {
    std::cout << "Playlist kosong.\n";
  }
}

void Playlist::pause() {
  if (currentTrack) {
    std::cout << "Paused: " << currentTrack->dataPtr->dataLagu.title << "\n";
  } else {
    std::cout << "Tidak ada lagu yang sedang diputar.\n";
  }
}

void Playlist::stop() { std::cout << "Stopped.\n"; }

bool Playlist::next() {
  if (currentTrack && currentTrack->next) {
    currentTrack = currentTrack->next;
    play();
    return true; // Berhasil next
  } else {
    std::cout << "End of playlist.\n";
    return false; // Gagal next (sudah di ujung)
  }
}

void Playlist::prev() {
  if (currentTrack && currentTrack->prev) {
    currentTrack = currentTrack->prev;
    play();
  } else {
    std::cout << "Start of playlist.\n";
  }
}

bool Playlist::playByTitle(std::string judul) {
  NodePlaylist *current = head;
  while (current != nullptr) {
    if (current->dataPtr->dataLagu.title.find(judul) != std::string::npos) {
      currentTrack = current;
      play();
      return true;
    }
    current = current->next;
  }
  std::cout << "Lagu '" << judul << "' tidak ditemukan di playlist.\n";
  return false;
}

NodeLagu *Playlist::getCurrentTrackPointer() {
  if (currentTrack)
    return currentTrack->dataPtr;
  return nullptr;
}
