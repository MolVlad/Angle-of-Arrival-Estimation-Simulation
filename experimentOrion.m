global globalParam;

CreateParams();

globalParam.fileForOrionResults = 'experiment/OrionResults.txt';

if ~isfile(globalParam.fileForOrionResults)
    fileID = fopen(globalParam.fileForOrionResults, 'w');
    fprintf(fileID,"ant\tseed\tSNR\tKfactor\trealAngle\testAngle\tstdAngle\terrorAngle"+...
        "\tnextAngle\tstdNextAngle\tpacketNum\tpacketPerSpec\tbandwidth\tdecimation\tsmoothing\tbackw\n");
    fclose(fileID);
end

saveOrionSpectrum = 0;
globalParam.OrionCsiSource = 0; % 0 - from csi.mat; 1 - from winner_csi/csi_?????
globalParam.OrionMeasurement = 1;
globalParam.plotOrionSpectrum = 0;

randomSeedForScenario = 1:10000;
numberOfAntennas = [8 4];
packetNum = [30 10];
packetPerSpectrum = [2 1];
bandwidth = [40 20];
subcarrierDecimationUsed = [0 1];
backwardSmoothingUsed = [1 0];
useSmothing = [1 0];

prod = length(randomSeedForScenario);
expNum = 0;

for r=randomSeedForScenario
    tic

    globalParam.seedForScenario = r;
    
    csi=sprintf('%d',int32(globalParam.seedForScenario)); seed_str = '00000'; seed_str(end+1-length(csi):end) = csi;
    matrixCSI = readfile("../music/experiment/winner_csi/csi_"+seed_str+".txt",28800);
    matrixCSI = reshape(matrixCSI, 120, 8, 30);
    save('data/matrixCSI.mat', 'matrixCSI');
    
    for OrionRun = 1
        if saveOrionSpectrum
            globalParam.plotOrionSpectrum = 1;
            globalParam.saveOrionSpectrum = 1;
            globalParam.closeOrionSpectrum = 1;
        else
            globalParam.plotOrionSpectrum = 0;
            globalParam.saveOrionSpectrum = 0;
            globalParam.closeOrionSpectrum = 0;
        end
        
        for ant=numberOfAntennas
            globalParam.numberOfAntennas = ant;
            for smoothing = useSmothing
                for band = bandwidth
                    for backw = backwardSmoothingUsed
                        for dec = subcarrierDecimationUsed
                            for perSpec = packetPerSpectrum
                                for p = packetNum
                                    globalParam.numberOfPacketsPerIteration = perSpec;
                                    globalParam.OrionNumberOfIterations = floor(p / perSpec);
                                    
                                    globalParam.OrionBackwardSmoothingUsed = backw;
                                    
                                    if smoothing
                                        switch ant
                                            case 8
                                                globalParam.OrionSubarrayNum = 3;
                                            case 4
                                                globalParam.OrionSubarrayNum = 2;
                                            otherwise
                                                error('smoothing')
                                        end
                                    else
                                        globalParam.OrionSubarrayNum = 1;
                                    end
                                    
                                    switch band
                                        case 20
                                            globalParam.subCarrIndEnd = 56;
                                            if dec
                                                globalParam.subCarrIndStep = 2;
                                            else
                                                globalParam.subCarrIndStep = 1;
                                            end
                                        case 40
                                            globalParam.subCarrIndEnd = 117;
                                            if dec
                                                globalParam.subCarrIndStep = 4;
                                            else
                                                globalParam.subCarrIndStep = 1;
                                            end
                                        otherwise
                                            error('band error');
                                    end
                                    
                                    Orion();
                                    fileID = fopen(globalParam.fileForOrionResults, 'a');
                                    fprintf(fileID, string(p)+"\t"+string(perSpec)+"\t"+string(band)+"\t"+string(dec)+"\t"+string(smoothing)+"\t"+string(backw)+"\n");
                                    fclose(fileID);
                                end
                            end
                        end
                    end
                end
            end
        end
    end % OrionRun

expNum = expNum + 1;
fprintf("%d/%d\n",expNum,prod);
toc
end
