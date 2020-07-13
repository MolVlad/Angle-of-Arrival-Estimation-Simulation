tic

nsDelayAngleSpotfiEstimated=load('experiment_spotfi/r_00005_ant_8_sm_1_backw_1_pack_30_perSp_2_bw_40_dec_0.txt');
nsDelayAngleSpotfiEstimated=reshape(nsDelayAngleSpotfiEstimated,2,[]);
% nsDelayAngleSpotfiEstimated

clusterNumber = 10;

global globalParam;

delayMax = globalParam.SpotfiNSDelayRange(2);
angleMax = globalParam.SpotfiAngleRange(2);

Y = nsDelayAngleSpotfiEstimated(1:2,:)';
X(:,1) = Y(:,2) / angleMax;
X(:,2) = Y(:,1) / delayMax;

rng(3);
options = statset('MaxIter',3000);

threshold = sqrt(chi2inv(0.99,2));

if size(X,1) <= clusterNumber
    clusterNumber = size(X,1) - 1;
end

gmfit = fitgmdist(X,clusterNumber,'CovarianceType','diagonal', ...
    'SharedCovariance', false, 'RegularizationValue',0.0001, 'Options',options); % Fitted GMM
clusterX = cluster(gmfit,X); % Cluster index

clSize = zeros(clusterNumber, 1);
stdA = zeros(clusterNumber, 1);
stdD = zeros(clusterNumber, 1);
meanA = zeros(clusterNumber, 1);
meanD = zeros(clusterNumber, 1);
for l=1:clusterNumber
    clSize(l) = sum(clusterX == l);
    stdA(l) = round(std(X(clusterX == l, 1))*angleMax*1000)/1000;
    stdD(l) = round(std(X(clusterX == l, 2))*delayMax*1000)/1000;
    meanA(l) = round(mean(X(clusterX == l, 1))*angleMax*1000)/1000;
    meanD(l) = round(mean(X(clusterX == l, 2))*delayMax*1000)/1000;
end

if globalParam.SpotfiMeasurement
    T=table(clSize,stdA,stdD,meanA,meanD);
    T = sortrows(T, 1, 'descend');
    writetable(T, globalParam.directory+"SpotfiClusterization.txt", 'Delimiter','\t');
    
    if length(T.clSize) == 1
        T.stdA(2) = -1;
        T.meanA(2) = -1;
    elseif T.clSize(2) == 0
        T.stdA(2) = -1;
        T.meanA(2) = -1;
    end
    
%     fileID = fopen(globalParam.fileForSpotfiResults, 'a');
%     fprintf(fileID, string(globalParam.numberOfAntennas)+"\t"+string(globalParam.SpotfiSubarrayNum)+ ...
%         "\t"+string(globalParam.seedForScenario)+"\t"+string(globalParam.SNR)+"\t"+string(globalParam.Kfactor)+ ...
%         "\t"+string(globalParam.AngleOfLOS)+"\t"+string(T.meanA(1))+"\t"+string(T.stdA(1))+"\t"+string(T.clSize(1))+ ...
%         "\t"+string(abs(T.meanA(1)-globalParam.AngleOfLOS))+"\t"+string(T.meanA(2))+ ...
%         "\t"+string(T.stdA(2))+"\t"+string(T.clSize(2))+"\t"+string(globalParam.ArraytrackBackwardSmoothingUsed)+ ...
%         "\t"+string(globalParam.SpotfiNumberOfIterations)+"\t"+string(globalParam.numberOfPacketsPerIteration)+"\t");
%     fclose(fileID);
end

if globalParam.plotClusters
    d = 1000; % Grid length
    x1 = linspace(min(X(:,1))-2, max(X(:,1))+2, d);
    x2 = linspace(min(X(:,2))-2, max(X(:,2))+2, d);
    [x1grid,x2grid] = meshgrid(x1,x2);
    X0 = [x1grid(:) x2grid(:)];

    mahalDist = mahal(gmfit,X0); % Distance from each grid point to each GMM component
    % Draw ellipsoids over each GMM component and show clustering result.
    f=figure; h1 = gscatter(X(:,1)*angleMax,X(:,2)*delayMax,clusterX, [], [], []);
    hold on
    title('Spotfi estimated AoA and ToF');
    ylabel('Delays, ns');
    xlabel('Angle, degrees');
    ylim([-delayMax delayMax]*1.05);
    xlim([-angleMax angleMax]*1.05);
    
    for m = 1:clusterNumber
        idx = mahalDist(:,m)<=threshold;
        h2 = plot(X0(idx,1)*angleMax,X0(idx,2)*delayMax,'.','MarkerSize',1);
        uistack(h2,'bottom');
    end
    plot(gmfit.mu(:,1)*angleMax,gmfit.mu(:,2)*delayMax,'kx','LineWidth',2,'MarkerSize',10)
    
    lines = []; labels = [];
    number = 0;
    for i=1:clusterNumber
        if clSize(i)>0
            number = number + 1;
            lines = [lines h1(number)];
            labels = [labels string(clSize(i))+",("+...
                sprintf("%.1f",gmfit.mu(i,1)*angleMax)+char(176)+sprintf(",%.1f",gmfit.mu(i,2)*delayMax)+"ns"+")"];
        end
    end
    
    legend(lines, labels, 'Location','southwest', 'FontSize',7);
    hold off
    
    if globalParam.saveClusters
        saveas(f, globalParam.directory+"SpotfiClusters.png");
    end
    
    if globalParam.closeClusters
        close
    end
end

toc