% matrix2alist_nb.m
% autheur: Cédric Marchand
% convert a parity matrix to the alist format, output in a text file




H = load('./Matrix.txt');

%function matrix2alist (H,str)


fileID =fopen("./Alist.txt",'w');
fclose(fileID);


H_bin = H;
%H_bin( H > -1 ) = 1;
%H_bin( H<0 ) = 0;


[M,N] = size(H);
dc = sum(H_bin,2);
dv = sum(H_bin,1);
dcmax = max(dc);
dvmax = max(dv);

[nlist,~] = find(H_bin);
[mlist,~] = find(H_bin');

%GF=64;
disp('converting matrix to alist...');
%write in a file named matalist2.txt
     fileID =fopen("./Alist.txt",'at');    
      fprintf(fileID,'%d %d \n%d %d \n',N,M,dvmax,dcmax);
    for i=1:N
        fprintf(fileID,'%d ',dv(i));
    end
    fprintf(fileID,' \n');
    for i=1:M
        fprintf(fileID,'%d ',dc(i));
    end
    fprintf(fileID,' \n\n');
    k=0;
    for i=1:N
        for j=1:dv(i)
            fprintf(fileID,'%d ',nlist(k + j ));
            %fprintf(fileID,'%d ',H( nlist(k + j  ),i));
        end
        k=k+dv(i);
        fprintf(fileID,'\n');
    end
    fprintf(fileID,'\n');
    
    k=0;
    for i=1:M
        for j=1:dc(i)
            fprintf(fileID,'%d ',mlist(k + j ));
            %fprintf(fileID,'%d ',H( i, mlist(k + j  )));
        end
        k=k+dc(i);
        fprintf(fileID,' \n');
    end

    
      fclose(fileID);   

%end