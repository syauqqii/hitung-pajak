/*
	-------------------------------------------------
	[#] App Hitung Pajak :
	-------------------------------------------------
	
	[#] Lapisan Pajak :
	-------------------------------------------------
		- Lapis 1:   0 - 60jt      (05%) 
		- Lapis 2: > 60jt - 250jt  (15%)
		- Lapis 3: > 250jt - 500jt (25%)
		- Lapis 4: > 500jt - 5m    (30%)
		- Lapis 5: > 5m            (35%)
	-------------------------------------------------
	
	[#] PTKP : 
	-------------------------------------------------
		[!] Info :
			- 1 Tanggungan : 4.500.000
	-------------------------------------------------
		[+] Tidak kawin :
			- TK0 : 54.000.000
			- TK1 : 58.500.000
			- TK2 : 63.000.000
			- TK3 : 67.500.000
	-------------------------------------------------
		[+] Kawin :
			- K0 : 58.500.000
			- K1 : 63.000.000
			- K2 : 67.500.000
			- K3 : 72.000.000
	-------------------------------------------------
		[+] Kawin, Penghasilan Suami Istri digabung :
			- K/I/0 : 112.500.000
			- K/I/1 : 117.000.000
			- K/I/2 : 121.500.000
			- K/I/3 : 126.000.000
	-------------------------------------------------
*/

// =========================================
// Area Import library
// =========================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

// =========================================
// Area Import library bersyarat
// =========================================
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// =========================================
// Area Deklarasi function
// =========================================
void clear_screen();
void check_input();
void format_angka();
void menu();

// =========================================
// Area main() program
// =========================================
int main(){
	// Panggil function clear_screen
	clear_screen();
	
	// Panggil function menu
	menu(1);

	return 0;
}

// =========================================
// Area function clear_screen()
// =========================================
void clear_screen(){
	// Untuk bersihkan konsol
	// Command cmd / terminal
	system("@cls||clear");
}

// =========================================
// Area function check_input
// =========================================
void check_input(int input, int opsi){
	
	// Untuk cek input menu
	if(opsi == 1){
		
		if(input >= 0 && input < 10){
			
			// Lanjut..
			
		} else {
			
			menu(0);
			
		}
		
	} // Untuk cek input tanggungan
	else if(opsi == 2){
		
		if(input >= 0 && input <= 3){
			
			// Lanjut..
			
		} else {
			
			menu(2);
			
		}
		
	}
	
}

// =========================================
// Area function format_angka()
// =========================================
void format_angka(long long int angka){
	// Jika parameter angka < 0 / negatif, maka tampilkan negatif
	if(angka < 0){
		printf("-");
		format_angka(-angka);
		return;
	} // JIka parameter kurang dari 1000, atau bisa di sebut > 0 - 99,
	// Maka tampilkan langusung tanpa di beri format . (titik)
	else if(angka < 1000){
		printf("%lld", angka);
		return;
	}
	
	// Rekrusif mengembalikan nilai angka dengan di bagi 1000
	format_angka(angka / 1000);
	
	// Print hasil dengan format
	printf(".%03lld", angka % 1000);
	
}

