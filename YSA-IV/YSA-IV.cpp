#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
double sigmoid(double x);
double tanh(double x);
double sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}
double tanh(double x)
{
    return tanh(x);
}

int main()
{
    using namespace std;

    ifstream in("YSA-IV/Oz.csv");

    string line, field;
    int GirisKatmanSayisi = 7;
    int CikisKatmanSayisi = 2;
    int LayerI;
    int LayerII;
    int iterasyon = 1000;
    

    vector< vector<string> > Input;  // 2D array
    vector< vector<double> > Dinput; // İnteger array
    vector< vector<double> > ILayer;  //  2D array
    vector< vector<double> > IILayer;  //  2D array
    vector< vector<double> > IIILayer;  //  2D array
    vector<string> v;                // array of values for one line only

    //************Weight******************
    vector< vector<double> > WeightI;  //  2D array
    vector< vector<double> > WeightII;  //  2D array
    vector< vector<double> > WeightIII;  //  2D array
   
    cout << "1. Noron Katmanini Giriniz=";
    cin >> LayerI;
    cout << "2. Noron Katmanini Giriniz=";
    cin >> LayerII;
   

    WeightI.resize(GirisKatmanSayisi);
    WeightII.resize(LayerI);
    WeightIII.resize(LayerII);
    for (size_t i = 0; i < LayerI; i++)
    {
        for (size_t j = 0; j < WeightI.size(); j++)
        {
            double r = ((double)rand() / (RAND_MAX));
            WeightI[i].push_back(r);
            cout << WeightI[i][j] << "|"; // (separate fields by |)
        }

    }
    
    for (size_t i = 0; i < LayerI; i++)
    {
        for (size_t j = 0; j < LayerII; j++)
        {
            double t = ((double)rand() / (RAND_MAX));
            WeightII[i].push_back(t);
        }

    }
   
    for (size_t i = 0; i < CikisKatmanSayisi; i++)//2
    {
        for (size_t j = 0; j < LayerII; j++)//2
        {
            double l = ((double)rand() / (RAND_MAX));
            WeightIII[i].push_back(l);

        }
    }
    
   
    ILayer.resize(LayerI);
    IILayer.resize(LayerII);
    IIILayer.resize(CikisKatmanSayisi);
    for (size_t i = 0; i < ILayer.size(); i++)
    {
        ILayer[i].push_back(0);

    }
    for (size_t i = 0; i < IILayer.size(); i++)
    {
        IILayer[i].push_back(0);

    }
    for (size_t i = 0; i < IIILayer.size(); i++)
    {
        IIILayer[i].push_back(0);

    }
    while (getline(in, line))    // get next line in file
    {
        v.clear();
        stringstream ss(line);
        
        while (getline(ss, field, ','))  // break line into comma delimitted fields
        {
            v.push_back(field);  // add each field to the 1D array

        }
        
        Input.push_back(v);  // add the 1D array to the 2D array
        
        
    }
 
    // print out what was read in
    Dinput.resize(Input.size());
    
    for (size_t i = 0; i < Input.size(); ++i)
    {
        for (size_t j = 0; j < Input[i].size(); ++j)
        {
            Dinput[i].push_back(atof(Input[i][j].c_str()));
            cout << Dinput[i][j] << "|"; // (separate fields by |)
        
        }
        cout << "\n";
    }
    // CH1
    
        for (size_t i = 0; i < Dinput.size(); i++)//for datas
        {
           
            for (size_t t = 0; t < LayerI; t++)//5
            {

                for (size_t l = 0; l < GirisKatmanSayisi; l++)//ILayer for layer //7
                {
                    ILayer[t][0] = (WeightI[t][l] * Dinput[i][l]) + ILayer[t][0];
                }

            }


            for (size_t i = 0; i < ILayer.size(); i++)
            {
                ILayer[i][0] = sigmoid(ILayer[i][0]);
            }

            for (size_t t = 0; t < LayerII; t++)
            {
                for (size_t l = 0; l < LayerI; l++)
                {
                    IILayer[t][0] = (ILayer[l][0] * WeightII[t][l]) + IILayer[t][0];

                }
            }
            for (size_t i = 0; i < IILayer.size(); i++)
            {
                IILayer[i][0] = sigmoid(IILayer[i][0]);

            }
            for (size_t t = 0; t < CikisKatmanSayisi; t++)//2
            {
                for (size_t l = 0; l < LayerII; l++)//5
                {
                    IIILayer[t][0] = (WeightIII[t][l] * IIILayer[l][0]) + IIILayer[t][0];
                }

            }

            for (size_t i = 0; i < IIILayer.size(); i++)
            {
                IIILayer[i][0] = sigmoid(IIILayer[i][0]);

            }
            
            //Error Values
            double Error_I = 0;
            double Error_0 = 0;
            Error_I = 0.5 * (pow(1 - IIILayer[1][0], 2));
            Error_0 = 0.5 * (pow(0 - IIILayer[0][0], 2));
            cout.precision(5);
            cout << "\n\n0.Error Values(predictable) = " << Error_0 << "\n\n 1.Error Values(default)= " << Error_I << endl;

        }
    

    return 0;
}




