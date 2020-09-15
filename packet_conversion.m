name = "80mhz packet";

out=readhexfile(name+".txt", 3520);

str = string(out);
f=fopen(name+" dec.txt", 'w');
for i=1:length(str)
    fprintf(f,'%s\n', str(i));
end

bin=de2bi(out);

bin_imag = bin(:,1:16);
bin_real = bin(:,17:32);

re = reinterpretcast(uint16(bi2de(bin_imag)), numerictype(1, 16, 13));
im = reinterpretcast(uint16(bi2de(bin_real)), numerictype(1, 16, 13));

c=complex(re, im);

f=fopen(name+" cpx.txt", 'w');
for i=1:length(c)
    fprintf(f,'%f+%fi\n', re(i), im(i));
end


