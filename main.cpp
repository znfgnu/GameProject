/**

Stany aplikacji:
 - klasa Application jest singletonem
 - klasa Application posiada stos stanów, którym zarzadza
 - zmiana stanu polega na wrzuceniu nowego stanu na stos
 - wykonywany jest zawsze stan z gory stosu

Klasy:
 - Application - klasa programu/aplikacji, w ramach zachowania obiektowosci
 - AppState - klasa bazowa dla wszystkich stanów aplikacji (intro/menu/rozgrywka/opcje/etc)
 - AS* - klasy pochodne AppState
 =====
 - TextureManager - klasa zarzadzajaca teksturami
 - ConfigManager
    - klasa wczytujaca ustawienia (wczytuje plik z domyslnymi ustawieniami, a nastepnie plik z ustawieniami uzytkownika - adpisujac jedynie elemeny wystepujace w pliku uzytkownika)
    - metody getString(key), getInt(key) - zwracaja pozadana wartosc, automatycznie robia konwersje
    - moze od razu trzymac w ConfigManagerze zamiast string-string to string-oczekiwanytyp? (zawsze mozna ograniczyc odwolania do config managera) // raczej string-string
    - import z pliku / eksport do pliku
 - SoundManager - ??
 - CollisionManager - ?? (obiekty z pozycjami? jak aktualizowac? etykiety?)
 - Drawable - cos do rysowania?
 - D* - klasy pochodne Drawable



*/

#include "Application.h"

int main ( int argc, char** argv )
{
    return Application::getInstance()->run(argc, argv);
}
