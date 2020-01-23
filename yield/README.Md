1)files with pim_x35_z70.C and pim_x35_z70_al.C will be for all pi+ and Pi- z values for D2 and Dummy.
 4 z settings, will have 4+4 (d2+al) for pi+ and exactly same files for pi- 

a)read the corresponding rootfiles
b)find ctime peak
c)find accidental contribution
d)do the accidental subtraction
e)save the final 4 histogram for pi+, and 4 for pi_in a rootfile......e.g.
root/pim_x35_z70.root 
root/pim_x35_z70_al.root.... and simila for Pi+


2)files  pim_x35_dummy_sub.C pip_x35_dummy_sub.C will
one will read pi+ data and other pi- data:

a)Read the above mentioned accidental subtracted z histograms for pi+ and pi+
b)Need to write manually the charge in each z settings for data pi+, data pi-, dummy pi+ and dummy pi-
c)Apply the scale factor of 0.244 for Al data due to difference in wall thickness of dummy annd D2 target
d)Calculate the yields for all different z settings separately, for D2 and Al.
e)Will subtract the yield of Al from yield of D2 for different z settings separately.
f)Save the four(or 3) dummy corrected yield in Rootfile: root/pim_x35_z_70_60_50_40.root  
       	   	      	    	      	       and	 root/pip_x35_z_70_60_50_40.root


3)Finally, x35_final_data_fit.C will read the 4 dummy subtracted yields from pi- and 4 from pi+ and then add all the pi+ yields 
   and also add 4 pi- yield separately, and then take the ratio of yields.
    It also, overlays the pi+/pi yield ratio from fit function obtained from Hermes Data.

4)I am working on plotting Rd_measured for this setting and also apply the tracking efficiency corrections, whatever I will have.


