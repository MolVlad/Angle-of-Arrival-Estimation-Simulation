function SecondScenarioWinner()

global globalParam;
global globalData;

for measureExecutionTime = 1
    if globalParam.printWinnerExecutionTime
        tic
    end
end % measure execution time
for channelConfigAndPacketGenerate = 1
        chanBW = 'CBW160';
        mcs = 0; % MCS: 0 - BPSK 1/2
        numTransmitAntennas = 1;
        cfg = wlanVHTConfig('ChannelBandwidth', chanBW, 'MCS', mcs, 'NumTransmitAntennas', numTransmitAntennas);
        sampleRate = wlanSampleRate(cfg);
        lstf = wlanLSTF(cfg);
        lltf = wlanLLTF(cfg);
        lsig = wlanLSIG(cfg);
        vhtsigA = wlanVHTSIGA(cfg);
        vhtstf = wlanVHTSTF(cfg);
        vhtltf = wlanVHTLTF(cfg);
        vhtsigB = wlanVHTSIGB(cfg);
        data = [lstf; lltf; lsig; vhtsigA; vhtstf; vhtltf; vhtsigB];
        fieldInd = wlanFieldIndices(cfg);
end % channel configuration and packet generation
for antennaConfig = 1
    configurationOfAntennas(1) = winner2.AntennaArray();  % BS, передатчик, 1 дефолтная антенна
    configurationOfAntennas(2) = winner2.AntennaArray('ULA', globalParam.numberOfAntennas, globalParam.separationBetweenAntennas); % MS, приемник, 4 антенны
    for rotateAntennaArray = 1
        
%         % old way of doing that
%         theta = globalParam.WinnerArrayRotationAngle/180*pi();
%         antennaSeparation = globalParam.separationBetweenAntennas;
%         antennasPlacement = [-1.5*antennaSeparation*cos(theta) -1.5*antennaSeparation*sin(theta) 0;
%             -0.5*antennaSeparation*cos(theta) -0.5*antennaSeparation*sin(theta) 0;
%             0.5*antennaSeparation*cos(theta) 0.5*antennaSeparation*sin(theta) 0;
%             1.5*antennaSeparation*cos(theta) 1.5*antennaSeparation*sin(theta) 0];
%         configurationOfAntennas(2) = winner2.AntennaArray('Pos', antennasPlacement);
        
        configurationOfAntennas(2).Rot = pi*[0 0 globalParam.WinnerArrayRotationAngle/180].';
    end % rotate antenna array
end % antennaConfig
for plotAntennasArrangement = 1
    % Отрисовка массива не учитывает задаваемый поворот, т.к. это поворот всего
    % массива как единого целого, а отрисовка это графический вывод координат в
    % системе отсчета центра массива
    if globalParam.plotAntennasArrangement
        pos = {configurationOfAntennas(2).Element(:).Pos};
        figure, hold on, plot(cellfun(@(x) x(1),pos),cellfun(@(x) x(2),pos),'+');
        xlim([-1 1]), ylim([-1 1]), title('AA Element Positions');
    end
end % plot antennas arrangement
for cfgLayoutConfig = 1
    maximumRangeBetweenMSandBS=50; % maximum layout range in meters used to randomly generate the MS and BS positions.
    msIdx = 2; bsIdx = {1}; numLinks = 1;
    cfgLayout = winner2.layoutparset(msIdx, bsIdx, numLinks, configurationOfAntennas, ...
        maximumRangeBetweenMSandBS, globalParam.seedForScenario);
    cfgLayout.Pairing = [1; 2];
    cfgLayout.ScenarioVector = 1; % A1 scenario
    cfgLayout.PropagConditionVector = globalParam.WinnerUseLos; % 0 - NLOS, 1 - LOS

    STAvelocity = 1e-6;
    cfgLayout.Stations(2).Velocity = [-STAvelocity 0 0].';

    if globalParam.WinnerUseFixedSTApositions
        cfgLayout.Stations(1).Pos= globalParam.BSposition; % BS position, transmitter, 1 antenna
        cfgLayout.Stations(2).Pos = globalParam.MSposition; % MS position, receiver, 4 antennas
    end
end % cfgLayoutConfig
for cfgModelParam = 1
cfgModel = winner2.wimparset;
cfgModel.RandomSeed = globalParam.seedForScenario;    % Repeatability
cfgModel.CenterFrequency = globalParam.centralFrequency;   % Carrier frequency in Hz
cfgModel.UseManualPropCondition = 'yes'; % the propagation condition (los/nlos) setting is defined manually
cfgModel.UniformTimeSampling = 'yes'; % all links to be sampled at the same time instants
cfgModel.SampleDensity = round(physconst('LightSpeed') / ...
     globalParam.centralFrequency/2/(STAvelocity/sampleRate)); % Oversampling factor, number of time samples per half wavelength

