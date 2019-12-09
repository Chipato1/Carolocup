%Dieses Sktipt initialisiert einen Zustandsvariablenfilter zur Ableitung
%der Ticks die durch die raddrehzahlsensoren geliefert werden.
%Diese entsprechen der gefahrenen Stecke un müssen durch differentiation in
%eine Geschwindigkeit umgerechnet werden.
%Da die erste ableitung benötigt wird muss der zvf 2 einträge enthalten,
%also auch die zweite ableitung berechnen. n = 2!!!
%der zvf liegt in
%regelungsnormalform vor:
n=2;
w=0.25*(2*pi/0.6);%annahme: es wird mit 1ms abgetastet
%Der Ausgang ist standartmäßig die Ableitung der Eingangsgöße, daraus
%folgt:
b = [0; 1];
cT = [0 1];

%bestimmung der Filterübertragungsfunktion
f = 1;
for k = 1:n
    s = exp(1i*pi*(2*k-1+n)/(2*n));
    f=conv(f,[1,-s]);%das berechnen den normierten vektor f
end
for i = 0:n-1
    f(i+1) = w^(n-i)*real(f(i+1));%hier wird f auf die passenden kreisfrequenz angepasst:
    %diese muss glaube ich der Abtastrate entprechen
end
A = [0, 1;-f(1), -f(2)];

filter = ss(A,b,cT,0);
pole(filter)
% bode(filter)
% data = timeseries(DATA012.AccX);
% data.time = DATA012.Time;
% sum = 0;
% for i = 1:100
%     sum = sum + data.DATA(i);
% end 
% sum = sum/100;
% %data.DATA = data.DATA - sum;
% sim = fix(data.time(end));
% 
% % 
% Am = [0 1; -0.5 -10];
% bm = [1;0];
% cTm = [1 0];
% e1 = [1 0];
% e2 = [0 1];
%  filterm = ss(Am,bm,cTm,0);
%  pole(filterm)

data = timeseries([1,2,3,4,5,6,7,8,9,4,7,1,3,2,5,5,5,6,7,5,3,8,8,9,2,3,4,5,6,7,8]');
sim = data.time(end)