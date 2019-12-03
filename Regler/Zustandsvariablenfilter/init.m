%Dieses Sktipt initialisiert einen Zustandsvariablenfilter zur gl�ttung und
%Gleichtichtung der Zustandsvariablen f�r den Zustandsraumregler

%Der Ausgang ist standartm��ig die Ableitung der Eingangsg��e, daraus
%folgt:
b = [1; 0; 0];
cT = [1 0 0];
A = [0 1 0; 0 0 1; -1 -8 -80];

filter = ss(A,b,cT,0);
pole(filter)
bode(filter)
