%mit diesem Skript wird die optimale Reglerstruktur k1 und k2 berechnet
%zur vereinfachung wird v konstant auf die maximale kurvengesch. von
%2.63m/s bei 1m kurvenradius gesetzt
%als Eingangsgr��e dient die Kurvenkr�mmung c0 die aus dem Kamerasystem
%kommt. Evtl besser: kamera liefert soll Kurswinkel delta_psi -> c0 =
%f(delta_psi)

v = 2;    %Geschwindigkeit
l = 0.25; %Achsenabstand
lh = l/2; %Abstand zuwischen Schwerpunkt und Hinterachse, noch auszumessen!!!

%%%%%%%%%%%%%%%%%%%%%%%%Zustandsraum
kp = 1;
systemMatrix_A = [0 , v ; 0 , 0];
ausgangsVektor_cT = [kp , 1];
eingangsMatrix_B = [0 , 0 ; v, -1];
durchgriffsVektor_d = [l , -lh/v];


%%%%%%%%%%%%%%%%%%%%%%%%Eigenschaften
system_s = ss(systemMatrix_A, eingangsMatrix_B, ausgangsVektor_cT, durchgriffsVektor_d);
steuer = rank(ctrb(system_s));
beobacht = rank(obsv(system_s));
pole_s = pole(system_s);

%%%%%%%%%%%%%%%%%%%%%%%%Regler
%regelMatrix_K = lqr(system_s, [10,0;0,1], 0.03)
p=10;   %doppelte Polstelle bei -10
a=2*p;
b = p*p/2;
regelMatrix_K=[b a ; b a];
geregelteSystemMatrix_Ar = systemMatrix_A-eingangsMatrix_B*regelMatrix_K;
system_r = ss(geregelteSystemMatrix_Ar, eingangsMatrix_B, ausgangsVektor_cT, durchgriffsVektor_d);
pole_r = pole(system_r);

%%%%%%%%%%%%%%%%%%%%%%%%Simulation
%sim('zustandsRegler.slx');