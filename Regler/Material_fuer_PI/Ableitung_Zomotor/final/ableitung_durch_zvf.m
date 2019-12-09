clear all;
disp('Anfang');
load test_daten;

% Filter Parametrierung
fcut = 25; % 
n    = 2;
r    = 3;
dt   = 0.01;

[AD,BD]=zvf_design(fcut,n,r,dt);
% [AD,BD,C,D]=zvf_design(fcut,n,r,dt)
% fcut [Hz]  Grenzfrequenz
% n          Filterordnung
% r          Polynomordnung: Interpolation durch die letzten r Punkte
% dt   [sec] Abtastzeitschrittweite

% Faktor um den Vorlauf für das Filter zu bestimmen
vv      =5;
% Berechnung der notwendigen Vorlaufzeit (5*1/fcut)
tv      = round((1/fcut*vv)/dt)*dt;
% Zeitvektor erzeugen
ts      = (-tv:dt:0)';
% Messsignal
uo(:,1) = test_kanal(1:max(find(test_kanal)));% wirft die Nullen aus der Seitenkraft raus
to      = (0:dt:((size(uo,1)-1)*dt))';
% Spiegelung
us      = -uo(size(ts):-1:1) + 2*uo(1,1);
% Messignal und Spiegelung zusammensetzten  
u       = [us(1:length(us)-1); uo];
t       = [ts(1:length(ts)-1); to];
% Anfangsbedingung auf Null setzten
AB1     = zeros(r+1,1);
AB2     = zeros(n,1);
%Simulation starten
[tout sout yout yfifo] = sim('zvfneu');
%Vorlauf wieder abscheiden
na      = length(ts);
ne      = length(tout);
tout    = tout(na:ne);
yout    = yout(na:ne,:);
% Ausgabe:  tout : Zeitkanal
%           yout : yout(1,:) gefiltertes Siganl
%                  yout(i,:) i-te Ableitung wobei i [1..n-1]

% Darstellung
figure(1);
hold on;
grid on;
plot(tout,yout(:,2),'b')
plot(tout,yout(:,1),'g')
hold off;
disp('Ende');