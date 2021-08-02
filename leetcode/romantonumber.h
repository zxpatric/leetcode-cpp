//
// Created by ZhouP on 3/5/2019.
//

#ifndef CPPSANDBOX_ROMANTONUMBER_H
#define CPPSANDBOX_ROMANTONUMBER_H
using namespace std;

class Solution {
public:

    string trimMs (string s, int& m)
    {
        auto iter = std::find(s.begin(),s.end(), 'M');
        if (iter!=s.end())
        {
            int pos = std::distance(s.begin(), iter);
            if (pos==0)
            {
                m+=1000;
            }
            else if(pos==1)
            {
                if (s[0]=='C')
                    m += 900;
            }
            else
            {

            }

            return trimMs(s.substr(pos+1), m);
        }
        else
        {
            return s;
        }
    }

    string trimDs (string s, int& d)
    {
        auto iter = std::find(s.begin(),s.end(), 'D');
        if (iter!=s.end())
        {
            int pos = std::distance(s.begin(), iter);
            if (pos==0)
            {
                d+=500;
            }
            else if(pos==1)
            {
                if (s[0]=='C')
                    d += 400;
            }
            else
            {

            }

            return trimDs(s.substr(pos+1), d);
        }
        else
        {
            return s;
        }
    }

    string trimCs (string s, int& c)
    {
        auto iter = std::find(s.begin(),s.end(), 'C');
        if (iter!=s.end())
        {
            int pos = std::distance(s.begin(), iter);
            if (pos==0)
            {
                c+=100;
            }
            else if(pos==1)
            {
                if (s[0]=='X')
                    c += 90;
            }
            else
            {

            }

            return trimCs(s.substr(pos+1), c);
        }
        else
        {
            return s;
        }
    }

    string trimLs (string s, int& l)
    {
        auto iter = std::find(s.begin(),s.end(), 'L');
        if (iter!=s.end())
        {
            int pos = std::distance(s.begin(), iter);
            if (pos==0)
            {
                l+=50;
            }
            else if(pos==1)
            {
                if (s[0]=='X')
                    l += 40;
            }
            else
            {

            }

            return trimLs(s.substr(pos+1), l);
        }
        else
        {
            return s;
        }
    }

    string trimXs (string s, int& x)
    {
        auto iter = std::find(s.begin(),s.end(), 'X');
        if (iter!=s.end())
        {
            int pos = std::distance(s.begin(), iter);
            if (pos==0)
            {
                x+=10;
            }
            else if(pos==1)
            {
                if (s[0]=='I')
                    x += 9;
            }
            else
            {

            }

            return trimXs(s.substr(pos+1), x);
        }
        else
        {
            return s;
        }
    }

    string trimVs (string s, int& v)
    {
        auto iter = std::find(s.begin(),s.end(), 'V');
        if (iter!=s.end())
        {
            int pos = std::distance(s.begin(), iter);
            if (pos==0)
            {
                v+=5;
            }
            else if(pos==1)
            {
                if (s[0]=='I')
                    v += 4;
            }
            else
            {

            }

            return trimVs(s.substr(pos+1), v);
        }
        else
        {
            return s;
        }
    }

    string trimIs (string s, int& i)
    {
        auto iter = std::find(s.begin(),s.end(), 'I');
        if (iter!=s.end())
        {
            int pos = std::distance(s.begin(), iter);
            if (pos==0)
            {
                i+=1;
            }
            else
            {

            }

            return trimIs(s.substr(pos+1), i);
        }
        else
        {
            return s;
        }
    }

    int romanToInt(string s) {
        int m(0), d(0), c(0), l(0), x(0), v(0), i(0);

        s = trimMs(s, m);
        s = trimDs(s, d);
        s = trimCs(s, c);
        s = trimLs(s, l);
        s = trimXs(s, x);
        s = trimVs(s, v);
        s = trimIs(s, i);

        return m+d+c+l+x+v+i;
    }
};

#endif //CPPSANDBOX_ROMANTONUMBER_H
