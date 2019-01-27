
    for (Int_t i = 0; i < *Ndata_H_cal_2ta_negAdcPulseTime ; i++) {//looping over No of hit per event 
      
      if (H_cal_2ta_negAdcErrorFlag[i] == 1) continue;
      Int_t current_pmt = H_cal_2ta_negAdcCounter[i] - 1;
      
      h2taCALNegAdcPulseTimeStarttimeDiff[current_pmt]->Fill(-H_cal_2ta_negAdcPulseTime[i] + *H_hod_starttime);//no hit selection
      h2taCALNegPulseAmpVsPulseTimeStarttimeDiff[current_pmt]->Fill(-H_cal_2ta_negAdcPulseTime[i] + *H_hod_starttime ,H_cal_2ta_negAdcPulseAmp[i]);
      
      if(*H_cer_npeSum >2.0)
	{
	  h2taCALNegAdcPulseTimeStarttimeDiffCer[current_pmt]->Fill(-H_cal_2ta_negAdcPulseTime[i] + *H_hod_starttime);//added1 //no hit but cer
	  h2taCALNegPulseAmpVsPulseTimeStarttimeDiffCer[current_pmt]->Fill(-H_cal_2ta_negAdcPulseTime[i] + *H_hod_starttime ,H_cal_2ta_negAdcPulseAmp[i]);//added1
	}
      
      if ( H_cal_2ta_goodNegAdcMult[current_pmt] ==1)
	{
	  h2CALNegAdcPulseTimeStarttimeDiffMult[current_pmt]->Fill(-H_cal_2ta_negAdcPulseTime[i] + *H_hod_starttime);//added2 //no hit but mult
	  h2taCALNegPulseAmpVsPulseTimeStarttimeDiffMult[current_pmt]->Fill(-H_cal_2ta_negAdcPulseTime[i] + *H_hod_starttime ,H_cal_2ta_negAdcPulseAmp[i]);//added2
	  
	  if (*H_cer_npeSum >2.0) 
	    {
	      h2taCALNegAdcPulseTimeStarttimeDiffMultCer[current_pmt]->Fill(-H_cal_2ta_negAdcPulseTime[i] + *H_hod_starttime); //no hit but mult cer
	      h2taCALNegPulseAmpVsPulseTimeStarttimeDiffMultCer[current_pmt]->Fill(-H_cal_2ta_negAdcPulseTime[i] + *H_hod_starttime ,H_cal_2ta_negAdcPulseAmp[i]);
	    }
	}
    }
    
    //Draw all those timediff plots on same canvas
    //tight window only make separate code only for good variable 

    //only for tight window make separate code
    for(Int_t i =0; i<*Ndata_H_cal_2ta_goodNegAdcTdcDiffTime; i++){//selecting one hit only
      if (H_cal_2ta_negAdcErrorFlag[i] == 1) continue;

      h2taCALNeggoodAdcTdcDiffTime[i]->Fill(H_cal_2ta_goodNegAdcTdcDiffTime[i]);//added3 //hit selection
      h2taCALgoodNegPulseAmpVsPulseTime[i]->Fill(H_cal_2ta_goodNegAdcTdcDiffTime[i], H_cal_2ta_goodNegAdcPulseAmp[i]);//added3

      if (*H_cer_npeSum>2.0)
	{
	  h2taCALNeggoodAdcTdcDiffTimeCer[i]->Fill(H_cal_2ta_goodNegAdcTdcDiffTime[i]);//added4 //hit but cer
	  h2taCALgoodNegPulseAmpVsPulseTimeCer[i]->Fill(H_cal_2ta_goodNegAdcTdcDiffTime[i], H_cal_2ta_goodNegAdcPulseAmp[i]);//added4
	}
      if (H_cal_2ta_goodNegAdcMult[i] ==1)
	{
	  h2taCALNeggoodAdcTdcDiffTimeMult[i]->Fill(H_cal_2ta_goodNegAdcTdcDiffTime[i]);//added5 //hit but mult
	  h2taCALgoodNegPulseAmpVsPulseTimeMult[i]->Fill(H_cal_2ta_goodNegAdcTdcDiffTime[i], H_cal_2ta_goodNegAdcPulseAmp[i]);//added5
	
	  if (*H_cer_npeSum >2.0) 
	    { 
	      h2taCALNeggoodAdcTdcDiffTimeMultCer[i]->Fill(H_cal_2ta_goodNegAdcTdcDiffTime[i]); //hit but mult cer
	      h2taCALgoodNegPulseAmpVsPulseTimeMultCer[i]->Fill(H_cal_2ta_goodNegAdcTdcDiffTime[i], H_cal_2ta_goodNegAdcPulseAmp[i]);
	    }
	}

    }
