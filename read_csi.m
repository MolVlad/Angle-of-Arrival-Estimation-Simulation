packnum = 2;
channelnum = 4;
csinum = 242;
samplenum = 1000;

sample = readfile("samples.txt", channelnum*samplenum*packnum);
sample = reshape(sample, channelnum, samplenum, packnum);
sample = permute(sample, [2 1 3]);

csi = readfile("csi.txt", channelnum*csinum*packnum);
csi = reshape(csi, channelnum, csinum, packnum);
csi = permute(csi, [2 1 3]);

