#include <iostream>
#include <string>

using namespace std;

#define N 4
#define V 10

int matrice[N][N];

void riempiMatrice(){
	srand(time(NULL));
	for(int r=0;r<N;r++){
		for(int c=0;c<N;c++){
			matrice[r][c] = rand() % V + 1; 
		}
	}
}

void riempiMatriceTastiera(){
	for(int r=0;r<N;r++){
		cout << "INSERIMENTO RIGA " << r << endl;
		for(int c=0;c<N;c++){
			cout << "Dammi l'elemento di indici " << r << "," << c << ":";
			cin >> matrice[r][c]; 
		}
	}
}

void visualizzaMatrice(){
	for(int r=0;r<N;r++){
		for(int c=0;c<N;c++){
			cout << matrice[r][c] << "\t"; 
		}
		cout << endl;
	}
}

int sommaRiga(int r){
	int somma = 0;
	for(int c=0;c<N;c++){
		somma += matrice[r][c];
	}
	return somma;
}

int sommaColonna(int c){
	int somma = 0;
	for(int r=0;r<N;r++){
		somma += matrice[r][c];
	}
	return somma;	
}

int main(){
	// Individuare la riga o colonna con la somma massima
	
	riempiMatrice();
	// riempiMatriceTastiera();
	visualizzaMatrice();
	
	// troviamo la riga che ha la somma massima
	int indice_riga_max = 0;
	int somma_max_riga = sommaRiga(0);
	
	int s;
	for(int r=1;r<N;r++){
		s = sommaRiga(r);
		if(s > somma_max_riga){
			indice_riga_max = r;
			somma_max_riga = s;
		}
	}
	
	// troviamo la colonna con somma massima
	int indice_colonna_max = 0;
	int somma_max_col = sommaColonna(0);
	
	for(int c=1;c<N;c++){
		s = sommaColonna(c);
		if(s > somma_max_col){
			indice_colonna_max = c;
			somma_max_col = s;
		}
	}
	
	if(somma_max_riga > somma_max_col)
		cout << "La somma massima "<< somma_max_riga << " si trova nella riga " << indice_riga_max;
	else{
		if(somma_max_riga < somma_max_col)
			cout << "La somma massima "<< somma_max_col << " si trova nella colonna " << indice_colonna_max;
		else
			cout << "La somma massima " <<
				somma_max_col << " si trova sia sulla riga " << indice_riga_max << " che sulla colonna " <<
				indice_colonna_max;	
	}

	return 0;
}