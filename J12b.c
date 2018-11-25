// Workshop 6_1: Portfolio trading ///////////////////

function tradeCounterTrend()
{
	TimeFrame = 1;
	vars Price = series(price());
	vars Filtered = series(BandPass(Price,optimize(30,25,35),0.5));
	vars Signal = series(Fisher(Filtered,500));
	var Threshold = optimize(1,0.5,1.5,0.1);
	
	Stop = optimize(4,2,10) * ATR(100);
	Trail = 4*ATR(100);
	
	if(crossUnder(Signal,-Threshold)) 
		enterLong(1000); 
	else if(crossOver(Signal,Threshold)) 
		enterShort(1000);
}

function tradeTrend()
{
	TimeFrame = 1;
	vars Price = series(price());
	vars Trend = series(LowPass(Price,optimize(500,300,700)));

	Stop = optimize(4,2,10) * ATR(100);
	Trail = 0;

	vars MMI_Raw = series(MMI(Price,300));
	vars MMI_Smooth = series(LowPass(MMI_Raw,500));
	
	if(falling(MMI_Smooth)) {
		if(valley(Trend))
			enterLong(100);
		else if(peak(Trend))
			enterShort(100);
	}
}

function run()
{
	//if (Train) set(PARAMETERS+SKIP3);  			// generate and use optimized parameters
	//if (Test) set(PARAMETERS+SKIP1+SKIP2);  	// generate and use optimized parameters
	
	set(PARAMETERS+PRELOAD);

	//DataSplit = 75;
	
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
	}
	
// portfolio loop

	while(asset(loop("AUD/USD","GBP/USD","USD/CAD","EUR/USD","USD/JPY")))
	while(algo(loop("TRND","CNTR")))
	{
		if(Algo == "TRND") 
			tradeTrend();
		else if(Algo == "CNTR") 
			tradeCounterTrend();
	}
	
	PlotWidth = 600;
	PlotHeight1 = 300;
	set(TESTNOW);
}