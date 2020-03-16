#to run this, you have to do python read_reportfile.py
#This code works very good, earlier the code was confused between HMS and SHMS 3/4 rate, becuase in all "SHMS", there is "HMS"
# and Deb fixed it.
#2019 oct 03
#import various modules 
import glob, string, pickle 
import numpy as np 
import pandas as pd
#use glob to grab the whole report folder and read those report file one by one

#rf = glob.glob('replay_coin_production_****_-1.report') 
rf = glob.glob('/lustre/expphy/volatile/hallc/spring17/hdbhatt/group/REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_****-1.report') 

#define the data dictionary 
dd={ }

#sort the list for consistency 
rf.sort()


#define a report file dictionary : where we will store the several values
#from the report files 
 
rfd={ 'rn' : [], # run number  
      'Target' : [],#Target mass (amu)
      'HMS_Angle' : [],
      'HMS_P_Central' : [],
      'hms_rate' : [], #HMS 3/4 Trigger Rate  line 133  //added     
      'SHMS_Angle' : [],
      'SHMS_P_Central' : [],
      'shms_rate' : [], # SHMS 3/4 Trigger Rate line 124  //added
      'current_1' : [], # current as measured by bcm 4A
      'charge_1' : [],
#      'ps1' : [],#Ps1_factor
#      'ps4' = [],
#      'ps6' = []

     }
for index, run in enumerate(rf):
    with open(rf[index]) as fobj:
        for line in fobj:
            report_data = line.split(':')
            if('Run #' in report_data[0]) : rfd['rn'].append(report_data[1].strip())
            if('Target mass (amu)' in report_data[0]) : rfd['Target'].append(report_data[1][:7].strip())
            if('HMS Angle' in report_data[0] and not 'SHMS' in report_data[0]) : rfd['HMS_Angle'].append(report_data[1][:7].strip())
            if('HMS P Central' in report_data[0] and not 'SHMS' in report_data[0]) : rfd['HMS_P_Central'].append(report_data[1][:5].strip())
            if('HMS 3/4 Trigger Rate' in report_data[0] and not 'SHMS' in report_data[0]) : rfd['hms_rate'].append(report_data[1][:5].strip()) 
            if('SHMS Angle' in report_data[0]) : rfd['SHMS_Angle'].append(report_data[1][:5].strip())
            if('SHMS P Central' in report_data[0]) : rfd['SHMS_P_Central'].append(report_data[1][:5].strip())
            if('SHMS 3/4 Trigger Rate' in report_data[0]) : rfd['shms_rate'].append(report_data[1][:7].strip())
            if('SHMS BCM1 Beam Cut Current' in report_data[0]) : rfd['current_1'].append(report_data[1][:7].strip())
            if('SHMS BCM1  Beam Cut Charge' in report_data[0]) : rfd['charge_1'].append(report_data[1][:7].strip())
#            if('Ps1_factor' in report_data[0]) : rfd['ps1'].append(report_data[1].strip())


            

#print(rfd)

for index, run in enumerate(rf):
    print(rfd['rn'][index])
    print(rfd['hms_rate'][index])

for var_str, var in rfd.items(): #var_str : keys, var : list of values
    #print(var)
    dd[var_str]=[]
    for index, var  in enumerate(rfd['rn']):
        dd[var_str].append(rfd[var_str][index])

for rfd_var, rfd_list in dd.items():
#    print(rfd_list)
    rfd_array = np.asarray(rfd_list, dtype='float')
    dd[rfd_var] = rfd_array

#print(dd)
#pickle.dump(dd,open('bcm_unser_cut_current.pkl','wb'))

file = open("hamlet.txt","w")
for index in range(len(rfd['rn'])):
    print(rfd['rn'][index] +"\t"+ rfd['Target'][index]+"\t"+ rfd['HMS_Angle'][index] +"\t"+ rfd['HMS_P_Central'][index]+"\t"+ rfd['hms_rate'][index]+"\t"+ rfd['SHMS_Angle'][index]+ "\t"+ rfd['SHMS_P_Central'][index]+"\t"+ rfd['shms_rate'][index]+"\t"+ rfd['current_1'][index]+"\t"+ rfd['charge_1'][index]+"\n")
    file.write(str(rfd['rn'][index] +"\t"+ rfd['Target'][index]+"\t"+ rfd['HMS_Angle'][index] +"\t"+ rfd['HMS_P_Central'][index]+"\t"+ rfd['hms_rate'][index]+"\t"+ rfd['SHMS_Angle'][index]+ "\t"+ rfd['SHMS_P_Central'][index]+"\t"+ rfd['shms_rate'][index]+"\t"+ rfd['current_1'][index]+"\t"+ rfd['charge_1'][index]) +"\n")


#    file.write(str(rfd['rn'][index]) + "   " +   str(rfd['hms_rate'][index])  +  "   " +  str(rfd['shms_rate'][index]) +"\n")

    
#    print(rfd['rn'][index] + " " + rfd['hms_rate'][index] + " "+rfd['shms_rate'][index])
#    file.write(str(rfd['rn'][index]) + "   " +   str(rfd['hms_rate'][index])  +  "   " +  str(rfd['shms_rate'][index]) +"\n")# "   " + str(rfd['current_4A'][index])+ " " + str(rfd['current_4B'][index]) + "\n")
    
    #added to read pkl file
    #unpickled_df = pd.read_pickle("./bcm_unser_cut_current.pkl")
    #print (unpickled_df)
file.close()
    
    
