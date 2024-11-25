# Temps d'éxécutions du programme

- **Carte :** mars.map (7x6)

| Mouvements | Construction<br/>(buildTree) | Feuille minimale<br/>(minimalNode) | Chemin<br/>(findNodePath) | Guidage<br/>Complet |
|:----------:|:----------------------------:|:----------------------------------:|:-------------------------:|:-------------------:|
| 3 parmi 5  |          0ms - 1ms           |                0ms                 |            0ms            |        79ms         |
| 5 parmi 9  |          1ms - 3ms           |             0ms - 1ms              |            0ms            |        38ms         |
| 7 parmi 13 |        42 ms - 332 ms        |            0ms - 63 ms             |            0ms            |       1.666s        |
| 9 parmi 15 |           54.193s            |               365ms                |            0ms            |       181.21s       |

- **Carte :** mars.map *with slopes* (7x6)

| Mouvements | Construction<br/>(buildTree) | Feuille minimale<br/>(minimalNode) | Chemin<br/>(findNodePath) | Guidage<br/>Complet |
|:----------:|:----------------------------:|:----------------------------------:|:-------------------------:|:-------------------:|
| 3 parmi 5  |          0ms - 1ms           |                0ms                 |            0ms            |        105ms        |
| 5 parmi 9  |          0ms - 2ms           |             0ms - 1ms              |            0ms            |        102ms        |
| 7 parmi 13 |         59ms - 359ms         |             1ms - 66ms             |            0ms            |        768ms        |
| 9 parmi 15 |           50.314s            |               484ms                |            0ms            |       197.65s       |
