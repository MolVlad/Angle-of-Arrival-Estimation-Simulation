function ScenarioWinner()

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
        ltf = wlanVHTLTF(cfg);
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

end % cfgModelParam
for passingThroughChannel = 1
WINNERChan = comm.WINNER2Channel(cfgModel, cfgLayout);
numPadZeros = 10 * globalParam.oversamplingFactor; % 10 all-zero samples appended to account for channel filter delay
cfgModel.NumTimeSamples = length(ltf);
chanOut = WINNERChan(ltf);
signal = chanOut{1};
signal=resample(signal, 1, globalParam.oversamplingFactor);
end % passing through channel
for printChannelInfo = 1
if globalParam.printWinnerChannelInfo
    chanInfo = info(WINNERChan)
end
end % print chanel info
for plotPacketPreambule = 1
    if globalParam.plotPacketPreambule
        fieldInd = wlanFieldIndices(cfg);
        numPream = fieldInd.LSIG(2);
        numberOfAntennasToPrint = globalParam.antennasNum;
        figure, hold on;
        time = ((0:double(numPream)-1)/sampleRate)*1e6; % Массив временных отметок в мкс
        peak = 1.2*max(abs(chanOut{1}(1:numPream, 1)));
        fieldMarkers = zeros(numPream,1);
        fieldMarkers(fieldInd.LSTF(2)-1,1) = peak;
        fieldMarkers(fieldInd.LLTF(2)-1,1) = peak;
        fieldMarkers(fieldInd.LSIG(2)-1,1) = peak;
        plot(time,abs(chanOut{1}(1:numPream,1:numberOfAntennasToPrint)),time,fieldMarkers)
        xlabel ('Time (microseconds)'), ylabel('Magnitude'), title('Packet Preamble')
    end
end % plot packet preambule
for iterationProcessing = 1 
    resultingIterationsNum = globalParam.WinnerNumberOfIterations;
    matrixCSI = zeros(484, globalParam.numberOfAntennas, resultingIterationsNum);
    signalToSave = zeros([size(signal) resultingIterationsNum]);
    for it = 1:resultingIterationsNum
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
            csiPerPacket = wlanVHTLTFDemodulate(signal, cfg);
            csiBefore = wlanVHTLTFDemodulate(ltf, cfg);
            
            csiPerPacket = csiPerPacket.*exp(-1i*angle(csiBefore));
            csiPerPacket = permute(csiPerPacket, [1 3 2]);
            matrixCSI(:, :, it) = csiPerPacket;
        end % subcarrierProcessing
        globalParam.seedForChannelEvolution = globalParam.seedForChannelEvolution + 1;
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