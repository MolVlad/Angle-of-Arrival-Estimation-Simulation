function Orion()

global globalParam;

for readCSIfromFile = 1
    subCarrInd = globalParam.subCarrIndStart:globalParam.subCarrIndStep:globalParam.subCarrIndEnd;

    switch globalParam.OrionCsiSource
        case 0
            file = load('data/matrixCSI');
            matrixCSI = file.matrixCSI;
            matrixCSI = matrixCSI(subCarrInd,1:globalParam.numberOfAntennas,:);
        case 1
            csi=sprintf('%d',int32(globalParam.seedForScenario)); seed_str = '00000'; seed_str(end+1-length(csi):end) = csi;
            matrixCSI = readfile("../music/experiment/winner_csi/csi_"+seed_str+".txt",28800);
            matrixCSI = reshape(matrixCSI, 120, 8, 30);
            matrixCSI = matrixCSI(subCarrInd,1:globalParam.numberOfAntennas,:);
    end
    
end % read CSI from file

for mainPartOfComputingSpotfi = 1
    sanitizedVectorCSI = sanitizeCSI(matrixCSI, subCarrInd);

    sanitizedVectorCSI = permute(sanitizedVectorCSI, [2 1 3]);
    
    if globalParam.OrionBackwardSmoothingUsed
        sanitizedVectorCSI = [sanitizedVectorCSI conj(sanitizedVectorCSI(size(sanitizedVectorCSI,1):-1:1,:,:))];
    end
    
    L = size(sanitizedVectorCSI, 1) - globalParam.OrionSubarrayNum + 1;
    Rxx = zeros(L, L, globalParam.OrionNumberOfIterations);
    for j = 1:globalParam.OrionNumberOfIterations
        for i = 1:globalParam.numberOfPacketsPerIteration
            csi = sanitizedVectorCSI(:,:,i+(j-1)*globalParam.numberOfPacketsPerIteration);
            
            for i = 1:globalParam.OrionSubarrayNum
                s = csi(i:i+L-1,:);
                rxx(:,:,i)=s*s';
            end
            rxx = sum(rxx,3) / globalParam.OrionSubarrayNum;
    
            Rxx(:,:,j) = Rxx(:,:,j) + rxx; % correlation matrix
        end
    end
    
    Rxx = Rxx / globalParam.numberOfPacketsPerIteration;
    
    for j = 1:globalParam.OrionNumberOfIterations
        if globalParam.OrionMode == 0 % old way, comparison with threshold
            [Utmp, eigenValue]=eig(Rxx(:,:,j));
            eigenValue=diag(eigenValue);
            ne=[]; % for noise eigenvectors
            for i=1:length(eigenValue)
                if real(eigenValue(i)) < globalParam.OrionThreshold
                    ne=[ne i]; % choose vector corresponding to the weakest eigenvalues
                end
            end
            
            if ~isempty(ne)
                En{j}=Utmp(:,ne);
            else
                numberOfSpatialSources = 1;
                [~,I] = sort(eigenValue, 'ascend');
                U = Utmp(:,I);
                En{j} = U(:,1:numberOfSpatialSources);
            end
            
