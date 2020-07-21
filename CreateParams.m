function CreateParams()

global globalParam;

for runSettings = 1
    globalParam.runSpotfi = 0;
    globalParam.runClassicalMusic = 0;
    globalParam.runOrion = 0;
    globalParam.runArraytrack = 0;
end % run Spotfi or/and classical music
for CSI = 1
    globalParam.subCarrIndStart = 1;
    globalParam.subCarrIndStep = 1;
    globalParam.subCarrIndEnd = 10;
    globalParam.csiSource = 4; % for Spotfi only. 0 - winner; 1 - sporfi's sample_csi_trace; 2 - csi from Gao; 3 - csi from RF dataset; 4 - from winner_csi/csi_?????.txt
end % CSI
for ExperimentSetupSettings = 1
    globalParam.centralFrequency = 5.63e9;
    globalParam.frequencyGap = 312.5e3; % frequency gap in Hz between successive subcarriers in WiFi
    globalParam.separationBetweenAntennas = physconst('LightSpeed')/globalParam.centralFrequency/2; % lambda/2 - distance between antennas
    globalParam.numberOfAntennas = 8;   % max 10, after reboot - 14 or 19
end % experiment setup settings such as central frequency, antennas number, antennas separation
for outputConfig = 1
    globalParam.printWinnerOutput = 1;
    globalParam.printWinnerOutputMatrix = 0;
    globalParam.printDifAngleCSI = 0;
    globalParam.printClassicalMusicOutput = 0;
    globalParam.printArraytrackOutput = 0;
    globalParam.printArraytrackStablePeaks = 0;
    globalParam.printSpotfiOutput = 0;
    globalParam.printResultingSpotfiOutput = 0;
    globalParam.printWinnerChannelInfo = 0;
    globalParam.printWinnerExecutionTime = 0;
    globalParam.printSpotfiExecutionTime = 0;    
    globalParam.printClassicalMusicExecutionTime = 0;
    globalParam.printArraytrackExecutionTime = 0;
end % OutputConfig
for ClusterizationConfig = 1
    globalParam.buildClusters = 0;
    globalParam.plotClusters = 1;
    globalParam.saveClusters = 0;  % to save it's necessary to build
    globalParam.closeClusters = 0;
    globalParam.numberOfClusters = 10;
    globalParam.indicesOfWinnerIterationsUsed = []; % if empty, use all
    globalParam.WinnerNumberOfIterations = 30;
    globalParam.iterationWinnerMode = 1; % 0 -only different noise; 1 - different noise and AoA deviation
    globalParam.specialSeedForAngles = 1;
    globalParam.onlyStrongPeaksUsed = 0;
    globalParam.strongPeakThreshold = 0.2;
end
for PlotConfig = 1
    globalParam.directory = "graphs/";
    globalParam.plotClassicalMusicSpectrum = 1;
    globalParam.saveClassicalMusicSpectrum = 0;  % to save it's necessary to plot
    globalParam.plotOrionSpectrum = 1;
    globalParam.saveOrionSpectrum = 0;
    globalParam.closeOrionSpectrum = 0;
    globalParam.plotArraytrackSpectrum = 1;
    globalParam.saveArraytrackSpectrum = 0;  % to save it's necessary to plot
    globalParam.closeArraytrackSpectrum = 0;
    globalParam.plotSpotfiSpectrum = 0;
    globalParam.saveSpotfiSpectrum = 0;  % to save it's necessary to plot
    globalParam.closeSpotfiSpectrum = 0;
    globalParam.plotSpotfiPeaks = 0;
    globalParam.saveSpotfiPeaks = 1;
    globalParam.closeSpotfiPeaks = 1;
    globalParam.plotClassicalMusicPeaks = 0;
    globalParam.saveClassicalMusicPeaks = 0;
    globalParam.plotArraytrackPeaks = 0;
    globalParam.saveArraytrackPeaks = 0;
    globalParam.plotPureCSI = 0;
    globalParam.plotSanitizedCSI = 0;
    globalParam.plotWinnerImpulseResponse = 0;
    globalParam.plotPacketPreambule = 0;
    globalParam.plotAntennasArrangement = 0;
