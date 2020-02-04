#Jan 31, 2020
##import various modules 
#########################################This prints the bcm current values in terminal #########
##########################################First column is  run, second is (bcm1-bcm2)/bcm1, second is (4A=4B)/4A, 3rd is (1-4A)/4A
##To do addition or subtraction, we need floats, not the strings, so, first thing is to get the numbers as float. 
##The method, how the report file was reading different value earlier is by using string.
#Need the way to store in the text file.


import glob, string, pickle 
import numpy as np 
import pandas as pd
from pprint import pprint
#use glob to grab the whole report folder and read those report file one by one
#it will create a list which look like :  

#rf = glob.glob('/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_*-1.report') 
rf = glob.glob('/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/REPORT_OUTPUT/COIN/PRODUCTION_ALL_RUNS_MAY23_2019/replay_coin_production_*-1.report') 

#define the data dictionary 
dd={ }

#sort the list for consistency 
rf.sort()


#define a report file dictionary : where we will store the several values
#from the report files 
 
rfd={ 'rn' : [], # run number  
      'bcm1'   : [], #SHMS 3/4 Trigger Rate  line 133  //added     
      'bcm2'  : [], # SSHMS 3/4 Trigger Rate line 124  //added
      'bcm4A' : [], # current as measured by bcm 4A
      'bcm4B' : [],  # current as measured by bcm 4B 
      'bcm4C' : [], # current as measured by 4C
      'unser' : [] # current as measured by Unser

     }
for index, run in enumerate(rf):
    with open(rf[index]) as fobj:
        for line in fobj:
            report_data = line.split(':')
            if('Run #' in report_data[0]) : rfd['rn'].append(report_data[1].strip())  # [1] is for 
            if('SHMS BCM1 Beam Cut Current' in report_data[0]) : rfd['bcm1'].append(report_data[1][:7].strip())  # [1][:7] is for 
            if('SHMS BCM2 Beam Cut Current' in report_data[0]) : rfd['bcm2'].append(report_data[1][:7].strip())
            if('SHMS BCM4A Beam Cut Current' in report_data[0]) : rfd['bcm4A'].append(report_data[1][:7].strip())
            if('SHMS BCM4B Beam Cut Current' in report_data[0]) : rfd['bcm4B'].append(report_data[1][:7].strip())
            if('SHMS BCM4C Beam Cut Current' in report_data[0]) : rfd['bcm4C'].append(report_data[1][:7].strip())
            if('SHMS Unser Beam Cut Current' in report_data[0]) : rfd['unser'].append(report_data[1][:7].strip())

#print(rfd)

for var_str, var in rfd.items(): #var_str : keys, var : list of values
    #print(var)
    dd[var_str]=[]
    for index, var  in enumerate(rfd['rn']):
        dd[var_str].append(rfd[var_str][index])

for rfd_var, rfd_list in dd.items():
    #print(rfd_list)
    rfd_array = np.asarray(rfd_list, dtype='float')
    dd[rfd_var] = rfd_array

#print(dd)
#pickle.dump(dd,open('bcm_unser_cut_current.pkl','wb'))

#print (type (rfd['shms_bcm1_beam_cut_current']))
for i in range(842):
    print (dd['rn'][i] ,  ((dd['bcm1'][i]- dd['bcm2'][i])/dd['bcm1'][i]), ((dd['bcm4A'][i]- dd['bcm4B'][i])/dd['bcm4A'][i]), ((dd['bcm1'][i]- dd['bcm4A'][i])/dd['bcm1'][i]))
#    print (dd['bcm2'][i],dd['bcm2'][i]) good

#    print (dd['rn'][i])



