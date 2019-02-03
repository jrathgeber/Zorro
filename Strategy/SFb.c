/* 

	SFa.c

	Super Fit USD/CAD

	Counter Trand Only

	Jason P Rathgeber
	
*/

function tradeCounterTrend()
{

	TimeFrame = 4;
	
	vars Price = series(price());
	vars Filtered = series(BandPass(Price,optimize(12,8,14),0.5));
	vars Signal = series(Fisher(Filtered,500));
	var Threshold = optimize(0.4,0.3,0.6);
	
	Stop = optimize(1,1,6) * ATR(100);
	Trail = .1*ATR(100);
	//Trail = 500;
	
	if(crossUnder(Signal,-Threshold)) {
		enterLong(); 
		plot("Valley",*Signal,TRIANGLE,GREEN);
	}
	else if(crossOver(Signal,Threshold)) {
		enterShort();
		plot("Peak",*Signal,TRIANGLE,RED);
	}
			
	plot("Filtered",*Filtered,NEW,BLACK);
	plot("Signal",*Signal,NEW,BLACK);	
	
}

function tradeTrend()
{
	/*
	
	TimeFrame = 1;
	vars Price = series(price());
	vars Trend = series(LowPass(Price,optimize(500,50,1000)));

	Stop = optimize(4,2,10) * ATR(100);
	Trail = 4*ATR(100);

	vars MMI_Raw = series(MMI(Price,300));
	vars MMI_Smooth = series(LowPass(MMI_Raw,600));
	
	//if(falling(MMI_Smooth)) {
		
		if(valley(Trend)) {
				enterLong(1000);
				plot("Valley",*Trend,TRIANGLE,GREEN);
		}	else if(peak(Trend)) {
				enterShort(1000);
				plot("Peak",*Trend,TRIANGLE,RED);
		} 
	
	//}
		
		plot("BAND",*MMI_Smooth,NEW,BLUE);	
		
		plot("Trend",*Trend,NEW,BLACK);	

		*/
		
}

function run()
{
	//if (Train) set(PARAMETERS+SKIP3);  		// generate and use optimized parameters					// skip every 3rd week trading 
	//if (Test) set(PARAMETERS+SKIP1);  		// generate and use optimized parameters					// test on thrid week (skip 1 and 2)
	//if (Test) set(PARAMETERS+SKIP1+SKIP2);  // generate and use optimized parameters					// test on thrid week (skip 1 and 2)
	//set(PARAMETERS+LOGFILE);  						// generate and use optimized parameters and factors
	
	//set(PARAMETERS);
	//DataSplit = 75;
	
	//setf(TrainMode);
	
	set(PLOTNOW);
	
	setf(PlotMode,PL_ALL+PL_FINE+PL_FILE);
	
	PlotScale = 8;
	PlotWidth = 2000;
	PlotHeight1 = 700;
	PlotHeight2 = 200;
	
	NumCores = 2;										// use multiple cores (Zorro S only) all my cores !
	BarPeriod = 240;									// 1 hour bars
	LookBack = 2000;									// needed for Fisher()
	StartDate = 2017;
	
	EndDate = 2019; 									// fixed simulation period
	
	//NumWFOCycles = 10; 								// activate WFO
	//NumSampleCycles = 4;
	
	if(ReTrain) {
		UpdateDays = -1;								// update price data from the server 
		SelectWFO = -1;								// select the last cycle for re-optimization
		reset(FACTORS);								// don't generate factors when re-training
	}
	
// portfolio loop

//	while(asset(loop("AUD/USD","GBP/USD","USD/CAD","EUR/USD","USD/JPY")))
	while(asset(loop("USD/CAD")))
	while(algo(loop("TRND","CNTR")))
	{
		if(Algo == "TRND") 
			tradeTrend();
		else if(Algo == "CNTR") 
			tradeCounterTrend();
	}

	set(TESTNOW+LOGFILE);
}