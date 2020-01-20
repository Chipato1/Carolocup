test1 = timeseries()
test1.Time = 1:size(DATA008.Time,1)
test1.Data = DATA008.AccX
sim = size(DATA008.Time,1)
sim2 = round(DATA008.Time(end))
backup = DATA008.Time;

% sim Kalman_gefiltert.slx
% simout.Time(3:end) = DATA008.Time(1:end)
% figure(1)
% plot(simout.Time, simout.Data(:,2))
% figure(2)
% plot(simout.Time, simout.Data(:,4))