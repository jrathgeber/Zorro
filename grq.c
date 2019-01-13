function run()
{
  Stop = 10*ATR(100);
  TakeProfit = 1*ATR(100);
// open new trade at random after last trade hit its target
  if(NumOpenTotal == 0) { 
    if(random() < 0)
      enterShort();
    else 
      enterLong();
  }
}