%             if globalParam.OrionMeasurement
%                 d = sort(eigenValue);
%                 N = length(ne);
%                 
%                 str = "noise:";
%                 for i = 1:N
%                     str = str + " " + string(round(d(i)*1000)/1000);
%                 end
%                 str = str + " signal:";
%                 for i = N+1:length(d)
%                     str = str + " " + string(round(d(i)*1000)/1000);
%                 end
%                 str = str + "\n";
%                 fileID = fopen(globalParam.directory+"OrionEigen.txt", 'a');
%                 fprintf(fileID, str);
%                 fclose(fileID);
%             end
        elseif globalParam.OrionMode == 1
            [Utmp,eigenValue] = eig(Rxx(:,:,j));
            eigenValue = diag(eigenValue);
            [~,I] = sort(eigenValue, 'ascend');
            U = Utmp(:,I);
            numberOfSpatialSources = 2; % Number of sources is fixed now
            En{j} = U(:,1:numberOfSpatialSources);
        end
    end
    
    antennasPositions = zeros(globalParam.numberOfAntennas - globalParam.OrionSubarrayNum + 1,3);
    for i=1:size(antennasPositions,1)
        antennasPositions(i,1)=globalParam.separationBetweenAntennas*i;
    end
    
    azimuthAngle = [-90:0.1:90] + 90; % vector of angle of arrivals with 0.5 deg resolution
    azimuthAngle = azimuthAngle'; % transpose
    elevationAngle = zeros(size(azimuthAngle)); % vector of zeros with the same size as az
    
    steeringVectors = steeringVectorsCreate(antennasPositions, [azimuthAngle,elevationAngle], globalParam.centralFrequency);
    musicSpectrum = zeros(length(azimuthAngle), globalParam.OrionNumberOfIterations);
    strongestPeaks = zeros(length(azimuthAngle), globalParam.OrionNumberOfIterations);

    for j = 1:globalParam.OrionNumberOfIterations
        for i=1:length(azimuthAngle)
            musicSpectrum(i,j)=-10*log10(abs(steeringVectors(:,i)'*(En{j}*En{j}')*steeringVectors(:,i)));
        end
        musicSpectrum(:,j) = musicSpectrum(:,j) - min(musicSpectrum(:,j));
        [angles, strongestPeaks(:,j)] = findPeaksOnSpectrum(musicSpectrum(:,j), azimuthAngle);
        angles = angles - 90;
        OrionEstimatedAngles{j} = angles(angles < 89.5 & angles > -89.5);
    end
    azimuthAngle = azimuthAngle-90;
    
    OrionStableStdMean = findstable(OrionEstimatedAngles);
    if globalParam.printOrionStablePeaks
        OrionStableStdMean = OrionStableStdMean
    end
    
    if globalParam.OrionMeasurement
