#include <iostream>
#include <fstream>
#include <conio.h>
#include <conio2.h>
#include <conio2.c>
#include <bits/stdc++.h>

using namespace std;

char lower_alpha[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
vector<string> suggestions;
int automatic = 1;

int incorrectArrangement(string input)
{
    string line;
    int found = 0;
    ifstream words ("words.txt");
    if (words)
    {
        while(getline(words,line))
        {
            string Xinput = input, Ninput, permutations, Tinput, Tline, Nline, Xline = line;
            int len = Xinput.size(), flen = line.size();
            if (len == flen)
            {
                for (int i=1; i<Xinput.length(); i++)
                    Ninput.push_back(input[i]);
                for (int i = 1; i < flen; i++)
                    Nline.push_back(Xline[i]);
                Xinput.resize(1);
                Xline.resize(1);
                sort(Nline.begin(),Nline.end());
                sort(Ninput.begin(), Ninput.end());
                Tinput = Xinput + Ninput;
                Tline = Xline + Nline;
                if (Tinput == Tline)
                {
                    found = 1;
                    suggestions.push_back(line);
                    break;
                }
            }
        }
        words.close();
    }
    else
    {
        cout<<endl<<"Unexpected error occurred......."<<endl;
    }
    return found;
}

//function to show correct spelling if extra character is present in the given word
int exchangedCharacters (string input)
{
    string line, Xinput;
    int found = 0;
    ifstream words ("words.txt");
    if (words)
    {
        while (getline(words,line))
        {
            int len = input.size(), flen = line.size();
            if (len == flen)
            {
                for (int i = len-1; i >= 0 ; i--)
                {
                    Xinput = input;
                    Xinput[i] = lower_alpha[0];
                    for (int j=0; j<26; j++)
                    {
                        if (Xinput == line)
                        {
                            found == 1;
                            suggestions.push_back(line);
                            break;
                        }
                        Xinput[i] = lower_alpha[j+1];
                    }
                    if (found == 1 ) break;
                    else continue;
                }
            }
        }
        words.close();
    }
    else cout<<"\nUnexpected error occurred"<<endl;
    return found;
}

//function to show correct spelling when there is a missing character in the given word.
int missingCharacter (string input)
{
    string Xinput, line, Tinput, Tline, Xline;
    int found = 0;
    ifstream words ("words.txt");
    if (words)
    {
        while (getline(words,line))
        {
            int len = input.size(), flen = line.size();
            for (int i = 0; i < 26; i++)
            {
                Xinput = input;
                Xline = line;
                Xinput.resize(len+1,'a');
                Xinput[len] = lower_alpha[i];
                len = Xinput.size();
                string Ninput, Nline;
                if (len == flen)
                {
                    for (int j = 1; j <=len; j++)
                        Ninput.push_back(Xinput[j]);
                    for (int j = 1; j <= flen; j++)
                        Nline.push_back(Xline[j]);
                    Xinput.resize(1);
                    Xline.resize(1);
                    sort(Nline.begin(),Nline.end());
                    sort(Ninput.begin(),Ninput.end());
                    Tinput = Xinput + Ninput;
                    Tline = Xline + Nline;
                    if (Tinput == Tline)
                    {
                        found = 1;
                        suggestions.push_back(line);
                        break;
                    }
                }
                if (found == 1) break;
            }
            if (found == 1) break;
        }
        words.close();
    }
    else
    {
        cout<<"\nUnexpected error occurred\n";
    }
    return found;
}

//function to show correct spelling of there is an extra character in given word.
int extraCharacter (string input)
{
    string Xinput, line, Ninput, Tinput;
    int found = 0;
    ifstream words ("words.txt");
    if (words)
    {
        while (getline(words,line))
        {
            int len = input.size(), flen = line.size();
            if ((len-1) == flen)
            {
                for (int i = 1; i < len; i++)
                {
                    Xinput = input;
                    Xinput.erase(Xinput.begin()+i);
                    if (Xinput == line)
                    {
                        found = 1;
                        suggestions.push_back(line);
                        break;
                    }

                }
            }
        }
        words.close();
    }
    else
    {
        cout<<"\nUnexpected error occurred\n";
    }
    return found;
}

//function to show right spelling when given word has wrong extra character and right one is missing.
int mixedExtraMissing (string input)
{
    string Xinput, line, Xline;
    int found = 0;
    ifstream words ("words.txt");
    if (words)
    {
        while (getline(words,line))
        {
            int len = input.size(), flen = line.size();
            if (len == flen)
            {
                for (int i = 1; i < len; i++)
                {
                    for (int j = 0; j < 26; j++)
                    {
                        Xinput = input; Xline = line;
                        Xinput.erase(Xinput.begin()+i);
                        Xinput.resize(len, 'a');
                        Xinput[len-1] = lower_alpha[j];
                        sort(Xinput.begin()+1,Xinput.end());
                        sort(Xline.begin()+1,Xline.end());
                        if (Xinput == Xline)
                        {
                            found = 1;
                            suggestions.push_back(line);
                            break;
                        }
                    }
                    if (found == 1) break;
                }
                if (found == 1) break;
            }
        }
        words.close();
    }
    return found;
}

int getInt() {
    int num = getch();
    if (num>=48&&num<=57) {
        return num-48;
    } else {
        return -1;
    }
}



int spellCheck(string input) {
    int len,flen,correct=0;
    string line;
    len = input.length();
    suggestions.clear();
    int totalLength = 0;

    transform(input.begin(), input.end(), input.begin(), ::tolower);
    //cout<<input;
    ifstream words;
    words.open("words.txt");
    if(words) {
        while (getline(words,line))
        {
            flen = line.length();
            if (len==flen)
            {
                if (line==input)
                {
                    correct=1;
                    return -1;
                }
                else continue;
            }
            else continue;
        }
        words.close();

        if (correct==0) {
            int missing = 0, extra = 0, mixed = 0, incorrect = 0, exchanged = 0;
//            cout<<endl<<"Possible right spellings are given below:- "<<endl<<endl;
            extra = extraCharacter(input);
            exchanged = exchangedCharacters(input);
            mixed = mixedExtraMissing(input);
            incorrect = incorrectArrangement(input);
            missing = missingCharacter(input);

            int prevLength = len;
            int originalX = c_wherex(), originalY =c_wherey();
            int i=1;
            for(auto suggestion: suggestions) {
                c_gotoxy(c_wherex()-prevLength, c_wherey()+1);
                prevLength = suggestion.length()+3;
                if (i>=10) {
                    prevLength++;
                }
                totalLength+= prevLength;
                cout<<i++<<". "<<suggestion;
            }
            if (suggestions.size()==0) {
                return -1;
            }
            int finalX = c_wherex(), finalY = c_wherey();
//            cout<<finalX<<" "<<finalY<<" "<<originalX<<" "<<originalY;
            c_gotoxy(originalX, originalY);
            int choice;
            choice = getInt();
            if (choice)
            if (suggestions.size()/10>0) {
                int inp = getInt();
                if(inp>=0&&inp<=9) {
                    choice = choice *10 + (getInt());
                }

            }
            if (suggestions.size()/100>0) {
                int inp = getInt();
                if(inp>=0&&inp<=9) {
                    choice = choice *10 + (getInt());
                }
            }
            if (suggestions.size()/1000>0) {
                int inp = getInt();
                if(inp>=0&&inp<=9) {
                    choice = choice *10 + (getInt());
                }
            }
            int currX = c_wherex(), currY = c_wherey();
//            cout<<finalX<<" "<<finalY<<" "<<currX<<" "<<currY;
            while (currY!=finalY) {
                cout<<(char)255;
                currX = c_wherex();
                currY = c_wherey();
            }
            while (currX!=finalX) {
                cout<<(char)255;
                currX = c_wherex();
                currY = c_wherey();
            }
            c_gotoxy(originalX, originalY);
            if (choice<=suggestions.size() && choice>0) {
                return choice - 1;
            } else {
                if(automatic==1) {
                    return 0;
                } else {
                    return -1;
                }
            }
//            if (missing == 0 && extra == 0 && mixed == 0 && incorrect == 0 && exchanged == 0)
//            {
//                cout<<endl<<"No such word exist"<<endl;
//            }
        }
    } else {
        cout<<"Not able to open words.txt"<<endl;

    }
//    cout<<endl<<"Press any key to continue..."<<endl<<endl;
//    for(int i=0;i<totalLength;i++) {
//        cout<<"\b";
//    }

}

int saveDocument(string documentText) {
    cout<<endl<<endl<<"Enter the document name (Already existing files will be overwritten)";
    string documentName, fileName;
    cin>>fileName;
    ofstream save;
    save.open(fileName + ".txt", ios::out);
    save<<documentText;
    save.close();
    system("cls");
    cout<<documentText;
    cout<<endl<<"Saved Successfully. "<<fileName<<".txt" <<" Press any key to continue!";
    getch();
    cout<<endl;

}

void editor() {
        string documentText = "", word = "";
        char ch;
        while (word !="--exit") {
            if (word=="--save") {
                saveDocument(documentText);
                word = "";
            }
            if (word=="--auto") {
                automatic = 1;
                word = "";
            }
            if (word=="--manual") {
                automatic = 0;
                word = "";
            }
            ch = getch();
            if (ch=='\b') {
                documentText += word;
                documentText.erase(documentText.length()-1);
                word = "";
                cout<<"\b";
                cout<<(char)255;
                cout<<"\b";
            } else if (ch=='\r') {
                if (word.length()!=0) {
                    spellCheck(word);

                }
                word += '\n';
                cout<<ch<<endl;
                documentText += word;
                word = "";
            } else if ( (ch == 32 || (!(ch>='A'&&ch<='Z') && !(ch>='a'&&ch<='z'))) && ch!='-' ) {
                int choice;
                if (word.length()!=0) {
                    choice = spellCheck(word);
                    if(choice>=0) {
                        for (int i=0;i<word.length();i++){
                            cout<<'\b';
                            cout<<(char)255;
                            cout<<'\b';
                        }
                        word = suggestions[choice];
                        cout<<word;
                    }
                }
                cout<<ch;
                word += ch;
                documentText += word;
                if(ch==32) {
                    word = "";
                }

            } else {

                word+=ch;
                cout<<ch;
            }

        }
        cout<<endl<<"Do you want to save the document? [Y/N]";
        char saveOrNot;
        cin>>saveOrNot;
        if ('y'==tolower(saveOrNot)) {
            saveDocument(documentText);
        }
        cout<<endl<<endl<<endl<<documentText;
        getch();
};

int main() {
    cout<<"Welcome to AutoCorrect 1.0"<<endl<<endl
    	<<"Made By : Harshit Gupta"<<endl<<endl
        <<"1. Enter --save to save as .txt document"<<endl<<endl
        <<"2. Enter --exit to exit with or without saving"<<endl<<endl
        <<"3. Enter --auto to enable aggressive auto correction"<<endl<<endl
        <<"4. Enter --manual to disable aggressive auto correction"<<endl<<endl
        <<"Press any key to open editor";
    getch();
    system("cls");
    editor();

    return 0;
}
