//var BarRange = 10;
var BarRange = 0.005;

//Range Bar
int checkBar(vars Open,vars High,vars Low,vars Close)
{
  if(Open[0] != Close[1]) {
    High[0] = max(Open[0],Close[1]);
    Low[0] = min(Open[0],Close[1]);
    Open[0] = Close[1];
  }
    
  if(High[0]-Low[0] >= BarRange)
    return 1;
  return 4;
}

function run()
{	
	set(PLOTNOW);
	StartDate = 2018;
	EndDate = 2019;
	BarPeriod = 1;	
	asset("EUR/USD");

	vars priceOpen = series(priceOpen());
	vars priceHigh = series(priceHigh());
	vars priceLow = series(priceLow());
	vars priceClose = series(priceClose());
		
	plot("Range",checkBar(priceOpen, priceHigh, priceLow, priceClose) ,NEW,RED);
	
}
