clear all
clc
L=1;
g=9.81;
dtheta2=@(t,theta)[(theta(2)); -(g/L)*(sin(theta(1)))];
tspan = linspace(0,10,100);
theta0 =[1;1];
[t,theta]=ode45(dtheta2,tspan,theta0);
position = theta(:, 1);
velocity = theta(:, 2);
hold on 
subplot(2,1,1);
plot(t,position);
legend('angular displacement','b');
xlabel('time');
ylabel('amplitude');
grid on
hold on 
subplot(2,1,2);
plot(t,velocity,'r');
legend('angular velocity');
xlabel('time');
ylabel('amplitude');
grid on