# LibLigma

A **Li**brary which **G**enerates **Ma**chines

# Documentation

## Conventions

The `target` symbol is the input `start` symbol, it's called like this because the real `start` symbol, which is required for building the automaton, is initialized as follow.

The last 3 symbols are respectivly:
- S: Inner start symbol, non terminal, widely called *start*
- $: Inner EOL symbol, terminal, widely called *eol*
- e: Inner empty symbol, terminal, widely called *epsilon*

as in

```
S' --> S $
A --> B | e
```
