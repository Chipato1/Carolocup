%mit diesem Skript wird die optimale Reglerstruktur k1 und k2 berechnet
%zur vereinfachung wird v konstant auf die maximale kurvengesch. von
%2.63m/s bei 1m kurvenradius gesetzt
%als Eingangsgr��e dient die Kurvenkr�mmung c0 die aus dem Kamerasystem
%kommt. Evtl besser: kamera liefert soll Kurswinkel delta_psi -> c0 =
%f(delta_psi)

v = 2;    %Geschwindigkeit
l = 0.25; %Achsenabstand
lh = l/2; %Abstand zuwischen Schwerpunkt und Hinterachse, noch auszumessen!!!
Ts = 1e-1; %scanning time for discrete systems
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


%%%%%%%%%%%%%%%%%%%%%%%%diskretes System
Ak = [0,1;0,0]; %time independent system
Bk = [0,0;1,-1];
ck = [1,1];
dk = [l, 0];
system_dummy = ss(Ak, Bk, [1,0;0,1], 0);%no feedtrough allowed in mpcDesigner, output vector not used
system_d = c2d(system_dummy, Ts);
%%%%%%%%%%%%%%%%%%%%%%%%Simulation
%sim('zustandsRegler.slx');


%% create MPC controller object with sample time
mpc1_1_C = mpc(mpc1_1_C_plant_C, 0.1);
%% specify prediction horizon
mpc1_1_C.PredictionHorizon = 10;
%% specify control horizon
mpc1_1_C.ControlHorizon = 2;
%% specify nominal values for inputs and outputs
mpc1_1_C.Model.Nominal.U = [0;0];
mpc1_1_C.Model.Nominal.Y = [0;0];
%% specify overall adjustment factor applied to weights
beta = 7.3891;
%% specify weights
mpc1_1_C.Weights.MV = [0 0]*beta;
mpc1_1_C.Weights.MVRate = [0.0135335283236613 0.0135335283236613]/beta;
mpc1_1_C.Weights.OV = [7.38905609893065 7.38905609893065]*beta;
mpc1_1_C.Weights.ECR = 100000;
%% specify overall adjustment factor applied to estimation model gains
alpha = 10;
%% adjust custom output disturbance model gains
setoutdist(mpc1_1_C, 'model', mpc1_1_C_ModelOD*alpha);
%% adjust custom measurement noise model gains
mpc1_1_C.Model.Noise = mpc1_1_C.Model.Noise/alpha;
%% specify simulation options
options = mpcsimopt();
options.RefLookAhead = 'off';
options.MDLookAhead = 'off';
options.Constraints = 'on';
options.OpenLoop = 'off';
%% run simulation
sim(mpc1_1_C, 101, mpc1_1_C_RefSignal, mpc1_1_C_MDSignal, options);
