function Spotfi() %#codegen

global globalParam;
global globalSpotfiParam;

for measureExecutionTime = 1
    if globalParam.printSpotfiExecutionTime
        tic
    end
end % measure execution time
for readCSIfromFile = 1    
    subCarrInd = globalParam.subCarrIndStart:globalParam.subCarrIndStep:globalParam.subCarrIndEnd;
    
    switch globalParam.csiSource
        case 0 % from winner
            file = load('data/matrixCSI');
            matrixCSI = file.matrixCSI;
            matrixCSI = matrixCSI(subCarrInd, 1:globalParam.numberOfAntennas,:);

            if globalParam.printDifAngleCSI
                ang = angle(matrixCSI);
                difAngleCSI = ang(2:end,:) - ang(1:end-1,:)
                %difAngleCSI = ang(:,2:end) - ang(:,1:end-1)
            end
        case 1 % from file with CSI from Intel NIC
            file = load('csi/sample_csi_trace');
            matrixCSI = file.sample_csi_trace;
            matrixCSI = reshape(matrixCSI,30,3);
        case 2
            matrixCSI = zeros(30,3,globalParam.WinnerNumberOfIterations * globalParam.numberOfPacketsPerIteration);
%             csi_trace = read_bf_file('csi/los6m-circle-bc-t1-1');
            csi_trace = read_bf_file('csi/los6m-circle-bc-t1-2');
            
            for i=1:globalParam.WinnerNumberOfIterations * globalParam.numberOfPacketsPerIteration
                matrixCSI(:,:,i) = permute(get_scaled_csi(csi_trace{i}),[3 2 1]);
            end
        case 3
%             csi = load('csi/meeting_los_static_close.mat');
            csi = load('csi/meeting_los_static_far.mat');
            subCarrInd = 6:18;
%             matrixCSI = permute(csi.H(6, subCarrNum,1,:), [2 4 1 3]);
            matrixCSI = permute(csi.H(2, subCarrInd,:,1), [2 3 1 4]);
    end
    
    if globalParam.plotPureCSI == 1
        figure, plot(db(abs(matrixCSI(:,:,1)))), title('Pure CSI')
    end
    
end % read CSI from file

% seed = 5;
% s=sprintf('%d',int32(seed)); str = '00000'; str(end+1-length(s):end) = s;
% filename = "winner_csi/csi_" + str + ".txt";
% f = fopen(filename, 'r');
% fseek(f, 0, 'eof');
% filelen = int32(ftell(f));
% fseek(f,0,'bof');
% maxBufferSize = int32(2^20);
% buffer = zeros(1, maxBufferSize,'uint8');
% remaining = filelen;
% index = int32(1);
% 
% while remaining > 0
%     if remaining + index > size(buffer,2)
%         fprintf('Attempt to read file which is bigger than internal buffer.\n');
%         fprintf('Current buffer size is %d bytes and file size is %d bytes.\n', maxBufferSize, filelen);
%         break
%     end
%     
%     [dataRead, nread] = fread(f,remaining, 'char');
%     buffer(index:index+nread-1) = dataRead;
%     n = int32(nread);
%     if n == 0
%         break;
%     end
%     % Did something went wrong when reading?
%     if n < 0
%         fprintf('Could not read from file: %d.\n', n);
%         break;
%     end
%     % Update state variables
%     remaining = remaining - n;
%     index = index + n;
% end
% 
% % Close file
% fclose(f);
% 
% str = (char(buffer(1:index)));
% str = str(1:index-1);
% 
% num = 28800;
% y = complex(zeros(1,num));
% 
% k = 1;
% for i = 1:num
%     j = k;
%     while str(j) ~= ' '
%         j = j + 1;
%     end
%     y(i) = str2double(str(k:j-1));
%     k = j + 1;
% end
% 
% matrixCSI = reshape(y,120,8,30);
% matrixCSI = matrixCSI(subCarrInd, 1:globalParam.numberOfAntennas,:);

