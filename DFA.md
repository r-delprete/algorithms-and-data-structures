# DFA definition

Un DFA è un automa che, dopo aver letto una qualunque sequenza di input, si trova in un unico stato.
È costituita dalla quintupla (Q, Σ, δ, q₀, F):
- Q: insieme finito di stati
- Σ: insieme finito di simboli in input
- δ: funzione di stato δ: Q x Σ -> Q (accetta un qualsiasi stato QQ in combinazione con qualsiasi simbolo di input Σ, restituendo uno stato appartenente a Q)
- q₀: stato iniziale incluso in Q
- F: stati accettanti o finali inclusi in Q