#to run this, you have to do python read_lins_from_reportfile.py


#import various modules 

import glob, string, pickle 
import numpy as np 
import pandas as pd
#use glob to grab the whole report folder and read those report file one by one


rf = glob.glob('/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_7*_-1.report') 

#define the data dictionary 
dd={ }

#sort the list for consistency 
rf.sort()


#define a report file dictionary : where we will store the several values
#from the report files 
 
rfd={ 'rn' : [], # run number  
      'hms_rate'   : [], #HMS 3/4 Trigger Rate  line 133  //added     
      'shms_rate'  : [], # SHMS 3/4 Trigger Rate line 124  //added
 
#     'current_4A' : [], # current as measured by bcm 4A
#      'current_4B' : [],  # current as measured by bcm 4B 
#      'current_unser' : [] # current as measured by Unser

     }
for index, run in enumerate(rf):
    with open(rf[index]) as fobj:
        for line in fobj:
            report_data = line.split(':')
            if('Run #' in report_data[0]) : rfd['rn'].append(report_data[1].strip())  # [1] is for 
            if('HMS 3/4 Trigger Rate' in report_data[0]) : rfd['hms_rate'].append(report_data[1].strip())  # [1][:7] is for upto 7 digits or 7 characters
            if('SHMS 3/4 Trigger Rate' in report_data[0]) : rfd['shms_rate'].append(report_data[1].strip())

#            if('BCM1 Current' in report_data[0]) : rfd['current_4A'].append(report_data[1][:7].strip())
#            if('BCM2 Current' in report_data[0]) : rfd['current_4B'].append(report_data[1][:7].strip())
#            if('Unser Current' in report_data[0]) : rfd['current_unser'].append(report_data[1][:7].strip())

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

file = open("rates_all.txt","w")
for index in range(len(rfd['rn'])):
 #   file.write(str(rfd['rn'][index]) + " " +   str(rfd['hms_rate'][index])  + "   " +  str(rfd['shms_rate'][index]) + "     "        + str(rfd['current_4A'][index])+ " " + str(rfd['current_4B'][index]) + "\n")
 file.write(str(rfd['rn'][index]) + "   " +   str(rfd['hms_rate'][index])  + "   " +  str(rfd['shms_rate'][index]) + "\n")

#added to read pkl file
#unpickled_df = pd.read_pickle("./bcm_unser_cut_current.pkl")
#print (unpickled_df)
file.close()




 
