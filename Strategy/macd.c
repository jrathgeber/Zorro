function run(){
	
	set(LOGFILE);
	
	int FastPeriod = 8;
	int SlowPeriod = 21;
	int SignalPeriod = 9;
	
	BarPeriod = 15;
	vars Close = series(priceClose());
	//TimeFrame = 1;
	
	MACD(Close,FastPeriod,SlowPeriod,SignalPeriod);
	vars MainLine = series(rMACD);
	vars SignalLine = series(rMACDSignal);
	vars Hist = series(rMACDHist);
	
	MACD(Close,FastPeriod*2,SlowPeriod*2,SignalPeriod*2);
	vars MainLine30 = series(rMACD);
	vars SignalLine30 = series(rMACDSignal);
	vars Hist30 = series(rMACDHist);
	
	MACD(Close,FastPeriod*4,SlowPeriod*4,SignalPeriod*4);
	vars MainLine60 = series(rMACD);
	vars SignalLine60 = series(rMACDSignal);
	vars Hist60 = series(rMACDHist);
	
	MACD(Close,FastPeriod*16,SlowPeriod*16,SignalPeriod*16);
	vars MainLine240 = series(rMACD);
	vars SignalLine240 = series(rMACDSignal);
	vars Hist240 = series(rMACDHist);
	
	

if(crossOver(MainLine,SignalLine) && MainLine30[0] > SignalLine30[0]
   && MainLine30[0] > SignalLine60[0] && MainLine240[0] > SignalLine240[0]){

    
exitShort();
    enterLong();
    }

if(crossUnder(MainLine,SignalLine) && MainLine30[0] < SignalLine30[0]
   && MainLine30[0] < SignalLine60[0] && MainLine240[0] < SignalLine240[0]){


exitLong();
    enterShort();
    }

            
}
