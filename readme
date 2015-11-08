PSZT Projekt JP.AE2

------------------------------
            TEMAT
------------------------------
Program ma wyznaczać przy pomocy algorytmu ewolucyjnego najlepszą trasę między określonymi punktami na podstawie zadanych przez użytkownika kryteriów.

------------------------------
      USTALENIA WSTĘPNE
------------------------------
1. Program otrzymuje niezbędne dane dotyczące połączeń między miastami w pliku tekstowym.
2. Użytkownik wprowadza swoje preferencje ustalając wagi dla dostępnych kryteriów wyboru optymalnej trasy.
3. Program na wyjściu podaje najlepszą trasę lub n najlepszych tras, z możliwością zapisu do pliku.
4. Komunikacja z programem jest realizowana poprzez GUI.

------------------------------
 USTALENIA PROJEKTOWE - MODEL
------------------------------
Osoba odpowiedzialna:
AR

Środowisko:
C++14 (GCC 4.9.3) + boost 1.59

Założenia:
1. Połączenia między miastami są opisane w zewnętrznym pliku tekstowym w postaci grafu.
2. Trasa jest wyznaczana za pomocą algorytmu ewolucyjnego.
    2a. Osobnikami są trasy.
    2b. Cechami osobników są kolejne wierzchołki grafu przez które prowadzi trasa.
    2c. Krzyżowanie odbywa się na zasadzie losowego podziału cech rodziców między potomków.
    2d. Osobniki o różnej liczbie cech są normalizowane poprzez dodanie do listy cech krótszej trasy w losowych miejscach pustych wierzchołków, usuwanych po przeprowadzeniu krzyżowania.
    2e. Mutacje pozwalają losowo zmienić wierzchołek na inny, usunąć go, lub wstawić nowy wierzchołek między już istniejące.
    2f. Trasy są ścieżkami prostymi i nie mogą zawierać nieistniejących krawędzi. Osobniki nie spełniające tych wymagań automatycznie kwalifikują się do odrzucenia.
    2g. Program pozwala na wybór kryterium zakończenia algorytmu: czas wykonania, liczba iteracji, akceptowalność rozwiązania.
3. Przed uruchomieniem algorytmu ewolucyjnego graf jest sprawdzany pod kątem obecności wierzchołka początkowego i końcowego w tej samej składowej.
4. Składowe niezawierające wierzchołka początkowego i końcowego są odrzucane.
5. Model dostarcza funkcję zwracającą n-tą najlepszą trasę z obecnej iteracji, funkcję pozwalającą zapisać obecną populację do wskazanego pliku oraz funkcję pozwalającą wstrzymać wykonywanie algorytmu.

----------------------------
Ustalenia projektowe – Kontroler

Osoba odpowiedzialna:
TJ (sigrond)

Środowisko:
C++11 + sockets + pthread / thread z C++11

Założenia:
 1.	Kontroler powinien zostać uruchomiony zanim użytkownik zacznie wprowadzać polecenia do GUI (lub innymi słowy: zanim widok zacznie wysyłać zapytania).
 2.	Kontroler po uruchomieniu tworzy gniazdo (socket) w nowym wątku (lub wątkach – fork server) i nasłuchuje na porcie. Po nawiązaniu połączenia może obsługiwać polecenia (data):
 a)	Wprowadzanie lub modyfikowanie danych i ustawień.
 b)	Uruchomienie obliczeń (algorytm ewolucyjny w modelu).
 c)	Zwracanie stanu obliczeń lub wyniku.
 d)	Zatrzymywanie obliczeń
 3.	Kontroler przekazuje dane i ustawienia do modelu, oraz pobiera z niego stan i wyniki.
 4.	Kontroler zażądza życiem modelu, uruchamia go w osobnym wątku (lub wątkach). Może też zażądzić zatrzymywanie wątków modelu.

Ustalenia komunikacji MVC:
 1.	Komunikacja z widokiem
•	Kontroler NIE serwuje pliku widoku, ewentualnie może go uruchomić przez shella lub kontroler i widok mogą zostać uruchomione skryptem.
•	Spodziewam się, że widok będzie plikiem HTML otwieranym w przeglądarce i będzie używał JavaScript/jQuery/AJAX get do wysyłania (prostych) zapytań HTMLowych do kontrolera. Aczkolwiek dzięki zastosowaniu wzorca MVC i wykożystaniu socketów do komunikacji można widok wymienić na zupełnie inny w innej technologii o ile będzie się stosował do ustaleń protokołu komunikacji.
•	Do komunikacji będzie potrzebne częściowe zaimplementowanie HTTP/1.1 - RFC 2616. Chodzi głównie oczywiście o sam nagłówek.
•	Odpowiedzi i dzałania kontrolera będą zależały od sekcji data w get. Niech na chwilę obecną będzie
{polecenie: 'dane', nazwa_parametru: 'wartość_parametru'}
{polecenie: 'licz'}
{polecenie: 'wynik'}
{polecenie: 'stop'}
•	Dane do widoku będą wysyłane jednym ze standardów AJAXa np. json lub xml. Co i jak dokładnie będzie wy tych danch wymaga dodatkowych ustaleń już bardziej związanch z implementacją.
 2.	Komunikacja z modelem będzie znacznie prostrza niż z widokiem. Należy ustalić, czy kontroler po prostu wywołuje metody modelu, czy raczej kontroler tylko uruchomi proces modelu i dalej będzie się komunikował przez kolejkę blokującą.
 
------------------------------
 Ustalenia projektowe - Widok
------------------------------

Osoba odpowiedzialna
RŚ (Antyradek)

Środowisko:
HTML5 + Javascript + AJAX + jQuery + CSS3

Założenia:
1. Widok będzie działać w przeglądarce jako klient i traktować Kontroler jako serwer.
2. Komunikacja odbywać się będzie za pomocą Javascript i AJAX implementowanej przez jQuery.
3. Użytkownik będzie miał do ustawień:
	a) Weryfikację i modyfikację danych.
	b) Ustalenie parametrów działania.
	c) Opcję rozpoczęcia kalkulacji.
	d) Opcję przerwania kalkulacji.
4. Dane będą asynchronicznie wysyłane i odbierane za pomocą XML (lub JSON).
5. Widok będzie pełnił funkcje pomocnicze do obsługi programu.
