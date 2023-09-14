# FBO download test

![Screenshot of sortingExample](sortingExample.png)

### An attempt at benchmarking FBO downloads

A shader produces data in the FBO, which is processed depending on mode, which is specified by hitting the corresponding key:

 - mode 0: no download
 - mode 1: download with current method
 - mode 2: download with proposed ES method
 - mode 3: download with fastFboReader
 
Thus, this needs the ofxFastFboReader addon.

Vertical sync is disabled, allowing > 60fps values.
 
Results:

| system  | mode 0 | mode 1 | mode 2 | mode 3 |
| - | -  | - | - | - |
| M1 (8 core / 8 gpu)  | 234-360 | 60 | 70-72 | 117-119 |
| M2 pro (12 core / 19 gpu) |
 i7990K / nvidia 2080SUPER
