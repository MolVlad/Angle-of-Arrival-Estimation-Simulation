clear all
close all

global globalParam;
global globalData;

CreateParams();

if globalParam.iterationWinnerMode == 0
    ScenarioWinner()
else
    SecondScenarioWinner()
end

for printInfo = 1
    if globalParam.printWinnerOutputMatrix
        nsDelayAnglePowerFromWinner = zeros(3, size(globalData.pathPower, 2));
        nsDelayAnglePowerFromWinner(1,:)=globalData.delays * 1e9;
        nsDelayAnglePowerFromWinner(2,:)=globalData.aoas(:,:,1);
        nsDelayAnglePowerFromWinner(3,:)=globalData.pathPower;
        
        nsDelayAnglePowerFromWinner = nsDelayAnglePowerFromWinner(:,~isnan(nsDelayAnglePowerFromWinner(1,:)));
        
        [~, order] = sort(nsDelayAnglePowerFromWinner(3,:), 'descend');
        nsDelayAnglePowerFromWinner = nsDelayAnglePowerFromWinner(:,order);
        
        nsDelayAnglePowerFromWinner = nsDelayAnglePowerFromWinner.'
    end
    
    if globalParam.printWinnerOutput
        phi = globalData.phi
        pathPower = globalData.pathPower
        nsDelays = globalData.delays * 1e9
        aoas = globalData.aoas
        Kfactor = globalData.Kfactor
        phiLOS = globalData.phiLOS
        LOSangle = globalData.LOSangle
        arrayRotationAngle = globalParam.WinnerArrayRotationAngle
    end
end

if globalParam.runClassicalMusic
    ClassicalMusic();
end

if globalParam.runOrion
	Orion();
end

if globalParam.runArraytrack
    Arraytrack();
end

if globalParam.runSpotfi
	Spotfi();
end