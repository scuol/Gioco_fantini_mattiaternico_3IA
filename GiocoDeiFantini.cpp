#include <iostream>
#include <ctime>
#include <cmath>
#include <windows.h>

#ifndef CURSORI_H_INCLUDED
#define CURSORI_H_INCLUDED

using namespace std;

struct fantino {
    int colore = 0; // Colore identificativo del fantino
    int avanzamento = 0; // Di quanti quadratini è avanzato il fantino
    bool arrivato = false; // Se il fantino è arrivato
};

int numeroFantini = 1; // Numero di fantini
int lunghezzaPercorso = 25; // Quanto è lungo il percorso

void inserisciParametri(); // Gestisce i parametri della gara

void avviaGioco(); // Fa' iniziare la gara tra fantini

void disegnaDadi(const int dado[]); // Disegna i dadi nel terminale

void disegnaFantino(fantino fantino[]); // Disegna il fantino nel terminale

void posizionaCursore(int x, int y); // Posiziona il cursone alle coordinate xy

int main() {
    int menu;

    srand(time(nullptr));

    do {
        system("cls");

        cout << "1. Inserisci parametri" << endl;
        cout << "2. Avvia gioco" << endl;
        cout << "3. Esci" << endl;

        do cin >> menu; // Scelta dell' argomento nel menu
        while (menu < 1 || menu > 3); // La scelta deve essere valida

        switch (menu) {
            case 1:
                inserisciParametri();
                break;
            case 2:
                avviaGioco();
                break;
            default:
                break;
        }
    } while (menu != 3); // Se la scelta è 3 termina l'esecuzione del programma

    return 0;
}

void inserisciParametri() {
    cout << "Quanti sono i fantini? (1-4): ";
    do cin >> numeroFantini;
    while (numeroFantini < 1 || numeroFantini > 4);

    cout << "Quanto e' lungo il percorso? (25-65): ";
    do cin >> lunghezzaPercorso;
    while (lunghezzaPercorso < 25 || lunghezzaPercorso > 65);
}

void avviaGioco() {
    bool computer = false;
    if (numeroFantini == 1) { // Controlla se c'è solo un giocatore
        numeroFantini = 2; // In questo caso i fantini diventano 2
        computer = true; // Uno di loro è un computer
    }

    fantino fantino[numeroFantini]; // Array di fantini
    for (int i = 0; i < numeroFantini; i++)
        fantino[i].colore = 2 + i; // Assegna a ogni fantino il suo colore

    int turno = rand() % numeroFantini; // Il fantino che parte per primo è randomico

    int ordineArrivo[numeroFantini]; // Ordine di arrivo
    int posizione = 0; // Che posizione nel podio è libera 0-3

    while (posizione < numeroFantini) {
        system("cls"); // Pulisce il terminale

        posizionaCursore(lunghezzaPercorso + 16, 0);
        cout << "||";
        posizionaCursore(lunghezzaPercorso + 16, numeroFantini * 7);
        cout << "||";

        int dado[2] = {rand() % 6 + 1, rand() % 6 + 1}, // Inizializza i dadi
                avanzamento = dado[0] + dado[1]; // Prossimo avanzamneto del fantino


        if (dado[0] == dado[1]) // Controlla se i dado hanno lo stesso valore
            avanzamento += ceil((double) avanzamento * 0.3); // Se si aumenta l'avanzamento del 30%

        fantino[turno].avanzamento += avanzamento; // Aggiorna l'avanzamento del fantino

        if (fantino[turno].avanzamento >= lunghezzaPercorso) { // Controlla se il fantino è arrivato
            fantino[turno].arrivato = true;  
            ordineArrivo[posizione] = turno + 1;
            posizione++;
        } else if (fantino[turno].avanzamento % 5 == 0) // Se l'avanzamento è un multiplo di 5 lo riduce di 6
            if (fantino[turno].avanzamento < 6)
                fantino[turno].avanzamento = 0;
            else fantino[turno].avanzamento -= 6;

        disegnaFantino(fantino); // Disegna il fantino
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); 
        disegnaDadi(dado); // Disegna i dadi

        if (posizione < numeroFantini) { // Se non sono arrivati tutti i fantini
            do turno = turno == numeroFantini - 1 ? 0 : turno + 1; // Passa il turno a un'altro fantino
            while (fantino[turno].arrivato == true); // Se il prossimo fantino è già arrivato passa al successivo
        }

        if (posizione != numeroFantini) { // Se non sono arrivati tutti i fantini
            if (computer == false) // Se il computer non gioca
                system("pause"); // Aspetta che venga premuto un tasto
            else if (turno % 2 == 0) // Altrimenti aspetta se sta al giocatore
                system("pause");
            else Sleep(800);
        }
    }

    cout << "Ordine di arrivo: ";
    for (int fantinoPosizione: ordineArrivo) // Per ogni fantino
        cout << fantinoPosizione << ' '; // Scrive il numero corripondente al fantino in ordine di arrivo
    cout << endl;
    system("pause");

// Se non si aggiornano i parametri dal menu il computer gioca anche la gara dopo
    if (computer == true) 
        numeroFantini = 1;  
}

void disegnaDadi(const int dado[]) {
    for (int i = 0; i < 2; i++) { // Per ognuno dei 2 dadi
        Sleep(400); // Aspetta 0,4 secondi
        switch (dado[i]) { // Disegna la faccia del dado corrispondente al valore
            case 1:
                cout << R"(
+-----+
|     |
|  0  |
|     |
+-----+)" << endl;
                break;
            case 2:
                cout << R"(
+-----+
|   0 |
|     |
| 0   |
+-----+)" << endl;
                break;
            case 3:
                cout << R"(
+-----+
|   0 |
|  0  |
| 0   |
+-----+)" << endl;
                break;
            case 4:
                cout << R"(
+-----+
| 0 0 |
|     |
| 0 0 |
+-----+)" << endl;
                break;
            case 5:
                cout << R"(
+-----+
| 0 0 |
|  0  |
| 0 0 |
+-----+)" << endl;
                break;
            case 6:
                cout << R"(
+-----+
| 0 0 |
| 0 0 |
| 0 0 |
+-----+)" << endl;
                break;
            default: break;
        }
    }
}

void disegnaFantino(fantino fantino[]) {
    for (int i = 0; i < numeroFantini; i++) { // Per ogni fantino
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fantino[i].colore); // Assegna al terminale il colore del fantino

        posizionaCursore(fantino[i].avanzamento, i * 7 + 1);
        cout << "            .''  ";
        Sleep(50);
        posizionaCursore(fantino[i].avanzamento, i * 7 + 2);
        cout << "  ._.-.___.' (`\\";
        Sleep(50);
        posizionaCursore(fantino[i].avanzamento, i * 7 + 3);
        cout << " //(        ( `' ";
        Sleep(50);
        posizionaCursore(fantino[i].avanzamento, i * 7 + 4);
        cout << "'/ )\\ ).__. )   ";
        Sleep(50);
        posizionaCursore(fantino[i].avanzamento, i * 7 + 5);
        cout << "' <' `\\ ._/'\\  ";
        Sleep(50);
        posizionaCursore(fantino[i].avanzamento, i * 7 + 6);
        cout << "   `   \\     \\ ";
        Sleep(50);
    }
}

void posizionaCursore(int x, int y) {
    COORD CursorPos = {(short) x, (short) y}; // Cordinate del posizionamento
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Recupera l' handle per l' output
    SetConsoleCursorPosition(hConsole, CursorPos); // Posiziona il cursore
}

#endif // CURSORI_H_INCLUDED
