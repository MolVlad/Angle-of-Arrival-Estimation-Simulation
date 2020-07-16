global globalParam;
global globalData;

CreateParams();

mkdir('experiment');
mkdir('experiment/winner_csi');
globalParam.fileForArraytrackResults = 'experiment/ArraytrackResults.txt';
globalParam.fileForOrionResults = 'experiment/OrionResults.txt';

if ~isfile(globalParam.fileForArraytrackResults)
    fileID = fopen(globalParam.fileForArraytrackResults, 'w');
    fprintf(fileID,"ant\tsubArrNum\tseed\tSNR\tKfactor\trealAngle\testAngle\tstdAngle\terrorAngle\tnextAngle"+...
        "\tstdNextAngle\tbackwSmth\tpacketNum\n");
    fclose(fileID);
end

if ~isfile(globalParam.fileForOrionResults)
    fileID = fopen(globalParam.fileForOrionResults, 'w');
    fprintf(fileID,"ant\tseed\tSNR\tKfactor\trealAngle\testAngle\tstdAngle\terrorAngle"+...
        "\tnextAngle\tstdNextAngle\tpacketNum\tpacketPerSpec\tbandwidth\tdecimation\n");
    fclose(fileID);
end

% globalParam.fileForSpotfiResults = 'experiment/SpotfiResults.txt';
% 
% if ~isfile(globalParam.fileForSpotfiResults)
%     fileID = fopen(globalParam.fileForSpotfiResults, 'w');
%     fprintf(fileID,"ant\tsubArrNum\tseed\tSNR\tKfactor\trealAngle\testAngle\tstdAngle\tclusterSize\terrorAngle"+...
%         "\tnextAngle\tstdNextAngle\tnextClusterSize\tbackwSmth\tpacketNum\tpacketPerSpec\tbandwidth\tdecimation\n");
%     fclose(fileID);
% end

saveArraytrackSpectrum = 0;
saveSpotfiClusters = 0;
saveOrionSpectrum = 0;

globalParam.OrionMeasurement = 1;
globalParam.SpotfiMeasurement = 1;
globalParam.ArraytrackMeasurement = 1;

globalParam.plotSpotfiSpectrum = 0;
globalParam.buildClusters = 1;
globalParam.plotArraytrackSpectrum = 0;
globalParam.plotOrionSpectrum = 0;
globalParam.realisticScenario = 1;

randomSeedForScenario = 1:10000;
numberOfAntennas = [8 4];

globalParam.SpotfiNSDelayRange = 1*[-300 300];
globalParam.SpotfiAngleRange = 90*[-1 1];
globalParam.SpotfiNumberOfGridPoints = [globalParam.SpotfiNSDelayRange(2)*2+1 globalParam.SpotfiAngleRange(2)*20+1 1];

packetNum = [30 10];
packetPerSpectrum = [2 1];
globalParam.WinnerNumberOfIterations = max(packetNum);

bandwidth = [40 20];
subcarrierDecimationUsed = [0 1];
backwardSmoothingUsed = [1 0];
useSmothing = [1 0];

prod = length(randomSeedForScenario);
expNum = 0;

for r=randomSeedForScenario
    tic
    directory = "experiment/r_"+string(r)+"/";
    [status, msg] = mkdir(directory);
    
    globalParam.numberOfAntennas = 8;
    
    if isempty(msg)
        for SetChannelParameters = 1
            globalParam.directory = directory;
            globalParam.seedForScenario = r;
            globalParam.seedForChannelEvolution = 1000 * r;
            
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
        
        for ArraytrackRun = 1
            for ant=numberOfAntennas
                globalParam.numberOfAntennas = ant;
                for smoothing = useSmothing
                    for backw = backwardSmoothingUsed
                        if saveArraytrackSpectrum
                            globalParam.plotArraytrackSpectrum = 1;
                            globalParam.saveArraytrackSpectrum = 1;
                            globalParam.closeArraytrackSpectrum = 1;
                        else
                            globalParam.plotArraytrackSpectrum = 0;
                            globalParam.saveArraytrackSpectrum = 0;
                            globalParam.closeArraytrackSpectrum = 0;
                        end
                        
                        for p = packetNum
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
                            
                            directory = "experiment/"+"r_"+string(r)+"/ant_"+string(ant)+"/subArr_"+string(smoothing)+ ...
                                "/Arraytrack/backw_"+string(backw)+"/packNum_"+string(p)+"/";
                            
                            [status, msg] = mkdir(directory);
                            
                            if isempty(msg)
                                globalParam.directory = directory;
                                
                                Arraytrack();
                            end
                            
                            globalParam.plotArraytrackSpectrum = 0;
                        end
                    end
                end
            end
        end % ArraytrackRun
        