for globalSpotfiParamConfiguration = 1
    globalSpotfiParam = struct;
    globalSpotfiParam.numberOfGridPoints = globalParam.SpotfiNumberOfGridPoints;
    globalSpotfiParam.delayRange = globalParam.SpotfiNSDelayRange * 1e-9;
    globalSpotfiParam.angleRange = globalParam.SpotfiAngleRange;
    globalSpotfiParam.SubCarrInd = subCarrInd;
    globalSpotfiParam.numberOfAntennaInSubset = globalParam.numberOfAntennas - globalParam.SpotfiSubarrayNum + 1;
    globalSpotfiParam.numberOfSubcarrierSubsets = floor(length(globalSpotfiParam.SubCarrInd)/2); % number fo subset of subcarriers chosen for smoothing music
    globalSpotfiParam.deltaRange = [0 0];
    globalSpotfiParam.numberOfAntennas = globalParam.numberOfAntennas;
    globalSpotfiParam.plotSanitizedCSI = globalParam.plotSanitizedCSI;
    globalSpotfiParam.frequencyGap = globalParam.frequencyGap;
    globalSpotfiParam.centralFrequency = globalParam.centralFrequency;
    globalSpotfiParam.separationBetweenAntennas = globalParam.separationBetweenAntennas;
    globalSpotfiParam.SpotfiMode = globalParam.SpotfiMode;
    globalSpotfiParam.SpotfiPeaksMode = globalParam.SpotfiPeaksMode;
    globalSpotfiParam.numberOfSetsOfCSI = globalParam.SpotfiNumberOfIterations;
    globalSpotfiParam.numberOfPeaksToDetect = globalParam.SpotfiNumberOfPeaksToDetect;
    globalSpotfiParam.peakThresholdRate = globalParam.SpotfiPeakThresholdRate;
    globalSpotfiParam.SpotfiMaxNumberOfPeaks = globalParam.SpotfiMaxNumberOfPeaks;
    globalSpotfiParam.backwardSmoothingUsed = globalParam.SpotfiBackwardSmoothingUsed;
    globalSpotfiParam.numberOfPacketsPerIteration = globalParam.numberOfPacketsPerIteration;
    globalSpotfiParam.usePhaseCompensation = globalParam.usePhaseCompensation;
end % globalSpotfiParam configuration
for mainPartOfComputingSpotfi = 1
    sanitizedVectorCSI = sanitizeCSI(matrixCSI);

    param.K = globalSpotfiParam.numberOfAntennaInSubset;
    param.L = globalSpotfiParam.numberOfSubcarrierSubsets;
    param.M = globalSpotfiParam.numberOfAntennas;
    param.N = length(globalSpotfiParam.SubCarrInd);
    param.T = globalSpotfiParam.numberOfSetsOfCSI;
    param.S = globalSpotfiParam.numberOfPacketsPerIteration;
    param.backw = globalParam.SpotfiBackwardSmoothingUsed;
    
    matrixCSI = formatCSI(sanitizedVectorCSI);
%     if globalSpotfiParam.numberOfAntennas == 4
%         matrixCSI = format4ant_test_mex(sanitizedVectorCSI, param);
%     else
%         matrixCSI = format8ant_test_mex(sanitizedVectorCSI, param);
%     end
    
    nsDelayAngleSpotfiEstimated = [];
    if isempty(globalParam.indicesOfWinnerIterationsUsed)
        for t = 1:globalSpotfiParam.numberOfSetsOfCSI
            [Qn,Qs] = findSpotfiEigenVectors(matrixCSI(:,:,t));
            [newEstimation, maxPeak] = pseudoSpectrumAndPeaksForSinglePacket(Qn,Qs, t);
            newEstimation = newEstimation(:,newEstimation(2,:)>-89 & newEstimation(2,:)<89);
            if globalParam.onlyStrongPeaksUsed
                if maxPeak > globalParam.strongPeakThreshold
                    nsDelayAngleSpotfiEstimated = [nsDelayAngleSpotfiEstimated newEstimation];
                end
            else
                nsDelayAngleSpotfiEstimated = [nsDelayAngleSpotfiEstimated newEstimation];
            end
        end
    else
        for i = 1:length(globalParam.indicesOfWinnerIterationsUsed)
            t = globalParam.indicesOfWinnerIterationsUsed(i);
            [Qn,Qs] = findSpotfiEigenVectors(matrixCSI(:,:,t));
            [newEstimation, maxPeak] = pseudoSpectrumAndPeaksForSinglePacket(Qn,Qs, t);
            if globalParam.onlyStrongPeaksUsed
                if maxPeak > globalParam.strongPeakThreshold
                    nsDelayAngleSpotfiEstimated = [nsDelayAngleSpotfiEstimated newEstimation];
                end
            else
                nsDelayAngleSpotfiEstimated = [nsDelayAngleSpotfiEstimated newEstimation];
            end
        end
    end
    if globalParam.printResultingSpotfiOutput
        nsDelayAngleSpotfiEstimated
    end   
    if globalParam.buildClusters
        for i=globalParam.numberOfClusters
            buildClusters(nsDelayAngleSpotfiEstimated, i);
        end
    end % buildClusters
end
% main part of computing Spotfi, such as sanitize CSI, format CSI, find eigen vectors, compute spectrum and find peaks

