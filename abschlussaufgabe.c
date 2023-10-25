#include <stdio.h>
#include <string.h>
#include <stdbool.h> // Für den Datentyp bool

// Funktion zur Überprüfung, ob ein Zeichen ein Whitespace-Zeichen ist
bool isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r'; // \n für Unix/Linux, \r für Windows
}

int main() {
    char filename[100];     // Zeichenarray, dazu da, um den Dateinamen zu speichern (maximal 100 Zeichen)
    char target_Char;       // Variable, um das gesuchte Zeichen zu speichern
    
    int char_Count = 0;     // Anzahl des gewünschten Zeichens
    int word_Count = 0;     // Anzahl der Wörter in der Datei
    int lower_Count = 0;    // Anzahl der Kleinbuchstaben
    int upper_Count = 0;    // Anzahl der Großbuchstaben

    bool inWord = false;    // Zustand, ob wir uns in einem Wort befinden (Anfangs nicht, weil wir uns noch in keinem Wort befinden bzw. eingegeben haben)

    while (1) {
        // Eingabe des Dateinamens von Nutzer
        printf("Bitte geben Sie den Dateinamen ein: ");
        scanf("%s", filename);

        // Überprüfung der Dateierweiterung
        int len = strlen(filename);
        if (len < 4 || (strcmp(filename + len - 4, ".txt") != 0 && strcmp(filename + len - 2, ".c") != 0)) {
            printf("Ungültige Dateierweiterung. Nur .txt und .c Dateien sind erlaubt.\n");
            continue; // Zurück zur Eingabe des Dateinamens
        }                   /*Zuerst überprüfe ich ob die Länge Dateinamens kleiner als 4 Zeichen ist,
                            danach ob die letzten 4 Zeichen des Dateinamens NICHT mit ".txt" übereinstimmen,
                            dann ob die letzten 2 Zeichen des Dateinamens NICHT mit ".c" übereinstimmen, 
                            schließlich wenn mindestens eine dieser Bedingungen wahr ist, sollte es mir einen 
                            Fehler anzeigen*/

        // Eingabe des Buchstabens, welcher gezählt werden soll
        printf("Bitte geben Sie den Buchstaben oder Sonderzeichen ein, den Sie zählen möchten: ");
        scanf(" %c", &target_Char);  // Leerzeichen vor %c, um eventuelle Whitespaces zu überspringen

        // Öffnen der Datei zum Lesen
        FILE *file = fopen(filename, "r");
        if (file == NULL) {                                             //falls öffnen nicht möglich ist 
            printf("Die Datei konnte nicht geöffnet werden.\n");
            continue;                                                   // Zurück zur Eingabe des Dateinamens
        }

        // Schleife zum Durchsuchen der Datei nach Zeichen und Wörtern
        char c;
        /* Solange ein Zeichen aus der Datei gelesen wird und das Dateiende (EOF) nicht erreicht ist, 
        wird der Codeblock innerhalb der Schleife ausgeführt, um jedes Zeichen zu überprüfen*/
        while ((c = fgetc(file)) != EOF) {
        if (c == target_Char || c == target_Char - ('a' - 'A')) {   // Kleinbuchstabe und zugehöriger Großbuchstabe
        if (c >= 'a' && c <= 'z'){
            lower_Count++;                                          // Kleinbuchstabe gefunden
        } else if (c >= 'A' && c <= 'Z'){
            upper_Count++;                                          // Großbuchstabe gefunden
        }
        char_Count++;                                               // Zeichen zählen
        }
    
        if (isWhitespace(c)) {
        inWord = false;                                             // Wenn Whitespace gefunden wird, befinde ich mich nicht mehr in einem Wort
        } else if (!inWord) {
        inWord = true;                                              // Wenn Nicht-Whitespace-Zeichen gefunden wird, beginnt ein neues Wort
        word_Count++;                                               // Wort zählen
        }
        }

        fclose(file); // Datei schließen

        // Ausgabe der Ergebnisse
        printf("Anzahl des Buchstabens oder Sonderzeichens '%c': %d\n", target_Char, char_Count);
        printf("Anzahl der Wörter: %d\n", word_Count);
        printf("Anzahl der Kleinbuchstaben von '%c': %d\n", target_Char, lower_Count);
        printf("Anzahl der Großbuchstaben von '%c': %d\n", target_Char, upper_Count);
        

        // Optionen anlegen
        int choice;
        printf("Bitte auswählen:\n");
        printf("1. Nach einem anderen Buchstaben, Sonderzeichen oder Worten suchen\n");
        printf("2. Programm beenden\n");
        printf("3. Mit einer neuen Datei starten\n");
        printf("Ihre Auswahl: ");
        scanf("%d", &choice);

        
        
        // Schleife, die abhängig von der Auswahl des Nutzers ist 
        if (choice == 1) {                              // Wenn der Nutzer Option 1 auswählt:          
            char_Count = 0;                                 // Setzt den Zähler für das Zeichen zurück               
            word_Count = 0;                                 // Setzt den Zähler für Wörter zurück                 
            lower_Count = 0;                                // Setzt den Zähler für Kleinbuchstaben zurück
            upper_Count = 0;                                // Setzt den Zähler für Großbuchstaben zurück
            inWord = false;                                             // Ich bin außerhalb eines Worts
            getchar();                                                  // Lösche den Zeilenumbruch im Eingabepuffer
            continue;                                                               // Springe zurück zur Eingabe des Buchstabens       
        } else if (choice == 2) {                       // Wenn der Nutzer Option 2 auswählt (Programm beenden):
            break;                                                      // Beende die Schleife, um das Programm zu beenden 
        } else if (choice == 3) {                       // Wenn der Nutzer Option 3 auswählt (mit neuer Datei starten):
            char_Count = 0;                                 // Setzt den Zähler für das Zeichen zurück
            word_Count = 0;                                 // Setzt den Zähler für Wörter zurück
            lower_Count = 0;                                // Setzt den Zähler für Kleinbuchstaben zurück
            upper_Count = 0;                                // Setzt den Zähler für Großbuchstaben zurück
            inWord = false;                                             // Ich bin außerhalb eines Worts   
            getchar();                                                              // Lösche den Zeilenumbruch im Eingabepuffer        
        } else {                                        // Wenn der Nutzer eine ungültige Option wählt:
            printf("Ungültige Auswahl.\n");                 // Gibt Fehlermeldung aus
            break;                                                      // Beende die Schleife, um das Programm zu beenden
        }
    }

    return 0;
}
