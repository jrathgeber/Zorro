// Workshop 6_1: Portfolio trading ///////////////////


function run()
{
	//if (Train) set(PARAMETERS+SKIP3);  			// generate and use optimized parameters
	//if (Test) set(PARAMETERS+SKIP1+SKIP2);  	// generate and use optimized parameters
	
	set(PARAMETERS+FACTORS+LOGFILE);  				// generate and use optimized parameters and factors
	
	//set(PARAMETERS+PRELOAD);
	
	DataSplit = 0;
	
	set(PLOTNOW);
	
	PlotScale = 8;
	PlotWidth = 1000;
	PlotHeight1 = 750;
	PlotHeight2 = 80;
	
	NumCores = 2;										// use multiple cores (Zorro S only) all my cores !
	BarPeriod = 240;									// 1 hour bars
	
	LookBack = 2000;									// needed for Fisher()
	StartDate = 2010;
	
	EndDate = 2018; 									// fixed simulation period
	NumWFOCycles = 10; 								// activate WFO
	NumSampleCycles = 4;
	
	if(ReTrain) {
		UpdateDays = -1;								// update price data from the server 
		SelectWFO = -1;								// select the last cycle for re-optimization
		reset(FACTORS);								// don't generate factors when re-training
	}
	
    // portfolio loop

	// while(asset(loop("AUD/USD"))) {
		
	while(asset(loop("AUD/USD","GBP/USD","USD/CAD","EUR/USD","USD/JPY"))) {

		TimeFrame = 1;
	
		vars Price = series(price());
		vars Filtered = series(BandPass(Price,optimize(30,20,40,1),0.5));
		vars Signal = series(Fisher(Filtered,500));
		var Threshold = optimize(0.4,0.5,1.5,0.1);
		
		Stop = optimize(4,2,10, 1) * ATR(100);
		Trail = 1*ATR(150);
		
		if(crossUnder(Signal,-Threshold)) {
			enterLong(1000); 
			plot("Valley",*Signal,TRIANGLE,GREEN);
		}
		else if(crossOver(Signal,Threshold)) {
			enterShort(1000);
			plot("Peak",*Signal,TRIANGLE,RED);
		}
				
		plot("Filtered",*Filtered,NEW,BLACK);
		
		plot("Signal",*Signal,NEW,BLACK);	
	
	}

	set(TESTNOW+LOGFILE);
}