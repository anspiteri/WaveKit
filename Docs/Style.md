# WaveKit Style Guide
---
## Documentation
**Inline Function Descriptions**^[Adapted from this source: https://www.doxygen.nl/manual/docblocks.html#cppblock]
```
/**
 * A brief history of JavaDoc-style (C-style) comments. {Simple Description}
 *
 * This is the typical JavaDoc-style C-style comment. It starts with two
 * asterisks. {Detailed Description (optional)}
 *
 * @param theory Even if there is only one possible unified theory. it is just a
 *               set of rules and equations {note: no full-stop}
 * @param code This is a second parameter
 * 
 * @return 0 on success, -1 on failure {newline after params, @return can be omitted when void}
 */
int cstyle(int theory, char code);
```