end % PlotConfig
for ArraytrackConfig = 1
    globalParam.fileForArraytrackResults = 'experiment/ArraytrackResults.txt';
    globalParam.ArraytrackBackwardSmoothingUsed = 0;
    globalParam.ArraytrackUsedPacketNum = 1;
    globalParam.ArraytrackSampleNum = 600; % number of samples used in correlation matrix finding
    globalParam.ArraytrackSubarrayNum = 2;
    globalParam.ArraytrackMode = 0; % 0 - default with threshold, 1 - fixed amount of noise eig value
    globalParam.ArraytrackPrintEigen = 0;
    globalParam.ArraytrackNoiseEigenNumber = 5;
    globalParam.ArraytrackThreshold = 0.1;  % default = 0.001
    globalParam.ArraytrackPeaksMode = 1;  % 0 - absolute max, 1 - threshold from max, 2 - k max peaks
    globalParam.ArraytrackPeakThresholdRate = 0.1; % for ArraytrackPeaksMode = 1
    globalParam.ArraytrackNumberOfPeaksToDetect = 8; % for ArraytrackPeaksMode = 2
    globalParam.ArraytrackMeasurement = 0;  % to specify if it is necessary to write results and dump
end
for OrionConfig = 1
    globalParam.fileForOrionResults = 'OrionResults.txt';
    globalParam.OrionBackwardSmoothingUsed = 0;
    globalParam.OrionSubarrayNum = 1;
    globalParam.OrionMeasurement = 0;
    globalParam.OrionMode = 0;
    globalParam.OrionThreshold = 0.1;
    globalParam.OrionPeaksMode = 2;  % 0 - absolute max, 1 - threshold from max, 2 - k max peaks
    globalParam.OrionPeakThresholdRate = 0.1; % for ArraytrackPeaksMode = 1
    globalParam.OrionNumberOfPeaksToDetect = 8; % for ArraytrackPeaksMode = 2
    globalParam.plotOrionPeaks = 0;
    globalParam.saveArraytrackPeaks = 0;
    globalParam.printOrionOutput = 0;
    globalParam.printOrionStablePeaks = 0;
    globalParam.OrionNumberOfIterations = 1;
    globalParam.OrionCsiSource = 0; % 0 - from csi.mat; 1 - from winner_csi/csi_?????
end
for classicalMusicConfig = 1
    globalParam.classicalMusicBackwardSmoothingUsed = 0;
    globalParam.classicalMusicSampleNum = 3000; % number of samples used in correlation matrix finding
    globalParam.classicalMusicMode = 0; % 0 - default with threshold, 1 - new way with fixed amount of eig value
    globalParam.classicalMusicThreshold = 0.15;  % default = 0.001
    globalParam.classicalMusicPeaksMode = 1;  % 0 - absolute max, 1 - threshold from max, 2 - k max peaks
    globalParam.classicalMusicPeakThresholdRate = 0.1; % for SpotFiPeaksMode = 1
    globalParam.classicalMusicNumberOfPeaksToDetect = 4; % for SpotFiPeaksMode = 2
