#include "MusicApp.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>


struct Account {
  std::string username;
  std::string password;
  std::string role;
};

// Data Dummy Akun
std::vector<Account> accounts = {{"admin", "admin123", "admin"},
                                 {"user", "user123", "user"}};

// Global Player State
NodeLagu *globalActiveSong = nullptr;
bool isPlayingFromPlaylist = false;

void clearInput() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Fungsi Login
std::string login() {
  int choice;
  std::cout << "\n=== AUTHENTICATOR ===\n";
  std::cout << "1. Admin\n";
  std::cout << "2. User\n";
  std::cout << "3. Keluar\n";
  std::cout << "Pilihan: ";
  std::cin >> choice;
  clearInput();

  if (choice == 3) {
    return "exit";
  }

  std::string targetRole = "";
  if (choice == 1) {
    targetRole = "admin";
  } else if (choice == 2) {
    targetRole = "user";
  } else {
    std::cout << "Pilihan tidak valid.\n";
    return "";
  }

  std::string u, p;
  std::cout << "\n=== LOGIN ===\n";
  std::cout << "Username: ";
  std::cin >> u;
  std::cout << "Password: ";
  std::cin >> p;

  for (const auto &acc : accounts) {
    if (acc.username == u && acc.password == p && acc.role == targetRole) {
      return acc.role;
    }
  }
  return "";
}

void showAdminMenu(MusicLibrary &lib, Playlist &myPlaylist) {
  int choice;
  do {
    std::cout << "\n=================================\n";
    std::cout << "           ADMIN DASHBOARD       \n";
    std::cout << "=================================\n";
    std::cout << "1. Tambah Lagu Baru\n";
    std::cout << "2. Tampilkan Semua Lagu\n";
    std::cout << "3. Hapus Lagu\n";
    std::cout << "4. Update Lagu\n";
    std::cout << "5. Cari Lagu\n";
    std::cout << "0. Logout\n";
    std::cout << "=================================\n";
    std::cout << "Pilihan: ";
    std::cin >> choice;
    clearInput();

    switch (choice) {
    case 1: {
      Song s;
      std::cout << "ID: ";
      std::getline(std::cin, s.id);
      std::cout << "Judul: ";
      std::getline(std::cin, s.title);
      std::cout << "Artis: ";
      std::getline(std::cin, s.artist);
      std::cout << "Album: ";
      std::getline(std::cin, s.album);
      std::cout << "Genre: ";
      std::getline(std::cin, s.genre);
      std::cout << "Tahun: ";
      std::cin >> s.year;
      std::cout << "Durasi (Menit): ";
      std::cin >> s.durationMin;
      std::cout << "Durasi (Detik): ";
      std::cin >> s.durationSec;
      lib.tambahLagu(s);
      break;
    }
    case 2:
      lib.tampilkanSemuaLagu();
      break;
    case 3: {
      std::string id;
      std::cout << "Masukkan ID Lagu yang dihapus: ";
      std::getline(std::cin, id);

      NodeLagu *ptr = lib.getPointerLagu(id);
      if (ptr) {
        myPlaylist.hapusLaguDariPlaylist(ptr);
        lib.hapusLagu(id);
      } else {
        std::cout << "Lagu tidak ditemukan.\n";
      }
      break;
    }
    case 4: {
      std::string id;
      std::cout << "Masukkan ID Lagu yang diupdate: ";
      std::getline(std::cin, id);
      if (lib.getPointerLagu(id) == nullptr) {
        std::cout << "Lagu tidak ditemukan.\n";
        break;
      }
      Song s;
      s.id = id;
      std::cout << "Judul Baru: ";
      std::getline(std::cin, s.title);
      std::cout << "Artis Baru: ";
      std::getline(std::cin, s.artist);
      std::cout << "Album Baru: ";
      std::getline(std::cin, s.album);
      std::cout << "Genre Baru: ";
      std::getline(std::cin, s.genre);
      std::cout << "Tahun Baru: ";
      std::cin >> s.year;
      std::cout << "Durasi Baru (Menit): ";
      std::cin >> s.durationMin;
      std::cout << "Durasi Baru (Detik): ";
      std::cin >> s.durationSec;
      lib.updateLagu(id, s);
      break;
    }
    case 5: {
      std::string q;
      std::cout << "Cari (Judul/Artis): ";
      std::getline(std::cin, q);
      lib.cariLagu(q);
      break;
    }
    case 0:
      std::cout << "Logging out...\n";
      break;
    default:
      std::cout << "Pilihan tidak valid.\n";
    }
  } while (choice != 0);
}

