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
 
Results with the window floating as frontmost, upload 0 with it's OF-set size of 1920x1080 (with an otherwise tranquil systems):

| system | arch | OS | build | mode 1 (current) | mode 2 (new) | mode 3 (ofxFast)| notes |
| - | - | - | - | - | - |
| M2 pro (6(12) core / 19 gpu)   | aarm64 | macOS 13.4 | debug   | 245-250 | 355-357 | 1042-1047 | AB:20230915 |
|                                |        |            | release | 245-255 | 360-363 | 1080-1090 | AB:20230915 | 
| M1 (8/4 cores ; 8 gpu)         | aarm64 | macOS 13.4 | debug   | 170-180 | 210-220 |  340-370  | AB:20230913 |
|                                |        |            | release | 175-180 | 215-220 |  360-375  | AB:20230913 |
| i7 2.6gHz (6/12 cores ; 560X)  | x64    | macOS 13.4 | debug   | 140-160 | 235-240 |  250-290  | AB:20230913 |
|                                |        |            | release | 142-165 | 220-240 |  305-320  | AB:20230913 |
| i7-9700K ; nvidia 2080SUPER    | x64    | linux 5.15 | debug   | 295-311 | 770-775 |  840-850  | AB:20230914 |
|                                |        |            | release | 11-12 | 31-32 |  35-36  | AB:20230914 |

results are eyeballed over a 10-second window of stability (outlier drops are not considered).

upload serves to visually confirm the data is correctly being downloaded but should be disabled for benchmarking purposes.

IMPRESSIONS:

on intel, the performance of new proposal is close to FastFboReader, however on aarm64 the gap is still quite large.

