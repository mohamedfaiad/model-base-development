clear all
clc
R=1;
C=1e-6;
f=1;
w=2*pi*f;
Vin=@(t) 5*sin(w*t);
dVCdt = @(t, VC) ((Vin(t)*R) - VC) / (R * C);
VC0 = 0;
tspan = linspace(0, 10, 1000);
[t, VC] = ode45(dVCdt, tspan, VC0);
hold on
subplot(2, 1, 1);
plot(t, VC, 'b');
title('Voltage Across Capacitor (RC Circuit)');
legend('VC(t)');
xlabel('Time (s)');
ylabel('Voltage (V)');
grid on
hold on
subplot(2, 1, 2);
plot(t, Vin(t), 'r');
title('input Voltage (RC Circuit)');
legend('Vin(t)');
xlabel('Time (s)');
ylabel('Voltage (V)');
grid on;