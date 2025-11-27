# Aplikasi Pemutar Musik_Struktur Data

# 🎵 Console Music Player (C++ ADT)

Aplikasi pemutar musik berbasis CLI (Command Line Interface) yang dibangun menggunakan bahasa C++. Proyek ini mengimplementasikan konsep **Abstract Data Types (ADT)** khususnya **Doubly Linked List** untuk manajemen lagu dan playlist.

## ✨ Fitur Utama

Aplikasi ini memiliki sistem autentikasi dengan dua peran pengguna: **Admin** dan **User**.

### 👨‍💻 Admin Features
* **CRUD Lagu:** Menambah, menampilkan, mengubah (update), dan menghapus lagu dari *Global Library*.
* **Search Engine:** Mencari lagu berdasarkan Judul atau Artis.
* **Manajemen Data:** Validasi ID lagu agar tidak duplikat.

### 🎧 User Features
* **Playlist Management:** Menambahkan lagu dari library ke playlist pribadi dan menghapusnya.
* **Playback Control:**
    * Play, Pause, Stop.
    * **Next / Previous** (Navigasi mulus menggunakan Doubly Linked List).
* **Smart Recommendation:** Ketika playlist selesai diputar, sistem otomatis menawarkan lagu lain yang **serupa** (berdasarkan artis atau genre yang sama).
* **Status Display:** Menampilkan lagu yang sedang diputar (*Now Playing*).

## 🛠️ Struktur Data (Technical Details)

Proyek ini menggunakan kombinasi struktur data untuk efisiensi:

1.  **Doubly Linked List (DLL):**
    * Digunakan pada **Music Library** dan **Playlist**.
    * Memungkinkan traversal dua arah (Next/Prev track) dengan mudah.
2.  **Hash Map / Dictionary (`std::map`):**
    * Digunakan untuk *indexing* lagu berdasarkan **Artist** dan **Genre**.
    * Mempercepat pencarian lagu serupa (*recommendation logic*).
3.  **Struct & Class:**
    * Pemisahan logika antara `MusicLibrary` (Database lagu) dan `Playlist` (Sesi user).

## 📂 Struktur File

* `main.cpp`: Entry point aplikasi, menangani menu login dan user interface utama.
* `MusicApp.h`: Header file, berisi definisi struct (`Song`, `Node`) dan prototipe class (`MusicLibrary`, `Playlist`).
* `MusicApp.cpp`: Implementasi logika dari setiap fungsi dan metode ADT.

## 🚀 Cara Menjalankan (How to Run)

Pastikan kamu memiliki compiler C++ (seperti G++).

1.  **Clone Repository**
    ```bash
    git clone [https://github.com/username-kamu/nama-repo.git](https://github.com/username-kamu/nama-repo.git)
    cd nama-repo
    ```

2.  **Compile Program**
    Compile ketiga file sekaligus:
    ```bash
    g++ main.cpp MusicApp.cpp -o musicplayer
    ```

3.  **Jalankan Aplikasi**
    * Windows:
        ```bash
        musicplayer.exe
        ```

## 🔐 Akun Demo (Credentials)

Gunakan akun berikut untuk masuk ke aplikasi:

| Role  | Username | Password |
| :--- | :--- | :--- |
| **Admin** | `admin` | `admin123` |
| **User** | `user` | `user123` |

## 📝 Catatan Pengembang
Proyek ini dibuat untuk memenuhi tugas Struktur Data dan Algoritma, mendemonstrasikan pemahaman tentang pointer, manajemen memori dinamis, dan operasi linked list.

---
*Created by Kelompok 5:
FARREL LABIB ALHAIDAR (103132400009)
ARDIAN NAFIS SAMUDRA (103132400012)
AHNAF ARIACHEDA (103132400037)
