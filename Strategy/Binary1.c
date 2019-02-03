var objective()
{
	return ((var)(NumWinLong+NumWinShort))/(NumLossLong+NumLossShort);
}


function run()
{
	BarPeriod = 5;
	LookBack = 100;
	NumWFOCycles = 20;
	NumCores = -1;
	
	set(BINARY);
	WinPayout = 85;
	LossPayout = 0;

	set(PARAMETERS);
	int TimePeriod = optimize(20,10,100);
	var Threshold = 0.01*(HH(TimePeriod)-LL(TimePeriod));

	if(NumOpenLong+NumOpenShort == 0) 
	{
		LifeTime = 1;
		if(HH(TimePeriod) - priceClose() < Threshold)
			enterShort();
		else if(priceClose() - LL(TimePeriod) < Threshold)
			enterLong();
	}
}