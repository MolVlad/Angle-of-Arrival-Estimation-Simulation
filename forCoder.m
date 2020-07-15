function forCoder(seed) %#codegen

numberOfGridPoints = [601 181 1]; % ЗДЕСЬ НУЖНО ЗАМЕНИТЬ 181 на 1801 и 61 на 601 !!!!!
spotfi_dir = "./";
winner_dir = "./";

s=sprintf('%d',int32(seed)); seed_str = '00000'; seed_str(end+1-length(s):end) = s;
subdir = "music_"+seed_str;
f = fopen(subdir, 'w');
fprintf(f,"lol\n");

filename = winner_dir+"csi_" + seed_str + ".txt";
f = fopen(filename, 'r');
fseek(f, 0, 'eof');
filelen = int32(ftell(f));
fseek(f,0,'bof');
maxBufferSize = int32(2^21);
buffer = zeros(1, maxBufferSize,'uint8');
remaining = filelen;
index = int32(1);

while remaining > 0
    if remaining + index > size(buffer,2)
        fprintf('Attempt to read file which is bigger than internal buffer.\n');
        fprintf('Current buffer size is %d bytes and file size is %d bytes.\n', maxBufferSize, filelen);
        break
    end
    
    [dataRead, nread] = fread(f,remaining, 'char');
    buffer(index:index+nread-1) = dataRead;
    n = int32(nread);
    if n == 0
        break;
    end
    % Did something went wrong when reading?
    if n < 0
        fprintf('Could not read from file: %d.\n', n);
        break;
    end
    % Update state variables
    remaining = remaining - n;
    index = index + n;
end

% Close file
fclose(f);

str = (char(buffer(1:index)));
str = str(1:index-1);

num = 28800;
y = complex(zeros(1,num));

k = 1;
for i = 1:num
    j = k;
    while str(j) ~= ' '
        j = j + 1;
    end
    y(i) = str2double(str(k:j-1));
    k = j + 1;
end

sourceMatrixCSI = reshape(y,120,8,30);

% reading completed

packetNum = [30 10];
packetPerSpectrum = [2 1];
antennasNum = [8 4];
bandwidth = [20];
subcarrierDecimationUsed = [0 1];
backwardSmoothing = [1 0];
useSmothing = [1 0];

% packetNum = [10];
% packetPerSpectrum = [1];
% antennasNum = [4];
% bandwidth = [20];
% subcarrierDecimationUsed = [1];
% backwardSmoothing = [0];
% useSmothing = [0];