for measureExecutionTime = 1
    if globalParam.printSpotfiExecutionTime
        SpotfiExecutionTime = toc
    end
end % measure execution time

end % Spotfi

function sanitizedVectorCSI = sanitizeCSI(vectorCSI)

global globalSpotfiParam;

sanitizedVectorCSI = zeros(size(vectorCSI));
numberOfAntennas = globalSpotfiParam.numberOfAntennas;
for packetIteration=1:globalSpotfiParam.numberOfSetsOfCSI*globalSpotfiParam.numberOfPacketsPerIteration
    reshapedCSI = reshape(vectorCSI(:,:,packetIteration), length(globalSpotfiParam.SubCarrInd), numberOfAntennas);
    
    [PhaseSlope, PhaseConstant] = removePhsSlope(reshapedCSI);
    if globalSpotfiParam.usePhaseCompensation
        phaseCompensation = exp(1i*(-PhaseSlope*repmat(globalSpotfiParam.SubCarrInd(:),1, numberOfAntennas) ...
            - PhaseConstant*ones(length(globalSpotfiParam.SubCarrInd), numberOfAntennas)));
        reshapedCSI = reshapedCSI .* phaseCompensation;
    end
    sanitizedVectorCSI(:,:,packetIteration) = reshapedCSI;
end

if globalSpotfiParam.plotSanitizedCSI == 1
    figure, plot(abs(sanitizedVectorCSI(:,:,1))), title('Sanitized CSI')
end

end

function [PhaseSlope, PhaseConstant] = removePhsSlope(reshapedCSI)

global globalSpotfiParam;

PhaseRelatedToFirstPacket = unwrap(angle(reshapedCSI));

for antIdForPhs = 1:globalSpotfiParam.numberOfAntennas
    if  PhaseRelatedToFirstPacket(1,antIdForPhs) - PhaseRelatedToFirstPacket(1,1) > pi
        PhaseRelatedToFirstPacket(:,antIdForPhs) = PhaseRelatedToFirstPacket(:,antIdForPhs) - 2*pi;
    elseif PhaseRelatedToFirstPacket(1,antIdForPhs) - PhaseRelatedToFirstPacket(1,1) < -pi
        PhaseRelatedToFirstPacket(:,antIdForPhs) = PhaseRelatedToFirstPacket(:,antIdForPhs) + 2*pi;
    end
end
A = [repmat(globalSpotfiParam.SubCarrInd(:), globalSpotfiParam.numberOfAntennas, 1) ones(length(globalSpotfiParam.SubCarrInd)*globalSpotfiParam.numberOfAntennas, 1)];
x = A\PhaseRelatedToFirstPacket(:);
PhaseSlope = x(1);
PhaseConstant = x(2);

end % removePhsSlope

function matrixCSI = formatCSI(vectorCSI)

global globalSpotfiParam;

K = globalSpotfiParam.numberOfAntennaInSubset;
L = globalSpotfiParam.numberOfSubcarrierSubsets;
M = globalSpotfiParam.numberOfAntennas;
N = length(globalSpotfiParam.SubCarrInd);
T = globalSpotfiParam.numberOfSetsOfCSI;
S = globalSpotfiParam.numberOfPacketsPerIteration;

vectorCSI = vectorCSI(:,:,1:T*S);

csiTracePerPacket = reshape(vectorCSI, N, M, T*S);

if globalSpotfiParam.backwardSmoothingUsed
    columnsNum = (M - K + 1)*(N - L + 1);
    matrixCSI=zeros(K * L, columnsNum*2*S, T);
    for t = 1:T
        for s = 1:S
            csiFromEachPacket = csiTracePerPacket(:,:,(t-1)*S+s);
            D = [];
            for m=1:M % mth antenna
                D{m} = hankel(csiFromEachPacket(1:L,m),csiFromEachPacket(L:N, m));
            end
            De = zeros(K * L, columnsNum);
            for start_idx = 1:K
                tmp =  cat(2,D{start_idx:start_idx+M-K});
                De((start_idx-1)*L+(1:L),:) = tmp;
            end
            matrixCSI(:,(s-1)*columnsNum*2+1:s*columnsNum*2-columnsNum,t) = De;
        end
    end
    
    conjCsiTracePerPacket = conj(csiTracePerPacket(size(csiTracePerPacket,1):-1:1,size(csiTracePerPacket,2):-1:1,:));
    
    for t = 1:T
        for s = 1:S
            csiFromEachPacket = conjCsiTracePerPacket(:,:,(t-1)*S+s);
            D = [];
            for m=1:M % mth antenna
                D{m} = hankel(csiFromEachPacket(1:L,m),csiFromEachPacket(L:N, m));
            end
            De = zeros(K * L, (M - K + 1)*(N - L + 1));
            for start_idx = 1:K
                tmp =  cat(2,D{start_idx:start_idx+M-K});
                De((start_idx-1)*L+(1:L),:) = tmp;
            end
            matrixCSI(:,(s-1)*columnsNum*2+columnsNum+1:s*columnsNum*2,t) = De;
        end
    end
