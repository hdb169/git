#2019 sept 16
#import various modules 
import glob, string, pickle 
import numpy as np 
import pandas as pd
#use glob to grab the whole report folder and read those report file one by one
#it will create a list which look like :  

rf = glob.glob('/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_**-1.report') 

#define the data dictionary 
dd={ }

#sort the list for consistency 
rf.sort()


#define a report file dictionary : where we will store the several values
#from the report files 
 
rfd={ 'rn' : [], # run number  
      'hms_bcm1_beam_cut_current'   : [], #HMS 3/4 Trigger Rate  line 133  //added     
      'hms_bcm2_beam_cut_current'  : [], # SHMS 3/4 Trigger Rate line 124  //added
      'hms_bcm4A_beam_cut_current' : [], # current as measured by bcm 4A
      'hms_bcm4B_beam_cut_current' : [],  # current as measured by bcm 4B 
      'hms_bcm4C_beam_cut_current' : [], # current as measured by 4C
      'hms_unser_beam_cut_current' : [] # current as measured by Unser

     }
for index, run in enumerate(rf):
    with open(rf[index]) as fobj:
        for line in fobj:
            report_data = line.split(':')
            if('Run #' in report_data[0]) : rfd['rn'].append(report_data[1].strip())  # [1] is for 
            if('HMS BCM1 Beam Cut Current' in report_data[0] and not 'SHMS' in report_data[0]) : rfd['hms_bcm1_beam_cut_current'].append(report_data[1][:7].strip())  # [1][:7] is for 
            if('HMS BCM2 Beam Cut Current' in report_data[0] and not 'SHMS' in report_data[0]) : rfd['hms_bcm2_beam_cut_current'].append(report_data[1][:7].strip())
            if('HMS BCM4A Beam Cut Current' in report_data[0] and not 'SHMS' in report_data[0]) : rfd['hms_bcm4A_beam_cut_current'].append(report_data[1][:7].strip())
            if('HMS BCM4B Beam Cut Current' in report_data[0] and not 'SHMS' in report_data[0]) : rfd['hms_bcm4B_beam_cut_current'].append(report_data[1][:7].strip())
            if('HMS BCM4C Beam Cut Current' in report_data[0] and not 'SHMS' in report_data[0]) : rfd['hms_bcm4C_beam_cut_current'].append(report_data[1][:7].strip())
            if('HMS Unser Beam Cut Current' in report_data[0] and not 'SHMS' in report_data[0]) : rfd['hms_unser_beam_cut_current'].append(report_data[1][:7].strip())

#print(rfd)

for var_str, var in rfd.items(): #var_str : keys, var : list of values
    #print(var)
    dd[var_str]=[]
    for index, var  in enumerate(rfd['rn']):
        dd[var_str].append(rfd[var_str][index])

for rfd_var, rfd_list in dd.items():
    print(rfd_list)
    rfd_array = np.asarray(rfd_list, dtype='float')
    dd[rfd_var] = rfd_array

#print(dd)
pickle.dump(dd,open('bcm_unser_cut_current.pkl','wb'))

file = open("1hms_bcm.txt","w")
for index in range(len(rfd['rn'])):
    file.write(str(rfd['rn'][index]) + " " +   str(rfd['hms_bcm1_beam_cut_current'][index])  + "   " +  str(rfd['hms_bcm2_beam_cut_current'][index]) + "     " + str(rfd['hms_bcm4A_beam_cut_current'][index])+ " " + str(rfd['hms_bcm4B_beam_cut_current'][index])+ " "+str(rfd['hms_bcm4C_beam_cut_current'][index])+" " +str(rfd['hms_unser_beam_cut_current'][index]) + "\n")


file.close()