void showUserMenu(MusicLibrary &lib, Playlist &myPlaylist) {
  int choice;
  do {
    std::cout << "\n=================================\n";
    std::cout << "           USER PLAYER           \n";
    std::cout << "=================================\n";
    std::cout << "1. Lihat Library Lagu\n";
    std::cout << "2. Cari Lagu\n";
    std::cout << "3. Tambah Lagu ke Playlist\n";
    std::cout << "4. Hapus Lagu dari Playlist\n";
    std::cout << "5. Lihat Playlist Saya\n";
    std::cout << "6. Music Player Control\n";
    std::cout << "7. Play Lagu dari Playlist (By Judul)\n";
    std::cout << "0. Logout\n";
    std::cout << "=================================\n";
    std::cout << "Pilihan: ";
    std::cin >> choice;
    clearInput();

    switch (choice) {
    case 1:
      lib.tampilkanSemuaLagu();
      break;
    case 2: {
      std::string q;
      std::cout << "Cari (Judul/Artis): ";
      std::getline(std::cin, q);
      lib.cariLagu(q);
      break;
    }
    case 3: {
      std::string id;
      std::cout << "Masukkan ID Lagu: ";
      std::getline(std::cin, id);
      NodeLagu *lagu = lib.getPointerLagu(id);
      if (lagu) {
        myPlaylist.tambahLaguKePlaylist(lagu);
      } else {
        std::cout << "Lagu tidak ditemukan.\n";
      }
      break;
    }
    case 4: {
      std::string id;
      std::cout << "Masukkan ID Lagu yang akan dihapus dari playlist: ";
      std::getline(std::cin, id);
      NodeLagu *lagu = lib.getPointerLagu(id);
      if (lagu) {
        myPlaylist.hapusLaguDariPlaylist(lagu);
      } else {
        std::cout << "Lagu tidak valid.\n";
      }
      break;
    }
    case 5:
      myPlaylist.tampilkanIsiPlaylist(false);
      break;
    case 6: {
      int sub;
      std::cout << "--- Player Control ---\n";
      std::cout << "Status: "
                << (isPlayingFromPlaylist ? "Playlist Mode" : "Library Mode")
                << "\n";
      if (!isPlayingFromPlaylist && globalActiveSong) {
        std::cout << "Sedang Memutar (Library): "
                  << globalActiveSong->dataLagu.title << " ("
                  << globalActiveSong->dataLagu.durationMin << ":"
                  << std::setw(2) << std::setfill('0')
                  << globalActiveSong->dataLagu.durationSec << std::setfill(' ')
                  << ")\n";
      }

      std::cout << "1. Start (Play lagu pertama dari Playlist)\n2. Pause\n3. Play\n4. Next\n5. Prev\n6. Stop\nPilih: ";
      std::cin >> sub;

      // start (memutar lagu pertama dari playlist)
      if (sub == 1) {
        isPlayingFromPlaylist = true;
        myPlaylist.start();
      } else if (isPlayingFromPlaylist) {
        if (sub == 2)
          myPlaylist.pause();
        else if (sub == 3)
          myPlaylist.play();
        else if (sub == 4) {
          // Cek apakah next berhasil, jika tidak (end of playlist), tawarkan rekomendasi
          if (!myPlaylist.next()) {
            NodeLagu *lastTrack = myPlaylist.getCurrentTrackPointer();
            if (lastTrack) {
              NodeLagu *similar = lib.getSimilarLagu(lastTrack);
              if (similar) {
                char offer;
                std::cout << "Playlist Selesai. Putar lagu serupa: "
                          << similar->dataLagu.title << " - "
                          << similar->dataLagu.artist << "? (y/n): ";
                std::cin >> offer;
                if (offer == 'y' || offer == 'Y') {
                  // Switch ke Library Mode sementara untuk lagu ini
                  globalActiveSong = similar;
                  isPlayingFromPlaylist = false;
                  std::cout << "Memutar Rekomendasi: "
                            << globalActiveSong->dataLagu.title << " ("
                            << globalActiveSong->dataLagu.durationMin << ":"
                            << std::setw(2) << std::setfill('0')
                            << globalActiveSong->dataLagu.durationSec
                            << std::setfill(' ') << ")\n";
                }
              }
            }
          }
        } else if (sub == 5)
          myPlaylist.prev();
        else if (sub == 6)
          myPlaylist.stop();
      } else {
        if (sub == 2) {
          std::cout << "Paused (Library Mode).\n";
        } else if (sub == 3) {
          if (globalActiveSong)
            std::cout << "Sedang Memutar: " << globalActiveSong->dataLagu.title
                      << " (" << globalActiveSong->dataLagu.durationMin << ":"
                      << std::setw(2) << std::setfill('0')
                      << globalActiveSong->dataLagu.durationSec
                      << std::setfill(' ') << ")\n";
          else
            std::cout << "Tidak ada lagu yang dipilih dari library.\n";
        } else if (sub == 4) {
          NodeLagu *similar = lib.getSimilarLagu(globalActiveSong);
          if (similar) {
            globalActiveSong = similar;
            std::cout << "Memutar Lagu Mirip: "
                      << globalActiveSong->dataLagu.title << " ("
                      << globalActiveSong->dataLagu.artist << ") ["
                      << globalActiveSong->dataLagu.durationMin << ":"
                      << std::setw(2) << std::setfill('0')
                      << globalActiveSong->dataLagu.durationSec
                      << std::setfill(' ') << "]\n";
          } else {
            std::cout << "Tidak ada lagu mirip lainnya.\n";
          }
        } else if (sub == 5) {
          std::cout << "Prev tidak tersedia di mode Library (Similar).\n";
        } else if (sub == 6) {
          std::cout << "Berhenti.\n";
        }
      }
      break;
    }
    case 7: {
      std::string judul;
      std::cout << "Masukkan Judul Lagu di Playlist: ";
      std::getline(std::cin, judul);
      if (myPlaylist.playByTitle(judul)) {
        isPlayingFromPlaylist = true;
      }
      break;
    }
    case 0:
      std::cout << "Logging out...\n";
      break;
    default:
      std::cout << "Pilihan tidak valid.\n";
    }
  } while (choice != 0);
}

