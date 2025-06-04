# DFA (Automa a Stati Finiti Deterministico)

Un **DFA (Automa a Stati Finiti Deterministico)** è un automa che, dopo aver letto una qualunque sequenza di input, si trova in un unico stato.

È costituita dalla quintupla $\left(Q, Σ, δ, q₀, F\right)$:

- $Q$: insieme finito di stati
- Σ: insieme finito di simboli in input
- δ: funzione di stato δ: $Q × Σ → Q$ (accetta un qualsiasi stato $Q$ in combinazione con qualsiasi simbolo di input Σ, restituendo uno stato appartenente a $Q$)
- q₀: stato iniziale incluso in $Q$
- $F$: stati accettanti o finali inclusi in $Q$
