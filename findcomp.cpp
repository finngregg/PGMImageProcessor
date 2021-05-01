#include "PGMimageProcessor.cpp"

/* Main Method */
int main(int argc, char * argv[]){
    FNNGRE002::PGMimageProcessor final;
    string fileName = argv[1];
    final.loadImage(fileName);

    string minMax = "-s";
    string thresh = "-t";
    string printer = "-p";
    string write = "-w";

    int min = 3;
    int max;
    int threshold = 128;

    if(argc > 2){
        for(int i = 2; i < argc; i++){
            
            string current = argv[i];

            if(current.compare(minMax) == 0){
                string tempMin = argv[i+1];
                string tempMax = argv[i+2];

                stringstream one(tempMin);
                one >> min;

                stringstream two(tempMax);
                two >> max;

                final.extractComponents(threshold, min);
                final.filterComponentsBySize(min, max);
            }
            if(current.compare(thresh) == 0){
                string tempThresh = argv[i+1];

                stringstream three(tempThresh);
                three >> threshold;

                final.extractComponents(threshold, min);
            }
            if(current.compare(printer) == 0){
                int total = final.getComponentCount();
                int biggest = final.getLargestSize();
                int smallest = final.getSmallestSize();
                cout << "Total ConnectedComponents: " << total << "\nBiggest ConnectedComponent: " << biggest << "\nSmallest ConnectedComponent: " << smallest << "\n";
                final.printAllData();
            }
            if(current.compare(write) == 0){
                final.writeComponents(argv[i+1]);
            }
        }
    }
    return 0;
}