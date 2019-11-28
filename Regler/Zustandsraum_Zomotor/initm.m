%mit diesem Skript wird die optimale Reglerstruktur k1 und k2 berechnet
%zur vereinfachung wird v konstant auf die maximale kurvengesch. von
%2.63m/s bei 1m kurvenradius gesetzt
%als Eingangsgröße dient die Kurvenkrümmung c0 die aus dem Kamerasystem
%kommt. Evtl besser: kamera liefert soll Kurswinkel delta_psi -> c0 =
%f(delta_psi)

%%%%%%%%%%%%%%%%%%%%%%%%Zustandsraum
systemMatrix_A = [0,2.63;0,0];%maximale Kurvengeschwindigkeit von 2.63m/s
ausgangsVektor_cT = [1,1.5];%wegen vorder und hinterache gilt: Kurswinkel ist 0.5 des vorderachseinschlags (ungewichtetes mittel aus vorder und hinterachse)
eingangsVektor_b = [0;2.63];%delta_psi' = -+psi' +- c0*v (letzteres ist der eingang, ersterees wird zusätlich in simulink addiert)

%%%%%%%%%%%%%%%%%%%%%%%%Eigenschaften
system_s = ss(systemMatrix_A, eingangsVektor_b, ausgangsVektor_cT, 0);
steuer = rank(ctrb(system_s))%überprüfung auf steuerbarkeit
beobacht = rank(obsv(system_s))%beobachtbarkeit

%%%%%%%%%%%%%%%%%%%%%%%%Regler
K = lqr(system_s, [1,0;0,1], 1)%tbd was sind Q, N, R? es handelt sich um Gewichtungsmatrixen in Diagonalform Q:Gewichtung des Zustandsvektors, R: Gewichtung der Eingangsvariable, N:Gewichtung beider größen???
reglerMatrix_Ar = systemMatrix_A-eingangsVektor_b*K;
system_r = ss(reglerMatrix_Ar, eingangsVektor_b, ausgangsVektor_cT, 0);
pole(system_r)
pole(tf(system_r)*tf('s'))
%rlocus(system_r);%ergibt die Ortskurve hier noch Sinn?

%%%%%%%%%%%%%%%%%%%%%%%%Simulation
sim('zustandsRegler.slx');