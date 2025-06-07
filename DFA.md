# DFA (Automa a Stati Finiti Deterministico)

Un **DFA (Automa a Stati Finiti Deterministico)** è un automa che, dopo aver letto una qualunque sequenza di input, si trova in un unico stato.

È costituita dalla quintupla $\left(Q, \Sigma, \delta, q_0, F\right)$:

- $Q$: insieme finito di stati
- $\Sigma$: insieme finito di simboli in input
- $\delta$: funzione di stato $\delta: Q \times \Sigma \rightarrow Q$ (accetta un qualsiasi stato $Q$ in combinazione con qualsiasi simbolo di input $\Sigma$, restituendo uno stato appartenente a $Q$)
- $q_0$: stato iniziale incluso in $Q$
- $F$: stati accettanti o finali inclusi in $Q$