%         for SpotfiRun = 1
%             if saveSpotfiClusters
%                 globalParam.plotClusters = 1;
%                 globalParam.saveClusters = 1;
%                 globalParam.closeClusters = 1;
%             else
%                 globalParam.plotClusters = 0;
%                 globalParam.saveClusters = 0;
%                 globalParam.closeClusters = 0;
%             end
%             
%             for ant=numberOfAntennas
%                 globalParam.numberOfAntennas = ant;
%                 for smoothing = useSmothing
%                     for backw = backwardSmoothingUsed
%                         for band = bandwidth
%                             for dec = subcarrierDecimationUsed
%                                 for perSpec = packetPerSpectrum
%                                     for p = packetNum
%                                         globalParam.SpotfiBackwardSmoothingUsed = backw;
%                                         globalParam.numberOfPacketsPerIteration = perSpec;
%                                         globalParam.SpotfiNumberOfIterations = floor(p / perSpec);
%                                         if smoothing
%                                             switch ant
%                                                 case 8
%                                                     globalParam.SpotfiSubarrayNum = 3;
%                                                 case 4
%                                                     globalParam.SpotfiSubarrayNum = 2;
%                                                 otherwise
%                                                     error('smoothing')
%                                             end
%                                         else
%                                             globalParam.numberOfAntennaInSubset = ant;
%                                         end
%                                         
%                                         switch band
%                                             case 20
%                                                 globalParam.subCarrIndEnd = 56;
%                                                 if dec
%                                                     globalParam.subCarrIndStep = 2;
%                                                 else
%                                                     globalParam.subCarrIndStep = 1;
%                                                 end
%                                             case 40
%                                                 globalParam.subCarrIndEnd = 117;
%                                                 if dec
%                                                     globalParam.subCarrIndStep = 4;
%                                                 else
%                                                     globalParam.subCarrIndStep = 1;
%                                                 end
%                                             otherwise
%                                                 error('band error');
%                                         end
%                                         
%                                         directory = "experiment/"+"ant_"+string(ant)+"/r_"+string(r)+"/subArr_"+string(smoothing)+ ...
%                                             "/backw_"+string(backw)+"/packNum_"+string(p)+"/perSpec_"+string(perSpec)+"/bandwidth_"+ ...
%                                             string(band)+"/dec_" + string(dec)+"/";
%                                         
%                                         [status, msg] = mkdir(directory);
%                                         
%                                         if isempty(msg)
%                                             globalParam.directory = directory;
%                                             
%                                             Spotfi();
%                                             fileID = fopen(globalParam.fileForSpotfiResults, 'a');
%                                             fprintf(fileID, string(band)+"\t"+string(dec)+"\n");
%                                             fclose(fileID);
%                                         end
%                                     end
%                                     
%                                 end
%                             end
%                         end
%                     end
%                 end
%             end
%         end % SpotfiRun
        
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
                        for dec = subcarrierDecimationUsed
                            for perSpec = packetPerSpectrum
                                for p = packetNum
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
                                    
                                    directory = "experiment/"+"r_"+string(r)+"/ant_"+string(ant)+"/subArr_"+string(smoothing)+ ...
                                        "/Orion/packNum_"+string(p)+"/perSpec_"+string(perSpec)+"/bandwidth_"+ ...
                                        string(band)+"/dec_" + string(dec)+"/";
                                    
                                    [status, msg] = mkdir(directory); 
                                    
                                    if isempty(msg)
                                        globalParam.directory = directory;
                                        
                                        Orion();
                                        fileID = fopen(globalParam.fileForOrionResults, 'a');
                                        fprintf(fileID, string(band)+"\t"+string(dec)+"\n");
                                        fclose(fileID);
                                    end
                                end
                            end
                        end
                    end
                end
            end
        end % OrionRun
    end
    
    expNum = expNum + 1;
    fprintf("%d/%d\n",expNum,prod);
    toc
end
