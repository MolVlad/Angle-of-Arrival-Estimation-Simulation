clear all
close all

global globalParam;

CreateParams();
        
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

