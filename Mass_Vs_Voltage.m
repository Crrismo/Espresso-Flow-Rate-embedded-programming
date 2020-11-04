Vout=[2.539e-3 2.589e-3 2.622e-3 2.667e-3 2.747e-3 2.904e-3 3.068e-3 3.106e-3 3.146e-3];
Mass=[0 5 10 15 25 45 65 70 75];%Mass in g
plot(Mass,Vout);
%Voltage=mass*gradient+intercept--> workout mass
%Volume=mass/density, density 1 for brewed coffee 
%Flow rate= Volume_diff/time