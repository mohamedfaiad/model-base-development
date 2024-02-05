clear all
clc
%example 1
A=[3 2 1;6 5 4;9 8 7];
B=[12 11 10; 15 14 13;18 17 16];
matrix_sum=A+B;
matrix_sum=A+B
%example 2
rowVector = 1:5;
columnVector = (6:10)';
horizontalConcat = [rowVector, columnVector'];
disp(horizontalConcat)
% example 3
originalMatrix = [1, 2; 3, 4];
repeatedMatrix = repmat(originalMatrix, 2, 2);
disp(repeatedMatrix)
% example 4
identityMatrix = eye(3);
matrixProduct = identityMatrix *A;
disp(matrixProduct)
