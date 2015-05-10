LetterClustering
================

Piotr Majcherczyk
pm334695


Preprocessing
-------------

Każdy obraz jest przerabiany na mapę 10x10 (wektor z liczbami całkowitymi).
Wartość pola {i, j} to liczba czarnych pól w odpowiadającym fragmencie obrazu.


Klasyfikator
------------

Został użyty klasyfikator DBScan.
Jest to klasyfikator wydajny i dobrze działający dla pewnej klasy problemów:
http://en.wikipedia.org/wiki/DBSCAN
Problem w tym zadaniu został sprowadzony do takiej postaci, że przypuszczalnie DBScan jest bardzo dobrym wyborem.
Podczas testowania programu dostosowane zostały stałe dla tego klasyfikatora (eps, minPts).


Wyniki
------

Program w miarę dobrze klasyfikuje podobne znaki, natomiast nie jest bardzo dokładny.
Prawdopodobnie jakość wyników mogłaby zostać poprawiona za pomocą zwiększenia rozmiaru mapy obrazu i dalszego dostosowywania stałych.
