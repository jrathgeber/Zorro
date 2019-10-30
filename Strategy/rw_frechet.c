/* 

	PLOT FRECHET SIMILARITY
 
	Taken from : https://robotwealth.com/pattern-recognition-with-the-frechet-distance/
 
*/
 
function run()
{
	set(PLOTNOW);
	StartDate = 20150712;
	EndDate = 20150826;
	BarPeriod = 1440;
	LookBack = 100;
	asset("EUR/USD");
   
   vars Price = series(priceClose());
   static var Tri_Sym[9] = {1,8,2,7,3,6,5,4,0};
   static var Tri_Asym[14] = {1,3,5,8,6,4,2,5,7,6,4,3,6,0};
	
	// More
	var rectangle[5] = {1,2,1,2,0};
	var cup[10] = {6,3,2,1,1,1,2,3,6,0};
	var zigzag[5] = {1,7,2,8,0};
	var headShldrs[17] = {1,2,3,3,3,4,5,6,6,5,4,3,3,3,2,1,0};
	var cup[10] = { 6,3,2,1,1,1,2,3,6,0 };
	var triangle_symmetric[9] = {1,8,2,7,3,6,5,4,0};
	var triangle_assymetric[14] = {1,3,5,8,6,4,2,5,7,6,4,3,6,0};
		
 
   int i;
   for(i=10;i<=30;i+=10)
   {
   	plot(strf("Tri_Sym_%d", i),frechet(Price, i, MaxVal(Price,i) - MinVal(Price,i), Tri_Sym),NEW,RED);
   	plot(strf("Tri_Asym_%d", i),frechet(Price, i, MaxVal(Price,i) - MinVal(Price,i), Tri_Asym),0,BLUE);
   	plot(strf("Tri_Sym_Inv_%d", i),frechet(Price, i, -(MaxVal(Price,i) - MinVal(Price,i)), Tri_Sym),NEW,BLACK);
   	plot(strf("Tri_Asym_Inv_%d", i),frechet(Price, i, -(MaxVal(Price,i) - MinVal(Price,i)), Tri_Asym),0,GREEN);
   }
   
   PlotWidth = 800;
   PlotScale = 15;
   PlotHeight1 = 500;
   PlotHeight2 = 125;
}