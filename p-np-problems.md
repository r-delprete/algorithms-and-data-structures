<h1> P and NP Problems (Problemi P e NP) </h1>

<h2> 📌 Table of contents </h2>

- [Definire le classi dei problemi P e NP e dimostrare che P ⊆ NP](#definire-le-classi-dei-problemi-p-e-np-e-dimostrare-che-p--np)
  - [Definizione classi](#definizione-classi)
  - [Dimostrazione P ⊆ NP](#dimostrazione-p--np)
- [Definire la classe dei problemi NP-completi e dimostrare che se un problema NP-completo non è risolvibile in tempo polinomiale, allora anche tutti gli altri problemi NP-completi non sono risolvibili in tempo polinomiale](#definire-la-classe-dei-problemi-np-completi-e-dimostrare-che-se-un-problema-np-completo-non-è-risolvibile-in-tempo-polinomiale-allora-anche-tutti-gli-altri-problemi-np-completi-non-sono-risolvibili-in-tempo-polinomiale)
  - [Definizione classe problemi NP-completi](#definizione-classe-problemi-np-completi)
  - [Dimostrazione](#dimostrazione)
- [Definire la classe dei problemi NP-completi e dimostrare che un problema NP-completo è risolvibile in tempo polinomiale, allora anche tutti gli altri problemi NP-completi sono risolvibili in tempo polinomiale](#definire-la-classe-dei-problemi-np-completi-e-dimostrare-che-un-problema-np-completo-è-risolvibile-in-tempo-polinomiale-allora-anche-tutti-gli-altri-problemi-np-completi-sono-risolvibili-in-tempo-polinomiale)
  - [Definizione classe problemi NP-completi](#definizione-classe-problemi-np-completi-1)
  - [Dimostrazione](#dimostrazione-1)

## Definire le classi dei problemi P e NP e dimostrare che P ⊆ NP

### Definizione classi

$P = \{∃x: \{0, 1\}^* : A(x) = 1\}$

$NP = \{∃x: \{0, 1\}^*, ∃y: |y| = O(|x|ᵏ) : A(x, y) = 1\}$

### Dimostrazione P ⊆ NP

Prendiamo un problema $x$ per cui $A(x) = 1$. Trasformiamo lo stesso algoritmo di decisione $A$ in un algoritmo di decisione a due argomenti $A(x, y)$. In questo caso, $y$ ha un comportamento dummy, ossia viene aggiunto nell’algoritmo ma mai utilizzato.
Ciò implica che per gli $x$ per cui $A(x) = 1$, anche gli stessi $x$ di $A(x, y) = 1$.
Possiamo concludere dicendo che $P ⊆ NP$.

## Definire la classe dei problemi NP-completi e dimostrare che se un problema NP-completo non è risolvibile in tempo polinomiale, allora anche tutti gli altri problemi NP-completi non sono risolvibili in tempo polinomiale

### Definizione classe problemi NP-completi

$$
\left\{
\begin{array}{l}
L ∈ NP \\
∀ L' ∈ NPC → L' \leq_p L
\end{array}
\right\}
$$

### Dimostrazione

Supponiamo che il linguaggio $L ∉ P$, ciò implica che $L$ non è calcolabile in tempo polinomiale. Vogliamo dimostrare che gli altri problemi $L' ∈ NP → ∃ L' ∉ P$.
Se ne trovo uno non calcolabile in tempo polinomiale, allora tutti gli altri della stessa classe non sono risolvibili in tempo polinomiale.

Supponiamo che $∃ L ∉ P$.

Supponiamo, per assurdo, che $∃ L' ∈ NP$ e $∃ L' ∈ P$, ossia supponiamo che esista un linguaggio $L'$ risolvibile in tempo polinomiale. Questo comporta che se $L' ∈ P$ e $L' ∈ NP$, allora oer definizione tutti gli altri problemi $L ∈ NP$ sono $L \leq_p L'$ e quindi $L' ∈ P$ ma anche $L ∈ P$.

Stiamo dicendo che se $L'$ si può calcolare in tempo polinomiale, anche tutti gli altri problemi possono essere calcolati in tempo polinomiale. Ciò significa che $L$, la quale abbiamo supposto che non appartenga alla classe dei problemi $P$, è riducibile in tempo polinomiale a $L'$, per cui ci appartiene. Quindi, questo è un assurdo e $L ∈ P$.

## Definire la classe dei problemi NP-completi e dimostrare che un problema NP-completo è risolvibile in tempo polinomiale, allora anche tutti gli altri problemi NP-completi sono risolvibili in tempo polinomiale

### Definizione classe problemi NP-completi

$$
\left\{
\begin{array}{l}
L ∈ NP \\
∀ L' ∈ NPC → L' \leq_p L
\end{array}
\right\}
$$

### Dimostrazione

Supponiamo che $∃ L ∈ P$ e $∃ L ∈ NP$. Per qualsiasi $L' ∈ NP$, per definizione, si ha che $L' \leq_p L$. Quindi $L' ∈ P$.
