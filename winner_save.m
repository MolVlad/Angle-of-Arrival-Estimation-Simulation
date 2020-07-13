a=[complex(1,2) complex(5,6); complex(3,4) complex(7,8)];
a(:,:,2) = [complex(9,10) complex(13,14); complex(11,12) complex(15,16)];

fileID = fopen('lol.txt', 'w');
for k = 1:size(a,3)
    for j = 1:size(a,2)
        for i = 1:size(a,1)
            fprintf(fileID, "%f+%fi\n", real(a(i,j,k)),imag(a(i,j,k)));
        end
    end
end
fclose(fileID);

fileID = fopen('lol.txt','r');
formatSpec = '%f+%fi\t';
A = fscanf(fileID,formatSpec);

num = length(A) / 2;
b = complex(zeros(num, 1));
for i = 1:num
    b(i) = complex(A(2*i-1),A(2*i));
end

reshape(b,2,2,2)