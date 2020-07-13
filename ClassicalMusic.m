function ClassicalMusic()

global globalParam;

for measureExecutionTime = 1
    if globalParam.printClassicalMusicExecutionTime
        tic
    end
end % measure execution time
for readSignalFromFile = 1
    file=load('data/signal.mat');
    signal = file.signalToSave;
    signal = signal(:,:,1).';
    signal = signal(:,2000:2000-1+globalParam.classicalMusicSampleNum);
    
    if globalParam.classicalMusicBackwardSmoothingUsed
        signal = [signal conj(signal(size(signal,1):-1:1,:))];
    end
end % read signal from file
for defineAntennasPositions = 1
    antennasPositions = zeros(globalParam.numberOfAntennas,3);
    for i=1:globalParam.numberOfAntennas
        antennasPositions(i,1)=globalParam.separationBetweenAntennas*i;
    end
end % define antennas positions

[numberOfSpatialSources, azimuthAngle, musicSpectrum] = reallocation(antennasPositions, globalParam.centralFrequency, ...
    signal, globalParam.classicalMusicSampleNum, globalParam.classicalMusicThreshold, globalParam.classicalMusicMode);

[classicalMusicEstimatedAngles, strongestPeaks] = findPeaksOnSpectrum(musicSpectrum, azimuthAngle);

for sourcesCheckPlotSavePrint = 1
    if numberOfSpatialSources == size(signal,1)
        disp('[ClassicalMusic]: spatial sources are not found')
        return
    end
    
    if globalParam.plotClassicalMusicSpectrum
        f = figure; plot(azimuthAngle,musicSpectrum), xlabel('Angle, degrees'), ylabel('Amplitude'), title('Pseudospectrum classical Music'),
        xlim([-100 100]), ylim([min(musicSpectrum)-2 max(musicSpectrum)+3]), xticks(-180:45:180);
        
        if globalParam.saveClassicalMusicSpectrum
            saveas(f, globalParam.directory+"classicalMusic.png");
        end
    end
    
    if globalParam.plotClassicalMusicPeaks
        f = figure; plot(azimuthAngle,strongestPeaks), xlabel('Angle, degrees'), ylabel('Amplitude'), title('Peaks classical Music'),
        xlim([-100 100]), ylim([min(strongestPeaks)-2 max(strongestPeaks)+3]), xticks(-180:45:180);
        
        if globalParam.saveClassicalMusicPeaks
            saveas(f, globalParam.directory+"peaksClassicalMusic.png");
        end
    end

    if globalParam.printClassicalMusicOutput
        classicalMusicEstimatedAngles
    end

end % sources check, plot, save, print
for measureExecutionTime = 1
    if globalParam.printClassicalMusicExecutionTime
        ClassicalMusicExecutionTime = toc
    end
end % measure execution time

end % ClassicalMusic

function [numberOfSpatialSources, azimuthAngle, musicSpectrum] = reallocation(antennasPositions, ...
    centralFrequency, signal, sampleNum, threshold, eigDecompositionMode)

for findingEigenVectors = 1
    Rxx=signal*signal'/sampleNum; % correlation matrix
    if eigDecompositionMode == 0 % old way, comparison with threshold
        [E, eigenValue]=eig(Rxx);
        eigen=diag(eigenValue);
        ne=[]; % for noise eigenvectors
        antennasNum=size(antennasPositions,1);
        for i=1:antennasNum
            if real(eigen(i))<threshold
                ne=[ne i]; % choose vector corresponding to the weakest eigenvalues
            end
        end
        numberOfSpatialSources=antennasNum-length(ne); % number of sources is equal to number of strong eigenvalues.
        En=E(:,ne);
    elseif eigDecompositionMode == 1
        [Utmp,eigenValue] = eig(Rxx);
        eigenValue = abs(eigenValue);
        [~,I] = sort(diag(eigenValue), 'ascend');
        U = Utmp(:,I);
        numberOfSpatialSources = 2; % Number of sources is fixed now
        En = U(:,1:numberOfSpatialSources);
    end