else
    columnsNum = (M - K + 1)*(N - L + 1);
    matrixCSI=zeros(K * L, columnsNum*S, T);
    for t = 1:T
        for s = 1:S
            csiFromEachPacket = csiTracePerPacket(:,:,(t-1)*S+s);
            D = [];
            for m=1:M % mth antenna
                D{m} = hankel(csiFromEachPacket(1:L,m),csiFromEachPacket(L:N, m));
            end
            De = zeros(K * L, columnsNum);
             for start_idx = 1:K
                tmp =  cat(2,D{start_idx:start_idx+M-K});
                De((start_idx-1)*L+(1:L),:) = tmp;
            end
            matrixCSI(:,(s-1)*columnsNum+1:s*columnsNum,t) = De;
        end
    end
end

end % formatCSI

function [Qn,Qs] = findSpotfiEigenVectors(matrixCSI)

global globalParam;

Rxx = matrixCSI*matrixCSI';

[Utmp,D] = eig(Rxx);
d = diag(abs(D));
[~,I] = sort(d, 'ascend');
U = Utmp(:,I);
d = d(I);

if globalParam.SpotfiEigenMode == 1
        N = 0;
        for i = 1:size(D,1)
            if D(i,i) < globalParam.SpotfiEigenThreshold
                N = i;
            end
        end
        if N == 0
            error('Spotfi: sources not found')
        end
        
        Qs = U(:,N+1:end);
        Qn = U(:,1:N);
        
        if globalParam.SpotfiPrintEigen
            noiseEigen = d(1:N)
            signalEigen = d(N+1:end)
            threshold = globalParam.SpotfiEigenThreshold
        end
        
        if globalParam.SpotfiMeasurement            
            str = "noise:";
            for i = 1:N
                str = str + " " + string(round(d(i)*1000)/1000);
            end
            str = str + " signal:";
            for i = N+1:length(d)
                str = str + " " + string(round(d(i)*1000)/1000);
            end
            str = str + "\n";
            fileID = fopen(globalParam.directory+"SpotfiEigen.txt", 'a');
            fprintf(fileID, str);
            fclose(fileID);
        end
elseif globalParam.SpotfiEigenMode == 2
        [~,I] = sort(d, 'ascend');
        U = Utmp(:,I);
        d = d(I);
        
        N = 0;
        for i = 1:size(D,1)
            if D(i,i) < globalParam.SpotfiEigenThresholdFromMax * D(end,end)
                N = i;
            end
        end
        if N == 0
            error('Spotfi: sources not found')
        end
        
        Qs = U(:,N+1:end);
        Qn = U(:,1:N);
        
        if globalParam.SpotfiPrintEigen
            noiseEigen = d(1:N)
            signalEigen = d(N+1:end)
            thresholdFromMax = globalParam.SpotfiEigenThresholdFromMax * D(end,end)
        end
elseif globalParam.SpotfiEigenMode == 0
    N = globalParam.SpotfiNumNoiseEigVector;
    
    if N > 0
        [~,I] = sort(d, 'ascend');
        U = Utmp(:,I);
        d = d(I);

        Qs = U(:,N+1:end);
        Qn = U(:,1:N);
        
        if globalParam.SpotfiPrintEigen
            noiseEigen = d(1:N)
            signalEigen = d(N+1:end)
            fprintf('fixed %d noise eig\n', N)
        end
    else
        [~,I] = sort(d, 'descend');
        U = Utmp(:,I);
        d = d(I);

        N = -N;
        Qn = U(:,N+1:end);
        Qs = U(:,1:N);
        
        if globalParam.SpotfiPrintEigen
            noiseEigen = d(N+1:end)
            signalEigen = d(1:N)
            fprintf('fixed %d signal eig\n', N)
        end
    end
end

end % findSpotfiEigenValues

function [nsDelayAngleSpotfiEstimated, SpotfiSpectrum, strongestPeaks, maxPeak] = computePseudoSpectrumAndFindPeaks(Qn,Qs)

global globalSpotfiParam;

for gridStartStopSpacingDefine = 1
    numberOfGridPoints = globalSpotfiParam.numberOfGridPoints;
    GridStart = [globalSpotfiParam.delayRange(1) globalSpotfiParam.angleRange(1) globalSpotfiParam.deltaRange(1)];
    GridStop = [globalSpotfiParam.delayRange(2) globalSpotfiParam.angleRange(2) globalSpotfiParam.deltaRange(2)];
    GridSpacing = (GridStop-GridStart)./max(1, numberOfGridPoints-ones(size(numberOfGridPoints)));