for ant = antennasNum
    for p = packetNum
        for perSpec = packetPerSpectrum
            for band = bandwidth
                for dec = subcarrierDecimationUsed
                    for smoothing = useSmothing
                        for backw = backwardSmoothing
                            switch band
                                case 20
                                    subCarrIndEnd = 56;
                                    if dec
                                        subCarrIndStep = 2;
                                    else
                                        subCarrIndStep = 1;
                                    end
                                case 40
                                    subCarrIndEnd = 117;
                                    if dec
                                        subCarrIndStep = 4;
                                    else
                                        subCarrIndStep = 1;
                                    end
                                otherwise
                                    error('band error');
                            end
                            subCarrInd = 1:subCarrIndStep:subCarrIndEnd;
                            numberOfSubcarr = length(subCarrInd);

                            numberOfAntennas = ant;
                            numberOfPacketsPerIteration = perSpec;
                            numberOfSpectrums = floor(p / perSpec);
                            backwardSmoothingUsed = backw;
                            
                            if smoothing
                                switch ant
                                    case 8
                                        subarrayNum = 3;
                                    case 4
                                        subarrayNum = 2;
                                    otherwise
                                        error('smoothing')
                                end
                            else
                                subarrayNum = 1;
                            end
                            numberOfAntennaInSubset = numberOfAntennas - subarrayNum + 1;
                            numberOfSubcarrierSubsets = floor(numberOfSubcarr/2); % number fo subset of subcarriers chosen for smoothing music
                            
                            matrixCSI = sourceMatrixCSI(subCarrInd, 1:numberOfAntennas,1:numberOfSpectrums*numberOfPacketsPerIteration);
                            smoothedMatrixCSI = reshape(matrixCSI, numberOfSubcarr, numberOfAntennas, numberOfSpectrums*numberOfPacketsPerIteration);
                            
                            if backwardSmoothingUsed
                                columnsNum = (numberOfAntennas - numberOfAntennaInSubset + 1)*(numberOfSubcarr - numberOfSubcarrierSubsets + 1);
                                matrixCSI=complex(zeros(numberOfAntennaInSubset * numberOfSubcarrierSubsets, columnsNum*2*numberOfPacketsPerIteration, numberOfSpectrums));
                                for t = 1:numberOfSpectrums
                                    for s = 1:numberOfPacketsPerIteration
                                        csiFromEachPacket = smoothedMatrixCSI(:,:,(t-1)*numberOfPacketsPerIteration+s);
                                        D = complex(zeros(numberOfSubcarrierSubsets, numberOfSubcarr-numberOfSubcarrierSubsets+1, numberOfAntennas));
                                        for m=1:numberOfAntennas % mth antenna
                                            D(:,:,m) = hankel(csiFromEachPacket(1:numberOfSubcarrierSubsets,m),csiFromEachPacket(numberOfSubcarrierSubsets:numberOfSubcarr, m));
                                        end
                                        De = complex(zeros(numberOfAntennaInSubset * numberOfSubcarrierSubsets, columnsNum));
                                        for start_idx = 1:numberOfAntennaInSubset
                                            tmp = complex(zeros(numberOfSubcarrierSubsets,(numberOfAntennas-numberOfAntennaInSubset+1)*(numberOfSubcarr-numberOfSubcarrierSubsets+1)));
                                            for j = 1:numberOfAntennas-numberOfAntennaInSubset+1
                                                tmp(:,(j-1)*(numberOfSubcarr-numberOfSubcarrierSubsets+1)+1:j*(numberOfSubcarr-numberOfSubcarrierSubsets+1)) = D(:,:,start_idx+j-1);
                                            end
                                            De((start_idx-1)*numberOfSubcarrierSubsets+(1:numberOfSubcarrierSubsets),:) = tmp;
                                        end
                                        matrixCSI(:,(s-1)*columnsNum*2+1:s*columnsNum*2-columnsNum,t) = De;
                                    end
                                end
                                
                                conjCsiTracePerPacket = conj(smoothedMatrixCSI(size(smoothedMatrixCSI,1):-1:1,size(smoothedMatrixCSI,2):-1:1,:));
                                
                                for t = 1:numberOfSpectrums
                                    for s = 1:numberOfPacketsPerIteration
                                        csiFromEachPacket = conjCsiTracePerPacket(:,:,(t-1)*numberOfPacketsPerIteration+s);
                                        D = complex(zeros(numberOfSubcarrierSubsets, numberOfSubcarr-numberOfSubcarrierSubsets+1, numberOfAntennas));
                                        for m=1:numberOfAntennas % mth antenna
                                            D(:,:,m) = hankel(csiFromEachPacket(1:numberOfSubcarrierSubsets,m),csiFromEachPacket(numberOfSubcarrierSubsets:numberOfSubcarr, m));
                                        end
                                        De = complex(zeros(numberOfAntennaInSubset * numberOfSubcarrierSubsets, (numberOfAntennas - numberOfAntennaInSubset + 1)*(numberOfSubcarr - numberOfSubcarrierSubsets + 1)));
                                        for start_idx = 1:numberOfAntennaInSubset
                                            tmp = complex(zeros(numberOfSubcarrierSubsets,(numberOfAntennas-numberOfAntennaInSubset+1)*(numberOfSubcarr-numberOfSubcarrierSubsets+1)));
                                            for j = 1:numberOfAntennas-numberOfAntennaInSubset+1
                                                tmp(:,(j-1)*(numberOfSubcarr-numberOfSubcarrierSubsets+1)+1:j*(numberOfSubcarr-numberOfSubcarrierSubsets+1)) = D(:,:,start_idx+j-1);
                                            end
                                            De((start_idx-1)*numberOfSubcarrierSubsets+(1:numberOfSubcarrierSubsets),:) = tmp;
                                        end
                                        matrixCSI(:,(s-1)*columnsNum*2+columnsNum+1:s*columnsNum*2,t) = De;
                                    end
                                end
                            else
                                columnsNum = (numberOfAntennas - numberOfAntennaInSubset + 1)*(numberOfSubcarr - numberOfSubcarrierSubsets + 1);
                                matrixCSI=complex(zeros(numberOfAntennaInSubset * numberOfSubcarrierSubsets, columnsNum*numberOfPacketsPerIteration, numberOfSpectrums));
                                for t = 1:numberOfSpectrums
                                    for s = 1:numberOfPacketsPerIteration
                                        csiFromEachPacket = smoothedMatrixCSI(:,:,(t-1)*numberOfPacketsPerIteration+s);
                                        D = complex(zeros(numberOfSubcarrierSubsets, numberOfSubcarr-numberOfSubcarrierSubsets+1, numberOfAntennas));
                                        for m=1:numberOfAntennas % mth antenna
                                            D(:,:,m) = hankel(csiFromEachPacket(1:numberOfSubcarrierSubsets,m),csiFromEachPacket(numberOfSubcarrierSubsets:numberOfSubcarr, m));
                                        end
                                        De = complex(zeros(numberOfAntennaInSubset * numberOfSubcarrierSubsets, columnsNum));
                                        for start_idx = 1:numberOfAntennaInSubset
                                            tmp = complex(zeros(numberOfSubcarrierSubsets,(numberOfAntennas-numberOfAntennaInSubset+1)*(numberOfSubcarr-numberOfSubcarrierSubsets+1)));
                                            for j = 1:numberOfAntennas-numberOfAntennaInSubset+1
                                                tmp(:,(j-1)*(numberOfSubcarr-numberOfSubcarrierSubsets+1)+1:j*(numberOfSubcarr-numberOfSubcarrierSubsets+1)) = D(:,:,start_idx+j-1);
                                            end
                                            De((start_idx-1)*numberOfSubcarrierSubsets+(1:numberOfSubcarrierSubsets),:) = tmp;
                                        end
                                        matrixCSI(:,(s-1)*columnsNum+1:s*columnsNum,t) = De;
                                    end
                                end
                            end
                            
                            % smoothing completed
                            
                            GridStart = [-300*1e-9 -90 0];
                            GridStop = [300*1e-9 90 0];
                            GridSpacing = (GridStop-GridStart)./max(1, numberOfGridPoints-ones(size(numberOfGridPoints)));
                            
                            delayConsider = GridStart(1) + (0:numberOfGridPoints(1)-1)*GridSpacing(1);
                            u_sConsider = 0.5 * sind(GridStart(2) + (0:numberOfGridPoints(2)-1)*GridSpacing(2) );
                            
                            delaySteering = exp(-1i*2*pi*(subCarrInd(1:numberOfSubcarrierSubsets).')*312500*delayConsider);
                            aoaSteering = exp(-1i*2*pi*(((numberOfAntennaInSubset-1)/2:-1:-(numberOfAntennaInSubset-1)/2)')*u_sConsider);
                            steeringVector = kron(aoaSteering, delaySteering);
                            
                            nsDelayAngleSpotfiEstimated = [];
                            for t = 1:numberOfSpectrums
                                
                                mat = matrixCSI(:,:,t);
                                Rxx = mat*mat';
                                
                                [Utmp,D] = eig(Rxx);
                                d = diag(abs(D));
                                [~,I] = sort(d, 'ascend');
                                U = Utmp(:,I);
                                d = d(I);
                                
                                numberOfSourses = 0;
                                for i = 1:size(d,1)
                                    if d(i) < 1
                                        numberOfSourses = i;
                                    end
                                end
                                if numberOfSourses == 0
                                    error('Spotfi: sources not found')
                                end
                                
                                % eig completed
                                
                                Qn = U(:,1:numberOfSourses);
                                Pn = (Qn*Qn');
                                
                                % Pn completed
                                
                                SpotfiSpectrum = sum((steeringVector').*((Pn*steeringVector).'),2);
                                SpotfiSpectrum = 1./abs(SpotfiSpectrum);
                                SpotfiSpectrum = SpotfiSpectrum - min(SpotfiSpectrum);
                                
                                % spotfi completed
                                
                                SpotfiSpectrum = reshape(SpotfiSpectrum,numberOfGridPoints(1),numberOfGridPoints(2),numberOfGridPoints(3));
                                isPeak = imregionalmax(SpotfiSpectrum);
                                [delay_idx, angle_idx] = ind2sub(size(isPeak), find(isPeak));
                                isStrongEnough = SpotfiSpectrum(isPeak) > (0.1 * max(SpotfiSpectrum(isPeak)));
                                delay_idx = delay_idx(isStrongEnough);
                                angle_idx = angle_idx(isStrongEnough);
                                
                                delayFromMusic = GridStart(1) + (delay_idx-1)*GridSpacing(1);
                                angleFromMusic = GridStart(2) + (angle_idx-1)*GridSpacing(2);
                                newEstimation = [delayFromMusic*1e9 angleFromMusic].';
                                newEstimation = newEstimation(:,newEstimation(2,:)>-89 & newEstimation(2,:)<89);
                                nsDelayAngleSpotfiEstimated = [nsDelayAngleSpotfiEstimated newEstimation];
                                
                                % peaks completed
                                
%                                 fileID = fopen(directory+"SpotfiEigen" + seed_str + ".txt", 'a');
%                                 fprintf(fileID, "noise: ");
%                                 for i = 1:numberOfSourses
%                                     fprintf(fileID, "%.3f ", d(i));
%                                 end
%                                 fprintf(fileID, "signal: ");
%                                 for i = numberOfSourses+1:length(d)
%                                     fprintf(fileID, "%.3f ", d(i));
%                                 end
%                                 fprintf(fileID, "\n");
%                                 fclose(fileID);
                            end
                            
                            name = "r_"+seed_str+"_ant_"+string(ant)+"_sm_"+string(smoothing)+"_backw_"+string(backw)+"_pack_"+string(p)+"_perSp_"+...
                                string(perSpec)+"_bw_"+string(band)+"_dec_" + string(dec) + ".txt";
                            
                            fileID = fopen(spotfi_dir+subdir+"/"+name, 'w');
                            for k = 1:size(nsDelayAngleSpotfiEstimated,3)
                                for j = 1:size(nsDelayAngleSpotfiEstimated,2)
                                    for i = 1:size(nsDelayAngleSpotfiEstimated,1)
                                        fprintf(fileID, "%.1f ", nsDelayAngleSpotfiEstimated(i,j,k));
                                    end
                                end
                            end
                            fclose(fileID);
                        end
                    end
                end
            end
        end
    end
end


end % Spotfi


