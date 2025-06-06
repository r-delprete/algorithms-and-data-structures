# Macchina di Turing

La **macchina di Turing** è un automa a stati finiti con nastro infinito su cui si può leggere e scrivere dati.
Viene definita dalla settupla $M = \left(Q, \Sigma, \Gamma, \delta, q_0, \beta, F\right)$:

- $Q$: insieme finito degli stati del controllo
- $\Sigma$: insieme finito dei simboli in input
- $\Gamma$: insieme completo dei simboli del nastro
- $\delta$: funzione di transizione
- $q_0$: stato iniziale del controllo
- $\beta$: simbolo detto _Blank_
- $F$: insieme degli stati finali o accettanti inclusi in $Q$

## Stati accettanti

Gli **stati accettanti** sono stati in cui la macchina, dopo aver eseguito la computazione su un input, raggiunge uno stato che indica che _l'input è stato accettato_.
