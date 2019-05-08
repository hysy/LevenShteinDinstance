# LevenShteinDinstance
Caluclate LevenShteinDistance and Restore Operation

# Implementation
Used naive Dynamic Programming.

- Time complexity
  - `O(|p||s|)`
- Space complexity)
  - `O(|p||s|)`
# Usage
```
hysy@trin ~/LevenShteinDinstance> g++ -std=c++14 LevenShteinDinstance.cpp
hysy@trin ~/LevenShteinDinstance> ./a.out hogefuga hfugoge
convert: hogefuga -> hfugoge !

(1, 1) operation: delete
  now pattern: hgefuga
(2, 1) operation: delete
  now pattern: hefuga
(3, 1) operation: delete
  now pattern: hfuga
(7, 4) operation: replace
  now pattern: hfugo
(8, 5) operation: insert
  now pattern: hfugog
(8, 6) operation: insert
  now pattern: hfugoge

LevenShteinDistance: 6
[Confirmation] Recursive LevenShteinDistance: 6
```
