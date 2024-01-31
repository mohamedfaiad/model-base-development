%Define and initialize a variable intVar with an integer value of your choice.
%Define and initialize a variable doubleVar with a double-precision floating-point value.
%Display the data type of both intVar and doubleVar using the class function.
clc
clear all
intVar = 25;
doubleVar = 4.56723;
disp("The data type of intVar is  intVar");
disp("The data type of doubleVar is doubleVar");
%Create a row vector evenNumbers containing the first 5 even numbers (2, 4, 6, 8, 10).
%Create a column vector primeNumbers containing the first 5 prime numbers (2, 3, 5, 7, 11).
%Display both evenNumbers and primeNumbers.
evenNumbers=2:2:10;
primeNumbers=(primes(11));
primeNumbers1=(primes(11))';
disp(evenNumbers)
disp(primeNumbers)
disp(primeNumbers1)
%Create a 3x3 identity matrix identityMatrix using a specialized matrix function.
%Create a 2x2 magic square magicSquare using another specialized matrix function.
%Display both identityMatrix and magicSquare
identityMatrix = eye(3);
magicSquare = magic(2);
disp(identityMatrix)
disp(magicSquare)
%Concatenate the evenNumbers vector horizontally with the primeNumbers vector to create a new row vector combinedVector.Display the combinedVector.
%Create a new matrix combinedMatrix by vertically concatenating identityMatrix and magicSquare.
%Dispay the combinedMatrix.
%combinedVector = horzcat(evenNumbers, primeNumbers);
%disp(combinedVector)
%combinedMatrix = vertcat(identityMatrix, magicSquare);
%disp(combinedMatrix)
%Error using vertcat
%Dimensions of arrays being concatenated are not consistent.
%Concatenate the evenNumbers vector horizontally with the primeNumbers vector to create a new row vector combinedVector.Display the combinedVector.
%Create a new matrix combinedMatrix by vertically concatenating identityMatrix and magicSquare.
%Dispay the combinedMatrix.
magicSquare1 = magic(3);
combinedVector = horzcat(evenNumbers, primeNumbers);
disp(combinedVector)
disp(magicSquare1)
combinedMatrix = vertcat(identityMatrix, magicSquare1);
disp(combinedMatrix)