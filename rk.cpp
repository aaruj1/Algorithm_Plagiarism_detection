#include<stdio.h> 
#include<string.h> 
#include <sstream>
#include <iostream>
#include<fstream>
#include<string> 
 
using namespace std; 
float rabinKarp(char seq[], char arr[], int line , int sent_line) 
{ 
    //seq is the sentence of the input text and arr corresponds to lines of the output file.
    int m = 121;
    int d = 256; 
    int y; 
	int len1 = strlen(seq); 
    int hash_1 = 0; 
	int len2 = strlen(arr);
    int hash_2 = 0;
    int h = 1; 
    int l = 0;
  
    for (int x = 0; x < len1-1; x++) 
	{
		h = (h*d)%m;
	}  
    
	//For calculating the hash code value.
    for (int x = 0; x < len1; x++) 
    { 
        hash_1 = (d*hash_1 + seq[x])%m;
        hash_2 = (d*hash_2 + arr[x])%m; 		
    } 
  
    for (int x = 0; x <= len2 - len1; x++) 
    { 
        if ( hash_1 == hash_2 ) 
        { 
            for (y = 0; y < len1; y++) 
            { 
                if (seq[y] != arr[x+y]) 
                    break; 
            } 
  
            if (y == len1) 
                {
					l++;
                    cout << "Sentence " <<sent_line << " of the input text found at line " << line << " of output file"<<std::endl;
					break;
                }
                
        } 

        else if ( x < len2-len1 ) 
        { 
	        int w = d* (hash_2 - arr[x]*h);
            hash_2 = (w + arr[x+len1])%m; 
            
			if (hash_2 < 0)
			{
			 hash_2 = (hash_2 + m);	
			}				
            
        } 
    } 
	return l;
} 

int main() 
{ 

    //string s = "Wikipedia is a free online encyclopedia.include the romantic.He made his Bollywood debut in 1992 with Deewana.this and that.";
    string s = "The United States emerged from the thirteen British colonies established along the East Coast.The end of the Cold War and the collapse of the Soviet Union.United States has a very powerful army.North America migrated from Siberia by way of the Bering land bridge.It is hard for other nation to fight against united nation.";
	istringstream iss(s);
    string strtest;
	int line;
	float q = 0;
	float p =0;
	float total_line = 0;
	float match_line = 0;
    while (getline(iss, strtest, '.')) 
	       {
             if (!strtest.empty())
			 {
			total_line ++;	 
			line = 1;	 
            int m = strtest.length();  
            char seq[m+1];   
            strcpy(seq, strtest.c_str());
			ifstream file;
            file.open("inputtest.txt");
            string st1;
            while(getline(file, st1))
              {	
	        int n = st1.length();  
            char char_array[n+1];   
            strcpy(char_array, st1.c_str());
	        q =   rabinKarp(seq, char_array , line, total_line);
			line ++;
			if(q > 0)
				p++;
               } 
			if(p>0)
               match_line++;				
			 }
          p = 0;
          }	  
	ofstream myfile;
    myfile.open ("output.txt");	
	float plag = 100 * (match_line/total_line);
	cout << " " << std::endl;
	myfile <<"Total match sentence in the given input text is " << match_line << " and total sentence in the given input text is " << total_line << std::endl;
	cout << "Total match sentence in the given input text is " << match_line << " and total sentence in the given input text is " << total_line << std::endl;
    if(plag > 70)
    {
		myfile << "The give file has significant amount of Plagarism and it is " << plag << " %" <<std::endl;
		cout << "The give file has significant amount of Plagarism and it is " << plag << " %" <<std::endl;
	}		
    else
	{
		myfile << "Plagarism is not detected in the given file and it is " << plag << " %" <<std::endl;
		cout << "Plagarism is not detected in the given file and it is " << plag << " %" <<std::endl;
	}
	cout << " " << std::endl;
    return 0; 
}