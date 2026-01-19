# IZP – Projekt 2: Hledání obrazců

Riešenie 2. projektu z predmetu IZP (Základy programování) na FIT VUT.

## Obsah úlohy
- **Analýza bitmapy** – spracovanie monochromatického obrázku (matica 0 a 1).
- **Hľadanie útvarov** – nájdenie najdlhšej horizontálnej/vertikálnej úsečky a najväčšieho štvorca.
- **Validácia vstupu** – kontrola formátu súboru a ošetrenie chybových stavov (`test`).
- **Algoritmizácia** – efektívne prehľadávanie 2D priestoru a práca so súradnicami.

Projekt bol vytvorený výlučne na vzdelávacie účely.

## Hodnotenie
- Získané body: **12.86 / 14**

---

<details>
<summary><b>Zobrazit kompletní zadání</b></summary>

### Popis projektu
Cílem projektu je vytvořit program `figsearch`, který v daném monochromatickém obrázku hledá nejdelší vodorovné a svislé úsečky a největší čtverce. Obrázek je uložen jako bitmapa v textovém souboru.

### Specifikace
- **Soubor:** `figsearch.c`
- **Překlad:** `cc -std=c11 -Wall -Wextra -Werror figsearch.c -o figsearch`
- **Spuštění:** `./figsearch [MOD] SOUBOR`

### Režimy (Argumenty)
- `--help`: Vypíše nápovědu.
- `test`: Zkontroluje validitu souboru (vypíše `Valid` nebo `Invalid`).
- `hline`: Najde nejdelší horizontální úsečku.
- `vline`: Najde nejdelší vertikální úsečku.
- `square`: Najde největší čtverec (obvod tvořený černými pixely).

### Vstupní data (Bitmapa)
Textový soubor, kde první dva údaje jsou rozměry (R C) a následuje matice 0 (bílá) a 1 (černá).
```text
4 5
0 0 1 1 1
0 0 1 0 1
1 0 1 1 1
1 1 1 1 1
