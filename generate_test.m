function generate_test(a)
 
fileID = fopen(str, 'w');
for k = 1:size(a,3)
    for j = 1:size(a,2)
        for i = 1:size(a,1)
            fprintf(fileID, "%f+%fi ", real(a(i,j,k)),imag(a(i,j,k)));
        end
    end
end
fclose(fileID);

end