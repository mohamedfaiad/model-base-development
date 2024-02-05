clear all
clc
% examples of If
x=7;
if x > 5
    disp('x is geeater than 5');
end
% if-else if
y=30;
if rem(y,2)== 0
    disp('y is even number');
else
    disp('y is odd number');
end
% if-else if-if
score=75;
if score >= 90
        disp('the degree of student is: A');
elseif score >= 80
        disp('the degree of student is: B');
elseif score >= 70
        disp('the degree of student is: C');
else
        disp('the degree of student is: F');
end