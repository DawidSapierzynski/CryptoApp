#include <stdint.h>
#include <iostream> // <- standardowe wejscie wyjscie
#include <fstream>
#include <string.h>
#include <stdint.h>
#include <sstream>
#include <iomanip>
using namespace std;

void encrypttea(uint32_t* v, uint32_t* k);
void decrypttea(uint32_t* v, uint32_t* k);
uint64_t rsa(uint64_t keypub, uint64_t n, uint64_t input);

void BlockEncryption(int wybor_algorytmu, std::ifstream &key, std::fstream &input, std::fstream &output);

void TEASymmetricEncryption(int wybor_algorytmu, std::ifstream &key, std::fstream &input, std::fstream &output);

void RSAAsymmetricalEncryption(int wybor_algorytmu, std::ifstream &key, std::fstream &input, std::fstream &output);

void DJB2(int wybor_algorytmu, std::fstream &input, std::fstream &output);

int main(int argc, char ** argv)//argc to liczba calkowita informujaca o tym ile argumentow zostalo przekazanych. PYTANIE! 
{
 	cout<<"**************************************************************"<< endl;
  	cout << "*\t\t     *******************   \t\t     *"<< endl;
	cout << "*\t\t     * CRYPTO WKR 2017 *   \t\t     *"<< endl;
 	cout << "*\t\t     *******************   \t\t     *"<< endl;
	cout<<"**************************************************************"<< endl; 

	if (argc == 2) // pierwszym parametrem jest nazwa programu
		{
		  	if( argv[1][0]=='-' && argv[1][1]=='h' && strlen(argv[1]) == 2  ||  std::string(argv[1])=="--help")
				{				
					cout<<"* Prosze uzupelnic pole pomocy w miare rozwoju aplikacji.    *"<< endl;
					cout<<"* W chwili obecnej program zbudowany jest jako szablon,      *"<< endl;
					cout<<"* ktory powinien byc uzupelniany o kolejne algorytmy         *"<< endl;
					cout<<"* kryptograficzne. Powodzenia.                               *"<< endl;
					cout<<"**************************************************************"<< endl;	
					cout<<"* Dolecowy program powinien dzialac w nastepujacy sposob:    *"<< endl;
					cout<<"* W wierszu polecen wywolujemy nazwe programu i parametry    *"<< endl;
					cout<<"* programu, gdzie:                                           *"<< endl;		
					cout<<"* -bc szyfr blokowy w trybie c/d (szyfrowanie/deszyfrowanie);*"<< endl;
					cout<<"* -sc szyfr strumieniowy w trybie c/d                        *"<< endl;
					cout<<"* (szyfrowanie/deszyfrowanie);                               *"<< endl;
					cout<<"* -hf funkcja skrotu bez trybow;                             *"<< endl;					
					cout<<"* -ac szyfr asymetryczny w trybie c/d                        *"<< endl;
					cout<<"* (szyfrowanie/deszyfrowanie);                               *"<< endl;					
					cout<<"* -i sciezka pliku wejsciowego (tekstu jawnego,              *"<< endl;	
					cout<<"* wiadomosci);                                               *"<< endl;
					cout<<"* -o sciezka pliku wyjsciowego (tekstu zaszyfrowanego,       *"<< endl;	
					cout<<"* skrotu);                                                   *"<< endl;
					cout<<"* -k sciezka klucza;                                         *"<< endl;		
					cout<<"* -h, --help to pomoc (wystepuje bez innych parametrow);     *"<< endl; 	
					cout<<"**************************************************************"<< endl;
					cout<<"*Przyklad:                                                   *"<< endl;
					cout<<"*crypto.exe -bc d -i C:\\in.txt -o D:\\out.txt -k C:\\key.txt   *"<< endl;
					cout<<"**************************************************************"<< endl;
					cout<<"* Porgram operuje na plikach tekstowych.                     *"<< endl;	
					cout<<"**************************************************************"<< endl;
				}
			else
				{
					cout<< argc<<endl;
					cout<<"blednie wprowadzone parametr/parametry. (Blad: E001)" <<endl;
				}			   
		}
	else
	{
		fstream input;
		fstream output;
		ifstream key;
		bool flaga_algorytmu = false;
		int flaga_poprawnosci_parametrow = 0;
		int wybor_algorytmu = 0;

		for (int i = 0; i < argc; i++)
		{
			if (argv[i][0] == '-')
			{
				if (argc == i + 1 || argv[i + 1][0] == '-')
				{
					if (std::string(argv[i]) == "-hf")
					{
						cout << argv[i] << ":";
						cout << "Ok, wyznaczenie skrotu do dzialania nie potrzebuje parametru ani pliku klucza;" << endl;
						wybor_algorytmu = 7;
					}
					else if (std::string(argv[i]) == "-bc")
					{
						flaga_algorytmu = true;
						cout << argv[i] << ": ";
						cout << "Nie podano parametru pracy szyfru blokowego;" << endl;
					}
					else if (std::string(argv[i]) == "-sc")
					{
						flaga_algorytmu = true;
						cout << argv[i] << ": ";
						cout << "Nie podano parametru pracy szyfru strumieniowego;" << endl;
					}
					else if (std::string(argv[i]) == "-ac")
					{
						flaga_algorytmu = true;
						cout << argv[i] << ": ";
						cout << "Nie podano parametru pracy szyfru asymetrycznego;" << endl;
					}
					else if (std::string(argv[i]) == "-i")
					{
						cout << argv[i] << ": ";
						cout << "Nie podano sciezki pliku wejsciowego;" << endl;
					}

					else if (std::string(argv[i]) == "-o")
					{
						cout << argv[i] << ": ";
						cout << "Nie podano sciezki pliku wyjsciowego;" << endl;
					}
					else if (std::string(argv[i]) == "-k")
					{
						cout << argv[i] << ": ";
						cout << "Nie podano pliku klucza;" << endl;

					}
					else
					{
						cout << argv[i] << ": ";
						cout << "Niepoprawny parametr pracy programu;" << endl;
					}
				}
				else
				{
					if (std::string(argv[i]) == "-i")
					{
						input.open(argv[i + 1], ios::in);

						if (input.good() == true)
						{
							cout << "Dane wejsciowe zostana pobrany z pliku: " << argv[++i] << endl;
						}
						else
						{
							cout << argv[i] << ": ";
							cout << "Niepoprawna sciezka pliku wejsciowego!" << endl;
						}
					}

					else if (std::string(argv[i]) == "-o")
					{
						output.open(argv[i + 1], ios::out);

						if (output.good() == true)
						{
							cout << "Dane wyjsciowe zostana zapisane do pliku: " << argv[++i] << endl;
						}
						else
						{
							cout << argv[i] << ": ";
							cout << "Niepoprawna sciezka pliku wejsciowego!" << endl;
						}
					}

					else if (std::string(argv[i]) == "-k")
					{
						key.open(argv[i + 1], ios::in);

						if (key.good() == true)
						{
							cout << "Klucz zostanie pobrany z pliku: " << argv[++i] << endl;
						}
						else
						{
							cout << argv[i] << ": ";
							cout << "Niepoprawna sciezka klucza!" << endl;
						}
					}

					else if (std::string(argv[i]) == "-bc")
					{
						if (std::string(argv[i + 1]) == "c" || std::string(argv[i + 1]) == "d")
						{
							cout << "Szyfr blokowy bedzie pracowal w trybie (szyfrowania -> c , deszyfrowania -> d): " << argv[++i] << endl;
							if (string(argv[i]) == "c") {
								wybor_algorytmu = 1;
							}
							else
							{
								wybor_algorytmu = 2;
							}
						}

						else
						{
							cout << argv[i] << ": ";
							cout << "Niepoprawny tryb pracy szyfru;" << endl;
						}
					}

					else if (std::string(argv[i]) == "-sc")
					{
						if (std::string(argv[i + 1]) == "c" || std::string(argv[i + 1]) == "d")
						{
							cout << "Szyfr strumieniowy bedzie pracowal w trybie (szyfrowania -c , deszyfrowania -d): " << argv[++i] << endl;
							if (string(argv[i]) == "c") {
								wybor_algorytmu = 3;
							}
							else
							{
								wybor_algorytmu = 4;
							}
						}
						else
						{
							cout << argv[i] << ": ";
							cout << "Niepoprawny tryb pracy szyfru;" << endl;
						}
					}

					else if (std::string(argv[i]) == "-as")
					{
						if (std::string(argv[i + 1]) == "c" || std::string(argv[i + 1]) == "d")
						{
							cout << "Szyfr asymetryczny bedzie pracowal w trybie (szyfrowania -c , deszyfrowania -d): " << argv[++i] << endl;
							if (string(argv[i]) == "c") {
								wybor_algorytmu = 5;
							}
							else
							{
								wybor_algorytmu = 6;
							}
						}
						else
						{
							cout << argv[i] << ": ";
							cout << "Niepoprawny tryb pracy szyfru;" << endl;
						}
					}
					else
					{
						cout << argv[i] << ": ";
						cout << "Niepoprawny parametr pracy programu;" << endl;
					}
				}
			}
		}

		if (output.good() == true && input.good() == true && key.good() == true){
			//obs³uga szyfrowania blokowego
			BlockEncryption(wybor_algorytmu, key, input, output);

			//szyfrowanie symetryczne TEA
			TEASymmetricEncryption(wybor_algorytmu, key, input, output);

			//Szyfrowanie asymetryczne RSA
			RSAAsymmetricalEncryption(wybor_algorytmu, key, input, output);

			//Funkcja skrótu DJB2
			DJB2(wybor_algorytmu, input, output);

		input.close();
		key.close();
		output.close();
		}
	}
getchar();
return 0;	
}

