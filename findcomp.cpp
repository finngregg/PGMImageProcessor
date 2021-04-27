#include "PGMimageProcessor.cpp"

/* Main Method */
int main(int argc, char * argv[]){
    FNNGRE002::PGMimageProcessor final;
    string fileName = argv[1];
    final.loadImage("chess.pgm");
    final.extractComponents(10,3);
    final.writeComponents("imageOut.pgm");
    return 0;
}


