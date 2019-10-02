# DiscreteMathematics Assignment 1  

## Problem Set  
### p1 : Sudoku *  
- input : 9X9 grid that each cell contains one of the following 3 types  
? : no specific number  
1..9 : one specific number  
\* : The cell is marked as Asterisk  
- output : the complete 9X9 grid that satisfies the rules, or "No Solution!"  
  
### p2 : Fill-a-Pix  
- input : NXM grid that each cell contains one of the following 2 types  
? : no clue is given  
1..9 : clue is given  
- output : the complete NXM grid that satisfies the rules, or "No Solution!"  
1 : BLACK
0 : WHITE  

### p3 : Numbrix  
- input : NXM grid that each cell contains one of the following 2 types  
? : no value is assigned yet  
1..9 : assigned value  
- output : the complete NXM grid that satisfies the rules, or "No Solution!"  

## How to build?
```
make p1  
make p2  
make p3  
```
or
```
gcc p1.c -o p1.out  
gcc p2.c -o p2.out  
gcc p3.c -o p3.out  
```

## How to execute?
```
./p1.out < standard_input.txt  > standard_output.txt
./p2.out < standard_input.txt  > standard_output.txt
./p3.out < standard_input.txt  > standard_output.txt
``` 

## Execution example
### P1  
```
./p1.out
? 2 ? 5 ? * ? 9 ?
8 ? ? 2 ? 3 ? ? 6
? 3 ? ? 6 ? * 7 ?
* ? ? ? * ? 6 ? ?
5 4 ? ? ? ? ? 1 9
? ? 2 ? ? ? 7 ? ?
? 9 * ? 3 ? ? 8 ?
2 ? ? 8 ? 4 ? * 7
? 1 ? 9 ? 7 ? 6 ?
```

### P2  
```
./p2.out
? ? ? ? ?
? 9 ? ? ?
? 8 8 ? ?
? ? ? ? 4
4 ? 5 ? 2
```
  
### P3   
```
./p3.out
? ? ? ? ? ?
? ? 20 13 ? ?
? 26 ? ? 9 ?
? 25 ? ? 10 ?
? ? 23 36 ? ?
```  

```
./p3.out
? ? ? ? ? ?
? ? ? ? ? ?
? ? ? ? ? ?
? ? ? ? ? ?
? ? ? ? ? ?
? ? ? ? ? ?
```  

## License  
Prof. Shin Hong hongshin@gmail.com  
Jiyoung Shin cinxdys2@gmail.com  
Sungbin 21700613@handong.edu  
Hyelim Lee 21800607@handong.edu  
Hayun Park gkahsdl@icloud.com  
Semin Sohn 21800386@handong.edu  