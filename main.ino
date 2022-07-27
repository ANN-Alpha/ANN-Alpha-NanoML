// Author Vihaan Mehta 2022
/*These the the Intizialing parmeters for the network to function*/
// Importing the math library in order to perform the complex mathimatical functions 
#include <math.h>
// Identifiying the number of nodes for the Input, Middle, and Output layer
const int PatternCount = 10; const int Input_Nodes = 7;const int Hidden_Nodes = 8; const int Output_Nodes = 4;
// We are also defining the rate that the neural netowrk learns, along with the maximum weight and the success margin
const float LearningRate = 0.85; const float Momentum = 0.9; const float InitialWeightMax = 0.5; const float Success = 0.0004;
// This is an array for the combinations we will feed into the input nodes in order to train the network
const byte Input[PatternCount][Input_Nodes] = 
 {{ 1, 1, 1, 1, 1, 1, 0 }, { 0, 1, 1, 0, 0, 0, 0 },
  { 1, 1, 0, 1, 1, 0, 1 }, { 1, 1, 1, 1, 0, 0, 1 },
  { 0, 1, 1, 0, 0, 1, 1 }, { 1, 0, 1, 1, 0, 1, 1 }, 
  { 0, 0, 1, 1, 1, 1, 1 }, { 1, 1, 1, 0, 0, 0, 0 },  
  { 1, 1, 1, 1, 1, 1, 1 }, { 1, 1, 1, 0, 0, 1, 1 }}; 
// This is the expected output, or at least the output that we want the metwork to give off.
const byte Target[PatternCount][Output_Nodes] = 
 {{ 0, 0, 0, 0 }, { 0, 0, 0, 1 }, 
  { 0, 0, 1, 0 }, { 0, 0, 1, 1 }, 
  { 0, 1, 0, 0 }, { 0, 1, 0, 1 }, 
  { 0, 1, 1, 0 }, { 0, 1, 1, 1 }, 
  { 1, 0, 0, 0 }, { 1, 0, 0, 1 }};
