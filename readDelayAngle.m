
clusterNumber = 10;
savetable = 0;
plotClusters = 0;
saveClusters = 1;
closeClusters = 0;
SpotfiMeasurement = 1;
directory = "SpotfiClusters/";
mkdir(directory);
data_dir = "experiment_spotfi/";
fileForResults = "SpotfiResults_fixed_eigen_1.txt";

if ~isfile(directory+fileForResults)
    fileID = fopen(directory+fileForResults, 'w');
    col = "";
    for k = 1:5
        sn = string(k);
        col = col + "\tclSize" + sn + "\tstdA" + sn + "\tstdD" + sn + "\tmeanA" + sn + "\tmeanD" + sn;
    end
                                                
    fprintf(fileID,"ant\tseed\tsmoothing\tbackw\tpacketNum\tpacketPerSpec\tbandwidth\tdecimation" + col + "\n");
    fclose(fileID);
end

randomSeedForScenario = 1:10000;
numberOfAntennas = [8 4];
useSmothing = [0 1];
backwardSmoothingUsed = [0 1];
packetNum = [30 10];
packetPerSpectrum = [1 2];
bandwidth = [20];
subcarrierDecimationUsed = [0 1];

all = length(randomSeedForScenario);
i = 0;
for seed=randomSeedForScenario
    s=sprintf('%d',int32(seed)); seed_str = '00000'; seed_str(end+1-length(s):end) = s;
    data_dir = "run_cluster/results/music_fixed_eigen_1/music_"+seed_str+"/";
    for ant=numberOfAntennas
        for smoothing = useSmothing
            for backw = backwardSmoothingUsed
                for p = packetNum
                    for perSpec = packetPerSpectrum
                        for band = bandwidth
                            for dec = subcarrierDecimationUsed
                                
                                name = "r_"+seed_str+"_ant_"+string(ant)+"_sm_"+string(smoothing)+"_backw_"+string(backw)+"_pack_"+string(p)+"_perSp_"+...
                                    string(perSpec)+"_bw_"+string(band)+"_dec_" + string(dec);

                                file = data_dir+name+".txt";
                                
                                if isfile(file)
                                    tic
                                    
                                    nsDelayAngleSpotfiEstimated=load(file);
                                    nsDelayAngleSpotfiEstimated=reshape(nsDelayAngleSpotfiEstimated,2,[]);
                                    % nsDelayAngleSpotfiEstimated
                                    
                                    if size(nsDelayAngleSpotfiEstimated,2) < round(p / perSpec / 2)
                                        if SpotfiMeasurement
                                            for_print = string(ant)+"\t"+string(seed)+"\t"+string(smoothing)+"\t"+string(backw)+"\t"+string(p)+"\t"+string(perSpec)+ ...
                                                "\t"+string(band)+"\t"+string(dec);
                                            
                                            for k = 1:5
                                                if k == 1
                                                    for_print = for_print + "\t" + -999 + "\t" + string(90) + "\t\t\t";
                                                else
                                                    for_print = for_print + "\t0\t\t\t\t";
                                                end
                                            end
                                            for_print = for_print + "\n";
                                            
                                            fileID = fopen(directory+fileForResults, 'a');
                                            fprintf(fileID, for_print);
                                            fclose(fileID);
                                        end
                                    else
                                        delayMax = 300;
                                        angleMax = 90;
                                        
                                        Y = nsDelayAngleSpotfiEstimated(1:2,:)';
                                        X = [];
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
                                        
                                        if SpotfiMeasurement
                                            T=table(clSize,stdA,stdD,meanA,meanD);
                                            T = sortrows(T, 1, 'descend');
                                            if savetable
                                                writetable(T, directory+name+"txt", 'Delimiter','\t');
                                            end
                                            
                                            for_print = string(ant)+"\t"+string(seed)+"\t"+string(smoothing)+"\t"+string(backw)+"\t"+string(p)+"\t"+string(perSpec)+ ...
                                                "\t"+string(band)+"\t"+string(dec);
                                            for k = 1:5
                                                if size(T,1) < k
                                                    for_print = for_print + "\t0\t\t\t\t";
                                                else
                                                    if T.clSize(k)
                                                        for_print = for_print + "\t" + string(T.clSize(k)) + "\t" + string(T.stdA(k)) + "\t" + string(T.stdD(k)) + ...
                                                            "\t" + string(T.meanA(k)) + "\t" + string(T.meanD(k));
                                                    else
                                                        for_print = for_print + "\t0\t\t\t\t";
                                                    end
                                                end
                                            end
                                            for_print = for_print + "\n";
                                            
                                            fileID = fopen(directory+fileForResults, 'a');
                                            fprintf(fileID, for_print);
                                            fclose(fileID);
                                        end
                                        
                                        if plotClusters
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
                                            
                                            if saveClusters
                                                saveas(f, directory+name+".png");
                                            end
                                            
                                            if closeClusters
                                                close
                                            end
                                        end
                                    end
                                else
                                    disp("name "+name+" doesn't exist");
                                end
                            end
                        end
                    end
                end
            end
        end
    end
    
    toc
    i = i + 1;
    fprintf("%d/%d\n", i, all);
end

