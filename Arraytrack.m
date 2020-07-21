function Arraytrack()

global globalParam;

for measureExecutionTime = 1
    if globalParam.printArraytrackExecutionTime
        tic
    end
end % measure execution time
for readSignalFromFile = 1
    file=load('data/signal.mat');
    
    signal = file.signalToSave;
    signal = permute(signal, [2 1 3]);

    signal = signal(1:globalParam.numberOfAntennas,1:globalParam.ArraytrackSampleNum,:);
    
    if globalParam.ArraytrackBackwardSmoothingUsed
        signal = [signal conj(signal(size(signal,1):-1:1,:,:))];
    end
end % read signal from file
for defineAntennasPositions = 1
    antennasPositions = zeros(globalParam.numberOfAntennas - globalParam.ArraytrackSubarrayNum + 1,3);
    for i=1:globalParam.numberOfAntennas - globalParam.ArraytrackSubarrayNum + 1
        antennasPositions(i,1)=globalParam.separationBetweenAntennas*i;
    end
end % define antennas positions

% azimuthAngle = -90:0.5:90; % vector of angle of arrivals with 0.5 deg resolution
azimuthAngle = -90:0.1:90; % vector of angle of arrivals with 0.5 deg resolution
azimuthAngle = azimuthAngle.'; % transpose

musicSpectrum = zeros(length(azimuthAngle), globalParam.ArraytrackUsedPacketNum);
strongestPeaks = zeros(length(azimuthAngle), globalParam.ArraytrackUsedPacketNum);

for it = 1:globalParam.ArraytrackUsedPacketNum
    musicSpectrum(:,it) = reallocation(antennasPositions, azimuthAngle, signal(:,:,it));
    [angles, strongestPeaks(:,it)] = findPeaksOnSpectrum(musicSpectrum(:,it), azimuthAngle);
    ArraytrackEstimatedAngles{it} = angles(angles < 89.5 & angles > -89.5);
end

