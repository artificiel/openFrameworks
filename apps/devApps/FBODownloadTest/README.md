# FBO download test

### An attempt at benchmarking FBO GPU downloads with 0 samples

A shader produces data in the FBO, which is processed depending on mode, which is specified by hitting the corresponding key:

 - mode 1: download with current method
 - mode 2: download with proposed ES method
 - mode 3: download with [ofxFastFboReader](https://github.com/satoruhiga/ofxFastFboReader)
 
Vertical sync is disabled, allowing > 60fps values. Compiled in Release.

 
**WHAT THE NUMBER MEANS**:

     a given system is capable, within a 1/30s interval, of how many iterations of:
        1) draw with a shader into a 1920x1080 RGBA FBO
        2) download the FBO's texture into RGBA pixels data with one of 3 methods
    

| system | specs | arch | OS |mode 1 (current) | mode 2 (new) | mode 3 (ofxFast) |
| - | - | - | - | :-: | :-: | :-: |
| MacBook Pro 16 2023 | M2 pro (8+4 core ; 19 gpu)   | arm64 | macOS 13.4 | 13 | 18 | 104 | AB:20230915 |
| Mac Mini 2020 | M1 4+4 cores ; 8 gpu         | arm64 | macOS 13.4 |   9 | 14 |  41 | AB:20230913 |
| MacBook Pro 15 2018 | i7 2.6gHz 6(12) cores; 560X  | x64    | macOS 13.4 |   3 | 11 |  22 | AB:20230913 |
| Custom Workstation | i7-9700K; nvidia 2080SUPER    | x64    | linux 5.15-LTS |  11 | 31 |  35 | AB:20230914 |

The number is the largest number that consistently reports ≥ 30fps. 

Results are taken with the window floating as frontmost, upload disabled, size of 1920x1080 (on otherwise tranquil systems). Results are eyeballed over a 10-second window of stability (outlier drops are not considered). 30fps was selected instead of the usual 60 to give a chance of meaningful number on slower systems.

The "upload" toggle serves to visually confirm the data is correctly being downloaded but should be disabled for benchmarking purposes.
