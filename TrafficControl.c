  //DE functie die bepaalt wat de volgende state wordt
void TrafficControl::calcNextState(){

  int stateWithHighestPriority = 0;
	int calculatedPriorityPerState[noStates]={0,0,0,0,0,0}, tempCalculatedPriorityPerSign[SAsize] = {0,0,0,0,0,0,0};
	int sum = 0;

	for(int i=0;i<SAsize;i++){
		sum+=psFA[i];
		}

	if(sum==0){
		if(currentState!=1)
			toBeState=1;
		if(currentState==1)
			toBeState=0;
		}

	else{
		//reset prioriteitswaardes van stoplichten die níet actief zijn (dus er staat niemand te wachten)
		for(int i=0;i<SAsize;i++){
			(pPriority[i])*=(psFA[i]);
			}

		//bereken de totale prioriteitswaarde van elke state
		for(int i=0;i<noStates;i++){
			sum=0;
		
			//tijdelijke array voor bereken van prioriteitswaarde per stoplicht, per state
			for(int j=0;j<SAsize;j++){
				tempCalculatedPriorityPerSign[j]=States[i][j]*(pPriority[j]);
				}
				/*
				//directe override als de wachttijd van gebruikers te hoog wordt
				if(tempCalculatedPriorityPerSign[j]>=(50*secfactor)){
					stateWithHighestPriority=i;
					toBeState = stateWithHighestPriority;
					break;
					}
				}*/

			//condenseer prioriteitswaarden per stoplicht, per state, naar samengevoegd per state.
			for(int j=0;j<SAsize;j++){
				sum+=tempCalculatedPriorityPerSign[j];}

			//sla deze op
			calculatedPriorityPerState[i]=sum;
		}

		//Kijk welke state de hoogste prioriteitswaarde heeft, zet deze als de volgende state
		//Controleer ook of de huidige state niet dezelfde is als de volgende state
		int highestPriorityValue=-1;
		for(int i=0;i<noStates;i++){
			if(calculatedPriorityPerState[i]>highestPriorityValue && i != currentState){
				highestPriorityValue=calculatedPriorityPerState[i];
				stateWithHighestPriority = i;
				}
		}

		toBeState = stateWithHighestPriority;

	    //reset alle sensorflags naar non actief
		for(int i=0;i<SAsize;i++){
			if(States[currentState][i]==1){
				psFA[i]=0;
				}
			}	
	}
};