end % some params for classical music, such as sampleNum, classicalMusicMode, threshold, peaks mode and etc.
for spotfiMode = 1
    globalParam.SpotfiNumberOfIterations = 5;
    globalParam.numberOfPacketsPerIteration = 1;
    globalParam.SpotfiSubarrayNum = 2;
    globalParam.fileForSpotfiResults = 'experiment/SpotfiResults.txt';
    globalParam.SpotfiMeasurement = 0;
    globalParam.usePhaseCompensation = 0;
    globalParam.SpotfiMode = 2;  % 0 - default mode, doesn't work well, 1 - doesn't work at all, 2 - works better
    globalParam.SpotfiPeaksMode = 1;  % 0 - absolute max, 1 - threshold from max, 2 - k max peaks, 3 - like 2 but with quantity limit
    globalParam.SpotfiPeakThresholdRate = 0.1; % for SpotFiPeaksMode = 1
    globalParam.SpotfiNumberOfPeaksToDetect = 10; % for SpotFiPeaksMode = 2
    globalParam.SpotfiMaxNumberOfPeaks = 6;
    globalParam.SpotfiPrintEigen = 0;
    globalParam.SpotfiEigenMode = 1; % 0 - fixed amount; 1 - lower than threshold; 2 - lower than threshold from max
    globalParam.SpotfiEigenThreshold = 1;
    globalParam.SpotfiEigenThresholdFromMax = 0.01;
    globalParam.SpotfiNumNoiseEigVector = -2; % if < 0 then num of strongest signal eigen vectors
    globalParam.SpotfiBackwardSmoothingUsed = 1;
end % spotfiMode
for gridConfig = 1
    switch globalParam.subCarrIndStep
        case 4
            globalParam.SpotfiNSDelayRange = 1*[-400 400];
        case 2
            globalParam.SpotfiNSDelayRange = 1*[-800 800];
        case 1
            globalParam.SpotfiNSDelayRange = 1*[-1600 1600];
        otherwise
            error('subCarrIndStep error');
    end
%     globalParam.SpotfiNSDelayRange = 1*[-50 50];
    globalParam.SpotfiAngleRange = 90*[-1 1];
    globalParam.SpotfiNSDelayRange = 1*[-300 300];
    globalParam.SpotfiNumberOfGridPoints = [globalParam.SpotfiNSDelayRange(2)*2+1 globalParam.SpotfiAngleRange(2)*2+1 1]; % [ToF, AoA, 1]
end
for WinnerChannelConfiguration = 1
    globalParam.roundDelays = 1;
    globalParam.oversamplingFactor = 1;
    globalParam.seedForScenario = 1;
    globalParam.realisticScenario = 1;
    globalParam.AngleOfLOS = 0;
    globalParam.WinnerUseLos = 0;
    globalParam.Kfactor = 2; % в разах по мощности. previous: 2.0338. if 0 then is set automatically 
    % normStream = RandStream('v5normal','Seed',1); 10.^(0.1*(6*randn(normStream, 25, 1)+ 7))
    globalParam.WinnerArrayRotationAngle = 0;
    globalParam.WinnerUseAWGN = 1;
    globalParam.SNR = 5; % SNR in dB
    globalParam.seedForChannelEvolution = 9; % for snr and Yn deviation
    globalParam.WinnerNumClusters = 2;   % max: 12 for LOS, 16 for NLOS
    globalParam.WinnerUseFixedPowerDelay = 1;
    globalParam.WinnerUseFixedAngles = 1;
    globalParam.WinnerNumSubPath = 1;   % 1 or 20
    globalParam.WinnerAddVariationToDoA = 0;
    globalParam.WinnerAddVariationToAoA = 0; % variation to each subpath angle
    globalParam.WinnerZeroPhases = 1;
    globalParam.WinnerDivideStrongestClusters = 0;
    globalParam.WinnerUsePolarisedArrays = 0;
    globalParam.WinnerUseShadowingModel = 0;
    globalParam.WinnerUsePathLossModel = 0;