void DJB2(int wybor_algorytmu, std::fstream &input, std::fstream &output)
{
	if (wybor_algorytmu == 7) {
		uint32_t iout = 5381;
		char sin = 0;

		while (input.get(sin)) {
			iout = ((iout << 5) + iout) + sin;
		}
		output << hex << iout;

		cout << "Funkcja skrotu djb2 zostala poprawnie utworzona" << endl;
	}
}

void RSAAsymmetricalEncryption(int wybor_algorytmu, std::ifstream &key, std::fstream &input, std::fstream &output)
{
	if (wybor_algorytmu == 5 || wybor_algorytmu == 6) {
		uint64_t keypub = 0, n = 0, iout = 0, iin = 0;
		char sin[3] = { 0 }, sout[3] = { 0 }; //tablice przechowujace znaki z plikow
		stringstream ss;
		string k[2];

		//odczytywanie kluczy z pliku pierwszy jest klucz publiczny
		//drugi to klucz prywatny odzielone s¹ œrednikiem
		//trzecia liczba po œredniku to n
		//07;67;8f
		getline(key, k[0], ';');
		ss << hex << const_cast<char*>(k[0].c_str());
		ss >> keypub;
		ss.clear();

		getline(key, k[1], ';');
		ss << hex << const_cast<char*>(k[1].c_str());
		ss >> n;
		ss.clear();


		while (input.get(sin, 3)) {
			iin = 0;
			ss << hex << sin;
			ss >> iin;
			ss.clear();

			iout = rsa(keypub, n, iin);

			ss << hex << iout;
			ss >> sout;
			ss.clear();
			output << setfill('0') << setw(2) << sout;
		}
		if (wybor_algorytmu == 5) {
			cout << "Zaszyfrowano." << endl;
		}
		else {
			cout << "Odszyfrowano." << endl;
		}
	}
}

