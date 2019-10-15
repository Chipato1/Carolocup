hwobj = jetson('IP','xavier','Jet&01');
hwobj.updatePeripheralInfo;

envCfg = coder.gpuEnvConfig('jetson');
envCfg.BasicCodegen = 1;
envCfg.Quiet = 1;
envCfg.HardwareObject = hwobj;
coder.checkGpuInstall(envCfg);