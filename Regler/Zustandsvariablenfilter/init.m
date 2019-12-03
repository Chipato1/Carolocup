%Dieses Sktipt initialisiert einen Zustandsvariablenfilter zur glättung und
%Gleichtichtung der Zustandsvariablen für den Zustandsraumregler

%Der Ausgang ist standartmäßig die Ableitung der Eingangsgöße, daraus
%folgt:
b = [1; 0; 0];
cT = [1 0 0];
A = [0 1 0; 0 0 1; -1 -8 -80];

filter = ss(A,b,cT,0);
pole(filter)
bode(filter)
