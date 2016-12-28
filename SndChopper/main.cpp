//============================================================================
// Name        : SndSample.cpp
// Author      : JMS3
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include "sndfile.h"
#include <math.h>
#include <time.h>
#include <string>
using namespace std;


int main(int argc, char** argv) {
    string fp;
    if(argc != 2) {
        cout << "Usege: " << argv[0] <<" [filename]" << endl;
        return -1;
    } else {
        fp = argv[1];
        cout << "processing: " << fp << endl;
    }
    srand ( time(NULL) );
    //load roar
    SF_INFO roarinfo;
    SNDFILE *roar = sf_open(fp.c_str(),SFM_READ,&roarinfo);
    
    if(!roar){
        cout<<"Can't open roar file"<<endl;
        return 1;
    }
    
    //create new file
    //const int format=SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    //const int channels=1;
    //const int sampleRate=44100;
    //const int sampleCount = sampleRate * 5; //5 seconds
    const char* outfilename="output.wav";
    int *buffer;
    SF_INFO outinfo;
    
    if (! (buffer = (int*)malloc (roarinfo.frames * sizeof (int))))
    {	cout<<"Malloc failed"<<endl;
        return 1;
    }
    
    memset (&outinfo, 0, sizeof (outinfo)) ;
    
    outinfo.samplerate = roarinfo.samplerate;
    outinfo.format = roarinfo.format;
    outinfo.channels = roarinfo.channels;
    
    SNDFILE *out = sf_open(outfilename,SFM_WRITE,&outinfo);
    
    if(!out){
        cout<<"Can't open roar file"<<endl;
        if(roar){
            sf_close(roar);
        }
        return 1;
    }
    
    //read write
    
    int i = 1;
    /*for (int k = 0 ; k < sampleCount ; k++){
     //sf_seek(roar,rand() % 20000,SEEK_SET);
     sf_read_int(roar,&i,1);
     buffer [k] = i;
     }
     */
    float cutrate = .125;
    float pieces = 8;
    int k = 0;
    int cuts = ceil(roarinfo.frames/roarinfo.samplerate)*pieces;
    for(int j = 0; j < (cuts); j++){
        for(int l=k; l<(k+roarinfo.samplerate*cutrate); l++){
            sf_read_int(roar,&i,1);
            buffer [l] = i;
        }
        k += roarinfo.samplerate*cutrate;
        sf_seek(roar,(rand() % cuts)*(roarinfo.samplerate*cutrate),SEEK_SET);
    }
    
    if (sf_write_int (out, buffer, outinfo.channels * roarinfo.frames) != outinfo.channels * roarinfo.frames){
        cout<<sf_strerror(out)<<endl;
    }
    
    //clean up
    sf_close(roar);
    sf_close(out);
    free(buffer);
    string wp = argv[0];
    cout << "Wrote file to " << wp << "/" << outfilename << endl;
    return 0;
}
