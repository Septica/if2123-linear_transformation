# Tugas Besar II IF2123 Aljabar Geometri
## Simulasi Transformasi Linier pada Bidang 2D Dengan Menggunakan OpenGL API

### Deskripsi Tugas:
Pada tugas kali ini, mahasiswa diminta membuat program yang mensimulasikan transformasi linier untuk melakukan operasi translasi, refleksi, dilatasi, rotasi, dan sebagainya pada sebuah bidang 2D. Bidang dibuat dengan mendefinisikan sekumpulan titik sudut lalu membuat bidang dari titik-titik tersebut.

Program akan memiliki dua buah window, window pertama (command prompt) berfungsi untuk menerima input dari user, sedangkan window kedua (GUI) berfungsi untuk menampilkan output berdasarkan input dari user. Kedua window ini muncul ketika user membuka file executable.

Saat program baru mulai dijalankan, program akan menerima input N, yaitu jumlah titik yang akan diterima. Berikutnya, program akan menerima input N buah titik tersebut (pasangan nilai x dan y). Setelah itu program akan menampilkan output sebuah bidang yang dibangkitkan dari titik-titik tersebut. Selain itu juga ditampilkan dua buah garis, yaitu sumbu x dan sumbu y. Nilai x dan y memiliki rentang minimal - 500 pixel dan maksikum 500 pixel. Pastikan window GUI yang Anda buat memiliki ukuran yang cukup untuk menampilkan kedua sumbu dari ujung ke ujung.

Berikutnya, program dapat menerima input yang didefinisikan pada tabel dibawah.

Input | Keterangan
-- | --
translate <dx> <dy> | Melakukan translasi objek dengan menggeser nilai x sebesar dx dan menggeser nilai y sebesar dy.
dilate <k> | Melakukan dilatasi objek dengan faktor scaling k.
rotate <deg> <a> <b> | Melakukan rotasi objek secara berlawanan arah jarum jam sebesar deg derajat terhadap titik a,b
reflect <param> | Melakukan pencerminan objek. Nilai param adalah salah satu dari nilai-nilai berikut: x, y, y=x, y=-x, atau (a,b). Nilai (a,b) adalah titik untuk melakukan pencerminan terhadap.
shear <param> <k> | Melakukan operasi shear pada objek. Nilai param dapat berupa x (terhadap sumbu x) atau y (terhadap sumbu y). Nilai k adalah faktor shear.
stretch <param> <k> | Melakukan operasi stretch pada objek. Nilai param dapat berupa x (terhadap sumbu x) atau y (terhadap sumbu y). Nilai k adalah faktor stretch.
custom <a> <b> <c> <d> | Melakukan transformasi linier pada objek dengan matriks transformasi.
multiple <n> | Melakukan transformasi linier pada objek sebanyak n kali berurutan. Setiap baris input 1..n dapat berupa translate, rotate, shear, dll tetapi bukan multiple, reset, exit.
reset | Mengembalikan objek pada kondisi awal objek didefinisikan.
exit | Keluar dari program.
  
