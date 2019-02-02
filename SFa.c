/* 

	SFa.c

	Super Fit USD/CAD

	Trand Only

	Jason P Rathgeber
	
*/
	
function tradeCounterTrend()
{
	/*
	
	TimeFrame = 1;
	
	vars Price = series(price());
	vars Filtered = series(BandPass(Price,optimize(30,10,100,1),0.5));
	vars Signal = series(Fisher(Filtered,500));
	var Threshold = optimize(0.39,0.3,1.5,0.1);
	
	Stop = optimize(4,2,10, 1) * ATR(100);
	Trail = 1*ATR(150);
	
	if(crossUnder(Signal,-Threshold)) {
		enterShort(1000); 
		plot("Valley",*Signal,TRIANGLE,GREEN);
	}
	else if(crossOver(Signal,Threshold)) {
		enterLong(1000);
		plot("Peak",*Signal,TRIANGLE,RED);
	}
			
	plot("Filtered",*Filtered,NEW,BLACK);
	
	plot("Signal",*Signal,NEW,BLACK);	
	
	*/
	
}

function tradeTrend()
{
	
	TimeFrame = 1;
	
	vars Price = series(price());
	vars Trend = series(LowPass(Price,optimize(300,200,500)));

	Stop = optimize(4,2,10) * ATR(100);
	Trail = 3*ATR(100);

	vars MMI_Raw = series(MMI(Price,900));
	vars MMI_Smooth = series(LowPass(MMI_Raw,800));
	
	// This filters for trending period
	if(falling(MMI_Smooth)) {
		
		if(valley(Trend)) {
				enterLong(Lots);
				plot("Valley",*Trend,TRIANGLE,GREEN);
		}	else if(peak(Trend)) {
				enterShort(Lots);
				plot("Peak",*Trend,TRIANGLE,RED);
		} 
	
	}
		
		plot("BAND",*MMI_Smooth,NEW,BLUE);	
		
		plot("Trend",*Trend,NEW,BLACK);	

		
		
}

function run()
{
	//if (Train) set(PARAMETERS+SKIP3);  			// generate and use optimized parameters					// skip every 3rd week trading 
	//if (Test) set(PARAMETERS+SKIP1);  		// generate and use optimized parameters					// test on thrid week (skip 1 and 2)
	//if (Test) set(PARAMETERS+SKIP1+SKIP2);  	// generate and use optimized parameters					// test on thrid week (skip 1 and 2)
	//set(PARAMETERS+LOGFILE);  					// generate and use optimized parameters and factors
	//set(PARAMETERS);
	//DataSplit = 75;
	
	// Sliders
	Lots = slider(1,2000,500,10000,"Lots","Lots per Trade");
	Stop = PIP*slider(2,15,0,30,"Stop","Stop Loss in PIPs");
	Capital = slider(3,2000,1000,10000,"Capital","Capital ALlocated");
	
	setf(TrainMode,PEAK);
	
	set(PLOTNOW);
	
	setf(PlotMode,PL_ALL+PL_FINE+PL_FILE);
	
	PlotScale = 8;
	PlotWidth = 2000;
	PlotHeight1 = 700;
	PlotHeight2 = 200;
	
	NumCores = 2;										// use multiple cores (Zorro S only) all my cores !
	BarPeriod = 240;									// 1 hour bars
	LookBack = 2000;									// needed for Fisher()
	
	StartDate = 2016;
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