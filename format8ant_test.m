function matrixCSI = format8ant_test(vectorCSI, param) %#codegen

K = param.K;
L = param.L;
M = param.M;
N = param.N;
T = param.T;
S = param.S;
backw = param.backw;

vectorCSI = vectorCSI(:,:,1:T*S);

csiTracePerPacket = reshape(vectorCSI, N, M, T*S);

if backw
    columnsNum = (M - K + 1)*(N - L + 1);
    matrixCSI=complex(zeros(K * L, columnsNum*2*S, T));
    for t = 1:T
        for s = 1:S
            csiFromEachPacket = csiTracePerPacket(:,:,(t-1)*S+s);
            D = complex(zeros(L, N-L+1, M));
            for m=1:M % mth antenna
                D(:,:,m) = hankel(csiFromEachPacket(1:L,m),csiFromEachPacket(L:N, m));
            end
            De = complex(zeros(K * L, columnsNum));
            for start_idx = 1:K
                tmp = complex(zeros(L,(M-K+1)*(N-L+1)));
                for j = 1:M-K+1
                    tmp(:,(j-1)*(N-L+1)+1:j*(N-L+1)) = D(:,:,start_idx+j-1);
                end
                De((start_idx-1)*L+(1:L),:) = tmp;
            end
            matrixCSI(:,(s-1)*columnsNum*2+1:s*columnsNum*2-columnsNum,t) = De;
        end
    end
    
    conjCsiTracePerPacket = conj(csiTracePerPacket(size(csiTracePerPacket,1):-1:1,size(csiTracePerPacket,2):-1:1,:));
    
    for t = 1:T
        for s = 1:S
            csiFromEachPacket = conjCsiTracePerPacket(:,:,(t-1)*S+s);
            D = complex(zeros(L, N-L+1, M));
            for m=1:M % mth antenna
                D(:,:,m) = hankel(csiFromEachPacket(1:L,m),csiFromEachPacket(L:N, m));
            end
            De = complex(zeros(K * L, (M - K + 1)*(N - L + 1)));
            for start_idx = 1:K
                tmp = complex(zeros(L,(M-K+1)*(N-L+1)));
                for j = 1:M-K+1
                    tmp(:,(j-1)*(N-L+1)+1:j*(N-L+1)) = D(:,:,start_idx+j-1);
                end
                De((start_idx-1)*L+(1:L),:) = tmp;
            end
            matrixCSI(:,(s-1)*columnsNum*2+columnsNum+1:s*columnsNum*2,t) = De;
        end
    end
else
    columnsNum = (M - K + 1)*(N - L + 1);
    matrixCSI=complex(zeros(K * L, columnsNum*S, T));
    for t = 1:T
        for s = 1:S
            csiFromEachPacket = csiTracePerPacket(:,:,(t-1)*S+s);
            D = complex(zeros(L, N-L+1, M));
            for m=1:M % mth antenna
                D(:,:,m) = hankel(csiFromEachPacket(1:L,m),csiFromEachPacket(L:N, m));
            end
            De = complex(zeros(K * L, columnsNum));
             for start_idx = 1:K
                 tmp = complex(zeros(L,(M-K+1)*(N-L+1)));
                for j = 1:M-K+1
                    tmp(:,(j-1)*(N-L+1)+1:j*(N-L+1)) = D(:,:,start_idx+j-1);
                end
                De((start_idx-1)*L+(1:L),:) = tmp;
            end
            matrixCSI(:,(s-1)*columnsNum+1:s*columnsNum,t) = De;
        end
    end
end

end % formatCSI