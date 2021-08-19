#include <bits/stdc++.h>
#include <fstream>
#include <algorithm>
using namespace std;
# define NO_OF_CHARS 256





void badCharHeuristic( string str, int size,
                        int badchar[NO_OF_CHARS])
{
    int i;


    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;


    for (i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}


int search( string txt, string pat)
{
    int m = pat.size();
    int n = txt.size();
    int counter=0;

    int badchar[NO_OF_CHARS];


    badCharHeuristic(pat, m, badchar);

    int s = 0;
    while(s <= (n - m))
    {
        int j = m - 1;


        while(j >= 0 && pat[j] == txt[s + j])
            j--;


        if (j < 0)
        {

            counter++;




            s += (s + m < n)? m-badchar[txt[s + m]] : 1;

        }

        else

            s += max(1, j - badchar[txt[s + j]]);
    }
    return counter;
}

/* Driver code */
int main()
{
    string txt;
    string pat;
    vector<string> wordsMain;
    vector<string> wordsTarget;
    vector<string> sentsMain;
    vector<string> sentsTarget;
    int counter = 0;
    int counterSents = 0;


    ifstream document;
    document.open(".\\target_doc.txt");
    document >> pat;
    document.close();

    ifstream infile { ".\\main_document2.txt" };
    string file_contents { istreambuf_iterator<char>(infile), istreambuf_iterator<char>() };

    txt = file_contents;


    ifstream doc { ".\\target_doc.txt" };
    string file_contents_target { istreambuf_iterator<char>(doc), istreambuf_iterator<char>() };

    pat = file_contents_target;


    using namespace std;

    string patCumle = pat;
    string txtCumle = txt;

    pat.erase(std::remove(pat.begin(), pat.end(), ','), pat.end());
    pat.erase(std::remove(pat.begin(), pat.end(), '.'), pat.end());
    txt.erase(std::remove(txt.begin(), txt.end(), ','), txt.end());
    txt.erase(std::remove(txt.begin(), txt.end(), '.'), txt.end());

    patCumle.erase(std::remove(patCumle.begin(), patCumle.end(), ','), patCumle.end());
    txtCumle.erase(std::remove(txtCumle.begin(), txtCumle.end(), ','), txtCumle.end());

    string line3 = patCumle;
    string line4 = txtCumle;

    string intermediate;

    stringstream check3(line3);
    stringstream check4(line4);

        while(getline(check3, intermediate, '.'))
    {
        sentsMain.push_back(intermediate);
    }

        while(getline(check4, intermediate, '.'))
    {
        sentsTarget.push_back(intermediate);
    }




    string line = pat;

    stringstream check1(line);




    while(getline(check1, intermediate, ' '))
    {
        wordsMain.push_back(intermediate);
    }



    string line2 = txt;

    stringstream check2(line2);

    while(getline(check2, intermediate, ' '))
    {
        wordsTarget.push_back(intermediate);
    }
    vector<int> similarSentIndexes;


    for(int a = 0; a < sentsMain.size(); a++) {
        //similarSentIndexes.reserve(sentsMain.size());


        for(int b = 0; b < sentsTarget.size(); b++) {


            if(sentsMain[a] == sentsTarget[b]) {
                similarSentIndexes.push_back(a);

                counterSents += 1;
            }
        }
    }




    int newCounter = 0;
    vector<int> indexesOfSent;
    string word;
    vector<int> counterBySent;
    int tempCounter = -1;
    counterBySent.reserve(sentsMain.size());

    for(int x = 0; x < sentsMain.size(); x++) {
        counterBySent.push_back(0);
    }



    for(int i=0;i<sentsMain.size(); i++){
        int tempCounterFS = 0;
        txt=sentsMain[i];




        if(find(similarSentIndexes.begin(), similarSentIndexes.end(), i) != similarSentIndexes.end()) {
            cout << endl;
        } else {
            for(int j=0; j<wordsTarget.size() - 3; j++){
                word=wordsTarget[j] + " " + wordsTarget[j+1] + " " + wordsTarget[j+2];
                tempCounter = newCounter;
                int searchTemp = search(txt,word);
                newCounter += searchTemp;
                tempCounterFS += searchTemp;
                counterBySent[i] =  tempCounterFS;
                if(tempCounter != newCounter) {
                        if(!(find(indexesOfSent.begin(), indexesOfSent.end(), i) != indexesOfSent.end())) {
                            indexesOfSent.push_back(i);

        }

            }
        }

        }



    }
    int percSent = (counterSents * 100)/sentsMain.size();
    cout << "\nCompletely similar sentence ratio: " << percSent << "%";


    for(int x = 0; x < similarSentIndexes.size(); x++) {
        cout << endl << "Completely similar sentence: " << sentsMain[similarSentIndexes[x]] << endl;
    }


    string tempstr;
    int simRateDoc;
    for(int h=0; h<indexesOfSent.size(); h++){
        int maxIndex = distance(counterBySent.begin(), max_element(counterBySent.begin(), counterBySent.end()));
        tempstr += sentsMain[maxIndex];
        int charsOftxt = txt.length();
        int charsofTemp = tempstr.length();
        simRateDoc = (charsOftxt*100)/charsofTemp;



    }
    cout <<endl <<  "Similarity rate of the document :" << simRateDoc << "%";


    for(int h=0; h<indexesOfSent.size(); h++){

            int maxIndex = distance(counterBySent.begin(), max_element(counterBySent.begin(), counterBySent.end()));
            counterBySent[maxIndex] = 0;

            if(h==0){

                cout << endl << "The most similar sentence: -" << sentsMain[maxIndex] ;
            }
            else if(h==1){
                cout << endl << "The second most similar sentence: -" << sentsMain[maxIndex] ;
            }
            else if(h==2){
                cout << endl << "The third most sentence: -" << sentsMain[maxIndex] ;
            }
            else if(h==3){
                cout << endl << "The fourth most similar sentence: -" << sentsMain[maxIndex] ;
            }
            else if(h==4){
                cout << endl << "The fifth most similar sentence: -" << sentsMain[maxIndex] ;

            }
    }




    return 0;
}


