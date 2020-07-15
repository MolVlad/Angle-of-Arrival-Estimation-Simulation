algorithm = [0];  % 0 - spotfi; 1 - arraytrack; 2 - orion
randomSeedForScenario = [1];
numberOfAntennas = [8];
useSmothing = [1];
backwardSmoothingUsed = [1];
packetNum = [30];
bandwidth = [40];
subcarrierDecimationUsed = [0];
packetPerSpectrum = [1];

directory = "debug/";

global globalParam;

for seed = randomSeedForScenario
    for ant = numberOfAntennas
        for p = packetNum
            for alg = algorithm
                switch alg
                    case 0  % spotfi
                        for smoothing = useSmothing
                            for backw = backwardSmoothingUsed
                                for band = bandwidth
                                    for dec = subcarrierDecimationUsed
                                        for perSpec = packetPerSpectrum
                                            
                                        end
                                    end
                                end
                            end
                        end
                    case 1  % arraytrack
                        for smoothing = useSmothing
                            for backw = backwardSmoothingUsed
                                for SetChannelParameters = 1
                                    CreateParams();
                                    globalParam.directory = directory+"winner/";
                                    globalParam.seedForScenario = seed;
                                    globalParam.seedForChannelEvolution = 1000 * seed;
                                    
                                    normStream = RandStream('v5normal','Seed',r);
                                    globalParam.Kfactor = 10.^(0.1*(6*randn(normStream, 1, 1)+ 7));
                                    
                                    rng(r);
                                    globalParam.SNR = rand*20;
                                    globalParam.AngleOfLOS = rand*180-90;
                                    
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

        
                            end
                        end
                    case 2  % orion
                        for band = bandwidth
                            for dec = subcarrierDecimationUsed
                                for perSpec = packetPerSpectrum
                                    
                                end
                            end
                        end
                    otherwise
                        error("alg")
                end
            end
        end
    end
end
