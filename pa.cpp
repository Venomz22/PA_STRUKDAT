#include <bits/stdc++.h>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <conio.h>
#include <math.h>
#include <fstream>
using namespace std;

//fungsi untuk mengelola tata letak output pada cli melalui koordinat x dan y
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition; 
void gotoXY(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console,CursorPosition); 
}

void color(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

struct akun {
	string username;
	string password;
	string mode;
};

struct bill {
	int no;
	
	string user;
	int jam;
	int harga;
};

struct porsi{
	string user;
	int porsi;
	string makanan;
	int harga;
	string status;
};

struct kantin{
	int id;
	string makanan;
	int harga;
};

struct node {
	bill data;
	node* next;
	node* prev;
};

struct nodekantin{
	kantin data;
	nodekantin* prev;
	nodekantin* next;
};

struct nodeporsi{
	porsi data;
	nodeporsi* next;
	nodeporsi* prev;
};

akun acc[1000];
int jumakun;
int jumpc;
int jumkantin;
int item1;
int t;
string makanan;
string user;
string harga;
string att;
string usr;
string src;

//fungsi untuk menampilkan data struct
void tampil2(node* tmp, int i) {
	if(i%2 == 0){
			gotoXY(0, i*10+0); cout << "+----------+";
			gotoXY(0, i*10+1); cout << "|          |";
			gotoXY(0, i*10+2); cout << "|          |";
			gotoXY(0, i*10+3); cout << "|          |";
			gotoXY(0, i*10+4); cout << "+----------+";
			gotoXY(0, i*10+5); cout << "   /___\\";
		gotoXY(0, i*10+6); cout << tmp->data.no << ".  ";
		if(tmp->data.user == "NULL"){
			cout << "IDLE";
		} else
			cout << tmp->data.user;
		gotoXY(0, i*10+7); cout << tmp->data.harga << "/jam";
		gotoXY(0, i*10+8); cout << "Sisa pemakaian (jam): " << tmp->data.jam;
	}
	
	
	if(i%2 == 1){
		i -= 1;
			gotoXY(30, i*10+0); cout << "+----------+";
			gotoXY(30, i*10+1); cout << "|          |";
			gotoXY(30, i*10+2); cout << "|          |";
			gotoXY(30, i*10+3); cout << "|          |";
			gotoXY(30, i*10+4); cout << "+----------+";
			gotoXY(30, i*10+5); cout << "   /___\\";
		gotoXY(30, i*10+6); cout << tmp->data.no << ".  ";
		if(tmp->data.user == "NULL"){
			cout << "IDLE";
		} else
			cout << tmp->data.user;
		gotoXY(30, i*10+7); cout << tmp->data.harga << "/jam";
		gotoXY(30, i*10+8); cout << "Sisa pemakaian (jam): " << tmp->data.jam;
	}
	
}

//fungsi untuk menampilkan data struct
void tampil3(nodekantin* tmp, int i){
	cout << "  " << tmp->data.id << ". "
		 << tmp->data.makanan << "   " 
		 << tmp->data.harga << endl;
}

//fungsi untuk menampilkan data struct
void tampil4(nodeporsi* tmp, int i){
	cout << string(40, '-') << endl;
	cout << "Nama Pemesan: " << tmp->data.user << endl;
	cout << tmp->data.makanan << endl;
	cout << "Porsi: " << tmp->data.porsi << endl;
	cout << "Harga Total: " << tmp->data.harga << endl;
	cout << "Status Pesanan: " << tmp->data.status << endl;
	cout << string(40, '-') << endl;
}

//fungsi menampilkan semua tiket yang tersedia
void tampil(node* head, int* indeks){
	int i=0;
	node* tmp3 = head;
	while (tmp3 != NULL){
		tampil2(tmp3, i);
		tmp3 = tmp3->next;
		i++;
	}
}

void pilihkantin(nodekantin* headkantin, int* indeks, nodeporsi** porsihead, nodeporsi** porsitail, string username) {
	nodekantin* tmp = headkantin;
	bool run = 1; int item = 1, porsi;
	while(run){
		
		system("cls");
		cout << "   +-------------------------------+" << endl;
		cout << "   |          DAFTAR MENU          |" << endl;
		cout << "   +-------------------------------+" << endl;
		gotoXY(0, 3); cout << "   _________________________________";
		gotoXY(0, 4); cout << "   |" << tmp->data.makanan; gotoXY(35, 4); cout << "|";
		gotoXY(0, 5); cout << "<< |                               | >>";
		gotoXY(0, 6); cout << "   |" << tmp->data.harga; gotoXY(35, 6); cout << "|";
		gotoXY(0, 7); cout << "   |_______________________________|";
		gotoXY(0, 8);cout << "pilih";
		gotoXY(0, 9);cout << "kembali";
		
		color(240);
		if(item == 1){
			gotoXY(0, 8);cout << "pilih";
		} else if(item == 2){
			gotoXY(0, 9);cout << "kembali";
		}color(7);
		
		system("pause>nul");
		if(GetAsyncKeyState(VK_RIGHT) && tmp->next != NULL){ 
			tmp = tmp->next;
		}
		if(GetAsyncKeyState(VK_LEFT) && tmp->prev != NULL){ 
			tmp = tmp->prev;
		}
		if(GetAsyncKeyState(VK_UP) && item != 1){
			item -= 1;
		}
		if(GetAsyncKeyState(VK_DOWN) && item != 2){
			item += 1;
		}		
		if(GetAsyncKeyState(VK_RETURN) & 0x8000){
			switch(item){
				case 1:
					if(username == "N/A"){
						gotoXY(0, 10);cout << "Anda belum login!";
						Sleep(500);
						
						return;
					} else{
					gotoXY(0, 10);cout << "Masukkan Jumlah Porsi: ";
					cin >> porsi;
					
					nodeporsi* p = new nodeporsi;
					p->data.harga = tmp->data.harga * porsi;
					p->data.makanan = tmp->data.makanan;
					p->data.porsi = porsi;
					p->data.user = username;
					p->data.status = "belum";
					
					if(*porsihead == NULL){
						p->prev = NULL;
						p->next = NULL;
						*porsihead = p;
						*porsitail = p;
						(*porsitail)->prev = *porsitail;
					} else {
						(*porsitail)->next = p;
						p->prev = *porsitail;
						*porsitail = p;
						p->next = NULL;
					}
				
					cout << endl << 
					"Terima Kasih Sudah Memesan, silahkan tunggu pesanan anda!"; Sleep(500);					
					}
				case 2:
					return;
			}
		}	
	}	
}

void regis(string* mode, string* username) {
	
	cin.ignore();
	string nama, pw, pw2;
	system("CLS");
	int item2 = 1, running = true;
	u:
	while(running) {
		gotoXY(0, 0); cout << "+-------------------------------+";
		gotoXY(0, 1); cout << "|          	REGIS		       |";
		gotoXY(0, 2); cout << "+-------------------------------+";
		gotoXY(0, 3); cout << "Username            :";
		gotoXY(0, 4); cout << "Password            :";
		gotoXY(0, 5); cout << "Konfirmasi Password :";
		gotoXY(0, 6); cout << "Regis";
		gotoXY(0, 7); cout << "Kembali";
		gotoXY(0, 8); cout << "+-------------------------------+";
		color(240);
		if(item2 == 1){
			gotoXY(0, 3); cout << "Username ";
		} else if(item2 == 2){
			gotoXY(0, 4); cout << "Password ";
		} else if(item2 == 3){
			gotoXY(0, 5); cout << "Konfirmasi Password ";
		} else if(item2 == 4){
			gotoXY(0, 6); cout << "Regis";
		} else if(item2 == 5){
			gotoXY(0, 7); cout << "Kembali";
		} color(7); gotoXY(0,0);
		system("pause>nul");
		if(GetAsyncKeyState(VK_UP) && item2 != 1) {
			item2 -= 1;
		}
		if(GetAsyncKeyState(VK_DOWN) && item2 != 5){
			item2 += 1;
		}
		if(GetAsyncKeyState(VK_RETURN) & 0x8000){
			if(item2 == 1){
				gotoXY(23, 3); getline(cin, nama);
			} else if(item2 == 2){
				gotoXY(23, 4); getline(cin, pw);
			} else if(item2 == 3){
				gotoXY(23, 5); getline(cin, pw2);
			} else if(item2 == 4){
				if((nama == "" || pw == "") || pw2 == "") {
					gotoXY(0, 9); cout << "Isi data dengan Lengkap!   " << endl;
					goto u;
				}
				int run = 0;
				int i=0;
				for(; i<jumakun; i++){
					if(acc[i].username == nama) {
						run = 1;
						break;
					}
					run = 0;
				}
				if(run) {
					gotoXY(0, 9); cout << "Username sudah digunakan!   " << endl;
					goto u;
				}
				else if(pw != pw2){
					gotoXY(0, 9); cout << "Konfirmasi kata sandi salah!" << endl;
					goto u;
				} else {
					gotoXY(0, 9);     cout << "Registrasi Berhasil!         "  << endl;Sleep(500);
					acc[jumakun].username = nama;
					acc[jumakun].password = pw;
					acc[jumakun].mode = "user";
					jumakun++;
					*mode = "user";
					*username = nama;
					return;
				}
			} else if(item2 == 5){
				return;
			}
		}
	}
	
//	int run = 0;
//	do{ 
//		cout << "\nMasukkan Username Anda : "; getline(cin, nama);
//		int i=0;
//		for(; i<jumakun; i++){
//			if(acc[i].username == nama) {
//				run = 1;
//				break;
//			}
//			run = 0;
//		}
//		if(run) cout << "Username sudah digunakan!" << endl;
//	} while(run);
//	
//	cout << "Masukkan Kata Sandi : "; getline(cin, pw);
//	cout << "Konfirmasi Kata Sandi : "; getline(cin, pw2);
//	while(pw != pw2){
//		cout << "Konfirmasi kata sandi salah!" << endl;
//		cout << "Konfirmasi Kata Sandi : "; getline(cin, pw2);
//	}
//	cout << "Registrasi Berhasil!"  << endl;Sleep(500);
//	acc[jumakun].username = nama;
//	acc[jumakun].password = pw;
//	acc[jumakun].mode = "user";
//	jumakun++;
//	*mode = "user";
//	*username = nama;
}

//fungsi login untuk beralih ke admin maupun user
void login(string* mode, string* username) {
	cin.ignore();
	bool run = true;
	int item2;
	string nama, pw;
	while(run){
		gotoXY(0, 0); cout << "+-------------------------------+";
		gotoXY(0, 1); cout << "|          	LOGIN		       |";
		gotoXY(0, 2); cout << "+-------------------------------+";
		gotoXY(0, 3); cout << "Username :";
		gotoXY(0, 4); cout << "Password :";
		gotoXY(0, 5); cout << "Konfirmasi";
		gotoXY(20, 5); cout << "Kembali";
		gotoXY(0, 6); cout << "+-------------------------------+";
		color(240);
		if(item2 == 1){
			gotoXY(0, 3); cout << "Username :";
		} else if(item2 == 2){
			gotoXY(0, 4); cout << "Password :";
		} else if(item2 == 3){
			gotoXY(0, 5); cout << "Konfirmasi";
		} else if(item2 == 4){
			gotoXY(20, 5); cout << "Kembali";
		} color(7); gotoXY(0,0);
		system("pause>nul");
		if(GetAsyncKeyState(VK_UP) && item2 != 1){ 
			item2 -= 1;
		}
		if(GetAsyncKeyState(VK_DOWN) && item2 != 4){ 
			item2 += 1;
		}
		if(GetAsyncKeyState(VK_RETURN) & 0x8000){
			if(item2 == 1){
				gotoXY(15, 3); getline(cin, nama); fflush(stdin);
			} else if(item2 == 2){
				gotoXY(15, 4); getline(cin, pw); fflush(stdin);
			} else if(item2 == 3){
				int i=0;
				for(; i<jumakun; i++){
					if(acc[i].username == nama) break;
				}
				if(i>=jumakun){
					gotoXY(0, 7); cout << "Username tidak terdaftar, silahkan registrasi terlebih dahulu" << endl;
					*username = "N/A";
					Sleep(800);
					continue;
				}
				if(pw == acc[i].password) {
					gotoXY(0, 7); cout << "Login Berhasil, Selamat Datang!" << endl;
					*mode = acc[i].mode;
					*username = acc[i].username;
					Sleep(500);
					return;
				} else {
					gotoXY(0, 7); cout << "Password salah!" << endl;
					Sleep(500);
					continue;
				}
			} else if(item2 == 4){
				return;
			}
		}
	}
}

void pilihpc(string username, node* head) {
	int no, jam; string nama = username;
	cout << "--------------------" << endl;
	cout << "| Masukkan nomor PC: "; cin >> no;
	cout << "| Masukkan jam: "; cin >> jam;
	node* tmp = head;
	int i=1;
	while(i<no){
		tmp = tmp->next;
		i++;		
	}
	if(tmp->data.user == "NULL"){
		tmp->data.user = nama;
		tmp->data.jam = jam;
		tampil2(tmp, i);
	} else {
		cout << "PC Masih digunakan!";
	}
}

void tampilkantin(nodekantin* headkantin, int* indeks){
	
	cout << "+-------------------------------+" << endl;
	cout << "|          DAFTAR MENU          |" << endl;
	cout << "+-------------------------------+" << endl;
	int i=0;
	nodekantin* tmp3 = headkantin;
	while (tmp3 != NULL){
		tampil3(tmp3, i);
		tmp3 = tmp3->next;
		i++;
	}	
}

void pilihmakan(string username, nodekantin* kantinhead, nodeporsi** porsihead, nodeporsi** porsitail) {
	int no, porsi;
	cout << "Masukkan nomor menu: "; cin >> no;
	cout << "Masukkan porsi: "; cin >> porsi;
	nodekantin* tmp = kantinhead;
	int i=1;
	while(i<no){
		tmp = tmp->next;
		i++;		
	}
	tampil3(tmp, i);
	
	nodeporsi* p = new nodeporsi;
	p->data.harga = tmp->data.harga * porsi;
	p->data.makanan = tmp->data.makanan;
	p->data.porsi = porsi;
	p->data.user = username;
	p->data.status = "belum";
	
	if(*porsihead == NULL){
		p->prev = NULL;
		p->next = NULL;
		*porsihead = p;
		*porsitail = p;
		(*porsitail)->prev = *porsitail;
	} else {
		(*porsitail)->next = p;
		p->prev = *porsitail;
		*porsitail = p;
		p->next = NULL;
	}

	cout << endl << 
	"Terima Kasih Sudah Memesan, silahkan tunggu pesanan anda!"; Sleep(500);
}

int tagihan(string username, node* head, int* indeks, nodeporsi* headporsi){
	int i=0; int total = 0;
	node* tmp3 = head;
	while (tmp3 != NULL){
		if(tmp3->data.user == username){
			total += tmp3->data.harga * tmp3->data.jam;
			tampil2(tmp3, i);
		}
		tmp3 = tmp3->next;
		i++;
	}

	nodeporsi* tmp4 = headporsi;

	while (tmp4 != NULL){
		if(tmp4->data.user == username && tmp4->data.status == "Sudah"){
			total += tmp4->data.harga;
			tampil4(tmp4, i);
		}
		tmp4 = tmp4->next;
		i++;
	}
	return total;
}

//fungsi untuk mengisi data awal pada linked list
void awal(node** head, node** tail, int* i, nodekantin** kantinhead, nodekantin** kantintail) {
	node* n = new node;
	
	n->data.no = 5;
	n->data.user = "NULL";
	n->data.jam = 0;
	n->data.harga = 5000;

	n->next = *head;
	n->prev = NULL;
	*head = n;
	*tail = n;
	
	nodekantin* m = new nodekantin;
	
	m->data.id = 5;
	m->data.makanan = "Nasi Goreng";
	m->data.harga = 5000;

	m->next = *kantinhead;
	m->prev = NULL;
	*kantinhead = m;
	*kantintail = m;

	
	*i += 1;
	
	n = new node;
	n->data.no = 4;
	n->data.user = "NULL";
	n->data.jam = 0;
	n->data.harga = 4000;

	n->next = *head;
	n->prev = NULL;
	(*head)->prev = n;
	*head = n;

	m = new nodekantin;
	m->data.id = 4;
	m->data.makanan = "nasi padang";
	m->data.harga = 4000;

	m->next = *kantinhead;
	m->prev = NULL;
	(*kantinhead)->prev = m;
	*kantinhead = m;
	
	*i += 1;	
	
	n = new node;
	n->data.no = 3;
	n->data.user = "NULL";
	n->data.jam = 0;
	n->data.harga = 3000;

	n->next = *head;
	n->prev = NULL;
	(*head)->prev = n;
	*head = n;

	m = new nodekantin;
	m->data.id = 3;
	m->data.makanan = "ayam geprek";
	m->data.harga = 9000;

	m->next = *kantinhead;
	m->prev = NULL;
	(*kantinhead)->prev = m;
	*kantinhead = m;

	*i += 1;
	
	n = new node;
	n->data.no = 2;
	n->data.user = "NULL";
	n->data.jam = 0;
	n->data.harga = 4500;

	n->next = *head;
	n->prev = NULL;
	(*head)->prev = n;
	*head = n;
	
	m = new nodekantin;
	m->data.id = 2;
	m->data.makanan = "mie goreng";
	m->data.harga = 18000;

	m->next = *kantinhead;
	m->prev = NULL;
	(*kantinhead)->prev = m;
	*kantinhead = m;
	
	*i += 1;
	
	n = new node;
	n->data.no = 1;
	n->data.user = "NULL";
	n->data.jam = 0;
	n->data.harga = 6000;

	n->next = *head;
	n->prev = NULL;
	(*head)->prev = n;
	*head = n;
	
	m = new nodekantin;
	m->data.id = 1;
	m->data.makanan = "es teh";
	m->data.harga = 3000;

	m->next = *kantinhead;
	m->prev = NULL;
	(*kantinhead)->prev = m;
	*kantinhead = m;
	
	*i += 1;
}

void bayar(int tot, nodeporsi** porsihead, string username, node** head) {
	if(tot == 0){
		cout << "Anda tidak memiliki tagihan!\n";
		Sleep(500);
		return;
	}
	int a=-1;
	cout << "\nMasukkan nominal pembayaran: "; cin >> a;
	while(a < tot){
		cout << "\nUang anda tidak cukup! ";
		cout << "\nMasukkan nominal pembayaran: "; cin >> a;
	}
	if(a>tot)cout << "\nKembalian Anda: Rp." << a-tot << endl;
	Sleep(500);
	
	
	int i = 0;
	node* tmp = *head;
	while(tmp != NULL){
		if(tmp->data.user == username){
			tmp->data.user = "NULL";
			tmp->data.jam = 0;
		}
		tmp = tmp->next;
	}
	
	
	nodeporsi* tmp2 = *porsihead;
	while(tmp2 != NULL){
		if(tmp2->data.user == username && tmp2->data.status == "Sudah"){
			*porsihead = tmp2->next;
			if(*porsihead != NULL)
			(*porsihead)->prev = NULL;
		} else {
			break;
		}
		tmp2=tmp2->next;
	}
	
	while(tmp2 != NULL){
		if(tmp2->data.user == username && tmp2->data.status == "Sudah"){
			if(tmp2->next != NULL)
				tmp2->next->prev = tmp2->prev;
			if(tmp2->prev != NULL)
				tmp2->prev->next = tmp2->next;	
		}
		tmp2=tmp2->next;
	}
}

void daftarakun(node* head, nodeporsi* porsihead, int* indeks){
	int t;
	for(int i=0; i<jumakun; i++){
		cout << i+1 << ".\n";
		cout << string(40, '-') << endl;
		cout << "Nama Pengguna: " << acc[i].username << endl;
		cout << "Status: " << acc[i].mode << endl;
		t = tagihan(acc[i].username, head, indeks, porsihead);
		cout << "Tagihan: " << t << endl;
		cout << string(40, '-') << endl;
	}
}

void tambahpc(node** head, node** tail, int* indeks) {
	node* n = new node;
	int jumlah, posisi;
	string line;
	while(cout<<"Berapa banyak data tiket yang anda ingin tambahkan?\n" && !(cin >> jumlah)){
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout<<"Masukkan tipe angka!"<<endl;
	}
	system("CLS");
	while(cout<<"Di posisi berapa anda ingin menambahkan data?\n" && !(cin >> posisi)){
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout<<"Masukkan tipe angka!"<<endl;
	}
	if(posisi > *indeks+1 || posisi <= 0){
		cout << "Indeks diluar jangkauan!"; Sleep(1000);
		system("CLS");
		return;
	}
	
	node* head2 = NULL; node* tail2 = NULL;
	
	for (int i=*indeks+1; i<*indeks+jumlah+1; i++){
		n = new node;	
		cout<<"Data ke "<<i<<endl;
		n->data.no = i;
		int ss;
		while(cout<<"\tHarga per jam:  "  && !(cin>>ss)){
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout<<"Masukkan tipe angka!"<<endl;
		}
		n->data.harga = ss;
		n->data.user = "NULL";
		n->data.jam = 0;
		
		if(head2 == NULL){
			head2 = n;
			tail2 = head2;
			head2->prev = NULL;
			tail2->next = NULL;
			
		} else {
			tail2->next = n;
			n->prev = tail2;
			tail2 = n;
			tail2->next = NULL;
		}
	}
	node* tmp = *head;
	if(posisi > *indeks){
		(*tail)->next = head2;
		head2->prev = *tail;
		*tail = tail2;
	} else if(posisi <= 1){
		tail2->next = *head;
		(*head)->prev = tail2;
		*head = head2;
	} else {
		int i = 0;
		while(i < posisi-2){
			tmp = tmp->next;
			i++;
		}
		head2->prev = tmp;
		tail2->next = tmp->next;
		tmp->next->prev = tail2;
		tmp->next = head2;	
	}
	
	*indeks+=jumlah;
	cout << "Data berhasil ditambahkan!";
	Sleep(1000);
	system("cls");
}

void ubahpc(node* head){
	int n;
	system("cls");
	cout << "Data pc mana yg ingin anda ubah? "; cin >> n;
	int i = 1;
	node* tmp = head;
	while(tmp->data.no != n){
		tmp = tmp->next;
		i++;
	}
	cout << "Masukkan tarif baru: "; cin >> n;
	tmp->data.harga = n;
	cout << "Data berhasil diubah!\n";
}

//Fungsi menghapus data
void hapuspc(node** head, int* indeks){
	int pilih;
	string konfirmasi;
	while(cout<<"Data ke berapa yang anda ingin hapus?\n" && !(cin>>pilih)){
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout<<"Masukkan tipe angka!"<<endl;
		Sleep(1000);
		system("cls");
	}
	if(pilih>*indeks || pilih<= 0){cout<<"Indeks data diluar jangkauan\n"; Sleep(1000); return;}
	system("CLS");
	
	node* tmp2 = *head;
	int i = 1;
	while(tmp2->data.no != pilih){
		tmp2 = tmp2->next;
		i++;
	}
	tampil2(tmp2, pilih-1);
	
	konfir:
	cout<< " Hapus Data Berikut?\n[Y/N]\n "; cin >> konfirmasi;
	if(konfirmasi == "Y" || konfirmasi == "y"){
		if (*head == NULL || tmp2 == NULL)
	        return;
		else if(i == 1){
			*head = tmp2->next;
			(*head)->prev = NULL;
			delete tmp2;
		} else {
			if(tmp2->next != NULL)
				tmp2->next->prev = tmp2->prev;
			if(tmp2->prev != NULL)
				tmp2->prev->next = tmp2->next;	
			delete tmp2;	
		}
		system("cls");
		cout << "Terhapus!";
		Sleep(1000);
	}
	else if(konfirmasi == "N" || konfirmasi == "n"){
		system("cls");
		cout<<"Penghapusan Dibatalkan";
		Sleep(1000);
	}
	else{
		cout << "Masukkan Tidak Valid";
		Sleep(1000);
		system("cls");
		goto konfir;
	}
}

//Fungsi menghapus data
void hapususer(){
	int pilih;
	string konfirmasi;
	while(cout << "Data ke berapa yang anda ingin hapus?\n" && !(cin>>pilih)){
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout<<"Masukkan tipe angka!"<<endl;
		Sleep(1000);
		system("cls");
	}
	if(pilih>jumakun || pilih<= 0){cout<<"Indeks data diluar jangkauan\n"; Sleep(1000); return;}
	system("CLS");
	
	cout << pilih << ".\n";
	cout << string(40, '-') << endl;
	cout << "Nama Pen/gguna: " << acc[pilih-1].username << endl;
	cout << "Status: " << acc[pilih-1].mode << endl;
	cout << string(40, '-') << endl;
	
	konfir:
	cout<< " Hapus Data Berikut?\n[Y/N]\n "; cin >> konfirmasi;
	if(konfirmasi == "Y" || konfirmasi == "y"){
		while(pilih < jumakun){
			acc[pilih-1] = acc[pilih];
			pilih++;
		}
		jumakun--;
		system("cls");
		cout << "Terhapus!";
		Sleep(1000);
	}
	else if(konfirmasi == "N" || konfirmasi == "n"){
		system("cls");
		cout<<"Penghapusan Dibatalkan";
		Sleep(1000);
	}
	else{
		cout << "Masukkan Tidak Valid";
		Sleep(1000);
		system("cls");
		goto konfir;
	}
}
 
void ubahuser(){
	int pilih;
	string konfirmasi;
	while(cout << "Data ke berapa yang anda ingin hapus?\n" && !(cin>>pilih)){
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout<<"Masukkan tipe angka!"<<endl;
		Sleep(1000);
		system("cls");
	}
	if(pilih>jumakun || pilih<= 0){cout<<"Indeks data diluar jangkauan\n"; Sleep(1000); return;}
	system("CLS");
	
	cout << pilih << ".\n";
	cout << string(40, '-') << endl;
	cout << "Nama Pengguna: " << acc[pilih-1].username << endl;
	cout << "Status: " << acc[pilih-1].mode << endl;
	cout << string(40, '-') << endl;
	int kk;
	konfir:
		
		cout << "\nUbah status\n";
		cout << "1. Admin\n";
		cout << "2. User\n";
		cout << "3. Ban\n";
		cin >> kk;
		if(kk == 1){
			acc[pilih-1].mode = "admin";
		} else if(kk == 2){
			acc[pilih-1].mode = "user";
		} else if(kk == 3){
			acc[pilih-1].mode = "ban";
		} else {
			cout << "Masukkan Tidak Valid";
			Sleep(1000);
			system("cls");
			goto konfir;
		}
		Sleep(1000);
	
}

void tambahmenu(nodekantin** head, nodekantin** tail, int* indeksmenu) {
	nodekantin* n = new nodekantin;
	int jumlah, posisi;
	string line;
	while(cout<<"Berapa banyak menu baru yang anda ingin tambahkan?\n" && !(cin >> jumlah)){
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout<<"Masukkan tipe angka!"<<endl;
	}
	system("CLS");
	while(cout<<"Di posisi berapa anda ingin menambahkan data?\n" && !(cin >> posisi)){
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout<<"Masukkan tipe angka!"<<endl;
	}
	if(posisi > *indeksmenu+1 || posisi <= 0){
		cout << "Indeks diluar jangkauan!"; Sleep(1000);
		system("CLS");
		return;
	}
	
	nodekantin* head2 = NULL; nodekantin* tail2 = NULL;
	
	for (int i=*indeksmenu+1; i<*indeksmenu+jumlah+1; i++){
		n = new nodekantin;	
		cout<<"Data ke "<<i<<endl;
		n->data.id = i;
		cout<<"\tNama Menu: "; cin.ignore(); getline(cin, line);
		n->data.makanan = line;
		int ss;
		while(cout<<"\tHarga:  "  && !(cin>>ss)){
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout<<"Masukkan tipe angka!"<<endl;
		}
		n->data.harga = ss;
		
		if(head2 == NULL){
			head2 = n;
			tail2 = head2;
			head2->prev = NULL;
			tail2->next = NULL;
			
		} else {
			tail2->next = n;
			n->prev = tail2;
			tail2 = n;
			tail2->next = NULL;
		}
	}
	nodekantin* tmp = *head;
	if(posisi > *indeksmenu){
		(*tail)->next = head2;
		head2->prev = *tail;
		*tail = tail2;
	} else if(posisi <= 1){
		tail2->next = *head;
		(*head)->prev = tail2;
		*head = head2;
	} else {
		int i = 0;
		while(i < posisi-2){
			tmp = tmp->next;
			i++;
		}
		head2->prev = tmp;
		tail2->next = tmp->next;
		tmp->next->prev = tail2;
		tmp->next = head2;	
	}
	
	*indeksmenu+=jumlah;
	cout << "Data berhasil ditambahkan!";
	Sleep(1000);
	system("cls");
}

void ubahmenu(nodekantin* head){
	int n; string line;
	system("cls");
	cout << "Menu nomor berapa yg ingin anda ubah? "; cin >> n;
	int i = 1;
	nodekantin* tmp = head;
	while(tmp->data.id != n){
		tmp = tmp->next;
		i++;
	}
	cout<<"\tNama Menu baru: "; cin.ignore(); getline(cin, line);
	tmp->data.makanan = line;	
	cout << "Masukkan harga menu baru: "; cin >> n;
	tmp->data.harga = n;
	cout << "Data berhasil diubah!\n";
}

//Fungsi menghapus data
void hapusmenu(nodekantin** head, int* indeksmenu){
	int pilih;
	string konfirmasi;
	while(cout<<"Data ke berapa yang anda ingin hapus?\n" && !(cin>>pilih)){
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout<<"Masukkan tipe angka!"<<endl;
		Sleep(1000);
		system("cls");
	}
	if(pilih>*indeksmenu || pilih<= 0){cout<<"Indeks data diluar jangkauan\n"; Sleep(1000); return;}
	system("CLS");
	
	nodekantin* tmp2 = *head;
	int i =1;
	while(tmp2->data.id != pilih){
		tmp2 = tmp2->next;
		i++;
	}
	tampil3(tmp2, pilih-1);
	
	konfir:
	cout<< " Hapus Data Berikut?\n[Y/N]\n "; cin >> konfirmasi;
	if(konfirmasi == "Y" || konfirmasi == "y"){
		if (*head == NULL || tmp2 == NULL)
	        return;
		else if(i == 1){
			*head = tmp2->next;
			(*head)->prev = NULL;
			delete tmp2;
		} else {
			if(tmp2->next != NULL)
				tmp2->next->prev = tmp2->prev;
			if(tmp2->prev != NULL)
				tmp2->prev->next = tmp2->next;	
			delete tmp2;	
		}
		system("cls");
		cout << "Terhapus!";
		Sleep(1000);
	}
	else if(konfirmasi == "N" || konfirmasi == "n"){
		system("cls");
		cout<<"Penghapusan Dibatalkan";
		Sleep(1000);
	}
	else{
		cout << "Masukkan Tidak Valid";
		Sleep(1000);
		system("cls");
		goto konfir;
	}
}

void antrimakan(nodeporsi* porsihead){
	nodeporsi* tmp4 = porsihead;
	int i =0;
	while (tmp4 != NULL){
		if(tmp4->data.status == "belum"){
			tampil4(tmp4, i);
		}
		tmp4 = tmp4->next;
		i++;
	}
}

void dequeue(nodeporsi** porsihead){
	nodeporsi* tmp4 = *porsihead;
	int i =0;
	while (tmp4 != NULL){
		if(tmp4->data.status == "belum"){
			tmp4->data.status = "sudah";
			break;
		}
		tmp4 = tmp4->next;
		i++;
	}	
}

void muatakun(){
	string line;
	ifstream akunmasuk("akun.txt");
	while(!akunmasuk.eof()){
		
		getline(akunmasuk, acc[jumakun].username, ',');
		getline(akunmasuk, acc[jumakun].password, ',');
		getline(akunmasuk, acc[jumakun].mode, '\n');
		
		jumakun++;
		if(akunmasuk.eof()){
			break;
		}
	}
	jumakun--;
	akunmasuk.close();
}

void muatpc(node** head, node** tail){
	string line;
	ifstream pcmasuk("pc.txt");
	node* tmp = *head; 
	node* n;
	string username, angka;
	while(!pcmasuk.eof()){
		
		n = new node;
		
		getline(pcmasuk, angka, ',');
		stringstream nomor(angka);
		nomor >> n->data.no;
		
		getline(pcmasuk, username, ',');
		n->data.user = username;
		
		getline(pcmasuk, angka, ',');
		stringstream jam(angka);
		jam >> n->data.jam;
		
		getline(pcmasuk, angka, '\n');
		stringstream harga(angka);
		harga >> n->data.harga;
		
		
		if(*head == NULL){
			*head = n;
			*tail = n;
			(*head)->prev = NULL;
			(*tail)->next = NULL;

		} else{
			(*tail)->next = n;
			n->prev = *tail;
			*tail = n;
			(*tail)->next = NULL;
		}
		
		jumpc+=1;
		if(pcmasuk.eof()){
			break;
		}
	}
	jumpc-=1;
	pcmasuk.close();
}

void muatkantin(nodekantin** kantinhead, nodekantin** kantintail){
	string line;
	nodekantin* n;
	ifstream kantinmasuk("kantin.txt");
	string angka, makanan;
	while(!kantinmasuk.eof()){
		n = new nodekantin;
		
		getline(kantinmasuk, angka, ',');
		stringstream id(angka);
		id >> n->data.id;
		
		getline(kantinmasuk, makanan, ',');
		n->data.makanan = makanan;
		
		getline(kantinmasuk, angka, '\n');
		stringstream harga(angka);
		harga >> n->data.harga;
		
		if(*kantinhead == NULL){
			*kantinhead = n;
			*kantintail = n;
			(*kantinhead)->prev = NULL;
			(*kantintail)->next = NULL;

		} else{
			(*kantintail)->next = n;
			n->prev = *kantintail;
			*kantintail = n;
			(*kantintail)->next = NULL;
		}		
		
		jumkantin++;
		if(kantinmasuk.eof()){
			break;
		}
	}
	jumkantin--;
	kantinmasuk.close();
}

void muatporsi(nodeporsi** porsihead, nodeporsi** porsitail){
	nodeporsi* n;
	ifstream porsimasuk("porsi.txt");
	string angka, line;
	while(!porsimasuk.eof()){
		n = new nodeporsi;
		
		getline(porsimasuk, angka, ',');
		stringstream harga(angka);
		harga >> n->data.harga;
		
		getline(porsimasuk, line, ',');
		n->data.makanan = line;
		
		getline(porsimasuk, angka, ',');
		stringstream porsi(angka);
		porsi >> n->data.porsi;
		
		getline(porsimasuk, line, ',');
		n->data.status = line;
		
		getline(porsimasuk, line, '\n');
		n->data.user = line;
		
		if(*porsihead == NULL){
			*porsihead = n;
			*porsitail = n;
			(*porsihead)->prev = NULL;
			(*porsitail)->next = NULL;

		} else{
			(*porsitail)->next = n;
			n->prev = *porsitail;
			*porsitail = n;
			(*porsitail)->next = NULL;
		}		
		
		jumkantin++;
		if(porsimasuk.eof()){
			break;
		}
	}
	jumkantin--;
	porsimasuk.close();
}

void simpanakun(){
	ofstream akunku("akun.txt");
	for(int i = 1; i<jumakun; i++){
		akunku << acc[i].username << ",";
		akunku << acc[i].password << ",";
		akunku << acc[i].mode << "\n";
	}
	akunku.close();
}
void simpanpc(node* head){
	ofstream pcku("pc.txt");
	node* tmp = head;
	while(tmp!=NULL){
		pcku << tmp->data.no << ",";
		pcku << tmp->data.user << ",";
		pcku << tmp->data.jam << ",";
		pcku << tmp->data.harga << "\n";
		tmp = tmp->next;
	}
	pcku.close();
}
void simpankantin(nodekantin* head){
	nodekantin* tmp = head;
	ofstream kantinku("kantin.txt");
	while(tmp!=NULL){
		kantinku << tmp->data.id << ",";
		kantinku << tmp->data.makanan << ",";
		kantinku << tmp->data.harga << "\n";
		tmp = tmp->next;
	}
	kantinku.close();
}
void simpanporsi(nodeporsi* head){
	nodeporsi* tmp = head;
	ofstream porsiku("porsi.txt");
	while(tmp!=NULL){
		porsiku << tmp->data.harga << ",";
		porsiku << tmp->data.makanan << ",";
		porsiku << tmp->data.porsi << ",";
		porsiku << tmp->data.status << ",";
		porsiku << tmp->data.user << "\n";
		tmp = tmp->next;
	}
	porsiku.close();
}

//QuickSort USER
// Fungsi untuk mengembalikan akhir dari linked list
struct node* getTail(struct node* cur)
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

void addtail(node** tail, node** head){
	node* tmp = *head;
	while(tmp->next != NULL){
		tmp = tmp->next;
	}
	*tail = tmp;
}

void swap ( bill* a, bill* b )    
{ bill t = *a; *a = *b; *b = t; }    
 
// Fungsi untuk membagi linked list dan mengambil elemen terakhir sebagai pivot
node* ascendingpartition(node *l, node *h)  
{
    
 
    node *i = l->prev;    
    
   
    for (node *j = l; j != h; j = j->next)    
    {    
    
    
    	if(usr == "user"){
	        if (j->data.user <= h->data.user)    
	        {    

	            i = (i == NULL)? l : i->next;    
	    
	            swap(&(i->data), &(j->data));    
	        }
	    }    
    	if(usr == "jam"){
	        if (j->data.jam <= h->data.jam)    
	        {    
	            
	            i = (i == NULL)? l : i->next;    
	    
	            swap(&(i->data), &(j->data));    
	        }

    } 
        if(usr == "harga"){
	        if (j->data.harga <= h->data.harga)    
	        {    
	            
	            i = (i == NULL)? l : i->next;    
	    
	            swap(&(i->data), &(j->data));    
	        }

    } 
}
    i = (i == NULL)? l : i->next; 
    swap(&(i->data), &(h->data));    
    return i;    
}
 
// Pengurutan quicksort ascending
void ascending_quickSort(node* l, node *h)    
{    
    if (h != NULL && l != h && l != h->next)    
    {    
        node *p = ascendingpartition(l, h);    
        ascending_quickSort(l, p->prev);    
        ascending_quickSort(p->next, h);    
    }    
}    
 
// fungsi rekursif Quicksort Ascending
void ascendingquickSort(node *head)    
{    
    
    node *h = getTail(head);    
    
     
    ascending_quickSort(head, h);    
}

//partisi quicksort secara ascending
node* descendingpartition(node *l, node *h)  
{
    
    
    node *i = l->prev;    
    
     
    for (node *j = l; j != h; j = j->next)    
    {    
    
    
    	if(usr == "user"){
	        if (j->data.user >= h->data.user)    
	        {    
	            
	            i = (i == NULL)? l : i->next;    
	    
	            swap(&(i->data), &(j->data));    
	        }
	    }    
    	if(usr == "jam"){
	        if (j->data.jam >= h->data.jam)    
	        {    
	           
	            i = (i == NULL)? l : i->next;    
	    
	            swap(&(i->data), &(j->data));    
	        }
	    }  
		if(usr == "harga"){
	        if (j->data.harga >= h->data.harga)    
	        {    
	           
	            i = (i == NULL)? l : i->next;    
	    
	            swap(&(i->data), &(j->data));    
	        }
	    }   
    }
             
}    
   

 
// Pengurutan quicksort descending
void descending_quickSort(node* l, node *h)    
{    
    if (h != NULL && l != h && l != h->next)    
    {    
        node *p = descendingpartition(l, h);    
        descending_quickSort(l, p->prev);    
        descending_quickSort(p->next, h);    
    }    
}    
 
// fungsi rekursif Quicksort Ascending
void descendingquickSort(node*head)    
{    
   
    node *h = getTail(head);    
    
   
    descending_quickSort(head, h);    
}
 


void split(struct node* head, struct node** a, struct node** b)
{
    struct node* slow = head;
    struct node* fast = head->next;
 
    
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
 
    *b = slow->next;
    slow->next = NULL;
}



//QuickSort KANTIN
// Fungsi untuk mengembalikan akhir dari linked list
struct nodekantin* getTail(struct nodekantin* cur)
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

void addtail(nodekantin** tail, nodekantin** head){
	nodekantin* tmp = *head;
	while(tmp->next != NULL){
		tmp = tmp->next;
	}
	*tail = tmp;
}

void swap ( kantin* a, kantin* b )    
{ kantin t = *a; *a = *b; *b = t; }    
 
// Fungsi untuk membagi linked list dan mengambil elemen terakhir sebagai pivot
nodekantin* ascpartition(nodekantin *l, nodekantin *h)  
{
    
 
    nodekantin *i = l->prev;    
    
   
    for (nodekantin *j = l; j != h; j = j->next)    
    {    
    
    
    	if(att == "makanan"){
	        if (j->data.makanan <= h->data.makanan)    
	        {    

	            i = (i == NULL)? l : i->next;    
	    
	            swap(&(i->data), &(j->data));    
	        }
	    }    
    	if(att == "harga"){
	        if (j->data.harga <= h->data.harga)    
	        {    
	            
	            i = (i == NULL)? l : i->next;    
	    
	            swap(&(i->data), &(j->data));    
	        }

    } 
}
    i = (i == NULL)? l : i->next; 
    swap(&(i->data), &(h->data));    
    return i;    
}
 
// Pengurutan quicksort ascending
void asc_quickSort(nodekantin* l, nodekantin *h)    
{    
    if (h != NULL && l != h && l != h->next)    
    {    
        nodekantin *p = ascpartition(l, h);    
        asc_quickSort(l, p->prev);    
        asc_quickSort(p->next, h);    
    }    
}    
 
// fungsi rekursif Quicksort Ascending
void ascquickSort(nodekantin *head)    
{    
    
    nodekantin *h = getTail(head);    
    
     
    asc_quickSort(head, h);    
}

//partisi quicksort secara ascending
nodekantin* despartition(nodekantin *l, nodekantin *h)  
{
    
    
    nodekantin *i = l->prev;    
    
     
    for (nodekantin *j = l; j != h; j = j->next)    
    {    
    
    
    	if(att == "makanan"){
	        if (j->data.makanan >= h->data.makanan)    
	        {    
	            
	            i = (i == NULL)? l : i->next;    
	    
	            swap(&(i->data), &(j->data));    
	        }
	    }    
    	if(att == "harga"){
	        if (j->data.harga >= h->data.harga)    
	        {    
	           
	            i = (i == NULL)? l : i->next;    
	    
	            swap(&(i->data), &(j->data));    
	        }
	    }    
    }
             
}    
   

 
// Pengurutan quicksort descending
void des_quickSort(nodekantin* l, nodekantin *h)    
{    
    if (h != NULL && l != h && l != h->next)    
    {    
        nodekantin *p = despartition(l, h);    
        des_quickSort(l, p->prev);    
        des_quickSort(p->next, h);    
    }    
}    
 
// fungsi rekursif Quicksort Ascending
void desquickSort(nodekantin*head)    
{    
   
    nodekantin *h = getTail(head);    
    
   
    des_quickSort(head, h);    
}
 


void split(struct nodekantin* head, struct nodekantin** a, struct nodekantin** b)
{
    struct nodekantin* slow = head;
    struct nodekantin* fast = head->next;
 
    
    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
 
    *b = slow->next;
    slow->next = NULL;
}



int main() {
	
	acc[0].username = "admin"; acc[0].password = "1"; acc[0].mode = "admin";
	jumakun = 1;
	
	int indeks = 0, indeksmenu = 0, c = 0, hasilcari, totall = 0;
	
	node* head = NULL;
	node* tail = NULL;
	
	nodekantin* kantinhead = NULL;
	nodekantin* kantintail = NULL;
	
	nodeporsi* porsihead = NULL;
	nodeporsi* porsitail = NULL;

	//Menambahkan nilai awal ke dalam linked list
	muatakun();
	muatpc(&head, &tail);
	muatkantin(&kantinhead, &kantintail);
	muatporsi(&porsihead, &porsitail);
//	muattagihan();
	
	indeksmenu = indeks;

	string mode="user", username = "N/A", kon;
	int menu, submenu;
	while(1){
		aut:
		if(mode == "user"){
			system("CLS");
		    
			int cari, x=1, y=5, item=1, item2, x2, y2, n; bool run;
//			gotoXY(x, y); cout << ">";
			while(true){
				gotoXY(0, 0); cout <<  "_________________\n";
				gotoXY(0, 1); cout <<  "|               |\n";
			  	gotoXY(0, 2); cout <<  "|   MENU USER   |\n";
			  	gotoXY(0, 3); cout <<  "|_______________|\n";
			  	gotoXY(0, 4); cout <<  "|               |\n";
				gotoXY(0, 5); cout <<  "|  1. Login     |\n";
			  	gotoXY(0, 6); cout <<  "|  2. Regis     |\n";
			  	gotoXY(0, 7); cout <<  "|  3. Sewa PC   |\n";
			  	gotoXY(0, 8); cout <<  "|  4. Kantin    |\n";
			  	gotoXY(0, 9); cout <<  "|  5. Tagihan   |\n";
			  	gotoXY(0, 10); cout << "|  6. Log Out   |\n";
			  	gotoXY(0, 11); cout << "|  7. Keluar    |\n";
			  	gotoXY(0, 12); cout << "|_______________|\n\n";
			  	if(item == 1){
			  		gotoXY(0, 5); cout << "|  "; color(240); cout << "1. Login"; color(7); gotoXY(16, 5); cout << "|";
			  	} else if(item == 2){
			  		gotoXY(0, 6); cout << "|  "; color(240); cout << "2. Regis"; color(7); gotoXY(16, 6); cout << "|";
			  	} else if(item == 3){
			  		gotoXY(0, 7); cout << "|  "; color(240); cout << "3. Sewa PC"; color(7);gotoXY(16, 7); cout << "|";
			  	} else if(item == 4){
			  		gotoXY(0, 8); cout << "|  "; color(240); cout << "4. Kantin"; color(7); gotoXY(16, 8); cout << "|";
			  	} else if(item == 5){
			  		gotoXY(0, 9); cout << "|  "; color(240); cout << "5. Tagihan"; color(7); gotoXY(16, 9); cout << "|";
			  	} else if(item == 6){
			  		gotoXY(0, 10); cout << "|  "; color(240); cout << "6. Log Out"; color(7); gotoXY(16, 10); cout << "|";
			  	} else if(item == 7){
			  		gotoXY(0, 11); cout << "|  "; color(240); cout << "7. Keluar"; color(7);gotoXY(16, 11); cout << "|";
			  	}
//			  	gotoXY(x, y); color(31); cout << ">";  color(7);
			  	system("pause>nul");
				if(GetAsyncKeyState(VK_DOWN) && y != 11){
//					gotoXY(x, y); cout << " ";
					y+=1;
					item+=1;		
				}
				if(GetAsyncKeyState(VK_UP) && y != 5){
//					gotoXY(x, y); cout << " ";
					y-=1;
					item-=1;
				}
				if(GetAsyncKeyState(VK_RETURN) & 0x8000) {
				  	switch (item) {
				  		case 1:
				  			system("cls");
				  			login(&mode , &username);system("cls");
				  			goto aut;
				  			break;
				  		case 2:system("cls");
				  			regis(&mode , &username);system("cls");
				  			break;
				  		case 3:system("cls");
				  			tampil(head, &indeks);
				  			cout << "\nSewa PC?(y/n)\n"; cin >> kon;
				  			if(kon == "y"){
							  	if(username == "N/A"){
							  		cout << "\n Silahkan login terlebih dahulu!\n";
							  	} else {
								  pilihpc(username, head);
								}
							}
				  			system("cls");
							break;
				  		case 4:system("cls");
				  			pilihkantin(kantinhead, &indeks, &porsihead, &porsitail, username);
//				  			cout << "\n1. Pesan Makanan\n";
//							cout << "\n2. Cari Menu\n";  
//				  			cout << "\n2. Urutkan Menu\n"; 
//							cin >> submenu;
//				  			if(submenu == 1){
//				  				if(username == "N/A"){
//							  		cout << "\n Silahkan login terlebih dahulu!\n";
//							  		Sleep(500);
//							  	} else {
//							  		pilihmakan(username, kantinhead, &porsihead, &porsitail);
//							  	}
//				  			} else if(submenu == 2){
//				  				// Tambahkan fungsi pencarian disini
//				  			if(submenu == 3){
//				  			string pilihansort;
//				  				cout <<"\n================================ PILIH YANG MANA MAU DIURUT =================================";
//						  	cout <<"\n1. Makanan\n";
//						 	cout <<"\n2. Harga\n";
//						 	cout <<"\n\n Pilih : ";
//						  	cin >> pilihansort;
//						  	system("cls");
//						  	
//						  	
//						  	if (pilihansort == "1"){
//						  		att = "makanan";
//							}
//							if (pilihansort == "2"){
//						  		att = "harga";
//							}
//								system("cls");
//				  				string pilihan;
//				  				cout <<"\n================================ PILIH PENGURUTAN =================================";
//	  							cout <<"\n1. Ascending";
//	 							cout <<"\n2. Descending";
//	  							cout <<"\n\nMasukkan Pilihan : ";
//	  							cin >> pilihan;
//	  							if(pilihan == "1"){
//								ascquickSort(kantinhead);
//								}
//								if(pilihan == "2"){
//									desquickSort(kantinhead);
//								}
//								tampilkantin(kantinhead, &indeks);
//				  			}
//							system("cls");
//				  			break;

				  		case 5:system("cls");
				  			totall = tagihan(username, head, &indeks, porsihead);
				  			cout << "Total tagihan: " << totall << endl;
				  			cout << "\nBayar Tagihan?(y/n)\n"; cin >> kon;
				  			if(kon == "y")	  			
				  				bayar(totall, &porsihead, username, &head);system("cls");
				  			break;
				  		case 6:
				  			username = "N/A";system("cls"); break;
				  		case 7:
				  			simpanakun();
				  			simpanpc(head);
				  			simpankantin(kantinhead);
				  			simpanporsi(porsihead);
				  			system("cls"); cout << "Terima Kasih telah menggunakan program kami."; exit(0);
			  		}				
				}
			}

		} else if(mode == "admin"){
			
			int cari, x=1, y=5, item=1, item2, x2, y2, n; bool run;
//			gotoXY(x, y); cout << ">";
			while(true){
				gotoXY(0, 0); cout <<  "______________________________\n";
				gotoXY(0, 1); cout <<  "|                            |\n";
			  	gotoXY(0, 2); cout <<  "|   	  MENU ADMIN         |\n";
			  	gotoXY(0, 3); cout <<  "|____________________________|\n";
			  	gotoXY(0, 4); cout <<  "|                            |\n";
				gotoXY(0, 5); cout <<  "|  1. Daftar PC              |\n";
			  	gotoXY(0, 6); cout <<  "|  2. Daftar User            |\n";
			  	gotoXY(0, 7); cout <<  "|  3. Daftar Menu Makanan    |\n";
			  	gotoXY(0, 8); cout <<  "|  4. Daftar Antrian Pesanan |\n";
			  	gotoXY(0, 9); cout <<  "|  5. Keluar Mode Admin      |\n";
			  	gotoXY(0, 10); cout << "|____________________________|\n";
			  	
				color(240);
				if(item == 1){
					gotoXY(6, 5); cout << "Daftar PC";
				} else if(item == 2){
					gotoXY(6, 6); cout << "Daftar User";
				} else if(item == 3){ 
					gotoXY(6, 7); cout << "Daftar Menu Makanan";
				} else if(item == 4){
					gotoXY(6, 8); cout << "Daftar Antrian Pesanan";
				} else if(item == 5){
					gotoXY(6, 9); cout << "Keluar Mode Admin";
				} else if(item == 6){
					gotoXY(6, 10); cout << "Log Out";
				} else if(item == 7){
					gotoXY(6, 11); cout << "Keluar";
				} color(7);
				
				system("pause>nul");
				if(GetAsyncKeyState(VK_DOWN) && item != 5){
					item+=1;		
				}
				if(GetAsyncKeyState(VK_UP) && item != 1){
					item-=1;			
				}
				if(GetAsyncKeyState(VK_RETURN) & 0x8000) {
				  	switch (item){
				  		case 1:system("cls");
				  			tampil(head, &indeks);
				  			cout << "\n1. Tambah PC\n";
				  			cout << "2. Ubah PC\n";
				  			cout << "3. Hapus PC\n";
				  			cout << "4. Batal\n";
				  			cin >> submenu;
				  			if(submenu == 1){
				  				tambahpc(&head, &tail, &indeks);
				  			} else if(submenu == 2){
				  				ubahpc(head);
				  			} else if(submenu == 3){
				  				hapuspc(&head, &indeks);
				  			} else if(submenu == 4){
				  				break;
				  			}
				  			system("cls");
				  			break;
				  		case 2:system("cls");
				  			daftarakun(head, porsihead, &indeks);
				  			cout << "\n1. Urutkan pengguna\n";
				  			cout << "\n2. Cari pengguna\n";
				  			cout << "\n3. Ubah status pengguna\n";
				  			cout << "\n4. Hapus pengguna\n";
				  			cout << "\n5. Batal\n\n";
				  			cout << "Pilih : ";
				  			cin >> submenu;
				  			if(submenu == 1){
							cout << "\n1. Mengsortir Data User\n";
							cout << "\n2. Kembali\n";  
				  			cout << " \npilih : ";
							cin >> submenu;
							system("cls");
				  			if(submenu == 1){
				  			string pilihansort;
				  			
							cout <<"\n================================ PILIH YANG MANA MAU DIURUT =================================";
						  	cout <<"\n1. User\n";
						 	cout <<"\n2. Jam\n";
						 	cout <<"\n3. Harga\n";
							cout <<"\n\n Pilih : ";
						  	cin >> pilihansort;
						  	system("cls");
						  	
						  	if (pilihansort == "1"){
						  		usr = "User";
							}
							if (pilihansort == "2"){
						  		usr = "Jam";
							}
							if (pilihansort == "3"){
						  		usr = "Harga";
							}
								system("cls");
				  				string pilihan;
				  				cout <<"\n================================ PILIH PENGURUTAN =================================";
	  							cout <<"\n1. Ascending";
	 							cout <<"\n2. Descending";
	  							cout <<"\n\nMasukkan Pilihan : ";
	  							cin >> pilihan;
	  							if(pilihan == "1"){
								ascendingquickSort(head);
								}
								if(pilihan == "2"){
									descendingquickSort(head);
								}
				  			} else if (submenu == 2){
				  				break;
							  }
							system("cls");
				  			break;
				  			} else if(submenu ==2 ){
				  				//fungsi pencarian user
				  			} else if (submenu == 3){
				  				ubahuser();
				  			} else if(submenu == 4){
				  				hapususer();
				  			}else if(submenu == 5){
				  				break;
				  				system("cls");
				  			}
				  			break; 
				  			system("cls");
				  		case 3:system("cls");
				  			tampilkantin(kantinhead, &indeks);
				  			cout << "\n1. Tambah Menu\n";
				  			cout << "2. Ubah Menu\n";
				  			cout << "3. Hapus Menu\n";
				  			cout << "4. Urutkan Menu\n";
				  			cout << "5. Carikan Menu\n";
				  			cout << "6. Batal\n";
				  			cout << "\nPilih : ";
				  			cin >> submenu;
				  			if(submenu == 1){
				  				tambahmenu(&kantinhead, &kantintail, &indeksmenu);
				  			} else if(submenu == 2){
				  				ubahmenu(kantinhead);
				  			} else if(submenu == 3){
				  				hapusmenu(&kantinhead, &indeksmenu);
							} else if(submenu == 4){
				  			cout << "\n1. Mengsortir Menu\n";
							cout << "\n2. Kembali\n";  
				  			cout << " \npilih : ";
							cin >> submenu;
							system("cls");
				  			if(submenu == 1){
				  			string pilihansort;
				  			
							cout <<"\n================================ PILIH YANG MANA MAU DIURUT =================================";
						  	cout <<"\n1. Makanan\n";
						 	cout <<"\n2. Harga\n";
						 	cout <<"\n\n Pilih : ";
						  	cin >> pilihansort;
						  	system("cls");
						  	
						  	if (pilihansort == "1"){
						  		att = "makanan";
							}
							if (pilihansort == "2"){
						  		att = "harga";
							}
								system("cls");
				  				string pilihan;
				  				cout <<"\n================================ PILIH PENGURUTAN =================================";
	  							cout <<"\n1. Ascending";
	 							cout <<"\n2. Descending";
	  							cout <<"\n\nMasukkan Pilihan : ";
	  							cin >> pilihan;
	  							if(pilihan == "1"){
								ascquickSort(kantinhead);
								}
								if(pilihan == "2"){
									desquickSort(kantinhead);
								}
								tampilkantin(kantinhead, &indeks);
				  			} else if (submenu == 2){
				  				break;
							  }
							system("cls");
				  			break;
				  			} else if(submenu == 5){
//				  			cout<<"Melakukan Pencarian"; Sleep(100); system("CLS");
//							cout<<"Melakukan Pencarian."; Sleep(100); system("CLS");
//							cout<<"Melakukan Pencarian.."; Sleep(100); system("CLS");
//							cout<<"Melakukan Pencarian..."; Sleep(100); system("CLS");
//													
//							t = 0;
//							att = "makanan";
//							ascquickSort(kantinhead);
//							if(src == "fib")
//								n = SearchMakanan(kantinhead, indeks);
//							if(n > -1){
//								trv(head, n, indeks);
//								if(t == 0){
//									cout << "Data Tidak Ditemukan"; getch();
//								}
//								else
//									pilih(head, &idx, &saya, &indeks);
//							}
//							else if(n <= -1)
//								cout << "Data Tidak Ditemukan"; getch();							
//				            system("CLS");
//							break;
//				  			} else if(submenu == 6){
//				  				break;
//				  			}system("cls");
//				  			break;
						}
				  		case 4:
				  			system("cls");
				  			antrimakan(porsihead);
				  			cout << "1. Layani Antrian\n";
				  			cout << "2. Kembali\n";
				  			cin >> submenu;
				  			if(submenu == 1){
				  				dequeue(&porsihead);
				  				cout << "Makanan diantar ke antrian pertama\n"; Sleep(500);
				  			}
				  			system("cls");
				  			break;
				  		case 5:system("cls");
				  			mode = "user"; username = "N/A";
				  			login(&mode , &username);
				  			system("cls");
				  			break;
				  	}					
				}
			}
		} else {
			system("cls");
			simpanakun();
			simpanpc(head);
			simpankantin(kantinhead);
			simpanporsi(porsihead);
			cout << "Akun anda telah diblokir, anda dikeluarkan dari program ini.";
			exit(0);
		}
	}
  	return 0;
}