for resultsProcessing = 1
    ArraytrackStableStdMean = findstable(ArraytrackEstimatedAngles);
    if globalParam.printArraytrackStablePeaks
        ArraytrackStableStdMean = ArraytrackStableStdMean
    end
    if globalParam.ArraytrackMeasurement        
        for i = 1:length(ArraytrackEstimatedAngles)
            dlmwrite(globalParam.directory+"ArraytrackEstimatedAngles.txt", ArraytrackEstimatedAngles{i}', '-append', 'delimiter', '\t');
        end
        
        fileID = fopen(globalParam.directory+'ArraytrackStableStdMean.txt', 'w');
        fprintf(fileID, 'std\tangle\n');
        fclose(fileID);
        dlmwrite(globalParam.directory+"ArraytrackStableStdMean.txt", ArraytrackStableStdMean, '-append', 'delimiter', '\t');
        
        if size(ArraytrackStableStdMean,1) < 2
            ArraytrackStableStdMean(2,:) = [999 999];
        end
        
%         fileID = fopen(globalParam.fileForArraytrackResults, 'a');
%         fprintf(fileID, string(globalParam.numberOfAntennas)+"\t"+string(globalParam.ArraytrackSubarrayNum)+ ...
%             "\t"+string(globalParam.seedForScenario)+"\t"+string(globalParam.SNR)+"\t"+string(globalParam.Kfactor)+ ...
%             "\t"+string(globalParam.AngleOfLOS)+"\t"+string(ArraytrackStableStdMean(1,2))+"\t"+string(ArraytrackStableStdMean(1,1))+ ...
%             "\t"+string(abs(ArraytrackStableStdMean(1,2)-globalParam.AngleOfLOS))+"\t"+string(ArraytrackStableStdMean(2,2))+ ...
%             "\t"+string(ArraytrackStableStdMean(2,1))+"\t"+string(globalParam.ArraytrackBackwardSmoothingUsed)+ ...
%             "\t"+string(globalParam.ArraytrackUsedPacketNum)+"\n");
%         fclose(fileID);
    end
end % resultsProcessing
for sourcesCheckPlotSavePrint = 1
    if globalParam.plotArraytrackSpectrum
        f = figure; plot(azimuthAngle,musicSpectrum), xlabel('Angle, degrees'), ylabel('Amplitude');
        title("Pseudospectrum Arraytrack, stable: " + string(ArraytrackStableStdMean(1,2)));
        xlim([-100 100]), ylim([min(musicSpectrum, [], 'all') max(musicSpectrum, [], 'all')]), xticks(-180:45:180);
        
        if globalParam.saveArraytrackSpectrum
            saveas(f, globalParam.directory+"Arraytrack.png");
        end
        if globalParam.closeArraytrackSpectrum
            close
        end
    end
    
    if globalParam.plotArraytrackPeaks
        f = figure; plot(azimuthAngle,strongestPeaks), xlabel('Angle, degrees'), ylabel('Amplitude'), title('Peaks Arraytrack'),
        xlim([-100 100]), ylim([min(strongestPeaks)-2 max(strongestPeaks)+3]), xticks(-180:45:180);
        
        if globalParam.saveArraytrackPeaks
            saveas(f, globalParam.directory+"peaksArraytrack.png");
        end
    end

    if globalParam.printArraytrackOutput
        for it = 1:size(signal,3)
            ArraytrackEstimatedAngles{it}
        end
    end

end % plot, save, print
for measureExecutionTime = 1
    if globalParam.printArraytrackExecutionTime
        ArraytrackExecutionTime = toc
    end
end % measure execution time

end % Arraytrack

function musicSpectrum = reallocation(antennasPositions, azimuthAngle, signal)

global globalParam;

for findingEigenVectors = 1
    L = size(antennasPositions,1);

    Rxx = zeros(L,L, globalParam.ArraytrackSubarrayNum);
    for i = 1:globalParam.ArraytrackSubarrayNum
        s = signal(i:i+L-1,:);
        Rxx(:,:,i)=s*s'/globalParam.ArraytrackSampleNum; % correlation matrix
    end
    Rxx = sum(Rxx,3) / globalParam.ArraytrackSubarrayNum;
    
    if globalParam.ArraytrackMode == 0 % old way, comparison with threshold
        [Utmp, eigenValue]=eig(Rxx);
        eigen=diag(abs(eigenValue));
        [~,I] = sort(eigen, 'ascend');
        U = Utmp(:,I);
        eigen = eigen(I);
        
        N = 0;
        for i=1:size(antennasPositions,1)
            if eigen(i) < globalParam.ArraytrackThreshold
                N = i;
            end
        end
        
        if N == 0
            N = 1;
        end
        
        En = U(:,1:N);
        
        if globalParam.ArraytrackPrintEigen
            noiseEigen = eigen(1:N)
            signalEigen = eigen(N+1:end)
            threshold = globalParam.ArraytrackThreshold
        end
        
        if globalParam.ArraytrackMeasurement
            str = "noise:";
            for i = 1:N
                str = str + " " + string(round(eigen(i)*1000)/1000);
            end
            str = str + " signal:";
            for i = N+1:length(eigen)
                str = str + " " + string(round(eigen(i)*1000)/1000);
            end
            str = str + "\n";
            fileID = fopen(globalParam.directory+"ArrayTrackEigen.txt", 'a');
            fprintf(fileID, str);
            fclose(fileID);
        end
        
        if N == 0
            error('Arraytrack: sources not found')
        end
    elseif globalParam.ArraytrackMode == 1
        [Utmp,eigenValue] = eig(Rxx);
        eigen=diag(abs(eigenValue));
        [~,I] = sort(eigen, 'ascend');
        U = Utmp(:,I);
        eigen = eigen(I);
        
        N = globalParam.ArraytrackNoiseEigenNumber;
        En = U(:,1:N);
        
        if globalParam.ArraytrackPrintEigen
            noiseEigen = eigen(1:N)
            signalEigen = eigen(N+1:end)
            fprintf('fixed %d\n', N)
        end
    end
end % finding eigen vectors
for musicSpectrumComputation = 1
    elevationAngle = zeros(size(azimuthAngle)); % vector of zeros with the same size as az
    steeringVectors = steeringVectorsCreate(antennasPositions, [azimuthAngle + 90,elevationAngle], globalParam.centralFrequency);
    musicSpectrum=zeros(1,length(azimuthAngle));
    for i=1:length(azimuthAngle)
        musicSpectrum(i)=-10*log10(abs(steeringVectors(:,i)'*(En*En')*steeringVectors(:,i)));
    end
    musicSpectrum = musicSpectrum.';
