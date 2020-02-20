%Initialisierungsskript für den Fahrzeugregler
v = 9;          % Geschwindigkeit des Fahrzeugs in m/s
m = 2;          % Masse des Fahrzeugs in kg
%Flaeche =       % Luftwiderstandsfläche des Fahrzeugs
FL = 0;         % Luftwiderstand FL ist bei einem 1:10 Modellauto vernachlässigbar.
lv = 0.15;      % Länge des Fahrzeugschwerpunktes zur Vorderachse
lh = 0.15;      % Länge des Fahrzeugschwerpunktes zur Hinterachse
cv = 1;         % Schräglaufstei?gkeit aus Kraft und Schräglaufwinkel alpha_v
ch = 1;         % Schräglaufstei?gkeit aus Kraft und Schräglaufwinkel alpha_h
Jzz = 1;        % Trägheitsmoment
i = 1;          % Keine Ahnung, was das ist?!


a11 = (FL - (cv + ch))/ (m*v);
a12 = (ch*lh-cv*lv)/(m*v^2)-1;
a13 = (cv / (m*v));
a14 = 0; a15 = 0;
a21 = (ch*lh-cv*lv)/Jzz;
a22 = -((ch*lh^2-cv*lv^2)/(Jzz*v));
a23 = cv*lv / Jzz;
a24 = 0; a25 = 0;
a31 = 0; a32 = 0; a33 = 0; a34 = 0; a35 = 0;
a42 = 1;
a41 = 0; a43 = 0; a44 = 0; a45 = 0;
a51 = -v;
a54 = v;
a52 = 0; a53 = 0; a55 = 0;

b11 = 0; b12 = 0; b14 = 0; b15 = 0;
b13 = 1 / i;

c11 = 0; c12 = 0; c13 = 1; c14 = 0; c15 = 0;

e11 = 0; e12 = 0; e13 = 0; e15 = 0;
e14 = v;

A = [a11, a12, a13, a14, a15; a21, a22, a23, a24, a25; a31, a32, a33, a34,...
    a35; a41, a42, a43, a44, a45; a51, a52, a53, a54, a55];
B = [b11; b12; b13; b14; b15];
C = [c11, c12, c13, c14, c15];
D = 0;
E = [e11, e12, e13, e14, e15];
Q = [1,0,0,0,0;0,1,0,0,0;0,0,1,0,0;0,0,0,1,0;0,0,0,0,1];
R = 2;

system = ss(A, B, C, D);
rank(ctrb(system))%überprüfung auf steuerbarkeit
rank(obsv(system))%beobachtbarkeit
K = lqr(system, Q, R);