end % define grid start/stop/spacing
for SpotfiModes = 1
switch globalSpotfiParam.SpotfiMode
    case 0 % using matrix multiplications for computing spectrum
        Ps = (Qs*Qs');
                
        delayConsider = GridStart(1) + (0:numberOfGridPoints(1)-1)*GridSpacing(1);
        u_sConsider = (globalSpotfiParam.separationBetweenAntennas*globalSpotfiParam.centralFrequency/physconst('LightSpeed')) * ...
            sind( GridStart(2) + (0:numberOfGridPoints(2)-1)*GridSpacing(2) );
        
        delaySteering = exp(-1i*2*pi*(globalSpotfiParam.SubCarrInd(1:globalSpotfiParam.numberOfSubcarrierSubsets).')*globalSpotfiParam.frequencyGap*delayConsider);
        aoaSteering = exp(-1i*2*pi*(((globalSpotfiParam.numberOfAntennaInSubset-1)/2:(globalSpotfiParam.numberOfAntennaInSubset-1)/2)')*u_sConsider);
        steeringVectors = kron(aoaSteering, delaySteering);
        
        music_spec_num = sum((steeringVectors').*((Ps*steeringVectors).'),2);
        music_spec_den = sum((steeringVectors').*(steeringVectors.'),2);
        SpotfiSpectrum = abs(music_spec_num./music_spec_den);
    case 1 % looping over all possible grid values for computing spectrum
        delayStart = GridStart(1);
        angleStart = GridStart(2);
        delayDiff = GridSpacing(1);
        angleDiff = GridSpacing(2);
        
        [delayIndices, angleIndices, ~] = ind2sub(numberOfGridPoints,1:prod(numberOfGridPoints));

        delayGridValue = delayStart + (delayIndices-1)*delayDiff;
        angleGridValue = (angleStart + (angleIndices-1)*angleDiff)*pi/180;
        u_sGridValue = (globalSpotfiParam.separationBetweenAntennas*globalSpotfiParam.centralFrequency/physconst('LightSpeed'))*sin(angleGridValue);

        SpotfiSpectrum = zeros(prod(numberOfGridPoints),1);

        Ps = (Qs*Qs');
        
        for loopVar = 1:prod(numberOfGridPoints)
            steeringVector = computeSteeringVectorAtGivenGridPoint(u_sGridValue(loopVar), delayGridValue(loopVar));
            SpotfiSpectrum(loopVar) = (steeringVector'*Ps*steeringVector)/(steeringVector'*steeringVector);
        end

        SpotfiSpectrum = abs(SpotfiSpectrum);
    case 2
        delayConsider = GridStart(1) + (0:numberOfGridPoints(1)-1)*GridSpacing(1);
        u_sConsider = (globalSpotfiParam.separationBetweenAntennas*globalSpotfiParam.centralFrequency/physconst('LightSpeed')) * ...
            sind(GridStart(2) + (0:globalSpotfiParam.numberOfGridPoints(2)-1)*GridSpacing(2) );

        delaySteering = exp(-1i*2*pi*(globalSpotfiParam.SubCarrInd(1:globalSpotfiParam.numberOfSubcarrierSubsets).')*globalSpotfiParam.frequencyGap*delayConsider);
        aoaSteering = exp(-1i*2*pi*(((globalSpotfiParam.numberOfAntennaInSubset-1)/2:-1:-(globalSpotfiParam.numberOfAntennaInSubset-1)/2)')*u_sConsider);
        steeringVector = kron(aoaSteering, delaySteering);
        
        Pn = (Qn*Qn');

        SpotfiSpectrum = sum((steeringVector').*((Pn*steeringVector).'),2);
        SpotfiSpectrum = 1./abs(SpotfiSpectrum);
end

end % SpotfiModes

SpotfiSpectrum = SpotfiSpectrum - min(SpotfiSpectrum);

maxPeak = max(SpotfiSpectrum);

for findPeaksOnSpectrum = 1
    switch globalSpotfiParam.SpotfiPeaksMode
        case 0
            [globalMaximumValue,loopVarMax] = max(SpotfiSpectrum);
            [delay_idx,angle_idx] = ind2sub(numberOfGridPoints,loopVarMax);
            delayFromMusic = GridStart(1) + (delay_idx-1)*GridSpacing(1);
            angleFromMusic = GridStart(2) + (angle_idx-1)*GridSpacing(2);
            strongestPeaks = SpotfiSpectrum .* (SpotfiSpectrum == globalMaximumValue);
            nsDelayAngleSpotfiEstimated = [delayFromMusic*1e9 angleFromMusic 0].';
            strongestPeaks = reshape(strongestPeaks,numberOfGridPoints(1),numberOfGridPoints(2),numberOfGridPoints(3));
            SpotfiSpectrum = reshape(SpotfiSpectrum,numberOfGridPoints(1),numberOfGridPoints(2),numberOfGridPoints(3));
        case 1
            SpotfiSpectrum = reshape(SpotfiSpectrum,numberOfGridPoints(1),numberOfGridPoints(2),numberOfGridPoints(3));
            isPeak = imregionalmax(SpotfiSpectrum);
            [delay_idx, angle_idx] = ind2sub(size(isPeak), find(isPeak));
            isStrongEnough = SpotfiSpectrum(isPeak) > (globalSpotfiParam.peakThresholdRate * max(SpotfiSpectrum(isPeak)));
            delay_idx = delay_idx(isStrongEnough);
            angle_idx = angle_idx(isStrongEnough);
            
            delayFromMusic = GridStart(1) + (delay_idx-1)*GridSpacing(1);
            angleFromMusic = GridStart(2) + (angle_idx-1)*GridSpacing(2);
            nsDelayAngleSpotfiEstimated = [delayFromMusic*1e9 angleFromMusic].';
            
            globalMaximumValue = max(SpotfiSpectrum(isPeak));
            pointIsPeak = SpotfiSpectrum & isPeak;
            eachPeakValue = pointIsPeak .*  SpotfiSpectrum;
            isPeakMoreThenThreshold = eachPeakValue > (globalSpotfiParam.peakThresholdRate * globalMaximumValue);
            strongestPeaks = isPeakMoreThenThreshold .* SpotfiSpectrum;
        case 2
            SpotfiSpectrum = reshape(SpotfiSpectrum,numberOfGridPoints(1),numberOfGridPoints(2),numberOfGridPoints(3));
            strongestPeaks = zeros(size(SpotfiSpectrum));
            isPeak = imregionalmax(SpotfiSpectrum);
            [delay_idx, angle_idx] = ind2sub(size(isPeak), find(isPeak));
            [~,topPeakIndices] = maxk(SpotfiSpectrum(isPeak), min(globalSpotfiParam.numberOfPeaksToDetect, length(find(isPeak(:)))));
            delay_idx = delay_idx(topPeakIndices);
            angle_idx = angle_idx(topPeakIndices);

            delayFromMusic = GridStart(1) + (delay_idx-1)*GridSpacing(1);
            angleFromMusic = GridStart(2) + (angle_idx-1)*GridSpacing(2);
            nsDelayAngleSpotfiEstimated = [delayFromMusic*1e9 angleFromMusic].';

            for i = 1:length(delay_idx)
                strongestPeaks(delay_idx(i), angle_idx(i)) = SpotfiSpectrum(delay_idx(i), angle_idx(i));
            end
        case 3
            SpotfiSpectrum = reshape(SpotfiSpectrum,numberOfGridPoints(1),numberOfGridPoints(2),numberOfGridPoints(3));
            strongestPeaks = zeros(size(SpotfiSpectrum));

            isPeak = imregionalmax(SpotfiSpectrum);
            [delay_idx, angle_idx] = ind2sub(size(isPeak), find(isPeak));
            peaks = SpotfiSpectrum(isPeak);
            isStrongEnough = peaks > (globalSpotfiParam.peakThresholdRate * max(peaks));
            delay_idx = delay_idx(isStrongEnough);
            angle_idx = angle_idx(isStrongEnough);
            
            [~,topPeakIndices] = maxk(peaks(isStrongEnough), min(globalSpotfiParam.SpotfiMaxNumberOfPeaks, length(find(isStrongEnough(:)))));

            delay_idx = delay_idx(topPeakIndices);
            angle_idx = angle_idx(topPeakIndices);

            delayFromMusic = GridStart(1) + (delay_idx-1)*GridSpacing(1);
            angleFromMusic = GridStart(2) + (angle_idx-1)*GridSpacing(2);
            nsDelayAngleSpotfiEstimated = [delayFromMusic*1e9 angleFromMusic].';
            
            for i = 1:length(delay_idx)
                strongestPeaks(delay_idx(i), angle_idx(i)) = SpotfiSpectrum(delay_idx(i), angle_idx(i));
            end
    end

end % find peaks on the spectrum

end
% compute pseudospectrum and find peaks

function steeringVector = computeSteeringVectorAtGivenGridPoint(u_sGridValue, delayGridValue)

global globalSpotfiParam;

M = globalSpotfiParam.numberOfAntennaInSubset;
ChosenSubCarrInd = globalSpotfiParam.SubCarrInd(1:globalSpotfiParam.numberOfSubcarrierSubsets);

aoaSteering = exp(-1i*2*pi*u_sGridValue*(-(M-1)/2:(M-1)/2).');
delaySteering = exp(-1i*2*pi*(ChosenSubCarrInd(:))*globalSpotfiParam.frequencyGap*delayGridValue);

steeringVecDelayAoA = delaySteering*aoaSteering.';
steeringVector = steeringVecDelayAoA(:);

end
% compute steering vector at a given grid point

function [nsDelayAngleSpotfiEstimated, maxPeak] = pseudoSpectrumAndPeaksForSinglePacket(Qn, Qs, numberOfIteration)

global globalParam;
global globalSpotfiParam;

[nsDelayAngleSpotfiEstimated, SpotfiSpectrum, strongestPeaks, maxPeak] = computePseudoSpectrumAndFindPeaks(Qn,Qs);

for outputSpotfi = 1
    if globalParam.printSpotfiOutput
        nsDelayAngleSpotfiEstimated
    end
    
    if globalParam.plotSpotfiSpectrum || globalParam.plotSpotfiPeaks
        delayPoints = (globalSpotfiParam.delayRange(1):(globalSpotfiParam.delayRange(2)-globalSpotfiParam.delayRange(1))/ ...
            (globalSpotfiParam.numberOfGridPoints(1)-1):globalSpotfiParam.delayRange(2))*1e9;
        anglePoints = globalSpotfiParam.angleRange(1):(globalSpotfiParam.angleRange(2)-globalSpotfiParam.angleRange(1))/ ...
            (globalSpotfiParam.numberOfGridPoints(2)-1):globalSpotfiParam.angleRange(2);
                
%         if maxPeak > globalParam.strongPeakThreshold
%             str = "use with strength: " + string(maxPeak) + " vs " + string(globalParam.strongPeakThreshold);
%         else
%             str = "drop with strength: " + string(maxPeak) + " vs " + string(globalParam.strongPeakThreshold);
%         end

        str = "("+sprintf("%.2f",nsDelayAngleSpotfiEstimated(2))+char(176)+sprintf(",%.1f",nsDelayAngleSpotfiEstimated(1))+"ns"+")";
        
        if globalParam.plotSpotfiSpectrum
            f = figure; surf(anglePoints, delayPoints, SpotfiSpectrum), colorbar, xlabel('Angle, degrees'), ylabel('Delay, ns')
            shading interp, title(string(numberOfIteration)+" Pseudospectrum "+str), xlim([globalSpotfiParam.angleRange(1) globalSpotfiParam.angleRange(2)]);
            ylim([globalSpotfiParam.delayRange(1) globalSpotfiParam.delayRange(2)] * 1e9), xticks(-180:45:180), yticks(delayPoints(1):(delayPoints(end)-delayPoints(1))/5:delayPoints(end))
            
            if globalParam.saveSpotfiSpectrum
                saveas(f, globalParam.directory+string(numberOfIteration)+'_Spotfi.png');
            end
            if globalParam.closeSpotfiSpectrum
                close;
            end
        end
        
        if globalParam.plotSpotfiPeaks
            f = figure; surf(anglePoints, delayPoints, strongestPeaks), colorbar, xlabel('Angle, degrees'), ylabel('Delay, ns')
            shading interp, title('Pseudospectrum peaks '+string(numberOfIteration)), xlim([globalSpotfiParam.angleRange(1) globalSpotfiParam.angleRange(2)]);
            ylim([globalSpotfiParam.delayRange(1) globalSpotfiParam.delayRange(2)] * 1e9), xticks(-180:45:180), yticks(delayPoints(1):(delayPoints(end)-delayPoints(1))/5:delayPoints(end))
            
            if globalParam.saveSpotfiPeaks
                saveas(f, globalParam.directory+string(numberOfIteration)+'_SpotfiPeaks'+'.png');
            end
            if globalParam.closeSpotfiPeaks
                close;
            end
        end
    end
end

end
% compute spectrum and find peaks for single packet

function buildClusters(nsDelayAngleSpotfiEstimated, clusterNumber)

global globalParam;

delayMax = globalParam.SpotfiNSDelayRange(2);
angleMax = globalParam.SpotfiAngleRange(2);

Y = nsDelayAngleSpotfiEstimated(1:2,:)';
X(:,1) = Y(:,2) / angleMax;
X(:,2) = Y(:,1) / delayMax;

rng(3);
options = statset('MaxIter',3000);

threshold = sqrt(chi2inv(0.99,2));

if size(X,1) <= clusterNumber
    clusterNumber = size(X,1) - 1;
end

gmfit = fitgmdist(X,clusterNumber,'CovarianceType','diagonal', ...
    'SharedCovariance', false, 'RegularizationValue',0.0001, 'Options',options); % Fitted GMM
clusterX = cluster(gmfit,X); % Cluster index

clSize = zeros(clusterNumber, 1);
stdA = zeros(clusterNumber, 1);
stdD = zeros(clusterNumber, 1);
meanA = zeros(clusterNumber, 1);
meanD = zeros(clusterNumber, 1);
for l=1:clusterNumber
    clSize(l) = sum(clusterX == l);
    stdA(l) = round(std(X(clusterX == l, 1))*angleMax*1000)/1000;
    stdD(l) = round(std(X(clusterX == l, 2))*delayMax*1000)/1000;
    meanA(l) = round(mean(X(clusterX == l, 1))*angleMax*1000)/1000;
    meanD(l) = round(mean(X(clusterX == l, 2))*delayMax*1000)/1000;
end

if globalParam.SpotfiMeasurement
    T=table(clSize,stdA,stdD,meanA,meanD);
    T = sortrows(T, 1, 'descend');
    writetable(T, globalParam.directory+"SpotfiClusterization.txt", 'Delimiter','\t');
    
    if length(T.clSize) == 1
        T.stdA(2) = -1;
        T.meanA(2) = -1;
    elseif T.clSize(2) == 0
        T.stdA(2) = -1;
        T.meanA(2) = -1;
    end
    
    fileID = fopen(globalParam.fileForSpotfiResults, 'a');
    fprintf(fileID, string(globalParam.numberOfAntennas)+"\t"+string(globalParam.SpotfiSubarrayNum)+ ...
        "\t"+string(globalParam.seedForScenario)+"\t"+string(globalParam.SNR)+"\t"+string(globalParam.Kfactor)+ ...
        "\t"+string(globalParam.AngleOfLOS)+"\t"+string(T.meanA(1))+"\t"+string(T.stdA(1))+"\t"+string(T.clSize(1))+ ...
        "\t"+string(abs(T.meanA(1)-globalParam.AngleOfLOS))+"\t"+string(T.meanA(2))+ ...
        "\t"+string(T.stdA(2))+"\t"+string(T.clSize(2))+"\t"+string(globalParam.ArraytrackBackwardSmoothingUsed)+ ...
        "\t"+string(globalParam.SpotfiNumberOfIterations)+"\t"+string(globalParam.numberOfPacketsPerIteration)+"\t");
    fclose(fileID);
end

if globalParam.plotClusters
    d = 1000; % Grid length
    x1 = linspace(min(X(:,1))-2, max(X(:,1))+2, d);
    x2 = linspace(min(X(:,2))-2, max(X(:,2))+2, d);
    [x1grid,x2grid] = meshgrid(x1,x2);
    X0 = [x1grid(:) x2grid(:)];

    mahalDist = mahal(gmfit,X0); % Distance from each grid point to each GMM component
    % Draw ellipsoids over each GMM component and show clustering result.
    f=figure; h1 = gscatter(X(:,1)*angleMax,X(:,2)*delayMax,clusterX, [], [], []);
    hold on
    title('Spotfi estimated AoA and ToF');
    ylabel('Delays, ns');
    xlabel('Angle, degrees');
    ylim([-delayMax delayMax]*1.05);
    xlim([-angleMax angleMax]*1.05);
    
    for m = 1:clusterNumber
        idx = mahalDist(:,m)<=threshold;
        h2 = plot(X0(idx,1)*angleMax,X0(idx,2)*delayMax,'.','MarkerSize',1);
        uistack(h2,'bottom');
    end
    plot(gmfit.mu(:,1)*angleMax,gmfit.mu(:,2)*delayMax,'kx','LineWidth',2,'MarkerSize',10)
    
    lines = []; labels = [];
    number = 0;
    for i=1:clusterNumber
        if clSize(i)>0
            number = number + 1;
            lines = [lines h1(number)];
            labels = [labels string(clSize(i))+",("+...
                sprintf("%.1f",gmfit.mu(i,1)*angleMax)+char(176)+sprintf(",%.1f",gmfit.mu(i,2)*delayMax)+"ns"+")"];
        end
    end
    
    legend(lines, labels, 'Location','southwest', 'FontSize',7);
    hold off
    
    if globalParam.saveClusters
        saveas(f, globalParam.directory+"SpotfiClusters.png");
    end
    
    if globalParam.closeClusters
        close
    end
end

end