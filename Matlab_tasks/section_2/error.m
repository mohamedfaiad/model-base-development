clc
clear all
file_id = fopen('MBD.txt','r');
if file_id == -1
    error("unable to open this file for reading");
end