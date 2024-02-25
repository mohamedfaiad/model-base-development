clear all
clc
b=10;
x0=1;
k=400;
m=3;
mdl=gcs;
massvalue =1:2:11;

for i = 1:numel(massvalue)
    m = massvalue(i);
    result = sim(mdl);
    plot(result.logsout.get("x").values);
    hold on
    disp("simulation " +num2str(i)+"compelete");
    legendlables{i}="m="+num2str(m);
end
legend(legendlables);