void TEASymmetricEncryption(int wybor_algorytmu, std::ifstream &key, std::fstream &input, std::fstream &output)
{
	if (wybor_algorytmu == 3 || wybor_algorytmu == 4) {
		char skey[9] = { 0 }, sin[2] = { 0 }; //tablice przechowujace znaki z plikow
		stringstream ss;
		uint32_t ikey = 0, reg = 0;
		uint16_t klucz = 0, iin = 0; //wykorzystuje tylko 4 bity
		bool k = 0;
		int rozmiar = 0, z = 0;

		//inicjacja rejestru
		key.get(skey, 9);
		ss << hex << skey;
		ss >> ikey;
		ss.clear();
		rozmiar = 8 - string(skey).length();
		ikey = ikey << rozmiar * 4; //dope³neinie 0 najmniej znaczacych bitow
		reg = ikey;

		while (input.get(sin, 2)) {
			ss << hex << sin;
			ss >> iin;
			ss.clear();

			klucz = 0;
			for (z = 0; z < 4; z++) { //klucz
									  //x31+x3+1
				klucz <<= 1;
				k = ((!!(reg & 0x80000000)) ^ (!!(reg & 0x00000008)) ^ (!!(reg & 0x00000001)));
				klucz += !!(reg & 0x80000000);
				reg <<= 1;
				reg += k;
			}

			iin = klucz ^ iin; //XOR danych z kluczem

			ss << hex << iin;
			ss >> sin;
			ss.clear();
			output << setfill('0') << setw(1) << sin;

		}
		if (wybor_algorytmu == 3) {
			cout << "Zaszyfrowano." << endl;
		}
		else {
			cout << "Odszyfrowano." << endl;
		}
	}
}

