/* 

	FRECHET TRADING
 
	Taken from : https://robotwealth.com/pattern-recognition-with-the-frechet-distance/
 
*/
 
var threshold = 30;
 
function run()
{
	set(PLOTNOW);
	StartDate = 2007;
	EndDate = 2017;
	BarPeriod = 1440;
	AssetList = "AssetsIB";
	if(is(INITRUN)) assetHistory("GLD", FROM_AV);
	asset("EUR/USD");
   
   vars Price = series(priceClose());
   var Tri_Asym[14] = {1,3,5,8,6,4,2,5,7,6,4,3,6,0};
 
   int i;
   for(i=10;i<=50;i+=10)
   {
   	algo(strf("_%d_Asym", i));
   	if(frechet(Price, i, MaxVal(Price,i)-MinVal(Price,i), Tri_Asym) > threshold)
		{
			Entry = 0.25*ATR(20);
			EntryTime = min(i, 10);
			LifeTime = min(i, 20);
			if(NumOpenLong == 0) enterLong();
			if(NumOpenShort == 0) enterShort();
		}
   }
   
   PlotWidth = 800;
   PlotHeight1 = 500;
   PlotHeight2 = 125;
}