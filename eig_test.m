function [U,d] = eig_test(Rxx)
% [Utmp,D] = eig(Rxx,eye(size(Rxx)),'qz');
[Utmp,D] = eig(Rxx);

d = diag(abs(D));
[~,I] = sort(d, 'ascend');
U = Utmp(:,I);
d = d(I);

end