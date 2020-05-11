%mit diesem Skript wird die optimale Reglerstruktur k1 und k2 berechnet
%zur vereinfachung wird v konstant auf die maximale kurvengesch. von
%2.63m/s bei 1m kurvenradius gesetzt
%als Eingangsgr��e dient die Kurvenkr�mmung c0 die aus dem Kamerasystem
%kommt. Evtl besser: kamera liefert soll Kurswinkel delta_psi -> c0 =
%f(delta_psi)

v = 2;    %Geschwindigkeit
l = 0.25; %Achsenabstand
lh = l/2; %Abstand zuwischen Schwerpunkt und Hinterachse, noch auszumessen!!!
Ts = 0.05; %scanning time for discrete systems
%%%%%%%%%%%%%%%%%%%%%%%%Zustandsraum
kp = 0.001;
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


%%%%%%%%%%%%%%%%%%%%%%%%diskretes System
Ak = [0,1;0,0]; %time independent system
Bk = [0,0;1,-1];
ck = [1,1];
dk = [l, 0];
system_dummy = ss(Ak, Bk, [1,0;0,1], 0);%no feedtrough allowed in mpcDesigner, output vector not used
system_d = c2d(system_dummy, Ts);
%%%%%%%%%%%%%%%%%%%%%%%%Simulation
%sim('zustandsRegler.slx');

%state space with pseudo states, tested: good result but loss of yawrate!
Ak2 = [0, 1, 0, 0; 0, 0, 0, 0; 0, 0, 0, kp; 0, 0, 0, 0];
Bk2 = [0, 0, 0, 0, 0; 1, -1, 0, 0, 0; 1, -1, 0, 0, l; 0, 0, 1, -1, 0];
Ck2 = [1, 0, 0, 0; 0, 1, 0, 0; 0, 0, 1, 0; 0, 0, 0, 1];
system_dummy = ss(Ak2, Bk2, Ck2, 0);%no feedtrough allowed in mpcDesigner, output vector not used
system_d2 = c2d(system_dummy, Ts);

%state space with pseudo staes, including yawrate in state vector!
Ak3 = [0, 1, 0, 0, 0, 0; 0, 0, 0, 0, -1, 0; 0, 0, 0, kp, -1, 0; 0, 0, 0, 0, 0, -1; 0, 0, 0, 0, 0, 0; 0, 0, 0, 0, 0, 0];
Bk3 = [0, 0, 0, 0, 0; 1, 0, 0, 0, 0; 1, 0, l, 0, 0; 0, 1, 0, 0, 0; 0, 0, 0, 1, 0; 0, 0, 0, 0, 1];
Ck3 = [1, 0, 0, 0, 0, 0; 0, 1, 0, 0, 0, 0; 0, 0, 1, 0, 0, 0; 0, 0, 0, 1, 0, 0; 0, 0, 0, 0, 1, 0; 0, 0, 0, 0, 0, 1];
system_dummy = ss(Ak3, Bk3, Ck3, 0);%no feedtrough allowed in mpcDesigner, output vector not used
system_d3 = c2d(system_dummy, Ts);