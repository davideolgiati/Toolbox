# ToolBox!



Toolbox is an experimental programming language written in C++. Currently you can only use it as an interpreter, load from file will be available in the future.



## Syntax an Features

Toolbox syntax can be described as "quite strange". Toolbox was inspired by two other PL: Prolog and CommonLisp.

| Feature | Toolbox | CommonLisp | Prolog |
|--|--|--|--|
| Feedback after<br/>every set of <br/>instructions | ****yes**** | no | ****yes**** |
|Function with <br/> variable number of <br/> arguments |****yes****|****yes****|no|
|visual runtime debug |****yes****|no|****yes****|

## Examples

[T] >> [1:42] // create a sequence starting from 1 to 42

1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42
true

[T] >> V = [1:42] // create a sequence starting from 1 to 42 and stores it in a variable called V

V = 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42
true

[T] >> +(V) // create a sum of all numbers stored in V

+(V)  = 903
true

