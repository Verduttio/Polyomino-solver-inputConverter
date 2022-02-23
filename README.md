# Polyomino-solver-inputConverter

This program converts polyominoes in ASCII representation to their number representation (block coordinates) and vice versa.  
This is an extension for `Polyomino-solver` repository.

Usage:  
inputConverter {toASCII, toNumbers} [fileName] (max coordinate+1 - only in toASCII mode)

Examples:  
./inputConverter toASCII file.txt 10  
./inputConverter toNumbers file.txt  

**ASCII file structure**  
```
1st polyomino
[enter]
2nd polyomino
[enter]
.
.
.
```

ASCII file example:  
```
#####
#####
#####
#####

####

####

####

####

####
```

Is equal to:  
```
(0,0) (0,1) (0,2) (0,3) (0,4) (1,0) (1,1) (1,2) (1,3) (1,4) (2,0) (2,1) (2,2) (2,3) (2,4) (3,0) (3,1) (3,2) (3,3) (3,4)
(0,0) (0,1) (0,2) (0,3)
(0,0) (0,1) (0,2) (0,3)
(0,0) (0,1) (0,2) (0,3)
(0,0) (0,1) (0,2) (0,3)
(0,0) (0,1) (0,2) (0,3)
```

