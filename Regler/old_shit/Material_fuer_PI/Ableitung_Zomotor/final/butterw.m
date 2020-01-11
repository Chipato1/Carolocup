function f=butterw(n)
f=1;
for k=1:n
  s=exp((2*k+n-1)/2/n*i*pi);
  f = conv(f,[1, -s ]);
end
f=real(f);