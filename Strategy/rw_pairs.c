/* 
Price-based spread trading in Zorro
*/
 
#define Y "NAS100"
#define X "SPX500"
#define MaxTrades 5
#define Spacing 0.5
// #define COSTS
 
int ZSLookback = 100;
int Portfolio_Units = 100; //units of the portfolio to buy/sell (more --> better fidelity to dictates of hedge ratio)
 
var calculate_spread(var hedge_ratio)
{
  var spread = 0;
  asset(Y);
#ifndef COSTS  
  Spread = Commission = Slippage = 0;
#endif
  spread += priceClose();
  
  asset(X); 
#ifndef COSTS
  Spread = Commission = Slippage = 0;
#endif 
  spread -= hedge_ratio*priceClose();
  
  return spread;
}
 
function run()
{
	set(PLOTNOW);
	setf(PlotMode, PL_FINE);
	StartDate = 20100101;
	EndDate = 20191231;
	BarPeriod = 1440;
	LookBack = ZSLookback;
	MaxLong = MaxShort = MaxTrades;
	
	// load data from Alpha Vantage in INITRUN
	if(is(INITRUN)) 
	{
		string Name;
		while(Name = loop(Y, X))
		{
			assetHistory(Name, FROM_AV);
		}
	}
	
	// calculate spread
	var beta = 0.4;	
	vars spread = series(calculate_spread(beta));
	vars ZScore = series(zscore(spread[0], 100));
	
	// set up trade levels
	var Levels[MaxTrades]; 
	int i;
	for(i=0; i<MaxTrades; i++)
	{
		Levels[i] = (i+1)*Spacing;
	}
	
// -------------------------------
// trade logic 
// -------------------------------
 
	// exit on cross of zero line
	if(crossOver(ZScore, 0) or crossUnder(ZScore, 0)) 
	{
		asset(X);
		exitLong(); exitShort();
		asset(Y);
		exitLong(); exitShort();
	}
	
	// entering positions at Levels
	for(i=0; i<=MaxTrades; i++)
	{
		if(crossUnder(ZScore, -Levels[i])) // buying the spread (long Y, short X)
		{
			asset(Y);
			Lots = Portfolio_Units;
			enterLong();
			asset(X);
			Lots = Portfolio_Units * beta;
			enterShort();
		}
		if(crossOver(ZScore, Levels[i])) // shorting the spread (short Y, long X)
		{
			asset(Y);
			Lots = Portfolio_Units;
			enterShort();
			asset(X);
			Lots = Portfolio_Units * beta;
			enterLong();
		}
	}
	
	// exiting positions at Levels
	for(i=1; i<=MaxTrades-1; i++)
	{
		if(crossOver(ZScore, -Levels[i])) // covering long spread (exiting long Y, exiting short X)
		{
			asset(Y);
			exitLong(0, 0, Portfolio_Units);
			asset(X);
			exitShort(0, 0, Portfolio_Units * beta);
		}
		if(crossUnder(ZScore, Levels[1])) // covering short spread (exiting short Y, exiting long X)
		{
			asset(Y);
			exitShort(0, 0, Portfolio_Units);
			asset(X);
			exitLong(0, 0, Portfolio_Units * beta);
		}
	}
	
 
	// plots
	if(!is(LOOKBACK))
	{
		plot("zscore", ZScore, NEW, BLUE);
		int i;
		for(i=0; i<MaxTrades; i++)
		{
			plot(strf("#level_%d", i), Levels[i], 0, BLACK);
			plot(strf("#neglevel_%d", i), -Levels[i], 0, BLACK);
		}	
		plot("spread", spread, NEW, BLUE);
	}
}