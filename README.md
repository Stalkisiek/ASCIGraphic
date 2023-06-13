# Generator ASCII Art

To jest prosty generator ASCII art zaimplementowany w języku C++. Program czyta plik konfiguracyjny zawierający informacje o rozmiarze płótna, nazwie pliku wynikowego oraz figurach do narysowania. Program obsługuje rysowanie prostokątów i okręgów na płótnie.

## Jak używać

1. Pobierz kod źródłowy i przejdź do katalogu projektu.
2. Skompiluj kod
   g++ main.cpp -o a
3. Utwórz plik konfiguracyjny o następującym formacie:
   <szerokość_płótna> <wysokość_płótna> <nazwa_pliku_wynikowego> <symbol_pustego_miejsca>
   <typ_figury> <dane_figury>
   <typ_figury> <dane_figury>
   ...

- `<szerokość_płótna>` i `<wysokość_płótna>` określają rozmiar płótna w znakach.
- `<nazwa_pliku_wynikowego>` to nazwa pliku, w którym zostanie zapisany ASCII art.
- `<symbol_pustego_miejsca>` to symbol używany dla pustych miejsc na płótnie.
- `<typ_figury>` może być "Kwadrat" ("Square"), "Prostokąt" ("Rectangle") lub "Okrąg" ("Circle").
- `<dane_figury>` zależą od typu figury:
  - Dla kwadratu: `<x> <y> <rozmiar> <symbol>` (współrzędne lewego górnego rogu, rozmiar i symbol)
  - Dla prostokąta: `<x> <y> <szerokość> <wysokość> <symbol>` (współrzędne lewego górnego rogu, szerokość, wysokość i symbol)
  - Dla okręgu: `<środek_x> <środek_y> <promień> <symbol>` (współrzędne środka, promień i symbol)
- Każda figura powinna być umieszczona w nowej linii.

4. Uruchom program i podaj ścieżkę do pliku konfiguracyjnego jako argument wiersza poleceń:
   ./a <plik_konfiguracyjny>

- `<plik_konfiguracyjny>` to ścieżka do pliku konfiguracyjnego utworzonego we wcześniejszym kroku.

5. ASCII art zostanie wygenerowany i zapisany w określonym pliku wynikowym. Program wyświetli wiadomość wskazującą lokalizację zapisanego pliku.

## Przykład

Poniżej znajduje się przykład pliku konfiguracyjnego (`config.txt`) oraz wynikowego ASCII art:

\*config\*
40 10
output.txt
.
Square
2 2 5 +
Rectangle
10 4 7 3 #
Circle
21 6 2 @