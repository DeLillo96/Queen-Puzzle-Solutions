# New Algorithm for research solutions of Queens Puzzle # 
## 1 The Aim ##  
The aim is build a new and powerful algorithm based on a layer in the chessboard.   
  
### 1.1 Rules ###
First thing is define the conditions to placed queen in mathematic method:
- There is one and only one queen in a row: for all q1(x,y) not exist q2(x,z)
- There is one and only one queen in a column: for all q1(x,y) not exist q2(z,y)
- There is one and only one queen in a diagonal sx->dx: for all q1(x,y), q2(a,b) |x-y| != |a-b|
- There is one and only one queen in a diagonal dx->sx: for all q1(x,y), q2(a,b) |x+y| != |a+b|   
