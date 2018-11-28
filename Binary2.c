void main()
{
	int BuyX,BuyY,SellX,SellY; // button coordinates

// open the browser	
	printf("\nOpening the broker's website...");
	exec("http://financial-hacker.com/shark.htm",0,1);

// get the position of the Buy button
	printf("\nRight click on [Buy]!");
	while(wait(50)) {
		int button = mouse(&BuyX,&BuyY,window(""));
		if(button & 2) break;
	}
// wait until right mouse key released	
	while(wait(50)) {
		int x,y,button = mouse(&x,&y,0);
		if(!(button & 2)) break;	
	}

// get the position of the Sell button	
	printf("\nRight click on [Sell]!");
	while(wait(50)) {
		int button = mouse(&SellX,&SellY,window(""));
		if(button & 2) break;
	}
// wait until right mouse key released	
	while(wait(50)) {
		int x,y,button = mouse(&x,&y,0);
		if(!(button & 2)) break;	
	}

// send mouse clicks to Buy and Sell	
	printf("\nI will now click on [Buy]!");
	keys("[click %d,%d]",BuyX,BuyY);
	printf("\nI will now click on [Sell]!");
	keys("[click %d,%d]",SellX,SellY);
	printf("\nDone!");
}