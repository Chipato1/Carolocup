test1 = timeseries()
test1.Time = DATA001.Time
test1.Data = DATA001.AccX
sim = size(DATA001.Time,1)
sim Kalman_gefiltert.slx
simout.Time(2:end) = DATA001.Time(1:end)
figure(1)
plot(simout.Time, simout.Data(:,2))