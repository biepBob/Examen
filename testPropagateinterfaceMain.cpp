// This program is used for testing the 'propagate' class

#include<iostream>
using std::cout;
#include <ctime>
#include <cstdlib>
#include <string>
using std::string;
using std::to_string;
#include <iterator>
using std::ostream_iterator;
#include <vector>
using std::vector;
#include <algorithm>
using std::copy;

#include "propagate.h"
#include "propagateinterface.h"

int main ()
{
    cout << "Beginning of program 'TestPropagate'." << '\n';

    //========================================================================================
    //// Create weights and biases for a test network with 'Nlayers' layers of neurons ////
    // Ninputs: number of inputs for network, Nlayers: number of layers in the network
    const int Ninputs = 784;
    const int Nlayers = 2;
    const int layer[Nlayers+1] = {Ninputs,150,10}; // layer[#] contains the amount of neurons in each layer # 
  							// except the first layer, it is the input layer which doesn't contain neurons
      
     const vector<int> nNeurons (layer+1, layer + sizeof(layer) / sizeof(int)); 
    
    cout << "A network is contructed with " << Nlayers << " layers of neurons." << '\n';
    cout << "The number of neurons in the layers are: " << '\n';
    copy(nNeurons.begin(),nNeurons.end()-1,ostream_iterator<int>(cout,","));
    cout << nNeurons.back() << '\n';
    cout << "The network must process " << Ninputs << " inputs." << '\n';
    //==========================================================================================

	string EvalImageString="t10k-images.idx3-ubyte";				// Load testbatch.
	string EvalLabelString="t10k-labels.idx1-ubyte";

	string TrainImageString="train-images.idx3-ubyte";				// Load trainingsbatch.
	string TrainLabelString="train-labels.idx1-ubyte";


        float eta = 2;
        int miniBatchSize = 20000;
    
    	propagateinterface propInter;
	propInter.setEta(eta);
	propInter.setEvaluationImages(EvalImageString);
	propInter.setEvaluationNumbers(EvalLabelString);
	propInter.setTrainingImages(TrainImageString);
	propInter.setTrainingNumbers(TrainLabelString);
	propInter.setMiniBatchSize(miniBatchSize);
        propInter.setLoadNetworkPath("tralalala.csv");
        propInter.setNumberOfNeuronsPerLayer(nNeurons);
        propInter.setThreshold(.2);
        propInter.useRooT(false);
        propInter.useLoadNetwork(false);
	propInter.makePropagate();
        propInter.propagateNEpochs(1);
	propInter.saveNetwork("Propproprop.csv");
        vector<vector<vector<float>>> Raw = propInter.getRawHistogram();
	vector<int> iterations = propInter.getIterations();
	vector<float> evaluationError = propInter.getEvaluationError();
	vector<float> trainingError = propInter.getTrainingError();
        vector<float> Acc = propInter.getAccuracy();
        vector<float> sens = propInter.getSensitivity();
        vector<float> Spec = propInter.getSpecificity();
        vector<float> Precision = propInter.getPrecision();
    
	cout << "Iterations: " << endl;
	copy(iterations.begin(),iterations.end(),ostream_iterator<float>(cout,","));
	cout << "\n";
	cout << "Evaluation Error: " << endl;
        copy(evaluationError.begin(),evaluationError.end(),ostream_iterator<float>(cout,","));
        cout << "\n";
	cout << "Training Error: " << endl;
        copy(trainingError.begin(),trainingError.end(),ostream_iterator<float>(cout,","));
        cout << "\n";
        cout << "Accuracy: " << endl;
        copy(Acc.begin(),Acc.end(),ostream_iterator<float>(cout,","));
        cout << "\n";
        cout << "Sensitifity: " << endl;
        copy(sens.begin(),sens.end(),ostream_iterator<float>(cout,","));
        cout << "\n";
        cout << "Specificity: " << endl;
        copy(Spec.begin(),Spec.end(),ostream_iterator<float>(cout,","));
        cout << "\n";
        cout << "Precision: " << endl;
        copy(Precision.begin(),Precision.end(),ostream_iterator<float>(cout,","));
        cout << "\n";
	cout << "End of program 'TestPropagte'." << '\n';
	return 0;
}

