#include "ledring.h"
#include "state_machine.h"

// LED-Ring Setup
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, LEDBandIN, NEO_GRB + NEO_KHZ800);

// Variablen für die Eingabe
uint32_t btn_state = BTN_NOT_PRESSED;
int btn_counter = 0;
int selectedNumber = 0;
int eingabeArrayMain[12];  // Platz für 12 LEDs
int eingabeArrayMainIndex = 0;
int vorgabeCodeArrayMain[3] = {3, 11, 7};  // Vorgabecode
bool ledsAngezeigt[12] = {false};  // Speichert, ob eine LED bereits aktiviert wurde
int currentSelection = -1;  // Speichert die aktuelle Auswahl

// Debug-Funktion zur Anzeige des aktuellen Zustands
void debugState() {
    Serial.print("Aktueller Zustand: ");
    switch (state) {
        case SAFE_LOCKED:
            Serial.println("SAFE_LOCKED");
            break;
        case LEVEL_1_UNLOCKED:
            Serial.println("LEVEL_1_UNLOCKED");
            break;
        case LEVEL_2_UNLOCKED:
            Serial.println("LEVEL_2_UNLOCKED");
            break;
        case LEVEL_3_UNLOCKED:
            Serial.println("LEVEL_3_UNLOCKED");
            break;
        case SAFE_OPEN:
            Serial.println("SAFE_OPEN");
            break;
        default:
            Serial.println("Unbekannter Zustand");
            break;
    }
}

void led_ring_setup() {
    pinMode(LEDBandIN, OUTPUT);
    strip.begin();
    strip.show();
    Serial.begin(9600);  // Serielles Debugging starten
}

// LED-Farben setzen
void setLEDColorAusgabe(int pixel, int red, int green, int blue) {
    strip.setPixelColor(pixel, strip.Color(red, green, blue));
    strip.show();
}

// Alle LEDs löschen
void clearLEDs() {
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    std::fill(std::begin(ledsAngezeigt), std::end(ledsAngezeigt), false);  // Reset der LED-Anzeige
    currentSelection = -1;  // Zurücksetzen der aktuellen Auswahl
}

// Reset des Eingabe-Arrays
void resetEingabeArray() {
    std::fill(std::begin(eingabeArrayMain), std::end(eingabeArrayMain), 0);
    eingabeArrayMainIndex = 0;
    clearLEDs();  // LEDs auch zurücksetzen
}

// Funktion zur Verarbeitung der Eingabe und LED-Steuerung
void verbindung(int selectedNumber) {
    clearLEDs();
    int EingabePIN = -1;  // Initialisiere EingabePIN

    // Korrigiere den Modulo für negative Werte
    int positiveIndex = (selectedNumber % 12 + 12) % 12;

    // Setze die aktuelle LED auf Blau, wenn sie noch nicht ausgewählt wurde
    if (!ledsAngezeigt[positiveIndex]) {
        setLEDColorAusgabe(positiveIndex, 0, 0, 255);  // Aktuelle Auswahl in Blau
    }

   // Zeige bereits ausgewählte LEDs in Violett an
    for (int i = 0; i < 12; i++) {
        if (eingabeArrayMain[i] == 1) {  // Prüfen, ob die LED ausgewählt wurde
            setLEDColorAusgabe(i, 128, 0, 128);  // Leuchte Violett
        }
    }

    // Wenn der Knopf gedrückt wird und weniger als 3 Eingaben gemacht wurden
    if (btn_state == BTN_PRESSED && eingabeArrayMainIndex < 3) {
        int selectedIndex = (selectedNumber % 12 + 12) % 12;  // Korrigiere Modulo für negative Werte

        // Markiere die LED als ausgewählt, wenn sie noch nicht ausgewählt wurde
        // Speichere den aktuellen PIN im Array, falls noch nicht ausgewählt
        if (eingabeArrayMain[selectedIndex] == 0) {
            eingabeArrayMain[selectedIndex] = 1;  // Markiere die LED als "aktiviert"
            eingabeArrayMain[eingabeArrayMainIndex] = selectedIndex;  // Speichere den ausgewählten PIN im Array

            eingabeArrayMainIndex++;  // Index erhöhen

        }
        btn_state = BTN_NOT_PRESSED;  // Reset des Button-Status nach der Auswahl
    }

    // Stelle sicher, dass die LEDs, die ausgewählt wurden, violett bleiben
    for (int i = 0; i < 12; i++) {
        if (ledsAngezeigt[i]) {
            setLEDColorAusgabe(i, 128, 0, 128);  // Violette LEDs für alle, die ausgewählt wurden
        }
    }
}

// Funktion zum Vergleich der eingegebenen Werte mit dem vorgegebenen Code
void arrayVergleich() {
    bool isCodeCorrect = true;

    // Vergleiche den eingegebenen Code mit dem vorgegebenen Code
    for (int i = 0; i < 3; i++) {
        if (eingabeArrayMain[i] != vorgabeCodeArrayMain[i]) {
            isCodeCorrect = false;
            break;
        }
    }

    if (isCodeCorrect) {
        // Falls der Code korrekt ist, leuchten alle LEDs grün
        for (int i = 0; i < 12; i++) {
            setLEDColorAusgabe(i, 0, 255, 0);  // Leuchte Grün
        }

        // Event in der State Machine auslösen
        state_machine(INPUT_1_ACCEPTED);

        // Aktuellen Zustand für Debug-Zwecke anzeigen
        debugState();

        // 10 Sekunden Verzögerung
        delay(10000);

        // Reset für die nächste Eingabe
        resetEingabeArray();
    } else if (eingabeArrayMainIndex >= 3) {
        // Falls der Code falsch ist, leuchten alle LEDs rot
        for (int i = 0; i < 12; i++) {
            setLEDColorAusgabe(i, 255, 0, 0);  // Leuchte Rot
        }

        // Event in der State Machine auslösen
        state_machine(INPUT_REFUSED);

        // Aktuellen Zustand für Debug-Zwecke anzeigen
        debugState();

        // 10 Sekunden Verzögerung
        delay(10000);

        // Reset für die nächste Eingabe
        resetEingabeArray();
    }
}