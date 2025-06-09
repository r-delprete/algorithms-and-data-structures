# SJF (Shortest Job First)

## Assignment

L'aereoporto di Capodichino ha fatto costruire una nuova pista di decollo e di atterraggio. Il direttore dell'aereoporto decide di utilizzare la pista per servire i nuovi N aerei che dovranno decollare dall'aereoporto.

Supponiamo che `T[i]` sia il tempo necessario all'i-esimo aereo per decollare, scrivere un algoritmo, in pseudocodice, che utilizzando la struttura dati coda di priorità minimizzi il tempo totale di attesa (o turnaround) degli N aerei per decollare (7 punti).

## Input parameter

- `T`: an array of integers, where `T[i]` represents the time required for the _i-th_ plane to take off
- `N`: total airplanes

## Output

Return minimum total waiting time (**turnaround**) for all N planes

## Pseudo-code

```
sjf(T, N):
    queue = ∅       // min priority queue

    for i = 1 to N:
        queue.insert(T[i])

    curr_time = 0
    tot_wait = 0

    while queue != ∅:
        t = queue.extract_min()          // min launch airplane time
        curr_time = curr_time + t
        tot_wait = tot_wait + curr_time

    return tot_wait
```
