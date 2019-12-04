%Dieses Sktipt initialisiert einen Zustandsvariablenfilter zur glättung und
%Gleichtichtung der Zustandsvariablen für den Zustandsraumregler

%Der Ausgang ist standartmäßig die Ableitung der Eingangsgöße, daraus
%folgt:
b = [1; 0; 0];
cT = [1 0 0];
A = [0 1 0; 0 0 1; -1 -8 -80];

% filter = ss(A,b,cT,0);
% pole(filter)
% bode(filter)


Am = [0 1; -0.5 -10];
bm = [1;0];
cTm = [1 0];
e1 = [1 0];
e2 = [0 1];
 filterm = ss(Am,bm,cTm,0);
 pole(filterm)