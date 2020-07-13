clear all
close all

global globalParam;
global globalData;

CreateParams();

randomSeedForScenario = 1:1;
Kfactor = [5 3 2 1 0.5 0.1 0.05];
AngleOfLOS = 30:-30:-30;
SNR = [5 4 3 2 1 0 -1 10 15];
% randomSeedForScenario = 1;
% Kfactor = [3];
% AngleOfLOS = [30 -30];
% SNR = [5 4 3 2 1 0 -1];

i = 0;
prod = length(randomSeedForScenario)*length(Kfactor)*length(AngleOfLOS)*length(SNR);

for r=randomSeedForScenario
    for s=SNR
        for k=Kfactor
            for a=AngleOfLOS
                tic
                directory = "experiment2/"+"k_"+string(k)+"_s_"+string(s)+"/a_"+string(a)+"/r_"+string(r)+"/";
                [status, msg] = mkdir(directory);
                
                if isempty(msg)
                    globalParam.directory = directory;
                    globalParam.Kfactor = k;
                    globalParam.SNR = s;
                    globalParam.randomSeedForScenario = r;
                    globalParam.awgnRndSeed = r;
                    
                    globalParam.AngleOfLOS = a;

                    globalParam.MSposition = [0 0 1.5].';
                    globalParam.BSposition = [0 0 1.5].';
                    
                    if globalParam.AngleOfLOS > 0
                        globalParam.MSposition(1) = 5;
                        globalParam.BSposition(2) = 5*tan(pi/2-pi/180*abs(globalParam.AngleOfLOS));
                    elseif globalParam.AngleOfLOS < 0
                        globalParam.BSposition(1) = 5;
                        globalParam.BSposition(2) = 5*tan(pi/2-pi/180*abs(globalParam.AngleOfLOS));
                    else
                        globalParam.BSposition(2) = 5;
                    end
                    
                    ScenarioWinner()
                                  
%                     fprintf("angle: %.2f vs %.2f\n", a, globalData.LOSangle);
%                     fprintf("kfactor: %.2f vs %.2f\n", k, globalData.Kfactor);
%                     fprintf("snr: %.2f vs %.2f\n", s, globalData.SNR);
%                     fprintf("seed: %.2f vs %.2f\n", r, globalParam.randomSeedForScenario);
                       
                    nsDelayAnglePowerFromWinner = zeros(3, size(globalData.pathPower, 2));
                    nsDelayAnglePowerFromWinner(1,:)=globalData.delays * 1e9;
                    nsDelayAnglePowerFromWinner(2,:)=-globalData.aoas(:,:,1);
                    nsDelayAnglePowerFromWinner(3,:)=globalData.pathPower;
                    
                    nsDelayAnglePowerFromWinner = nsDelayAnglePowerFromWinner(:,~isnan(nsDelayAnglePowerFromWinner(1,:)));

                    [~, order] = sort(nsDelayAnglePowerFromWinner(3,:), 'descend');
                    nsDelayAnglePowerFromWinner = nsDelayAnglePowerFromWinner(:,order);
                    dlmwrite(directory+"nsDelayAnglePowerFromWinner.txt",nsDelayAnglePowerFromWinner', '\t');
                    
                    Spotfi();
                end
                
                i = i + 1;
                fprintf("%d/%d\n",i,prod);
                toc
            end
        end
    end
end