// =========================================
// Area function menu()
// =========================================
void menu(int option){
	// Deklarasi input menu awal
	int input_pilihan_menu; // Pilih menu diawal
	
	// Deklarasi hitung ulang / exit
	char menu_exit;
	
	// Deklarasi variabel penting
	long long int penghasilan, pajak; // Untuk input jumlah penghasilan, pajak
	long long int lapis_1, lapis_2, lapis_3, lapis_4, lapis_5; // Lapisan pajak
	long long int ptkp, pkp; // Untuk mengetahui berapa penghasilan tidak kena pajak dan kena pajak
	
	// Deklarasi untuk keperluan perhitungan PTKP
	char status_pernikahan; // Sudah nikah atau belum
	char status_penghasilan; // Jika sudah nikah -> penghasilan digabung?
	int jumlah_tanggungan, ulangi; // Jumlah yang ditanggung
	char temp_pernikahan[500];
	char temp_penghasilan[500];
	
	for(ulangi = 0; ulangi < 500; ulangi++){
		temp_pernikahan[ulangi]  = '\0';
		temp_penghasilan[ulangi] = '\0';
	}
	
	// Menu awal -> menu tidak tersedia (handle error)
	if(option == 0){
		
		clear_screen();
		
		printf("\n  [#] Error: Menu Tidak Tersedia!\n");
		
		sleep(1);
		exit(0);
		
	} // Menu awal -> halaman utama
	else if(option == 1){
		
		clear_screen();
		
		printf("\n [#] Program Menghitung Pajak\n\n");
		printf("  [1] Hitung Pajak\n");
		printf("  [2] Keluar dari Program\n\n");
		
		printf("  [>] Pilih Menu : ");
		scanf("%d", &input_pilihan_menu);
		
		check_input(input_pilihan_menu, 1);
		
		if(input_pilihan_menu == 1){
			menu(2);
		} else if(input_pilihan_menu == 2){
			menu(9);
		}else{
			menu(0);
		}
		
	} // Menu awal -> proses penghitungan pajak
	else if(option == 2){
		
		clear_screen();
		
		printf("\n [#] Program Menghitung Pajak\n\n");
		
		printf("  [>] Apakah anda sudah nikah? (y/n) ");
		scanf(" %c", &status_pernikahan);
		
		status_pernikahan = toupper(status_pernikahan);
		
		// Hitung PTKP -> nikah
		if(status_pernikahan == 'Y'){
			
			strcat(temp_pernikahan, "Iya");
			
			printf("  [>] Apakah penghasilan anda digabung? (y/n) ");
			scanf(" %c", &status_penghasilan);
			
			status_penghasilan = toupper(status_penghasilan);
			
			// Hitung PTKP -> nikah -> digabung
			if(status_penghasilan == 'Y'){
				
				strcat(temp_penghasilan, "Iya");
				
				ptkp = 112500000;
				
				printf("  [>] Berapa jumlah tanggungan anda? (0-3) ");
				scanf(" %d", &jumlah_tanggungan);
				
				check_input(jumlah_tanggungan, 2);
				
				for(ulangi = 0; ulangi < jumlah_tanggungan; ulangi++){
					
					ptkp += 4500000;
					
				}
				
			} // Hitung PTKP -> nikah -> tidak digabung
			else if(status_penghasilan == 'N'){
				
				strcat(temp_penghasilan, "Tidak");
				
				ptkp = 58500000;
				
				printf("  [>] Berapa jumlah tanggungan anda? (0-3) ");
				scanf(" %d", &jumlah_tanggungan);
				
				check_input(jumlah_tanggungan, 2);
				
				for(ulangi = 0; ulangi < jumlah_tanggungan; ulangi++){
					
					ptkp += 4500000;
					
				}
				
			} // Hitung PTKP -> nikah -> handle error input
			else {
				
				menu(2);
				
			}
			
		} // Hitung PTKP -> tidak nikah
		else if(status_pernikahan == 'N'){
			
			strcat(temp_pernikahan, "Tidak");
			strcat(temp_penghasilan, "Tidak");
			
			ptkp = 54000000;
			
			printf("  [>] Berapa jumlah tanggungan anda? (0-3) ");
			scanf(" %d", &jumlah_tanggungan);
			
			check_input(jumlah_tanggungan, 2);
			
			for(ulangi = 0; ulangi < jumlah_tanggungan; ulangi++){
			
				ptkp += 4500000;
				
			}
			
		} // Hitung PTKP -> handle error input
		else {
			
			menu(2);
			
		}
		
		clear_screen();
		
		printf("\n [#] Program Menghitung Pajak\n\n");
		
		printf("  [>] PTKP anda            : Rp "); format_angka(ptkp);
		printf("\n  [>] Masukkan Penghasilan : Rp ");
		scanf("%lld", &penghasilan);
		
		pkp = penghasilan - ptkp;
		
		// Lapis 1 : 0 - 60jt
		if(pkp > 0 && pkp <= 60000000){
			
			lapis_1 = pkp * 0.05;
			
			pajak   = lapis_1;
			
		} // Lapis 2 : > 60jt - 250jt
		else if(pkp > 60000000 && pkp <= 250000000){
			
			lapis_1 = 60000000 * 0.05;
			
			lapis_2 = (pkp - 60000000) * 0.15;
			
			pajak   = lapis_1 + lapis_2;
			
		} // Lapis 3 : > 250jt - 500jt
		else if(pkp > 250000000 && pkp <= 500000000){
			
			lapis_1 = 60000000 * 0.05;
			lapis_2 = (250000000 - 60000000) * 0.15;
			
			lapis_3 = (pkp - 250000000) * 0.25;
			
			pajak   = lapis_1 + lapis_2 + lapis_3;
			
		} // Lapis 4 : > 500jt - 5m
		else if(pkp > 500000000 && pkp <= 5000000000){
			
			lapis_1 = 60000000 * 0.05;
			lapis_2 = (250000000 - 60000000) * 0.15;
			lapis_3 = (500000000 - 250000000) * 0.25;
			
			lapis_4 = (pkp - 500000000) * 0.3;
			
			pajak   = lapis_1 + lapis_2 + lapis_3 + lapis_4;
			
		} // Lapis 5 : > 5m
		else if(pkp > 5000000000){
			
			lapis_1 = 60000000 * 0.05;
			lapis_2 = (250000000 - 60000000) * 0.15;
			lapis_3 = (500000000 - 250000000) * 0.25;
			lapis_4 = (5000000000 - 500000000) * 0.3;
			
			lapis_5 = (pkp - 5000000000) * 0.35;
			
			pajak = lapis_1 + lapis_2 + lapis_3 + lapis_4 + lapis_5;
			
		} // Jika hasil minus, maka tidak wajib pajak
		else {
			
			clear_screen();
			
			printf("\n [>] Anda tidak wajib pajak!\n");
			
			sleep(3);
			
			clear_screen();
			
			printf("           [ LAPORAN PAJAK ]\n");
			printf(" ---------------------------------------\n");
			printf(" [>] Status Pajak : Tidak Wajib Pajak\n");
			printf(" ---------------------------------------\n");
			printf(" [>] Status Pernikahan     : %s\n", temp_pernikahan);
			printf(" [>] Penghasilan di Gabung : %s\n", temp_penghasilan);
			printf(" [>] Jumlah Tanggungan     : %d\n", jumlah_tanggungan);
			printf(" ---------------------------------------");
			printf("\n [>] Penghasilan : Rp "); format_angka(penghasilan);
			printf("\n ---------------------------------------");
			printf("\n [>] PTKP : Rp "); format_angka(ptkp);
			printf("\n [>] PKP  : Rp 0");
			printf("\n ---------------------------------------");
			printf("\n [>] Total Pajak       : Rp 0");
			printf("\n [>] Peghasilan Bersih : Rp "); format_angka(penghasilan);
			printf("\n ---------------------------------------");
			
			menu_exit = '\0';
			
			printf("\n [?] Keluar Program? (y/n) ");
			scanf(" %c", &menu_exit);
			
			menu_exit = toupper(menu_exit);
			
			if(menu_exit == 'Y'){
			
				menu(9);
				
			} else if(menu_exit == 'N'){
				
				menu(1);
				
			} else {
				
				menu(2);
				
			}
			
		}
		
		clear_screen();
		
		printf("           [ LAPORAN PAJAK ]\n");
		printf(" ---------------------------------------\n");
		printf(" [>] Status Pajak : Wajib Pajak\n");
		printf(" ---------------------------------------\n");
		printf(" [>] Status Pernikahan     : %s\n", temp_pernikahan);
		printf(" [>] Penghasilan di Gabung : %s\n", temp_penghasilan);
		printf(" [>] Jumlah Tanggungan     : %d\n", jumlah_tanggungan);
		printf(" ---------------------------------------");
		printf("\n [>] Penghasilan : Rp "); format_angka(penghasilan);
		printf("\n ---------------------------------------");
		printf("\n [>] PTKP : Rp "); format_angka(ptkp);
		printf("\n [>] PKP  : Rp "); format_angka(pkp);
		printf("\n ---------------------------------------");
		printf("\n [>] Total Pajak       : Rp "); format_angka(pajak);
		printf("\n [>] Peghasilan Bersih : Rp "); format_angka(penghasilan - pajak);
		printf("\n ---------------------------------------");
		
		menu_exit = '\0';
		
		printf("\n [?] Keluar Program? (y/n) ");
		scanf(" %c", &menu_exit);
		
		menu_exit = toupper(menu_exit);
		
		if(menu_exit == 'Y'){
			
			menu(9);
			
		} else if(menu_exit == 'N'){
			
			menu(1);
			
		} else {
			
			menu(2);
			
		}
		
	} // Menu awal -> keluar program
	else if(option == 9){
		
		clear_screen();
		
		printf("\n [#] Keluar Program\n");
		
		sleep(1);
		exit(0);
		
	}
	
}