end % music spectrum computation

musicSpectrum = musicSpectrum - min(musicSpectrum);

end % reallocation

function steeringVectors = steeringVectorsCreate(antennasPositions, directionOfArrival, centralFrequency)

directionOfArrival=directionOfArrival*pi()/180.0; % Degree to radian conversion
azimuthAngle = directionOfArrival(:,1);
elevationAngle = directionOfArrival(:,2);
projection = [cos(azimuthAngle).*cos(elevationAngle)   sin(azimuthAngle).*cos(elevationAngle)   sin(elevationAngle)]';

waveNumberProjection = 2 * pi() * centralFrequency / physconst('LightSpeed') * projection;
steeringVectors = exp(-1j*(antennasPositions*waveNumberProjection));

end % steeringVectorsCreate

function [ArraytrackEstimatedAngles, strongestPeaks] = findPeaksOnSpectrum(musicSpectrum, azimuthAngle)
global globalParam;

switch globalParam.ArraytrackPeaksMode
    case 0
        [globalMaximumValue, indexOfGlobalMaximum] = max(musicSpectrum);
        ArraytrackEstimatedAngles = azimuthAngle(1) + (indexOfGlobalMaximum-1)*(azimuthAngle(2)-azimuthAngle(1));
        strongestPeaks = musicSpectrum .* (musicSpectrum == globalMaximumValue);
    case 1
        isPeak = imregionalmax(musicSpectrum);
        peakIndex = ind2sub(size(isPeak), find(isPeak));
        isStrongEnough = musicSpectrum(isPeak) > (globalParam.ArraytrackPeakThresholdRate * max(musicSpectrum(isPeak)));
        peakIndex = peakIndex(isStrongEnough);
        ArraytrackEstimatedAngles = azimuthAngle(1) + (peakIndex-1)*(azimuthAngle(2)-azimuthAngle(1));
        
        globalMaximumValue = max(musicSpectrum(isPeak));
        pointIsPeak = musicSpectrum & isPeak;
        eachPeakValue = pointIsPeak .*  musicSpectrum;
        isPeakMoreThenThreshold = eachPeakValue > (globalParam.ArraytrackPeakThresholdRate * globalMaximumValue);
        strongestPeaks = isPeakMoreThenThreshold .* musicSpectrum;
    case 2
        strongestPeaks = zeros(size(musicSpectrum));
        isPeak = imregionalmax(musicSpectrum);
        peakIndex = ind2sub(size(isPeak), find(isPeak));
        [~,topPeakIndices] = maxk(musicSpectrum(isPeak), min(globalParam.ArraytrackNumberOfPeaksToDetect, length(find(isPeak(:)))));
        peakIndex = peakIndex(topPeakIndices);
        ArraytrackEstimatedAngles = azimuthAngle(1) + (peakIndex-1)*(azimuthAngle(2)-azimuthAngle(1));
        
        for i = 1:length(peakIndex)
            strongestPeaks(peakIndex(i)) = musicSpectrum(peakIndex(i));
        end
end
end % findPeaksOnSpectrum