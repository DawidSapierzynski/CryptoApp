crypto.exe -bc c -i input_bc.txt -o ./out/out_1_bc.txt -k key_bc.txt 
crypto.exe -bc d -i ./out/out_1_bc.txt -k key_bc.txt -o ./out/out_2_bc.txt
crypto.exe -sc c -i input_sc.txt -o ./out/out_1_sc.txt -k key_sc.txt 
crypto.exe -sc d -i ./out/out_1_sc.txt -k key_sc.txt -o ./out/out_2_sc.txt
crypto.exe -as c -i input_ac.txt -o ./out/out_1_ac.txt -k key1_ac.txt 
crypto.exe -as d -i ./out/out_1_ac.txt -k key2_ac.txt -o ./out/out_2_ac.txt
crypto.exe -hf -i input_hf.txt -o ./out/out_1_h.txt