test1 = timeseries()
test1.Time = 1:size(DATA011.Time,1)
test1.Data = DATA011.AccX
sim = 130%size(DATA011.Time,1)
sim2 = round(DATA011.Time(end))
backup = DATA011.Time;
[num, denum] = butter(4,0.1);
% sim Kalman_gefiltert.slx
% simout.Time(3:end) = DATA008.Time(1:end)
% figure(1)
% plot(simout.Time, simout.Data(:,2))
% figure(2)
% plot(simout.Time, simout.Data(:,4))