function [AD,BD]=zvf_design(fcut,n,r,dt)
% [AD,BD,C,D]=zvf_design(fcut,n,r,dt)
% fcut [Hz]  Grenzfrequenz
% n          Filterordnung
% r          Polynomordnung: Interpolation durch die letzten r Punkte
% dt   [sec] Abtastzeitschrittweite

% Filterkoeffizienten
f=butterw(n);
om=2*pi*fcut;
f=f(1:n);

% kontinuierliche A-Matrix
A=zeros(n,n);
A(1:n-1,2:n)=eye(n-1);
for ii=1:n
  A(n,ii)= -f(ii)*om^(n-ii+1);
end

% kontinuierlicher b-Vektor
b=zeros(n,1);
b(n)=om^n;

% Gewichtsmatrik für Polynom durch die letzten r Punkte
K=zeros(r+1,r+1);
for z=0:r
  for s=0:r
    K(z+1,s+1) = z^s;
  end
end
K=inv(K);

% diskrete Matrizen berechnen 
AD=zeros(n,n);
BD=zeros(n,r+1);
Fold=zeros(n,n);
F=eye(n);
v=0;
while 1
  if v>0
    F=F*A*dt/v;
  end
  if  Fold==F
    break;
  else
    Fold=F;
  end
  AD=AD+F;
  for ii=0:r
    BD(:,ii+1) = BD(:,ii+1) + F*b*dt/(v+ii+1);
  end
  v=v+1;
end
BD=BD*K;

