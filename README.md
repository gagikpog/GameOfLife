# Игра «Жизнь»
## Правила 
* Место действия этой игры — «вселенная»
* Каждая клетка на этой поверхности может находиться в двух состояниях: быть «живой» (заполненной) или быть «мёртвой» (пустой). 
* Распределение живых клеток в начале игры называется первым поколением. Каждое следующее поколение рассчитывается на основе предыдущего по таким правилам:
    - в пустой (мёртвой) клетке, рядом с которой ровно три живые клетки, зарождается жизнь;
    - если у живой клетки есть две или три живые соседки, то эта клетка продолжает жить; в противном случае, если соседей меньше двух или больше трёх, клетка умирает («от одиночества» или «от перенаселённости»)
* Игра прекращается, если
    - на поле не останется ни одной «живой» клетки
    - конфигурация на очередном шаге в точности (без сдвигов и поворотов) повторит себя же на одном из более ранних шагов (складывается периодическая конфигурация)
    - при очередном шаге ни одна из клеток не меняет своего состояния (складывается стабильная конфигурация; предыдущее правило, вырожденное до одного шага назад)

Игра написано на C++ с использованием библиотеки OpenGL.

[![Game Of Life](https://raw.githubusercontent.com/gagikpog/GameOfLife/master/GameOfLife/GameOfLife.ico)](https://github.com/gagikpog "Игра «Жизнь»")

Источник - [Википедия](https://ru.wikipedia.org/wiki/%D0%98%D0%B3%D1%80%D0%B0_%C2%AB%D0%96%D0%B8%D0%B7%D0%BD%D1%8C%C2%BB)