if globalParam.WinnerUseFixedPowerDelay
    cfgModel.FixedPdpUsed = 'yes'; % the power and delay parameters are not drawn randomly
else
    cfgModel.FixedPdpUsed = 'no';
end
if globalParam.WinnerUseFixedAngles
    cfgModel.FixedAnglesUsed    = 'yes'; % the angle parameters are not drawn randomly
else
    cfgModel.FixedAnglesUsed    = 'no';
end
if globalParam.WinnerDivideStrongestClusters
    cfgModel.IntraClusterDsUsed = 'yes'; % the two strongest clusters in power are divided in delay into three subclusters
else
    cfgModel.IntraClusterDsUsed = 'no';
end
if globalParam.WinnerUsePolarisedArrays
    cfgModel.PolarisedArrays    = 'yes'; % Use dual-polarized arrays
else
    cfgModel.PolarisedArrays    = 'no';
end
if globalParam.WinnerUsePathLossModel
    cfgModel.PathLossModelUsed = 'yes';
else
    cfgModel.PathLossModelUsed = 'no';
end
if globalParam.WinnerUseShadowingModel
    cfgModel.ShadowingModelUsed = 'yes'; 
else
    cfgModel.ShadowingModelUsed = 'no';
end

numPadZeros = 10 * globalParam.oversamplingFactor; % 10 all-zero samples appended to account for channel filter delay
cfgModel.NumTimeSamples = length(data);

end % cfgModelParam

for iterationProcessing = 1
    resultingIterationsNum = globalParam.WinnerNumberOfIterations;
    matrixCSI = zeros(484, globalParam.numberOfAntennas, resultingIterationsNum);
    signalToSave = zeros([cfgModel.NumTimeSamples globalParam.numberOfAntennas resultingIterationsNum]);
    for it = 1:resultingIterationsNum
        WINNERChan = comm.WINNER2Channel(cfgModel, cfgLayout);
        chanOut = WINNERChan(data);
        signal = chanOut{1};
        signal=resample(signal, 1, globalParam.oversamplingFactor);      

        for useAwgn = 1
            globalData.SNR = globalParam.SNR;
            globalData.seedSNR = globalParam.seedForChannelEvolution;
            if globalParam.WinnerUseAWGN
                noisySignal = awgn(signal, globalParam.SNR, 'measured', globalParam.seedForChannelEvolution);
            else
                noisySignal = signal;
            end
            signalToSave(:,:,it) = noisySignal;
        end % useAwgn
        for subcarrierProcessing = 1
            csiPerPacket = wlanVHTLTFDemodulate(signal(fieldInd.VHTLTF(1):fieldInd.VHTLTF(2),:), cfg);
            csiBefore = wlanVHTLTFDemodulate(data(fieldInd.VHTLTF(1):fieldInd.VHTLTF(2),:), cfg);

            csiPerPacket = csiPerPacket.*exp(-1i*angle(csiBefore));
            csiPerPacket = permute(csiPerPacket, [1 3 2]);
            matrixCSI(:, :, it) = csiPerPacket;
        end % subcarrierProcessing        
        globalParam.seedForChannelEvolution = globalParam.seedForChannelEvolution + 1;
        
        release(WINNERChan);
    end

end % iterationProcessing
for measureExecutionTime = 1
    if globalParam.printWinnerExecutionTime
        WinnerExecutionTime = toc
    end
end % measure execution time
for saveData = 1
    save('data/signal.mat', 'signalToSave');
    save('data/matrixCSI.mat', 'matrixCSI');
    
    matrixCSI = matrixCSI(1:120,1:8,1:30);
    s=num2str(globalParam.seedForScenario); str = '00000'; str(end+1-length(s):end) = s; str = "experiment/winner_csi/csi_" + str + ".txt";
    fileID = fopen(str, 'w');
    for k = 1:size(matrixCSI,3)
        for j = 1:size(matrixCSI,2)
            for i = 1:size(matrixCSI,1)
                fprintf(fileID, "%.10f+%.10fi ", real(matrixCSI(i,j,k)),imag(matrixCSI(i,j,k)));
            end
        end
    end
    fclose(fileID);

end % save data, such as signal and vector of CSI
for plotImpulseResponse = 1
    if globalParam.plotWinnerImpulseResponse
        release(WINNERChan);
        
        frameLen = cfgModel.NumTimeSamples;
        impulseSigTx = [ones(1,1);zeros(frameLen-1,1)];
        impulseSigRx = WINNERChan(impulseSigTx);
        
        chanInfo = info(WINNERChan);
        figure, hold on, stem((0:frameLen-1)/chanInfo.SampleRate, abs(impulseSigRx{1}(:,:))), legend;
        minX = -0.1e-6; maxX = 2e-6; xlim([minX, maxX]);
        xlabel('Time (s)'); ylabel('Magnitude'); title('Impulse Response for 4 antennas');
    end
end % plot impulse response

end % ScenarioWinner