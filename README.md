# Tugas Besar IF2224 - Teori Bahasa Formal dan Automata

### Identitas Kelompok

Kelompok std_abs
Kode ABS
| NIM | Nama |
|-----|------|
| 13524115 | Ega Luthfi Rais |
| 13524134 | Salman Faiz Assidqi |
| 13524141 | Ahmad Fauzan Putra |
| 13524146 | Leonardus Brain Fatolosja |

### Deskripsi Program

Program ini merupakan implementasi Lexical Analyzer berbasis Deterministic Finite Automata (DFA) untuk bahasa Arion. Lexer membaca source code dari file teks karakter per karakter, melakukan transisi state sesuai DFA, dan menghasilkan daftar token yang sesuai.
### Struktur Direktori

bin/            binary
src/            Source code
doc/            Laporan
test/           File input dan output pengujian
  milestone-1/  Pengujian milestone 1


### Requirements

- g++ dengan C++17
- GNU Make

### Cara Instalasi dan Penggunaan Program ###

### Build

(bash)
make clean           
make       


### Penggunaan

(bash)
./bin/lexer <file_input.txt>                # Output ke terminal
./bin/lexer <file_input.txt> <output.txt>   # Output ke file


Contoh:
(bash)
./bin/lexer test/milestone-1/input-1.txt
./bin/lexer test/milestone-1/input-1.txt test/milestone-1/output-1.txt


### Pembagian Tugas

| Nama | Pembagian Tugas | Kontribusi |
|------|----------------|------------|
| Ega Luthfi Rais | Project Manager, Inisiasi GitHub, Design struktur GitHub, Assist Design dan Implementasi DFA | 25% |
| Salman Faiz Assidqi | Laporan (Implementasi DFA) dan debugging  | 25% |
| Ahmad Fauzan Putra | Implementasi DFA (token.hpp dan token.cpp), pengujian | 25% |
| Leonardus Brain Fatolosja | Pembuatan DFA, Laporan (Teori singkat dan Penjelasan DFA) | 25% |
