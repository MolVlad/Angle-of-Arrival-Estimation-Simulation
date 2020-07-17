algorithm = [0];  % 0 - spotfi; 1 - arraytrack; 2 - orion
randomSeedForScenario = [5];
numberOfAntennas = [4];
useSmothing = [0];
backwardSmoothingUsed = [0];
packetNum = [10];
packetPerSpectrum = [1];
bandwidth = [20];
subcarrierDecimationUsed = [0];

closePlots = 0;
closeSpectrums = 1;
plotSpotfiSpectrums = 1;

directory = "debug/";

global globalParam;
global globalData;

CreateParams();

globalParam.printResultingSpotfiOutput = 0;

% globalParam.SpotfiEigenMode = 1;
globalParam.SpotfiEigenMode = 1;
globalParam.SpotfiNumNoiseEigVector = -1; % if < 0 then num of strongest signal eigen vectors

for seed = randomSeedForScenario
    for ant = numberOfAntennas
        for p = packetNum
            for alg = algorithm
                tic
                
                globalParam.seedForScenario = seed;
                globalParam.seedForChannelEvolution = 1000 * seed;
                
                normStream = RandStream('v5normal','Seed',seed);
                globalParam.Kfactor = 10.^(0.1*(6*randn(normStream, 1, 1)+ 7));
                
                rng(seed);
                globalParam.SNR = rand*20;
                globalParam.AngleOfLOS = rand*180-90;
                
                fprintf("SNR: %.4f\tAngleLOS: %.4f\tKfactor: %.4f\n", globalParam.SNR, globalParam.AngleOfLOS, globalParam.Kfactor);
                
                switch alg
                    case 0  % spotfi
                        for smoothing = useSmothing
                            for backw = backwardSmoothingUsed
                                for band = bandwidth
                                    for dec = subcarrierDecimationUsed
                                        for perSpec = packetPerSpectrum
                                            globalParam.seedForScenario = seed;
                                            globalParam.csiSource = 4;

                                            globalParam.SpotfiMeasurement = 1;

                                            if plotSpotfiSpectrums
                                                globalParam.plotSpotfiSpectrum = 1;
                                            else
                                                globalParam.plotSpotfiSpectrum = 0;
                                            end
                                            globalParam.saveSpotfiSpectrum = 1;
                                            if closeSpectrums
                                                globalParam.closeSpotfiSpectrum = 1;
                                            else
                                                globalParam.closeSpotfiSpectrum = 0;
                                            end
                                            
                                            globalParam.buildClusters = 1;
                                            globalParam.plotClusters = 1;
                                            globalParam.saveClusters = 1;
                                            if closePlots
                                                globalParam.closeClusters = 1;
                                            else
                                                globalParam.closeClusters = 0;
                                            end                                            
                                            
                                            globalParam.numberOfAntennas = ant;
                                            
                                            globalParam.SpotfiBackwardSmoothingUsed = backw;
                                            globalParam.numberOfPacketsPerIteration = perSpec;
                                            globalParam.SpotfiNumberOfIterations = floor(p / perSpec);
                                            if smoothing
                                                switch ant
                                                    case 8
                                                        globalParam.SpotfiSubarrayNum = 3;
                                                    case 4
                                                        globalParam.SpotfiSubarrayNum = 2;
                                                    otherwise
                                                        error('smoothing')
                                                end
                                            else
                                                globalParam.numberOfAntennaInSubset = ant;
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
                                            
                                            directory = "debug/"+"r_"+string(seed)+"/ant_"+string(ant)+"/smoothing_"+string(smoothing)+ ...
                                                "/Spotfi/backw_"+string(backw)+"/packNum_"+string(p)+"/perSpec_"+string(perSpec)+"/bandwidth_"+ ...
                                                string(band)+"/dec_" + string(dec)+"/";
                                            
                                            [status, msg] = mkdir(directory);
                                            globalParam.directory = directory;
                                                
                                            Spotfi();
                                        end
                                    end
                                end
                            end
                        end
                        fprintf("Spotfi ");
                        toc
                    case 1  % arraytrack
                        for SetChannelParameters = 1
                            globalParam.numberOfAntennas = 8;
                            globalParam.WinnerNumberOfIterations = 30;
                            globalParam.iterationWinnerMode = 1;
                            globalParam.realisticScenario = 1;

                            directory = "debug/r_"+string(seed)+"/";
                            [status, msg] = mkdir(directory);
                            globalParam.directory = directory;
                            globalParam.seedForScenario = seed;
                            globalParam.seedForChannelEvolution = 1000 * seed;
                            
                            normStream = RandStream('v5normal','Seed',seed);
                            globalParam.Kfactor = 10.^(0.1*(6*randn(normStream, 1, 1)+ 7));
                            
                            rng(seed);
                            globalParam.SNR = rand*20;
                            globalParam.AngleOfLOS = rand*180-90;
                            
                            fileID = fopen(directory+'LOS_SNR_K.txt', 'w');
                            fprintf(fileID, "LOS angle: %.4f\tSNR: %.4f\tKfactor: %.4f\n", globalParam.AngleOfLOS, globalParam.SNR, globalParam.Kfactor);
                            fclose(fileID);
                            
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
                            
                            if globalParam.iterationWinnerMode == 0
                                ScenarioWinner()
                            else
                                SecondScenarioWinner()
                            end
                            
                            
                            nsDelayAnglePowerFromWinner = zeros(3, size(globalData.pathPower, 2));
                            nsDelayAnglePowerFromWinner(1,:)=globalData.delays * 1e9;
                            nsDelayAnglePowerFromWinner(2,:)=-globalData.aoas(:,:,1);
                            nsDelayAnglePowerFromWinner(3,:)=globalData.pathPower;
                            
                            nsDelayAnglePowerFromWinner = nsDelayAnglePowerFromWinner(:,~isnan(nsDelayAnglePowerFromWinner(1,:)));
                            
                            [~, order] = sort(nsDelayAnglePowerFromWinner(3,:), 'descend');
                            nsDelayAnglePowerFromWinner = nsDelayAnglePowerFromWinner(:,order);
                            
                            fileID = fopen(directory+'nsDelayAnglePowerFromWinner.txt', 'w');
                            fprintf(fileID, 'delay (ns)\tangle\tpower\n');
                            fclose(fileID);
                            
                            dlmwrite(directory+"nsDelayAnglePowerFromWinner.txt",nsDelayAnglePowerFromWinner', '-append', 'delimiter', '\t');
                            
                        end % SetChannelParameters
                        for smoothing = useSmothing
                            for backw = backwardSmoothingUsed
                                globalParam.numberOfAntennas = ant;
                                globalParam.ArraytrackMeasurement = 1;
                                globalParam.plotArraytrackSpectrum = 1;
                                globalParam.saveArraytrackSpectrum = 1;
                                if closePlots
                                    globalParam.closeArraytrackSpectrum = 1;
                                else
                                    globalParam.closeArraytrackSpectrum = 0;
                                end
                                directory = "debug/"+"r_"+string(seed)+"/ant_"+string(ant)+"/smoothing_"+string(smoothing)+ ...
                                    "/Arraytrack/backw_"+string(backw)+"/packNum_"+string(p)+"/";
                                [status, msg] = mkdir(directory);
                                globalParam.directory = directory;
                                
                                if smoothing
                                    switch ant
                                        case 8
                                            globalParam.ArraytrackSubarrayNum = 3;
                                        case 4
                                            globalParam.ArraytrackSubarrayNum = 2;
                                        otherwise
                                            error('smoothing')
                                    end
                                else
                                    globalParam.ArraytrackSubarrayNum = 1;
                                end
                                globalParam.ArraytrackBackwardSmoothingUsed = backw;
                                globalParam.ArraytrackUsedPacketNum = p;
                                Arraytrack();
                            end
                        end
                        fprintf("Arraytrack ");
                        toc
                    case 2  % Orion
                        for band = bandwidth
                            for dec = subcarrierDecimationUsed
                                for perSpec = packetPerSpectrum
                                    globalParam.OrionCsiSource = 1;
                                    globalParam.seedForScenario = seed;

                                    globalParam.plotOrionSpectrum = 1;
                                    globalParam.saveOrionSpectrum = 1;
                                    if closePlots
                                        globalParam.closeOrionSpectrum = 1;
                                    else
                                        globalParam.closeOrionSpectrum = 0;
                                    end
                                    globalParam.OrionMeasurement = 1;

                                    globalParam.numberOfAntennas = ant;
                                    
                                    globalParam.numberOfPacketsPerIteration = perSpec;
                                    globalParam.OrionNumberOfIterations = floor(p / perSpec);
                                    
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
                                    
                                    directory = "debug/"+"r_"+string(seed)+"/ant_"+string(ant)+"/smoothing_"+string(smoothing)+ ...
                                        "/Orion/packNum_"+string(p)+"/perSpec_"+string(perSpec)+"/bandwidth_"+ ...
                                        string(band)+"/dec_" + string(dec)+"/";
                                    
                                    [status, msg] = mkdir(directory);
                                    globalParam.directory = directory;
                                    
                                    Orion();

                                end
                            end
                        end
                        fprintf("Orion ");
                        toc
                    otherwise
                        error("alg")
                end
            end
        end
    end
end