end % finding eigen vectors
for defineGrid = 1
    azimuthAngle = [-90:0.5:90] + 90; % vector of angle of arrivals with 0.5 deg resolution
    azimuthAngle = azimuthAngle'; % transpose
    elevationAngle = zeros(size(azimuthAngle)); % vector of zeros with the same size as az
end % define grid for music spectrum computation
for musicSpectrumComputation = 1
    steeringVectors = steeringVectorsCreate(antennasPositions, [azimuthAngle,elevationAngle], centralFrequency);
    musicSpectrum=zeros(1,length(azimuthAngle));
    for i=1:length(azimuthAngle)
        musicSpectrum(i)=-10*log10(abs(steeringVectors(:,i)'*(En*En')*steeringVectors(:,i)));
    end
    azimuthAngle = azimuthAngle-90;
end % music spectrum computation

end % reallocation

function steeringVectors = steeringVectorsCreate(antennasPositions, directionOfArrival, centralFrequency)

directionOfArrival=directionOfArrival*pi()/180.0; % Degree to radian conversion
azimuthAngle = directionOfArrival(:,1);
elevationAngle = directionOfArrival(:,2);
projection = [cos(azimuthAngle).*cos(elevationAngle)   sin(azimuthAngle).*cos(elevationAngle)   sin(elevationAngle)]';

waveNumberProjection = 2 * pi() * centralFrequency / physconst('LightSpeed') * projection;
steeringVectors = exp(-1j*(antennasPositions*waveNumberProjection));

end % steeringVectorsCreate

function [classicalMusicEstimatedAngles, strongestPeaks] = findPeaksOnSpectrum(musicSpectrum, azimuthAngle)
global globalParam;

switch globalParam.classicalMusicPeaksMode
    case 0
        [globalMaximumValue, indexOfGlobalMaximum] = max(musicSpectrum);
        classicalMusicEstimatedAngles = azimuthAngle(1) + (indexOfGlobalMaximum-1)*(azimuthAngle(2)-azimuthAngle(1));
        strongestPeaks = musicSpectrum .* (musicSpectrum == globalMaximumValue);
    case 1
        isPeak = imregionalmax(musicSpectrum);
        peakIndex = ind2sub(size(isPeak), find(isPeak));
        isStrongEnough = musicSpectrum(isPeak) > (globalParam.classicalMusicPeakThresholdRate * max(musicSpectrum(isPeak)));
        peakIndex = peakIndex(isStrongEnough);
        classicalMusicEstimatedAngles = azimuthAngle(1) + (peakIndex-1)*(azimuthAngle(2)-azimuthAngle(1));
        
        globalMaximumValue = max(musicSpectrum(isPeak));
        pointIsPeak = musicSpectrum & isPeak;
        eachPeakValue = pointIsPeak .*  musicSpectrum;
        isPeakMoreThenThreshold = eachPeakValue > (globalParam.classicalMusicPeakThresholdRate * globalMaximumValue);
        strongestPeaks = isPeakMoreThenThreshold .* musicSpectrum;
    case 2
        strongestPeaks = zeros(size(musicSpectrum));
        isPeak = imregionalmax(musicSpectrum);
        peakIndex = ind2sub(size(isPeak), find(isPeak));
        [~,topPeakIndices] = maxk(musicSpectrum(isPeak), min(globalParam.classicalMusicNumberOfPeaksToDetect, length(find(isPeak(:)))));
        peakIndex = peakIndex(topPeakIndices);
        classicalMusicEstimatedAngles = azimuthAngle(1) + (peakIndex-1)*(azimuthAngle(2)-azimuthAngle(1));
        
        for i = 1:length(peakIndex)
            strongestPeaks(peakIndex(i)) = musicSpectrum(peakIndex(i));
        end
end
end % findPeaksOnSpectrum