// Here we are defining iteration variables, when the error difference shows up, and the random, error, and training cycle vars.
int i, j, p, q, r, RandomizedIndex[PatternCount], Print_Time; long TrainingCycle; float Rando, Error, Accumalation;
// These are the variables that make the nodes iterable and connect them as one whole layer
float Hidden[Hidden_Nodes],Output[Output_Nodes],HiddenWeights[Input_Nodes+1][Hidden_Nodes];
// These variabels store the change in vairables, hence the name Delta
float OutputWeights[Hidden_Nodes+1][Output_Nodes],HiddenDelta[Hidden_Nodes],OutputDelta[Output_Nodes];
float ChangeOutputWeights[Hidden_Nodes+1][Output_Nodes],ChangeHiddenWeights[Input_Nodes+1][Hidden_Nodes];
/*This is the setup loop which starts the serial monitor at 9600 buad and intizlizes the reporting variable*/
void setup(){ Serial.begin(9600); Print_Time = 1;}  
/*This is the main loop where all of the code will constanlty loop over and over again*/
void loop (){for( i = 0 ; i < Hidden_Nodes ; i++ ) {  // A for loop to iterate through hidden weights and put random values  
  for( j = 0 ; j <= Input_Nodes ; j++ ) { ChangeHiddenWeights[j][i] = 0.0; Rando = float(random(100))/100;
    HiddenWeights[j][i] = 2.0 * ( Rando - 0.5 ) * InitialWeightMax;}}
  // Another for loop to iterate through output weights and put random values 
  for( i = 0 ; i < Output_Nodes ; i ++ ) {
    for( j = 0 ; j <= Hidden_Nodes ; j++ ) {ChangeOutputWeights[j][i] = 0.0 ; Rando = float(random(100))/100;        
      OutputWeights[j][i] = 2.0 * ( Rando - 0.5 ) * InitialWeightMax;}} Show_on_shell();
  // Here we start the training for the network
  for( TrainingCycle = 1 ; TrainingCycle < 2147483647 ; TrainingCycle++) { Error = 0.0 ;
    // We are going through each training pattern in a random order to ensure the full and correct devolpment
    for( q = 0 ; q < PatternCount ; q++ ) { p = RandomizedIndex[q];
      /*Now we will calculate the different node activations*/
      // In this for loop we are interating through all of the hidden layers nodes and finding out whihc ones are activated
      for( i = 0 ; i < Hidden_Nodes ; i++ ) { Accumalation = HiddenWeights[Input_Nodes][i];
        for( j = 0 ; j < Input_Nodes ; j++ ) {Accumalation += Input[p][j] * HiddenWeights[j][i];} Hidden[i] = 1.0/(1.0 + exp(-Accumalation));}
      // Now here we calculate the output layer and it's activations, along with finindg out the error margins 
      for( i = 0 ; i < Output_Nodes ; i++ ) { Accumalation = OutputWeights[Hidden_Nodes][i] ;
        for( j = 0 ; j < Hidden_Nodes ; j++ ) {Accumalation += Hidden[j] * OutputWeights[j][i] ;} Output[i] = 1.0/(1.0 + exp(-Accumalation));   
        OutputDelta[i] = (Target[p][i] - Output[i]) * Output[i] * (1.0 - Output[i]);
        Error += 0.5 * (Target[p][i] - Output[i]) * (Target[p][i] - Output[i]) ;}
      // Here we are now going in a reverse way of the nueral network and look at the connections
      for( i = 0 ; i < Hidden_Nodes ; i++ ) { Accumalation = 0.0 ;
        for( j = 0 ; j < Output_Nodes ; j++ ) {Accumalation += OutputWeights[i][j] * OutputDelta[j] ;}
        HiddenDelta[i] = Accumalation * Hidden[i] * (1.0 - Hidden[i]);}
      // Now we are updating the Hidden weights to match the output
      for( i = 0 ; i < Hidden_Nodes ; i++ ) {     
        ChangeHiddenWeights[Input_Nodes][i] = LearningRate * HiddenDelta[i] + Momentum * ChangeHiddenWeights[Input_Nodes][i] ;
        HiddenWeights[Input_Nodes][i] += ChangeHiddenWeights[Input_Nodes][i] ;
        for( j = 0 ; j < Input_Nodes ; j++ ) { 
          ChangeHiddenWeights[j][i] = LearningRate * Input[p][j] * HiddenDelta[i] + Momentum * ChangeHiddenWeights[j][i];
          HiddenWeights[j][i] += ChangeHiddenWeights[j][i];}}
      // Now we are updating the Output weights to match the output
      for( i = 0 ; i < Output_Nodes ; i ++ ) {    
        ChangeOutputWeights[Hidden_Nodes][i] = LearningRate * OutputDelta[i] + Momentum * ChangeOutputWeights[Hidden_Nodes][i] ;
        OutputWeights[Hidden_Nodes][i] += ChangeOutputWeights[Hidden_Nodes][i] ;
        for( j = 0 ; j < Hidden_Nodes ; j++ ) {
          ChangeOutputWeights[j][i] = LearningRate * Hidden[j] * OutputDelta[i] + Momentum * ChangeOutputWeights[j][i];
          OutputWeights[j][i] += ChangeOutputWeights[j][i] ;}}}
    //This part is where we ouput the information every 1000 cycles for the trainging set.
    Print_Time = Print_Time - 1;
    if (Print_Time == 0) {Serial.println(); Serial.print ("  *Error* Margin = "); Serial.print(Error, 20); Show_on_shell();
      if (TrainingCycle==1){Print_Time = 999;} else {Print_Time = 1000;}} if( Error < Success ) break ;}
  Show_on_shell(); Serial.println (); Serial.println (); Print_Time = 1;}
//The show on shell function is the function that we use to display and output the information onto the serial monitor, it is counted as a void
void Show_on_shell()
 //Here we are cycling through the array of input sets in order to one by one print them out
 {for( p = 0 ; p < PatternCount ; p++ ) { Serial.println(); Serial.print ("  Input ");
    //In here we are cycling through the array of target sets for the network
    for( i = 0 ; i < Input_Nodes ; i++ ) {Serial.print (Input[p][i], DEC);Serial.print (" ");} Serial.print ("  Target ");
    //And the rest for these loops are just printing the networks outputs and the different variables such as the error margin
    for( i = 0 ; i < Output_Nodes ; i++ ) {Serial.print (Target[p][i], DEC); Serial.print (" ");}
    for( i = 0 ; i < Hidden_Nodes ; i++ ) {Accumalation = HiddenWeights[Input_Nodes][i];
    for( j = 0 ; j < Input_Nodes ; j++ ) {Accumalation += Input[p][j] * HiddenWeights[j][i] ;} Hidden[i] = 1.0/(1.0 + exp(-Accumalation)) ;}
    for( i = 0 ; i < Output_Nodes ; i++ ) {    Accumalation = OutputWeights[Hidden_Nodes][i] ;
      for( j = 0 ; j < Hidden_Nodes ; j++ ) {Accumalation += Hidden[j] * OutputWeights[j][i];} Output[i] = 1.0/(1.0 + exp(-Accumalation)) ; }
    Serial.print ("  Output "); for( i = 0 ; i < Output_Nodes ; i++ ) {Serial.print (Output[i], 5);}}}