int main() {
  MusicLibrary lib;
  Playlist myPlaylist("Favorit Saya");

  // Seed lagu
  lib.tambahLagu({"1", "Laskar Pelangi", "Nidji", "OST Laskar Pelangi", "Pop",
                  2008, 3, 34});
  lib.tambahLagu({"2", "Hapus Aku", "Nidji", "Breakthru'", "Pop", 2006, 4, 21});
  lib.tambahLagu(
      {"3", "Separuh Aku", "Noah", "Seperti Seharusnya", "Pop", 2012, 4, 28});
  lib.tambahLagu(
      {"4", "Yang Terdalam", "Noah", "Taman Langit", "Pop", 2003, 3, 19});
  lib.tambahLagu({"5", "Kangen", "Dewa 19", "19", "Rock", 1992, 5, 12});
  lib.tambahLagu(
      {"6", "Pupus", "Dewa 19", "Cintailah Cinta", "Rock", 2002, 5, 5});
  lib.tambahLagu(
      {"7", "Hampa", "Ari Lasso", "Keseimbangan", "Pop", 2003, 4, 45});
  lib.tambahLagu(
      {"8", "Misteri Ilahi", "Ari Lasso", "Sendiri Dulu", "Pop", 2001, 3, 52});

  while (true) {
    std::string role = login();
    if (role == "exit") {
      std::cout << "Terima kasih telah menggunakan aplikasi ini.\n";
      break;
    }

    if (role == "admin") {
      std::cout << "Login Berhasil sebagai ADMIN!\n";
      showAdminMenu(lib, myPlaylist);
    } else if (role == "user") {
      std::cout << "Login Berhasil sebagai USER!\n";
      showUserMenu(lib, myPlaylist);
    } else {
      std::cout << "Login Gagal! Username atau Password salah.\n";
      char retry;
      std::cout << "Coba lagi? (y/n): ";
      std::cin >> retry;
      if (retry == 'n' || retry == 'N')
        break;
    }
  }

  return 0;
}