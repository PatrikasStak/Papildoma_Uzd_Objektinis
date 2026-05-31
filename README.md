# Žodžių dažnumas ir URL paieška

Programa nuskaito tekstinį failą, suskaičiuoja žodžių pasikartojimus naudojant asociatyvų konteinerį (`std::map`) ir išrenka URL adresus.

## Kompiliavimas

```
make
```

## Naudojimas

1. Įkelkite tekstą į `text.txt` failą (ne mažiau 1000 žodžių, tekstas turi turėti URL adresų).
2. Paleiskite programą:
```
./program
```
3. Pasirinkite rūšiavimo būdą:
   - `1` — rūšiuoti pagal žodžių kiekį (mažėjančia tvarka)
   - `2` — rūšiuoti pagal abėcėlę

## Išvesties failai

| Failas | Turinys |
|--------|---------|
| `count.txt` | Žodžiai, kurie pasikartojo daugiau nei vieną kartą, su jų skaičiumi |
| `lines.txt` | Kryžminių nuorodų lentelė — kuriose eilutėse kiekvienas žodis buvo paminėtas |
| `urls.txt` | Visi tekste rasti URL adresai |

## Valymas

```
make clean
```
