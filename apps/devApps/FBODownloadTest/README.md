# FBO download test

![Screenshot of sortingExample](sortingExample.png)

### An attempt at benchmarking FBO GPU downloads with 0 samples

A shader produces data in the FBO, which is processed depending on mode, which is specified by hitting the corresponding key:

 - mode 0: no download
 - mode 1: download with current method
 - mode 2: download with proposed ES method
 - mode 3: download with fastFboReader
 
Thus, this needs the ofxFastFboReader addon.

Vertical sync is disabled, allowing > 60fps values.
 
Results with the window floating as frontmost, upload 0 with it's OF-set size of 1920x1080 (with an otherwise tranquil systems):

NUMBER MEANS: within 1/30s, the system is capable of how many iterations of:
    draw with a shader into a 1920x1080 RGBA FBO
    download the FBO's texture into RGBA pixels data with one of 3 methods
    
(30fps was selected instead of the usual 60 to give a chance of meaningful number on slower systems)
    

| system | arch | OS |  | mode 1 (current) | mode 2 (new) | mode 3 (ofxFast)| notes |
| - | - | - | - | - | - |
| M2 pro (6(12) core / 19 gpu)   | aarm64 | macOS 13.4 |    | 13 | 18 | 104 | AB:20230915 |
| M1 (8/4 cores ; 8 gpu)         | aarm64 | macOS 13.4 |    |  9 | 14 |  41 | AB:20230913 |
| i7 2.6gHz (6/12 cores ; 560X)  | x64    | macOS 13.4 |    |  3 | 11 |  22 | AB:20230913 |
| i7-9700K ; nvidia 2080SUPER    | x64    | linux 5.15 |    | 11 | 31 |  35 | AB:20230914 |

results are eyeballed over a 10-second window of stability (outlier drops are not considered).

upload serves to visually confirm the data is correctly being downloaded but should be disabled for benchmarking purposes.

IMPRESSIONS:

on intel, the performance of new proposal is close to FastFboReader, however on aarm64 the gap is still quite large.