end % Winner channel config, such as numSubPath
for fixedNLOSparams = 1
    % globalParam.NLOSdeparture = [45 77 43 72 54 -65 -60 85 0 -104 95 -104 -105 103 -135 -122];
    x = 0;
    y = 0;
    globalParam.NLOSdeparture = [x y x y x y x y x y x y x y x y];
    
    % globalParam.NLOSpower = 10.^(-[15.2 19.7 15.1 18.8 16.3 17.7 17.1 21.2 13.0 14.6 23.0 25.1 25.4 24.8 33.4 29.6]/10);
    x = 20;
    y = 20;
    globalParam.NLOSpower = 10.^(-[x y x y x y x y x y x y x y x y]/10);
    
    % globalParam.NLOSdelay = [0 5 5 5 15 15 15 20 20 35 80 85 110 115 150 175]*1e-9;
    % y = 0;
    % runParam.NLOSdelay = [y y y y y y y y y y y y y y y y]*1e-9;
    x = 50;
    y = 100;
    globalParam.NLOSdelay = [x y x y x y x y x y x y x y x y]*1e-9;
    
    % globalParam.NLOSangle = [41 -70 39 66 -49 59 -55 -78 0 95 86 95 -96 -94 123 -111];
    x = 5;
    y = -x;
    globalParam.NLOSangle = [x y x y x y x y x y x y x y x y];
end % fixed NLOS parameters for Winner channel
for fixedLOSparams = 1
    % globalParam.LOSdeparture = [0 -107 -100 131 118 131 116 131 146 102 -126 131];
    x = 0;
    y = 0;
    globalParam.LOSdeparture = [x y x y x y x y x y x y x y x y];
    
%     globalParam.LOSdelay = [0 10 25 50 65 75 75 115 115 145 195 350]*1e-9;  % Unit: seconds
    globalParam.LOSdelay = [4.1587 12.4991 31.2624 43.5319 0 77.2131 48.3025 119.5621 81.6675 7.2041 193.7343 309.2356]*1e-9;
    
    x = 40;
    y = 10;
%     globalParam.LOSdelay = [x y x y x y x y x y x y x y x y]*1e-9;
    
%     globalParam.LOSpower = 10.^(-[22.9 28.8 26.5 25.1 32.2 36.5 31.3 36.4 42.2 27.2 34.6 36.4]/10); % Linear scale
    globalParam.LOSpower = [0.3133 0.1535 0.1526 0.1435 0.1071 0.0512 0.0239 0.0166 0.0135 0.0121 0.0083 0.0039];
    x = 200;
    y = 200;
%     globalParam.LOSpower = 10.^(-[x y x y x y x y x y x y x y x y]/10);
    
    % globalParam.LOSangle = [0 -110 102 -134 121 -134 -118 -134 149 105 129 -134];
    globalParam.LOSangle = [-60 33.7072 -80.5514 -24.1160 0.5835 59.6872 69.6728 -68.2885 83.9247 87.1027 -71.5879 -75.2758];
    x = 40;
    y = -30;
%     globalParam.LOSangle = [x y x y x y x y x y x y x y x y];

end % fixed LOS parameters for Winner channel
for STApositions = 1
    globalParam.WinnerUseFixedSTApositions = 1;
    globalParam.MSposition = [0 0 1.5].';
    globalParam.BSposition = [0 0 1.5].';
    
    if globalParam.AngleOfLOS < 0
        globalParam.MSposition(1) = 5;
        globalParam.BSposition(2) = 5*tan(pi/2-pi/180*abs(globalParam.AngleOfLOS));
    elseif globalParam.AngleOfLOS > 0
        globalParam.BSposition(1) = 5;
        globalParam.BSposition(2) = 5*tan(pi/2-pi/180*abs(globalParam.AngleOfLOS));
    else
        globalParam.BSposition(2) = 5;
    end
    
    globalParam.MSposition = globalParam.MSposition;
    globalParam.BSposition = globalParam.BSposition;
end % set Los Angle using STA positions
for realisticScenario = 1
    if globalParam.realisticScenario
        globalParam.WinnerUseLos = 1;
        globalParam.WinnerUseAWGN = 1;
        globalParam.WinnerNumClusters = 12;   % max: 12 for LOS, 16 for NLOS
        globalParam.WinnerUseFixedPowerDelay = 0;
        globalParam.WinnerUseFixedAngles = 0;
        globalParam.WinnerNumSubPath = 20;   % 1 or 20
        globalParam.WinnerZeroPhases = 0;
        globalParam.WinnerDivideStrongestClusters = 1;
    end
end % use realistic scenario if needed

end % CreateParams