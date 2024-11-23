# How the maps work

Maps are stored in `.map` text file in `/maps` directory.
- The first line correspond to the dimension of the map (height, width)

```
 O                           N
  ┌ ⭢ x (width)              ⭡
  ⭣                      W ⭠ ┼ ⭢ E
  y                ⭢         ⭣
(height)                     S
```

- The second line correspond to the starting localisation of the rover (x, y, orientation).

| Int | Orientation |
|:---:|-------------|
|  0  | NORTH       |
|  1  | EAST        |
|  2  | SOUTH       |
|  3  | WEST        |


- The rest of the line correspond to the map matrix with integers representing soils.

| Int | Soil type    | Influence                     |
|:---:|--------------|-------------------------------|
|  0  | BASE_STATION | Final rover destination       |
|  1  | PLAIN        | No impact                     |
|  2  | ERG          | Reduced next move by 10 meter |
|  3  | REG          | Reduced next phase move by 1  |
|  4  | CREVASSE     | Kill the rover (no respawn)   |