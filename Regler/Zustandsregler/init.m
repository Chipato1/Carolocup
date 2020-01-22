%mit diesem Skript wird die optimale Reglerstruktur k1 und k2 berechnet
%zur vereinfachung wird v konstant auf die maximale kurvengesch. von
%2.63m/s bei 1m kurvenradius gesetzt
%als Eingangsgr��e dient die Kurvenkr�mmung c0 die aus dem Kamerasystem
%kommt. Evtl besser: kamera liefert soll Kurswinkel delta_psi -> c0 =
%f(delta_psi)
v=2;%geschwindigkeit
l=0.25;%Achsenabstand
lh=l/2;%Abstand zuwischen Schwerpunkt und Hinterachse, noch auszumessen!!!
u = 7;
%%%%%%%%%%%%%%%%%%%%%%%%Zustandsraum
systemMatrix_A = [0,v;0,0];%maximale Kurvengeschwindigkeit von 2.63m/s
ausgangsVektor_cT = [0,1];%wegen vorder und hinterache gilt: Kurswinkel ist 0.5 des vorderachseinschlags (ungewichtetes mittel aus vorder und hinterachse)
eingangsVektor_b = [0,0;v, -1];%delta_psi' = -+psi' +- c0*v (letzteres ist der eingang, ersterees wird zus�tlich in simulink addiert)
d = [l,-lh/v];
%%%%%%%%%%%%%%%%%%%%%%%%Eigenschaften
system_s = ss(systemMatrix_A, eingangsVektor_b, ausgangsVektor_cT, d);
steuer = rank(ctrb(system_s))%�berpr�fung auf steuerbarkeit
beobacht = rank(obsv(system_s))%beobachtbarkeit

%%%%%%%%%%%%%%%%%%%%%%%%Regler
K = lqr(system_s, [1,0;0,1], 0.05)%tbd was sind Q, N, R? es handelt sich um Gewichtungsmatrixen in Diagonalform Q:Gewichtung des Zustandsvektors, R: Gewichtung der Eingangsvariable, N:Gewichtung beider gr��en???
reglerMatrix_Ar = systemMatrix_A-eingangsVektor_b*K;
system_r = ss(reglerMatrix_Ar, eingangsVektor_b, ausgangsVektor_cT, d);
pole(system_r)
%pole(tf(system_r)*tf('s'))
%rlocus(system_r);%ergibt die Ortskurve hier noch Sinn?

%%%%%%%%%%%%%%%%%%%%%%%%Simulation
%sim('zustandsRegler.slx');