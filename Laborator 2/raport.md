# Raport Proiect 2
### Solving the Josephus problem with circular lists

<br>

## Descrierea codului

Acest proiect implementeaza rezolvarea *Josephus problem* pe cazul general cu ***n*** persoane, ***k*** skip-uri si incepand de la orice persoana ***i***.

Proiectul a fost implementat in C++ folosind programare orientata pe obiecte. Pentru rezolvarea problemei am implementat o structura sablon `Node` ce poate retine informatii de orice tip particular de date, si clasa sablon `CircularList` ce foloseste structura anterioara pentru reprezentarea datelor sub forma unei liste circulare simplu inlantuite.

Clasa `CircularList` are implementate urmatoarele metode publice:
- `add_back(valoare)` - adauga un nod la finalul listei
- `set_current(index)` - seteaza pozitia nodulului curent din lista la un index dat
- `move_current(pos)` - muta nodul curent cu ***pos*** pozitii la dreapta
- `get_next()` - returneaza informatia succesorului nodului curent
- `get_current()` - returneaza informatia nodului curent
- `delete_next()` - sterge succesorul nodului curent din lista
- `get_size()` - returneaza lungimea listei
- `operator<<` - pentru afisarea tuturor elementelor

Clasa a fost conceputa sa retina in permanenta nodul curent pe care operam, pentru a nu fi nevoiti sa facem parcurgeri inutile incepand de fiecare data de la primul nod al listei cirulare. Totodata, lista este conceputa sa isi mentina in permanenta proprietatea de circularitate dupa adaugari si stergeri de noduri.

<br>

## Teste si experimente

Programul citeste de la tastatura numerele *n*, *k* si *i* cu semnificatiile anterioare si afiseaza la fiecare pas toti oamenii ramasi inca in viata, cat si oamenii ce sunt executati, pana cand lista va mai contine un singur element.

Un exemplu de input / output:
```angular2html
Enter total number of people: 5
Enter number of people to be skipped: 2
Enter starting person #: 0

People remaining: 1 2 3 4 5
Killed person 2
People remaining: 1 3 4 5
Killed person 4
People remaining: 1 3 5
Killed person 1
People remaining: 3 5
Killed person 5
The last person alive is 3
```

*Observatie: persoana care incepe nu este luata in considerare la prima numarare a skip-urilor, numarul **i** reprezentand, de fapt, indexul nodului curent din lista circulara.*
