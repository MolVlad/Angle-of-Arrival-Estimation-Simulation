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
