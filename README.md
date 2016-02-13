RechenWerk
==========

RechenWerk is a small demonstrator that shows the approximation of natural constants.
It is designed not to be efficient but to demonstrate the process of approaching the
desired value step by step without getting there. Many steps that compute fast are
prefered over big steps in accuracy that take longer to compute.
In the end it should sit in showcases and look nice.


## Approximation of *e*
The formular used to approximate *e* is an endless sum.
```
     ---  1
e =  \   ----
     /__  n!
```

This formular is very inefficient but fast to compute step by step.
```
        1                       1                         1
e ≈ 1+ --- = foo -> e ≈ foo + ----- = bar -> e ≈ bar + ------- = ...
        1                      1*2                      1*2*3
```


## Approximation of *π*
TODO
http://de.wikipedia.org/wiki/Wallissches_Produkt
