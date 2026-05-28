## Objektinio programavimo egzamino išankstinė užduotis

### Apie programą

Užduoties kodas gali vykdyti 3 skirtingus dalykus:

- Iš teksto išrinkti žodžius ir faile pateikti kiekvieną žodį (besikartojantį daugiau nei kartą) ir jo pasikartojimų skaičių;
- Iš teksto išrinkti žodžius ir faile pateikti kiekvieną žodį (besikartojantį daugiau nei kartą), jo pasikartojimų skaičių ir eilučių, kuriose žodis kartojosi, sąrašą;
- Iš teksto išrinkti URL nuorodas ir pateikti jas faile.

Programos naudojimas:

- Įvesti norimo apdoroti teksto failo pilną pavadinimą (su .txt ar kt. priesaga). Tekstinis failas turi būti "tekstai" aplanke. Prieš teksto failo įvedimą programa parodo visus tame aplanke esančius failus.
- Netrukus programa nurodo, kad išvedimas baigtas ir pati programa baigiama. Išvestis talpinama "isvestis" aplanke.

Programos diegimas:

- Atsisiųsti programos kodą (failai prisegti prie šio programos leidimo);
- Atidaryti komandinę eilutę programos aplanke;
- Įvesti komandą "make" (arba kitą jūsų turimo kūrimo įrankio komandą, pvz.: "mingw32-make", jei naudojate MinGW paketą), ją įvykdžius bus sukurtas programos paleidžiamasis failas;
  - (šiam žingsniui įvykdyti kompiuteryje turi būti įdiegtas kuris nors programų sukūrimo įrankis, pvz., MinGW-w64, MSVC)
- Įvesti "./programa", taip bus paleista programa (bus matomas prašymas įvesti failo pavadinimą ir nurodytas aplanke esančių failų sąrašas).

<sup>Pastaba: programa pritaikyta Windows operacinei sistemai.</sup>
