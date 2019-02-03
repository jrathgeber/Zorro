function run()
{
  StartDate = 2005;   // use > 10 years data
  BarPeriod = 1440;   // 1 day
  BarZone = WET;      // West European midnight
  BarOffset = 1;      // trade at day start
  Weekend = 1;        // separate Friday and Sunday bars
  LookBack = 3;       // only 3 bars needed
  NumWFOCycles = 10;   // mandatory for machine learning functions
 
  set(RULES+TESTNOW); // generate rules, test after training
  set(LOGFILE+PLOTNOW);
  setf(PlotMode,PL_ALL+PL_FINE+PL_FILE);
  
  if(Train) Hedge = 2; // allow long + short
  LifeTime = 5;        // = one week
  MaxLong = MaxShort = 1; // only 1 open trade
 
 while(asset(loop("USD/CAD","EUR/USD")))
 {
  if(adviseLong(PATTERN+2,0,
    priceHigh(2),priceLow(2),priceClose(2),
    priceHigh(1),priceLow(1),priceClose(1),
    priceHigh(1),priceLow(1),priceClose(1),
    priceHigh(0),priceLow(0),priceClose(0)) > 40)
    enterLong();
  if(adviseShort() > 40)
    enterShort();
 }
 
 }