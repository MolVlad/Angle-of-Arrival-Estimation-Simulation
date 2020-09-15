% y = readfile(filename)
% Read file 'filename' and return a MATLAB string with the contents
% of the file.
function out = readfile(filename, num) %#codegen

% Call fopen(filename 'r'), but we need to convert the MATLAB
% string into a C type string (which is the same string with the
% NUL (\0) string terminator).
f = fopen(filename, 'r');

% Call fseek(f, 0, SEEK_END) to set file position to the end of
% the file.
fseek(f, 0, 'eof');

% Call ftell(f) which will return the length of the file in bytes
% (as current file position is at the end of the file).
filelen = int32(ftell(f));

% Reset current file position
fseek(f,0,'bof');

% Initialize a buffer
maxBufferSize = int32(2^25);
buffer = zeros(1, maxBufferSize,'uint8');

% Remaining is the number of bytes to read (from the file)
remaining = filelen;

% Index is the current position to read into the buffer
index = int32(1);

while remaining > 0
    % Buffer overflow?
    if remaining + index > size(buffer,2)
        fprintf('Attempt to read file which is bigger than internal buffer.\n');
        fprintf('Current buffer size is %d bytes and file size is %d bytes.\n', maxBufferSize, filelen);
        break
    end
    % Read as much as possible from the file into internal buffer

    [dataRead, nread] = fread(f,remaining, 'char');
    buffer(index:index+nread-1) = dataRead;
    n = int32(nread);
    if n == 0
        % Nothing more to read
        break;
    end
    % Did something went wrong when reading?
    if n < 0
        fprintf('Could not read from file: %d.\n', n);
        break;
    end
    % Update state variables
    remaining = remaining - n;
    index = index + n;
end

% Close file
fclose(f);

str = (char(buffer(1:index)));
str = str(1:index-1);

y = complex(zeros(1,num));

s = length(str);

str = strrep(str, ',', '.');

k = 1;
for i = 1:num
    j = k;
    while (str(j) ~= ' ') && (j <= s)
        j = j + 1;
    end
    y(i) = str2double(str(k:j-1));
    k = j + 1;
end

out = y;