test1 = timeseries()
test1.Time = 1:size(DATA011.Time,1)
test1.Data = DATA011.AccX
sim = 130%size(DATA011.Time,1)
sim2 = round(DATA011.Time(end))
start = 60
stop = 100
backup = DATA011.Time;
[num, denum] = butter(2,0.1);
[num_cheby, denom_cheby] = cheby1(2,0.1,0.2);
[num_bessel, denom_bessel] = besself(2,0.5);
sim Kalman_gefiltert.slx
xlswrite('test.xls', [(60:100)', out.simout1, out.simout2])
% simout.Time(3:end) = DATA008.Time(1:end
% figure(1)
% plot(simout.Time, simout.Data(:,2))
% figure(2)
% plot(simout.Time, simout.Data(:,4))