void BlockEncryption(int wybor_algorytmu, std::ifstream &key, std::fstream &input, std::fstream &output)
{
	if (wybor_algorytmu == 1 || wybor_algorytmu == 2) {
		char skey[4][9] = { 0 }, sin[2][9] = { 0 }; //zmienne przechowujace znaki z plikow
		stringstream ss;
		uint32_t iin[2] = { 0 }, ikey[4] = { 0 };
		int rozmiar = 0;
		int z = 0; //literator pentli while;

				   //pobranie klucza 128 bit
		for (int x = 0; x < 4; x++)
		{
			key.get(skey[x], 9);
			ss << hex << skey[x];
			ss >> ikey[x];
			rozmiar = 8 - string(skey[x]).length(); //wyliczenie rozmiaru polowy bloku klucza
			ikey[x] = ikey[x] << rozmiar * 4; //dope³neinie 0 najmniej znaczacych bitow
			ss.clear();
		}

		while (input.get(sin[z], 9))
		{
			ss << hex << sin[z];
			ss >> iin[z];
			rozmiar = 8 - string(sin[z]).length();
			iin[z] = iin[z] << rozmiar * 4;
			ss.clear();
			if (z % 2 == 1) //szyfrowanie w co drugiej literacji
			{
				if (wybor_algorytmu == 1) {
					encrypttea(iin, ikey);
				}
				else {
					decrypttea(iin, ikey);
				}

				for (int x = 0; x < 2; x++)
				{
					ss << hex << iin[x];
					ss >> sin[x];
					ss.clear();
					output << setfill('0') << setw(8) << sin[x];
				}
				z = -1;
			}
			z++;
		}

		// Obs³uga niepe³nych 32 bit
		if (z == 1) {

			iin[1] = NULL;

			if (wybor_algorytmu == 1) {
				encrypttea(iin, ikey);
			}

			for (int x = 0; x < 2; x++)
			{
				ss << hex << iin[x];
				ss >> sin[x];
				ss.clear();
				output << setfill('0') << setw(8) << sin[x];
			}
		}

		if (wybor_algorytmu == 1) {
			cout << "Zaszyfrowano." << endl;
		}
		else {
			cout << "Odszyfrowano." << endl;
		}
	}
}


uint64_t rsa(uint64_t keypub, uint64_t n, uint64_t input) {
	uint64_t c = 1;
	/* Opcja ma³o wydajna
	for (uint64_t i = 0; i < keypub; i++) {
		c = (c*input) % n;
	}*/

	for (uint64_t i = keypub; i > 0; i /= 2) {
		if(i%2==1)
			c = (c*input) % n;
			input = (input*input) % n;
	}
	return c;
}

void encrypttea(uint32_t* v, uint32_t* k) {
	uint32_t v0 = v[0], v1 = v[1], sum = 0, i;           /* set up */
	uint32_t delta = 0x9e3779b9;                     /* a key schedule constant */
	uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];   /* cache key */
	for (i = 0; i < 32; i++) {                       /* basic cycle start */
		sum += delta;
		v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
		v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
	}                                              /* end cycle */
	v[0] = v0; v[1] = v1;
}

void decrypttea(uint32_t* v, uint32_t* k) {
	uint32_t v0 = v[0], v1 = v[1], sum = 0xC6EF3720, i;  /* set up */
	uint32_t delta = 0x9e3779b9;                     /* a key schedule constant */
	uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];   /* cache key */
	for (i = 0; i<32; i++) {                         /* basic cycle start */
		v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
		v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
		sum -= delta;
	}                                              /* end cycle */
	v[0] = v0; v[1] = v1;
}