%         for i = 1:length(OrionEstimatedAngles)
%             dlmwrite(globalParam.directory+"OrionEstimatedAngles.txt", OrionEstimatedAngles{i}', '-append', 'delimiter', '\t');
%         end
        
%         fileID = fopen(globalParam.directory+'OrionStableStdMean.txt', 'w');
%         fprintf(fileID, 'std\tangle\n');
%         fclose(fileID);
%         dlmwrite(globalParam.directory+"OrionStableStdMean.txt", OrionStableStdMean, '-append', 'delimiter', '\t');
        
        if size(OrionStableStdMean,1) < 2
            OrionStableStdMean(2,:) = [999 999];
        end
        fileID = fopen(globalParam.fileForOrionResults, 'a');
        fprintf(fileID, string(globalParam.numberOfAntennas)+ ...
            "\t"+string(globalParam.seedForScenario)+"\t"+string(globalParam.SNR)+"\t"+string(globalParam.Kfactor)+ ...
            "\t"+string(globalParam.AngleOfLOS)+"\t"+string(OrionStableStdMean(1,2))+"\t"+string(OrionStableStdMean(1,1))+ ...
            "\t"+string(abs(OrionStableStdMean(1,2)-globalParam.AngleOfLOS))+"\t"+string(OrionStableStdMean(2,2))+ ...
            "\t"+string(OrionStableStdMean(2,1))+"\t");
        fclose(fileID);
    end
    
    if globalParam.plotOrionSpectrum
        f = figure; plot(azimuthAngle,musicSpectrum), xlabel('Angle, degrees'), ylabel('Amplitude');
        title("Pseudospectrum Orion, stable: " + string(OrionStableStdMean(1,2)));
        xlim([-100 100]), ylim([min(musicSpectrum, [], 'all')-2 max(musicSpectrum, [], 'all')+3]), xticks(-180:45:180);
        
        if globalParam.saveOrionSpectrum
            saveas(f, globalParam.directory+"Orion.png");
        end
        if globalParam.closeOrionSpectrum
            close
        end
    end
    
    if globalParam.plotOrionPeaks
        f = figure; plot(azimuthAngle,strongestPeaks), xlabel('Angle, degrees'), ylabel('Amplitude'), title('Peaks Arraytrack'),
        xlim([-100 100]), ylim([min(strongestPeaks, [], 'all')-2 max(strongestPeaks, [], 'all')+3]), xticks(-180:45:180);
        
        if globalParam.saveArraytrackPeaks
            saveas(f, globalParam.directory+"peaksOrion.png");
        end
    end
    
    if globalParam.printOrionOutput
        for it = 1:length(OrionEstimatedAngles)
            OrionEstimatedAngles{it}
        end
    end
end

end

function sanitizedVectorCSI = sanitizeCSI(vectorCSI, subCarrInd)

global globalParam;

sanitizedVectorCSI = zeros(size(vectorCSI));
numberOfAntennas = globalParam.numberOfAntennas;
for packetIteration=1:globalParam.OrionNumberOfIterations*globalParam.numberOfPacketsPerIteration
    reshapedCSI = reshape(vectorCSI(:,:,packetIteration), length(subCarrInd), numberOfAntennas);
    
    [PhaseSlope, PhaseConstant] = removePhsSlope(reshapedCSI, subCarrInd);
    if globalParam.usePhaseCompensation
        phaseCompensation = exp(1i*(-PhaseSlope*repmat(subCarrInd(:),1, numberOfAntennas) ...
            - PhaseConstant*ones(length(subCarrInd), numberOfAntennas)));
        reshapedCSI = reshapedCSI .* phaseCompensation;
    end
    sanitizedVectorCSI(:,:,packetIteration) = reshapedCSI;
end

if globalParam.plotSanitizedCSI == 1
    figure, plot(abs(sanitizedVectorCSI(:,:,1))), title('Sanitized CSI')
end

end

function [PhaseSlope, PhaseConstant] = removePhsSlope(reshapedCSI, subCarrInd)

global globalParam;

PhaseRelatedToFirstPacket = unwrap(angle(reshapedCSI));

for antIdForPhs = 1:globalParam.numberOfAntennas
    if  PhaseRelatedToFirstPacket(1,antIdForPhs) - PhaseRelatedToFirstPacket(1,1) > pi
        PhaseRelatedToFirstPacket(:,antIdForPhs) = PhaseRelatedToFirstPacket(:,antIdForPhs) - 2*pi;
    elseif PhaseRelatedToFirstPacket(1,antIdForPhs) - PhaseRelatedToFirstPacket(1,1) < -pi
        PhaseRelatedToFirstPacket(:,antIdForPhs) = PhaseRelatedToFirstPacket(:,antIdForPhs) + 2*pi;
    end
end
A = [repmat(subCarrInd(:), globalParam.numberOfAntennas, 1) ones(length(subCarrInd)*globalParam.numberOfAntennas, 1)];
x = A\PhaseRelatedToFirstPacket(:);
PhaseSlope = x(1);
PhaseConstant = x(2);

end % removePhsSlope

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

switch globalParam.OrionPeaksMode
    case 0
        [globalMaximumValue, indexOfGlobalMaximum] = max(musicSpectrum);
        ArraytrackEstimatedAngles = azimuthAngle(1) + (indexOfGlobalMaximum-1)*(azimuthAngle(2)-azimuthAngle(1));
        strongestPeaks = musicSpectrum .* (musicSpectrum == globalMaximumValue);
    case 1
        isPeak = imregionalmax(musicSpectrum);
        peakIndex = ind2sub(size(isPeak), find(isPeak));
        isStrongEnough = musicSpectrum(isPeak) > (globalParam.OrionThresholdRate * max(musicSpectrum(isPeak)));
        peakIndex = peakIndex(isStrongEnough);
        ArraytrackEstimatedAngles = azimuthAngle(1) + (peakIndex-1)*(azimuthAngle(2)-azimuthAngle(1));
        
        globalMaximumValue = max(musicSpectrum(isPeak));
        pointIsPeak = musicSpectrum & isPeak;
        eachPeakValue = pointIsPeak .*  musicSpectrum;
        isPeakMoreThenThreshold = eachPeakValue > (globalParam.OrionThresholdRate * globalMaximumValue);
        strongestPeaks = isPeakMoreThenThreshold .* musicSpectrum;
    case 2
        strongestPeaks = zeros(size(musicSpectrum));
        isPeak = imregionalmax(musicSpectrum);
        peakIndex = ind2sub(size(isPeak), find(isPeak));
        [~,topPeakIndices] = maxk(musicSpectrum(isPeak), min(globalParam.OrionNumberOfPeaksToDetect, length(find(isPeak(:)))));
        peakIndex = peakIndex(topPeakIndices);
        ArraytrackEstimatedAngles = azimuthAngle(1) + (peakIndex-1)*(azimuthAngle(2)-azimuthAngle(1));
        
        for i = 1:length(peakIndex)
            strongestPeaks(peakIndex(i)) = musicSpectrum(peakIndex(i));
        end
end
end % findPeaksOnSpectrum