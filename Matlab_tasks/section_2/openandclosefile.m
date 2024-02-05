FileID = fopen('TextFile.txt','w');
Diploma ='Model-Based development';
Modles_Number = 10;
Current_Module ='MATLAB BASIC';
fprintf(FileID,'diploma:%s\n',Diploma);
fprintf(FileID,'Modles_Number:%d\n',Modles_Number);
fprintf(FileID,'Current_Module:%s\n',Current_Module);
fopen(FileID);