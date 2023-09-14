# FBO download test

![Screenshot of sortingExample](sortingExample.png)

### An attempt at benchmarking FBO downloads with 0 samples

A shader produces data in the FBO, which is processed depending on mode, which is specified by hitting the corresponding key:

 - mode 0: no download
 - mode 1: download with current method
 - mode 2: download with proposed ES method
 - mode 3: download with fastFboReader
 
Thus, this needs the ofxFastFboReader addon.

Vertical sync is disabled, allowing > 60fps values.
 
Results (with otherwise tranquil systems):

| system | OS | build | mode 0 | mode 1 | mode 2 | mode 3 | notes |
| - | - | - | - | - | - |
| M2 pro (6(12) core / 19 gpu)   | macOS 13.4 | debug   | 234-360 | 60-61 | 70-72 | 117-119 | AB/20230913 |
|                                |            | release | 234-360 | 60-61 | 70-72 | 117-119 | AB/20230913 | 
| M1 (8/4 cores ; 8 gpu)         | macOS 13.4 | debug   | 1030-1080 | 146-147 | 177-178 | 219-225 | AB/20230913 |
|                                |            | release | 1030-1100 | 148-149 | 177-178 | 200-230 | AB/20230913 |
| i7 2.6gHz (6/12 cores ; 560X)  | macOS 13.4 | debug   |  270-320  |  48-49  |  60-62  | 120-130 | AB/20230913 |
|                                |            | release |  330-390  |  49-50  |  60-61  | 145-150 | AB/20230913 |
| i7990K ; nvidia 2080SUPER      | linux      | debug   | 234-360 | 60-61 | 70-72 | 117-119 | AB/20230914 |
|                                |            | release | 234-360 | 60-61 | 70-72 | 117-119 | AB/20230914 |

results are eyeballed over a 10-second window of stability
